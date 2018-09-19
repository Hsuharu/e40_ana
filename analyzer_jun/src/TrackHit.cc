/**
 *  file: TrackHit.cc
 *  date: 2017.04.10
 *
 */

#include "TrackHit.hh"

#include <cstring>
#include <sstream>
#include <stdexcept>

#include "DCGeomMan.hh"
#include "DCLocalTrack.hh"
#include "DebugCounter.hh"

namespace
{
  const std::string& class_name("TrackHit");
}

//______________________________________________________________________________
TrackHit::TrackHit( DCLTrackHit *hit )
  : m_dcltrack_hit(hit)
{
  debug::ObjectCounter::increase(class_name);
}

//______________________________________________________________________________
TrackHit::~TrackHit( void )
{
  debug::ObjectCounter::decrease(class_name);
}

//______________________________________________________________________________
double
TrackHit::GetLocalHitPos( void ) const
{
  return m_dcltrack_hit->GetLocalHitPos();
}

//______________________________________________________________________________
double
TrackHit::GetResidual( void ) const
{
  double a = GetTiltAngle()*math::Deg2Rad();
  double u = m_cal_global_mom.x()/m_cal_global_mom.z();
  double v = m_cal_global_mom.y()/m_cal_global_mom.z();
  double dsdz = u*std::cos(a)+v*std::sin(a);
  double coss = IsHoneycomb() ? std::cos( std::atan(dsdz) ) : 1.;
  double wp   = GetWirePosition();
  double ss   = wp+(GetLocalHitPos()-wp)/coss;
  return (ss-m_cal_local_pos)*coss;
}

//______________________________________________________________________________
double
TrackHit::GetTiltAngle( void ) const
{
  return m_dcltrack_hit->GetTiltAngle();
}

//______________________________________________________________________________
bool
TrackHit::ReCalc( bool applyRecursively )
{
  if( applyRecursively )
    return m_dcltrack_hit->ReCalc(applyRecursively);
  else
    return true;
}
