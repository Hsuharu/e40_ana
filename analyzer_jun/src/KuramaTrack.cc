/**
 *  file: KuramaTrack.cc
 *  date: 2017.04.10
 *
 */

#include "KuramaTrack.hh"

#include <cstring>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <TMinuit.h>

#include <std_ostream.hh>

#include "DCAnalyzer.hh"
#include "DCGeomMan.hh"
#include "DCLocalTrack.hh"
#include "MathTools.hh"
#include "PrintHelper.hh"
#include "TrackHit.hh"

namespace
{
  const std::string& class_name("KuramaTrack");
  const DCGeomMan& gGeom = DCGeomMan::GetInstance();
  // const int& IdTOF   = gGeom.DetectorId("TOF");
  const int& IdTOFUX = gGeom.DetectorId("TOF-UX");
  const int& IdTOFDX = gGeom.DetectorId("TOF-DX");
  const int    MaxIteraction = 100;
  const double InitialChiSqr = 1.e+10;
  const double MaxChiSqr     = 1.e+2;
  const double MinDeltaChiSqrR = 0.0002;
}

#define WARNOUT 0

//______________________________________________________________________________
KuramaTrack::KuramaTrack( DCLocalTrack *track_in, DCLocalTrack *track_out )
  : m_status( kInit ),
    m_track_in( track_in ),
    m_track_out( track_out ),
    m_tof_seg( -1 ),
    m_initial_momentum( 0. ),
    m_n_iteration( -1 ),
    m_nef_iteration( -1 ),
    m_chisqr( InitialChiSqr ),
    m_polarity( 0. ),
    m_path_length_tof( 0. ),
    m_path_length_total( 0. ),
    m_tof_pos( ThreeVector( 0., 0., 0. ) ),
    m_tof_mom( ThreeVector( 0., 0., 0. ) ),
    m_gfastatus( true )
{
  s_status[kInit]                = "Initialized";
  s_status[kPassed]              = "Passed";
  s_status[kExceedMaxPathLength] = "Exceed Max Path Length";
  s_status[kExceedMaxStep]       = "Exceed Max Step";
  s_status[kFailedTraceLast]     = "Failed to Trace Last";
  s_status[kFailedGuess]         = "Failed to Guess";
  s_status[kFailedSave]          = "Failed to Save";
  s_status[kFatal]               = "Fatal";
  FillHitArray();
  debug::ObjectCounter::increase(class_name);
}

//______________________________________________________________________________
KuramaTrack::~KuramaTrack( void )
{
  ClearHitArray();
  debug::ObjectCounter::decrease(class_name);
}

//______________________________________________________________________________
TrackHit*
KuramaTrack::GetHit( std::size_t nth ) const
{
  static const std::string func_name("["+class_name+"::"+__func__+"()]");
  if( nth<m_hit_array.size() )
    return m_hit_array[nth];
  else
    return 0;
}

//______________________________________________________________________________
TrackHit*
KuramaTrack::GetHitOfLayerNumber( int lnum ) const
{
  static const std::string func_name("["+class_name+"::"+__func__+"()]");
  std::size_t nh = m_hit_array.size();
  for( std::size_t i=0; i<nh; ++i ){
    if( m_hit_array[i]->GetLayer()==lnum )
      return m_hit_array[i];
  }
  return 0;
}

//______________________________________________________________________________
void
KuramaTrack::FillHitArray( void )
{
  static const std::string func_name("["+class_name+"::"+__func__+"()]");

  std::size_t nIn  = m_track_in->GetNHit();
  std::size_t nOut = m_track_out->GetNHit();
  ClearHitArray();
  m_hit_array.reserve( nIn+nOut );

  for( std::size_t i=0; i<nIn; ++i ){
    DCLTrackHit *hit  = m_track_in->GetHit( i );
    TrackHit    *thit = new TrackHit( hit );
    m_hit_array.push_back( thit );
  }

  for( std::size_t i=0; i<nOut; ++i ){
    DCLTrackHit *hit  = m_track_out->GetHit( i );
    TrackHit    *thit = new TrackHit( hit );
    m_hit_array.push_back( thit );
    if( hit->GetLayer() == IdTOFUX ||
	hit->GetLayer() == IdTOFDX ){
      m_tof_seg = hit->GetWire();
    }
  }

}

