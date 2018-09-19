#ifndef HODO_HIT_HH
#define HODO_HIT_HH

#include "HodoHit.hh"

class RawData;

//______________________________________________________________________________
class HodoHit
{
public:
  HodoHit( void );
  virtual ~HodoHit() = 0;

public:
  virtual double DeltaE( int n=0 ) const = 0;

  virtual double GetTUp( int n=0 ) const = 0;
  virtual double GetTDown( int n=0 ) const = 0;

  virtual double MeanTime( int n=0 ) const = 0;
  virtual double CMeanTime( int n=0 ) const = 0;

  virtual int DetectorId( void ) const = 0;
  virtual int PlaneId( void ) const = 0;
  virtual int SegmentId( void ) const = 0;

  virtual bool ReCalc( bool applyRecursively=false) = 0;

};

#endif
