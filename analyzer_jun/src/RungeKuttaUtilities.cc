/**
 *  file: RungeKuttaUtilities.cc
 *  date: 2017.04.10
 *  note: Runge-Kutta Routines
 *        Ref.) NIM 160 (1979) 43 - 48
 *
 */

#include "RungeKuttaUtilities.hh"

#include <cmath>
#include <iomanip>
#include <iostream>
#include <stdexcept>
#include <string>

#include <std_ostream.hh>

#include "ConfMan.hh"
#include "DCGeomMan.hh"
#include "DCGeomRecord.hh"
#include "EventDisplay.hh"
#include "FieldMan.hh"
#include "KuramaTrack.hh"
#include "PrintHelper.hh"

namespace
{
  const DCGeomMan& gGeom   = DCGeomMan::GetInstance();
  EventDisplay&    gEvDisp = EventDisplay::GetInstance();
  const FieldMan & gField  = FieldMan::GetInstance();
  // const int& IdTOF    = gGeom.DetectorId("TOF");
  const int& IdTOF_UX = gGeom.DetectorId("TOF-UX");
  const int& IdTOF_UY = gGeom.DetectorId("TOF-UY");
  const int& IdTOF_DX = gGeom.DetectorId("TOF-DX");
  const int& IdTOF_DY = gGeom.DetectorId("TOF-DY");
  const int& IdVTOF   = gGeom.DetectorId("VTOF");
  const int& IdTarget = gGeom.DetectorId("Target");

  const double CHLB     = 2.99792458E-4;
  // const double Polarity = 1.;
  const double Polarity = -1.;
}

#define WARNOUT 0
#define ExactFFTreat 1

//______________________________________________________________________________
void
RKFieldIntegral::Print( std::ostream &ost ) const
{
  PrintHelper helper( 3, std::ios::scientific, ost );
  ost << std::setw(9) << kx << " "
      << std::setw(9) << ky << std::endl;
  ost << std::setw(9) << axu << " "
      << std::setw(9) << axv << " "
      << std::setw(9) << ayu << " "
      << std::setw(9) << ayv << std::endl;
  ost << std::setw(9) << cxx << " "
      << std::setw(9) << cxy << " "
      << std::setw(9) << cyx << " "
      << std::setw(9) << cyy << std::endl;
}

//______________________________________________________________________________
void
RKDeltaFieldIntegral::Print( std::ostream &ost ) const
{
  PrintHelper helper( 3, std::ios::scientific, ost );
  ost << std::setw(9) << dkxx << " "
      << std::setw(9) << dkxy << " "
      << std::setw(9) << dkxu << " "
      << std::setw(9) << dkxv << " "
      << std::setw(9) << dkxq << std::endl;
  ost << std::setw(9) << dkyx << " "
      << std::setw(9) << dkyy << " "
      << std::setw(9) << dkyu << " "
      << std::setw(9) << dkyv << " "
      << std::setw(9) << dkyq << std::endl;
}

//______________________________________________________________________________
void
RKCordParameter::Print( std::ostream &ost ) const
{
  PrintHelper helper( 3, std::ios::scientific, ost );
}

//______________________________________________________________________________
RKCordParameter::RKCordParameter( const ThreeVector &pos,
                                  const ThreeVector &mom )
  : x( pos.x() ), y( pos.y() ), z( pos.z() ),
    u( mom.x()/mom.z() ), v( mom.y()/mom.z() )
{
  double p = mom.Mag();
  q = -Polarity/p;
}

//______________________________________________________________________________
ThreeVector
RKCordParameter::MomentumInGlobal( void ) const
{
  double p  = -Polarity/q;
  double pz = -std::abs(p)/std::sqrt(1.+u*u+v*v);
  return ThreeVector( pz*u, pz*v, pz );
}

//______________________________________________________________________________
void
RKTrajectoryPoint::Print( std::ostream &ost ) const
{
  PrintHelper helper( 3, std::ios::scientific, ost );
}

//______________________________________________________________________________
RKFieldIntegral
RK::CalcFieldIntegral( double U, double V, double Q, const ThreeVector &B )
{
  double fac = std::sqrt(1.+U*U+V*V);
  double f1  = U*V*B.x() - (1.+U*U)*B.y() + V*B.z();
  double f2  = (1.+V*V)*B.x() - U*V*B.y() - U*B.z();

  double axu = U/fac*f1 + fac*(V*B.x()-2.*U*B.y());
  double axv = V/fac*f1 + fac*(U*B.x()+B.z());
  double ayu = U/fac*f2 - fac*(V*B.y()+B.z());
  double ayv = V/fac*f2 + fac*(2.*V*B.x()-U*B.y());

  double qfac = Q*CHLB;

  return RKFieldIntegral( fac*f1*qfac, fac*f2*qfac,
			  axu*qfac, axv*qfac, ayu*qfac, ayv*qfac );

}

