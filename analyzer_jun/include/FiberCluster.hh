/**
 *  file: FiberCluster.hh
 *  date: 2017.04.10
 *
 */

#ifndef FIBER_CLUSTER_HH
#define FIBER_CLUSTER_HH

#include <vector>

class FLHit;

//______________________________________________________________________________
class FiberCluster
{
public:
  FiberCluster( void );
  virtual ~FiberCluster( void );

private:
  FiberCluster( const FiberCluster& object );
  FiberCluster& operator =( const FiberCluster& object );

protected:
  typedef std::vector<FLHit*> HitContainer;
  enum FlagsFiber { Initialized, gfastatus, sizeFlagsFiber };
  HitContainer m_hit_container;
  int          m_cluster_size;
  int          m_cluster_id;
  double       m_mean_time;
  double       m_real_mean_time; // real mean (not a closest value of CTime)
  double       m_max_width;
  double       m_mean_seg;
  double       m_mean_pos;
  bool         m_flag[sizeFlagsFiber];

public:
  bool   Calculate( void );
  void   push_back( FLHit* hit ) { m_hit_container.push_back(hit); };
  int    VectorSize( void )      const { return m_hit_container.size();    }
  int    ClusterId( void )       const { return m_cluster_id;    }
  int    ClusterSize( void )     const { return m_cluster_size;    }
  double CMeanTime( void )       const { return m_mean_time;       }
  double RCMeanTime( void )      const { return m_real_mean_time;  }
  double Width( void )           const { return m_max_width;       }
  double Tot( void )             const { return Width();           }
  double MeanPosition( void )    const { return m_mean_pos;        }
  double MeanSeg( void )         const { return m_mean_seg;        }
  FLHit* GetHit( int i )     const;
  bool   GoodForAnalysis( void ) const { return m_flag[gfastatus]; }
  bool   GoodForAnalysis( bool status );
  bool   ReCalc( bool applyRecusively=false );

private:
  void calc( void );
  void Debug( void );

};

#endif
