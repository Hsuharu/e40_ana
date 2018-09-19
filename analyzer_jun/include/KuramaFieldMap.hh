/**
 *  file: KuramaFieldMap.hh
 *  date: 2017.04.10
 *
 */

#ifndef KURAMA_FIELD_MAP_HH
#define KURAMA_FIELD_MAP_HH

#include <string>
#include <vector>

//______________________________________________________________________________
class KuramaFieldMap
{
public:
  KuramaFieldMap( const std::string& file_name );
  ~KuramaFieldMap( void );

private:
  KuramaFieldMap( const KuramaFieldMap& );
  KuramaFieldMap& operator =( const KuramaFieldMap& );

private:
  struct XYZ { double x, y, z; };
  typedef std::vector< std::vector< std::vector<XYZ> > > Field;
  bool        m_is_ready;
  std::string m_file_name;
  Field       B;
  int         Nx, Ny, Nz;
  double      X0, Y0, Z0;
  double      dX, dY, dZ;

public:
  bool Initialize( void );
  bool IsReady( void ) const { return m_is_ready; }
  bool GetFieldValue( const double pointCM[3], double *BfieldTesla ) const;

private:
  void ClearField( void );
};

#endif
