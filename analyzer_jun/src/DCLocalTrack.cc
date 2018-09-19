/**
 *  file: DCLocalTrack.cc
 *  date: 2017.04.10
 *
 */

#include "DCLocalTrack.hh"

#include <string>
#include <vector>
#include <cmath>
#include <iostream>
#include <iomanip>
#include <cstring>
#include <stdexcept>
#include <sstream>

#include <std_ostream.hh>

#include "DCAnalyzer.hh"
#include "DCLTrackHit.hh"
#include "DCGeomMan.hh"
#include "DetectorID.hh"
#include "MathTools.hh"
#include "PrintHelper.hh"

namespace
{
  const std::string& class_name("DCLocalTrack");
  const DCGeomMan& gGeom = DCGeomMan::GetInstance();
  const double& zK18tgt = gGeom.LocalZ("K18Target");
  const double& zTgt    = gGeom.LocalZ("Target");

  const int ReservedNumOfHits  = 16;
  const int DCLocalMinNHits    =  4;
  const int DCLocalMinNHitsVXU =  2;// for SSD
  const int MaxIteration       = 100;// for Honeycomb
  const double MaxChisqrDiff   = 1.0e-3;
}

//______________________________________________________________________________
DCLocalTrack::DCLocalTrack( void )
  : m_is_fitted(false),
    m_is_calculated(false),
    m_Ax(0.), m_Ay(0.), m_Au(0.), m_Av(0.),
    m_Chix(0.), m_Chiy(0.), m_Chiu(0.), m_Chiv(0.),
    m_x0(0.), m_y0(0.),
    m_u0(0.), m_v0(0.),
    m_a(0.),  m_b(0.),
    m_chisqr(1.e+10),
    m_good_for_tracking(true),
    m_de(0.),
    m_chisqr1st(1.e+10),
    m_n_iteration(0)
{
  m_hit_array.reserve( ReservedNumOfHits );
  debug::ObjectCounter::increase(class_name);
}

//______________________________________________________________________________
DCLocalTrack::~DCLocalTrack( void )
{
  debug::ObjectCounter::decrease(class_name);
}

//______________________________________________________________________________
void
DCLocalTrack::AddHit( DCLTrackHit *hitp )
{
  if( hitp )
    m_hit_array.push_back( hitp );
}

//______________________________________________________________________________
void
DCLocalTrack::Calculate( void )
{
  static const std::string func_name("["+class_name+"::"+__func__+"()]");

  if( IsCalculated() ){
    hddaq::cerr << "#W " << func_name << " "
		<< "already called" << std::endl;
    return;
  }

  const std::size_t n = m_hit_array.size();
  for( std::size_t i=0; i<n; ++i ){
    DCLTrackHit *hitp = m_hit_array[i];
    double z0 = hitp->GetZ();
    hitp->SetCalPosition( GetX(z0), GetY(z0) );
    hitp->SetCalUV( m_u0, m_v0 );
    // for Honeycomb
    if( !hitp->IsHoneycomb() )
      continue;
    double scal = hitp->GetLocalCalPos();
    double wp   = hitp->GetWirePosition();
    double dl   = hitp->GetDriftLength();
    double ss   = scal-wp>0 ? wp+dl : wp-dl;
    hitp->SetLocalHitPos( ss );
  }
  m_is_calculated = true;
}

//______________________________________________________________________________
int
DCLocalTrack::GetNDF( void ) const
{
  static const std::string func_name("["+class_name+"::"+__func__+"()]");

  const std::size_t n = m_hit_array.size();
  int ndf = 0;
  for( std::size_t i=0; i<n; ++i ){
    if( m_hit_array[i] ) ++ndf;
  }
  return ndf-4;
}

//______________________________________________________________________________
int
DCLocalTrack::GetNHitSFT(void) const
{
  int n_sft=0;
  for(const auto& hit : m_hit_array){
    if(hit->GetLayer() > 6) ++n_sft;
  }

  return n_sft;
}

//______________________________________________________________________________
int
DCLocalTrack::GetNHitY(void) const
{
  int n_y=0;
  for(const auto& hit : m_hit_array){
    if(hit->GetTiltAngle() > 1) ++n_y;
  }

  return n_y;
}

