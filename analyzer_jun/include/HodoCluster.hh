/**
 *  file: HodoCluster.hh
 *  date: 2017.04.10
 *
 */

#ifndef HODO_CLUSTER_HH
#define HODO_CLUSTER_HH

#include <cstddef>

class HodoHit;
class HodoAnalyzer;

//______________________________________________________________________________
class HodoCluster
{
public:
  HodoCluster( HodoHit *hitA, HodoHit *hitB=0, HodoHit *hitC=0 );
  virtual ~HodoCluster( void );

private:
  HodoCluster( const HodoCluster & );
  HodoCluster & operator = ( const HodoCluster & );

private:
  HodoHit *m_hitA;
  HodoHit *m_hitB;
  HodoHit *m_hitC;
  int       m_indexA;
  int       m_indexB;
  int       m_indexC;
  int       m_cluster_size;
  double    m_mean_time;
  double    m_cmean_time;
  double    m_de;
  double    m_mean_seg;
  double    m_time_diff;
  double    m_1st_seg;
  double    m_1st_time;
  bool      m_good_for_analysis;

public:
  void Calculate( void );
  HodoHit*  GetHit( int i )         const;
  int       ClusterSize( void )     const { return m_cluster_size; }
  double    MeanTime( void )        const { return m_mean_time;    }
  double    CMeanTime( void )       const { return m_cmean_time;    }
  double    DeltaE( void )          const { return m_de;           }
  double    MeanSeg( void )         const { return m_mean_seg;     }
  double    TimeDif( void )         const { return m_time_diff;    }
  double    C1stSeg( void )         const { return m_1st_seg;      }
  double    C1stTime( void )        const { return m_1st_time;     }
  bool      GoodForAnalysis( void ) const { return m_good_for_analysis; }
  bool      GoodForAnalysis( bool status )
  {
    bool pre_status = m_good_for_analysis;
    m_good_for_analysis = status;
    return pre_status;
  }

  void      SetIndex(int iA, int iB=0, int iC=0)
  {
    m_indexA = iA; m_indexB = iB; m_indexC = iC;
  }

  bool ReCalc( bool applyRecusively=false );

private:

};
#endif
