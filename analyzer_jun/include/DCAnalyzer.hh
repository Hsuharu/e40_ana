/**
 *  file: DCAnalyzer.hh
 *  date: 2017.04.10
 *
 */

#ifndef DC_ANALYZER_HH
#define DC_ANALYZER_HH

#include "DetectorID.hh"
#include "ThreeVector.hh"
#include <vector>

class DCHit;
class DCLocalTrack;
class K18TrackU2D;
class K18TrackD2U;
class KuramaTrack;
class RawData;
class MWPCCluster;
class FiberCluster;
class HodoCluster;

class Hodo1Hit;
class Hodo2Hit;
class HodoAnalyzer;

typedef std::vector<DCHit*>        DCHitContainer;
typedef std::vector<MWPCCluster*>  MWPCClusterContainer;
typedef std::vector<DCLocalTrack*> DCLocalTrackContainer;
typedef std::vector<K18TrackU2D*>  K18TrackU2DContainer;
typedef std::vector<K18TrackD2U*>  K18TrackD2UContainer;
typedef std::vector<KuramaTrack*>  KuramaTrackContainer;

typedef std::vector<Hodo1Hit*> Hodo1HitContainer;
typedef std::vector<Hodo2Hit*> Hodo2HitContainer;
typedef std::vector<HodoCluster*> HodoClusterContainer;

//______________________________________________________________________________
class DCAnalyzer
{
public:
  DCAnalyzer( void );
  ~DCAnalyzer( void );

private:
  DCAnalyzer( const DCAnalyzer& );
  DCAnalyzer& operator =( const DCAnalyzer& );

private:
  enum e_type { k_BcIn,  k_BcOut,
		k_SdcIn, k_SdcOut,
		k_SsdIn, k_SsdOut,
		// k_SftIn, k_SftOut,
		k_TOF, n_type };
  std::vector<bool>     m_is_decoded;
  std::vector<int>      m_much_combi;
  std::vector<MWPCClusterContainer> m_MWPCClCont;
  std::vector<DCHitContainer>       m_TempBcInHC;
  std::vector<DCHitContainer>       m_BcInHC;
  std::vector<DCHitContainer>       m_BcOutHC;
  std::vector<DCHitContainer>       m_SdcInHC;
  std::vector<DCHitContainer>       m_SdcOutHC;
  DCHitContainer        m_TOFHC;
  DCHitContainer        m_VtxPoint;
  DCLocalTrackContainer m_BcInTC;
  DCLocalTrackContainer m_BcOutTC;
  DCLocalTrackContainer m_SdcInTC;
  DCLocalTrackContainer m_SdcOutTC;
  K18TrackU2DContainer  m_K18U2DTC;
  K18TrackD2UContainer  m_K18D2UTC;
  KuramaTrackContainer  m_KuramaTC;
  DCLocalTrackContainer m_BcOutSdcInTC;
  DCLocalTrackContainer m_SdcInSdcOutTC;
  // Exclusive Tracks
  std::vector<DCLocalTrackContainer> m_SdcInExTC;
  std::vector<DCLocalTrackContainer> m_SdcOutExTC;

public:
  int  MuchCombinationSdcIn( void ) const { return m_much_combi[k_SdcIn]; }
  bool DecodeRawHits( RawData* rawData );
  // bool DecodeFiberHits( FiberCluster* FiberCl, int layer );
  bool DecodeFiberHits( RawData* rawData );
  bool DecodeBcInHits( RawData* rawData );
  bool DecodeBcOutHits( RawData* rawData );
  bool DecodeSdcInHits( RawData* rawData );
  bool DecodeSdcOutHits( RawData* rawData, double ofs_dt=0.);
  bool DecodeTOFHits( const Hodo2HitContainer& HitCont );
  bool DecodeTOFHits( const HodoClusterContainer& ClCont );
  //bool DecodeSimuHits( SimuData *simuData );
  int  ClusterizeMWPCHit( const DCHitContainer& hits,
			  MWPCClusterContainer& clusters );

  inline const DCHitContainer& GetTempBcInHC( int layer ) const;
  inline const DCHitContainer& GetBcInHC( int layer ) const;
  inline const DCHitContainer& GetBcOutHC( int layer ) const;
  inline const DCHitContainer& GetSdcInHC( int layer ) const;
  inline const DCHitContainer& GetSdcOutHC( int layer ) const;
  inline const DCHitContainer& GetTOFHC( void ) const;

  bool TrackSearchBcIn( void );
  bool TrackSearchBcIn( const std::vector< std::vector<DCHitContainer> >& hc );
  bool TrackSearchBcOut( int T0Seg );
  bool TrackSearchBcOut( const std::vector< std::vector<DCHitContainer> >& hc, int T0Seg );
  bool TrackSearchSdcIn( void );
  bool TrackSearchSdcInFiber( void );
  bool TrackSearchSdcOut( void );
  bool TrackSearchSdcOut( const Hodo2HitContainer& HitCont );
  bool TrackSearchSdcOut( const HodoClusterContainer& ClCont );

