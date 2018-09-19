/**
 *  file: BH2Hit.cc
 *  date: 2017.04.10
 *
 */

#include "BH2Hit.hh"

#include <cmath>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>

#include <std_ostream.hh>

#include "HodoParamMan.hh"
#include "HodoPHCMan.hh"
#include "RawData.hh"

namespace
{
  const std::string& class_name("BH2Hit");
  const HodoParamMan& gHodo = HodoParamMan::GetInstance();
  //  const HodoPHCMan&   gPHC  = HodoPHCMan::GetInstance();
}

//______________________________________________________________________________
BH2Hit::BH2Hit( HodoRawHit *rhit, double max_time_diff )
  : Hodo2Hit(rhit, max_time_diff),
    m_time_offset(0.)
{
  debug::ObjectCounter::increase(class_name);
}

//______________________________________________________________________________
BH2Hit::~BH2Hit( void )
{
  debug::ObjectCounter::decrease(class_name);
}

//______________________________________________________________________________
bool
BH2Hit::Calculate( void )
{
  static const std::string func_name("["+class_name+"::"+__func__+"()]");

  if(!Hodo2Hit::Calculate()) return false;

  int cid  = m_raw->DetectorId();
  int plid = m_raw->PlaneId();
  int seg  = m_raw->SegmentId();
  gHodo.GetTime( cid, plid, seg, 2, 0, m_time_offset );

  return true;
}
