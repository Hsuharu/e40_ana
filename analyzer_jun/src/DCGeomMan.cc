/**
 *  file: DCGeomMan.cc
 *  date: 2017.04.10
 *
 */

#include "DCGeomMan.hh"
#include "DCGeomRecord.hh"

#include <string>
#include <stdexcept>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <fstream>
#include <sstream>

#include <std_ostream.hh>

#include "DeleteUtility.hh"

namespace
{
  const std::string& class_name("DCGeomMan");
}

//______________________________________________________________________________
DCGeomMan::DCGeomMan( void )
  : m_is_ready(false),
    m_file_name(""),
    m_container(),
    m_detector_id_map(),
    m_global_z_map(),
    m_local_z_map()
{
}

//______________________________________________________________________________
DCGeomMan::~DCGeomMan( void )
{
  ClearElements();
}

//______________________________________________________________________________
void
DCGeomMan::SetFileName( const char* file_name )
{
  m_file_name = file_name;
}

//______________________________________________________________________________
void
DCGeomMan::SetFileName( const std::string& file_name )
{
  m_file_name = file_name;
}

//______________________________________________________________________________
bool
DCGeomMan::Initialize( const char* file_name )
{
  m_file_name = file_name;
  return Initialize();
}

//______________________________________________________________________________
bool
DCGeomMan::Initialize( const std::string& file_name )
{
  m_file_name = file_name;
  return Initialize();
}

//______________________________________________________________________________
double
DCGeomMan::GetLocalZ( int lnum ) const
{
  static const std::string func_name("["+class_name+"::"+__func__+"()]");
  const DCGeomRecord *record = GetRecord(lnum);
  if( record ){
    return record->Length();
  }else{
    hddaq::cerr << func_name << ": No record. Layer#="
		<< lnum << std::endl;
    throw std::out_of_range(func_name+": No record" );
  }
}

//______________________________________________________________________________
double
DCGeomMan::GetLocalZ( const std::string& key ) const
{
  return GetLocalZ( GetDetectorId( key ) );
}

//______________________________________________________________________________
double
DCGeomMan::GetResolution( int lnum ) const
{
  static const std::string func_name("["+class_name+"::"+__func__+"()]");
  const DCGeomRecord *record = GetRecord(lnum);
  if( record ) return record->Resolution();
  else{
    hddaq::cerr << func_name << ": No record. Layer#="
		<< lnum << std::endl;
    throw std::out_of_range(func_name+": No record" );
  }
}

//______________________________________________________________________________
double
DCGeomMan::GetResolution( const std::string& key ) const
{
  return GetResolution( GetDetectorId( key ) );
}

//______________________________________________________________________________
double
DCGeomMan::GetTiltAngle( int lnum ) const
{
  static const std::string func_name("["+class_name+"::"+__func__+"()]");
  const DCGeomRecord *record = GetRecord(lnum);
  if( record ) return record->TiltAngle();
  else{
    hddaq::cerr << func_name << ": No record. Layer#="
		<< lnum << std::endl;
    throw std::out_of_range(func_name+": No record" );
  }
}

//______________________________________________________________________________
double
DCGeomMan::GetTiltAngle( const std::string& key ) const
{
  return GetTiltAngle( GetDetectorId( key ) );
}

//______________________________________________________________________________
double
DCGeomMan::GetRotAngle1( int lnum ) const
{
  static const std::string func_name("["+class_name+"::"+__func__+"()]");
  const DCGeomRecord *record = GetRecord(lnum);
  if( record ) return record->RotationAngle1();
  else{
    hddaq::cerr << func_name << ": No record. Layer#="
		<< lnum << std::endl;
    throw std::out_of_range(func_name+": No record" );
  }
}

//______________________________________________________________________________
double
DCGeomMan::GetRotAngle1( const std::string& key ) const
{
  return GetRotAngle1( GetDetectorId( key ) );
}

