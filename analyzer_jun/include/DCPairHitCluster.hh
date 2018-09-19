/**
 *  file: DCPairHitCluster.hh
 *  date: 2017.04.10
 *
 */

#ifndef DC_PAIR_HIT_CLUSTER_HH
#define DC_PAIR_HIT_CLUSTER_HH

class DCLTrackHit;

//______________________________________________________________________________
class DCPairHitCluster
{
public:
  DCPairHitCluster( DCLTrackHit *hitA, DCLTrackHit *hitB=0 );
  ~DCPairHitCluster( void );

private:
  DCPairHitCluster( const DCPairHitCluster& );
  DCPairHitCluster& operator =( const DCPairHitCluster& );

private:
  DCLTrackHit *m_hitA;
  DCLTrackHit *m_hitB;
  int          m_nhits;

public:
  int          NumberOfHits( void ) const { return m_nhits; }
  DCLTrackHit* GetHit( int i=0 )    const;
  bool         IsHoneycomb( void )  const;
  void         SetHoneycomb( bool flag );
};

#endif
