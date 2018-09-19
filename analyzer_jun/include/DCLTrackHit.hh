/**
 *  file: DCLTrackHit.hh
 *  date: 2017.04.10
 *
 */

#ifndef DC_LTRACK_HIT_HH
#define DC_LTRACK_HIT_HH

#include "DCHit.hh"

#include "MathTools.hh"

class DCAnalyzer;

//______________________________________________________________________________
class DCLTrackHit
{
public:
  DCLTrackHit( DCHit *hit, double pos, int nh );
  DCLTrackHit( const DCLTrackHit& right );

private:
  ~DCLTrackHit( void );

private:
  DCHit  *m_hit;
  int     m_nth_hit;
  double  m_local_hit_pos;
  double  m_cal_pos;
  double  m_xcal;
  double  m_ycal;
  double  m_ucal;
  double  m_vcal;
  bool    m_honeycomb;

public:
  void   SetLocalHitPos( double xl )                 { m_local_hit_pos = xl; }
  void   SetCalPosition( double x, double y )        { m_xcal = x; m_ycal = y; }
  void   SetCalUV( double u, double v )              { m_ucal = u; m_vcal = v; }
  void   SetHoneycomb( bool flag=true )              { m_honeycomb = flag;     }
  bool   IsHoneycomb( void )                   const { return m_honeycomb; }
  int    GetLayer( void )                      const { return m_hit->GetLayer(); }
  double GetWire( void )                       const { return m_hit->GetWire(); }
  int    GetTdcVal( void )                     const { return m_hit->GetTdcVal(m_nth_hit); }
  int    GetTdcSize( void )                    const { return m_hit->GetTdcSize(); }
  double GetDriftTime( void )                  const { return m_hit->GetDriftTime(m_nth_hit); }
  void   SetDriftTime( int ith, double dt )          { m_hit->SetDriftTime(ith, dt); }
  double GetDriftLength( void )                const { return m_hit->GetDriftLength(m_nth_hit); }
  void   SetDriftLength( int ith, double dl )        { m_hit->SetDriftLength(ith, dl); }
  double GetTrailingTime( void )               const { return m_hit->GetTrailingTime(m_nth_hit); }
  double GetTot( void )                        const { return m_hit->GetTot(m_nth_hit); }

  DCHit* GetHit( void ) const { return m_hit; }

  double GetTiltAngle( void )    const { return m_hit->GetTiltAngle(); }
  double GetWirePosition( void ) const { return m_hit->GetWirePosition(); }
  double GetLocalHitPos( void )  const { return m_local_hit_pos; }
  double GetLocalCalPos( void )  const;

  double GetXcal( void )     const { return m_xcal; }
  double GetYcal( void )     const { return m_ycal; }
  double GetUcal( void )     const { return m_ucal; }
  double GetVcal( void )     const { return m_vcal; }
  double GetResidual( void ) const;
  double GetResolution( void ) const { return m_hit->GetResolution(); }

  ///// for XUV tracking
  void   SetLocalCalPosVXU( double xcl ) { m_cal_pos=xcl; }
  double GetLocalCalPosVXU( void ) const { return m_cal_pos; }
  double GetResidualVXU( void )    const { return m_local_hit_pos-m_cal_pos; }

  ///// for TOF
  double GetZ( void ) const { return m_hit->GetZ(); }

  void JoinTrack( void ) { m_hit->JoinTrack(m_nth_hit); }
  void QuitTrack( void ) { m_hit->QuitTrack(m_nth_hit); }
  bool BelongToTrack( void ) const { return m_hit->BelongToTrack(m_nth_hit); }

  void Print( const std::string& arg="" ) const;

  bool ReCalc( bool applyRecursively=false );

  friend class DCHit;
};

#endif
