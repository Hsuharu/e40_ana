/**
 *  file: PrintHelper.hh
 *  date: 2017.04.10
 *
 */

#ifndef PRINT_HELPER_HH
#define PRINT_HELPER_HH

#include <iomanip>
#include <iostream>
#include <string>

#include <std_ostream.hh>

//______________________________________________________________________________
class PrintHelper
{
public:
  PrintHelper( std::size_t precision,
	       std::ios::fmtflags flags,
	       std::ostream& ost=hddaq::cout )
    : m_ostream(ost),
      m_precision(ost.precision()),
      m_flags(ost.flags())
  {
    m_ostream.precision(precision);
    m_ostream.setf(flags);
  }
  ~PrintHelper( void )
  {
    m_ostream.precision(m_precision);
    m_ostream.setf(m_flags);
  }

private:
  std::ostream&      m_ostream;
  std::size_t        m_precision;
  std::ios::fmtflags m_flags;

public:
  void precision( std::size_t precision );
  void setf( std::ios::fmtflags flags );
  void set( std::size_t precision, std::ios::fmtflags flags );

};

//______________________________________________________________________________
inline void
PrintHelper::precision( std::size_t precision )
{
  m_ostream.precision(precision);
}

//______________________________________________________________________________
inline void
PrintHelper::setf( std::ios::fmtflags flags )
{
  m_ostream.setf(flags);
}

//______________________________________________________________________________
inline void
PrintHelper::set( std::size_t precision, std::ios::fmtflags flags )
{
  m_ostream.precision(precision);
  m_ostream.setf(flags);
}

#endif
