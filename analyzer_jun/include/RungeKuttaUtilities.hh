/**
 *  file: RungeKuttaUtilities.hh
 *  date: 2017.04.10
 *
 */

#ifndef RUNGE_KUTTA_UTILITIES_HH
#define RUNGE_KUTTA_UTILITIES_HH

#include "ThreeVector.hh"

#include <vector>
#include <utility>
#include <iosfwd>

class RKFieldIntegral;
class RKDeltaFieldIntegral;
class RKTrajectoryPoint;
class RKcalcHitPoint;
class RKCordParameter;
class RKHitPointContainer;

//______________________________________________________________________________
namespace RK
{
  //______________________________________________________________________________
  RKFieldIntegral
  CalcFieldIntegral( double U, double V, double Q, const ThreeVector &B );
  //______________________________________________________________________________
  RKFieldIntegral
  CalcFieldIntegral( double U, double V, double Q,
		     const ThreeVector &B,
		     const ThreeVector &dBdX, const ThreeVector &dBdY );
  //______________________________________________________________________________
  RKDeltaFieldIntegral
  CalcDeltaFieldIntegral( const RKTrajectoryPoint &prevPoint,
			  const RKFieldIntegral &intg );
  //______________________________________________________________________________
  RKDeltaFieldIntegral
  CalcDeltaFieldIntegral( const RKTrajectoryPoint &prevPoint,
			  const RKFieldIntegral &intg,
			  const RKDeltaFieldIntegral &dIntg1,
			  const RKDeltaFieldIntegral &dIntg2, double StepSize );
  //______________________________________________________________________________
  bool
  CheckCrossing( int lnum, const RKTrajectoryPoint &startPoint,
		 const RKTrajectoryPoint &endPoint, RKcalcHitPoint &crossPoint );
  //______________________________________________________________________________
  int
  Trace( const RKCordParameter &initial, RKHitPointContainer &hitContainer );
  //______________________________________________________________________________
  RKTrajectoryPoint
  TraceOneStep( double StepSize, const RKTrajectoryPoint &prevPoint );
  //______________________________________________________________________________
  bool
  TraceToLast( RKHitPointContainer &hitContainer );
  //______________________________________________________________________________
  RKHitPointContainer
  MakeHPContainer( void );
}

//______________________________________________________________________________
class RKFieldIntegral
{
public:
  RKFieldIntegral( double Kx, double Ky,
		   double Axu, double Axv, double Ayu, double Ayv,
		   double Cxx=0., double Cxy=0.,
		   double Cyx=0., double Cyy=0. )
    : kx(Kx), ky(Ky), axu(Axu), axv(Axv), ayu(Ayu), ayv(Ayv),
      cxx(Cxx), cxy(Cxy), cyx(Cyx), cyy(Cyy)
  {
  }

private:
  double kx, ky;
  double axu, axv, ayu, ayv;
  double cxx, cxy, cyx, cyy;

public:
  void Print( std::ostream &ost ) const;

  friend RKTrajectoryPoint RK::TraceOneStep( double, const RKTrajectoryPoint & );
  friend RKDeltaFieldIntegral
  RK::CalcDeltaFieldIntegral( const RKTrajectoryPoint &,
			      const RKFieldIntegral &,
			      const RKDeltaFieldIntegral &,
			      const RKDeltaFieldIntegral &, double );
  friend RKDeltaFieldIntegral
  RK::CalcDeltaFieldIntegral( const RKTrajectoryPoint &,
			      const RKFieldIntegral & );
};

//______________________________________________________________________________
class RKDeltaFieldIntegral
{
public:
  RKDeltaFieldIntegral( double dKxx, double dKxy, double dKxu,
			double dKxv, double dKxq,
			double dKyx, double dKyy, double dKyu,
			double dKyv, double dKyq )
    : dkxx(dKxx), dkxy(dKxy), dkxu(dKxu), dkxv(dKxv), dkxq(dKxq),
      dkyx(dKyx), dkyy(dKyy), dkyu(dKyu), dkyv(dKyv), dkyq(dKyq)
  {}

private:
  double dkxx, dkxy, dkxu, dkxv, dkxq;
  double dkyx, dkyy, dkyu, dkyv, dkyq;
public:
  void Print( std::ostream &ost ) const;
  friend RKTrajectoryPoint RK::TraceOneStep( double, const RKTrajectoryPoint & );
  friend RKDeltaFieldIntegral
  RK::CalcDeltaFieldIntegral( const RKTrajectoryPoint &,
			      const RKFieldIntegral &,
			      const RKDeltaFieldIntegral &,
			      const RKDeltaFieldIntegral &, double );
  friend RKDeltaFieldIntegral
  RK::CalcDeltaFieldIntegral( const RKTrajectoryPoint &,
			      const RKFieldIntegral & );
};

