/**
 *  file: DCPairHitCluster.cc
 *  date: 2017.04.10
 *
 */

#include "DCPairHitCluster.hh"
#include "DCLTrackHit.hh"
#include "DebugCounter.hh"

namespace
{
  const std::string& class_name("DCPairHitCluster");
}

//______________________________________________________________________________
DCPairHitCluster::DCPairHitCluster( DCLTrackHit *hitA, DCLTrackHit *hitB )
  : m_hitA(hitA),
    m_hitB(hitB),
    m_nhits(0)
{
  if(m_hitA) ++m_nhits;
  if(m_hitB) ++m_nhits;
  debug::ObjectCounter::increase(class_name);
}

//______________________________________________________________________________
DCPairHitCluster::~DCPairHitCluster( void )
{
  debug::ObjectCounter::decrease(class_name);
}

//______________________________________________________________________________
DCLTrackHit*
DCPairHitCluster::GetHit( int i ) const
{
  if(i==0) return m_hitA;
  if(i==1) return m_hitB;
  return 0;
}

//______________________________________________________________________________
bool
DCPairHitCluster::IsHoneycomb( void ) const
{
  if( m_hitA ) return m_hitA->IsHoneycomb();
  if( m_hitB ) return m_hitB->IsHoneycomb();

  return false;
}

//______________________________________________________________________________
void
DCPairHitCluster::SetHoneycomb( bool flag )
{
  if( m_hitA ) m_hitA->SetHoneycomb( flag );
  if( m_hitB ) m_hitB->SetHoneycomb( flag );
}