//______________________________________________________________________________
DCLTrackHit*
DCLocalTrack::GetHit( std::size_t nth ) const
{
  static const std::string func_name("["+class_name+"::"+__func__+"()]");

  if( nth<m_hit_array.size() )
    return m_hit_array[nth];
  else
    return 0;
}

//______________________________________________________________________________
DCLTrackHit*
DCLocalTrack::GetHitOfLayerNumber( int lnum ) const
{
  static const std::string func_name("["+class_name+"::"+__func__+"()]");

  const std::size_t n = m_hit_array.size();
  for( std::size_t i=0; i<n; ++i ){
    if( m_hit_array[i]->GetLayer()==lnum )
      return m_hit_array[i];
  }
  return 0;
}

//______________________________________________________________________________
void
DCLocalTrack::DeleteNullHit( void )
{
  static const std::string func_name("["+class_name+"::"+__func__+"()]");

  for( std::size_t i=0; i<m_hit_array.size(); ++i ){
    DCLTrackHit *hitp = m_hit_array[i];
    if( !hitp ){
      hddaq::cout << func_name << " "
		  << "null hit is deleted" << std::endl;
      m_hit_array.erase( m_hit_array.begin()+i );
      --i;
    }
  }
}

//______________________________________________________________________________
bool
DCLocalTrack::DoFit( void )
{
  static const std::string func_name("["+class_name+"::"+__func__+"()]");

  if( IsFitted() ){
    hddaq::cerr << "#W " << func_name << " "
		<< "already called" << std::endl;
    return false;
  }

  DeleteNullHit();

  const std::size_t n = m_hit_array.size();
  if( n < DCLocalMinNHits ){
    hddaq::cout << "#D " << func_name << " "
		<< "the number of layers is too small : " << n << std::endl;
    return false;
  }

  const int nItr = HasHoneycomb() ? MaxIteration : 1;

  double prev_chisqr = m_chisqr;
  std::vector <double> z0(n), z(n), wp(n),
    w(n), s(n), ct(n), st(n), coss(n);
  std::vector<bool> honeycomb(n);
  for( int iItr=0; iItr<nItr; ++iItr ){
    for( std::size_t i=0; i<n; ++i ){
      DCLTrackHit *hitp = m_hit_array[i];
      int    lnum = hitp->GetLayer();
      honeycomb[i] = hitp->IsHoneycomb();
      wp[i] = hitp->GetWirePosition();
      z0[i] = hitp->GetZ();
      double ww = gGeom.GetResolution( lnum );
      w[i] = 1./(ww*ww);
      double aa = hitp->GetTiltAngle()*math::Deg2Rad();
      ct[i] = std::cos(aa); st[i] = std::sin(aa);
      double ss = hitp->GetLocalHitPos();
      double dl = hitp->GetDriftLength();
      double dsdz = m_u0*std::cos(aa)+m_v0*std::sin(aa);
      double dcos = std::cos( std::atan(dsdz) );
      coss[i] = dcos;
      double dsin = std::sin( std::atan(dsdz) );
      double ds = dl * dcos;
      double dz = dl * dsin;
      double scal = iItr==0 ? ss : GetS(z[i],aa);
      if( honeycomb[i] ){
	s[i] = scal-wp[i]>0 ? wp[i]+ds : wp[i]-ds;
	z[i] = scal-wp[i]>0 ? z0[i]-dz : z0[i]+dz;
      }else{
	s[i] = ss;
	z[i] = z0[i];
      }
    }

    double x0, u0, y0, v0;
    if( !math::SolveGaussJordan( z, w, s, ct, st,
				 x0, u0, y0, v0 ) ){
      hddaq::cerr << func_name << " Fitting failed" << std::endl;
      return false;
    }

    double chisqr = 0.;
    double de     = 0.;
    for( std::size_t i=0; i<n; ++i ){
      double scal = (x0+u0*z0[i])*ct[i]+(y0+v0*z0[i])*st[i];
      double ss   = wp[i]+(s[i]-wp[i])/coss[i];
      double res  = honeycomb[i] ? (ss-scal)*coss[i] : s[i]-scal;
      chisqr += w[i]*res*res;
    }
    chisqr /= GetNDF();

    if( iItr==0 ) m_chisqr1st = chisqr;

    // if worse, not update
    if( prev_chisqr-chisqr>0. ){
      m_x0 = x0;
      m_y0 = y0;
      m_u0 = u0;
      m_v0 = v0;
      m_chisqr = chisqr;
      m_de     = de;
    }

    // judge convergence
    if( prev_chisqr-chisqr<MaxChisqrDiff ){
#if 0
      // if( chisqr<200. && GetTheta()>4. )
      if( chisqr<20. )
      {
	if( iItr==0 ) hddaq::cout << "=============" << std::endl;
	hddaq::cout << func_name << " NIteration : " << iItr << " "
		    << "chisqr = " << std::setw(10) << std::setprecision(4)
		    << m_chisqr << " "
		    << "diff = " << std::setw(20) << std::left
		    << m_chisqr-m_chisqr1st << " ndf = " << GetNDF() << std::endl;
      }
#endif
      m_n_iteration = iItr;
      break;
    }

    prev_chisqr = chisqr;
  }

  m_is_fitted = true;
  return true;
}

