/**
 *  file: TrackHit.hh
 *  date: 2017.04.10
 *
 */

#ifndef TRACK_HIT_HH
#define TRACK_HIT_HH

#include "DCLTrackHit.hh"
#include "ThreeVector.hh"

#include <cstddef>

class DCLocalTrack;

//______________________________________________________________________________
class TrackHit
{
public:
  explicit TrackHit( DCLTrackHit *hit );
  ~TrackHit( void );

private:
  TrackHit( const TrackHit& );
  TrackHit& operator =( const TrackHit& );

private:
  DCLTrackHit *m_dcltrack_hit;
  ThreeVector  m_cal_global_mom;
  ThreeVector  m_cal_global_pos;
  double       m_cal_local_pos;

public:
  bool               IsHoneycomb( void ) const { return m_dcltrack_hit->IsHoneycomb(); }
  void               SetCalGMom( const ThreeVector &mom ) { m_cal_global_mom = mom; }
  void               SetCalGPos( const ThreeVector &pos ) { m_cal_global_pos = pos; }
  void               SetCalLPos( double pos )             { m_cal_local_pos=pos; }
  DCLTrackHit*       GetHit( void )                       { return m_dcltrack_hit; }
  double             GetWirePosition( void ) const { return m_dcltrack_hit->GetWirePosition(); }
  int                GetLayer( void )       const { return m_dcltrack_hit->GetLayer(); }
  double             GetLocalHitPos( void ) const;
  const ThreeVector& GetCalGPos( void )     const { return m_cal_global_pos; }
  double             GetCalLPos( void )     const { return m_cal_local_pos; }
  double             GetResidual( void )    const;
  double             GetResolution( void )  const { return m_dcltrack_hit->GetResolution(); }
  double             GetTiltAngle( void )   const;
  DCLTrackHit*       GetDCLTrack( void ){ return m_dcltrack_hit; }
  bool               ReCalc( bool applyRecursively=false );
};

#endif
