/**
 *  file: Kinematics.hh
 *  date: 2017.04.10
 *
 */

#ifndef KINEMATICS_HH
#define KINEMATICS_HH

#include "ThreeVector.hh"

//______________________________________________________________________________
namespace Kinematics
{
  double      MassSquare( double p, double path, double time );
  double      CalcTimeOfFlight( double p, double path, double mass );
  ThreeVector VertexPoint( const ThreeVector & Xin, const ThreeVector & Xout,
			   const ThreeVector & Pin, const ThreeVector & Pout );
  ThreeVector VertexPointByHonly( const ThreeVector & Xin,
				  const ThreeVector & Xout,
				  const ThreeVector & Pin,
				  const ThreeVector & Pout );
  ThreeVector VertexPoint( const ThreeVector & Xin, const ThreeVector & Xout,
			   const ThreeVector & Pin, const ThreeVector & Pout,
			   double & dist );
  ThreeVector VertexPointReal( const ThreeVector & Xin, const ThreeVector & Xout,
			       const ThreeVector & Pin, const ThreeVector & Pout,
			       double & dist );
  double      closeDist( const ThreeVector & Xin, const ThreeVector & Xout,
			 const ThreeVector & Pin, const ThreeVector & Pout );
  ThreeVector CorrElossIn( const ThreeVector & Pin,
			   const ThreeVector & Xin,
			   const ThreeVector & vtx, double mass );
  double      calcLengthBeam( const ThreeVector & Pin,
			      const ThreeVector & Xin,
			      const ThreeVector & vtx );
  ThreeVector CorrElossOut( const ThreeVector & Pout,
			    const ThreeVector & Xout,
			    const ThreeVector & vtx, double mass );
  double      calcLengthScat( const ThreeVector & Pout,
			      const ThreeVector & Xout,
			      const ThreeVector & vtx );
  ThreeVector CorrElossOutCheck( const ThreeVector & Pout,
				 const ThreeVector & Xout,
				 const ThreeVector & vtx, double mass );
  bool        IsInsideTarget( const ThreeVector &point );
  bool        calcCrossingPoint( double u, double v, ThreeVector Point,
				 double *z1, double *z2 );
  double      diffE( double mass, double E, double length, double Elast );
  int         caldE( double momentum, double mass, double distance,
		     double *momentum_cor, double *energy_cor );
  double      calc_dE_dx( double beta );
  double      mygamma( double beta );
  double      mybeta( double energy,double mormentum );
}

#endif