//______________________________________________________________________________
void
KuramaTrack::ClearHitArray( void )
{
  static const std::string func_name("["+class_name+"::"+__func__+"()]");
  int nh = m_hit_array.size();
  for( int i=nh-1; i>=0; --i ){
    delete m_hit_array[i];
  }
  m_hit_array.clear();
}

//______________________________________________________________________________
bool
KuramaTrack::ReCalc( bool applyRecursively )
{
  static const std::string func_name("["+class_name+"::"+__func__+"()]");

  if( applyRecursively ){
    m_track_in->ReCalc(applyRecursively);
    m_track_out->ReCalc(applyRecursively);
    //    int nh=m_hit_array.size();
    //    for( int i=0; i<nh; ++i ){
    //      m_hit_array[i]->ReCalc(applyRecursively);
    //    }
  }

  return DoFit( m_cord_param );
  //  return DoFit();
}

//______________________________________________________________________________
bool
KuramaTrack::DoFit( void )
{
  static const std::string func_name("["+class_name+"::"+__func__+"()]");

  m_status = kInit;

  if( m_initial_momentum<0 ){
    hddaq::cout << "#E " << func_name << " initial momentum must be positive"
  		<< m_initial_momentum << std::endl;
    m_status = kFatal;
    return false;
  }

  static const ThreeVector gTof = gGeom.GetGlobalPosition( "TOF" );
  const double       xOut   = m_track_out->GetX( gTof.z() );
  const double       yOut   = m_track_out->GetY( gTof.z() );
  const ThreeVector& posOut = ThreeVector( xOut, yOut, gTof.z() );
  const double       uOut   = m_track_out->GetU0();
  const double       vOut   = m_track_out->GetV0();
  const double       pzOut  = m_initial_momentum/std::sqrt( 1.+uOut*uOut+vOut*vOut );
  const ThreeVector& momOut = ThreeVector( pzOut*uOut, pzOut*vOut, pzOut );

  RKCordParameter     iniCord( posOut, momOut );
  RKCordParameter     prevCord;
  RKHitPointContainer preHPntCont;

  double chiSqr     = InitialChiSqr;
  double prevChiSqr = InitialChiSqr;
  double estDChisqr = InitialChiSqr;
  double lambdaCri  = 0.01;
  double dmp = 0.;

  m_HitPointCont = RK::MakeHPContainer();
  RKHitPointContainer prevHPntCont;

  int iItr = 0, iItrEf = 1;

  while( ++iItr<MaxIteraction ){
    m_status = (RKstatus)RK::Trace( iniCord, m_HitPointCont );
    if( m_status != kPassed ){
#ifdef WARNOUT
      // hddaq::cerr << "#E " << func_name << " "
      // 		<< "something is wrong : " << iItr << std::endl;
#endif
      break;
    }

    chiSqr = CalcChiSqr( m_HitPointCont );
    double dChiSqr  = chiSqr - prevChiSqr;
    double dChiSqrR = dChiSqr/prevChiSqr;
    double Rchisqr  = dChiSqr/estDChisqr;
#if 0
    {
      PrintHelper helper( 3, std::ios::scientific );
      hddaq::cout << func_name << ": #"
		  << std::setw(3) << iItr << " ( "
		  << std::setw(2) << iItrEf << " )"
		  << " chi=" << std::setw(10) << chiSqr;
      hddaq::cout.precision(5);
      hddaq::cout << " (" << std::fixed << std::setw(10) << dChiSqrR << " )"
		  << " [" << std::fixed << std::setw(10) << Rchisqr << " ]";
      helper.precision(2);
      hddaq::cout << " df=" << std::setw(8) << dmp
		  << " (" << std::setw(8) << lambdaCri << ")" << std::endl;
      hddaq::cout << "iniCord x:" << iniCord.X()
		  << " y:" << iniCord.Y() << " z:" << iniCord.Z()
		  << " u:" << iniCord.U() << " v:" << iniCord.V()
		  << " p:" << 1./iniCord.Q() << std::endl;
    }
#endif

#if 0
    PrintCalcHits( m_HitPointCont );
#endif

    if( std::abs( dChiSqrR )<MinDeltaChiSqrR &&
	( chiSqr<MaxChiSqr || Rchisqr>1. ) ){
      // Converged
      m_status = kPassed;
      if( dChiSqr>0. ){
	iniCord        = prevCord;
	chiSqr         = prevChiSqr;
	m_HitPointCont = prevHPntCont;
      }
      break;
    }

    // Next Guess
    if( iItr==1 ){
      prevCord     = iniCord;
      prevChiSqr   = chiSqr;
      prevHPntCont = m_HitPointCont;
      ++iItrEf;
    }
    else if( dChiSqr <= 0.0 ){
      prevCord     = iniCord;
      prevChiSqr   = chiSqr;
      prevHPntCont = m_HitPointCont;
      ++iItrEf;
      if( Rchisqr>=0.75 ){
	dmp*=0.5;
	if( dmp < lambdaCri ) dmp=0.;
      }
      else if( Rchisqr>0.25 ){
	// nothing
      }
      else{
	if( dmp==0. ) dmp=lambdaCri;
	else dmp*=2.;
      }
    }
    else {
      if( dmp==0. ) dmp = lambdaCri;
      else {
	double uf=2.;
	if( 2.-Rchisqr > 2. ) uf=2.-Rchisqr;
	dmp *= uf;
      }
      iniCord        = prevCord;
      m_HitPointCont = prevHPntCont;
    }

    if( !GuessNextParameters( m_HitPointCont, iniCord,
			      estDChisqr, lambdaCri, dmp ) ){
      hddaq::cerr << "#W " << func_name << " "
		  << "cannot guess next paramters" << std::endl;
      m_status = kFailedGuess;
      return false;
    }

  }  /* End of Iteration */

  m_n_iteration   = iItr;
  m_nef_iteration = iItrEf;
  m_chisqr = chiSqr;

  if( !RK::TraceToLast( m_HitPointCont ) )
    m_status = kFailedTraceLast;

  if( !SaveCalcPosition( m_HitPointCont ) ||
      !SaveTrackParameters( iniCord )     )
    m_status = kFailedSave;

#if 0
  Print( "in "+func_name );
#endif

  if( m_status != kPassed )
    return false;

  return true;
}