//______________________________________________________________________________
bool
DCLocalTrack::DoFitBcSdc( void )
{
  static const std::string func_name("["+class_name+"::"+__func__+"()]");

  if( IsFitted() ){
    hddaq::cerr << "#W " << func_name << " "
		<< "already called" << std::endl;
    return false;
  }

  DeleteNullHit();

  std::size_t n = m_hit_array.size();
  if( n < DCLocalMinNHits ) return false;

  std::vector <double> z, w, s, ct, st;
  z.reserve(n); w.reserve(n); s.reserve(n);
  ct.reserve(n); st.reserve(n);

  for( std::size_t i=0; i<n; ++i ){
    DCLTrackHit *hitp = m_hit_array[i];
    int lnum = hitp->GetLayer();
    double ww = gGeom.GetResolution( lnum );
    double zz = hitp->GetZ();
    if ( lnum>=113&&lnum<=124 ){ // BcOut
      zz -= zK18tgt - zTgt;
    }
    if ( lnum>=11&&lnum<=18 ){ // SsdIn/Out
      zz -= zK18tgt - zTgt;
    }
    double aa = hitp->GetTiltAngle()*math::Deg2Rad();
    z.push_back( zz ); w.push_back( 1./(ww*ww) );
    s.push_back( hitp->GetLocalHitPos() );
    ct.push_back( cos(aa) ); st.push_back( sin(aa) );
  }

  if( !math::SolveGaussJordan( z, w, s, ct, st,
			       m_x0, m_u0, m_y0, m_v0 ) ){
    hddaq::cerr << func_name << " Fitting fails" << std::endl;
    return false;
  }

  double chisqr = 0.;
  for( std::size_t i=0; i<n; ++i ){
    double ww=w[i], zz=z[i];
    double scal=GetX(zz)*ct[i]+GetY(zz)*st[i];
    chisqr += ww*(s[i]-scal)*(s[i]-scal);
  }
  chisqr /= GetNDF();
  m_chisqr = chisqr;

  for( std::size_t i=0; i<n; ++i ){
    DCLTrackHit *hitp = m_hit_array[i];
    if( hitp ){
      int lnum = hitp->GetLayer();
      double zz = hitp->GetZ();
      if ( (lnum>=113&&lnum<=124) ){ // BcOut
        zz -= zK18tgt - zTgt;
      }
      if ( (lnum>=11&&lnum<=18) ){ // SsdIn/Out
        zz -= zK18tgt - zTgt;
      }
      hitp->SetCalPosition( GetX(zz), GetY(zz) );
    }
  }

  m_is_fitted = true;
  return true;
}