//______________________________________________________________________________
RKFieldIntegral
RK::CalcFieldIntegral( double U, double V, double Q, const ThreeVector &B,
		       const ThreeVector &dBdX, const ThreeVector &dBdY )
{
  double fac = std::sqrt(1.+U*U+V*V);
  double f1  = U*V*(B.x()) - (1.+U*U)*(B.y()) + V*(B.z());
  double f2  = (1.+V*V)*(B.x()) - U*V*(B.y()) - U*(B.z());

  double axu = U/fac*f1 + fac*(V*B.x()-2.*U*B.y());
  double axv = V/fac*f1 + fac*(U*B.x()+B.z());
  double ayu = U/fac*f2 - fac*(V*B.y()+B.z());
  double ayv = V/fac*f2 + fac*(2.*V*B.x()-U*B.y());

  double cxx = U*V*(dBdX.x()) - (1.+U*U)*(dBdX.y()) + V*(dBdX.z());
  double cxy = U*V*(dBdY.x()) - (1.+U*U)*(dBdY.y()) + V*(dBdY.z());
  double cyx = (1.+V*V)*(dBdX.x()) - U*V*(dBdX.y()) - U*(dBdX.z());
  double cyy = (1.+V*V)*(dBdY.x()) - U*V*(dBdY.y()) - U*(dBdY.z());

  double qfac = Q*CHLB;

  return RKFieldIntegral( fac*f1*qfac, fac*f2*qfac,
			  axu*qfac, axv*qfac, ayu*qfac, ayv*qfac,
			  fac*cxx*qfac, fac*cxy*qfac,
			  fac*cyx*qfac, fac*cyy*qfac );
}

//______________________________________________________________________________
RKDeltaFieldIntegral
RK::CalcDeltaFieldIntegral( const RKTrajectoryPoint &prevPoint,
			    const RKFieldIntegral &intg )
{
  double dkxx = intg.axu*prevPoint.dudx + intg.axv*prevPoint.dvdx
    + intg.cxx*prevPoint.dxdx + intg.cxy*prevPoint.dydx;
  double dkxy = intg.axu*prevPoint.dudy + intg.axv*prevPoint.dvdy
    + intg.cxx*prevPoint.dxdy + intg.cxy*prevPoint.dydy;
  double dkxu = intg.axu*prevPoint.dudu + intg.axv*prevPoint.dvdu
    + intg.cxx*prevPoint.dxdu + intg.cxy*prevPoint.dydu;
  double dkxv = intg.axu*prevPoint.dudv + intg.axv*prevPoint.dvdv
    + intg.cxx*prevPoint.dxdv + intg.cxy*prevPoint.dydv;
  double dkxq = intg.kx/prevPoint.r.q
    + intg.axu*prevPoint.dudq + intg.axv*prevPoint.dvdq
    + intg.cxx*prevPoint.dxdq + intg.cxy*prevPoint.dydq;

  double dkyx = intg.ayu*prevPoint.dudx + intg.ayv*prevPoint.dvdx
    + intg.cyx*prevPoint.dxdx + intg.cyy*prevPoint.dydx;
  double dkyy = intg.ayu*prevPoint.dudy + intg.ayv*prevPoint.dvdy
    + intg.cyx*prevPoint.dxdy + intg.cyy*prevPoint.dydy;
  double dkyu = intg.ayu*prevPoint.dudu + intg.ayv*prevPoint.dvdu
    + intg.cyx*prevPoint.dxdu + intg.cyy*prevPoint.dydu;
  double dkyv = intg.ayu*prevPoint.dudv + intg.ayv*prevPoint.dvdv
    + intg.cyx*prevPoint.dxdv + intg.cyy*prevPoint.dydv;
  double dkyq = intg.ky/prevPoint.r.q
    + intg.ayu*prevPoint.dudq + intg.ayv*prevPoint.dvdq
    + intg.cyx*prevPoint.dxdq + intg.cyy*prevPoint.dydq;

  return RKDeltaFieldIntegral( dkxx, dkxy, dkxu, dkxv, dkxq,
			       dkyx, dkyy, dkyu, dkyv, dkyq );
}