//______________________________________________________________________________
double
DCGeomMan::GetRotAngle2( int lnum ) const
{
  static const std::string func_name("["+class_name+"::"+__func__+"()]");
  const DCGeomRecord *record = GetRecord(lnum);
  if( record ) return record->RotationAngle2();
  else{
    hddaq::cerr << func_name << ": No record. Layer#="
		<< lnum << std::endl;
    throw std::out_of_range(func_name+": No record" );
  }
}

//______________________________________________________________________________
double
DCGeomMan::GetRotAngle2( const std::string& key ) const
{
  return GetRotAngle2( GetDetectorId( key ) );
}

//______________________________________________________________________________
const ThreeVector&
DCGeomMan::GetGlobalPosition( int lnum ) const
{
  static const std::string func_name("["+class_name+"::"+__func__+"()]");
  const DCGeomRecord *record = GetRecord(lnum);
  if( record ) return record->Pos();
  else{
    hddaq::cerr << func_name << ": No record. Layer#="
		<< lnum << std::endl;
    throw std::out_of_range(func_name+": No record" );
  }
}

//______________________________________________________________________________
const ThreeVector&
DCGeomMan::GetGlobalPosition( const std::string& key ) const
{
  return GetGlobalPosition( GetDetectorId( key ) );
}

//______________________________________________________________________________
ThreeVector
DCGeomMan::NormalVector( int lnum ) const
{
  static const std::string func_name("["+class_name+"::"+__func__+"()]");
  const DCGeomRecord *record = GetRecord(lnum);
  if( record ) return record->NormalVector();
  else{
    hddaq::cerr << func_name << ": No record. Layer#="
		<< lnum << std::endl;
    throw std::out_of_range(func_name+": No record" );
  }
}

//______________________________________________________________________________
ThreeVector
DCGeomMan::NormalVector( const std::string& key ) const
{
  return NormalVector( GetDetectorId( key ) );
}

//______________________________________________________________________________
ThreeVector
DCGeomMan::UnitVector( int lnum ) const
{
  static const std::string func_name("["+class_name+"::"+__func__+"()]");
  const DCGeomRecord *record = GetRecord(lnum);
  if( record ) return record->UnitVector();
  else{
    hddaq::cerr << func_name << ": No record. Layer#="
		<< lnum << std::endl;
    throw std::out_of_range(func_name+": No record" );
  }
}

//______________________________________________________________________________
ThreeVector
DCGeomMan::UnitVector( const std::string& key ) const
{
  return UnitVector( GetDetectorId( key ) );
}

//______________________________________________________________________________
const DCGeomRecord*
DCGeomMan::GetRecord( int lnum ) const
{
  static const std::string func_name("["+class_name+"::"+__func__+"()]");
  DCGeomIterator itr = m_container.find(lnum);
  DCGeomIterator end = m_container.end();
  DCGeomRecord *record = 0;
  if( itr!=end )
    record = itr->second;
  if( !record ){
    hddaq::cerr << func_name << ": No record. Layer#="
		<< lnum << std::endl;
    throw std::out_of_range(func_name+": No record" );
  }
  return record;
}

//______________________________________________________________________________
const DCGeomRecord*
DCGeomMan::GetRecord( const std::string& key ) const
{
  return GetRecord( GetDetectorId( key ) );
}

//______________________________________________________________________________
double
DCGeomMan::CalcWirePosition( int lnum, double wire ) const
{
  static const std::string func_name("["+class_name+"::"+__func__+"()]");
  const DCGeomRecord *record = GetRecord(lnum);
  if( record ){
    return record->WirePos(wire);
  }
  else{
    hddaq::cerr << func_name << ": No record. Layer#="
		<< lnum << std::endl;
    throw std::out_of_range(func_name+": No record" );
  }
}

//______________________________________________________________________________
double
DCGeomMan::CalcWirePosition( const std::string& key, double wire ) const
{
  return CalcWirePosition( GetDetectorId( key ), wire );
}

//______________________________________________________________________________
int
DCGeomMan::CalcWireNumber( int lnum, double pos ) const
{
  static const std::string func_name("["+class_name+"::"+__func__+"()]");
  const DCGeomRecord *record = GetRecord(lnum);
  if( record ){
    return record->WireNumber(pos);
  }
  else{
    hddaq::cerr << func_name << ": No record. Layer#="
		<< lnum << std::endl;
    throw std::out_of_range(func_name+": No record" );
  }
}

