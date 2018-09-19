/**
 *  file: HodoRawHit.cc
 *  date: 2017.04.10
 *
 */

#include "HodoRawHit.hh"

#include <iterator>

#include "DebugCounter.hh"

namespace
{
  const std::string class_name("HodoRawHit");
}

//______________________________________________________________________________
HodoRawHit::HodoRawHit( int detector_id, int plane_id, int segment_id )
  : m_detector_id(detector_id),
    m_plane_id(plane_id),
    m_segment_id(segment_id),
    m_adc1(1, -1), m_adc2(1, -1),
    m_tdc1(1, -1), m_tdc2(1, -1),
    m_tdc_t1(1, -1), m_tdc_t2(1, -1),
    m_oftdc( false ), m_nhtdc(0)
{
  debug::ObjectCounter::increase(class_name);
}

//______________________________________________________________________________
HodoRawHit::~HodoRawHit( void )
{
  debug::ObjectCounter::decrease(class_name);
}

//______________________________________________________________________________
void
HodoRawHit::SetAdc1( int adc )
{
  if(-1 == m_adc1.at(0))
    m_adc1.at(0) = adc;
  else
    m_adc1.push_back(adc);
}

//______________________________________________________________________________
void
HodoRawHit::SetAdc2( int adc )
{
  if(-1 == m_adc2.at(0))
    m_adc2.at(0) = adc;
  else
    m_adc2.push_back(adc);
}

//______________________________________________________________________________
void
HodoRawHit::SetTdc1( int tdc )
{
  if(-1 == m_tdc1.at(0)){
    m_tdc1.at(0) = tdc;
    ++m_nhtdc;
  }else{
    m_tdc1.push_back(tdc);
  }
}

//______________________________________________________________________________
void
HodoRawHit::SetTdc2( int tdc )
{
  if(-1 == m_tdc2.at(0)){
    m_tdc2.at(0) = tdc;
    ++m_nhtdc;
  }else{
    m_tdc2.push_back(tdc);
  }
}

//______________________________________________________________________________
void
HodoRawHit::SetTdcT1( int tdc )
{
  if(-1 == m_tdc_t1.at(0)){
    m_tdc_t1.at(0) = tdc;
  }else{
    m_tdc_t1.push_back(tdc);
  }
}

//______________________________________________________________________________
void
HodoRawHit::SetTdcT2( int tdc )
{
  if(-1 == m_tdc_t2.at(0)){
    m_tdc_t2.at(0) = tdc;
  }else{
    m_tdc_t2.push_back(tdc);
  }
}

//______________________________________________________________________________
int
HodoRawHit::SizeAdc1( void ) const
{
  if(-1 == m_adc1.at(0))
    return 0;
  else
    return m_adc1.size();
}

//______________________________________________________________________________
int
HodoRawHit::SizeAdc2( void ) const
{
  if(-1 == m_adc2.at(0))
    return 0;
  else
    return m_adc2.size();
}

//______________________________________________________________________________
int
HodoRawHit::SizeTdc1( void ) const
{
  if(-1 == m_tdc1.at(0))
    return 0;
  else
    return m_tdc1.size();
}

//______________________________________________________________________________
int
HodoRawHit::SizeTdc2( void ) const
{
  if(-1 == m_tdc2.at(0))
    return 0;
  else
    return m_tdc2.size();
}

//______________________________________________________________________________
int
HodoRawHit::SizeTdcT1( void ) const
{
  if(-1 == m_tdc_t1.at(0))
    return 0;
  else
    return m_tdc_t1.size();
}

//______________________________________________________________________________
int
HodoRawHit::SizeTdcT2( void ) const
{
  if(-1 == m_tdc_t2.at(0))
    return 0;
  else
    return m_tdc_t2.size();
}

//______________________________________________________________________________
void
HodoRawHit::Clear( void )
{
  m_nhtdc = 0;
  m_adc1.clear();
  m_adc2.clear();
  m_tdc1.clear();
  m_tdc2.clear();
  m_tdc_t1.clear();
  m_tdc_t2.clear();
  m_adc1.push_back(-1);
  m_adc2.push_back(-1);
  m_tdc1.push_back(-1);
  m_tdc2.push_back(-1);
  m_tdc_t1.push_back(-1);
  m_tdc_t2.push_back(-1);
}

//______________________________________________________________________________
void
HodoRawHit::Print( const std::string& arg )
{
  static const std::string func_name("["+class_name+"::"+__func__+"()]");
  hddaq::cerr << func_name << " " << arg << std::endl
	      << "detector_id = " << m_detector_id << std::endl
	      << "plane_id    = " << m_plane_id    << std::endl
	      << "segment_id  = " << m_segment_id   << std::endl;

  std::vector<int>::const_iterator itr, end;
  hddaq::cout << "adc1        = " << m_adc1.size() << " ";
  std::copy( m_adc1.begin(), m_adc1.end(),
	     std::ostream_iterator<int>(hddaq::cout," ") );
  hddaq::cout << std::endl
	      << "adc2        = " << m_adc2.size() << " ";
  std::copy( m_adc2.begin(), m_adc2.end(),
	     std::ostream_iterator<int>(hddaq::cout," ") );
  hddaq::cout << std::endl
	      << "tdc1        = " << m_tdc1.size() << " ";
  std::copy( m_tdc1.begin(), m_tdc1.end(),
	     std::ostream_iterator<int>(hddaq::cout," ") );
  hddaq::cout << std::endl
	      << "tdc2        = " << m_tdc2.size() << " ";
  std::copy( m_tdc2.begin(), m_tdc2.end(),
	     std::ostream_iterator<int>(hddaq::cout," ") );
  hddaq::cout << std::endl
	      << "tdc_t1      = " << m_tdc_t1.size() << " ";
  std::copy( m_tdc_t1.begin(), m_tdc_t1.end(),
	     std::ostream_iterator<int>(hddaq::cout," ") );
  hddaq::cout << std::endl
	      << "tdc_t2      = " << m_tdc_t2.size() << " ";
  std::copy( m_tdc2.begin(), m_tdc2.end(),
	     std::ostream_iterator<int>(hddaq::cout," ") );
  hddaq::cout << std::endl;
}
