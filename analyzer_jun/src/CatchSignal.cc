/**
 *  file: CatchSignal.cc
 *  date: 2017.04.10
 *
 */

#include "CatchSignal.hh"

#include <csignal>

#include <Unpacker.hh>
#include <UnpackerManager.hh>
#include <escape_sequence.hh>
#include <std_ostream.hh>

namespace CatchSignal
{
  namespace
  {
    using namespace hddaq::unpacker;
    const std::string& name("CatchSignal");
    const UnpackerManager& gUnpacker = GUnpacker::get_instance();

    bool user_stop = false;
  }

  //______________________________________________________________________________
  bool
  Stop( void )
  {
    return user_stop;
  }

  //______________________________________________________________________________
  void
  Catch( int sig )
  {
    static const std::string func_name("["+name+"::"+__func__+"()]");
    std::signal( SIGINT, SIG_IGN );
    user_stop = true;
    if ( gUnpacker.get_root()->is_esc_on() )
      hddaq::cout << esc::k_yellow
		  << "#D " << func_name << " exit process by signal " << sig
		  << esc::k_default_color << std::endl;
    else
      hddaq::cout << "#D " << func_name << " exit process by signal " << sig
		  << std::endl;
  }

  //______________________________________________________________________________
  void
  Set( int sig )
  {
    std::signal( sig, Catch );
  }
}