//______________________________________________________________________________
int
DCGeomMan::CalcWireNumber( const std::string& key, double wire ) const
{
  return CalcWireNumber( GetDetectorId( key ), wire );
}

//______________________________________________________________________________
void
DCGeomMan::ClearElements( void )
{
  del::ClearMap( m_container );
}

//______________________________________________________________________________
bool
DCGeomMan::Initialize( void )
{
  static const std::string func_name("["+class_name+"::"+__func__+"()]");

  if( m_is_ready ){
    hddaq::cerr << "#W " << func_name
		<< " already initialied" << std::endl;
    return false;
  }

  std::ifstream ifs( m_file_name.c_str() );
  if( !ifs.is_open() ){
    hddaq::cerr << "#E " << func_name
		<< " file open fail : " << m_file_name << std::endl;
    return false;
  }

  ClearElements();

  std::string line;
  while( ifs.good() && std::getline( ifs, line ) ){
    if( line.empty() || line[0]=='#' ) continue;
    std::istringstream iss( line );
    int id; std::string name;
    double gx, gy, gz, ta, ra1, ra2, l, res, w0, dd, ofs;
    if( iss >> id >> name >> gx >> gy >> gz >> ta >> ra1 >> ra2
	>> l >> res >> w0 >> dd >> ofs ){
      DCGeomRecord *record =
	new DCGeomRecord( id, name, gx, gy, gz, ta, ra1, ra2,
			  l, res, w0, dd, ofs );
      if( m_container[id] ){
	hddaq::cerr << "#W " << func_name << " "
		    << "duplicated key is deleted : " << id << std::endl;
	m_container[id]->Print();
	delete m_container[id];
      }
      m_container[id] = record;

      m_detector_id_map[name] = id;
      m_global_z_map[name]    = gz;
      m_local_z_map[name]     = l;
    }else{
      hddaq::cerr << "#E " << func_name << " "
		  << "invalid format : " << line << std::endl;
    }
  }

  m_is_ready = true;
  return m_is_ready;
}

//______________________________________________________________________________
std::vector<int>
DCGeomMan::GetDetectorIDList( void ) const
{
  std::vector<int> vlist;
  vlist.reserve( m_container.size() );
  DCGeomIterator itr, end=m_container.end();
  for( itr=m_container.begin(); itr!=end; ++itr ){
    vlist.push_back( itr->first );
  }

  return vlist;
}

//______________________________________________________________________________
ThreeVector
DCGeomMan::Local2GlobalPos( int lnum, const ThreeVector& in ) const
{
  static const std::string func_name("["+class_name+"::"+__func__+"()]");

  const DCGeomRecord *record = GetRecord(lnum);
  if( !record )
    throw std::out_of_range(func_name+": No record" );

  double x = record->dxds()*in.x() + record->dxdt()*in.y()
    + record->dxdu()*in.z() + record->Pos().x();
  double y = record->dyds()*in.x() + record->dydt()*in.y()
    + record->dydu()*in.z() + record->Pos().y();
  double z = record->dzds()*in.x() + record->dzdt()*in.y()
    + record->dzdu()*in.z() + record->Pos().z();

  return ThreeVector( x, y, z );
}

//______________________________________________________________________________
ThreeVector
DCGeomMan::Local2GlobalPos( const std::string& key, const ThreeVector& in ) const
{
  return Local2GlobalPos( GetDetectorId( key ), in );
}

