/**
 *  file: DCRawHit.cc
 *  date: 2017.04.10
 *
 */

#include "DCRawHit.hh"

#include <iostream>
#include <iterator>

#include "std_ostream.hh"

#include "DebugCounter.hh"

namespace
{
  const std::string& class_name("DCRawHit");
}

//______________________________________________________________________________
DCRawHit::DCRawHit( int plane_id, int wire_id )
  : m_plane_id(plane_id),
    m_wire_id(wire_id),
    m_oftdc( false )
{
  m_tdc.clear();
  m_trailing.clear();
  debug::ObjectCounter::increase(class_name);
}

//______________________________________________________________________________
DCRawHit::~DCRawHit( void )
{
  debug::ObjectCounter::decrease(class_name);
}

//______________________________________________________________________________
void
DCRawHit::Print( const std::string& arg ) const
{
  static const std::string func_name("["+class_name+"::"+__func__+"()]");
  hddaq::cerr << func_name << " " << arg << std::endl
	      << "plane_id = " << m_plane_id    << std::endl
	      << "wire_id  = " << m_wire_id     << std::endl;

  std::vector<int>::const_iterator itr, end;
  hddaq::cout << "tdc      = " << m_tdc.size() << " ";
  std::copy( m_tdc.begin(), m_tdc.end(),
	     std::ostream_iterator<int>(hddaq::cout," ") );
  hddaq::cout << std::endl
	      << "trailing = " << m_trailing.size() << " ";
  std::copy( m_trailing.begin(), m_trailing.end(),
	     std::ostream_iterator<int>(hddaq::cout," ") );
  hddaq::cout << std::endl;
}
