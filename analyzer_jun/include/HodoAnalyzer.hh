/**
 *  file: HodoAnalyzer.hh
 *  date: 2017.04.10
 *
 */

#ifndef HODO_ANALYZER_HH
#define HODO_ANALYZER_HH

#include <vector>

#include "DetectorID.hh"
#include "RawData.hh"

class RawData;
class Hodo1Hit;
class Hodo2Hit;
class BH2Hit;
class FiberHit;
class FLHit;
class HodoCluster;
class BH2Cluster;
class FiberCluster;

typedef std::vector <Hodo1Hit*> Hodo1HitContainer;
typedef std::vector <Hodo2Hit*> Hodo2HitContainer;
typedef std::vector <BH2Hit*>   BH2HitContainer;
typedef std::vector <FiberHit*> FiberHitContainer;
typedef std::vector < std::vector< FiberHit*> > MultiPlaneFiberHitContainer;
typedef std::vector <FLHit*>    FLHitContainer;

typedef std::vector <HodoCluster*>  HodoClusterContainer;
typedef std::vector <BH2Cluster*>   BH2ClusterContainer;
typedef std::vector <FiberCluster*> FiberClusterContainer;
typedef std::vector < std::vector< FiberCluster*> > MultiPlaneFiberClusterContainer;

//______________________________________________________________________________
class HodoAnalyzer
{
public:
  HodoAnalyzer( void );
  ~HodoAnalyzer( void );

  static HodoAnalyzer& GetInstance( void );

private:
  HodoAnalyzer( const HodoAnalyzer& );
  HodoAnalyzer& operator =( const HodoAnalyzer& );

private:
  Hodo2HitContainer     m_BH1Cont;
  BH2HitContainer       m_BH2Cont;
  Hodo1HitContainer     m_SACCont;
  Hodo2HitContainer     m_TOFCont;
  Hodo1HitContainer     m_HtTOFCont;
  Hodo1HitContainer     m_LCCont;
  MultiPlaneFiberHitContainer m_BFTCont;
  FiberHitContainer     m_SCHCont;
  MultiPlaneFiberHitContainer m_SFTCont;
  MultiPlaneFiberHitContainer m_FBT1UCont;
  MultiPlaneFiberHitContainer m_FBT1DCont;
  MultiPlaneFiberHitContainer m_FBT2UCont;
  MultiPlaneFiberHitContainer m_FBT2DCont;

  HodoClusterContainer  m_BH1ClCont;
  BH2ClusterContainer   m_BH2ClCont;
  HodoClusterContainer  m_SACClCont;
  HodoClusterContainer  m_TOFClCont;
  HodoClusterContainer  m_HtTOFClCont;
  HodoClusterContainer  m_LCClCont;
  FiberClusterContainer m_BFTClCont;
  FiberClusterContainer m_SCHClCont;
  MultiPlaneFiberClusterContainer m_SFTClCont;
  MultiPlaneFiberClusterContainer m_FBT1UClCont;
  MultiPlaneFiberClusterContainer m_FBT1DClCont;
  MultiPlaneFiberClusterContainer m_FBT2UClCont;
  MultiPlaneFiberClusterContainer m_FBT2DClCont;

public:
  bool DecodeRawHits( RawData* rawData );
  bool DecodeBH1Hits( RawData* rawData );
  bool DecodeBH2Hits( RawData* rawData );
  bool DecodeSACHits( RawData* rawData );
  bool DecodeTOFHits( RawData* rawData );
  bool DecodeHtTOFHits( RawData* rawData );
  bool DecodeLCHits( RawData* rawData );
  bool DecodeBFTHits( RawData* rawData );
  bool DecodeSFTHits( RawData* rawData );
  bool DecodeSCHHits( RawData* rawData );
  bool DecodeFBT1Hits( RawData* rawData );
  bool DecodeFBT2Hits( RawData* rawData );
  int  GetNHitsBH1( void )  const { return m_BH1Cont.size();  };
  int  GetNHitsBH2( void )  const { return m_BH2Cont.size();  };
  int  GetNHitsSAC( void )  const { return m_SACCont.size();  };
  int  GetNHitsTOF( void )  const { return m_TOFCont.size();  };
  int  GetNHitsHtTOF( void )const { return m_HtTOFCont.size();  };
  int  GetNHitsLC( void )   const { return m_LCCont.size();  };
  int  GetNHitsBFT( int plane)  const { return m_BFTCont.at( plane ).size(); };
  int  GetNHitsSFT( int plane ) const { return m_SFTCont.at( plane ).size(); };
  int  GetNHitsSCH( void )  const { return m_SCHCont.size();  };
  int  GetNHitsFBT1( int layer, int UorD)  const 
  { return UorD==0? m_FBT1UCont.size() : m_FBT1DCont.size();}
  int  GetNHitsFBT2( int layer, int UorD)  const
  { return UorD==0? m_FBT2UCont.size() : m_FBT2DCont.size();}

