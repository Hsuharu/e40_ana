/**
 *  file: DCLocalTrack.hh
 *  date: 2017.04.10
 *
 */

#ifndef DC_LOCAL_TRACK_HH
#define DC_LOCAL_TRACK_HH

#include <vector>
#include <functional>

#include <std_ostream.hh>

#include "ThreeVector.hh"
#include "DCLTrackHit.hh"

class DCLTrackHit;
class DCAnalyzer;

//______________________________________________________________________________
class DCLocalTrack
{
public:
  explicit DCLocalTrack( void );
  ~DCLocalTrack( void );

private:
  DCLocalTrack( const DCLocalTrack & );
  DCLocalTrack & operator =( const DCLocalTrack & );

private:
  bool   m_is_fitted;     // flag of DoFit()
  bool   m_is_calculated; // flag of Calculate()
  std::vector<DCLTrackHit*> m_hit_array;
  double m_Ax;
  double m_Ay;
  double m_Au;
  double m_Av;
  double m_Chix;
  double m_Chiy;
  double m_Chiu;
  double m_Chiv;

  double m_x0;
  double m_y0;
  double m_u0;
  double m_v0;
  double m_a;
  double m_b;
  double m_chisqr;
  bool   m_good_for_tracking;
  // for SSD
  double m_de;
  // for Honeycomb
  double m_chisqr1st; // 1st iteration for honeycomb
  double m_n_iteration;

public:
  void         AddHit( DCLTrackHit *hitp );
  void         Calculate( void );
  void         DeleteNullHit( void );
  bool         DoFit( void );
  bool         DoFitBcSdc( void );
  bool         FindLayer( int layer ) const;
  int          GetNDF( void ) const;
  int          GetNHit( void ) const { return m_hit_array.size(); }
  int          GetNHitSFT( void ) const;
  int          GetNHitY( void ) const;
  DCLTrackHit* GetHit( std::size_t nth ) const;
  DCLTrackHit* GetHitOfLayerNumber( int lnum ) const;
  double       GetWire( int layer ) const;
  bool         HasHoneycomb( void ) const;
  bool         IsFitted( void ) const { return m_is_fitted; }
  bool         IsCalculated( void ) const { return m_is_calculated; }

  void SetAx( double Ax ) { m_Ax = Ax; }
  void SetAy( double Ay ) { m_Ay = Ay; }
  void SetAu( double Au ) { m_Au = Au; }
  void SetAv( double Av ) { m_Av = Av; }
  void SetChix( double Chix ) { m_Chix = Chix; }
  void SetChiy( double Chiy ) { m_Chiy = Chiy; }
  void SetChiu( double Chiu ) { m_Chiu = Chiu; }
  void SetChiv( double Chiv ) { m_Chiv = Chiv; }
  void SetDe( double de ) { m_de = de; }

  double GetX0( void ) const { return m_x0; }
  double GetY0( void ) const { return m_y0; }
  double GetU0( void ) const { return m_u0; }
  double GetV0( void ) const { return m_v0; }

  //For XUV Tracking
  bool DoFitVXU( void );

  double GetVXU_A( void ) const { return m_a; }
  double GetVXU_B( void ) const { return m_b; }
  double GetVXU( double z ) const { return m_a*z+m_b; }
  double GetAx( void ) const { return m_Ax; }
  double GetAy( void ) const { return m_Ay; }
  double GetAu( void ) const { return m_Au; }
  double GetAv( void ) const { return m_Av; }

  double GetDifVXU( void ) const ;
  double GetDifVXUSDC34( void ) const;
  double GetChiSquare( void ) const { return m_chisqr; }
  double GetChiSquare1st( void ) const { return m_chisqr1st; }
  double GetChiX( void ) const { return m_Chix; }
  double GetChiY( void ) const { return m_Chiy; }
  double GetChiU( void ) const { return m_Chiu; }
  double GetChiV( void ) const { return m_Chiv; }
  double GetX( double z ) const { return m_x0+m_u0*z; }
  double GetY( double z ) const { return m_y0+m_v0*z; }
  double GetS( double z, double tilt ) const { return GetX(z)*std::cos(tilt)+GetY(z)*std::sin(tilt); }
  int    GetNIteration( void ) const { return m_n_iteration; }
  double GetTheta( void ) const;
  bool   GoodForTracking( void ) const { return m_good_for_tracking; }
  bool   GoodForTracking( bool status )
  { bool ret = m_good_for_tracking; m_good_for_tracking = status; return ret; }
  bool   ReCalc( bool ApplyRecursively=false );
  double GetDe( void ) const { return m_de; }
  void   Print( const std::string& arg="", std::ostream& ost=hddaq::cout ) const;
  void   PrintVXU( const std::string& arg="" ) const;
};


//______________________________________________________________________________
inline
std::ostream&
operator <<( std::ostream& ost,
	     const DCLocalTrack& track )
{
  track.Print( "", ost );
  return ost;
}