  int GetNtracksBcIn( void )   const { return m_BcInTC.size(); }
  int GetNtracksBcOut( void )  const { return m_BcOutTC.size(); }
  int GetNtracksSdcIn( void )  const { return m_SdcInTC.size(); }
  int GetNtracksSdcOut( void ) const { return m_SdcOutTC.size(); }
  // Exclusive Tracks
  int GetNtracksSdcInEx( int layer ) const { return m_SdcInExTC[layer].size(); }
  int GetNtracksSdcOutEx( int layer ) const { return m_SdcOutExTC[layer].size(); }

  inline DCLocalTrack* GetTrackBcIn( int i ) const;
  inline DCLocalTrack* GetTrackBcOut( int i ) const;
  inline DCLocalTrack* GetTrackSdcIn( int i ) const;
  inline DCLocalTrack* GetTrackSdcOut( int i ) const;
  // Exclusive Tracks
  inline DCLocalTrack* GetTrackSdcInEx( int layer, int i ) const;
  inline DCLocalTrack* GetTrackSdcOutEx( int layer, int i ) const;

  bool TrackSearchK18U2D( void );
  bool TrackSearchK18D2U( const std::vector<double>& XinCont );
  bool TrackSearchKurama( double initial_momentum );
  bool TrackSearchKurama( void );

  void ChiSqrCutBcOut( double chisqr );
  void ChiSqrCutSdcIn( double chisqr );
  void ChiSqrCutSdcOut( double chisqr );

  void TotCutSDC2( double min_tot );
  void TotCutSDC3( double min_tot );

  void DriftTimeCutBC34( double min_dt, double max_dt);
  void DriftTimeCutSDC2( double min_dt, double max_dt);
  void DriftTimeCutSDC3( double min_dt, double max_dt);

  int GetNTracksK18U2D( void ) const { return m_K18U2DTC.size(); }
  int GetNTracksK18D2U( void ) const { return m_K18D2UTC.size(); }
  int GetNTracksKurama( void ) const { return m_KuramaTC.size(); }

  inline K18TrackU2D  * GetK18TrackU2D( int i ) const;
  inline K18TrackD2U  * GetK18TrackD2U( int i ) const;
  inline KuramaTrack  * GetKuramaTrack( int i )    const;

  int GetNClustersMWPC( int layer ) const { return m_MWPCClCont[layer].size(); };

  inline const MWPCClusterContainer & GetClusterMWPC( int layer ) const;

  void PrintKurama( const std::string& arg="" ) const;

  bool ReCalcMWPCHits( std::vector<DCHitContainer>& cont,
		       bool applyRecursively=false );
  bool ReCalcDCHits( std::vector<DCHitContainer>& cont,
		     bool applyRecursively=false );
  bool ReCalcDCHits( bool applyRecursively=false );

  bool ReCalcTrack( DCLocalTrackContainer& cont, bool applyRecursively=false );
  bool ReCalcTrack( K18TrackD2UContainer& cont, bool applyRecursively=false );
  bool ReCalcTrack( KuramaTrackContainer& cont, bool applyRecursively=false );

  bool ReCalcTrackBcIn( bool applyRecursively=false );
  bool ReCalcTrackBcOut( bool applyRecursively=false );
  bool ReCalcTrackSdcIn( bool applyRecursively=false );
  bool ReCalcTrackSdcOut( bool applyRecursively=false );

  bool ReCalcK18TrackD2U( bool applyRecursively=false );
  // bool ReCalcK18TrackU2D( bool applyRecursively=false );
  bool ReCalcKuramaTrack( bool applyRecursively=false );

  bool ReCalcAll( void );

  bool TrackSearchBcOutSdcIn( void );
  bool TrackSearchSdcInSdcOut( void );
  int GetNtracksBcOutSdcIn( void ) const { return m_BcOutSdcInTC.size(); }
  int GetNtracksSdcInSdcOut( void ) const { return m_SdcInSdcOutTC.size(); }
  inline DCLocalTrack * GetTrackBcOutSdcIn( int i ) const;
  inline DCLocalTrack * GetTrackSdcInSdcOut( int i ) const;

  bool MakeBH2DCHit(int t0seg);

protected:
  void ClearDCHits( void );
  void ClearBcInHits( void );
  void ClearBcOutHits( void );
  void ClearSdcInHits( void );
  void ClearSdcOutHits( void );

  // void ClearSftHits( void );
  void ClearTOFHits( void );
  void ClearVtxHits( void );
  void ClearTracksBcIn( void );
  void ClearTracksBcOut( void );
  void ClearTracksSdcIn( void );
  void ClearTracksSdcOut( void );
  void ClearTracksBcOutSdcIn( void );
  void ClearTracksSdcInSdcOut( void );
  void ClearK18TracksU2D( void );
  void ClearK18TracksD2U( void );
  void ClearKuramaTracks( void );
  void ChiSqrCut( DCLocalTrackContainer& cont, double chisqr );
  void TotCut( DCHitContainer& cont, double min_tot, bool adopt_nan );
  void DriftTimeCut( DCHitContainer& cont, double min_dt, double max_dt, bool select_1st );
  static int MakeUpMWPCClusters( const DCHitContainer& HitCont,
  				 MWPCClusterContainer& ClusterCont,
  				 double maxTimeDif );
public:
  void ResetTracksBcIn( void )        { ClearTracksBcIn();        }
  void ResetTracksBcOut( void )       { ClearTracksBcOut();       }
  void ResetTracksSdcIn( void )       { ClearTracksSdcIn();       }
  void ResetTracksSdcOut( void )      { ClearTracksSdcOut();      }
  void ResetTracksBcOutSdcIn( void )  { ClearTracksBcOutSdcIn();  }
  void ResetTracksSdcInSdcOut( void )  { ClearTracksSdcInSdcOut();  }
  void ApplyBh1SegmentCut(const std::vector<double>& validBh1Cluster);
  void ApplyBh2SegmentCut(const double Time0_Cluster);

};

