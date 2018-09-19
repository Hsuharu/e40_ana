/**
 *  file: SdcOutTrackMaker.hh
 *  date: 2017.04.10
 *
 */

#ifndef SDCOUT_TRACK_MAKER_HH
#define SDCOUT_TRACK_MAKER_HH

#include <string>
#include <vector>
#include <deque>

#include "TrackMaker.hh"

class DCPairHitCluster;
class DCLocalTrack;

//______________________________________________________________________________
class SdcOutTrackMaker : TrackMaker
{
public:
  SdcOutTrackMaker( const std::vector<ClusterList>& candCont,
		    int minNumOfHits,
		    double maxCombi,
		    double maxChiSquare);
  virtual ~SdcOutTrackMaker( void );

private:
  SdcOutTrackMaker( const SdcOutTrackMaker& );
  SdcOutTrackMaker& operator =( const SdcOutTrackMaker& );

protected:

public:
  virtual void  MakeTracks( std::vector<DCLocalTrack*>& trackList );

protected:
  virtual bool IsGood( const DCLocalTrack* track ) const;

};

#endif
