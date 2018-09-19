/**
 *  file: DCTdcCalibMan.hh
 *  date: 2017.04.10
 *
 */

#ifndef DC_TDC_CALIB_MAN_HH
#define DC_TDC_CALIB_MAN_HH

#include <map>
#include <string>
#include <vector>

struct DCTdcCalMap;

//______________________________________________________________________________
class DCTdcCalibMan
{
public:
  static DCTdcCalibMan&     GetInstance( void );
  static const std::string& ClassName( void );
  ~DCTdcCalibMan( void );

private:
  DCTdcCalibMan( void );
  DCTdcCalibMan( const DCTdcCalibMan & );
  DCTdcCalibMan& operator =( const DCTdcCalibMan & );

private:
  typedef std::map <unsigned int, DCTdcCalMap*> DCTdcContainer;
  typedef DCTdcContainer::const_iterator DCTdcIterator;
  bool           m_is_ready;
  std::string    m_file_name;
  DCTdcContainer m_container;

public:
  bool Initialize( void );
  bool Initialize( const std::string& file_name );
  bool IsReady( void ) const { return m_is_ready; }
  bool GetTime( int plane_id, double wire_id, int tdc, double& time ) const;
  bool GetTdc( int plane_id, double wire_id, double time, int& tdc ) const;
  void SetFileName( const std::string& file_name ) { m_file_name = file_name; }

private:
  DCTdcCalMap* GetMap( int plane_id, double wire_id ) const;
  void         ClearElements( void );
};

//______________________________________________________________________________
inline DCTdcCalibMan&
DCTdcCalibMan::GetInstance( void )
{
  static DCTdcCalibMan g_instance;
  return g_instance;
}

//______________________________________________________________________________
inline const std::string&
DCTdcCalibMan::ClassName( void )
{
  static std::string g_name("DCTdcCalibMan");
  return g_name;
}

#endif
