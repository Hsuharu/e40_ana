/**
 *  file: DCTrackSearch.hh
 *  date: 2017.04.10
 *
 */

#ifndef DC_TRACK_SEARCH_HH
#define DC_TRACK_SEARCH_HH

#include "DCAnalyzer.hh"

#include <vector>

struct DCPairPlaneInfo;
class  DCPairHitCluster;
class  DCLocalTrack;
class  DCLTrackHit;
class  MWPCCluster;

typedef std::vector<DCPairHitCluster*> ClusterList;
typedef std::vector<int>               IndexList;

namespace track
{
  //______________________________________________________________________________
  int LocalTrackSearch( const std::vector<DCHitContainer>& HC,
			const DCPairPlaneInfo *PpInfo,
			int npp, std::vector<DCLocalTrack*>& TrackCont,
			int MinNumOfHits=6, int T0Seg = -1 );

  //______________________________________________________________________________
  int LocalTrackSearch( const std::vector< std::vector<DCHitContainer> >& hcAssemble,
			const DCPairPlaneInfo *PpInfo,
			int npp, std::vector<DCLocalTrack*>& TrackCont,
			int MinNumOfHits=6, int T0Seg = -1 );

  //______________________________________________________________________________
  int LocalTrackSearchSdcInFiber( const std::vector<DCHitContainer>& HC,
				  const DCPairPlaneInfo *PpInfo,
				  int npp, std::vector<DCLocalTrack*>& trackCont,
				  int MinNumOfHits=6 );

  //______________________________________________________________________________
  int LocalTrackSearchVUX( const std::vector<DCHitContainer>& HC,
			   const DCPairPlaneInfo *PpInfo,
			   int npp, std::vector<DCLocalTrack*>& TrackCont,
			   int MinNumOfHits=6 );

  //______________________________________________________________________________
  int LocalTrackSearchSdcOut( const std::vector<DCHitContainer>& SdcOutHC,
			      const DCPairPlaneInfo *PpInfo, int npp,
			      std::vector<DCLocalTrack*>& TrackCont,
			      int MinNumOfHits=6 );

  //______________________________________________________________________________
  int LocalTrackSearchSdcOut( const DCHitContainer& TOFHC,
			      const std::vector<DCHitContainer>& SdcOutHC,
			      const DCPairPlaneInfo *PpInfo,
			      int npp,
			      std::vector<DCLocalTrack*>& TrackCont,
			      int MinNumOfHits=6 );

  //______________________________________________________________________________
  int LocalTrackSearchBcOutSdcIn( const std::vector<DCHitContainer>& BcHC,
				  const DCPairPlaneInfo *BcPpInfo,
				  const std::vector<DCHitContainer>& SdcHC,
				  const DCPairPlaneInfo *SdcPpInfo,
				  int BcNpp, int SdcNpp,
				  std::vector<DCLocalTrack*>& TrackCont,
				  int MinNumOfHits=18 );

  //______________________________________________________________________________
  int LocalTrackSearchSdcInSdcOut( const std::vector<DCHitContainer>& SdcInHC,
				   const DCPairPlaneInfo *SdcInPpInfo,
				   const std::vector<DCHitContainer>& SdcOutHC,
				   const DCPairPlaneInfo *SdcOutPpInfo,
				   int SdcInNpp, int SdcOutNpp,
				   std::vector<DCLocalTrack*>& TrackCont,
				   int MinNumOfHits=12 );
  //______________________________________________________________________________
  int MWPCLocalTrackSearch( const std::vector<DCHitContainer>& HC,
			    std::vector<DCLocalTrack*>& TrackCont );

  //______________________________________________________________________________
  int MWPCLocalTrackSearch( const std::vector< std::vector<DCHitContainer> >& hcList,
			    std::vector<DCLocalTrack*>& trackCont );

}

#endif