//______________________________________________________________________________
class RKCordParameter
{
public:
  RKCordParameter( void )
    : x(0.), y(0.), z(0.), u(0.), v(0.), q(0.)
  {}
  RKCordParameter( double X, double Y, double Z,
                   double U, double V, double Q )
    : x(X), y(Y), z(Z), u(U), v(V), q(Q)
  {}

  RKCordParameter( const ThreeVector &pos,
                   double U, double V, double Q )
    : x(pos.x()), y(pos.y()), z(pos.z()),
      u(U), v(V), q(Q)
  {}

  RKCordParameter( const ThreeVector &pos,
                   const ThreeVector &mom );
private:
  double x, y, z, u, v, q;
public:
  ThreeVector PositionInGlobal( void ) const
  { return ThreeVector( x, y, z ); }
  ThreeVector MomentumInGlobal( void ) const;
  void Print( std::ostream &ost ) const;

  double X( void ) const { return x; }
  double Y( void ) const { return y; }
  double Z( void ) const { return z; }
  double U( void ) const { return u; }
  double V( void ) const { return v; }
  double Q( void ) const { return q; }

  friend class RKTrajectoryPoint;
  friend RKTrajectoryPoint
  RK::TraceOneStep( double, const RKTrajectoryPoint & );
  friend RKDeltaFieldIntegral
  RK::CalcDeltaFieldIntegral( const RKTrajectoryPoint &,
			      const RKFieldIntegral &,
			      const RKDeltaFieldIntegral &,
			      const RKDeltaFieldIntegral &, double );
  friend RKDeltaFieldIntegral
  RK::CalcDeltaFieldIntegral( const RKTrajectoryPoint &,
			      const RKFieldIntegral & );
  friend bool
  RK::CheckCrossing( int, const RKTrajectoryPoint &,
		     const RKTrajectoryPoint &, RKcalcHitPoint & );
};

