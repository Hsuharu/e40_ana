/**
 *  file: Main.cc
 *  date: 2017.04.10
 *
 */

#include <ctime>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

#include <TROOT.h>
#include <TFile.h>

#include <filesystem_util.hh>
#include <std_ostream.hh>

#include "CatchSignal.hh"
#include "ConfMan.hh"
#include "DebugCounter.hh"
#include "DebugTimer.hh"
#include "DeleteUtility.hh"
#include "UnpackerManager.hh"
#include "VEvent.hh"

namespace
{
  using namespace hddaq::unpacker;
  const std::string& class_name("");
  ConfMan&              gConf     = ConfMan::GetInstance();
  debug::ObjectCounter& gCounter  = debug::ObjectCounter::GetInstance();
  UnpackerManager&      gUnpacker = GUnpacker::get_instance();
  enum EArg
    {
      kArgProcess,
      kArgConfFile,
      kArgInFile,
      kArgOutFile,
      kArgc
    };
}

TROOT theROOT("k18analyzer", "k18analyzer");

//______________________________________________________________________________
int
main( int argc, char **argv )
{
  static const std::string func_name("["+class_name+"::"+__func__+"()]");

  std::vector<std::string> arg( argv, argv + argc );
  const std::string& process = arg[kArgProcess];
  if( argc!=kArgc ){
    hddaq::cout << "#D Usage: " << hddaq::basename(process)
  		<< " [analyzer config file]"
  		<< " [data input stream]"
  		<< " [output root file]"
  		<< std::endl;
    return EXIT_SUCCESS;
  }

  debug::Timer timer(func_name+" End of Analyzer");

  const std::string& conf_file = arg[kArgConfFile];
  const std::string& in_file   = arg[kArgInFile];
  const std::string& out_file  = arg[kArgOutFile];

  hddaq::cout << "#D " << func_name
	      << " recreate root file : " << out_file << std::endl;
  new TFile( out_file.c_str(), "recreate" );

  if( !gConf.Initialize( conf_file ) || !gConf.InitializeUnpacker() )
    return EXIT_FAILURE;

  gUnpacker.set_istream( in_file );
  gUnpacker.initialize();

  CatchSignal::Set(SIGINT);

  for( ; !gUnpacker.eof() && !CatchSignal::Stop(); ++gUnpacker ){
    VEvent* event = gConf.EventAllocator();
    event->ProcessingBegin();
    event->ProcessingNormal();
    event->ProcessingEnd();
    delete event;
    gCounter.check();
  }
  gConf.Finalize();

  gFile->Write();
  gFile->Close();

  return EXIT_SUCCESS;
}