//______________________________________________________________________________
RKDeltaFieldIntegral
RK::CalcDeltaFieldIntegral( const RKTrajectoryPoint    &prevPoint,
			    const RKFieldIntegral      &intg,
			    const RKDeltaFieldIntegral &dIntg1,
			    const RKDeltaFieldIntegral &dIntg2,
			    double StepSize )
{
  double h  = StepSize;
  double h2 = StepSize*StepSize;

  double dkxx
    = intg.axu*(prevPoint.dudx + h*dIntg1.dkxx)
    + intg.axv*(prevPoint.dvdx + h*dIntg1.dkyx)
    + intg.cxx*(prevPoint.dxdx + h*prevPoint.dudx + 0.5*h2*dIntg2.dkxx)
    + intg.cxy*(prevPoint.dydx + h*prevPoint.dvdx + 0.5*h2*dIntg2.dkyx);
  double dkxy
    = intg.axu*(prevPoint.dudy + h*dIntg1.dkxy)
    + intg.axv*(prevPoint.dvdy + h*dIntg1.dkyy)
    + intg.cxx*(prevPoint.dxdy + h*prevPoint.dudy + 0.5*h2*dIntg2.dkxy)
    + intg.cxy*(prevPoint.dydy + h*prevPoint.dvdy + 0.5*h2*dIntg2.dkyy);
  double dkxu
    = intg.axu*(prevPoint.dudu + h*dIntg1.dkxu)
    + intg.axv*(prevPoint.dvdu + h*dIntg1.dkyu)
    + intg.cxx*(prevPoint.dxdu + h*prevPoint.dudu + 0.5*h2*dIntg2.dkxu)
    + intg.cxy*(prevPoint.dydu + h*prevPoint.dvdu + 0.5*h2*dIntg2.dkyu);
  double dkxv
    = intg.axu*(prevPoint.dudv + h*dIntg1.dkxv)
    + intg.axv*(prevPoint.dvdv + h*dIntg1.dkyv)
    + intg.cxx*(prevPoint.dxdv + h*prevPoint.dudv + 0.5*h2*dIntg2.dkxv)
    + intg.cxy*(prevPoint.dydv + h*prevPoint.dvdv + 0.5*h2*dIntg2.dkyv);
  double dkxq = intg.kx/prevPoint.r.q
    + intg.axu*(prevPoint.dudq + h*dIntg1.dkxq)
    + intg.axv*(prevPoint.dvdq + h*dIntg1.dkyq)
    + intg.cxx*(prevPoint.dxdq + h*prevPoint.dudq + 0.5*h2*dIntg2.dkxq)
    + intg.cxy*(prevPoint.dydq + h*prevPoint.dvdq + 0.5*h2*dIntg2.dkyq);

  double dkyx
    = intg.ayu*(prevPoint.dudx + h*dIntg1.dkxx)
    + intg.ayv*(prevPoint.dvdx + h*dIntg1.dkyx)
    + intg.cyx*(prevPoint.dxdx + h*prevPoint.dudx + 0.5*h2*dIntg2.dkxx)
    + intg.cyy*(prevPoint.dydx + h*prevPoint.dvdx + 0.5*h2*dIntg2.dkyx);
  double dkyy
    = intg.ayu*(prevPoint.dudy + h*dIntg1.dkxy)
    + intg.ayv*(prevPoint.dvdy + h*dIntg1.dkyy)
    + intg.cyx*(prevPoint.dxdy + h*prevPoint.dudy + 0.5*h2*dIntg2.dkxy)
    + intg.cyy*(prevPoint.dydy + h*prevPoint.dvdy + 0.5*h2*dIntg2.dkyy);
  double dkyu
    = intg.ayu*(prevPoint.dudu + h*dIntg1.dkxu)
    + intg.ayv*(prevPoint.dvdu + h*dIntg1.dkyu)
    + intg.cyx*(prevPoint.dxdu + h*prevPoint.dudu + 0.5*h2*dIntg2.dkxu)
    + intg.cyy*(prevPoint.dydu + h*prevPoint.dvdu + 0.5*h2*dIntg2.dkyu);
  double dkyv
    = intg.ayu*(prevPoint.dudv + h*dIntg1.dkxv)
    + intg.ayv*(prevPoint.dvdv + h*dIntg1.dkyv)
    + intg.cyx*(prevPoint.dxdv + h*prevPoint.dudv + 0.5*h2*dIntg2.dkxv)
    + intg.cyy*(prevPoint.dydv + h*prevPoint.dvdv + 0.5*h2*dIntg2.dkyv);
  double dkyq = intg.ky/prevPoint.r.q
    + intg.ayu*(prevPoint.dudq + h*dIntg1.dkxq)
    + intg.ayv*(prevPoint.dvdq + h*dIntg1.dkyq)
    + intg.cyx*(prevPoint.dxdq + h*prevPoint.dudq + 0.5*h2*dIntg2.dkxq)
    + intg.cyy*(prevPoint.dydq + h*prevPoint.dvdq + 0.5*h2*dIntg2.dkyq);

  return RKDeltaFieldIntegral( dkxx, dkxy, dkxu, dkxv, dkxq,
			       dkyx, dkyy, dkyu, dkyv, dkyq );
}

