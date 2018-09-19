/**
 *  file: MstParamMan.cc
 *  date: 2017.04.10
 *
 */

#include "MsTParamMan.hh"

#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <stdexcept>

#include <std_ostream.hh>

#include "ConfMan.hh"
#include "DetectorID.hh"

namespace
{
  const std::string& class_name("MsTParamMan");
  const int NumOfSegDetA = NumOfSegTOF;
  const int NumOfSegDetB = NumOfSegSCH;
}

//______________________________________________________________________________
MsTParamMan::MsTParamMan( void )
  : m_is_ready(false),
    m_nA(NumOfSegDetA),
    m_nB(NumOfSegDetB)
{
  m_low_threshold.resize( NumOfSegDetA );
  m_high_threshold.resize( NumOfSegDetA );
  for( int i=0; i<NumOfSegDetA; ++i ){
    m_low_threshold[i].resize( NumOfSegDetB );
    m_high_threshold[i].resize( NumOfSegDetB );
  }
}

//______________________________________________________________________________
MsTParamMan::~MsTParamMan( void )
{
}

//______________________________________________________________________________
double
MsTParamMan::GetLowThreshold( std::size_t detA, std::size_t detB ) const
{
  if( detA<0 || m_nA<=detA ) return false;
  if( detB<0 || m_nB<=detB ) return false;
  return m_low_threshold[detA][detB];
}

//______________________________________________________________________________
double
MsTParamMan::GetHighThreshold( std::size_t detA, std::size_t detB ) const
{
  if( detA<0 || m_nA<=detA ) return false;
  if( detB<0 || m_nB<=detB ) return false;
  return m_high_threshold[detA][detB];
}

//______________________________________________________________________________
bool
MsTParamMan::Initialize( const std::string& filename )
{
  static const std::string func_name("["+class_name+"::"+__func__+"()]");

  {
    std::ifstream ifs( filename.c_str() );
    if( !ifs.is_open() ){
      hddaq::cerr << "#E " << func_name << " "
		<< "No such parameter file : " << filename << std::endl;
      std::exit( EXIT_FAILURE );
    }

    std::string line;
    int tofseg = 0;
    int LorH   = 0;
    while( !ifs.eof() && std::getline( ifs, line ) ){
      if( line.empty() ) continue;

      std::string param[NumOfSegDetB];
      std::istringstream iss( line );

      for( int i=0; i<NumOfSegDetB; ++i ){
	iss >> param[i];
      }
      if( param[0].at(0) == '#' ) continue;
      if( param[1] == "Mem_Thr_Low" ){
	tofseg =  0;
	LorH   = -1;
	continue;
      }
      if( param[1] == "Mem_Thr_Hi" ){
	tofseg =  0;
	LorH   =  1;
	continue;
      }

      if( param[NumOfSegDetB-1].empty() ) continue;
      for( int i=0; i<NumOfSegDetB; ++i ){
	std::replace( param[i].begin(), param[i].end(), '(', ' ');
	std::replace( param[i].begin(), param[i].end(), ')', ' ');
	std::replace( param[i].begin(), param[i].end(), ',', ' ');
	if( LorH == -1 )
	  m_low_threshold[tofseg][i] = std::strtol( param[i].c_str(), NULL, 0 );
	if( LorH ==  1 )
	  m_high_threshold[tofseg][i] = std::strtol( param[i].c_str(), NULL, 0 );
      }
      ++tofseg;
    }

#if 0
    // Low
    hddaq::cout << "Low Threshold" << std::endl;
    for( int i=0; i<NumOfSegDetA; ++i ){
      hddaq::cout << i << "\t:";
      for( int j=0; j<NumOfSegDetB; ++j ){
	hddaq::cout << " " << m_low_threshold[i][j];
      }
      hddaq::cout << std::endl;
    }
    // High
    hddaq::cout << "High Threshold" << std::endl;
    for( int i=0; i<NumOfSegDetA; ++i ){
      hddaq::cout << i << "\t:";
      for( int j=0; j<NumOfSegDetB; ++j ){
	hddaq::cout << " " << m_high_threshold[i][j];
      }
      hddaq::cout << std::endl;
    }
#endif
  }

  m_is_ready = true;
  return true;
}

//______________________________________________________________________________
bool
MsTParamMan::IsAccept( std::size_t detA, std::size_t detB, int tdc ) const
{
  static const std::string func_name("["+class_name+"::"+__func__+"()]");

  if( !m_is_ready ){
    throw std::runtime_error(func_name+" "+ClassName()+" is not initialized");
    // return false;
  }
  if( m_nA<=detA || m_nB<=detB ){
    std::ostringstream oss;
    oss << " detA/detB is out of range : "
	<< std::setw(2) << detA << " "
	<< std::setw(2) << detB;
    throw std::out_of_range(func_name+oss.str());
    // return false;
  }

  int low  = (int)m_low_threshold[detA][detB];
  int high = (int)m_high_threshold[detA][detB];
  return ( low < tdc && tdc < high );
}

//______________________________________________________________________________
void
MsTParamMan::Print( const std::string& arg ) const
{
  static const std::string func_name("["+class_name+"::"+__func__+"()]");

  hddaq::cout << "#D " << func_name << " " << arg << std::endl;

  for( std::size_t iA=0; iA<m_nA; ++iA ){
    hddaq::cout << std::setw(2) << iA << ": ";
    int iBok = 0;
    for( std::size_t iB=0; iB<m_nB; ++iB ){
      // ofs << iA << "\t" << iB << "\t"
      // 	  << m_low_threshold[iA][iB] << "\t"
      // 	  << m_high_threshold[iA][iB] << std::endl;
      if( m_low_threshold[iA][iB]==0 &&
	  m_high_threshold[iA][iB]==0 )
	continue;


      iBok++;
      hddaq::cout << std::setw(2) << iB << " "
		  << std::setw(4) << m_low_threshold[iA][iB] << " "
		  << std::setw(4) << m_high_threshold[iA][iB] << "  ";
      if( iBok%5==0 ){
	hddaq::cout << std::endl << "    ";
      }
    }
    hddaq::cout << std::endl;
  }
}

//______________________________________________________________________________
void
MsTParamMan::Print( std::size_t detA, std::size_t detB, int tdc ) const
{
  static const std::string func_name("["+class_name+"::"+__func__+"()]");

  if( detA<0 || m_nA<=detA ) return;
  if( detB<0 || m_nB<=detB ) return;

  hddaq::cout << " detA " << std::setw(2) << detA
	      << " detB " << std::setw(2) << detB
	      << " : " << IsAccept( detA, detB, tdc ) << std::endl;

}