//______________________________________________________________________________
struct DCLTrackComp
  : public std::binary_function <DCLocalTrack *, DCLocalTrack *, bool>
{
  bool operator()( const DCLocalTrack * const p1,
		   const DCLocalTrack * const p2 ) const
  {
    int n1=p1->GetNHit(), n2=p2->GetNHit();
    double chi1=p1->GetChiSquare(), chi2=p2->GetChiSquare();
    if( n1>n2+1 )
      return true;
    if( n2>n1+1 )
      return false;
    if( n1<=4 || n2<=4 )
      return ( n1 >= n2 );
    if( n1==n2 )
      return ( chi1 <= chi2 );

    return ( chi1-chi2 <= 3./(n1-4) );// 3-sigma
  }
};

//______________________________________________________________________________
struct DCLTrackComp1
  : public std::binary_function <DCLocalTrack *, DCLocalTrack *, bool>
{
  bool operator()( const DCLocalTrack * const p1,
		   const DCLocalTrack * const p2 ) const
  {
    int n1=p1->GetNHit(), n2=p2->GetNHit();
    double chi1=p1->GetChiSquare(),chi2=p2->GetChiSquare();
    if(n1>n2) return true;
    if(n2>n1) return false;
    return ( chi1<=chi2 );
  }

};

//______________________________________________________________________________
struct DCLTrackComp2
  : public std::binary_function <DCLocalTrack *, DCLocalTrack *, bool>
{
  bool operator()( const DCLocalTrack * const p1,
		   const DCLocalTrack * const p2 ) const
  {
    int n1=p1->GetNHit(), n2=p2->GetNHit();
    double chi1=p1->GetChiSquare(),chi2=p2->GetChiSquare();
    if(n1<n2) return true;
    if(n2<n1) return false;
    return ( chi1<=chi2 );
  }

};

//______________________________________________________________________________
struct DCLTrackComp3
  : public std::binary_function <DCLocalTrack *, DCLocalTrack *, bool>
{
  bool operator()( const DCLocalTrack * const p1,
		   const DCLocalTrack * const p2 ) const
  {
    int n1=p1->GetNHit(), n2=p2->GetNHit();
    double chi1=p1->GetChiSquare(),chi2=p2->GetChiSquare();
    double a1= std::abs(1.-chi1), a2=std::abs(1.-chi2);
    if(a1<a2) return true;
    if(a2<a1) return false;
    return (n1<=n2);
  }

};

//______________________________________________________________________________
struct DCLTrackComp4
  : public std::binary_function <DCLocalTrack *, DCLocalTrack *, bool>
{
  bool operator()( const DCLocalTrack * const p1,
		   const DCLocalTrack * const p2 ) const
  {
    int n1=p1->GetNHit(), n2=p2->GetNHit();
    double chi1=p1->GetChiSquare(),chi2=p2->GetChiSquare();
    if( (n1>n2+1) && (std::abs(chi1-chi2)<2.) )
      return true;
    if( (n2>n1+1) && ( std::abs(chi1-chi2)<2.) )
      return false;

    return (chi1<=chi2);
  }
};

//______________________________________________________________________________
struct DCLTrackCompSdcInFiber
  : public std::binary_function <DCLocalTrack *, DCLocalTrack *, bool>
{
  bool operator()( const DCLocalTrack * const p1,
		   const DCLocalTrack * const p2 ) const
  {
    int n1=p1->GetNHit(), n2=p2->GetNHit();
    double chi1=p1->GetChiSquare(),chi2=p2->GetChiSquare();
    int NofFiberHit1 = 0;
    int NofFiberHit2 = 0;
    for(int ii=0;ii<n1;ii++){
      int layer = p1->GetHit(ii)->GetLayer();
      if( layer > 6 ) NofFiberHit1++;
    }
    for(int ii=0;ii<n2;ii++){
      int layer = p2->GetHit(ii)->GetLayer();
      if( layer > 6 ) NofFiberHit2++;
    }

    if( (n1>n2+1) ){
      return true;
    }
    else if( (n2>n1+1)  ){
      return false;
    }
    else if( NofFiberHit1 > NofFiberHit2 ){
      return true;
    }
    else if( NofFiberHit2 > NofFiberHit1 ){
      return false;
    }
    else{
      return (chi1<=chi2);
    }

  }
};

//______________________________________________________________________________
struct DCLTrackCompSdcOut
  : public std::binary_function <DCLocalTrack *, DCLocalTrack *, bool>
{
  bool operator()( const DCLocalTrack * const p1,
		   const DCLocalTrack * const p2 ) const
  {
    int n1=p1->GetNHit(), n2=p2->GetNHit();
    double chi1=p1->GetChiSquare(), chi2=p2->GetChiSquare();
    if( n1 > n2 ) return true;
    if( n2 > n1 ) return false;
    return ( chi1 <= chi2 );
  }
};

#endif