//______________________________________________________________________________
RKTrajectoryPoint
RK::TraceOneStep( double StepSize, const RKTrajectoryPoint &prevPoint )
{
  static const std::string func_name = "[RK::TraceOneStep()]";

  double pre_x = prevPoint.r.x;
  double pre_y = prevPoint.r.y;
  double pre_z = prevPoint.r.z;
  double pre_u = prevPoint.r.u;
  double pre_v = prevPoint.r.v;
  double pre_q = prevPoint.r.q;
  double dr    = StepSize/std::sqrt( 1.+pre_u*pre_u+pre_v*pre_v );

  ThreeVector Z1 = prevPoint.PositionInGlobal();
  ThreeVector B1 = gField.GetField( Z1 );
#ifdef ExactFFTreat
  ThreeVector dBdX1 = gField.GetdBdX( Z1 );
  ThreeVector dBdY1 = gField.GetdBdY( Z1 );
  RKFieldIntegral f1 =
    RK::CalcFieldIntegral( pre_u, pre_v, pre_q,
			   B1, dBdX1, dBdY1 );
#else
  RKFieldIntegral f1 =
    RK::CalcFieldIntegral( pre_u, pre_v, pre_q, B1 );
#endif
  RKDeltaFieldIntegral df1 =
    RK::CalcDeltaFieldIntegral( prevPoint, f1 );

  ThreeVector Z2 = Z1 +
    ThreeVector( 0.5*dr,
                 0.5*dr*pre_u + 0.125*dr*dr*f1.kx,
                 0.5*dr*pre_v + 0.125*dr*dr*f1.ky );
  ThreeVector B2 = gField.GetField( Z2 );
#ifdef ExactFFTreat
  ThreeVector dBdX2 = gField.GetdBdX( Z2 );
  ThreeVector dBdY2 = gField.GetdBdY( Z2 );
  RKFieldIntegral f2 =
    RK::CalcFieldIntegral( pre_u + 0.5*dr*f1.kx,
			   pre_v + 0.5*dr*f1.ky,
			   pre_q, B2, dBdX2, dBdY2 );
#else
  RKFieldIntegral f2 =
    RK::CalcFieldIntegral( pre_u + 0.5*dr*f1.kx,
			   pre_v + 0.5*dr*f1.ky,
			   pre_q, B2 );
#endif
  RKDeltaFieldIntegral df2 =
    RK::CalcDeltaFieldIntegral( prevPoint, f2, df1, df1, 0.5*dr );

#ifdef ExactFFTreat
  RKFieldIntegral f3 =
    RK::CalcFieldIntegral( pre_u + 0.5*dr*f2.kx,
			   pre_v + 0.5*dr*f2.ky,
			   pre_q, B2, dBdX2, dBdY2 );
#else
  RKFieldIntegral f3 =
    RK::CalcFieldIntegral( pre_u + 0.5*dr*f2.kx,
			   pre_v + 0.5*dr*f2.ky,
			   pre_q, B2 );
#endif
  RKDeltaFieldIntegral df3 =
    RK::CalcDeltaFieldIntegral( prevPoint, f3, df2, df1, 0.5*dr );

  ThreeVector Z4 = Z1 +
    ThreeVector( dr,
                 dr*pre_u + 0.5*dr*dr*f3.kx,
                 dr*pre_v + 0.5*dr*dr*f3.ky );
  ThreeVector B4 = gField.GetField( Z4 );
#ifdef ExactFFTreat
  ThreeVector dBdX4 = gField.GetdBdX( Z4 );
  ThreeVector dBdY4 = gField.GetdBdY( Z4 );
  RKFieldIntegral f4 =
    RK::CalcFieldIntegral( pre_u + dr*f3.kx,
			   pre_v + dr*f3.ky,
			   pre_q, B4, dBdX4, dBdY4 );
#else
  RKFieldIntegral f4 =
    RK::CalcFieldIntegral( pre_u + dr*f3.kx,
                         pre_v + dr*f3.ky,
                         pre_q, B4 );
#endif
  RKDeltaFieldIntegral df4 =
    RK::CalcDeltaFieldIntegral( prevPoint, f4, df3, df3, dr );

  double z = pre_z + dr;
  double x = pre_x + dr*pre_u
    + 1./6.*dr*dr*(f1.kx+f2.kx+f3.kx);
  double y = pre_y + dr*pre_v
    + 1./6.*dr*dr*(f1.ky+f2.ky+f3.ky);
  double u = pre_u + 1./6.*dr*(f1.kx+2.*(f2.kx+f3.kx)+f4.kx);
  double v = pre_v + 1./6.*dr*(f1.ky+2.*(f2.ky+f3.ky)+f4.ky);

  double dxdx = prevPoint.dxdx + dr*prevPoint.dudx
    + 1./6.*dr*dr*(df1.dkxx+df2.dkxx+df3.dkxx);
  double dxdy = prevPoint.dxdy + dr*prevPoint.dudy
    + 1./6.*dr*dr*(df1.dkxy+df2.dkxy+df3.dkxy);
  double dxdu = prevPoint.dxdu + dr*prevPoint.dudu
    + 1./6.*dr*dr*(df1.dkxu+df2.dkxu+df3.dkxu);
  double dxdv = prevPoint.dxdv + dr*prevPoint.dudv
    + 1./6.*dr*dr*(df1.dkxv+df2.dkxv+df3.dkxv);
  double dxdq = prevPoint.dxdq + dr*prevPoint.dudq
    + 1./6.*dr*dr*(df1.dkxq+df2.dkxq+df3.dkxq);

  double dydx = prevPoint.dydx + dr*prevPoint.dvdx
    + 1./6.*dr*dr*(df1.dkyx+df2.dkyx+df3.dkyx);
  double dydy = prevPoint.dydy + dr*prevPoint.dvdy
    + 1./6.*dr*dr*(df1.dkyy+df2.dkyy+df3.dkyy);
  double dydu = prevPoint.dydu + dr*prevPoint.dvdu
    + 1./6.*dr*dr*(df1.dkyu+df2.dkyu+df3.dkyu);
  double dydv = prevPoint.dydv + dr*prevPoint.dvdv
    + 1./6.*dr*dr*(df1.dkyv+df2.dkyv+df3.dkyv);
  double dydq = prevPoint.dydq + dr*prevPoint.dvdq
    + 1./6.*dr*dr*(df1.dkyq+df2.dkyq+df3.dkyq);

  double dudx = prevPoint.dudx
    + 1./6.*dr*(df1.dkxx+2.*(df2.dkxx+df3.dkxx)+df4.dkxx);
  double dudy = prevPoint.dudy
    + 1./6.*dr*(df1.dkxy+2.*(df2.dkxy+df3.dkxy)+df4.dkxy);
  double dudu = prevPoint.dudu
    + 1./6.*dr*(df1.dkxu+2.*(df2.dkxu+df3.dkxu)+df4.dkxu);
  double dudv = prevPoint.dudv
    + 1./6.*dr*(df1.dkxv+2.*(df2.dkxv+df3.dkxv)+df4.dkxv);
  double dudq = prevPoint.dudq
    + 1./6.*dr*(df1.dkxq+2.*(df2.dkxq+df3.dkxq)+df4.dkxq);

  double dvdx = prevPoint.dvdx
    + 1./6.*dr*(df1.dkyx+2.*(df2.dkyx+df3.dkyx)+df4.dkyx);
  double dvdy = prevPoint.dvdy
    + 1./6.*dr*(df1.dkyy+2.*(df2.dkyy+df3.dkyy)+df4.dkyy);
  double dvdu = prevPoint.dvdu
    + 1./6.*dr*(df1.dkyu+2.*(df2.dkyu+df3.dkyu)+df4.dkyu);
  double dvdv = prevPoint.dvdv
    + 1./6.*dr*(df1.dkyv+2.*(df2.dkyv+df3.dkyv)+df4.dkyv);
  double dvdq = prevPoint.dvdq
    + 1./6.*dr*(df1.dkyq+2.*(df2.dkyq+df3.dkyq)+df4.dkyq);

  double dl = (ThreeVector(x,y,z)-Z1).Mag()*StepSize/std::abs(StepSize);

#if 0
  {
    PrintHelper helper( 2, std::ios::fixed );
    hddaq::cout << func_name << ": "
		<< std::setw(9) << x
		<< std::setw(9) << y
		<< std::setw(9) << z;
    hddaq::cout.precision(4);
    hddaq::cout << std::setw(10) << u
		<< std::setw(10) << v
		<< std::setw(10) << prevPoint.r.q;
    hddaq::cout.precision(2);
    hddaq::cout << std::setw(10) << prevPoint.l+dl;
    hddaq::cout.precision(4);
    hddaq::cout << std::setw(10) << B1.z()
		<< std::endl;


    helper.set( 3, std::ios::scientific );
    hddaq::cout << std::setw(10) << dxdx << " "
		<< std::setw(10) << dxdy << " "
		<< std::setw(10) << dxdu << " "
		<< std::setw(10) << dxdv << " "
		<< std::setw(10) << dxdq << std::endl;
    hddaq::cout << std::setw(10) << dydx << " "
		<< std::setw(10) << dydy << " "
		<< std::setw(10) << dydu << " "
		<< std::setw(10) << dydv << " "
		<< std::setw(10) << dydq << std::endl;
    hddaq::cout << std::setw(10) << dudx << " "
		<< std::setw(10) << dudy << " "
		<< std::setw(10) << dudu << " "
		<< std::setw(10) << dudv << " "
		<< std::setw(10) << dudq << std::endl;
    hddaq::cout << std::setw(10) << dvdx << " "
		<< std::setw(10) << dvdy << " "
		<< std::setw(10) << dvdu << " "
		<< std::setw(10) << dvdv << " "
		<< std::setw(10) << dvdq << std::endl;
  }
#endif

  return RKTrajectoryPoint( x, y, z, u, v, prevPoint.r.q,
                            dxdx, dxdy, dxdu, dxdv, dxdq,
                            dydx, dydy, dydu, dydv, dydq,
                            dudx, dudy, dudu, dudv, dudq,
                            dvdx, dvdy, dvdu, dvdv, dvdq,
                            prevPoint.l+dl );
}

