/**
 *  file: K18Parameters.hh
 *  date: 2017.04.10
 *
 */

#ifndef K18_PARAMETERS_HH
#define K18_PARAMETERS_HH

namespace K18Parameter
{
  const double MinK18InX  = -80.;
  const double MinK18InY  = -20.;
  const double MinK18InU  =  -0.15;
  const double MinK18InV  =  -0.05;

  const double MaxK18InX  =  80.;
  const double MaxK18InY  =  20.;
  const double MaxK18InU  =   0.15;
  const double MaxK18InV  =   0.05;

  const double MinK18OutX = -80.;
  const double MinK18OutY = -50.;
  const double MinK18OutU =  -0.15;
  const double MinK18OutV =  -0.05;

  const double MaxK18OutX =  80.;
  const double MaxK18OutY =  50.;
  const double MaxK18OutU =   0.12;
  const double MaxK18OutV =   0.05;

  const double MinK18Delta = -0.20;
  const double MaxK18Delta =  0.20;
}

#endif
