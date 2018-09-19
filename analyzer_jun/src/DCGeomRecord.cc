/**
 *  file: DCGeomRecord.cc
 *  date: 2017.04.10
 *
 */

#include "DCGeomRecord.hh"

#include <cmath>
#include <cstdlib>
#include <iostream>

#include "MathTools.hh"
#include "PrintHelper.hh"

namespace
{
  const std::string& class_name("DCGeomRecord");
  enum  EDefinition { kSks, kKurama };
  const EDefinition GlobalCoordinate = kKurama;
}

//______________________________________________________________________________
DCGeomRecord::DCGeomRecord( int id, const std::string &name,
			    double x, double y, double z, double ta,
			    double ra1, double ra2, double length, double resol,
			    double w0, double dd, double ofs )
  : m_id(id), m_name(name), m_pos(x,y,z), m_tilt_angle(ta),
    m_rot_angle1(ra1), m_rot_angle2(ra2),
    m_length(length), m_resolution(resol), m_w0(w0), m_dd(dd), m_offset(ofs)
{
  CalcVectors();
}

//______________________________________________________________________________
DCGeomRecord::DCGeomRecord( int id, const std::string &name,
			    const ThreeVector pos, double ta,
			    double ra1, double ra2, double length, double resol,
			    double w0, double dd, double ofs )
  : m_id(id), m_name(name), m_pos(pos),  m_tilt_angle(ta),
    m_rot_angle1(ra1), m_rot_angle2(ra2),
    m_length(length), m_resolution(resol), m_w0(w0), m_dd(dd), m_offset(ofs)
{
  CalcVectors();
}

//______________________________________________________________________________
DCGeomRecord::~DCGeomRecord( void )
{
}

//______________________________________________________________________________
void
DCGeomRecord::CalcVectors( void )
{
  double ct0 = std::cos( m_tilt_angle*math::Deg2Rad() );
  double st0 = std::sin( m_tilt_angle*math::Deg2Rad() );
  double ct1 = std::cos( m_rot_angle1*math::Deg2Rad() );
  double st1 = std::sin( m_rot_angle1*math::Deg2Rad() );
  double ct2 = std::cos( m_rot_angle2*math::Deg2Rad() );
  double st2 = std::sin( m_rot_angle2*math::Deg2Rad() );

  switch( GlobalCoordinate ){
  case kSks: // SKS difinition
    m_dxds =  ct0*ct2-st0*ct1*st2;
    m_dxdt = -st0*ct2-ct0*ct1*st2;
    m_dxdu =  st1*st2;

    m_dyds =  ct0*st2+st0*ct1*ct2;
    m_dydt = -st0*st2+ct0*ct1*ct2;
    m_dydu = -st1*ct2;

    m_dzds =  st0*st1;
    m_dzdt =  ct0*st1;
    m_dzdu =  ct1;

    m_dsdx =  ct0*ct2-st0*ct1*st2;
    m_dsdy =  ct0*st2+st0*ct1*ct2;
    m_dsdz =  st0*st1;

    m_dtdx = -st0*ct2-ct0*ct1*st2;
    m_dtdy = -st0*st2+ct0*ct1*ct2;
    m_dtdz =  ct0*st1;

    m_dudx =  st1*st2;
    m_dudy = -st1*ct2;
    m_dudz =  ct1;
    break;
  case kKurama: // new difinition : RA2 is around Y-axis
    m_dxds =  ct0*ct2+st0*st1*st2;
    m_dxdt = -st0*ct2+ct0*st1*st2;
    m_dxdu =  ct1*st2;

    m_dyds =  st0*ct1;
    m_dydt =  ct0*ct1;
    m_dydu = -st1;

    m_dzds = -ct0*st2+st0*st1*ct2;
    m_dzdt =  st0*st2+ct0*st1*ct2;
    m_dzdu =  ct1*ct2;

    m_dsdx =  ct0*ct2+st0*st1*st2;
    m_dsdy =  st0*ct1;
    m_dsdz = -ct0*st2+st0*st1*ct2;

    m_dtdx = -st0*ct2+ct0*st1*st2;
    m_dtdy =  ct0*ct1;
    m_dtdz =  st0*st2+ct0*st1*ct2;

    m_dudx =  ct1*st2;
    m_dudy = -st1;
    m_dudz =  ct1*ct2;
    break;
  }
}

//______________________________________________________________________________
ThreeVector
DCGeomRecord::NormalVector( void ) const
{
  return ThreeVector( m_dxdu, m_dydu, m_dzdu );
}

//______________________________________________________________________________
ThreeVector
DCGeomRecord::UnitVector( void ) const
{
  return ThreeVector( m_dxds, m_dyds, m_dzds );
}

//______________________________________________________________________________
double
DCGeomRecord::WirePos( double wire ) const
{
  return m_dd*(wire - m_w0)+m_offset;
}

//______________________________________________________________________________
int
DCGeomRecord::WireNumber( double pos ) const
{
  double dw = ( (pos-m_offset)/m_dd ) + m_w0;
  int    iw = int(dw);
  if( (dw-double(iw))>0.5 )
    return iw+1;
  else
    return iw;
}

//______________________________________________________________________________
void
DCGeomRecord::Print( const std::string& arg, std::ostream& ost ) const
{
  PrintHelper helper( 3, std::ios::fixed, ost );
  ost << " id = "   << std::setw(3) << std::right << m_id << " "
      << " name = " << std::setw(9) << std::left << m_name << " "
      << " pos = (" << " " << std::right << std::fixed
      << std::setw(8)  << m_pos.x() << ", "
      << std::setw(8)  << m_pos.y() << ", "
      << std::setw(10) << m_pos.z() << " ) "
      << " TA = "     << std::setw(7) << m_tilt_angle << " "
      << " RA1 = "    << std::setw(6) << m_rot_angle1 << " "
      << " RA2 = "    << std::setw(6) << m_rot_angle2 << " "
      << " L = "      << std::setw(9) << m_length << " "
      << " W0 = "     << std::setw(7) << m_w0 << " "
      << " dWdX = "   << std::setw(6) << m_dd << " "
      << " offset = " << std::setw(7) << m_offset << std::endl;
}
