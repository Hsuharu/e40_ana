/**
 *  file: MatrixMaker.hh
 *  date: 2017.04.10
 *
 */

#ifndef MATRIX_MAKER_HH
#define MATRIX_MAKER_HH

#include <cmath>

//______________________________________________________________________________
double q10[6] = { 0.002726, 0.0007644, -2.119E-7, 4.418E-10, -3.141E-13, 6.316E-17 };
double q11[6] = { 0.002226, 0.0007601, -2.329E-7, 4.964E-10, -3.7E-13,   7.839E-17 };
double q12[6] = { 0.0025,   0.0007636, -2.209E-7, 4.877E-10, -3.719E-13, 7.984E-17 };
double q13[6] = { 0.002755, 0.0007593, -2.202E-7, 4.917E-10, -3.744E-13, 8.024E-17 };

//______________________________________________________________________________
inline double
func( double current, double *p )
{
  double mag_field =
    p[0] + p[1]*std::pow(current,1) + p[2]*std::pow(current,2) + p[3]*std::pow(current,3)
    + p[4]*std::pow(current,4) + p[5]*std::pow(current,5);
  return mag_field;
}

//______________________________________________________________________________
inline double
funcQ10( double current )
{
  return func(current, q10);
}

//______________________________________________________________________________
inline double
funcQ11( double current )
{
  return func(current, q11);
}

//______________________________________________________________________________
inline double
funcQ12( double current )
{
  return func(current, q12);
}

//______________________________________________________________________________
inline double
funcQ13( double current )
{
  return func(current, q13);
}

//______________________________________________________________________________
void
MakeOrbitFile( double *mag, double magfield_d4 );

#endif
