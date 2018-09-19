/**
 *  file: DstCollection.cc
 *  date: 2017.04.10
 *
 */

#include <cmath>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>

#include <filesystem_util.hh>

#include "ConfMan.hh"
#include "RootHelper.hh"
#include "DetectorID.hh"

#include "DstHelper.hh"

namespace
{
  using namespace dst;
  const std::string& class_name("DstCollection");
}

namespace dst
{
  enum kArgc
    {
      kProcess,
      kHodoscope, kEasiroc,
      kBcOutTracking, kSdcInTracking, kSdcOutTracking,
      kK18Tracking, kKuramaTracking,
      kEMC, kHUL, kMassTrigger,
      kOutFile, nArgc
    };
  std::vector<TString> ArgName =
    { "[Process]",
      "[Hodoscope]", "[Easiroc]",
      "[BcOutTracking]", "[SdcInTracking]", "[SdcOutTracking]",
      "[K18Tracking]", "[KuramaTracking]",
      "[EMC]", "[HUL]", "[MassTrigger]",
      "[OutFile]" };
  std::vector<TString> TreeName =
    { "",
      "hodo", "ea0c",
      "bcout", "sdcin", "sdcout",
      "k18track", "kurama",
      "emc", "hul", "mst",
      "" };
  std::vector<TFile*> TFileCont;
  std::vector<TTree*> TTreeCont;
}

//_____________________________________________________________________
int
main( int argc, char **argv )
{
  std::vector<std::string> arg( argv, argv+argc );

  if( !CheckArg( arg ) )
    return EXIT_FAILURE;
  if( !DstOpen( arg ) )
    return EXIT_FAILURE;

  DstRead();

  DstClose();

  return EXIT_SUCCESS;
}

//_____________________________________________________________________
bool
dst::InitializeEvent( void )
{
  return true;
}

//_____________________________________________________________________
bool
dst::DstOpen( std::vector<std::string> arg )
{
  int open_file = 0;
  int open_tree = 0;
  for( std::size_t i=0; i<nArgc; ++i ){
    if( i==kProcess || i==kOutFile ) continue;
    open_file += OpenFile( TFileCont[i], arg[i] );
    open_tree += OpenTree( TFileCont[i], TTreeCont[i], TreeName[i] );
  }

  if( open_file!=open_tree || open_file!=nArgc-2 )
    return false;
  if( !CheckEntries( TTreeCont ) )
    return false;

  TFileCont[kOutFile] = new TFile( arg[kOutFile].c_str(), "recreate" );

  return true;
}

//_____________________________________________________________________
bool
dst::DstRead( void )
{
  static const std::string func_name("["+class_name+"::"+__func__+"()]");
  std::cout << "#D " << func_name << std::endl;

  const std::size_t n = TFileCont.size();
  for( std::size_t i=0; i<n; ++i ){
    if( TTreeCont[i] ){
      std::cout << "   Cloning Tree ... "
		<< std::setw(8) << TTreeCont[i]->GetName() << "   "
		<< std::setw(3) << TTreeCont[i]->GetNbranches()
		<< " branches" << std::endl;
      TTreeCont[i]->CloneTree( -1, "fast" );
    }
  }
  return true;
}

//_____________________________________________________________________
bool
dst::DstClose( void )
{
  TFileCont[kOutFile]->Write();
  std::cout << "#D Close : " << TFileCont[kOutFile]->GetName() << std::endl;
  TFileCont[kOutFile]->Close();

  const std::size_t n = TFileCont.size();
  for( std::size_t i=0; i<n; ++i ){
    if( TTreeCont[i] ) delete TTreeCont[i];
    if( TFileCont[i] ) delete TFileCont[i];
  }
  return true;
}

//_____________________________________________________________________
bool
ConfMan::InitializeHistograms( void )
{
  return true;
}

//_____________________________________________________________________
bool
ConfMan::InitializeParameterFiles( void )
{
  return true;
}

//_____________________________________________________________________
bool
ConfMan::FinalizeProcess( void )
{
  return true;
}