//______________________________________________________________________________
bool
KuramaTrack::DoFit( RKCordParameter iniCord )
{
  static const std::string func_name("["+class_name+"::"+__func__+"()]");

  //  ClearHitArray();
  //  FillHitArray();

  RKCordParameter prevCord;
  RKHitPointContainer preHPntCont;

  double chiSqr     = InitialChiSqr;
  double prevChiSqr = InitialChiSqr;
  double estDChisqr = InitialChiSqr;
  double lambdaCri  = 0.01;
  double dmp = 0.;
  m_status = kInit;

  m_HitPointCont = RK::MakeHPContainer();
  RKHitPointContainer prevHPntCont;

  int iItr=0, iItrEf=1;

  while( ++iItr < MaxIteraction ){
    if( !RK::Trace( iniCord, m_HitPointCont ) ){
      // Error
#ifdef WARNOUT
      //hddaq::cerr << func_name << ": Error in RK::Trace. " << std::endl;
#endif
      break;
    }

    chiSqr = CalcChiSqr( m_HitPointCont );
    double dChiSqr  = chiSqr-prevChiSqr;
    double dChiSqrR = dChiSqr/prevChiSqr;
    double Rchisqr  = dChiSqr/estDChisqr;
#if 0
    {
      PrintHelper helper( 3, std::ios::scientific );
      hddaq::cout << func_name << ": #"
		  << std::setw(3) << iItr << " ( "
		  << std::setw(2) << iItrEf << " )"
		  << " chi=" << std::setw(10) << chiSqr;
      helper.precision(5);
      hddaq::cout << " (" << std::fixed << std::setw(10) << dChiSqrR << " )"
		  << " [" << std::fixed << std::setw(10) << Rchisqr << " ]";
      helper.precision(2);
      hddaq::cout << " df=" << std::setw(8) << dmp
		  << " (" << std::setw(8) << lambdaCri << ")" << std::endl;
    }
#endif

#if 0
    PrintCalcHits( m_HitPointCont );
#endif

    if( std::abs( dChiSqrR )<MinDeltaChiSqrR &&
	( chiSqr<MaxChiSqr || Rchisqr>1. ) ){
      // Converged
      m_status = kPassed;
      if( dChiSqr>0. ){
	iniCord        = prevCord;
	chiSqr         = prevChiSqr;
	m_HitPointCont = prevHPntCont;
      }
      break;
    }

    // Next Guess
    if( iItr==1 ){
      prevCord     = iniCord;
      prevChiSqr   = chiSqr;
      prevHPntCont = m_HitPointCont;
      ++iItrEf;
    }
    else if( dChiSqr <= 0.0 ){
      prevCord     = iniCord;
      prevChiSqr   = chiSqr;
      prevHPntCont = m_HitPointCont;
      ++iItrEf;
      if( Rchisqr>=0.75 ){
	dmp*=0.5;
	if( dmp < lambdaCri ) dmp=0.;
      }
      else if( Rchisqr>0.25 ){
	// nothing
      }
      else{
	if( dmp==0.0 ) dmp=lambdaCri;
	else dmp*=2.;
      }
    }
    else {
      if( dmp==0.0 ) dmp=lambdaCri;
      else {
	double uf=2.;
	if( 2.-Rchisqr > 2. ) uf=2.-Rchisqr;
	dmp *= uf;
      }
      iniCord = prevCord;
      m_HitPointCont = prevHPntCont;
    }
    if( !GuessNextParameters( m_HitPointCont, iniCord,
			      estDChisqr, lambdaCri, dmp ) ){
      m_status = kFailedGuess;
      return false;
    }
  }  /* End of Iteration */

  m_n_iteration   = iItr;
  m_nef_iteration = iItrEf;
  m_chisqr        = chiSqr;

  if( !RK::TraceToLast( m_HitPointCont ) )
    m_status = kFailedTraceLast;

  if( !SaveCalcPosition( m_HitPointCont ) ||
      !SaveTrackParameters( iniCord ) )
    m_status = kFailedSave;

#if 0
  Print( "in "+func_name );
#endif

  if( m_status != kPassed )
    return false;

  return true;
}

