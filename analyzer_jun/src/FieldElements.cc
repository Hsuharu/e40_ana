/**
 *  file: FieldElements.cc
 *  date: 2017.04.10
 *
 */

#include "FieldElements.hh"

namespace
{
  const std::string& class_name("FieldElements");
}

//______________________________________________________________________________
FieldElements::FieldElements( const char *name,
                              const ThreeVector &pos,
                              double ta, double ra1, double ra2 )
  : m_geom_record( -1, name, pos, ta, ra1, ra2, 0., 0., 0., 0., 0. )
{
}

//______________________________________________________________________________
FieldElements::~FieldElements( void )
{
}

//______________________________________________________________________________
ThreeVector
FieldElements::Local2GlobalPos( const ThreeVector &in ) const
{
  ThreeVector gPos = m_geom_record.Position();
  double x = gPos.x()
    + m_geom_record.dxds()*in.x()
    + m_geom_record.dxdt()*in.y()
    + m_geom_record.dxdu()*in.z();
  double y = gPos.y()
    + m_geom_record.dyds()*in.x()
    + m_geom_record.dydt()*in.y()
    + m_geom_record.dydu()*in.z();
  double z = gPos.z()
    + m_geom_record.dzds()*in.x()
    + m_geom_record.dzdt()*in.y()
    + m_geom_record.dzdu()*in.z();

  return ThreeVector( x, y, z );
}

//______________________________________________________________________________
ThreeVector
FieldElements::Local2GlobalDir( const ThreeVector &in ) const
{
  double x
    = m_geom_record.dxds()*in.x()
    + m_geom_record.dxdt()*in.y()
    + m_geom_record.dxdu()*in.z();
  double y
    = m_geom_record.dyds()*in.x()
    + m_geom_record.dydt()*in.y()
    + m_geom_record.dydu()*in.z();
  double z
    = m_geom_record.dzds()*in.x()
    + m_geom_record.dzdt()*in.y()
    + m_geom_record.dzdu()*in.z();

  return ThreeVector( x, y, z );
}

//______________________________________________________________________________
ThreeVector
FieldElements::Global2LocalPos( const ThreeVector &in ) const
{
  ThreeVector gPos = m_geom_record.Position();
  double x
    = m_geom_record.dsdx()*(in.x()-gPos.x())
    + m_geom_record.dsdy()*(in.y()-gPos.y())
    + m_geom_record.dsdz()*(in.z()-gPos.z());
  double y
    = m_geom_record.dtdx()*(in.x()-gPos.x())
    + m_geom_record.dtdy()*(in.y()-gPos.y())
    + m_geom_record.dtdz()*(in.z()-gPos.z());
  double z
    = m_geom_record.dudx()*(in.x()-gPos.x())
    + m_geom_record.dudy()*(in.y()-gPos.y())
    + m_geom_record.dudz()*(in.z()-gPos.z());

  return ThreeVector( x, y, z );
}

//______________________________________________________________________________
ThreeVector
FieldElements::Global2LocalDir( const ThreeVector &in ) const
{
  double x
    = m_geom_record.dsdx()*in.x()
    + m_geom_record.dsdy()*in.y()
    + m_geom_record.dsdz()*in.z();
  double y
    = m_geom_record.dtdx()*in.x()
    + m_geom_record.dtdy()*in.y()
    + m_geom_record.dtdz()*in.z();
  double z
    = m_geom_record.dudx()*in.x()
    + m_geom_record.dudy()*in.y()
    + m_geom_record.dudz()*in.z();

  return ThreeVector( x, y, z );
}