//______________________________________________________________________________
inline const DCHitContainer&
DCAnalyzer::GetTempBcInHC( int layer ) const
{
  if( layer>NumOfLayersBcIn ) layer=0;
  return m_TempBcInHC[layer];
}

//______________________________________________________________________________
inline const DCHitContainer&
DCAnalyzer::GetBcInHC( int layer ) const
{
  if( layer>NumOfLayersBcIn ) layer=0;
  return m_BcInHC[layer];
}

//______________________________________________________________________________
inline const DCHitContainer&
DCAnalyzer::GetBcOutHC( int layer ) const
{
  if( layer>NumOfLayersBcOut+1 ) layer=0;
  return m_BcOutHC[layer];
}

//______________________________________________________________________________
inline const DCHitContainer&
DCAnalyzer::GetSdcInHC( int layer ) const
{
  if( layer>NumOfLayersSdcIn ) layer=0;
  return m_SdcInHC[layer];
}

//______________________________________________________________________________
inline const DCHitContainer&
DCAnalyzer::GetSdcOutHC( int layer ) const
{
  if( layer>NumOfLayersSdcOut ) layer=0;
  return m_SdcOutHC[layer];
}

//______________________________________________________________________________
inline const DCHitContainer&
DCAnalyzer::GetTOFHC( void ) const
{
  return m_TOFHC;
}

//______________________________________________________________________________
inline DCLocalTrack*
DCAnalyzer::GetTrackBcIn( int i ) const
{
  if( i<m_BcInTC.size() )
    return m_BcInTC[i];
  else
    return 0;
}

//______________________________________________________________________________
inline DCLocalTrack*
DCAnalyzer::GetTrackBcOut( int i ) const
{
  if( i<m_BcOutTC.size() )
    return m_BcOutTC[i];
  else
    return 0;
}

//______________________________________________________________________________
inline DCLocalTrack*
DCAnalyzer::GetTrackSdcIn( int i ) const
{
  if( i<m_SdcInTC.size() )
    return m_SdcInTC[i];
  else
    return 0;
}

//______________________________________________________________________________
inline DCLocalTrack*
DCAnalyzer::GetTrackSdcOut( int i ) const
{
  if( i<m_SdcOutTC.size() )
    return m_SdcOutTC[i];
  else
    return 0;
}

//______________________________________________________________________________
inline DCLocalTrack*
DCAnalyzer::GetTrackSdcInEx( int layer, int i ) const
{
  if( i<m_SdcInExTC[layer].size() )
    return m_SdcInExTC[layer][i];
  else
    return 0;
}

//______________________________________________________________________________
inline DCLocalTrack*
DCAnalyzer::GetTrackSdcOutEx( int layer, int i ) const
{
  if( i<m_SdcOutExTC[layer].size() )
    return m_SdcOutExTC[layer][i];
  else
    return 0;
}

//______________________________________________________________________________
inline K18TrackU2D*
DCAnalyzer::GetK18TrackU2D( int i ) const
{
  if( i<m_K18U2DTC.size() )
    return m_K18U2DTC[i];
  else
    return 0;
}

//______________________________________________________________________________
inline K18TrackD2U*
DCAnalyzer::GetK18TrackD2U( int i ) const
{
  if( i<m_K18D2UTC.size() )
    return m_K18D2UTC[i];
  else
    return 0;
}

//______________________________________________________________________________
inline KuramaTrack*
DCAnalyzer::GetKuramaTrack( int i ) const
{
  if( i<m_KuramaTC.size() )
    return m_KuramaTC[i];
  else
    return 0;
}

//______________________________________________________________________________
inline DCLocalTrack*
DCAnalyzer::GetTrackBcOutSdcIn( int i ) const
{
  if( i<m_BcOutSdcInTC.size() )
    return m_BcOutSdcInTC[i];
  else
    return 0;
}

//______________________________________________________________________________
inline DCLocalTrack*
DCAnalyzer::GetTrackSdcInSdcOut( int i ) const
{
  if( i<m_SdcInSdcOutTC.size() )
    return m_SdcInSdcOutTC[i];
  else
    return 0;
}

//______________________________________________________________________________
inline const MWPCClusterContainer&
DCAnalyzer::GetClusterMWPC( int layer ) const
{
  if( layer>NumOfLayersBcIn ) layer=0;
  return m_MWPCClCont[layer];
}

#endif