//______________________________________________________________________________
bool
DCLocalTrack::DoFitVXU( void )
{
  static const std::string func_name("["+class_name+"::"+__func__+"()]");

  if( IsFitted() ){
    hddaq::cerr << "#W " << func_name << " "
		<< "already called" << std::endl;
    return false;
  }

  DeleteNullHit();

  const std::size_t n = m_hit_array.size();
  if( n<DCLocalMinNHitsVXU ) return false;

  double w[n+1],z[n+1],x[n+1];

  for( std::size_t i=0; i<n; ++i ){
    DCLTrackHit *hitp = m_hit_array[i];
    int lnum = hitp->GetLayer();
    w[i] = gGeom.GetResolution( lnum );
    z[i] = hitp->GetZ();
    x[i] = hitp->GetLocalHitPos();
#if 0
    hddaq::cout << "" << std::endl;
    hddaq::cout << "**********" << std::endl;
    hddaq::cout << std::setw(10) << "layer = " << lnum
		<< std::setw(10) << "wire  = " << hitp->GetWire() << " "
		<< std::setw(20) << "WirePosition = "<<hitp->GetWirePosition() << " "
		<< std::setw(20) << "DriftLength = "<<hitp->GetDriftLength() << " "
		<< std::setw(20) << "hit position = "<<hitp->GetLocalHitPos()<< " "
		<< std::endl;
    hddaq::cout << "**********" << std::endl;
    hddaq::cout << "" << std::endl;
#endif
  }

  double A=0, B=0, C=0, D=0, E=0;// <-Add!!
  for( std::size_t i=0; i<n; ++i ){
    A += z[i]/(w[i]*w[i]);
    B += 1/(w[i]*w[i]);
    C += x[i]/(w[i]*w[i]);
    D += z[i]*z[i]/(w[i]*w[i]);
    E += x[i]*z[i]/(w[i]*w[i]);
  }

  m_a = (E*B-C*A)/(D*B-A*A);
  m_b = (D*C-E*A)/(D*B-A*A);

  double chisqr = 0.;
  for( std::size_t i=0; i<n; ++i ){
    chisqr += (x[i]-m_a*z[i]-m_b)*(x[i]-m_a*z[i]-m_b)/(w[i]*w[i]);
  }

  if(n==2) chisqr  = 0.;
  else     chisqr /= n-2.;
  m_chisqr = chisqr;

  for( std::size_t i=0; i<n; ++i ){
    DCLTrackHit *hitp = m_hit_array[i];
    if( hitp ){
      double zz = hitp->GetZ();
      hitp->SetLocalCalPosVXU( m_a*zz+m_b );
    }
  }

  m_is_fitted = true;
  return true;
}

//______________________________________________________________________________
bool
DCLocalTrack::FindLayer( int layer ) const
{
  const std::size_t n = m_hit_array.size();
  for( std::size_t i=0; i<n; ++i ){
    DCLTrackHit *hitp = m_hit_array[i];
    if( !hitp )
      continue;
    if( layer == hitp->GetLayer() )
      return true;
  }
  return false;
}

//______________________________________________________________________________
double
DCLocalTrack::GetWire( int layer ) const
{
  const std::size_t n = m_hit_array.size();
  for( std::size_t i=0; i<n; ++i ){
    DCLTrackHit *hitp = m_hit_array[i];
    if( !hitp )
      continue;
    if( layer == hitp->GetLayer() )
      return hitp->GetWire();
  }
  return math::nan();
}

//______________________________________________________________________________
double
DCLocalTrack::GetDifVXU( void ) const
{
  static const double Cu = cos(  15.*math::Deg2Rad() );
  static const double Cv = cos( -15.*math::Deg2Rad() );
  static const double Cx = cos(   0.*math::Deg2Rad() );

  return
    pow( m_Av/Cv - m_Ax/Cx, 2 ) +
    pow( m_Ax/Cx - m_Au/Cu, 2 ) +
    pow( m_Au/Cu - m_Av/Cv, 2 );
}

//______________________________________________________________________________
double
DCLocalTrack::GetDifVXUSDC34( void ) const
{
  static const double Cu = cos(  30.*math::Deg2Rad() );
  static const double Cv = cos( -30.*math::Deg2Rad() );
  static const double Cx = cos(   0.*math::Deg2Rad() );

  return
    pow( m_Av/Cv - m_Ax/Cx, 2 ) +
    pow( m_Ax/Cx - m_Au/Cu, 2 ) +
    pow( m_Au/Cu - m_Av/Cv, 2 );
}

//______________________________________________________________________________
double
DCLocalTrack::GetTheta( void ) const
{
  double cost = 1./std::sqrt(1.+m_u0*m_u0+m_v0*m_v0);
  return std::acos(cost)*math::Rad2Deg();
}

