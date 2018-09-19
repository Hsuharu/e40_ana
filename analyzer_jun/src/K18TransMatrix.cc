/**
 *  file: K18TransMatrix.cc
 *  date: 2017.04.10
 *
 */

#include "K18TransMatrix.hh"

#include <cmath>
#include <cstdlib>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <sstream>
#include <vector>

#include <lexical_cast.hh>
#include <std_ostream.hh>

#include "MathTools.hh"

namespace
{
  const std::string& class_name("K18TransMatrix");
  const double MMtoM = 1.E-3;
  const double MtoMM = 1000.;
}

//______________________________________________________________________________
K18TransMatrix::K18TransMatrix( void )
  : m_is_ready(false),
    m_file_name("")
{
}

//______________________________________________________________________________
K18TransMatrix::~K18TransMatrix( void )
{
}

//______________________________________________________________________________
bool
K18TransMatrix::Initialize( void )
{
  static const std::string func_name("["+class_name+"::"+__func__+"()]");

  std::vector< std::vector<double> > parameters;
  parameters.resize(4);

  std::ifstream file( m_file_name.c_str() );

  if( !file.is_open() ){
    hddaq::cerr << "#E " << func_name
		<< " cannot open file : " << m_file_name << std::endl;
    std::exit(EXIT_FAILURE);
  }

  while( file.good() ){
    std::string buf;
    std::getline(file,buf);

    std::istringstream is(buf);
    std::istream_iterator<std::string> begin(is);
    std::istream_iterator<std::string> end;
    std::vector<std::string> param( begin, end );

    if( param.empty() || param[0].empty() ) continue;

    std::size_t n = param.size();

    if(param[0]=="X" && param[1]!="A"){
      for( std::size_t i=1; i<n; ++i ){
	double p = hddaq::a2d(param[i]);
	parameters[0].push_back(p);
      }
    }
    if(param[0]=="A"){
      for(std::size_t i=1;i<n;++i){
	double p = hddaq::a2d(param[i]);
	parameters[1].push_back(p);
      }
    }
    if(param[0]=="Y" && param[1]!="B"){
      for(std::size_t i=1;i<n;++i){
	double p = hddaq::a2d(param[i]);
	parameters[2].push_back(p);
      }
    }
    if(param[0]=="B"){
      for(std::size_t i=1;i<n;++i){
	double p = hddaq::a2d(param[i]);
	parameters[3].push_back(p);
      }
    }
  }//while( file.good() )

  file.close();

  std::size_t n0 = parameters[0].size();
  std::size_t n1 = parameters[1].size();
  std::size_t n2 = parameters[2].size();
  std::size_t n3 = parameters[3].size();

  for( std::size_t i=0; i<n0; ++i ) m_X[i] = parameters[0][i];
  for( std::size_t i=0; i<n1; ++i ) m_U[i] = parameters[1][i];
  for( std::size_t i=0; i<n2; ++i ) m_Y[i] = parameters[2][i];
  for( std::size_t i=0; i<n3; ++i ) m_V[i] = parameters[3][i];

#ifdef DEBUG
  for( std::size_t i=0; i<n0; ++i ) hddaq::cout << m_X[i] << " ";
  hddaq::cout << std::endl;
  for( std::size_t i=0; i<n1; ++i ) hddaq::cout << m_U[i] << " ";
  hddaq::cout << std::endl;
  for( std::size_t i=0; i<n2; ++i ) hddaq::cout << m_Y[i] << " ";
  hddaq::cout << std::endl;
  for( std::size_t i=0; i<n3; ++i ) hddaq::cout << m_V[i] << " ";
  hddaq::cout << std::endl;
#endif

  m_is_ready = true;
  return true;
}

//______________________________________________________________________________
bool
K18TransMatrix::Initialize( const std::string& file_name )
{
  m_file_name = file_name;
  return Initialize();
}