//______________________________________________________________________________
class RKcalcHitPoint
{
public:
  RKcalcHitPoint( void ){}
  RKcalcHitPoint( const ThreeVector &pos, const ThreeVector &mom,
                  double S, double L,
                  double Dsdx,  double Dsdy,  double Dsdu,  double Dsdv,  double Dsdq,
                  double Dsdxx, double Dsdxy, double Dsdxu, double Dsdxv, double Dsdxq,
                  double Dsdyx, double Dsdyy, double Dsdyu, double Dsdyv, double Dsdyq,
                  double Dsdux, double Dsduy, double Dsduu, double Dsduv, double Dsduq,
                  double Dsdvx, double Dsdvy, double Dsdvu, double Dsdvv, double Dsdvq,
                  double Dsdqx, double Dsdqy, double Dsdqu, double Dsdqv, double Dsdqq,
                  double Dxdx,  double Dxdy,  double Dxdu,  double Dxdv,  double Dxdq,
                  double Dydx,  double Dydy,  double Dydu,  double Dydv,  double Dydq,
                  double Dudx,  double Dudy,  double Dudu,  double Dudv,  double Dudq,
                  double Dvdx,  double Dvdy,  double Dvdu,  double Dvdv,  double Dvdq )
    : posG(pos), momG(mom), s(S), l(L),
      dsdx(Dsdx),   dsdy(Dsdy),   dsdu(Dsdu),   dsdv(Dsdv),   dsdq(Dsdq),
      dsdxx(Dsdxx), dsdxy(Dsdxy), dsdxu(Dsdxu), dsdxv(Dsdxv), dsdxq(Dsdxq),
      dsdyx(Dsdyx), dsdyy(Dsdyy), dsdyu(Dsdyu), dsdyv(Dsdyv), dsdyq(Dsdyq),
      dsdux(Dsdux), dsduy(Dsduy), dsduu(Dsduu), dsduv(Dsduv), dsduq(Dsduq),
      dsdvx(Dsdvx), dsdvy(Dsdvy), dsdvu(Dsdvu), dsdvv(Dsdvv), dsdvq(Dsdvq),
      dsdqx(Dsdqx), dsdqy(Dsdqy), dsdqu(Dsdqu), dsdqv(Dsdqv), dsdqq(Dsdqq),
      dxdx(Dxdx),   dxdy(Dxdy),   dxdu(Dxdu),   dxdv(Dxdv),   dxdq(Dxdq),
      dydx(Dydx),   dydy(Dydy),   dydu(Dydu),   dydv(Dydv),   dydq(Dydq),
      dudx(Dudx),   dudy(Dudy),   dudu(Dudu),   dudv(Dudv),   dudq(Dudq),
      dvdx(Dvdx),   dvdy(Dvdy),   dvdu(Dvdu),   dvdv(Dvdv),   dvdq(Dvdq)
  {}

private:
  ThreeVector posG, momG;
  double s; // local X
  double l;
  double dsdx,  dsdy,  dsdu,  dsdv,  dsdq;
  double dsdxx, dsdxy, dsdxu, dsdxv, dsdxq;
  double dsdyx, dsdyy, dsdyu, dsdyv, dsdyq;
  double dsdux, dsduy, dsduu, dsduv, dsduq;
  double dsdvx, dsdvy, dsdvu, dsdvv, dsdvq;
  double dsdqx, dsdqy, dsdqu, dsdqv, dsdqq;
  double dxdx,  dxdy,  dxdu,  dxdv,  dxdq;
  double dydx,  dydy,  dydu,  dydv,  dydq;
  double dudx,  dudy,  dudu,  dudv,  dudq;
  double dvdx,  dvdy,  dvdu,  dvdv,  dvdq;

public:
  const ThreeVector& PositionInGlobal( void ) const { return posG; }
  const ThreeVector& MomentumInGlobal( void ) const { return momG; }
  double PositionInLocal( void ) const { return s; }
  double PathLength( void ) const { return l; }
  double coefX( void ) const { return dsdx; }
  double coefY( void ) const { return dsdy; }
  double coefU( void ) const { return dsdu; }
  double coefV( void ) const { return dsdv; }
  double coefQ( void ) const { return dsdq; }
  double coefXX( void ) const { return dsdxx; }
  double coefXY( void ) const { return dsdxy; }
  double coefXU( void ) const { return dsdxu; }
  double coefXV( void ) const { return dsdxv; }
  double coefXQ( void ) const { return dsdxq; }
  double coefYX( void ) const { return dsdyx; }
  double coefYY( void ) const { return dsdyy; }
  double coefYU( void ) const { return dsdyu; }
  double coefYV( void ) const { return dsdyv; }
  double coefYQ( void ) const { return dsdyq; }
  double coefUX( void ) const { return dsdux; }
  double coefUY( void ) const { return dsduy; }
  double coefUU( void ) const { return dsduu; }
  double coefUV( void ) const { return dsduv; }
  double coefUQ( void ) const { return dsduq; }
  double coefVX( void ) const { return dsdvx; }
  double coefVY( void ) const { return dsdvy; }
  double coefVU( void ) const { return dsdvu; }
  double coefVV( void ) const { return dsdvv; }
  double coefVQ( void ) const { return dsdvq; }
  double coefQX( void ) const { return dsdqx; }
  double coefQY( void ) const { return dsdqy; }
  double coefQU( void ) const { return dsdqu; }
  double coefQV( void ) const { return dsdqv; }
  double coefQQ( void ) const { return dsdqq; }

  double dXdX( void ) const { return dxdx; }
  double dXdY( void ) const { return dxdy; }
  double dXdU( void ) const { return dxdu; }
  double dXdV( void ) const { return dxdv; }
  double dXdQ( void ) const { return dxdq; }
  double dYdX( void ) const { return dydx; }
  double dYdY( void ) const { return dydy; }
  double dYdU( void ) const { return dydu; }
  double dYdV( void ) const { return dydv; }
  double dYdQ( void ) const { return dydq; }
  double dUdX( void ) const { return dudx; }
  double dUdY( void ) const { return dudy; }
  double dUdU( void ) const { return dudu; }
  double dUdV( void ) const { return dudv; }
  double dUdQ( void ) const { return dudq; }
  double dVdX( void ) const { return dvdx; }
  double dVdY( void ) const { return dvdy; }
  double dVdU( void ) const { return dvdu; }
  double dVdV( void ) const { return dvdv; }
  double dVdQ( void ) const { return dvdq; }

