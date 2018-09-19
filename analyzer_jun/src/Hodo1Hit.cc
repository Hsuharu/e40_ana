/**
 *  file: Hodo1Hit.cc
 *  date: 2017.04.10
 *
 */

#include "Hodo1Hit.hh"

#include <cstring>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>

#include <std_ostream.hh>

#include "DebugCounter.hh"
#include "HodoParamMan.hh"
#include "HodoPHCMan.hh"
#include "RawData.hh"

namespace
{
  const std::string& class_name("Hodo1Hit");
  const HodoParamMan& gHodo = HodoParamMan::GetInstance();
  const HodoPHCMan&   gPHC  = HodoPHCMan::GetInstance();
}

//______________________________________________________________________________
HodoHit::HodoHit(){};
HodoHit::~HodoHit(){};

//______________________________________________________________________________
Hodo1Hit::Hodo1Hit( HodoRawHit *rhit, int index )
  : HodoHit(), m_raw(rhit), m_is_calculated(false), m_index(index)
{
  debug::ObjectCounter::increase(class_name);
}

//______________________________________________________________________________
Hodo1Hit::~Hodo1Hit( void )
{
  debug::ObjectCounter::decrease(class_name);
}

//______________________________________________________________________________
bool
Hodo1Hit::Calculate( void )
{
  static const std::string func_name("["+class_name+"::"+__func__+"()]");

  if( m_is_calculated ){
    hddaq::cout << func_name << " already calculated" << std::endl;
    return false;
  }

  if( m_raw->GetNumOfTdcHits()!=1 )
    return false;

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

  // hit information
  m_multi_hit_l = m_raw->SizeTdc1()  > m_raw->SizeTdc2()?  m_raw->SizeTdc1()  : m_raw->SizeTdc2();
  m_multi_hit_t = m_raw->SizeTdcT1() > m_raw->SizeTdcT2()? m_raw->SizeTdcT1() : m_raw->SizeTdcT2();
  int UorD=0;
  int adc = m_raw->GetAdc1(0);
  if( 0 > m_raw->GetTdc1(0) ){
    UorD=1;
    adc = m_raw->GetAdc2(0);
  }

  double dE = 0.;
  if( adc>=0 ){
    if( !gHodo.GetDe( cid, plid, seg, UorD, adc, dE ) ){
      hddaq::cerr << "#E " << func_name
		  << " something is wrong at GetDe("
		  << cid  << ", " << plid << ", " << seg << ", "
		  << UorD << ", " << adc  << ", " << dE  << ")" << std::endl;
      return false;
    }
  }

  m_a.push_back(dE);

  int mhit = m_multi_hit_l;
  for( int m=0; m<mhit; ++m ){
    int    tdc  = -999;
    double time = -999.;
    if(0 == UorD){
      tdc = m_raw->GetTdc1(m);
    }else{
      tdc = m_raw->GetTdc2(m);
    }

    if( tdc<0 ) continue;

    if( !gHodo.GetTime( cid, plid, seg, UorD, tdc, time ) ){
      hddaq::cerr << "#E " << func_name
		  << " something is wrong at GetTime("
		  << cid  << ", " << plid << ", " << seg  << ", "
		  << UorD << ", " << tdc  << ", " << time << ")" << std::endl;
      return false;
    }
    m_t.push_back(time);

    double ctime = time;
    gPHC.DoCorrection(cid, plid, seg, UorD, time, dE, ctime );
    m_ct.push_back(ctime);

    m_flag_join.push_back(false);
  }

  m_is_calculated = true;
  return true;
}

// ____________________________________________________________
bool
Hodo1Hit::JoinedAllMhit()
{
  bool ret = true;
  for(int i = 0; i<m_flag_join.size(); ++i){
    ret = ret & m_flag_join[i];
  }// for(i)
  return ret;
}
