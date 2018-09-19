/**
 *  file: DCHit.cc
 *  date: 2017.04.10
 *
 */

#include "DCHit.hh"

#include <algorithm>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <sstream>
#include <stdexcept>
#include <string>

#include <std_ostream.hh>

#include "DCDriftParamMan.hh"
#include "DCGeomMan.hh"
#include "DCParameters.hh"
#include "DCTdcCalibMan.hh"
#include "DCLTrackHit.hh"
#include "DebugCounter.hh"
#include "MathTools.hh"
#include "RootHelper.hh"

namespace
{
  const std::string& class_name("DCHit");
  const DCGeomMan&       gGeom  = DCGeomMan::GetInstance();
  const DCTdcCalibMan&   gTdc   = DCTdcCalibMan::GetInstance();
  const DCDriftParamMan& gDrift = DCDriftParamMan::GetInstance();
  const bool SelectTDC1st  = false;
}

//______________________________________________________________________________
DCHit::DCHit( void )
  : m_layer(-1), m_wire(-1),
    m_wpos(-9999.), m_angle(0.),
    m_cluster_size(0.),
    m_mwpc_flag(false),
    m_ofs_dt(0.)
{
  debug::ObjectCounter::increase(class_name);
}

//______________________________________________________________________________
DCHit::DCHit( int layer )
  : m_layer( layer ), m_wire(-1),
    m_wpos(-9999.), m_angle(0.),
    m_cluster_size(0.),
    m_mwpc_flag(false),
    m_ofs_dt(0.)
{
  debug::ObjectCounter::increase(class_name);
}

//______________________________________________________________________________
DCHit::DCHit( int layer, double wire )
  : m_layer(layer), m_wire(wire),
    m_wpos(-9999.), m_angle(0.),
    m_cluster_size(0.),
    m_mwpc_flag(false),
    m_ofs_dt(0.)
{
  debug::ObjectCounter::increase(class_name);
}

//______________________________________________________________________________
DCHit::~DCHit( void )
{
  ClearRegisteredHits();
  debug::ObjectCounter::decrease(class_name);
}

//______________________________________________________________________________
void
DCHit::SetDummyPair()
{
  data_pair a_pair = {0.,
		      0., 
		      std::numeric_limits<double>::quiet_NaN(), 
		      std::numeric_limits<double>::quiet_NaN(), 
		      -1,
		      false,
		      true};
  m_pair_cont.push_back(a_pair);
}

//______________________________________________________________________________
void
DCHit::ClearRegisteredHits( void )
{
  int n = m_register_container.size();
  for(int i=0; i<n; ++i){
    delete m_register_container[i];
  }
}

