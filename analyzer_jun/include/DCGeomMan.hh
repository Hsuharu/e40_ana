/**
 *  file: DCGeomMan.hh
 *  date: 2017.04.10
 *
 */

#ifndef DC_GEOM_MAN_HH
#define DC_GEOM_MAN_HH

#include "ThreeVector.hh"
#include <string>
#include <vector>
#include <map>

class DCGeomRecord;

//______________________________________________________________________________
class DCGeomMan
{
public:
  static DCGeomMan&         GetInstance( void );
  static const std::string& ClassName( void );
  ~DCGeomMan( void );

private:
  DCGeomMan( void );
  DCGeomMan( const DCGeomMan& );
  DCGeomMan& operator=( const DCGeomMan& );

private:
  typedef std::map <int, DCGeomRecord*>   DCGeomContainer;
  typedef DCGeomContainer::const_iterator DCGeomIterator;
  typedef std::map <std::string, int>     IntList;
  typedef std::map <std::string, double>  DoubleList;
  bool            m_is_ready;
  std::string     m_file_name;
  DCGeomContainer m_container;
  IntList         m_detector_id_map;
  DoubleList      m_global_z_map;
  DoubleList      m_local_z_map;

public:
  bool                Initialize( void );
  bool                Initialize( const char *file_name );
  bool                Initialize( const std::string& file_name );
  bool                IsReady( void ) const { return m_is_ready; }
  double              GetLocalZ( int lnum ) const;
  double              GetLocalZ( const std::string& key ) const;
  double              GetResolution( int lnum ) const;
  double              GetResolution( const std::string& key ) const;
  double              GetTiltAngle( int lnum ) const;
  double              GetTiltAngle( const std::string& key ) const;
  double              GetRotAngle1( int lnum ) const;
  double              GetRotAngle1( const std::string& key ) const;
  double              GetRotAngle2( int lnum ) const;
  double              GetRotAngle2( const std::string& key ) const;
  const ThreeVector&  GetGlobalPosition( int lnum ) const;
  const ThreeVector&  GetGlobalPosition( const std::string& key ) const;
  ThreeVector         NormalVector( int lnum ) const;
  ThreeVector         NormalVector( const std::string& key ) const;
  ThreeVector         UnitVector( int lnum ) const;
  ThreeVector         UnitVector( const std::string& key ) const;
  const DCGeomRecord* GetRecord( int lnum ) const;
  const DCGeomRecord* GetRecord( const std::string& key ) const;
  ThreeVector         Local2GlobalPos( int lnum, const ThreeVector &in ) const;
  ThreeVector         Local2GlobalPos( const std::string& key, const ThreeVector &in ) const;
  ThreeVector         Global2LocalPos( int lnum, const ThreeVector &in ) const;
  ThreeVector         Global2LocalPos( const std::string& key, const ThreeVector &in ) const;
  ThreeVector         Local2GlobalDir( int lnum, const ThreeVector &in ) const;
  ThreeVector         Local2GlobalDir( const std::string& key, const ThreeVector &in ) const;
  ThreeVector         Global2LocalDir( int lnum, const ThreeVector &in ) const;
  ThreeVector         Global2LocalDir( const std::string& key, const ThreeVector &in ) const;
  double              CalcWirePosition( int lnum, double wire ) const;
  double              CalcWirePosition( const std::string& key, double wire ) const;
  int                 CalcWireNumber( int lnum, double position ) const;
  int                 CalcWireNumber( const std::string& key, double position ) const;
  std::vector<int>    GetDetectorIDList( void ) const;
  int                 GetDetectorId( const std::string &key ) const;
  void                SetFileName( const char *file_name );
  void                SetFileName( const std::string &file_name );
  // Do not use this method except for special cases
  void                SetResolution( int lnum, double res );
  void                SetResolution( const std::string& key, double res );

  // Static method
  static const int&    DetectorId( const std::string& key );
  static const double& GlobalZ( const std::string& key );
  static const double& LocalZ( const std::string& key );

private:
  void ClearElements( void );
};

//______________________________________________________________________________
inline DCGeomMan&
DCGeomMan::GetInstance( void )
{
  static DCGeomMan g_instance;
  return g_instance;
}

//______________________________________________________________________________
inline const std::string&
DCGeomMan::ClassName( void )
{
  static std::string g_name("DCGeomMan");
  return g_name;
}

//______________________________________________________________________________
inline const int&
DCGeomMan::DetectorId( const std::string& key )
{
  return GetInstance().m_detector_id_map[key];
}

//______________________________________________________________________________
inline const double&
DCGeomMan::GlobalZ( const std::string& key )
{
  return GetInstance().m_global_z_map[key];
}

//______________________________________________________________________________
inline const double&
DCGeomMan::LocalZ( const std::string& key )
{
  return GetInstance().m_local_z_map[key];
}

#endif