  friend bool
  RK::CheckCrossing( int, const RKTrajectoryPoint &,
		     const RKTrajectoryPoint &, RKcalcHitPoint & );
};

//______________________________________________________________________________
class RKTrajectoryPoint
{
public:
  RKTrajectoryPoint( double X, double Y, double Z,
                     double U, double V, double Q,
                     double Dxdx, double Dxdy, double Dxdu,
                     double Dxdv, double Dxdq,
                     double Dydx, double Dydy, double Dydu,
                     double Dydv, double Dydq,
                     double Dudx, double Dudy, double Dudu,
                     double Dudv, double Dudq,
                     double Dvdx, double Dvdy, double Dvdu,
                     double Dvdv, double Dvdq,
                     double L )
    : r(X,Y,Z,U,V,Q),
      dxdx(Dxdx), dxdy(Dxdy), dxdu(Dxdu), dxdv(Dxdv), dxdq(Dxdq),
      dydx(Dydx), dydy(Dydy), dydu(Dydu), dydv(Dydv), dydq(Dydq),
      dudx(Dudx), dudy(Dudy), dudu(Dudu), dudv(Dudv), dudq(Dudq),
      dvdx(Dvdx), dvdy(Dvdy), dvdu(Dvdu), dvdv(Dvdv), dvdq(Dvdq),
      l(L)
  {}

  RKTrajectoryPoint( const RKCordParameter &R,
                     double Dxdx, double Dxdy, double Dxdu,
                     double Dxdv, double Dxdq,
                     double Dydx, double Dydy, double Dydu,
                     double Dydv, double Dydq,
                     double Dudx, double Dudy, double Dudu,
                     double Dudv, double Dudq,
                     double Dvdx, double Dvdy, double Dvdu,
                     double Dvdv, double Dvdq,
                     double L )
    : r(R),
      dxdx(Dxdx), dxdy(Dxdy), dxdu(Dxdu), dxdv(Dxdv), dxdq(Dxdq),
      dydx(Dydx), dydy(Dydy), dydu(Dydu), dydv(Dydv), dydq(Dydq),
      dudx(Dudx), dudy(Dudy), dudu(Dudu), dudv(Dudv), dudq(Dudq),
      dvdx(Dvdx), dvdy(Dvdy), dvdu(Dvdu), dvdv(Dvdv), dvdq(Dvdq),
      l(L)
  {}

  RKTrajectoryPoint( const ThreeVector &pos,
                     double U, double V, double Q,
                     double Dxdx, double Dxdy, double Dxdu,
                     double Dxdv, double Dxdq,
                     double Dydx, double Dydy, double Dydu,
                     double Dydv, double Dydq,
                     double Dudx, double Dudy, double Dudu,
                     double Dudv, double Dudq,
                     double Dvdx, double Dvdy, double Dvdu,
                     double Dvdv, double Dvdq,
                     double L )
    : r(pos,U,V,Q),
      dxdx(Dxdx), dxdy(Dxdy), dxdu(Dxdu), dxdv(Dxdv), dxdq(Dxdq),
      dydx(Dydx), dydy(Dydy), dydu(Dydu), dydv(Dydv), dydq(Dydq),
      dudx(Dudx), dudy(Dudy), dudu(Dudu), dudv(Dudv), dudq(Dudq),
      dvdx(Dvdx), dvdy(Dvdy), dvdu(Dvdu), dvdv(Dvdv), dvdq(Dvdq),
      l(L)
  {}

