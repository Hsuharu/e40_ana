/**
 *  file: DCLTrackHit.cc
 *  date: 2017.04.10
 *
 */

#include "DCLTrackHit.hh"

#include <cmath>
#include <cstring>
#include <iostream>
#include <sstream>
#include <stdexcept>

#include <std_ostream.hh>

#include "DCAnalyzer.hh"
#include "MathTools.hh"

namespace
{
  const std::string& class_name("DCLTrackHit");
}

//______________________________________________________________________________
DCLTrackHit::DCLTrackHit( DCHit *hit, double pos, int nh )
  : m_hit(hit),
    m_nth_hit(nh),
    m_local_hit_pos(pos),
    m_cal_pos(-9999.),
    m_xcal(-9999.),
    m_ycal(-9999.),
    m_ucal(-9999.),
    m_vcal(-9999.),
    m_honeycomb(false)
{
  debug::ObjectCounter::increase(class_name);
  m_hit->RegisterHits(this);
}

//______________________________________________________________________________
DCLTrackHit::DCLTrackHit( const DCLTrackHit& right )
  : m_hit(right.m_hit),
    m_nth_hit(right.m_nth_hit),
    m_local_hit_pos(right.m_local_hit_pos),
    m_cal_pos(right.m_cal_pos),
    m_xcal(right.m_xcal),
    m_ycal(right.m_ycal),
    m_ucal(right.m_ucal),
    m_vcal(right.m_vcal),
    m_honeycomb(right.m_honeycomb)
{
  m_hit->RegisterHits(this);
  debug::ObjectCounter::increase(class_name);
}

//______________________________________________________________________________
DCLTrackHit::~DCLTrackHit( void )
{
  debug::ObjectCounter::decrease(class_name);
}

//______________________________________________________________________________
double
DCLTrackHit::GetLocalCalPos( void ) const
{
  double angle = m_hit->GetTiltAngle()*math::Deg2Rad();
  return m_xcal*std::cos(angle) + m_ycal*std::sin(angle);
}

//______________________________________________________________________________
double
DCLTrackHit::GetResidual( void ) const
{
  double a    = GetTiltAngle()*math::Deg2Rad();
  double dsdz = m_ucal*std::cos(a)+m_vcal*std::sin(a);
  double coss = m_honeycomb ? std::cos( std::atan(dsdz) ) : 1.;
  double scal = GetLocalCalPos();
  double wp   = GetWirePosition();
  double ss   = wp+(m_local_hit_pos-wp)/coss;
  return (ss-scal)*coss;
}

//______________________________________________________________________________
void
DCLTrackHit::Print( const std::string& arg ) const
{
  m_hit->Print( arg );
  hddaq::cout << "local_hit_pos " << m_local_hit_pos << std::endl
	      << "residual " << GetResidual() << std::endl
	      << "honeycomb " << m_honeycomb << std::endl;
}

//______________________________________________________________________________
bool
DCLTrackHit::ReCalc( bool applyRecursively )
{
  if( applyRecursively ){
    if( !m_hit->ReCalcDC(applyRecursively) ) return false;
    // if( !m_hit->ReCalcDC(applyRecursively)   ||
    // 	!m_hit->ReCalcMWPC(applyRecursively) ){
    //   return false;
    // }
  }

  double wp = GetWirePosition();
  double dl = GetDriftLength();

  if( m_local_hit_pos>wp )  m_local_hit_pos = wp+dl;
  else                      m_local_hit_pos = wp-dl;

  return true;
}