//______________________________________________________________________________
double
KuramaTrack::CalcChiSqr( const RKHitPointContainer &hpCont ) const
{
  std::size_t nh = m_hit_array.size();

  double chisqr=0.0;
  int n=0;

  for( std::size_t i=0; i<nh; ++i ){
    TrackHit *thp = m_hit_array[i];
    if(!thp) continue;
    int    lnum = thp->GetLayer();
    const RKcalcHitPoint& calhp = hpCont.HitPointOfLayer( lnum );
    const ThreeVector& mom = calhp.MomentumInGlobal();
    double w = gGeom.GetResolution(lnum);
    w = 1./(w*w);
    double hitpos = thp->GetLocalHitPos();
    double calpos = calhp.PositionInLocal();
    double a = thp->GetTiltAngle()*math::Deg2Rad();
    double u = mom.x()/mom.z();
    double v = mom.y()/mom.z();
    double dsdz = u*std::cos(a)+v*std::sin(a);
    double coss = thp->IsHoneycomb() ? std::cos( std::atan(dsdz) ) : 1.;
    double wp   = thp->GetWirePosition();
    double ss   = wp+(hitpos-wp)/coss;
    double res  = (ss-calpos)*coss;
    chisqr += w*res*res;
    ++n;
  }
  chisqr /= double(n-5);
  return chisqr;
}