//______________________________________________________________________________
bool
RK::CheckCrossing( int lnum, const RKTrajectoryPoint &startPoint,
		   const RKTrajectoryPoint &endPoint,
		   RKcalcHitPoint &crossPoint )
{
  static const std::string func_name = "[RK::CheckCrossing()]";

  const DCGeomRecord *geom_record = gGeom.GetRecord( lnum );
  ThreeVector posVector   = geom_record->Position();
  ThreeVector nomalVector = geom_record->NormalVector();

  ThreeVector startVector = startPoint.PositionInGlobal();
  ThreeVector endVector   = endPoint.PositionInGlobal();
  // move to origin
  startVector -= posVector;
  endVector   -= posVector;

  // inner product
  double ip1 = nomalVector * startVector;
  double ip2 = nomalVector * endVector;

  // judge whether start/end points are same side
  if( ip1*ip2 > 0. ) return false;

  double x = (ip1*endPoint.r.x - ip2*startPoint.r.x)/(ip1-ip2);
  double y = (ip1*endPoint.r.y - ip2*startPoint.r.y)/(ip1-ip2);
  double z = (ip1*endPoint.r.z - ip2*startPoint.r.z)/(ip1-ip2);
  double u = (ip1*endPoint.r.u - ip2*startPoint.r.u)/(ip1-ip2);
  double v = (ip1*endPoint.r.v - ip2*startPoint.r.v)/(ip1-ip2);
  double q = (ip1*endPoint.r.q - ip2*startPoint.r.q)/(ip1-ip2);
  double l = (ip1*endPoint.l   - ip2*startPoint.l)/(ip1-ip2);

  double dxdx = (ip1*endPoint.dxdx - ip2*startPoint.dxdx)/(ip1-ip2);
  double dxdy = (ip1*endPoint.dxdy - ip2*startPoint.dxdy)/(ip1-ip2);
  double dxdu = (ip1*endPoint.dxdu - ip2*startPoint.dxdu)/(ip1-ip2);
  double dxdv = (ip1*endPoint.dxdv - ip2*startPoint.dxdv)/(ip1-ip2);
  double dxdq = (ip1*endPoint.dxdq - ip2*startPoint.dxdq)/(ip1-ip2);

  double dydx = (ip1*endPoint.dydx - ip2*startPoint.dydx)/(ip1-ip2);
  double dydy = (ip1*endPoint.dydy - ip2*startPoint.dydy)/(ip1-ip2);
  double dydu = (ip1*endPoint.dydu - ip2*startPoint.dydu)/(ip1-ip2);
  double dydv = (ip1*endPoint.dydv - ip2*startPoint.dydv)/(ip1-ip2);
  double dydq = (ip1*endPoint.dydq - ip2*startPoint.dydq)/(ip1-ip2);

  double dudx = (ip1*endPoint.dudx - ip2*startPoint.dudx)/(ip1-ip2);
  double dudy = (ip1*endPoint.dudy - ip2*startPoint.dudy)/(ip1-ip2);
  double dudu = (ip1*endPoint.dudu - ip2*startPoint.dudu)/(ip1-ip2);
  double dudv = (ip1*endPoint.dudv - ip2*startPoint.dudv)/(ip1-ip2);
  double dudq = (ip1*endPoint.dudq - ip2*startPoint.dudq)/(ip1-ip2);

  double dvdx = (ip1*endPoint.dvdx - ip2*startPoint.dvdx)/(ip1-ip2);
  double dvdy = (ip1*endPoint.dvdy - ip2*startPoint.dvdy)/(ip1-ip2);
  double dvdu = (ip1*endPoint.dvdu - ip2*startPoint.dvdu)/(ip1-ip2);
  double dvdv = (ip1*endPoint.dvdv - ip2*startPoint.dvdv)/(ip1-ip2);
  double dvdq = (ip1*endPoint.dvdq - ip2*startPoint.dvdq)/(ip1-ip2);

  double pz = Polarity/(std::sqrt(1.+u*u+v*v)*q);

  crossPoint.posG = ThreeVector( x, y, z );
  crossPoint.momG = ThreeVector( pz*u, pz*v, pz );

  if( lnum==IdTOF_UX || lnum==IdTOF_DX )
    crossPoint.s = crossPoint.posG.x();
  else if( lnum==IdTOF_UY || lnum==IdTOF_DY )
    crossPoint.s = crossPoint.posG.y();
  else
    crossPoint.s = gGeom.Global2LocalPos( lnum, crossPoint.posG ).x();

  crossPoint.l    = l;

  double sx = geom_record->dsdx();
  double sy = geom_record->dsdy();
  double sz = geom_record->dsdz();
  double ux = geom_record->dudx();
  double uy = geom_record->dudy();
  double uz = geom_record->dudz();

  if( uz==0. ){
    crossPoint.dsdx = crossPoint.dsdy =
      crossPoint.dsdu = crossPoint.dsdv = crossPoint.dsdq = 0.;
    crossPoint.dsdxx = crossPoint.dsdxy =
      crossPoint.dsdxu = crossPoint.dsdxv = crossPoint.dsdxq = 0.;
    crossPoint.dsdyx = crossPoint.dsdyy =
      crossPoint.dsdyu = crossPoint.dsdyv = crossPoint.dsdyq = 0.;
    crossPoint.dsdux = crossPoint.dsduy =
      crossPoint.dsduu = crossPoint.dsduv = crossPoint.dsduq = 0.;
    crossPoint.dsdvx = crossPoint.dsdvy =
      crossPoint.dsdvu = crossPoint.dsdvv = crossPoint.dsdvq = 0.;
    crossPoint.dsdqx = crossPoint.dsdqy =
      crossPoint.dsdqu = crossPoint.dsdqv = crossPoint.dsdqq = 0.;
  }
  else {
    double ffx = ux/uz, ffy = uy/uz;
    double dzdx = -ffx*dxdx - ffy*dydx;
    double dzdy = -ffx*dxdy - ffy*dydy;
    double dzdu = -ffx*dxdu - ffy*dydu;
    double dzdv = -ffx*dxdv - ffy*dydv;
    double dzdq = -ffx*dxdq - ffy*dydq;

    crossPoint.dsdx = sx*dxdx + sy*dydx + sz*dzdx;
    crossPoint.dsdy = sx*dxdy + sy*dydy + sz*dzdy;
    crossPoint.dsdu = sx*dxdu + sy*dydu + sz*dzdu;
    crossPoint.dsdv = sx*dxdv + sy*dydv + sz*dzdv;
    crossPoint.dsdq = sx*dxdq + sy*dydq + sz*dzdq;

    crossPoint.dsdxx = sx*dzdx*dudx + sy*dzdx*dvdx;
    crossPoint.dsdxy = sx*dzdx*dudy + sy*dzdx*dvdy;
    crossPoint.dsdxu = sx*dzdx*dudu + sy*dzdx*dvdu;
    crossPoint.dsdxv = sx*dzdx*dudv + sy*dzdx*dvdv;
    crossPoint.dsdxq = sx*dzdx*dudq + sy*dzdx*dvdq;

    crossPoint.dsdyx = sx*dzdy*dudx + sy*dzdy*dvdx;
    crossPoint.dsdyy = sx*dzdy*dudy + sy*dzdy*dvdy;
    crossPoint.dsdyu = sx*dzdy*dudu + sy*dzdy*dvdu;
    crossPoint.dsdyv = sx*dzdy*dudv + sy*dzdy*dvdv;
    crossPoint.dsdyq = sx*dzdy*dudq + sy*dzdy*dvdq;

    crossPoint.dsdux = sx*dzdu*dudx + sy*dzdu*dvdx;
    crossPoint.dsduy = sx*dzdu*dudy + sy*dzdu*dvdy;
    crossPoint.dsduu = sx*dzdu*dudu + sy*dzdu*dvdu;
    crossPoint.dsduv = sx*dzdu*dudv + sy*dzdu*dvdv;
    crossPoint.dsduq = sx*dzdu*dudq + sy*dzdu*dvdq;

    crossPoint.dsdvx = sx*dzdv*dudx + sy*dzdv*dvdx;
    crossPoint.dsdvy = sx*dzdv*dudy + sy*dzdv*dvdy;
    crossPoint.dsdvu = sx*dzdv*dudu + sy*dzdv*dvdu;
    crossPoint.dsdvv = sx*dzdv*dudv + sy*dzdv*dvdv;
    crossPoint.dsdvq = sx*dzdv*dudq + sy*dzdv*dvdq;

    crossPoint.dsdqx = sx*dzdq*dudx + sy*dzdq*dvdx;
    crossPoint.dsdqy = sx*dzdq*dudy + sy*dzdq*dvdy;
    crossPoint.dsdqu = sx*dzdq*dudu + sy*dzdq*dvdu;
    crossPoint.dsdqv = sx*dzdq*dudv + sy*dzdq*dvdv;
    crossPoint.dsdqq = sx*dzdq*dudq + sy*dzdq*dvdq;
  }

  crossPoint.dxdx=dxdx; crossPoint.dxdy=dxdy; crossPoint.dxdu=dxdu;
  crossPoint.dxdv=dxdv; crossPoint.dxdq=dxdq;
  crossPoint.dydx=dydx; crossPoint.dydy=dydy; crossPoint.dydu=dydu;
  crossPoint.dydv=dydv; crossPoint.dydq=dydq;
  crossPoint.dudx=dudx; crossPoint.dudy=dudy; crossPoint.dudu=dudu;
  crossPoint.dudv=dudv; crossPoint.dudq=dudq;
  crossPoint.dvdx=dvdx; crossPoint.dvdy=dvdy; crossPoint.dvdu=dvdu;
  crossPoint.dvdv=dvdv; crossPoint.dvdq=dvdq;

#if 0
  {
    PrintHelper helper( 5, std::ios::fixed );
    hddaq::cout << func_name << ": Layer#"
		<< std::setw(3) << lnum << std::endl;
    hddaq::cout << " " << std::setw(12) << dxdx
		<< " " << std::setw(12) << dxdy
		<< " " << std::setw(12) << dxdu
		<< " " << std::setw(12) << dxdv
		<< " " << std::setw(12) << dxdq << std::endl;
    hddaq::cout << " " << std::setw(12) << dydx
		<< " " << std::setw(12) << dydy
		<< " " << std::setw(12) << dydu
		<< " " << std::setw(12) << dydv
		<< " " << std::setw(12) << dydq << std::endl;
    hddaq::cout << " " << std::setw(12) << dudx
		<< " " << std::setw(12) << dudy
		<< " " << std::setw(12) << dudu
		<< " " << std::setw(12) << dudv
		<< " " << std::setw(12) << dudq << std::endl;
    hddaq::cout << " " << std::setw(12) << dvdx
		<< " " << std::setw(12) << dvdy
		<< " " << std::setw(12) << dvdu
		<< " " << std::setw(12) << dvdv
		<< " " << std::setw(12) << dvdq << std::endl;
  }
#endif

  return true;
}