//______________________________________________________________________________
bool
K18TransMatrix::Transport( double xin, double yin,
			   double uin, double vin, double delta,
			   double& xout, double& yout,
			   double& uout, double& vout ) const
{
  static const std::string func_name("["+class_name+"::"+__func__+"()]");

  xin *= -MMtoM;
  yin *= -MMtoM;
  uin  = -uin;
  vin  = -vin;
  xout = 0.;
  yout = 0.;
  uout = 0.;
  vout = 0.;

  double bj1[31], bj2[8];
  bj1[ 0] = xin;
  bj1[ 1] = uin;
  bj1[ 2] = delta;
  bj1[ 3] = xin*xin;
  bj1[ 4] = xin*uin;
  bj1[ 5] = xin*delta;
  bj1[ 6] = uin*uin;
  bj1[ 7] = uin*delta;
  bj1[ 8] = delta*delta;
  bj1[ 9] = yin*yin;
  bj1[10] = yin*vin;
  bj1[11] = vin*vin;
  bj1[12] = xin*xin*xin;
  bj1[13] = xin*xin*uin;
  bj1[14] = xin*xin*delta;
  bj1[15] = xin*uin*uin;
  bj1[16] = xin*uin*delta;
  bj1[17] = xin*delta*delta;
  bj1[18] = xin*yin*yin;
  bj1[19] = xin*yin*vin;
  bj1[20] = xin*vin*vin;
  bj1[21] = uin*uin*uin;
  bj1[22] = uin*uin*delta;
  bj1[23] = uin*delta*delta;
  bj1[24] = uin*yin*yin;
  bj1[25] = uin*yin*vin;
  bj1[26] = uin*vin*vin;
  bj1[27] = delta*delta*delta;
  bj1[28] = delta*yin*yin;
  bj1[29] = delta*yin*vin;
  bj1[30] = delta*vin*vin;

  bj2[ 0] = yin;
  bj2[ 1] = vin;
  bj2[ 2] = yin*xin;
  bj2[ 3] = yin*uin;
  bj2[ 4] = yin*delta;
  bj2[ 5] = vin*xin;
  bj2[ 6] = vin*uin;
  bj2[ 7] = vin*delta;

  for( int i=0; i<31; ++i ){
    xout += m_X[i]*bj1[i];
    uout += m_U[i]*bj1[i];
  }

  for( int i=0; i<8; ++i ){
    yout += m_Y[i]*bj2[i];
    vout += m_V[i]*bj2[i];
  }

  xout *= -MtoMM; yout *= -MtoMM; uout = -uout; vout = -vout;
  return true;
}