//______________________________________________________________________________
bool
KuramaTrack::GuessNextParameters( const RKHitPointContainer& hpCont,
				  RKCordParameter& Cord, double& estDeltaChisqr,
				  double& lambdaCri, double dmp ) const
{
  static const std::string func_name("["+class_name+"::"+__func__+"()]");

  double *a2[10], a2c[10*5], *v[5],  vc[5*5];
  double *a3[5],  a3c[5*5],  *v3[5], v3c[5*5], w3[5];
  double dm[5];

  for( int i=0; i<10; ++i ){
    a2[i] =& a2c[5*i];
  }
  for( int i=0; i<5; ++i ){
    v[i]=&vc[5*i]; a3[i]=&a3c[5*i]; v3[i]=&v3c[5*i];
  }

  double cb2[10], wSvd[5], dcb[5];
  double wv[5];   // working space for SVD functions

  std::size_t nh = m_hit_array.size();

  for( int i=0; i<10; ++i ){
    cb2[i]=0.0;
    for( int j=0; j<5; ++j ) a2[i][j]=0.0;
  }

  int nth=0;
  for( std::size_t i=0; i<nh; ++i ){
    TrackHit *thp = m_hit_array[i];
    if(!thp) continue;
    int lnum = thp->GetLayer();
    const RKcalcHitPoint &calhp = hpCont.HitPointOfLayer( lnum );
    const ThreeVector&    mom   = calhp.MomentumInGlobal();
    double hitpos = thp->GetLocalHitPos();
    double calpos = calhp.PositionInLocal();
    double a = thp->GetTiltAngle()*math::Deg2Rad();
    double u = mom.x()/mom.z();
    double v = mom.y()/mom.z();
    double dsdz = u*std::cos(a)+v*std::sin(a);
    double coss = thp->IsHoneycomb() ? std::cos( std::atan(dsdz) ) : 1.;
    double wp   = thp->GetWirePosition();
    double ss   = wp+(hitpos-wp)/coss;
    double cb   = ss-calpos;
    // double cb = thp->GetLocalHitPos()-calhp.PositionInLocal();
    // double cb = thp->GetResidual();
    double wt = gGeom.GetResolution( lnum );
    wt = 1./(wt*wt);

    double cfx=calhp.coefX(), cfy=calhp.coefY();
    double cfu=calhp.coefU(), cfv=calhp.coefV(), cfq=calhp.coefQ();
    ++nth;

    cb2[0] += 2.*cfx*wt*cb;  cb2[1] += 2.*cfy*wt*cb;  cb2[2] += 2.*cfu*wt*cb;
    cb2[3] += 2.*cfv*wt*cb;  cb2[4] += 2.*cfq*wt*cb;

    a2[0][0] += 2.*wt*(cfx*cfx - cb*calhp.coefXX());
    a2[0][1] += 2.*wt*(cfx*cfy - cb*calhp.coefXY());
    a2[0][2] += 2.*wt*(cfx*cfu - cb*calhp.coefXU());
    a2[0][3] += 2.*wt*(cfx*cfv - cb*calhp.coefXV());
    a2[0][4] += 2.*wt*(cfx*cfq - cb*calhp.coefXQ());

    a2[1][0] += 2.*wt*(cfy*cfx - cb*calhp.coefYX());
    a2[1][1] += 2.*wt*(cfy*cfy - cb*calhp.coefYY());
    a2[1][2] += 2.*wt*(cfy*cfu - cb*calhp.coefYU());
    a2[1][3] += 2.*wt*(cfy*cfv - cb*calhp.coefYV());
    a2[1][4] += 2.*wt*(cfy*cfq - cb*calhp.coefYQ());

    a2[2][0] += 2.*wt*(cfu*cfx - cb*calhp.coefUX());
    a2[2][1] += 2.*wt*(cfu*cfy - cb*calhp.coefUY());
    a2[2][2] += 2.*wt*(cfu*cfu - cb*calhp.coefUU());
    a2[2][3] += 2.*wt*(cfu*cfv - cb*calhp.coefUV());
    a2[2][4] += 2.*wt*(cfu*cfq - cb*calhp.coefUQ());

    a2[3][0] += 2.*wt*(cfv*cfx - cb*calhp.coefVX());
    a2[3][1] += 2.*wt*(cfv*cfy - cb*calhp.coefVY());
    a2[3][2] += 2.*wt*(cfv*cfu - cb*calhp.coefVU());
    a2[3][3] += 2.*wt*(cfv*cfv - cb*calhp.coefVV());
    a2[3][4] += 2.*wt*(cfv*cfq - cb*calhp.coefVQ());

    a2[4][0] += 2.*wt*(cfq*cfx - cb*calhp.coefQX());
    a2[4][1] += 2.*wt*(cfq*cfy - cb*calhp.coefQY());
    a2[4][2] += 2.*wt*(cfq*cfu - cb*calhp.coefQU());
    a2[4][3] += 2.*wt*(cfq*cfv - cb*calhp.coefQV());
    a2[4][4] += 2.*wt*(cfq*cfq - cb*calhp.coefQQ());
  }

  for( int i=0; i<5; ++i )
    for( int j=0; j<5; ++j )
      a3[i][j]=a2[i][j];

  // Levenberg-Marqardt method
  double lambda = std::sqrt( dmp );
  //  a2[5][0]=a2[6][1]=a2[7][2]=a2[8][3]=a2[9][4]=lambda;

  for( int ii=0; ii<5; ++ii ){
    dm[ii]       = a2[ii][ii];
    a2[ii+5][ii] = lambda * std::sqrt( a2[ii][ii] );
  }

#if 0
  {
    PrintHelper helper( 3, std::ios::scientific );
    hddaq::cout << func_name << ": A2 and CB2 before SVDcmp"
		<<  std::endl;
    for( int ii=0; ii<10; ++ii )
      hddaq::cout << std::setw(12) << a2[ii][0] << ","
		  << std::setw(12) << a2[ii][1] << ","
		  << std::setw(12) << a2[ii][2] << ","
		  << std::setw(12) << a2[ii][3] << ","
		  << std::setw(12) << a2[ii][4] << "  "
		  << std::setw(12) << cb2[ii] << std::endl;
  }
#endif

  // Solve the Eq. with SVD (Singular Value Decomposition) Method
  if( !math::SVDcmp( a2, 10, 5, wSvd, v, wv ) )
    return false;

#if 0
  {
    PrintHelper helper( 3, std::ios::scientific );
    hddaq::cout << func_name << ": A2 after SVDcmp"
		<<  std::endl;
    for( int ii=0; ii<10; ++ii )
      hddaq::cout << std::setw(12) << a2[ii][0] << ","
		  << std::setw(12) << a2[ii][1] << ","
		  << std::setw(12) << a2[ii][2] << ","
		  << std::setw(12) << a2[ii][3] << ","
		  << std::setw(12) << a2[ii][4] << std::endl;
  }
#endif

#if 0
  // check orthogonality of decomposted matrics
  {
    PrintHelper helper( 5, std::ios::scientific );
    hddaq::cout << func_name << ": Check V*~V" <<  std::endl;
    for( int i=0; i<5; ++i ){
      for( int j=0; j<5; ++j ){
	double f=0.0;
	for( int k=0; k<5; ++k )
	  f += v[i][k]*v[j][k];
	hddaq::cout << std::setw(10) << f;
      }
      hddaq::cout << std::endl;
    }
    hddaq::cout << func_name << ": Check U*~U" <<  std::endl;
    for( int i=0; i<10; ++i ){
      for( int j=0; j<10; ++j ){
	double f=0.0;
	for( int k=0; k<5; ++k )
	  f += a2[i][k]*a2[j][k];
	hddaq::cout << std::setw(10) << f;
      }
      hddaq::cout << std::endl;
    }

    hddaq::cout << func_name << ": Check ~U*U" <<  std::endl;
    for( int i=0; i<5; ++i ){
      for( int j=0; j<5; ++j ){
	double f=0.0;
	for( int k=0; k<10; ++k )
	  f += a2[k][i]*a2[k][j];
	hddaq::cout << std::setw(10) << f;
      }
      hddaq::cout << std::endl;
    }
  }
#endif

  double wmax=0.0;
  for( int i=0; i<5; ++i )
    if( wSvd[i]>wmax ) wmax=wSvd[i];

  double wmin=wmax*1.E-15;
  for( int i=0; i<5; ++i )
    if( wSvd[i]<wmin ) wSvd[i]=0.0;

#if 0
  {
    PrintHelper helper( 3, std::ios::scientific );
    hddaq::cout << func_name << ": V and Wsvd after SVDcmp"
		<<  std::endl;
    for( int ii=0; ii<5; ++ii )
      hddaq::cout << std::setw(12) << v[ii][0] << ","
		  << std::setw(12) << v[ii][1] << ","
		  << std::setw(12) << v[ii][2] << ","
		  << std::setw(12) << v[ii][3] << ","
		  << std::setw(12) << v[ii][4] << "  "
		  << std::setw(12) << wSvd[ii] << std::endl;
  }
#endif

  math::SVDksb( a2, wSvd, v, 10, 5, cb2, dcb, wv );

#if 0
  {
    PrintHelper helper( 5, std::ios::scientific );
    hddaq::cout << func_name << ": "
		<< std::setw(12) << Cord.Z();
    hddaq::cout << "  Dumping Factor = " << std::setw(12) << dmp << std::endl;
    helper.setf( std::ios::fixed );
    hddaq::cout << std::setw(12) << Cord.X() << "  "
		<< std::setw(12) << dcb[0] << " ==>  "
		<< std::setw(12) << Cord.X()+dcb[0] << std::endl;
    hddaq::cout << std::setw(12) << Cord.Y() << "  "
		<< std::setw(12) << dcb[1] << " ==>  "
		<< std::setw(12) << Cord.Y()+dcb[1] << std::endl;
    hddaq::cout << std::setw(12) << Cord.U() << "  "
		<< std::setw(12) << dcb[2] << " ==>  "
		<< std::setw(12) << Cord.U()+dcb[2] << std::endl;
    hddaq::cout << std::setw(12) << Cord.V() << "  "
		<< std::setw(12) << dcb[3] << " ==>  "
		<< std::setw(12) << Cord.V()+dcb[3] << std::endl;
    hddaq::cout << std::setw(12) << Cord.Q() << "  "
		<< std::setw(12) << dcb[4] << " ==>  "
		<< std::setw(12) << Cord.Q()+dcb[4] << std::endl;
  }
#endif

  Cord = RKCordParameter( Cord.X()+dcb[0],
			  Cord.Y()+dcb[1],
			  Cord.Z(),
			  Cord.U()+dcb[2],
			  Cord.V()+dcb[3],
			  Cord.Q()+dcb[4] );

  // calc. the critical dumping factor & est. delta-ChiSqr
  double s1=0., s2=0.;
  for(  int i=0; i<5; ++i ){
    s1 += dcb[i]*dcb[i]; s2 += dcb[i]*cb2[i];
  }
  estDeltaChisqr = (-s2-dmp*s1)/double(nth-5);

  if( !math::SVDcmp( a3, 5, 5, w3, v3, wv ) )
    return false;

  double spur=0.;
  for( int i=0; i<5; ++i ){
    double s=0.;
    for( int j=0; j<5; ++j )
      s += v3[i][j]*a3[i][j];
    if( w3[i]!=0.0 )
      spur += s/w3[i]*dm[i];
  }

  lambdaCri = 1./spur;

  return true;
}