//______________________________________________________________________________
int
RK::Trace( const RKCordParameter &initial, RKHitPointContainer &hitContainer )
{
  static const std::string func_name="[RK::Trace()]";

  const std::size_t nPlane = hitContainer.size();
  int iPlane = nPlane-1;

  RKTrajectoryPoint prevPoint( initial,
                               1., 0., 0., 0., 0.,
                               0., 1., 0., 0., 0.,
                               0., 0., 1., 0., 0.,
                               0., 0., 0., 1., 0.,
                               0.0 );
  int    MaxStep        = 40000;
  static const double MaxPathLength  = 6000.; // mm
  static const double NormalStepSize = - 10.;   // mm
  double MinStepSize = 2.;     // mm

  /*for EventDisplay*/
  ThreeVector StepPoint[MaxStep];

  int iStep = 0;

  while( ++iStep < MaxStep ){
    //    std::cout << "step#: " << iStep << std::endl;
    double StepSize = gField.StepSize( prevPoint.PositionInGlobal(),
				       NormalStepSize, MinStepSize );
    RKTrajectoryPoint nextPoint = RK::TraceOneStep( StepSize, prevPoint );

    /*for EventDisplay*/
    StepPoint[iStep-1] = nextPoint.PositionInGlobal();

    while( RK::CheckCrossing( hitContainer[iPlane].first,
			      prevPoint, nextPoint,
			      hitContainer[iPlane].second ) ){
#if 0
      {
	PrintHelper helper( 1, std::ios::fixed );

	hddaq::cout << std::flush;
        int plnum = hitContainer[iPlane].first;
        const RKcalcHitPoint &chp = hitContainer[iPlane].second;
        const ThreeVector &gpos = chp.PositionInGlobal();
        const ThreeVector &gmom = chp.MomentumInGlobal();

	hddaq::cout << func_name << ": PL#="
		    << std::setw(2) << plnum  << " X="
		    << std::setw(7) << chp.PositionInLocal()
		    << " ("  << std::setw(8) << gpos.x()
		    << ","   << std::setw(8) << gpos.y()
		    << ","   << std::setw(8) << gpos.z()
		    << ")";
	helper.precision(3);
	hddaq::cout << " P=" << std::setw(8) << gmom.Mag()
		    << "  (" << std::setw(8) << gmom.x()
		    << ","   << std::setw(8) << gmom.y()
		    << ","   << std::setw(8) << gmom.z()
		    << ")"   << std::endl;

	helper.precision(2);
	hddaq::cout << "  PL=" << std::setw(10) << chp.PathLength();
	helper.set( 3, std::ios::scientific );
	hddaq::cout << "  Coeff.s = "
		    << std::setw(10) << chp.coefX() << " "
		    << std::setw(10) << chp.coefY() << " "
		    << std::setw(10) << chp.coefU() << " "
		    << std::setw(10) << chp.coefV() << " "
		    << std::setw(10) << chp.coefQ() << std::endl;
      }
#endif
      --iPlane;
      if( iPlane<0 ) {
	if( gEvDisp.IsReady() ){
	  double q = hitContainer[0].second.MomentumInGlobal().z();
	  gEvDisp.DrawKuramaTrack( iStep, StepPoint, q );
        }
	return KuramaTrack::kPassed;
      }
    } // while( RKcheckCrossing() )

    if( nextPoint.PathLength() > MaxPathLength ){
#if WARNOUT
      hddaq::cerr << func_name << ": Exceed MaxPathLength. "
		  << " PL=" << std::dec << nextPoint.PathLength()
		  << " Step=" << std::dec << iStep
		  << " iPlane=" << std::dec << hitContainer[iPlane+1].first
		  << std::endl;
#endif
      return KuramaTrack::kExceedMaxPathLength;
    }
    prevPoint = nextPoint;
  }// while( ++iStep )

#if WARNOUT
  hddaq::cerr << func_name << ": Exceed MaxStep. "
	      << " PL=" << std::dec << prevPoint.PathLength()
	      << " Step=" << std::dec << iStep
	      << " iPlane=" << std::dec << hitContainer[iPlane+1].first
	      << std::endl;
#endif
  return KuramaTrack::kExceedMaxPathLength;
}

