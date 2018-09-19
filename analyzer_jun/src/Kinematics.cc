/**
 *  file: Kinematics.cc
 *  date: 2017.04.10
 *
 */

#include "Kinematics.hh"

#include <cmath>
#include <cstdio>

#include <std_ostream.hh>

#include "MathTools.hh"

namespace
{
  const std::string& name("Kinematics");
  const double z_offset      = 0.0;
  const double TARGETcenter  = 0.0;//Z position
  const double TARGEThw      = 15.0/2.0;
  const double TARGETsizeX   = 25.0/2.0;
  const double TARGETsizeY   = 15.0/2.0;
  const double TARGETsizeZ   = 15.0/2.0;
  const double TARGETradius  = 67.3/2.0;
  const double TARGETcenterX = 0.0;
  const double TARGETcenterY = 0.0;
}

//______________________________________________________________________________
namespace Kinematics
{
  //______________________________________________________________________________
  double
  MassSquare( double p, double path, double time )
  {
    if( time<0 ) return -9999.;
    double beta = path/time/math::C();
    return p*p*(1.-beta*beta)/beta/beta;
  }

  //______________________________________________________________________________
  double
  CalcTimeOfFlight( double p, double path, double mass )
  {
    return path*sqrt(mass*mass+p*p)/p/math::C();
  }

  //______________________________________________________________________________
  ThreeVector
  VertexPoint( const ThreeVector & Xin, const ThreeVector & Xout,
	       const ThreeVector & Pin, const ThreeVector & Pout )
  {
    static const std::string func_name("["+name+"::"+__func__+"()]");
    double xi=Xin.x(), yi=Xin.y(), xo=Xout.x(), yo=Xout.y();
    double ui=Pin.x()/Pin.z(), vi=Pin.y()/Pin.z();
    double uo=Pout.x()/Pout.z(), vo=Pout.y()/Pout.z();

    double z=((xi-xo)*(uo-ui)+(yi-yo)*(vo-vi))/
      ((uo-ui)*(uo-ui)+(vo-vi)*(vo-vi));
    double x1=xi+ui*z, y1=yi+vi*z;
    double x2=xo+uo*z, y2=yo+vo*z;
    double x = 0.5*(x1+x2);
    double y = 0.5*(y1+y2);
    if( std::isnan(x) || std::isnan(y) || std::isnan(z) )
      return ThreeVector( -9999., -9999., -9999. );

    return ThreeVector( x, y, z+z_offset );

  }

  //______________________________________________________________________________
  ThreeVector
  VertexPointByHonly( const ThreeVector & Xin,
		      const ThreeVector & Xout,
		      const ThreeVector & Pin,
		      const ThreeVector & Pout )
  {
    static const std::string func_name("["+name+"::"+__func__+"()]");
    double xi=Xin.x(), yi=Xin.y(), xo=Xout.x();//, yo=Xout.y();
    double ui=Pin.x()/Pin.z(), vi=Pin.y()/Pin.z();
    double uo=Pout.x()/Pout.z();//, vo=Pout.y()/Pout.z();

    double z=(xi-xo)/(uo-ui);
    return ThreeVector( xi+ui*z, yi+vi*z, z+z_offset );
  }

