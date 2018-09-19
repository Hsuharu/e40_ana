/**
 *  file: K18TrackD2U.cc
 *  date: 2017.04.10
 *
 */

#include "K18TrackD2U.hh"

#include <algorithm>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>

#include <std_ostream.hh>

#include "ConfMan.hh"
#include "DCAnalyzer.hh"
#include "DCGeomMan.hh"
#include "DCHit.hh"
#include "DCLocalTrack.hh"
#include "DetectorID.hh"
#include "K18Parameters.hh"
#include "K18TransMatrix.hh"
#include "Minuit.hh"
#include "TrackHit.hh"

namespace
{
  using namespace K18Parameter;
  const std::string& class_name("K18TrackD2U");
  const DCGeomMan&      gGeom   = DCGeomMan::GetInstance();
  const K18TransMatrix& gK18Mtx = K18TransMatrix::GetInstance();
  const double& zK18Target = gGeom.LocalZ("K18Target");

  const double LowBand[5] =
    { MinK18InX, MinK18InY, MinK18InU, MinK18InV, MinK18Delta };
  const double UpperBand[5] =
    { MaxK18InX, MaxK18InY, MaxK18InU, MaxK18InV, MaxK18Delta };
  const double LowBandOut[5] =
    { MinK18OutX, MinK18OutY, MinK18OutU, MinK18OutV, MinK18Delta };
  const double UpperBandOut[5] =
    { MaxK18OutX, MaxK18OutY, MaxK18OutU, MaxK18OutV, MaxK18Delta };
}

//______________________________________________________________________________
K18TrackD2U::K18TrackD2U( double local_x, DCLocalTrack *track_out, double p0 )
  : m_local_x(local_x),
    m_track_out(track_out),
    m_p0(p0),
    m_Xi(0), m_Yi(0), m_Ui(0), m_Vi(0),
    m_Xo(0), m_Yo(0), m_Uo(0), m_Vo(0),
    m_status(false), m_good_for_analysis(true)
{
  debug::ObjectCounter::increase(class_name);
}

//______________________________________________________________________________
K18TrackD2U::~K18TrackD2U( void )
{
  debug::ObjectCounter::decrease(class_name);
}

//______________________________________________________________________________
bool
K18TrackD2U::CalcMomentumD2U( void )
{
  static const std::string func_name("["+class_name+"::"+__func__+"()]");

  m_status = false;

  if( !gK18Mtx.IsReady() ) return m_status;

  double xi, yi, ui, vi;
  double xo, yo, uo, vo;
  double delta1, delta2;
  xi= -m_track_out->GetX0();
  yi=  m_track_out->GetY0();
  ui=  m_track_out->GetU0();
  vi= -m_track_out->GetV0();
  xo= -m_local_x;

  m_status = gK18Mtx.CalcDeltaD2U( xi, yi, ui, vi,
				   xo, yo, uo, vo,
				   delta1, delta2 );

#if 0
  hddaq::cout << func_name << ": after calculation. "
	      << " StatusD2U=" << m_status  << std::endl;
#endif

  if( m_status ){
    // hddaq::cout << "delta1 = " << delta1 << ", delta2 = " << delta2 << std::endl;
    m_delta    = delta1;
    m_delta3rd = delta2;

    m_Xi = -xo;
    m_Yi =  yo;
    m_Ui =  uo;
    m_Vi = -vo;

    m_Xo = m_track_out->GetX0();
    m_Yo = m_track_out->GetY0();
    m_Uo = m_track_out->GetU0();
    m_Vo = m_track_out->GetV0();
  }

  return m_status;
}

//______________________________________________________________________________
ThreeVector
K18TrackD2U::BeamMomentumD2U( void ) const
{
  double u  = m_track_out->GetU0(), v=m_track_out->GetV0();
  double pz = P()/std::sqrt(1.+u*u+v*v);
  return ThreeVector( pz*u, pz*v, pz );
}

//______________________________________________________________________________
double
K18TrackD2U::GetChiSquare( void ) const
{
  return m_track_out->GetChiSquare();
}

//______________________________________________________________________________
double
K18TrackD2U::Xtgt( void ) const
{
  return m_track_out->GetU0()*zK18Target+m_track_out->GetX0();
}

//______________________________________________________________________________
double
K18TrackD2U::Ytgt( void ) const
{
  return m_track_out->GetV0()*zK18Target+m_track_out->GetY0();
}

//______________________________________________________________________________
double
K18TrackD2U::Utgt( void ) const
{
  return m_track_out->GetU0();
}

//______________________________________________________________________________
double
K18TrackD2U::Vtgt( void ) const
{
  return m_track_out->GetV0();
}

//______________________________________________________________________________
bool
K18TrackD2U::GoodForAnalysis( bool status )
{
  bool pre_status = m_good_for_analysis;
  m_good_for_analysis = status;
  return pre_status;
}

//______________________________________________________________________________
bool
K18TrackD2U::ReCalc( bool applyRecursively )
{
  if( applyRecursively )
    m_track_out->ReCalc(applyRecursively);

  return CalcMomentumD2U();
}