  inline Hodo2Hit * GetHitBH1( std::size_t i )  const;
  inline BH2Hit   * GetHitBH2( std::size_t i )  const;
  inline Hodo1Hit * GetHitSAC( std::size_t i )  const;
  inline Hodo2Hit * GetHitTOF( std::size_t i )  const;
  inline Hodo1Hit * GetHitHtTOF( std::size_t i )const;
  inline Hodo1Hit * GetHitLC( std::size_t i )   const;
  inline FiberHit * GetHitBFT( int plane, std::size_t seg ) const;
  inline FiberHit * GetHitSFT( int plane, std::size_t seg ) const;
  inline FiberHit * GetHitSCH( std::size_t seg ) const;
  inline FiberHit * GetHitFBT1( int layer, int UorD, std::size_t seg ) const;
  inline FiberHit * GetHitFBT2( int layer, int UorD, std::size_t seg ) const;

  int GetNClustersBH1( void ) const { return m_BH1ClCont.size(); };
  int GetNClustersBH2( void ) const { return m_BH2ClCont.size(); };
  int GetNClustersTOF( void ) const { return m_TOFClCont.size(); }
  int GetNClustersHtTOF( void )const{ return m_HtTOFClCont.size(); }
  int GetNClustersLC( void )  const { return m_LCClCont.size(); }
  int GetNClustersSAC( void ) const { return m_SACClCont.size(); }
  int GetNClustersBFT( void ) const { return m_BFTClCont.size(); };
  int GetNClustersSFT( int layer ) const { return m_SFTClCont.at( layer ).size(); };
  int GetNClustersSCH( void ) const { return m_SCHClCont.size(); };
  int  GetNClustersFBT1( int layer, int UorD)  const 
  { return UorD==0? m_FBT1UClCont.at(layer).size() : m_FBT1DClCont.at(layer).size();}
  int  GetNClustersFBT2( int layer, int UorD)  const
  { return UorD==0? m_FBT2UClCont.at(layer).size() : m_FBT2DClCont.at(layer).size();}

  inline HodoCluster  * GetClusterBH1( std::size_t i ) const;
  inline BH2Cluster   * GetClusterBH2( std::size_t i ) const;
  inline HodoCluster  * GetClusterTOF( std::size_t i ) const;
  inline HodoCluster  * GetClusterHtTOF( std::size_t i ) const;
  inline HodoCluster  * GetClusterLC( std::size_t i ) const;
  inline HodoCluster  * GetClusterSAC( std::size_t i ) const;
  inline FiberCluster * GetClusterBFT( std::size_t i ) const;
  inline FiberCluster * GetClusterSFT( int layer, std::size_t i ) const;
  inline FiberCluster * GetClusterSCH( std::size_t i ) const;
  inline FiberCluster * GetClusterFBT1( int layer, int UorD, std::size_t i ) const;
  inline FiberCluster * GetClusterFBT2( int layer, int UorD, std::size_t i ) const;

  bool ReCalcBH1Hits( bool applyRecursively=false );
  bool ReCalcBH2Hits( bool applyRecursively=false );
  bool ReCalcSACHits( bool applyRecursively=false );
  bool ReCalcTOFHits( bool applyRecursively=false );
  bool ReCalcHtTOFHits( bool applyRecursively=false );
  bool ReCalcLCHits( bool applyRecursively=false );
  bool ReCalcBH1Clusters( bool applyRecursively=false );
  bool ReCalcBH2Clusters( bool applyRecursively=false );
  bool ReCalcTOFClusters( bool applyRecursively=false );
  bool ReCalcHtTOFClusters( bool applyRecursively=false );
  bool ReCalcLCClusters( bool applyRecursively=false );
  bool ReCalcFBT1Clusters( bool applyRecursively=false );
  bool ReCalcFBT2Clusters( bool applyRecursively=false );
  bool ReCalcAll( void );

  void TimeCutBH1(double tmin, double tmax);
  void TimeCutBH2(double tmin, double tmax);
  void TimeCutTOF(double tmin, double tmax);
  void TimeCutBFT(double tmin, double tmax);
  void TimeCutSFT( int layer, double tmin, double tmax );
  void TimeCutSCH(double tmin, double tmax);
  void TimeCutFBT1( int layer, int UorD, double tmin, double tmax );
  void TimeCutFBT2( int layer, int UorD, double tmin, double tmax );

