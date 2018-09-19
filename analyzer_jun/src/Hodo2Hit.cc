/**
 *  file: Hodo2Hit.cc
 *  date: 2017.04.10
 *
 */

#include "Hodo2Hit.hh"

#include <cmath>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>

#include "DebugCounter.hh"
#include "HodoParamMan.hh"
#include "HodoPHCMan.hh"
#include "RawData.hh"

#include <std_ostream.hh>

namespace
{
  const std::string& class_name("Hodo2Hit");
  const HodoParamMan& gHodo = HodoParamMan::GetInstance();
  const HodoPHCMan&   gPHC = HodoPHCMan::GetInstance();
}

//______________________________________________________________________________
Hodo2Hit::Hodo2Hit( HodoRawHit *rhit, double max_time_diff)
  : HodoHit(), m_raw(rhit),
    m_is_calculated(false),
    m_is_tof(false),
    m_max_time_diff(max_time_diff)
{
  debug::ObjectCounter::increase(class_name);
}

//______________________________________________________________________________
Hodo2Hit::~Hodo2Hit( void )
{
  debug::ObjectCounter::decrease(class_name);
}

//______________________________________________________________________________
bool
Hodo2Hit::Calculate( void )
{
  static const std::string func_name("["+class_name+"::"+__func__+"()]");

  if( m_is_calculated ){
    hddaq::cout << func_name << " already calculated" << std::endl;
    return false;
  }

  if( m_raw->GetNumOfTdcHits()!=2 ){
    return false;
  }

  if( !gHodo.IsReady() ){
    hddaq::cout << func_name << " HodoParamMan must be initialized" << std::endl;
    return false;
  }

  if( !gPHC.IsReady() ){
    hddaq::cout << func_name << " HodoPHCMan must be initialized" << std::endl;
    return false;
  }

  int cid  = m_raw->DetectorId();
  int plid = m_raw->PlaneId();
  int seg  = m_raw->SegmentId();
  int adc1 = m_raw->GetAdc1(), adc2=m_raw->GetAdc2();

  double offset_vtof = 0;
  if(m_is_tof){
    gHodo.GetTime( cid, plid, seg, 2, 0, offset_vtof );
    offset_vtof = offset_vtof;
  }// offset vtof

  double dE1 = 0., dE2 = 0.;
  if( adc1>=0 ){
    if( !gHodo.GetDe( cid, plid, seg, 0, adc1, dE1 ) ){
      hddaq::cerr << "#E " << func_name
		  << " something is wrong at GetDe("
		  << cid  << ", " << plid << ", " << seg  << ", "
		  << "0, " << adc1 << ", " << dE1 << ")" << std::endl;
      return false;
    }
  }
  if( adc2>=0 ){
    if( !gHodo.GetDe( cid, plid, seg, 1, adc2, dE2 ) ){
      hddaq::cerr << "#E " << func_name
		  << " something is wrong at GetDe("
		  << cid  << ", " << plid << ", " << seg  << ", "
		  << "0, " << adc2 << ", " << dE2 << ")" << std::endl;
      return false;
    }
  }

  m_a1.push_back( dE1 );
  m_a2.push_back( dE2 );

  // Multi-hit analysis ________________________________________________________
  int n_mhit1 = m_raw->SizeTdc1();
  int n_mhit2 = m_raw->SizeTdc2();

  // local container
  std::vector<double> time1;
  std::vector<double> time2;
  std::vector<double> ctime1;
  std::vector<double> ctime2;
  
  // Tdc1
  for(int i = 0; i<n_mhit1; ++i){
    int tdc = m_raw->GetTdc1(i);

    double time = 0.;
    if( !gHodo.GetTime( cid, plid, seg, 0, tdc, time )){
      hddaq::cerr << "#E " << func_name
		  << " something is wrong at GetTime("
		  << cid  << ", " << plid << ", " << seg  << ", "
		  << "U, " << tdc << ", " << "time"
		  << ")" << std::endl;
      return false;
    }

    time1.push_back(time);

    double ctime = -999.;
    gPHC.DoCorrection( cid, plid, seg, 0, time, dE1, ctime );
    ctime1.push_back(ctime);
  }// for(i)

  // Tdc2
  for(int i = 0; i<n_mhit2; ++i){
    int tdc = m_raw->GetTdc2(i);

    double time = 0.;
    if( !gHodo.GetTime( cid, plid, seg, 1, tdc, time )){
      hddaq::cerr << "#E " << func_name
		  << " something is wrong at GetTime("
		  << cid  << ", " << plid << ", " << seg  << ", "
		  << "D, " << tdc << ", " << "time"
		  << ")" << std::endl;
      return false;
    }

    time2.push_back(time);

    double ctime = -999.;
    gPHC.DoCorrection( cid, plid, seg, 1, time, dE2, ctime );
    ctime2.push_back(ctime);
  }// for(i)

  std::sort(time1.begin(),   time1.end(), std::greater<double>());
  std::sort(time2.begin(),   time2.end(), std::greater<double>());
  std::sort(ctime1.begin(), ctime1.end(), std::greater<double>());
  std::sort(ctime2.begin(), ctime2.end(), std::greater<double>());

  // Make coincidence
  for(int i = 0, i_d = 0, last_d = 0; i<n_mhit1; ++i){
    while(i_d < n_mhit2){
      if(abs(time1[i]-time2[i_d]) < m_max_time_diff){
	// Coincidence
	data_pair a_pair;
	a_pair.time1   = time1[i]     + offset_vtof;
	a_pair.time2   = time2[i_d]   + offset_vtof;
	a_pair.ctime1  = ctime1[i]    + offset_vtof;
	a_pair.ctime2  = ctime2[i_d]  + offset_vtof;
	m_pair_cont.push_back(a_pair);
	last_d         = i_d+1;
	++i_d;

	m_flag_join.push_back(false);
	break;
      }
      ++i_d;
    }// go to next D hit

    if(last_d == n_mhit2) break; // no more D hit
    if(i_d == n_mhit2-1) i_d = last_d;
  }// for(i)

  if(m_pair_cont.size() == 0) return false;
  
  m_is_calculated = true;

  return true;
}

// ____________________________________________________________
bool
Hodo2Hit::JoinedAllMhit()
{
  bool ret = true;
  for(int i = 0; i<m_flag_join.size(); ++i){
    ret = ret & m_flag_join[i];
  }// for(i)
  return ret;
}