//______________________________________________________________________________
bool
KuramaTrack::SaveCalcPosition( const RKHitPointContainer &hpCont )
{
  for( std::size_t i=0, n=m_hit_array.size(); i<n; ++i ){
    TrackHit *thp = m_hit_array[i];
    if( !thp ) continue;
    int lnum = thp->GetLayer();
    const RKcalcHitPoint &calhp = hpCont.HitPointOfLayer( lnum );
    thp->SetCalGPos( calhp.PositionInGlobal() );
    thp->SetCalGMom( calhp.MomentumInGlobal() );
    thp->SetCalLPos( calhp.PositionInLocal() );
  }
  return true;
}

//______________________________________________________________________________
void
KuramaTrack::Print( const std::string& arg, std::ostream& ost )
{
  static const std::string func_name("["+class_name+"::"+__func__+"()]");

  PrintHelper helper( 5, std::ios::fixed, ost );

  ost << "#D " << func_name << " " << arg << std::endl
      << "   status : " << s_status[m_status] << std::endl
      << " in " << std::setw(3) << m_n_iteration << " ( "
      << std::setw(2) << m_nef_iteration << " ) Iteractions "
      << " chisqr=" << std::setw(10) << m_chisqr << std::endl;
  ost << " Target X ( " << std::setprecision(2)
      << std::setw(7) << m_primary_position.x() << ", "
      << std::setw(7) << m_primary_position.y() << ", "
      << std::setw(7) << m_primary_position.z() << " )" << std::endl
      << "        P " << std::setprecision(5)
      << std::setw(7) << m_primary_momentum.Mag() << " ( "
      << std::setw(7) << m_primary_momentum.x() << ", "
      << std::setw(7) << m_primary_momentum.y() << ", "
      << std::setw(7) << m_primary_momentum.z() << " )"
      << " init=" << m_initial_momentum
      << std::endl
      << "        PathLength  " << std::setprecision(1)
      << std::setw(7) << m_path_length_tof << " "
      << "TOF#" << std::setw(2) << std::right
      << (int)m_tof_seg << std::endl;
  //  << std::setw(7) << m_path_length_total << std::endl;

  PrintCalcHits( m_HitPointCont );
}

