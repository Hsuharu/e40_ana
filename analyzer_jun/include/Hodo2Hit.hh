/**
 *  file: Hodo2Hit.hh
 *  date: 2017.04.10
 *
 */

#ifndef HODO2_HIT_HH
#define HODO2_HIT_HH

#include <cmath>
#include <cstddef>

#include "HodoRawHit.hh"
#include "HodoHit.hh"
#include "ThreeVector.hh"

class RawData;

//______________________________________________________________________________
class Hodo2Hit : public HodoHit
{
public:
  explicit Hodo2Hit( HodoRawHit *rhit, double max_time_diff=10.);
  virtual ~Hodo2Hit( void );

private:
  Hodo2Hit( const Hodo2Hit&);
  Hodo2Hit& operator =( const Hodo2Hit& );

protected:
  HodoRawHit          *m_raw;
  bool                 m_is_calculated;
  bool                 m_is_tof;
  double               m_max_time_diff; // unit:ns
  std::vector<double>  m_a1;
  std::vector<double>  m_a2;

  struct data_pair{
    double time1;
    double time2;
    double ctime1;
    double ctime2;
  };

  std::vector<data_pair> m_pair_cont;
  std::vector<bool>      m_flag_join;

public:
  HodoRawHit* GetRawHit( void )           { return m_raw; }
  virtual
  int         DetectorId( void )    const { return m_raw->DetectorId(); }
  virtual
  int         PlaneId( void )       const { return m_raw->PlaneId(); }
  virtual
  int         SegmentId( void )     const { return m_raw->SegmentId(); }

  bool        Calculate( void );
  bool        IsCalculated( void )  const { return m_is_calculated; }
  void        MakeAsTof( void )           { m_is_tof = true;}

  int         GetNumOfHit( void )   const { return m_pair_cont.size(); }
  double      GetAUp( int n=0 )     const { return m_a1.at(n); }
  double      GetALeft( int n=0 )   const { return m_a1.at(n); }
  double      GetADown( int n=0 )   const { return m_a2.at(n); }
  double      GetARight( int n=0 )  const { return m_a2.at(n); }
  virtual
  double      GetTUp( int n=0 )     const { return m_pair_cont[n].time1; }
  double      GetTLeft( int n=0 )   const { return m_pair_cont[n].time1; }
  virtual
  double      GetTDown( int n=0 )   const { return m_pair_cont[n].time2; }
  double      GetTRight( int n=0 )  const { return m_pair_cont[n].time2; }
  double      GetCTUp( int n=0 )    const { return m_pair_cont[n].ctime1; }
  double      GetCTLeft( int n=0 )  const { return m_pair_cont[n].ctime1; }
  double      GetCTDown( int n=0 )  const { return m_pair_cont[n].ctime2; }
  double      GetCTRight( int n=0 ) const { return m_pair_cont[n].ctime2; }

  virtual
  double      MeanTime( int n=0 )   const { return 0.5*(m_pair_cont[n].time1 + m_pair_cont[n].time2); }
  virtual
  double      CMeanTime( int n=0 )  const { return 0.5*(m_pair_cont[n].ctime1 + m_pair_cont[n].ctime2); }
  virtual
  double      DeltaE( int n=0 )     const { return std::sqrt(std::abs(m_a1.at(n)*m_a2.at(n))); }
  double      TimeDiff( int n=0 )   const { return m_pair_cont[n].ctime2 - m_pair_cont[n].ctime1; }

  void        SetJoined( int m )          { m_flag_join.at(m) = true;         }
  bool        Joined( int m )       const { return m_flag_join.at(m);         }
  bool        JoinedAllMhit();

  virtual bool ReCalc( bool applyRecursively=false )
  { return Calculate(); }

};


#endif