  RKTrajectoryPoint( const ThreeVector &pos,
                     const ThreeVector &mom,
                     double Dxdx, double Dxdy, double Dxdu,
                     double Dxdv, double Dxdq,
                     double Dydx, double Dydy, double Dydu,
                     double Dydv, double Dydq,
                     double Dudx, double Dudy, double Dudu,
                     double Dudv, double Dudq,
                     double Dvdx, double Dvdy, double Dvdu,
                     double Dvdv, double Dvdq,
                     double L )
    : r(pos,mom),
      dxdx(Dxdx), dxdy(Dxdy), dxdu(Dxdu), dxdv(Dxdv), dxdq(Dxdq),
      dydx(Dydx), dydy(Dydy), dydu(Dydu), dydv(Dydv), dydq(Dydq),
      dudx(Dudx), dudy(Dudy), dudu(Dudu), dudv(Dudv), dudq(Dudq),
      dvdx(Dvdx), dvdy(Dvdy), dvdu(Dvdu), dvdv(Dvdv), dvdq(Dvdq),
      l(L)
  {}

  RKTrajectoryPoint( const RKcalcHitPoint& hp )
    : r( hp.PositionInGlobal(), hp.MomentumInGlobal() ),
      dxdx( hp.dXdX() ), dxdy( hp.dXdY() ),
      dxdu( hp.dXdU() ), dxdv( hp.dXdV() ), dxdq( hp.dXdQ() ),
      dydx( hp.dYdX() ), dydy( hp.dYdY() ),
      dydu( hp.dYdU() ), dydv( hp.dYdV() ), dydq( hp.dYdQ() ),
      dudx( hp.dUdX() ), dudy( hp.dUdY() ),
      dudu( hp.dUdU() ), dudv( hp.dUdV() ), dudq( hp.dUdQ() ),
      dvdx( hp.dVdX() ), dvdy( hp.dVdY() ),
      dvdu( hp.dVdU() ), dvdv( hp.dVdV() ), dvdq( hp.dVdQ() ),
      l( hp.PathLength() )
  {}

private:
  RKCordParameter r;
  double dxdx, dxdy, dxdu, dxdv, dxdq;
  double dydx, dydy, dydu, dydv, dydq;
  double dudx, dudy, dudu, dudv, dudq;
  double dvdx, dvdy, dvdu, dvdv, dvdq;
  double l;

public:
  ThreeVector PositionInGlobal( void ) const { return r.PositionInGlobal(); }
  ThreeVector MomentumInGlobal( void ) const { return r.MomentumInGlobal(); }
  double      PathLength( void )         const { return l; }
  void        Print( std::ostream &ost ) const;

  friend RKTrajectoryPoint
  RK::TraceOneStep( double, const RKTrajectoryPoint & );
  friend bool
  RK::CheckCrossing( int, const RKTrajectoryPoint &,
		     const RKTrajectoryPoint &, RKcalcHitPoint & );
  friend RKDeltaFieldIntegral
  RK::CalcDeltaFieldIntegral( const RKTrajectoryPoint &,
			      const RKFieldIntegral &,
			      const RKDeltaFieldIntegral &,
			      const RKDeltaFieldIntegral &, double );
  friend RKDeltaFieldIntegral
  RK::CalcDeltaFieldIntegral( const RKTrajectoryPoint &,
			      const RKFieldIntegral & );
};

//______________________________________________________________________________
class RKHitPointContainer
  : public std::vector< std::pair<int,RKcalcHitPoint> >
{
public:
  const RKcalcHitPoint & HitPointOfLayer( int lnum ) const;
  RKcalcHitPoint & HitPointOfLayer( int lnum );

  typedef std::vector<std::pair<int,RKcalcHitPoint> >
  ::const_iterator RKHpCIterator;

  typedef std::vector<std::pair<int,RKcalcHitPoint> >
  ::iterator RKHpIterator;

};

//______________________________________________________________________________
inline std::ostream&
operator <<( std::ostream &ost, const RKFieldIntegral &obj )
{
  obj.Print( ost );
  return ost;
}

//______________________________________________________________________________
inline std::ostream&
operator <<( std::ostream &ost, const RKDeltaFieldIntegral &obj )
{
  obj.Print( ost );
  return ost;
}

//______________________________________________________________________________
inline std::ostream&
operator <<( std::ostream &ost, const RKCordParameter &obj )
{
  obj.Print( ost );
  return ost;
}

//______________________________________________________________________________
inline std::ostream&
operator <<( std::ostream &ost, const RKTrajectoryPoint &obj )
{
  obj.Print( ost );
  return ost;
}

#endif