//______________________________________________________________________________
bool
RK::TraceToLast( RKHitPointContainer &hitContainer )
{
  static const std::string func_name="[RK::TraceToLast()]";
  int nPlane = (int)hitContainer.size();
  int iPlane = nPlane-1;
  int idini  = hitContainer[iPlane].first;

  // add downstream detectors from TOF
  std::vector<int> IdList = gGeom.GetDetectorIDList();
  std::size_t IdSize = IdList.size();
  for( std::size_t i=0; i<IdSize; ++i ){
    if( idini<IdList[i] && IdList[i]<=IdVTOF ){
      hitContainer.push_back( std::make_pair( IdList[i], RKcalcHitPoint() ) );
    }
  }

  nPlane = hitContainer.size();

  const RKcalcHitPoint& hpini  = hitContainer[iPlane].second;
  // const ThreeVector&    iniPos = hpini.PositionInGlobal();
  // const ThreeVector&    iniMom = hpini.MomentumInGlobal();

  RKTrajectoryPoint prevPoint( hpini );

  const int    MaxStep  = 80000;
  const double StepSize =  -20.;  // mm

  iPlane += 1;

  ThreeVector StepPoint[MaxStep];
  int iStep = 0;
  while( ++iStep < MaxStep ){
    RKTrajectoryPoint
      nextPoint = RK::TraceOneStep( -StepSize, prevPoint );

    StepPoint[iStep-1] = nextPoint.PositionInGlobal();

    while( RK::CheckCrossing( hitContainer[iPlane].first,
			      prevPoint, nextPoint,
			      hitContainer[iPlane].second ) ){
      if( ++iPlane>=nPlane ){
	// if( gEvDisp.IsReady() ){
	//   double q = hitContainer[0].second.MomentumInGlobal().z();
	//   gEvDisp.DrawKuramaTrack( iStep, StepPoint, q );
        // }
	return true;
      }
    }
    prevPoint = nextPoint;
  }

  return false;
}