//______________________________________________________________________________
bool
K18TransMatrix::CalcDeltaD2U( double xin, double yin,
			      double uin, double vin,
			      double xout, double& yout,
			      double& uout, double& vout,
			      double& delta1, double& delta2 ) const
{
  static const std::string func_name("["+class_name+"::"+__func__+"()]");

  xin  *= MMtoM;
  yin  *= MMtoM;
  uin   = uin;
  vin   = vin;
  xout *= MMtoM;

  // use untill 2nd order
  double A_, B_, C_, D_;
  A_ = m_X[8];
  B_ = m_X[2]+m_X[5]*xin+m_X[7]*uin;
  C_ = m_X[0]*xin+m_X[1]*uin+m_X[3]*xin*xin+m_X[4]*xin*uin+m_X[6]*uin*uin
    + m_X[9]*yin*yin+m_X[10]*yin*vin+m_X[11]*vin*vin -xout;

  D_ = B_*B_-4.*A_*C_;
  if (D_<0) {
    hddaq::cerr << "#E " << func_name
		<< " negative Hanbetu-shiki" << std::endl;
    return false;
  }

  double ans1;//, ans2;

  ans1 = (-B_+std::sqrt(D_))/(2.*A_);
  // ans2 = (-B_-std::sqrt(D_))/(2.*A_);

  delta1 = ans1;

  /*
    Calc cubic equation

    a*x^3 + b*x^2 + c^x + d = 0;
    ==>
    x^3 + alpha*x^2 + beta*x + gamma = 0;
    { alpha = b/a;  beta = c/a;  gamma = d/a; }

    x = y - alpha/3;
    ==>
    y^3 + py + q = 0; -- (eq 1)
    { p = (-alpha^2)/3 + beta;  q = (2*alpha^3)/27 - (alpha*beta)/3 + gamma}

    general solution of the equation below are,
    X^3 -3*u*v*X -(u^3 + v^3) = 0;
    X =
    u + v         -- (1);
    w*u + (w^2)*v -- (2);
    (w^2)*u + w*v -- (3);
    { w is a solution of X^3 = 1},  w = (-1 + std::sqrt(3)*i)/2;}

    then,
    p = -3uv;  q = -(u^3 + v^3);

    u^3 = -q/2 + std::sqrt(q^2/4 + p^3/27)
    v^3 = -q/2 - std::sqrt(q^2/4 + p^3/27)

    D = -((q/2)^2 + (p/3)^3);
    D > 0 => 3 real number;
    D < 0 => 1 real number, 2 complex number;
    D = 0 => 2 real equal root;

    if(D > 0) (in this case, p < 0)
    y = r*cos(t) (r > 0, 0 < t <pi);
    (r^3)*cos^3(t) +p*cos(t) +q = 0;
    To use 4*cos^3(t) -3*cos(t) = cos(3t), r should be,
    r = std::sqrt(-4*p/3);
    then, cos(3t) = 3q/(rp);
    since 0 < t < pi, 0 < (1/3.)*arccos(3q/(rp)) < pi/3;
    therefore, these are real number solutions of (eq 1)
    y =
    r*cos(t), r*cos(t + 2pi/3), r*cos(t - 2pi/3);
    (t = (1/3.)*arccos(3q/(rp)), x = y -alpha/3, r = std::sqrt(-4p/3));

    if(D < 0)
    this is a unique real number solution of (eq 1)
    y = cbrt(-q/2 + std::sqrt(-D)) + cbrt(-q/2 - std::sqrt(-D)); (x = y - alpha/3);
  */
  {
    double alpha, beta, gamma;
    double x, a, y, b;
    x = xin; a = uin; y = yin; b = vin;
    alpha = m_X[TT] + m_X[XTT]*x + m_X[ATT]*a;
    beta  = m_X[T] + m_X[XT]*x + m_X[AT]*a + m_X[XXT]*x*x + m_X[XAT]*x*a
      + m_X[AAT]*a*a + m_X[TYY]*y*y + m_X[TYB]*y*b + m_X[TBB]*b*b;
    gamma = m_X[X]*x + m_X[A]*a + m_X[XX]*x*x + m_X[XA]*x*a + m_X[AA]*a*a
      + m_X[YY]*y*y + m_X[YB]*y*b + m_X[BB]*b*b + m_X[XXX]*x*x*x
      + m_X[XXA]*x*x*a + m_X[XAA]*x*a*a + m_X[XYY]*x*y*y + m_X[XYB]*x*y*b
      + m_X[XBB]*x*b*b + m_X[AAA]*a*a*a + m_X[AYY]*a*y*y + m_X[AYB]*a*y*b
      + m_X[ABB]*a*b*b - xout;

    alpha = alpha/m_X[TTT];
    beta  = beta/m_X[TTT];
    gamma = gamma/m_X[TTT];

    double p, q;
    p = -(alpha*alpha)/3 + beta;
    q = (2*alpha*alpha*alpha)/27 - (alpha*beta)/3 + gamma;

    double hanbetu = -((q/2)*(q/2) + (p/3)*(p/3)*(p/3));
    if(hanbetu > 0){
      double r = std::sqrt(-4*p/3);
      double s1, s2, s3;
      double theta = (1/3.)*std::acos(3*q/(r*p));
      s1 = r*cos(theta) -alpha/3;
      s2 = r*cos(theta + 2*math::Pi()/3.) -alpha/3;
      s3 = r*cos(theta - 2*math::Pi()/3.) -alpha/3;

      double tmpans = s1;
      if( std::abs(tmpans-ans1)>std::abs(s2-ans1) ){
	tmpans = s2;
      }
      if( std::abs(tmpans-ans1)>std::abs(s3-ans1) ){
	tmpans = s3;
      }
      delta2 = tmpans;
      //      hddaq::cout << "ans1 " << ans1 << std::endl;
      //      hddaq::cout << delta2 << std::endl;
    }else{
      double s1;
      s1 = cbrt(-q/2 + std::sqrt(-hanbetu)) + cbrt(-q/2 - std::sqrt(-hanbetu))
	-alpha/3;
      delta2 = s1;
      //      hddaq::cout << "ans1 " << ans1 << std::endl;
      //      hddaq::cout << delta2 << std::endl;
    }

    // Calc u0, v0, y0 at BFT position.
    double d = delta2;

    // u0
    double Au, Bu, Cu, Du;
    Au = m_U[TTT];
    Bu = m_U[TT] + m_U[XTT]*x + m_U[ATT]*a;
    Cu = m_U[T] + m_U[XT]*x + m_U[AT]*a + m_U[XXT]*x*x + m_U[XAT]*x*a
      + m_U[AAT]*a*a + m_U[TYY]*y*y + m_U[TYB]*y*b + m_U[TBB]*b*b;
    Du = m_U[X]*x + m_U[A]*a + m_U[XX]*x*x + m_U[XA]*x*a + m_U[AA]*a*a
      + m_U[YY]*y*y + m_U[YB]*y*b + m_U[BB]*b*b + m_U[XXX]*x*x*x
      + m_U[XXA]*x*x*a + m_U[XAA]*x*a*a + m_U[XYY]*x*y*y + m_U[XYB]*x*y*b
      + m_U[XBB]*x*b*b + m_U[AAA]*a*a*a + m_U[AYY]*a*y*y + m_U[AYB]*a*y*b
      + m_U[ABB]*a*b*b;

    double u0 = Au*d*d*d + Bu*d*d + Cu*d +Du;

    // v0
    double Av, Bv;
    Av = m_V[YT]*y + m_V[BT]*b;
    Bv = m_V[Y]*y + m_V[B]*b + m_V[YX]*y*x + m_V[YA]*y*a + m_V[BX]*b*x + m_V[BA]*b*a;

    double v0 = Av*d + Bv;

    // y0
    double Ay, By;
    Ay = m_Y[YT]*y + m_Y[BT]*b;
    By = m_Y[Y]*y + m_Y[B]*b + m_Y[YX]*y*x + m_Y[YA]*y*a + m_Y[BX]*b*x + m_Y[BA]*b*a;

    double y0 = Ay*d + By;
    y0 *= MtoMM;

    yout = y0;
    uout = u0;
    vout = v0;

  }

  return true;
}