//______________________________________________________________________________
void
KuramaTrack::PrintCalcHits( const RKHitPointContainer &hpCont, std::ostream &ost ) const
{
  static const std::string func_name("["+class_name+"::"+__func__+"()]");

  PrintHelper helper( 2, std::ios::fixed, ost );

  const std::size_t n = m_hit_array.size();
  RKHitPointContainer::RKHpCIterator itr, end = hpCont.end();
  for( itr=hpCont.begin(); itr!=end; ++itr ){
    int lnum = itr->first;
    TrackHit *thp = 0;
    for( std::size_t i=0; i<n; ++i ){
      if( m_hit_array[i] && m_hit_array[i]->GetLayer()==lnum ){
	thp = m_hit_array[i];
	if( thp ) break;
      }
    }
    const RKcalcHitPoint &calhp = itr->second;
    ThreeVector pos = calhp.PositionInGlobal();
    std::string h = " ";
    if ( thp ){ h = "-"; if ( thp->IsHoneycomb() ) h = "+"; }
    ost << "#"   << std::setw(2) << lnum << h
	<< " L " << std::setw(8) << calhp.PathLength()
	<< " X " << std::setw(7) << calhp.PositionInLocal()
	<< " ( " << std::setw(7) << pos.x()
	<< ", "  << std::setw(7) << pos.y()
	<< ", "  << std::setw(8) << pos.z() << " )";
    if( thp ){
      ost << " "   << std::setw(7) << thp->GetLocalHitPos()
	  << " -> " << std::setw(7)
	  << thp->GetResidual();
    //<< thp->GetLocalHitPos()-calhp.PositionInLocal();
    }
    ost << std::endl;
#if 0
    {
      ThreeVector mom = calhp.MomentumInGlobal();
      ost << "   P=" << std::setw(7) << mom.Mag()
	  << " (" << std::setw(9) << mom.x()
	  << ", " << std::setw(9) << mom.y()
	  << ", " << std::setw(9) << mom.z()
	  << " )" << std::endl;
    }
#endif
  }
}