  void WidthCutBFT(double min_width, double max_width);
  void WidthCutSFT( int layer, double min_width, double max_width);
  void WidthCutSCH(double min_width, double max_width);
  void WidthCutFBT1( int layer, int UorD, double min_width, double max_width);
  void WidthCutFBT2( int layer, int UorD, double min_width, double max_width);

  BH2Cluster*  GetTime0BH2Cluster();
  HodoCluster* GetBtof0BH1Cluster(double time0);

private:
  void ClearBH1Hits( void );
  void ClearBH2Hits( void );
  void ClearSACHits( void );
  void ClearTOFHits( void );
  void ClearHtTOFHits( void );
  void ClearLCHits( void );
  void ClearBFTHits();
  void ClearSFTHits();
  void ClearSCHHits();
  void ClearFBT1Hits();
  void ClearFBT2Hits();

  template<typename TypeCluster>
  void TimeCut(std::vector<TypeCluster>& cont, double tmin, double tmax);

  template<typename TypeCluster>
  void WidthCut(std::vector<TypeCluster>& cont, double min_width, double max_width, bool adopt_nan);

  static int MakeUpClusters( const Hodo1HitContainer& HitCont,
			     HodoClusterContainer& ClusterCont,
			     double maxTimeDif );

  static int MakeUpClusters( const Hodo2HitContainer& HitCont,
			     HodoClusterContainer& ClusterCont,
			     double maxTimeDif );

  static int MakeUpClusters( const BH2HitContainer& HitCont,
			     BH2ClusterContainer& ClusterCont,
			     double maxTimeDif );

  static int MakeUpClusters( const FiberHitContainer& cont,
			     FiberClusterContainer& ClusterCont,
			     double maxTimeDif,
			     int DifPairId);

  static int MakeUpClusters( const FLHitContainer& cont,
			     FiberClusterContainer& ClusterCont,
			     double maxTimeDif,
			     int DifPairId);

  static int MakeUpCoincidence( const FiberHitContainer& cont,
				FLHitContainer& CoinCont,
				double maxTimeDif);
};

//______________________________________________________________________________
inline HodoCluster*
HodoAnalyzer::GetClusterBH1( std::size_t i ) const
{
  if( i<m_BH1ClCont.size() )
    return m_BH1ClCont[i];
  else
    return 0;
}

//______________________________________________________________________________
inline BH2Cluster*
HodoAnalyzer::GetClusterBH2( std::size_t i ) const
{
  if( i<m_BH2ClCont.size() )
    return m_BH2ClCont[i];
  else
    return 0;
}

//______________________________________________________________________________
inline HodoCluster*
HodoAnalyzer::GetClusterSAC( std::size_t i ) const
{
  if( i<m_SACClCont.size() )
    return m_SACClCont[i];
  else
    return 0;
}

//______________________________________________________________________________
inline HodoCluster*
HodoAnalyzer::GetClusterTOF( std::size_t i ) const
{
  if( i<m_TOFClCont.size() )
    return m_TOFClCont[i];
  else
    return 0;
}

//______________________________________________________________________________
inline HodoCluster*
HodoAnalyzer::GetClusterHtTOF( std::size_t i ) const
{
  if( i<m_HtTOFClCont.size() )
    return m_HtTOFClCont[i];
  else
    return 0;
}

//______________________________________________________________________________
inline HodoCluster*
HodoAnalyzer::GetClusterLC( std::size_t i ) const
{
  if( i<m_LCClCont.size() )
    return m_LCClCont[i];
  else
    return 0;
}

//______________________________________________________________________________
inline FiberCluster*
HodoAnalyzer::GetClusterBFT( std::size_t i ) const
{
  if( i<m_BFTClCont.size() )
    return m_BFTClCont[i];
  else
    return 0;
}

//______________________________________________________________________________
inline FiberCluster*
HodoAnalyzer::GetClusterSFT( int layer, std::size_t i ) const
{
  if( i<m_SFTClCont.at( layer ).size() )
    return m_SFTClCont.at( layer ).at( i );
  else
    return 0;
}

//______________________________________________________________________________
inline FiberCluster*
HodoAnalyzer::GetClusterSCH( std::size_t i ) const
{
  if( i<m_SCHClCont.size() )
    return m_SCHClCont[i];
  else
    return 0;
}