  //______________________________________________________________________________
  ThreeVector
  VertexPoint( const ThreeVector & Xin, const ThreeVector & Xout,
	       const ThreeVector & Pin, const ThreeVector & Pout,
	       double & dist )
  {
    static const std::string func_name("["+name+"::"+__func__+"()]");
    double xi=Xin.x(), yi=Xin.y(), xo=Xout.x(), yo=Xout.y();
    double ui=Pin.x()/Pin.z(), vi=Pin.y()/Pin.z();
    double uo=Pout.x()/Pout.z(), vo=Pout.y()/Pout.z();

    double z=((xi-xo)*(uo-ui)+(yi-yo)*(vo-vi))/
      ((uo-ui)*(uo-ui)+(vo-vi)*(vo-vi));
    double x1=xi+ui*z, y1=yi+vi*z;
    double x2=xo+uo*z, y2=yo+vo*z;
    dist=sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));

    return ThreeVector( 0.5*(x1+x2), 0.5*(y1+y2), z+z_offset );
  }

  //______________________________________________________________________________
  ThreeVector
  VertexPointReal( const ThreeVector & Xin, const ThreeVector & Xout,
		   const ThreeVector & Pin, const ThreeVector & Pout,
		   double & dist )
  {
    static const std::string func_name("["+name+"::"+__func__+"()]");
    double a1_2  = Pin.Mag()*Pin.Mag();
    double a2_2  = Pout.Mag()*Pout.Mag();
    double a1a2  = Pin.Dot(Pout);
    double bunbo = a1_2*a2_2 -a1a2*a1a2;
    ThreeVector b1_b2;
    b1_b2 = (Xin - Xout);

    double t[2];
    t[0] = (b1_b2.Dot(Pout)*a1a2 - b1_b2.Dot(Pin)*a2_2)
      /bunbo;
    t[1] = (b1_b2.Dot(Pout)*a1_2 - b1_b2.Dot(Pin)*a1a2)
      /bunbo;

    ThreeVector tempVector[2];
    tempVector[0] = t[0]*Pin + Xin;
    tempVector[1] = t[1]*Pout + Xout;

    double vertex[3];
    vertex[0] = (tempVector[0].X() + tempVector[1].X())/2.;
    vertex[1] = (tempVector[0].Y() + tempVector[1].Y())/2.;
    vertex[2] = (tempVector[0].Z() + tempVector[1].Z())/2.;

    ThreeVector DistanceVector;
    DistanceVector  = tempVector[0] - tempVector[1];
    dist = DistanceVector.Mag();

    return ThreeVector( vertex[0], vertex[1], vertex[2] );
  }

  //______________________________________________________________________________
  double
  closeDist( const ThreeVector & Xin, const ThreeVector & Xout,
	     const ThreeVector & Pin, const ThreeVector & Pout )
  {
    static const std::string func_name("["+name+"::"+__func__+"()]");
    double xi=Xin.x(), yi=Xin.y(), xo=Xout.x(), yo=Xout.y();
    double ui=Pin.x()/Pin.z(), vi=Pin.y()/Pin.z();
    double uo=Pout.x()/Pout.z(), vo=Pout.y()/Pout.z();

    double z=((xi-xo)*(uo-ui)+(yi-yo)*(vo-vi))/
      ((uo-ui)*(uo-ui)+(vo-vi)*(vo-vi));
    double x1=xi+ui*z, y1=yi+vi*z;
    double x2=xo+uo*z, y2=yo+vo*z;

    return sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));
  }

  //______________________________________________________________________________
  ThreeVector
  CorrElossIn( const ThreeVector & Pin, const ThreeVector & Xin,
	       const ThreeVector & vtx, double mass )
  {
    static const std::string func_name("["+name+"::"+__func__+"()]");
    double length = 0.;//, dE;
    double mom_new, energy_new;

    ThreeVector CorPin = Pin;
    double mom = Pin.Mag();

    mom_new = mom;
    energy_new = sqrt(mass*mass+mom*mom);

    if ( std::abs(vtx.z()-TARGETcenter) <= TARGETsizeZ )
      length = calcLengthBeam(Pin, Xin, vtx);
    else if ( vtx.z() > TARGETsizeZ+TARGETcenter ){
      double u=Pin.x()/Pin.z();
      double v=Pin.y()/Pin.z();
      double ztgtOut=TARGETcenter+TARGETsizeZ;
      ThreeVector tgtOutPos(u*(ztgtOut)+Xin.x(), v*(ztgtOut)+Xin.y(), ztgtOut);
      length = calcLengthBeam(Pin, Xin, tgtOutPos);
    }
    else if ( vtx.z() < -TARGETsizeZ+TARGETcenter )
      return CorPin;

    if ( caldE(mom, mass, length, &mom_new, &energy_new) ) {
      CorPin = mom_new/mom*Pin;
      // hddaq::cout << "CorrElossIn:: mom = " << mom << ", mom_new = " << mom_new
      // 	      << std::endl;
      return CorPin;
    } else {
      return Pin;
    }
  }

  //______________________________________________________________________________
  double
  calcLengthBeam( const ThreeVector & Pin, const ThreeVector & Xin,
		  const ThreeVector & vtx )
  {
    static const std::string func_name("["+name+"::"+__func__+"()]");
    double u=Pin.x()/Pin.z();
    double v=Pin.y()/Pin.z();

    // hddaq::cout << "calcLengthBeam:: vtx (x,y,z)=(" << vtx.x() << ", "
    // 	    << vtx.y() << ", " << vtx.z() << ")" << std::endl;

    ThreeVector point1, point2;
    /* vertex point check */
    if ( IsInsideTarget(vtx) )
      point1=vtx;
    else {
      double z1,z2;
      double z;
      if ( calcCrossingPoint(u, v, vtx, &z1, &z2) ) {
	if ( std::abs(vtx.z()-z1)<std::abs(vtx.z()-z2) )
	  z=z1;
	else
	  z=z2;

	point1 = ThreeVector(u*(z-vtx.z())+vtx.x(), v*(z-vtx.z())+vtx.y(), z);
      } else {
	return 0.0;
      }
    }
    // hddaq::cout << "calcLengthBeam:: Point1 (x,y,z)=(" << point1.x() << ", "
    // 	    << point1.y() << ", " << point1.z() << ")" << std::endl;
    /* target entrance point check */
    double ztgtIn=TARGETcenter-TARGETsizeZ;

    ThreeVector tgtInPos( u*(ztgtIn)+Xin.x(), v*(ztgtIn)+Xin.y(), ztgtIn );
    if ( IsInsideTarget(tgtInPos) )
      point2=tgtInPos;
    else {
      double z1,z2;
      double z;
      if (calcCrossingPoint(u, v, tgtInPos, &z1, &z2)) {
	if (std::abs(tgtInPos.z()-z1)<std::abs(tgtInPos.z()-z2))
	  z=z1;
	else
	  z=z2;

	point2 = ThreeVector(u*(z)+Xin.x(), v*(z)+Xin.y(), z);
      } else {
	return 0.0;
      }
    }

    // hddaq::cout << "calcLengthBeam:: Point2 (x,y,z)=(" << point2.x() << ", "
    // 	    << point2.y() << ", " << point2.z() << ")" << std::endl;
    // hddaq::cout << "calcLengthBeam:: length=" << (point1-point2).Mag() << std::endl;

    return (point1-point2).Mag();
  }

  /*
    Correct Energy loss (Downstream part of Vertex)
  */
  //______________________________________________________________________________
  ThreeVector
  CorrElossOut( const ThreeVector & Pout, const ThreeVector & Xout,
		const ThreeVector & vtx, double mass )
  {
    static const std::string func_name("["+name+"::"+__func__+"()]");
    double FL,FH,FTMP;
    double Elow, Ehigh, Elast, EPS;
    double E = 0., length = 0.;

    ThreeVector CorPout = Pout;
    double mom = Pout.Mag();

    if ( std::abs( vtx.z()-TARGETcenter ) < TARGETsizeZ )
      length =  calcLengthScat(Pout, Xout, vtx);
    else if ( vtx.z() < -TARGETsizeZ-TARGETcenter ){
      double u=Pout.x()/Pout.z();
      double v=Pout.y()/Pout.z();
      double ztgtIn=TARGETcenter-TARGETsizeZ;
      ThreeVector tgtInPos(u*(ztgtIn)+Xout.x(), v*(ztgtIn)+Xout.y(), ztgtIn);
      length = calcLengthScat(Pout, Xout, tgtInPos);
    }
    else if ( vtx.z() > TARGETsizeZ+TARGETcenter )
      return CorPout;

    Elow  = mass;
    Ehigh = 10.;
    Elast = sqrt(mass*mass+mom*mom);
    EPS = 0.001;
    FL  = diffE(mass, Elow, length, Elast);
    FH  = diffE(mass, Ehigh, length, Elast);
    while ( std::abs( (Ehigh-Elow)/Ehigh ) > EPS ) {
      E = Ehigh-(Ehigh-Elow)*FH/(FH-FL);
      //printf("-------E=%f, Elow=%f, Ehigh=%f, FL=%f, FH=%f----------\n",E, Elow, Ehigh, FL, FH);
      if (std::abs(FTMP=diffE(mass, E, length, Elast)) < 0.0000001){
	Elow = E;
	Ehigh = E;
	FH = FTMP;
      } if ((FTMP=diffE(mass, E, length, Elast)) < 0) {
	Elow = E;
	FL = FTMP;
      } else if ((FTMP=diffE(mass, E, length, Elast)) > 0){
	Ehigh = E;
	FH = FTMP;
      }
    }

    double energy_new = E;
    double mom_new = sqrt(energy_new*energy_new-mass*mass);

    CorPout = mom_new/mom*Pout;
    // hddaq::cout << "CorrElossOut:: mom = " << mom << ", mom_new = " << mom_new
    // 	    << std::endl;

    return CorPout;
  }

  //______________________________________________________________________________
  double
  calcLengthScat( const ThreeVector & Pout, const ThreeVector & Xout,
		  const ThreeVector & vtx )
  {
    static const std::string func_name("["+name+"::"+__func__+"()]");
    double u=Pout.x()/Pout.z();
    double v=Pout.y()/Pout.z();

    // hddaq::cout << "calcLengthScat:: vtx (x,y,z)=(" << vtx.x() << ", "
    // 	    << vtx.y() << ", " << vtx.z() << ")" << std::endl;

    ThreeVector point1, point2;
    /* vertex point check */
    if (IsInsideTarget(vtx))
      point1=vtx;
    else {
      double z1,z2;
      double z;
      if (calcCrossingPoint(u, v, vtx, &z1, &z2)) {
	if (std::abs(vtx.z()-z1)<std::abs(vtx.z()-z2))
	  z=z1;
	else
	  z=z2;

	point1 = ThreeVector(u*(z-vtx.z())+vtx.x(), v*(z-vtx.z())+vtx.y(), z);
      } else {
	return 0.0;
      }
    }
    // hddaq::cout << "calcLengthScat:: Point1 (x,y,z)=(" << point1.x() << ", "
    // 	    << point1.y() << ", " << point1.z() << ")" << std::endl;

    /* target exit point check */
    double ztgtOut=TARGETcenter+TARGETsizeZ;

    ThreeVector tgtOutPos(u*(ztgtOut)+Xout.x(), v*(ztgtOut)+Xout.y(), ztgtOut);
    if ( IsInsideTarget(tgtOutPos) )
      point2=tgtOutPos;
    else {
      double z1,z2;
      double z;
      if (calcCrossingPoint(u, v, tgtOutPos, &z1, &z2)) {
	if (std::abs(tgtOutPos.z()-z1)<std::abs(tgtOutPos.z()-z2))
	  z=z1;
	else
	  z=z2;

	point2 = ThreeVector(u*(z)+Xout.x(), v*(z)+Xout.y(), z);
      } else {
	return 0.0;
      }
    }

    // hddaq::cout << "calcLengthScat:: Point2 (x,y,z)=(" << point2.x() << ", "
    // 	    << point2.y() << ", " << point2.z() << ")" << std::endl;
    // hddaq::cout << "calcLengthScata:: length=" << (point1-point2).Mag() << std::endl;

    return (point1-point2).Mag();

  }

  //______________________________________________________________________________
  ThreeVector
  CorrElossOutCheck( const ThreeVector & Pout, const ThreeVector & Xout,
		     const ThreeVector & vtx, double mass )
  {
    static const std::string func_name("["+name+"::"+__func__+"()]");
    double length = 0.;//, dE;
    double energy_new, mom_new;

    double mom=Pout.Mag();

    mom_new = mom;
    energy_new = sqrt(mass*mass+mom*mom);

    ThreeVector CorPout = Pout;

    if ( std::abs( vtx.z()-TARGETcenter ) <= TARGETsizeZ )
      length =  calcLengthBeam(Pout, Xout, vtx);
    else if ( vtx.z() < -TARGETsizeZ+TARGETcenter ){
      double u=Pout.x()/Pout.z();
      double v=Pout.y()/Pout.z();
      double ztgtIn=TARGETcenter-TARGETsizeZ;
      ThreeVector tgtInPos(u*(ztgtIn)+Xout.x(), v*(ztgtIn)+Xout.y(), ztgtIn);
      length = calcLengthBeam(Pout, Xout, tgtInPos);
    }
    else if ( vtx.z() > TARGETsizeZ+TARGETcenter )
      return CorPout;

    if (caldE(mom, mass, length, &mom_new, &energy_new)) {
      CorPout = mom_new/mom*Pout;
      return CorPout;
    } else {
      return Pout;
    }
  }

  //______________________________________________________________________________
  bool
  IsInsideTarget( const ThreeVector &point )
  {
    static const std::string func_name("["+name+"::"+__func__+"()]");
#if 1
    return ( ( std::abs( point.x() - TARGETcenterX ) < TARGETsizeX ) &&
	     ( std::abs( point.y() - TARGETcenterY ) < TARGETsizeY ) );
#else
    return ( pow( ( point.x()-TARGETcenterX ), 2. ) +
	     pow( ( point.y()-TARGETcenterY ), 2. ) <=
	     pow( TARGETradius, 2. ) );
#endif
    return false;
  }

  //______________________________________________________________________________
  bool
  calcCrossingPoint( double u, double v, ThreeVector Point,
		     double *z1, double *z2 )
  {
    static const std::string func_name("["+name+"::"+__func__+"()]");
    double x0=TARGETcenterX, y0=TARGETcenterY;
    double a=Point.x()-u*Point.z()-x0;
    double b=Point.y()-v*Point.z()-y0;
    double r=TARGETradius;

    double c=(a*u+b*v)*(a*u+b*v)-(u*u+v*v)*(a*a+b*b-r*r);

    if (c<0) {
      // hddaq::cerr << "#W " << func_name << " "
      // 	      << "this track does not cross target" << std::endl;
      return false;
    } else {
      // hddaq::cout << "#D " << func_name << " "
      // 	      << "this track cross target!" << std::endl;
      *z1 = (-(a*u+b*v)+sqrt(c))/(u*u+v*v);
      *z2 = (-(a*u+b*v)-sqrt(c))/(u*u+v*v);
      return true;
    }
  }

  //______________________________________________________________________________
  double
  diffE( double mass, double E, double length, double Elast )
  {
    static const std::string func_name("["+name+"::"+__func__+"()]");
    double p;
    double mom_new, energy_new;

    p = sqrt(E*E-mass*mass);

    caldE(p, mass, length, &mom_new, &energy_new);
    return (energy_new-Elast);
    //return (sqrt(mass*mass+p*p)-caldE(particle,p,length)-Elast);
  }

  //______________________________________________________________________________
  int
  caldE( double momentum, double mass, double distance,
	 double *momentum_cor, double *energy_cor )
  {
    static const std::string func_name("["+name+"::"+__func__+"()]");
    double dE_dx; /*MeV/cm*/
    double eloss; /*MeV*/

    double beta;
    double thickness = distance/10.0; /*cm*/
    double m = mass*1000.0;  /*mass of incident particle(Mev)*/

    double E_0;
    double E;
    double p = momentum*1000.0;
    //double delta=0.01; /*cm*/
    double delta=0.1; /*cm*/
    int i;
    double length=0.0;
    double total_eloss=0.0;

    //E_0=mygamma(beta)*m;
    //p=mygamma(beta)*beta*m;

    E_0= sqrt(m*m + p*p);
    E=E_0;
    beta = mybeta(E,p);
    //printf("beta=%f, E=%f, p=%f\n",beta, E, p);
    if (beta<=0.0) {
      *momentum_cor = p/1000.0;
      *energy_cor = E/1000.0;
      return 1;
    }
    dE_dx=0.0;
    eloss=0.0;
    for(i=0;i<=thickness/delta;i++){
      dE_dx=calc_dE_dx(beta);
      eloss=dE_dx*delta;
      E=E-eloss;
      if(E<m){
	fprintf(stderr,"particle stops in material at %5.3fcm\n",length);
	*momentum_cor = p/1000.0;
	*energy_cor = E/1000.0;
	return 0;
	//break;
      }
      p=sqrt(pow(E,2.0)-pow(m,2.0));
      beta=mybeta(E,p);
      length=length+delta;
      total_eloss=total_eloss+eloss;
      /*
	printf("beta:%5.3f\n",beta);
	printf("dE_dx:%5.3f\teloss:%5.3f\n",dE_dx,eloss);
	printf("E:%5.3f(MeV)\tp:%5.3f(MeV/c)\n",E,p);
	printf("length:%5.3f(cm)\n",length);
	printf("total energy loss:%5.3f(MeV)\n",total_eloss);
      */
      //getchar();
    }
    *momentum_cor = p/1000.0;
    *energy_cor = E/1000.0;

    return 1;
  }

  //______________________________________________________________________________
  double
  calc_dE_dx( double beta )
  {
    static const std::string func_name("["+name+"::"+__func__+"()]");
    double value;
    const double C=0.1535; /*MeVcm^2/g*/
    const double m_e=0.511;
    double logterm;
    double gamma_2;
    double W_max;
    double gamma;
    double X;
    double delta = 0.;

    double rho=0.0709;   /*g/cm^3 (C)*/
    double I=21.8;     /*eV*/
    double Z_A=0.99216;
    int z=1;
    double C0=-3.2632;
    double X0=0.4759;
    double X1=1.9215;
    double a=0.13483;
    double M=5.6249;

    gamma = mygamma(beta);
    X = log10(beta*gamma);
    if (X<=X0)
      delta=0.0;
    else if (X0<X && X<X1)
      delta=4.6052*X+C0+a*pow((X1-X),M);
    else if (X>=X1)
      delta=4.6052*X+C0;

    gamma_2=1/(1-pow(beta,2.0));
    //printf("sqrt(gamma_2):%f\n",sqrt(gamma_2));

    W_max=2.0*m_e*pow(beta,2.0)*gamma_2;

    logterm=log(2.0*m_e*gamma_2*pow(beta,2.0)*W_max*pow(10.0,12.0)/pow(I,2.0))-2.0*pow(beta,2.0)-delta/2.0;

    value=C*rho*Z_A*pow((double)z,2.0)*logterm/pow(beta,2.0);

    return value;

  }

  //______________________________________________________________________________
  double
  mygamma( double beta )
  {
    return 1./sqrt(1.-beta*beta);
  }

  //______________________________________________________________________________
  double
  mybeta( double energy,double mormentum )
  {
    return mormentum/energy;
  }

}
