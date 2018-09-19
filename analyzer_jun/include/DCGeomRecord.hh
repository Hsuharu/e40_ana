/**
 *  file: DCGeomRecord.hh
 *  date: 2017.04.10
 *
 */

#ifndef DC_GEOM_RECORD_HH
#define DC_GEOM_RECORD_HH

#include "ThreeVector.hh"

#include <string>
#include <functional>

#include <std_ostream.hh>

//______________________________________________________________________________
class DCGeomRecord
{
public:
  DCGeomRecord( int id, const std::string &name,
                double x, double y, double z, double ta,
                double ra1, double ra2, double length, double resol,
		double w0, double dd, double ofs );
  DCGeomRecord( int id, const std::string &name,
		const ThreeVector pos, double ta,
		double ra1, double ra2, double length, double resol,
		double w0, double dd, double ofs );
  ~DCGeomRecord( void );
  DCGeomRecord( const DCGeomRecord& );
  DCGeomRecord& operator =( const DCGeomRecord );

private:
  int         m_id;
  std::string m_name;
  ThreeVector m_pos;
  double      m_tilt_angle;
  double      m_rot_angle1;
  double      m_rot_angle2;
  double      m_length;
  double      m_resolution;
  double      m_w0;
  double      m_dd;
  double      m_offset;

  double m_dxds, m_dxdt, m_dxdu;
  double m_dyds, m_dydt, m_dydu;
  double m_dzds, m_dzdt, m_dzdu;

  double m_dsdx, m_dsdy, m_dsdz;
  double m_dtdx, m_dtdy, m_dtdz;
  double m_dudx, m_dudy, m_dudz;

public:
  const ThreeVector& Position( void )     const { return m_pos; }
  ThreeVector        NormalVector( void ) const;
  ThreeVector        UnitVector( void )   const;
  int                Id( void )             const { return m_id;         }
  std::string        Name( void )           const { return m_name;       }
  const ThreeVector& Pos( void )            const { return m_pos;        }
  double             TiltAngle( void )      const { return m_tilt_angle; }
  double             RotationAngle1( void ) const { return m_rot_angle1; }
  double             RotationAngle2( void ) const { return m_rot_angle2; }
  double             Length( void )         const { return m_length;     }
  double             Resolution( void )     const { return m_resolution; }
  void               SetResolution( double res )  { m_resolution = res;  }

  double dsdx( void ) const { return m_dsdx; }
  double dsdy( void ) const { return m_dsdy; }
  double dsdz( void ) const { return m_dsdz; }
  double dtdx( void ) const { return m_dtdx; }
  double dtdy( void ) const { return m_dtdy; }
  double dtdz( void ) const { return m_dtdz; }
  double dudx( void ) const { return m_dudx; }
  double dudy( void ) const { return m_dudy; }
  double dudz( void ) const { return m_dudz; }

  double dxds( void ) const { return m_dxds; }
  double dxdt( void ) const { return m_dxdt; }
  double dxdu( void ) const { return m_dxdu; }
  double dyds( void ) const { return m_dyds; }
  double dydt( void ) const { return m_dydt; }
  double dydu( void ) const { return m_dydu; }
  double dzds( void ) const { return m_dzds; }
  double dzdt( void ) const { return m_dzdt; }
  double dzdu( void ) const { return m_dzdu; }

  double WirePos( double wire )   const;
  int    WireNumber( double pos ) const;
  void   Print( const std::string& arg="", std::ostream& ost=hddaq::cout ) const;

private:
  void CalcVectors( void );

};

//______________________________________________________________________________
struct DCGeomRecordComp
  : public std::binary_function <DCGeomRecord*, DCGeomRecord*, bool>
{
  bool operator()( const DCGeomRecord* const p1,
		   const DCGeomRecord* const p2 ) const
  { return p1->Id() < p2->Id(); }
};

#endif