//______________________________________________________________________________
bool
DCLocalTrack::HasHoneycomb( void ) const
{
  for( std::size_t i=0, n = m_hit_array.size(); i<n; ++i ){
    DCLTrackHit *hitp = m_hit_array[i];
    if( !hitp ) continue;
    if( hitp->IsHoneycomb() ) return true;
  }
  return false;
}

//______________________________________________________________________________
bool
DCLocalTrack::ReCalc( bool applyRecursively )
{
  static const std::string func_name("["+class_name+"::"+__func__+"()]");

  std::size_t n = m_hit_array.size();
  for( std::size_t i=0; i<n; ++i ){
    DCLTrackHit *hitp = m_hit_array[i];
    if( hitp ) hitp->ReCalc( applyRecursively );
  }

  bool status = DoFit();
  if( !status ){
    hddaq::cerr << "#W " << func_name << " "
		<< "Recalculation fails" << std::endl;
  }

  return status;
}

//______________________________________________________________________________
void
DCLocalTrack::Print( const std::string& arg, std::ostream& ost ) const
{
  static const std::string func_name("["+class_name+"::"+__func__+"()]");

  PrintHelper helper( 3, std::ios::fixed, ost );

  const int w = 8;
  ost << func_name << " " << arg << std::endl
      << " X0 : " << std::setw(w) << std::left << m_x0
      << " Y0 : " << std::setw(w) << std::left << m_y0
      << " U0 : " << std::setw(w) << std::left << m_u0
      << " V0 : " << std::setw(w) << std::left << m_v0;
  helper.setf( std::ios::scientific );
  ost << " Chisqr : " << std::setw(w) << m_chisqr << std::endl;
  helper.setf( std::ios::fixed );
  const std::size_t n = m_hit_array.size();
  for( std::size_t i=0; i<n; ++i ){
    DCLTrackHit *hitp = m_hit_array[i];
    if( !hitp ) continue;
    int lnum = hitp->GetLayer();
    double zz = hitp->GetZ();
    double s  = hitp->GetLocalHitPos();
    double res = hitp->GetResidual();
    // double aa = hitp->GetTiltAngle()*math::Deg2Rad();
    // double scal=GetX(zz)*cos(aa)+GetY(zz)*sin(aa);
    const std::string& h = hitp->IsHoneycomb() ? "+" : "-";
    ost << "[" << std::setw(2) << i << "]"
	<< " #"  << std::setw(2) << lnum << h
	<< " S " << std::setw(w) << s
	<< " ( " << std::setw(w) << GetX(zz)
	<< ", "  << std::setw(w) << GetY(zz)
	<< ", "  << std::setw(w) << zz
	<< " )"
	<< " " << std::setw(w) << s
	<< " -> " << std::setw(w) << res << std::endl;
	// << " -> " << std::setw(w) << s-scal << std::endl;
  }
  ost << std::endl;
}

//______________________________________________________________________________
void
DCLocalTrack::PrintVXU( const std::string& arg ) const
{
  static const std::string func_name("["+class_name+"::"+__func__+"()]");

  PrintHelper helper( 3, std::ios::fixed );

  const int w = 10;
  hddaq::cout << func_name << " " << arg << std::endl
	      << "(Local X = A*z + B) "
	      << " A : " << std::setw(w) << m_a
	      << " B : " << std::setw(w) << m_b;
  helper.setf( std::ios::scientific );
  hddaq::cout << " Chisqr : " << std::setw(w) << m_chisqr << std::endl;
  helper.setf( std::ios::fixed );

  const std::size_t n = m_hit_array.size();
  for( std::size_t i=0; i<n; ++i ){
    const DCLTrackHit * const hitp = m_hit_array[i];
    if( !hitp ) continue;
    int    lnum = hitp->GetLayer();
    double zz   = hitp->GetZ();
    double s    = hitp->GetLocalHitPos();
    double res  = hitp->GetResidualVXU();
    const std::string& h = hitp->IsHoneycomb() ? "+" : "-";
    hddaq::cout << "[" << std::setw(2) << i << "] "
		<< " #"  << std::setw(2) << lnum << h
		<< " S " << std::setw(w) << s
		<< " ( " << std::setw(w) << (m_a*zz+m_b)
		<< ", "  << std::setw(w) << zz
		<< " )"
		<< " " << std::setw(w) << s
		<< " -> " << std::setw(w) << res << std::endl;
  }
  hddaq::cout << std::endl;
}
