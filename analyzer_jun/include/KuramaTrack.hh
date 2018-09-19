/**
 *  file: KuramaTrack.hh
 *  date: 2017.04.10
 *
 */

#ifndef KURAMA_TRACK_HH
#define KURAMA_TRACK_HH

#include "RungeKuttaUtilities.hh"
#include "ThreeVector.hh"

#include <vector>
#include <iosfwd>
#include <iostream>
#include <functional>

#include <std_ostream.hh>

class DCLocalTrack;
class TrackHit;
class DCAnalyzer;
class Hodo2Hit;

//______________________________________________________________________________
class KuramaTrack
{
public:
  KuramaTrack( DCLocalTrack *track_in, DCLocalTrack *track_out );
  ~KuramaTrack( void );

private:
  KuramaTrack( const KuramaTrack& );
  KuramaTrack& operator =( const KuramaTrack& );

public:
  enum RKstatus { kInit,
		  kPassed,
		  kExceedMaxPathLength,
		  kExceedMaxStep,
		  kFailedTraceLast,
		  kFailedGuess,
		  kFailedSave,
		  kFatal,
		  nRKstatus };

private:
  std::string             s_status[nRKstatus];
  RKstatus                m_status;
  DCLocalTrack           *m_track_in;
  DCLocalTrack           *m_track_out;
  double                  m_tof_seg;
  double                  m_initial_momentum;
  std::vector<TrackHit*>  m_hit_array;
  RKHitPointContainer     m_HitPointCont;
  int                     m_n_iteration;
  int                     m_nef_iteration;
  double                  m_chisqr;
  double                  m_polarity;
  ThreeVector             m_primary_position;
  ThreeVector             m_primary_momentum;
  double                  m_path_length_tof;
  double                  m_path_length_total;
  ThreeVector             m_tof_pos;
  ThreeVector             m_tof_mom;
  RKCordParameter         m_cord_param;
  bool                    m_gfastatus;

public:
  DCLocalTrack*      GetLocalTrackIn( void ) { return m_track_in;}
  DCLocalTrack*      GetLocalTrackOut( void ) { return m_track_out; }
  bool               DoFit( void );
  bool               DoFit( RKCordParameter iniCord );
  bool               DoFitMinuit( void );
  bool               Status( void ) const { return m_status; }
  int                Niteration( void ) const { return m_n_iteration; }
  void               SetInitialMomentum( double initial_momentum )
  { m_initial_momentum = initial_momentum; }
  const ThreeVector& PrimaryPosition( void ) const { return m_primary_position; }
  const ThreeVector& PrimaryMomentum( void ) const { return m_primary_momentum; }
  double             PrimaryMomMag( void )   const { return m_primary_momentum.Mag();}
  double             PathLengthToTOF( void ) const { return m_path_length_tof; }
  double             PathLengthTotal( void ) const { return m_path_length_total; }
  double             TofSeg( void ) const { return m_tof_seg; }
  const ThreeVector& TofPos( void ) const { return m_tof_pos; }
  const ThreeVector& TofMom( void ) const { return m_tof_mom; }
  double             chisqr( void )          const { return m_chisqr; }
  double             Polarity( void )        const { return m_polarity; }
  std::size_t        GetNHits( void )        const { return m_hit_array.size(); }
  TrackHit*          GetHit( std::size_t nth ) const;
  TrackHit*          GetHitOfLayerNumber( int lnum ) const;
  bool               GoodForAnalysis( void ) const { return m_gfastatus; }
  bool               GoodForAnalysis( bool status )
  { bool ret=m_gfastatus; m_gfastatus=status; return ret; }
  double             GetInitialMomentum( void ) const { return m_initial_momentum; }
  bool               GetTrajectoryLocalPosition( int layer, double & x, double & y ) const;
  void               Print( const std::string& arg="", std::ostream& ost=hddaq::cout );
  bool               ReCalc( bool applyRecursively=false );

private:
  void   FillHitArray( void );
  void   ClearHitArray( void );
  double CalcChiSqr( const RKHitPointContainer &hpCont ) const;
  bool   GuessNextParameters( const RKHitPointContainer &hpCont,
			      RKCordParameter &Cord,
			      double &estDeltaChisqr,
			      double &lambdaCri, double dmp=0. ) const;
  bool   SaveCalcPosition( const RKHitPointContainer &hpCont );
  void   PrintCalcHits( const RKHitPointContainer &hpCont,
			std::ostream &ost = std::cout ) const;
  bool   SaveTrackParameters( const RKCordParameter &cp );

};

//______________________________________________________________________________
struct KuramaTrackComp
  : public std::binary_function<KuramaTrack*, KuramaTrack*, bool>
{
  bool operator()( const KuramaTrack * const p1,
		   const KuramaTrack * const p2 ) const
  {
    int n1=p1->GetNHits(), n2=p2->GetNHits();
    if( n1>n2+1 ) return true;
    if( n2>n1+1 ) return false;
    return (p1->chisqr())<(p2->chisqr());
  }
};

#endif
