/**
 *  file: FieldElements.hh
 *  date: 2017.04.10
 *
 */

#ifndef FIELD_ELEMENTS_HH
#define FIELD_ELEMENTS_HH

#include "DCGeomRecord.hh"
#include "ThreeVector.hh"

//______________________________________________________________________________
class FieldElements
{
public:
  FieldElements( const char *name, const ThreeVector &pos,
                 double ta, double ra1, double ra2 );
  virtual ~FieldElements( void );

private:
  enum FERegion { kFERSurface, kFERInside, kFEROutside };
  DCGeomRecord m_geom_record;

public:
  static FERegion FERSurface( void ) { return kFERSurface; }
  static FERegion FERInside( void ) { return kFERInside;  }
  static FERegion FEROutside( void ) { return kFEROutside; }
  ThreeVector     Local2GlobalPos( const ThreeVector &in ) const;
  ThreeVector     Local2GlobalDir( const ThreeVector &in ) const;
  ThreeVector     Global2LocalPos( const ThreeVector &in ) const;
  ThreeVector     Global2LocalDir( const ThreeVector &in ) const;

  virtual ThreeVector GetField( const ThreeVector &gPos ) const = 0;
  virtual bool        ExistField( const ThreeVector &gPos ) const = 0;
  virtual FERegion    CheckRegion( const ThreeVector &gPos,
				   double Tolerance ) const = 0;
};

#endif