//______________________________________________________________________________
bool
DCHit::CalcDCObservables( void )
{
  static const std::string func_name("["+class_name+"::"+__func__+"()]");

  if( !gGeom.IsReady() ||
      !gTdc.IsReady()  ||
      !gDrift.IsReady() ){
    return false;
  }

  m_wpos  = gGeom.CalcWirePosition( m_layer,m_wire );
  m_angle = gGeom.GetTiltAngle( m_layer );
  m_z     = gGeom.GetLocalZ( m_layer );

  bool status = true;
  int  nh_tdc      = m_tdc.size();
  int  nh_trailing = m_trailing.size();

  IntVec leading_cont, trailing_cont;

  // Prepare 
  {
    for ( int m = 0; m < nh_tdc; ++m ) {
      leading_cont.push_back( m_tdc.at( m ) );
    }
    for ( int m = 0; m < nh_trailing; ++m ) {
      trailing_cont.push_back( m_trailing.at( m ) );
    }

    std::sort(leading_cont.begin(),  leading_cont.end(),  std::greater<int>());
    std::sort(trailing_cont.begin(), trailing_cont.end(), std::greater<int>());

    int i_t = 0;
    for(int i = 0; i<nh_tdc; ++i){
      data_pair a_pair = {0., 0., 
			  std::numeric_limits<double>::quiet_NaN(), 
			  std::numeric_limits<double>::quiet_NaN(), 
			  -1, false, false};

      int leading  = leading_cont.at(i);
      while(i_t < nh_trailing){
	int trailing = trailing_cont.at(i_t);

	if(leading > trailing){
	  a_pair.index_t = i_t;
	  m_pair_cont.push_back(a_pair);
	  break;
	}else{
	  ++i_t;
	}// Goto next trailing
      }

      if(i_t == nh_trailing){
	a_pair.index_t = -1;
	m_pair_cont.push_back(a_pair);
	continue;
      }// no more trailing data
    }// for(i)
  }

  // Delete duplication index_t
  for(int i = 0; i<nh_tdc-1; ++i){
    if(true
       && m_pair_cont.at(i).index_t != -1
       && m_pair_cont.at(i).index_t == m_pair_cont.at(i+1).index_t)
      {
	m_pair_cont.at(i).index_t = -1;
      }
  }// for(i)


  for ( int i=0; i<nh_tdc; ++i ) {
    double ctime;
    if( !gTdc.GetTime( m_layer, m_wire, leading_cont.at(i), ctime ) ){
      return false;
    } 

    double dtime, dlength;
    double corrected_ctime = ctime + m_ofs_dt;
    if( !gDrift.CalcDrift( m_layer, m_wire, corrected_ctime, dtime, dlength ) ){
      status = false;
    } 

    m_pair_cont.at(i).drift_time   = dtime;
    m_pair_cont.at(i).drift_length = dlength;

    if(m_pair_cont.at(i).index_t != -1){
      double trailing_ctime;
      gTdc.GetTime( m_layer, m_wire, trailing_cont.at(m_pair_cont.at(i).index_t), trailing_ctime );
      m_pair_cont.at(i).trailing_time = trailing_ctime;
      m_pair_cont.at(i).tot           = ctime - trailing_ctime;
    }else{
      m_pair_cont.at(i).trailing_time = std::numeric_limits<double>::quiet_NaN();
      m_pair_cont.at(i).tot           = std::numeric_limits<double>::quiet_NaN();
    }


    switch( m_layer ){
      // BC3,4
    case 113: case 114: case 115: case 116: case 117: case 118:
    case 119: case 120: case 121: case 122: case 123: case 124:
      if( MinDLBc[m_layer-100] < m_pair_cont.at(i).drift_length && m_pair_cont.at(i).drift_length < MaxDLBc[m_layer-100] ){
	m_pair_cont.at(i).dl_range = true;
      } 
      break;

      // SDC1,2,3
    case 1: case 2: case 3: case 4: case 5: case 6:
    case 31: case 32: case 33: case 34:
    case 35: case 36: case 37: case 38:
      //      m_pair_cont.at(i).dl_range = true;
      if( MinDLSdc[m_layer] < m_pair_cont.at(i).drift_length && m_pair_cont.at(i).drift_length < MaxDLSdc[m_layer] ){
      	m_pair_cont.at(i).dl_range = true;
      }
      break;
    default:
      hddaq::cout << "#E " << func_name << " "
		  << "invalid layer id : " << m_layer << std::endl;
      status = false;
      break;
    }
  }

  if( SelectTDC1st && status ){
    int       tdc1st   = 0;
    data_pair pair1st;
    for( int i=0; i<nh_tdc; ++i ){
      if( tdc1st < leading_cont[i]
	  /* && m_dl_range[i] */ ){
	tdc1st   = leading_cont[i];
	pair1st  = m_pair_cont.at(i);
      }
    }
    if( tdc1st>0 ){
      m_tdc.clear();
      m_pair_cont.clear();
      m_tdc.push_back( tdc1st );
      m_pair_cont.push_back( pair1st );
    } else {
      m_tdc.clear();
      m_pair_cont.clear();
    }
  }

  return status;
}

//______________________________________________________________________________
bool
DCHit::CalcMWPCObservables( void )
{
  static const std::string func_name("["+class_name+"::"+__func__+"()]");

  if( !gGeom.IsReady() || !gTdc.IsReady() )
    return false;

  m_angle = gGeom.GetTiltAngle( m_layer );
  m_wpos  = gGeom.CalcWirePosition( m_layer, m_wire );
  m_z     = gGeom.GetLocalZ( m_layer );

  bool status = true;
  int  nh_tdc      = m_tdc.size();
  int  nh_trailing = m_trailing.size();

  IntVec leading_cont, trailing_cont;

  // Prepare 
  {
    for ( int m = 0; m < nh_tdc; ++m ) {
      leading_cont.push_back( m_tdc.at( m ) );
    }
    for ( int m = 0; m < nh_trailing; ++m ) {
      trailing_cont.push_back( m_trailing.at( m ) );
    }

    std::sort(leading_cont.begin(),  leading_cont.end(),  std::greater<int>());
    std::sort(trailing_cont.begin(), trailing_cont.end(), std::greater<int>());

    int i_t = 0;
    for(int i = 0; i<nh_tdc; ++i){
      data_pair a_pair = {0., 0.,
			  std::numeric_limits<double>::quiet_NaN(), 
			  std::numeric_limits<double>::quiet_NaN(), 
			  -1, false, false};

      int leading  = leading_cont.at(i);
      while(i_t < nh_trailing){
	int trailing = trailing_cont.at(i_t);

	if(leading > trailing){
	  a_pair.index_t = i_t;
	  m_pair_cont.push_back(a_pair);
	  break;
	}else{
	  ++i_t;
	}// Goto next trailing
      }

      if(i_t == nh_trailing){
	a_pair.index_t = -1;
	m_pair_cont.push_back(a_pair);
	continue;
      }// no more trailing data
    }// for(i)
  }

  // Delete duplication index_t
  for(int i = 0; i<nh_tdc-1; ++i){
    if(true
       && m_pair_cont.at(i).index_t != -1
       && m_pair_cont.at(i).index_t == m_pair_cont.at(i+1).index_t)
      {
	m_pair_cont.at(i).index_t = -1;
      }
  }// for(i)


  for ( int i=0; i<nh_tdc; ++i ) {
    double ctime;
    if( !gTdc.GetTime( m_layer, m_wire, leading_cont.at(i), ctime ) ){
      return false;
    } 

    double dtime, dlength;
    if( !gDrift.CalcDrift( m_layer, m_wire, ctime, dtime, dlength ) ){
      status = false;
    } 

    m_pair_cont.at(i).drift_time   = dtime;
    m_pair_cont.at(i).drift_length = dlength;

    if(m_pair_cont.at(i).index_t != -1){
      double trailing_ctime;
      gTdc.GetTime( m_layer, m_wire, trailing_cont.at(i), trailing_ctime );
      m_pair_cont.at(i).trailing_time = trailing_ctime;
      m_pair_cont.at(i).tot           = ctime - trailing_ctime;
    }else{
      m_pair_cont.at(i).trailing_time = std::numeric_limits<double>::quiet_NaN();
      m_pair_cont.at(i).tot           = std::numeric_limits<double>::quiet_NaN();
    }

    if( m_pair_cont.at(i).drift_time > MinDLBc[m_layer-100] && m_pair_cont.at(i).drift_time < MaxDLBc[m_layer-100] ){
      m_pair_cont.at(i).dl_range = true;
    }else{
      status = false;
    } 
  }

  return status;
}

