/**
 *  file: DebugTimer.hh
 *  date: 2017.04.10
 *
 */

#include "DebugTimer.hh"

#include <ctime>
#include <iomanip>
#include <iostream>

#include <std_ostream.hh>

namespace debug
{
  //______________________________________________________________________________
  Timer::Timer( const std::string& msg, bool verbose )
    : m_start(new ::timespec),
      m_stop(0),
      m_cstart(),
      m_cstop(),
      m_msg(msg),
      m_verbose(verbose)
  {
    ::clock_gettime(CLOCK_REALTIME, m_start);
    const std::time_t& start = std::time(0);
    m_cstart = std::ctime(&start);
  }

  //______________________________________________________________________________
  Timer::~Timer( void )
  {
    if (!m_stop){
      stop();
      if( m_verbose )
	print_verbose();
      else
	print();
    }

    delete m_stop;  m_stop = 0;
    delete m_start; m_start = 0;
  }

  //______________________________________________________________________________
  double
  Timer::sec( void ) const
  {
    if ( m_start && m_stop )
      return m_stop->tv_sec - m_start->tv_sec;
    else
      return 0.;
  }

  //______________________________________________________________________________
  double
  Timer::nsec( void ) const
  {
    if ( m_start && m_stop )
      return m_stop->tv_nsec - m_start->tv_nsec;
    else
      return 0.;
  }

  //______________________________________________________________________________
  void
  Timer::print( const std::string& arg, std::ostream& ost ) const
  {
    const double sec  = m_stop->tv_sec  - m_start->tv_sec;
    const double nsec = m_stop->tv_nsec - m_start->tv_nsec;
    ost << "#DTimer " << m_msg << " " << arg << std::endl
	<< "        " << std::setw(10) << (sec*.1e9 + nsec) << " nsec ("
	<< (sec + nsec*1.e-9) << " sec)" << std::endl;
  }

  //______________________________________________________________________________
  void
  Timer::print_verbose( const std::string& arg, std::ostream& ost ) const
  {
    const std::clock_t& time = m_stop->tv_sec - m_start->tv_sec;
    ost << "#DTimer " << m_msg << " " << arg << std::endl
	<< "   Process Start   : " << m_cstart
	<< "   Process Stop    : " << m_cstop
	<< "   Processing Time : " << time/3600 << ":"
	<< std::setfill('0') << std::setw(2) << std::right
	<< (time/60)%60 << ":"
	<< std::setfill('0') << std::setw(2) << std::right
	<< time%60 << std::endl;

    return;
  }

  //______________________________________________________________________________
  void
  Timer::stop( void )
  {
    m_stop = new ::timespec;
    ::clock_gettime(CLOCK_REALTIME, m_stop);
    const std::time_t& stop = std::time(0);
    m_cstop = std::ctime(&stop);
    return;
  }

}
