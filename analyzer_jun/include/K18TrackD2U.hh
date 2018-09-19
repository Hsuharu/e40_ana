/**
 *  file: K18TrackD2U.hh
 *  date: 2017.04.10
 *
 */

#ifndef K18_TRACK_D2U_HH
#define K18_TRACK_D2U_HH

#include "ThreeVector.hh"

#include <vector>
#include <functional>

class DCLocalTrack;
class TrackHit;
class DCAnalyzer;
class DCHit;

//______________________________________________________________________________
class K18TrackD2U
{
public:
  K18TrackD2U( double LocalX, DCLocalTrack *tout, double P0 );
  ~K18TrackD2U( void );

private:
  K18TrackD2U( void );
  K18TrackD2U( const K18TrackD2U & );
  K18TrackD2U& operator= ( const K18TrackD2U & );

private:
  double        m_local_x;
  DCLocalTrack *m_track_out;
  double        m_p0;
  double        m_Xi, m_Yi, m_Ui, m_Vi;
  double        m_Xo, m_Yo, m_Uo, m_Vo;
  bool          m_status;
  double        m_delta;
  double        m_delta3rd;
  bool          m_good_for_analysis;

public:
  ThreeVector   BeamMomentumD2U( void ) const;
  bool          CalcMomentumD2U( void );
  double        Delta( void ) const { return m_delta; }
  double        Delta3rd( void ) const { return m_delta3rd; }
  double        GetChiSquare( void ) const;
  bool          GoodForAnalysis( bool status );
  bool          GoodForAnalysis( void ) const { return m_good_for_analysis; }
  double        P( void ) const { return m_p0*(1.+m_delta); }
  double        P3rd( void ) const { return m_p0*(1.+m_delta3rd); }
  bool          StatusD2U( void ) const { return m_status; }
  DCLocalTrack* TrackOut( void ) { return m_track_out; }
  double        Uin( void )  const { return m_Ui; }
  double        Uout( void ) const { return m_Uo; }
  double        Utgt( void ) const;
  double        Vin( void )  const { return m_Vi; }
  double        Vout( void ) const { return m_Vo; }
  double        Vtgt( void ) const;
  double        Xin( void )  const { return m_Xi; }
  double        Xout( void ) const { return m_Xo; }
  double        Xtgt( void ) const;
  double        Yin( void )  const { return m_Yi; }
  double        Yout( void ) const { return m_Yo; }
  double        Ytgt( void ) const;
  bool          ReCalc( bool applyRecursively=false );

};

#endif