//______________________________________________________________________________
bool
DCHit::CalcFiberObservables( void )
{
  static const std::string func_name("["+class_name+"::"+__func__+"()]");

  if( !gGeom.IsReady() ) return false;

  m_angle = gGeom.GetTiltAngle( m_layer );
  m_z     = gGeom.GetLocalZ( m_layer );

  bool status = true;
  std::size_t nh_tdc = m_tdc.size();

  for( std::size_t i=0; i<nh_tdc; i++ ){
    data_pair a_pair = {(double)m_tdc[i], 0., 
			std::numeric_limits<double>::quiet_NaN(), 
			std::numeric_limits<double>::quiet_NaN(), 
			-1, false, true};
    m_pair_cont.push_back( a_pair );
  }

  return status;
}

//______________________________________________________________________________
double
DCHit::GetResolution( void ) const
{
  return gGeom.GetResolution(m_layer);
}

//______________________________________________________________________________
void
DCHit::TotCut(double min_tot, bool adopt_nan)
{
  auto itr_new_end = 
    std::remove_if(m_pair_cont.begin(), m_pair_cont.end(),
		   [min_tot, adopt_nan](data_pair a_pair)->bool 
		   {return (isnan(a_pair.tot) && adopt_nan) ? false : !(a_pair.tot > min_tot);}
		   );
  m_pair_cont.erase(itr_new_end, m_pair_cont.end());
}

//______________________________________________________________________________
void
DCHit::GateDriftTime(double min, double max, bool select_1st)
{
  auto itr_new_end = 
    std::remove_if(m_pair_cont.begin(), m_pair_cont.end(),
		   [min, max](data_pair a_pair)->bool
		   {return !(min < a_pair.drift_time && a_pair.drift_time < max);}
		   );
  m_pair_cont.erase(itr_new_end, m_pair_cont.end());
  if(0 == m_pair_cont.size()) return;
  
  if(select_1st) m_pair_cont.erase(m_pair_cont.begin()+1, m_pair_cont.end());
}

//______________________________________________________________________________
void
DCHit::Print( const std::string& arg, std::ostream& ost ) const
{
  static const std::string func_name("["+class_name+"::"+__func__+"()]");

  const int w = 16;
  ost << "#D " << func_name << " " << arg << std::endl
      << std::setw(w) << std::left << "layer" << m_layer << std::endl
      << std::setw(w) << std::left << "wire"  << m_wire  << std::endl
      << std::setw(w) << std::left << "wpos"  << m_wpos  << std::endl
      << std::setw(w) << std::left << "angle" << m_angle << std::endl
      << std::setw(w) << std::left << "z"     << m_z     << std::endl;

  ost << std::setw(w) << std::left << "tdc" << m_tdc.size() << " : ";
  std::copy( m_tdc.begin(), m_tdc.end(),
	     std::ostream_iterator<int>(ost, " ") );
  ost << std::endl;

  if(m_mwpc_flag){
    ost << std::endl
	<< std::setw(w) << std::left << "clsize" << m_cluster_size << std::endl
	<< std::setw(w) << std::left << "mean wire" << m_mwpc_wire << std::endl
	<< std::setw(w) << std::left << "mean pos"  << m_mwpc_wpos << std::endl;
  }
}
