/**
 *  file: DatabasePDG.hh
 *  date: 2017.04.10
 *
 */

#ifndef DATABASE_PDG_HH
#define DATABASE_PDG_HH

#include <TPDGCode.h>

namespace pdg
{
  // Mass [GeV/c2]
  double Mass( int pdg_code );
  double KaonMass( void );
  double PionMass( void );
  double ProtonMass( void );
  double NeutronMass( void );
  double LambdaMass( void );
  double SigmaNMass( void );
  double SigmaPMass( void );
  double XiMass( void );
  void   Print( int pdg_code );
  void   Print( void );
}

#endif
