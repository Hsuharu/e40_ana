/**
 *  file: DebugCounter.cc
 *  date: 2017.04.10
 *
 */

#include "DebugCounter.hh"

#include <iomanip>
#include <iostream>
#include <iterator>
#include <map>

#include <std_ostream.hh>

namespace debug
{
  namespace
  {
    const std::string& class_name("ObjectCounter");
  }

//_____________________________________________________________________
ObjectCounter::ObjectCounter( void )
  : m_map()
{
}

//_____________________________________________________________________
ObjectCounter::~ObjectCounter( void )
{
}

//_____________________________________________________________________
void
ObjectCounter::check( const std::string& arg ) const
{
#ifdef MemoryLeak
  static const std::string func_name("["+class_name+"::"+__func__+"()]");

  bool has_leak = false;

  ObjectIter itr, end=m_map.end();
  for( itr=m_map.begin(); itr!=end; ++itr ){
    if( itr->second!=0 ) has_leak = true;
  }

  if( has_leak )
    print( arg+" "+func_name );

#endif
}

//_____________________________________________________________________
void
ObjectCounter::print( const std::string& arg ) const
{
  static const std::string func_name("["+class_name+"::"+__func__+"()]");

  hddaq::cout << "#DCounter " << func_name << " " << arg << std::endl;
  ObjectIter itr, end=m_map.end();
  for( itr=m_map.begin(); itr!=end; ++itr ){
    hddaq::cout << std::setw(20) << std::left
		<< itr->first << " : " << itr->second << std::endl;
  }
}

}
