/**
 *  file: FiberHit.cc
 *  date: 2017.04.10
 *
 */

#include "FiberHit.hh"

#include <cstring>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <limits>

#include <std_ostream.hh>

#include "ConfMan.hh"
#include "DCGeomMan.hh"
#include "DebugCounter.hh"
#include "DeleteUtility.hh"
#include "FLHit.hh"
#include "HodoParamMan.hh"
#include "HodoPHCMan.hh"
#include "RawData.hh"

namespace
{
  const std::string& class_name("FiberHit");
  const DCGeomMan&    gGeom = DCGeomMan::GetInstance();
  const HodoParamMan& gHodo = HodoParamMan::GetInstance();
  const HodoPHCMan&   gPHC  = HodoPHCMan::GetInstance();
}

//______________________________________________________________________________
FiberHit::FiberHit( HodoRawHit *object, const char* name )
  : Hodo1Hit(object),
    m_detector_name(name),
    m_segment(-1),
    m_ud(0),
    m_position(-999.),
    m_offset(0),
    m_pair_id(0),
    m_status(false)
{
  debug::ObjectCounter::increase(class_name);
}

//______________________________________________________________________________
FiberHit::~FiberHit( void )
{
  del::ClearContainer( m_hit_container );
  debug::ObjectCounter::decrease(class_name);
}