//______________________________________________________________________________
bool
KuramaTrack::SaveTrackParameters( const RKCordParameter &cp )
{
  static const std::string func_name("["+class_name+"::"+__func__+"()]");

  m_cord_param = cp;
  const int TGTid = m_HitPointCont.begin()->first;

  // const RKcalcHitPoint& hpTof  = m_HitPointCont.HitPointOfLayer( IdTOF );

  const RKcalcHitPoint& hpTgt  = m_HitPointCont.begin()->second;
  const RKcalcHitPoint& hpLast = m_HitPointCont.rbegin()->second;

  const ThreeVector& pos = hpTgt.PositionInGlobal();
  const ThreeVector& mom = hpTgt.MomentumInGlobal();

  m_primary_position = gGeom.Global2LocalPos( TGTid, pos );
  m_primary_momentum = gGeom.Global2LocalDir( TGTid, mom );

  m_polarity = m_primary_momentum.z()<0. ? -1. : 1.;

  const RKcalcHitPoint& hpTofU = m_HitPointCont.HitPointOfLayer( IdTOFUX );
  const RKcalcHitPoint& hpTofD = m_HitPointCont.HitPointOfLayer( IdTOFDX );

  if( (int)m_tof_seg%2==0 ){ // upstream
    m_path_length_tof = std::abs( hpTgt.PathLength()-hpTofU.PathLength() );
    m_tof_pos = hpTofU.PositionInGlobal();
    m_tof_mom = hpTofU.MomentumInGlobal();
  }
  else if( (int)m_tof_seg%2==1 ){ // downstream
    m_path_length_tof = std::abs( hpTgt.PathLength()-hpTofD.PathLength() );
    m_tof_pos = hpTofD.PositionInGlobal();
    m_tof_mom = hpTofD.MomentumInGlobal();
  }
  else {
    m_path_length_tof = std::abs( hpTgt.PathLength()-(hpTofU.PathLength()+hpTofD.PathLength())/2. );
    m_tof_pos = (hpTofU.PositionInGlobal()+hpTofD.PositionInGlobal())*0.5;
    m_tof_mom = (hpTofU.MomentumInGlobal()+hpTofD.MomentumInGlobal())*0.5;
  }

  m_path_length_total = std::abs( hpTgt.PathLength()-hpLast.PathLength() );

  return true;
}

//______________________________________________________________________________
bool
KuramaTrack::GetTrajectoryLocalPosition( int layer, double & x, double & y ) const
{
  static const std::string func_name("["+class_name+"::"+__func__+"()]");

   try {
    const RKcalcHitPoint& HP   = m_HitPointCont.HitPointOfLayer( layer );
    const ThreeVector&    gpos = HP.PositionInGlobal();
    ThreeVector lpos = gGeom.Global2LocalPos( layer,gpos );
    x = lpos.x();
    y = lpos.y();
    return true;
  }
  catch( std::out_of_range ) {
    return false;
  }
}
