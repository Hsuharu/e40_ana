/**
 *  file: SdcOutTrackMaker.cc
 *  date: 2017.04.10
 *
 */

#include "SdcOutTrackMaker.hh"

#include <cstdlib>
#include <iomanip>
#include <iostream>

#include <std_ostream.hh>

#include "DCLocalTrack.hh"
#include "DCLTrackHit.hh"
#include "DCPairHitCluster.hh"

namespace
{
  const std::string& class_name("SdcOutTrackMaker");
}

//______________________________________________________________________________
SdcOutTrackMaker::SdcOutTrackMaker( const std::vector<ClusterList>& candCont,
				    int minNumOfHits,
				    double maxCombi,
				    double maxChiSquare )
  : TrackMaker( candCont, minNumOfHits,
		maxCombi, maxChiSquare )
{
}

//______________________________________________________________________________
SdcOutTrackMaker::~SdcOutTrackMaker( void )
{
}

//______________________________________________________________________________
bool
SdcOutTrackMaker::IsGood( const DCLocalTrack* track ) const
{
  return
    (static_cast<int>(track->GetNHit())>=m_minNumOfHits)
    &&
    (const_cast<DCLocalTrack*>(track)->DoFit())
    &&
    (track->GetChiSquare()<m_maxChiSquare);
}