//______________________________________________________________________________
bool
FiberHit::Calculate( void )
{
  static const std::string func_name("["+class_name+"::"+__func__+"()]");

  if( m_status ){
    hddaq::cerr << func_name << " already calculated" << std::endl;
    return false;
  }

  if( !gHodo.IsReady() ){
    hddaq::cerr << func_name << " HodoParamMan must be initialized" << std::endl;
    return false;
  }

  if( !gPHC.IsReady() ){
    hddaq::cerr << func_name << " HodoPHCMan must be initialized" << std::endl;
    return false;
  }

  // Detector information
  int cid  = m_raw->DetectorId();
  int plid = m_raw->PlaneId();
  int seg  = m_raw->SegmentId();
  m_segment = seg;

  // Geometry calibration
  m_ud = 0; // BFT is allways U
  if( "BFT" == m_detector_name || "SFT-X" == m_detector_name ){
    // case of BFT and SFT X layers
    // They have up and down planes in 1 layer.
    // We treat these 2 planes as 1 dimentional plane.
    // if(1 == m_raw->PlaneId()){
    if ( 1 == m_raw->PlaneId()%2 ) {
      // case of down plane
      m_offset = 0.5;
      m_pair_id  = 1;
    }
    m_pair_id += 2*m_raw->SegmentId();
  }else if(false 
	   || "FBT1-UX1" == m_detector_name 
	   || "FBT1-UX2" == m_detector_name
	   || "FBT2-UX1" == m_detector_name 
	   || "FBT2-UX2" == m_detector_name
	   ){
    m_ud = 0;
    m_pair_id = seg;
  }else if(false
	   || "FBT1-DX1" == m_detector_name 
	   || "FBT1-DX2" == m_detector_name
	   || "FBT2-DX1" == m_detector_name 
	   || "FBT2-DX2" == m_detector_name
	   ){
    m_ud = 1;
    m_pair_id = seg;
  }else{
    // case of SFT UV layers
    // They have only 1 plane in 1 layer.
    m_pair_id = m_raw->SegmentId();
  }

  int DetectorId = gGeom.GetDetectorId( m_detector_name );
  m_position     = gGeom.CalcWirePosition( DetectorId, seg );

  // hit information
  m_multi_hit_l = m_ud==0? m_raw->SizeTdc1()  : m_raw->SizeTdc2();
  m_multi_hit_t = m_ud==0? m_raw->SizeTdcT1() : m_raw->SizeTdcT2();

  std::vector<int> leading_cont, trailing_cont;
  {
    for ( int m = 0; m < m_multi_hit_l; ++m ) {
      leading_cont.push_back( m_ud==0? m_raw->GetTdc1( m ) : m_raw->GetTdc2(m));
    }
    for ( int m = 0; m < m_multi_hit_t; ++m ) {
      trailing_cont.push_back( m_ud==0? m_raw->GetTdcT1( m ): m_raw->GetTdcT2(m));
    }

    std::sort(leading_cont.begin(),  leading_cont.end(),  std::greater<int>());
    std::sort(trailing_cont.begin(), trailing_cont.end(), std::greater<int>());

    int i_t = 0;
    for(int i = 0; i<m_multi_hit_l; ++i){
      data_pair a_pair;

      int leading  = leading_cont.at(i);
      while(i_t < m_multi_hit_t){
	int trailing = trailing_cont.at(i_t);

	if(leading > trailing){
	  a_pair.index_t = i_t;
	  m_pair_cont.push_back(a_pair);
	  break;
	}else{
	  ++i_t;
	}// Goto next trailing
      }

      if(i_t == m_multi_hit_t){
	a_pair.index_t = -1;
	m_pair_cont.push_back(a_pair);
	continue;
      }// no more trailing data
    }// for(i)
  }

  // Delete duplication index_t
  for(int i = 0; i<m_multi_hit_l-1; ++i){
    if(true
       && m_pair_cont.at(i).index_t != -1
       && m_pair_cont.at(i).index_t == m_pair_cont.at(i+1).index_t)
      {
	m_pair_cont.at(i).index_t = -1;
      }
  }// for(i)

  for(int i = 0; i<m_multi_hit_l; ++i){
    // leading
    int leading = leading_cont.at(i);
    double time_leading = -999.;
    if( !gHodo.GetTime(cid, plid, seg, m_ud, leading, time_leading) ){
      hddaq::cerr << "#E " << func_name
		  << " something is wrong at GetTime("
		  << cid  << ", " << plid          << ", " << seg  << ", "
		  << m_ud << ", " << leading  << ", " << time_leading << ")" << std::endl;
      return false;
    }
    m_t.push_back( time_leading );
    m_flag_join.push_back( false );

    // Is there paired trailing ?
    if(m_pair_cont.at(i).index_t == -1){
      m_pair_cont.at(i).time_l  = time_leading;
      m_pair_cont.at(i).time_t  = std::numeric_limits<double>::quiet_NaN();
      m_pair_cont.at(i).ctime_l = time_leading;
      m_pair_cont.at(i).tot     = std::numeric_limits<double>::quiet_NaN();
      continue;
    }

    // trailing
    int trailing = trailing_cont.at(m_pair_cont.at(i).index_t);
    double time_trailing = -999.;
    if( !gHodo.GetTime(cid, plid, seg, m_ud, trailing, time_trailing) ){
      hddaq::cerr << "#E " << func_name
		  << " something is wrong at GetTime("
		  << cid  << ", " << plid          << ", " << seg  << ", "
		  << m_ud << ", " << trailing  << ", " << time_trailing << ")" << std::endl;
      return false;
    }

    double tot           = time_trailing - time_leading;
    double ctime_leading = time_leading;
    gPHC.DoCorrection( cid, plid, seg, m_ud, time_leading, tot, ctime_leading );

    m_a.push_back( tot );
    m_ct.push_back( ctime_leading );

    m_pair_cont.at(i).time_l  = time_leading;
    m_pair_cont.at(i).time_t  = time_trailing;
    m_pair_cont.at(i).ctime_l = ctime_leading;
    m_pair_cont.at(i).tot     = tot;


  }// for(i)

  m_status = true;
  return true;
}

//______________________________________________________________________________
void
FiberHit::Print( const std::string& arg, std::ostream& ost ) const
{
  static const std::string func_name("["+class_name+"::"+__func__+"()]");

  ost << func_name << " " << arg << '\n'
      << std::setw(10) << "DetectorName" << std::setw(8) << m_detector_name << '\n'
      << std::setw(10) << "Segment"      << std::setw(8) << m_segment       << '\n'
      << std::setw(10) << "Position"     << std::setw(8) << m_position      << '\n'
      << std::setw(10) << "Offset"       << std::setw(8) << m_offset        << '\n'
      << std::setw(10) << "PairID"       << std::setw(8) << m_pair_id       << '\n'
      << std::setw(10) << "Status"       << std::setw(8) << m_status        << std::endl;
}
