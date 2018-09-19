/**
 *  file: DatabasePDG.cc
 *  date: 2017.04.10
 *  note: PDG code is defined in ROOT/include/TPDGCode.h
 *        Mass unit [GeV/c2]
 *
 */

#include "DatabasePDG.hh"

#include <string>

#include <TDatabasePDG.h>
#include <TParticlePDG.h>

#include <iostream>

namespace
{
  const std::string& name("DatabasePDG");
}

//______________________________________________________________________________
namespace pdg
{
  //______________________________________________________________________________
  double
  Mass( int pdg_code )
  {
    TParticlePDG *particle = TDatabasePDG::Instance()->GetParticle(pdg_code);
    return ( particle ? particle->Mass() : -1. );
  }

  //______________________________________________________________________________
  double
  KaonMass( void )
  {
    return Mass(kKMinus);
  }

  //______________________________________________________________________________
  double
  PionMass( void )
  {
    return Mass(kPiMinus);
  }

  //______________________________________________________________________________
  double
  ProtonMass( void )
  {
    return Mass(kProton);
  }

  //______________________________________________________________________________
  double
  NeutronMass( void )
  {
    return Mass(kNeutron);
  }

  //______________________________________________________________________________
  double
  LambdaMass( void )
  {
    return Mass(kLambda0);
  }

  //______________________________________________________________________________
  double
  SigmaNMass( void )
  {
    return Mass(kSigmaMinus);
  }

  //______________________________________________________________________________
  double
  SigmaPMass( void )
  {
    return Mass(kSigmaPlus);
  }

  //______________________________________________________________________________
  double
  XiMass( void )
  {
    return Mass(kXiMinus);
  }

  //______________________________________________________________________________
  void
  Print( int pdg_code )
  {
    TParticlePDG *particle = TDatabasePDG::Instance()->GetParticle(pdg_code);
    if( particle ) particle->Print();
  }

  //______________________________________________________________________________
  void
  Print( void )
  {
    TDatabasePDG::Instance()->Print();
  }

}
