/**
 *  file: BH2Hit.hh
 *  date: 2017.04.10
 *
 */

#ifndef BH2_HIT_HH
#define BH2_HIT_HH

#define USE_COINCIDENCE_OUT_FOR_FINAL_BH2 0

#include "DebugCounter.hh"
#include "Hodo2Hit.hh"

//______________________________________________________________________________
class BH2Hit : public Hodo2Hit
{
public:
  BH2Hit( HodoRawHit *rhit, double max_time_diff=10. );
  ~BH2Hit( void );

private:
  double m_time_offset;

public:
  bool   Calculate( void );
  double UTime0( int n=0 )  const { return m_pair_cont[n].time1  +m_time_offset; }
  double UCTime0( int n=0 ) const { return m_pair_cont[n].ctime1 +m_time_offset; }
  double DTime0( int n=0 )  const { return m_pair_cont[n].time2  +m_time_offset; }
  double DCTime0( int n=0 ) const { return m_pair_cont[n].ctime2 +m_time_offset; }
#if USE_COINCIDENCE_OUT_FOR_FINAL_BH2
  double MeanTime( int n = 0 )  const { return m_pair_cont[n].time2; }
  double CMeanTime( int n = 0 ) const { return m_pair_cont[n].ctime2; }
  double Time0( int n = 0 )  const { return m_pair_cont[n].time2 + m_time_offset; }
  double CTime0( int n = 0 ) const { return m_pair_cont[n].ctime2 + m_time_offset; }
#else
  double MeanTime( int n = 0 )  const { return 0.5*(m_pair_cont[n].time1 + m_pair_cont[n].time2); }
  double CMeanTime( int n = 0 ) const { return 0.5*(m_pair_cont[n].ctime1 + m_pair_cont[n].ctime2); }
  double Time0( int n=0 )   const { return 0.5*(m_pair_cont[n].time1 + m_pair_cont[n].time2) +m_time_offset; }
  double CTime0( int n=0 )  const { return 0.5*(m_pair_cont[n].ctime1 + m_pair_cont[n].ctime2) +m_time_offset; }
#endif

  virtual bool ReCalc( bool applyRecursively=false )
  { return Calculate(); };

};

#endif