//______________________________________________________________________________
inline FiberCluster*
HodoAnalyzer::GetClusterFBT1( int layer, int UorD, std::size_t seg ) const
{
  if(!(0 <= UorD && UorD <=1)) return NULL;

  if(UorD==0){
    if( seg<m_FBT1UClCont.at( layer ).size() ) return m_FBT1UClCont.at( layer ).at( seg );
    else return NULL;    
  }else{
    if( seg<m_FBT1DClCont.at( layer ).size() ) return m_FBT1DClCont.at( layer ).at( seg );
    else return NULL;    
  }
}

//______________________________________________________________________________
inline FiberCluster*
HodoAnalyzer::GetClusterFBT2( int layer, int UorD, std::size_t seg ) const
{
  if(!(0 <= UorD && UorD <=1)) return NULL;

  if(UorD==0){
    if( seg<m_FBT2UClCont.at( layer ).size() ) return m_FBT2UClCont.at( layer ).at( seg );
    else return NULL;    
  }else{
    if( seg<m_FBT2DClCont.at( layer ).size() ) return m_FBT2DClCont.at( layer ).at( seg );
    else return NULL;    
  }
}

//______________________________________________________________________________
inline Hodo2Hit*
HodoAnalyzer::GetHitBH1( std::size_t i ) const
{
  if( i<m_BH1Cont.size() )
    return m_BH1Cont[i];
  else
    return 0;
}

//______________________________________________________________________________
inline BH2Hit*
HodoAnalyzer::GetHitBH2( std::size_t i ) const
{
  if( i<m_BH2Cont.size() )
    return m_BH2Cont[i];
  else
    return 0;
}

//______________________________________________________________________________
inline Hodo1Hit*
HodoAnalyzer::GetHitSAC( std::size_t i ) const
{
  if( i<m_SACCont.size() )
    return m_SACCont[i];
  else
    return 0;
}

//______________________________________________________________________________
inline Hodo2Hit*
HodoAnalyzer::GetHitTOF( std::size_t i ) const
{
  if( i<m_TOFCont.size() )
    return m_TOFCont[i];
  else
    return 0;
}

//______________________________________________________________________________
inline Hodo1Hit*
HodoAnalyzer::GetHitHtTOF( std::size_t i ) const
{
  if( i<m_HtTOFCont.size() )
    return m_HtTOFCont[i];
  else
    return 0;
}

//______________________________________________________________________________
inline Hodo1Hit*
HodoAnalyzer::GetHitLC( std::size_t i ) const
{
  if( i<m_LCCont.size() )
    return m_LCCont[i];
  else
    return 0;
}

//______________________________________________________________________________
inline FiberHit*
HodoAnalyzer::GetHitBFT( int plane, std::size_t seg ) const
{
  if( seg<m_BFTCont.at(plane).size() )
    return m_BFTCont.at(plane).at(seg);
  else
    return NULL;
}

//______________________________________________________________________________
inline FiberHit*
HodoAnalyzer::GetHitSFT( int plane, std::size_t seg ) const
{
  if( seg<m_SFTCont.at( plane ).size() )
    return m_SFTCont.at( plane ).at( seg );
  else
    return NULL;
}

//______________________________________________________________________________
inline FiberHit*
HodoAnalyzer::GetHitSCH( std::size_t seg ) const
{
  if( seg<m_SCHCont.size() )
    return m_SCHCont[seg];
  else
    return NULL;
}

//______________________________________________________________________________
inline FiberHit*
HodoAnalyzer::GetHitFBT1( int layer, int UorD, std::size_t seg ) const
{
  if(!(0 <= UorD && UorD <=1)) return NULL;

  if(UorD==0){
    if( seg<m_FBT1UCont.at( layer ).size() ) return m_FBT1UCont.at( layer ).at( seg );
    else return NULL;    
  }else{
    if( seg<m_FBT1DCont.at( layer ).size() ) return m_FBT1DCont.at( layer ).at( seg );
    else return NULL;    
  }
}

//______________________________________________________________________________
inline FiberHit*
HodoAnalyzer::GetHitFBT2( int layer, int UorD, std::size_t seg ) const
{
  if(!(0 <= UorD && UorD <=1)) return NULL;

  if(UorD==0){
    if( seg<m_FBT2UCont.at( layer ).size() ) return m_FBT2UCont.at( layer ).at( seg );
    else return NULL;    
  }else{
    if( seg<m_FBT2DCont.at( layer ).size() ) return m_FBT2DCont.at( layer ).at( seg );
    else return NULL;    
  }
}

inline HodoAnalyzer&
HodoAnalyzer::GetInstance( void )
{
    static HodoAnalyzer g_instance;
    return g_instance;
}
#endif
