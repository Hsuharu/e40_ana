/**
 *  file: ConfMan.cc
 *  date: 2017.04.10
 *
 */

#include "ConfMan.hh"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <sstream>
#include <vector>

#include <lexical_cast.hh>
#include <filesystem_util.hh>
#include <replace_string.hh>
#include <std_ostream.hh>

// #include "BH1Filter.hh"
#include "BH1Match.hh"
#include "BH2Filter.hh"
#include "DCGeomMan.hh"
#include "DCTdcCalibMan.hh"
#include "DCDriftParamMan.hh"
#include "EventDisplay.hh"
#include "FieldMan.hh"
#include "HodoParamMan.hh"
#include "HodoPHCMan.hh"
#include "K18TransMatrix.hh"
#include "MatrixParamMan.hh"
#include "MsTParamMan.hh"
#include "UnpackerManager.hh"
#include "UserParamMan.hh"

namespace
{
  using namespace hddaq::unpacker;
  const std::string& class_name("ConfMan");
  const std::string& kConfFile("CONF");
  std::string sConfDir;
  UnpackerManager&      gUnpacker = GUnpacker::get_instance();
  const MatrixParamMan& gMatrix   = MatrixParamMan::GetInstance();
  const UserParamMan&   gUser     = UserParamMan::GetInstance();
}

//______________________________________________________________________________
ConfMan::ConfMan( void )
  : m_is_ready(false)
{
}

//______________________________________________________________________________
ConfMan::~ConfMan( void )
{
}

//______________________________________________________________________________
bool
ConfMan::Initialize( void )
{
  static const std::string func_name("["+class_name+"::"+__func__+"()]");

  if( m_is_ready ){
    hddaq::cerr << "#W " << func_name
		<< " already initialied" << std::endl;
    return false;
  }

  std::ifstream ifs( m_file[kConfFile].c_str() );
  if( !ifs.is_open() ){
    hddaq::cerr << "#E " << func_name
		<< " cannot open file : " << m_file[kConfFile] << std::endl;
    return false;
  }

  hddaq::cout << "#D " << func_name << std::endl;

  sConfDir = hddaq::dirname(m_file[kConfFile]);

  std::string line;
  while( ifs.good() && std::getline( ifs, line ) ){
    if( line.empty() || line[0]=='#' ) continue;

    hddaq::replace_all(line, ",",  ""); // remove ,
    hddaq::replace_all(line, ":",  ""); // remove :
    hddaq::replace_all(line, "\"", ""); // remove "

    std::istringstream iss( line );
    std::istream_iterator<std::string> begin( iss );
    std::istream_iterator<std::string> end;
    std::vector<std::string> v( begin, end );
    if( v.size()<2 ) continue;

    std::string key = v[0];
    hddaq::cout << " key = "   << std::setw(10) << std::left << key
		<< " value = " << std::setw(30) << std::left << v[1]
		<< std::endl;

    m_file[key]   = FilePath(v[1]);
    m_string[key] = v[1];
    m_double[key] = hddaq::lexical_cast<double>(v[1]);
    m_int[key]    = hddaq::lexical_cast<int>(v[1]);
    m_bool[key]   = hddaq::lexical_cast<bool>(v[1]);
  }

  if ( !InitializeParameterFiles() || !InitializeHistograms() )
    return false;

  if( gMatrix.IsReady() )
    gMatrix.Print2D();
  if( gUser.IsReady() )
    gUser.Print();

  m_is_ready = true;
  return true;
}

//______________________________________________________________________________
bool
ConfMan::Initialize( const std::string& file_name )
{
  m_file[kConfFile] = file_name;
  return Initialize();
}

//______________________________________________________________________________
bool
ConfMan::InitializeUnpacker( void )
{
  gUnpacker.set_config_file( m_file["UNPACK"],
			     m_file["DIGIT"],
			     m_file["CMAP"] );
  return true;
}

//______________________________________________________________________________
bool
ConfMan::Finalize( void )
{
  return FinalizeProcess();
}

//______________________________________________________________________________
std::string
ConfMan::FilePath( const std::string& src ) const
{
  std::ifstream tmp( src.c_str() );
  if ( tmp.good() )
    return src;
  else
    return sConfDir + "+" + src;
}