//______________________________________________________________________________
RKHitPointContainer
RK::MakeHPContainer( void )
{
  std::vector<int> IdList   = gGeom.GetDetectorIDList();
  static const std::size_t size = IdList.size();
  RKHitPointContainer container;
  container.reserve( size );

  // for( std::size_t i=0; i<size; ++i ){
  //   if( IdList[i]<IdTOF )
  //     container.push_back( std::make_pair( IdList[i], RKcalcHitPoint() ) );
  // }

  /*** From Upstream ***/
  container.push_back( std::make_pair( IdTarget, RKcalcHitPoint() ) );
  
  for( std::size_t i=0; i<NumOfLayersSFT; ++i ){
    std::size_t plid = i +PlOffsSft +1;
    container.push_back( std::make_pair( plid, RKcalcHitPoint() ) );
  }
  for( std::size_t i=0; i<NumOfLayersSDC1; ++i ){
    std::size_t plid = i +PlOffsSdcIn +1;
    container.push_back( std::make_pair( plid, RKcalcHitPoint() ) );
  }
  for( std::size_t i=0; i<NumOfLayersVP; ++i ){
    std::size_t plid = i +PlOffsVP +1;
    container.push_back( std::make_pair( plid, RKcalcHitPoint() ) );
  }
  for( std::size_t i=0; i<NumOfLayersSdcOut; ++i ){
    std::size_t plid = 80;
    if( i<4 ){
      plid = i +PlOffsFbt;
    }
    else if( i<12 ){
      plid = i -3 +PlOffsSdcOut;
    }
    else{
      plid = i -8 +PlOffsFbt;
    }
    
    container.push_back( std::make_pair( plid, RKcalcHitPoint() ) );
  }
  
  container.push_back( std::make_pair( IdTOF_UX, RKcalcHitPoint() ) );
  container.push_back( std::make_pair( IdTOF_UY, RKcalcHitPoint() ) );
  container.push_back( std::make_pair( IdTOF_DX, RKcalcHitPoint() ) );
  container.push_back( std::make_pair( IdTOF_DY, RKcalcHitPoint() ) );

  return container;
}

//______________________________________________________________________________
const RKcalcHitPoint&
RKHitPointContainer::HitPointOfLayer( int lnum ) const
{
  static const std::string func_name =
    "[RKHitPointContainer::HitPointOfLayer(int) const]";

  std::vector<std::pair<int,RKcalcHitPoint> >::const_iterator
    itr = this->begin(), end = this->end();

  for( ; itr!=end; ++itr ){
    if( lnum == itr->first )
      return itr->second;
  }
  hddaq::cerr << func_name << ": No Record. #Layer="
	      << lnum << std::endl;
  throw std::out_of_range( func_name+": No Record" );
}

//______________________________________________________________________________
RKcalcHitPoint&
RKHitPointContainer::HitPointOfLayer( int lnum )
{
  static const std::string func_name =
    "[RKHitPointContainer::HitPointOfLayer(int)]";

  std::vector<std::pair<int,RKcalcHitPoint> >::iterator
    itr = this->begin(), end = this->end();

  for( ; itr!=end; ++itr ){
    if( lnum == itr->first )
      return itr->second;
  }
  hddaq::cerr << func_name << ": No Record. #Layer="
	      << lnum << std::endl;
  throw std::out_of_range( func_name+": No Record" );
}
