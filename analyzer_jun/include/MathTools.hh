/**
 *  file: MathTools.hh
 *  date: 2017.04.10
 *
 */

#ifndef MATH_TOOLS_HH
#define MATH_TOOLS_HH

#include <TMath.h>

#include "ThreeVector.hh"

//______________________________________________________________________________
namespace math
{
  //______________________________________________________________________________
  inline double Rad2Deg( void ){ return TMath::RadToDeg(); }
  inline double Deg2Rad( void ){ return TMath::DegToRad(); }
  inline double Rad2Deg( double rad ){ return rad*Rad2Deg(); }
  inline double Deg2Rad( double deg ){ return deg*Deg2Rad(); }

  //______________________________________________________________________________
  inline double nan( void ) { return TMath::QuietNaN(); }
  inline double Infinity( void ) { return TMath::Infinity(); }
  inline double Epsilon( void ) { return TMath::Limits<double>::Epsilon(); }
  inline int    Round( double a ) { return int(a+0.5-(a<0.)); }

  //______________________________________________________________________________
  template <typename T>
  inline T Sign( T a ) { return (a>0) - (a<0); }

  template <typename Container>
  inline double Accumulate( const Container& c )
  {
    double sum = 0.;
    typename Container::const_iterator itr, end=c.end();
    for( itr=c.begin(); itr!=end; ++itr ){
      sum += *itr;
    }
    return sum;
  }

  template <typename Container>
  inline double Average( const Container& c )
  {
    return Accumulate(c)/c.size();
  }

  template <typename Container>
  inline double Deviation( const Container& c )
  {
    double sum  = 0.;
    double sum2 = 0.;
    typename Container::const_iterator itr, end=c.end();
    for( itr=c.begin(); itr!=end; ++itr ){
      sum  += *itr;
      sum2 += (*itr) * (*itr);
    }
    std::size_t n = c.size();
    return std::sqrt( ( sum2-(sum*sum/n) ) / n );
  }

  template <typename Container>
  inline double MaxElement( const Container& c )
  {
    return *std::max_element(c.begin(), c.end());
  }

  template <typename Container>
  inline double MinElement( const Container& c )
  {
    return *std::min_element(c.begin(), c.end());
  }

  //______________________________________________________________________________
  // compare l and r
  template <typename T>
  inline bool Equal( const T& l, const T& r );

  // 3.14159265358979323846
  inline double Pi( void ) { return TMath::Pi(); }
  // velocity of light : 299.792458 mm ns^-1
  inline double C( void ) { return TMath::C()*1e-6; }
  // base of natural log
  inline double E( void ) { return TMath::E(); }

  bool SolveGaussJordan( const std::vector<double>& z,
			 const std::vector<double>& w,
			 const std::vector<double>& s,
			 const std::vector<double>& ct,
			 const std::vector<double>& st,
			 double& x0,
			 double& u0,
			 double& y0,
			 double& v0 );

  bool GaussElim( double **a, int n, double *b, int *indx, int *ipiv );
  bool GaussJordan( double **a, int n, double *b,
		    int *indxc, int *indxd, int *ipiv );
  bool InterpolateRatio( int n, const double *xa, const double *ya,
			 double *w1, double *w2,
			 double x, double &y, double &dy );
  bool InterpolatePol( int n, const double *xa, const double *ya,
		       double *w1, double *w2,
		       double x, double &y, double &dy );
  bool SVDksb( double **u, const double *w, double **v,
	       int m, int n, const double *b, double *x, double *wv );
  bool SVDcmp( double **a, int m, int n, double *w, double **v, double *wv );
  template <typename T>
  void PrintMatrix( T *mat, const std::string& arg="",
		    const int column=4, const int line=4 );
  template <typename T>
  void PrintVector( T *vec, const std::string& arg="",
		    const std::size_t size=4 );
}

//______________________________________________________________________________
template <typename T>
inline bool
math::Equal( const T& l, const T& r )
{
  double al = std::abs(l), ar = std::abs(r);
  return
    ( ( al <= Epsilon() ) || ( ar <= Epsilon() ) )
    ?
    ( std::abs(l-r) <= Epsilon() )
    :
    ( ( std::abs(l-r)/std::max( al, ar ) ) <= Epsilon() );
}


#endif