//______________________________________________________________________________
ThreeVector
DCGeomMan::Global2LocalPos( int lnum, const ThreeVector& in ) const
{
  static const std::string func_name("["+class_name+"::"+__func__+"()]");

  const DCGeomRecord *record = GetRecord(lnum);
  if( !record ){
    hddaq::cerr << func_name << ": No record. Layer#="
		<< lnum << std::endl;
    throw std::out_of_range(func_name+": No record" );
  }

  double x
    = record->dsdx()*(in.x()-record->Pos().x())
    + record->dsdy()*(in.y()-record->Pos().y())
    + record->dsdz()*(in.z()-record->Pos().z());
  double y
    = record->dtdx()*(in.x()-record->Pos().x())
    + record->dtdy()*(in.y()-record->Pos().y())
    + record->dtdz()*(in.z()-record->Pos().z());
  double z
    = record->dudx()*(in.x()-record->Pos().x())
    + record->dudy()*(in.y()-record->Pos().y())
    + record->dudz()*(in.z()-record->Pos().z());

  return ThreeVector( x, y, z );
}

//______________________________________________________________________________
ThreeVector
DCGeomMan::Global2LocalPos( const std::string& key, const ThreeVector& in ) const
{
  return Global2LocalPos( GetDetectorId( key ), in );
}

//______________________________________________________________________________
ThreeVector
DCGeomMan::Local2GlobalDir( int lnum, const ThreeVector& in ) const
{
  static const std::string func_name("["+class_name+"::"+__func__+"()]");

  const DCGeomRecord *record = GetRecord(lnum);
  if( !record ){
    hddaq::cerr << func_name << ": No record. Layer#="
		<< lnum << std::endl;
    throw std::out_of_range(func_name+": No record" );
  }

  double x = record->dxds()*in.x() + record->dxdt()*in.y()
    + record->dxdu()*in.z();
  double y = record->dyds()*in.x() + record->dydt()*in.y()
    + record->dydu()*in.z();
  double z = record->dzds()*in.x() + record->dzdt()*in.y()
    + record->dzdu()*in.z();

  return ThreeVector( x, y, z );
}

//______________________________________________________________________________
ThreeVector
DCGeomMan::Local2GlobalDir( const std::string& key, const ThreeVector& in ) const
{
  return Local2GlobalDir( GetDetectorId( key ), in );
}

//______________________________________________________________________________
ThreeVector
DCGeomMan::Global2LocalDir( int lnum, const ThreeVector& in ) const
{
  static const std::string func_name("["+class_name+"::"+__func__+"()]");

  const DCGeomRecord *record = GetRecord(lnum);
  if( !record ){
    hddaq::cerr << func_name << ": No record. Layer#="
		<< lnum << std::endl;
    throw std::out_of_range(func_name+": No record" );
  }

  double x = record->dsdx()*in.x() + record->dsdy()*in.y()
    + record->dsdz()*in.z();
  double y = record->dtdx()*in.x() + record->dtdy()*in.y()
    + record->dtdz()*in.z();
  double z = record->dudx()*in.x() + record->dudy()*in.y()
    + record->dudz()*in.z();

  return ThreeVector( x, y, z );
}

//______________________________________________________________________________
ThreeVector
DCGeomMan::Global2LocalDir( const std::string& key, const ThreeVector& in ) const
{
  return Global2LocalDir( GetDetectorId( key ), in );
}

//______________________________________________________________________________
void
DCGeomMan::SetResolution( int lnum, double res )
{
  static const std::string func_name("["+class_name+"::"+__func__+"()]");
  DCGeomRecord *record = m_container[lnum];
  if( record ) {
    record->SetResolution( res );
    return;
  }
  else{
    hddaq::cerr << func_name << ": No record. Layer#="
		<< lnum << std::endl;
    throw std::out_of_range(func_name+": No record" );
  }
}

//______________________________________________________________________________
void
DCGeomMan::SetResolution( const std::string& key, double res )
{
  SetResolution( GetDetectorId( key ), res );
}

//______________________________________________________________________________
int
DCGeomMan::GetDetectorId( const std::string &key ) const
{
  static const std::string func_name("["+class_name+"::"+__func__+"()]");

  DCGeomIterator itr, end   = m_container.end();
  for( itr=m_container.begin(); itr!=end; ++itr ){
    if ( itr->second->Name() == key )
      return itr->second->Id();
  }

  hddaq::cerr << func_name << " : No such key " << key << std::endl;
  std::exit(EXIT_FAILURE);
}
