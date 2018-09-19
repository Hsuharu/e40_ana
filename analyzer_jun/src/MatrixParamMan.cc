/**
 *  file: MatrixParamMan.cc
 *  date: 2017.04.10
 *
 */

#include <sstream>
#include <fstream>
#include <iostream>
#include <cstdlib>

#include <std_ostream.hh>

#include "MatrixParamMan.hh"
#include "ConfMan.hh"
#include "DetectorID.hh"
#include "ThreeVector.hh"

namespace
{
  const std::string& class_name("MatrixParamMan");
}

//______________________________________________________________________________
MatrixParamMan::MatrixParamMan( void )
  : m_is_ready(false),
    m_file_name_2d(""),
    m_file_name_3d("")
{
  // 2D
  m_enable_2d.resize( NumOfSegTOF );
  for( int i=0; i<NumOfSegTOF; ++i ){
    m_enable_2d[i].resize( NumOfSegSCH );
  }
  // 3D
  m_enable_3d.resize( NumOfSegTOF );
  for( int i=0; i<NumOfSegTOF; ++i ){
    m_enable_3d[i].resize( NumOfSegSCH );
    for( int j=0; j<NumOfSegSCH; ++j ){
      m_enable_3d[i][j].resize( NumOfSegSFT_Mtx );
    }
  }
}

//______________________________________________________________________________
MatrixParamMan::~MatrixParamMan( void )
{
}

//______________________________________________________________________________
bool
MatrixParamMan::Initialize( void )
{
  return Initialize( m_file_name_2d, m_file_name_3d );
}

//______________________________________________________________________________
bool
MatrixParamMan::Initialize( const std::string& filename_2d,
			    const std::string& filename_3d )
{
  static const std::string func_name("["+class_name+"::"+__func__+"()]");

  {
    std::ifstream ifs( filename_2d.c_str() );
    if( !ifs.is_open() ){
      hddaq::cerr << "#E " << func_name << " "
		  << "No such 2D parameter file : " << filename_2d << std::endl;
      std::exit( EXIT_FAILURE );
    }

    std::string line;
    int tofseg = 0;
    while( !ifs.eof() && std::getline( ifs, line ) ){
      if( line.empty() ) continue;

      std::string param[2];
      std::istringstream iss( line );
      iss >> param[0] >> param[1];

      if( param[0].at(0) == '#' ) continue;

      if( param[0].substr(2).at(0)=='0' )
	param[0] = param[0].substr(3);
      else
	param[0] = param[0].substr(2);

      int channel = std::strtol( param[0].c_str(), NULL, 0 );
      int enable  = std::strtol( param[1].substr(0,1).c_str(), NULL, 0 );

      m_enable_2d[tofseg][channel] = enable;
      if( channel==NumOfSegSCH-1 ) ++tofseg;
    }
  }

  {
    std::ifstream ifs( filename_3d.c_str() );
    if( !ifs.is_open() ){
      hddaq::cerr << "#E " << func_name << " "
		  << "No such 3D parameter file : " << filename_3d << std::endl;
      std::exit( EXIT_FAILURE );
    }

    std::string line;
    int tofseg = 0;
    while( !ifs.eof() && std::getline( ifs, line ) ){
      if( line.empty() ) continue;

      std::string param[2];
      std::istringstream iss( line );
      iss >> param[0] >> param[1];

      if( param[0].at(0) == '#' ) continue;

      if( param[0].substr(2).at(0)=='0' )
	param[0] = param[0].substr(3);
      else
	param[0] = param[0].substr(2);

      int channel = std::strtol( param[0].c_str(), NULL, 0 );
      int enable[NumOfSegSFT_Mtx] = {};
      for( int i=0; i<NumOfSegSFT_Mtx; ++i ){
	enable[i] = std::strtol( param[1].substr(i,1).c_str(), NULL, 0 );
	m_enable_3d[tofseg][channel][i] = enable[i];
      }

      if( channel==NumOfSegSCH-1 ) ++tofseg;
    }
  }

  m_is_ready = true;
  return true;
}

//______________________________________________________________________________
bool
MatrixParamMan::IsAccept( std::size_t detA, std::size_t detB ) const
{
  static const std::string func_name("["+class_name+"::"+__func__+"()]");
  if( m_enable_2d.size()<=detA ){
    hddaq::cerr << "#W " << func_name << " detA is too much : "
		<< detA << "/" << m_enable_2d.size() << std::endl;
    return false;
  }

  if( m_enable_2d[detA].size()<=detB ){
    hddaq::cerr << "#W " << func_name << " detB is too much : "
		<< detB << "/" << m_enable_2d[detA].size() << std::endl;
    return false;
  }

  return ( m_enable_2d[detA][detB] != 0. );
}

//______________________________________________________________________________
bool
MatrixParamMan::IsAccept( std::size_t detA, std::size_t detB, std::size_t detC ) const
{
  static const std::string func_name("["+class_name+"::"+__func__+"()]");

  if( m_enable_3d.size()<=detA ){
    hddaq::cerr << "#W " << func_name << " detA is too much : "
		<< detA << "/" << m_enable_3d.size() << std::endl;
    return false;
  }

  if( m_enable_3d[detA].size()<=detB ){
    hddaq::cerr << "#W " << func_name << " detB is too much : "
		<< detB << "/" << m_enable_3d[detA].size() << std::endl;
    return false;
  }

  if( m_enable_3d[detA][detB].size()<=detC ){
    hddaq::cerr << "#W " << func_name << " detC is too much : "
		<< detC << "/" << m_enable_3d[detA][detB].size() << std::endl;
    return false;
  }

  return ( m_enable_3d[detA][detB][detC] != 0. );
}

//______________________________________________________________________________
void
MatrixParamMan::Print2D( const std::string& arg ) const
{
  static const std::string func_name("["+class_name+"::"+__func__+"()]");

  hddaq::cout << "#D " << func_name << " " << arg << std::endl;
  for( int i=NumOfSegTOF-1; i>=0; --i ){
    hddaq::cout << " detA = " << std::setw(2)
		<< std::right << i << " : ";
    for( int j=0; j<NumOfSegSCH; ++j ){
      hddaq::cout << m_enable_2d[i][j];
    }
    hddaq::cout << std::endl;
  }
}

//______________________________________________________________________________
void
MatrixParamMan::Print3D( const std::string& arg ) const
{
  static const std::string func_name("["+class_name+"::"+__func__+"()]");

  hddaq::cout << "#D " << func_name << " " << arg << std::endl;
  for( int k=0; k<NumOfSegSFT_Mtx; ++k ){
    hddaq::cout << " detC = " << std::setw(2)
		<< std::right << k << std::endl;
    for( int i=NumOfSegTOF-1; i>=0; --i ){
      hddaq::cout << " detA = " << std::setw(2)
		  << std::right << i << " : ";
      for( int j=0; j<NumOfSegSCH; ++j ){
	hddaq::cout << m_enable_3d[i][j][k];
      }
      hddaq::cout << std::endl;
    }
  }
}

//______________________________________________________________________________
void
MatrixParamMan::SetMatrix2D( const std::string& file_name )
{
  m_file_name_2d = file_name;
}

//______________________________________________________________________________
void
MatrixParamMan::SetMatrix3D( const std::string& file_name )
{
  m_file_name_3d = file_name;
}
