/**
 *  file: UserKuramaTracking.cc
 *  date: 2017.04.10
 *
 */

#include <iostream>
#include <sstream>
#include <cmath>
#include <string>
#include <iomanip>

#include "ConfMan.hh"
#include "DatabasePDG.hh"
#include "DCRawHit.hh"
#include "DebugTimer.hh"
#include "DetectorID.hh"
#include "RMAnalyzer.hh"
#include "KuramaLib.hh"
#include "MathTools.hh"
#include "RawData.hh"
#include "RootHelper.hh"
#include "UnpackerManager.hh"
#include "VEvent.hh"

#define HodoCut 0
#define UseTOF  1

namespace
{
  using namespace root;
  const std::string& classname("KuramaTracking");
  const DCGeomMan&    gGeom = DCGeomMan::GetInstance();
  RMAnalyzer&         gRM   = RMAnalyzer::GetInstance();
  const UserParamMan& gUser = UserParamMan::GetInstance();
  const hddaq::unpacker::UnpackerManager& gUnpacker
  = hddaq::unpacker::GUnpacker::get_instance();
  const double& zTOF = gGeom.LocalZ("TOF");
}

//______________________________________________________________________________
VEvent::VEvent( void )
{
}

//______________________________________________________________________________
VEvent::~VEvent( void )
{
}

//______________________________________________________________________________
class EventKuramaTracking : public VEvent
{
private:
  RawData      *rawData;
  DCAnalyzer   *DCAna;
  HodoAnalyzer *hodoAna;

public:
        EventKuramaTracking( void );
       ~EventKuramaTracking( void );
  bool  ProcessingBegin( void );
  bool  ProcessingEnd( void );
  bool  ProcessingNormal( void );
  bool  InitializeHistograms( void );
  void  InitializeEvent( void );
};

//______________________________________________________________________________
EventKuramaTracking::EventKuramaTracking( void )
  : VEvent(),
    rawData(0),
    DCAna( new DCAnalyzer ),
    hodoAna( new HodoAnalyzer )
{
}

//______________________________________________________________________________
EventKuramaTracking::~EventKuramaTracking( void )
{
  if( DCAna )   delete DCAna;
  if( hodoAna ) delete hodoAna;
  if( rawData ) delete rawData;
}

//______________________________________________________________________________
struct Event
{
  int evnum;

  int trignhits;
  int trigpat[NumOfSegTrig];
  int trigflag[NumOfSegTrig];

  double btof;
  double time0;

  int nhBh2;
  double Bh2Seg[MaxHits];
  double tBh2[MaxHits];
  double t0Bh2[MaxHits];
  double deBh2[MaxHits];

  int nhBh1;
  double Bh1Seg[MaxHits];
  double tBh1[MaxHits];
  double deBh1[MaxHits];

  int nhSac;
  int nhSac_khodo;
  double SacSeg[MaxHits];
  double tSac[MaxHits];
  double tSac_khodo[NumOfSegSAC*MaxDepth];
  double deSac[MaxHits];

  int nhTof;
  double TofSeg[MaxHits];
  double tTof[MaxHits];
  double dtTof[MaxHits];
  double deTof[MaxHits];

  int ntSdcIn;
  int much; // debug
  int nlSdcIn;
  int nhSdcIn[MaxHits];
  double wposSdcIn[NumOfLayersSdcIn];
  double chisqrSdcIn[MaxHits];
  double u0SdcIn[MaxHits];
  double v0SdcIn[MaxHits];
  double x0SdcIn[MaxHits];
  double y0SdcIn[MaxHits];

  int ntSdcOut;
  int nlSdcOut;
  int nhSdcOut[MaxHits];
  double wposSdcOut[NumOfLayersSdcOut];
  double chisqrSdcOut[MaxHits];
  double u0SdcOut[MaxHits];
  double v0SdcOut[MaxHits];
  double x0SdcOut[MaxHits];
  double y0SdcOut[MaxHits];

  int ntKurama;
  int nlKurama;
  int nhKurama[MaxHits];
  double chisqrKurama[MaxHits];
  double path[MaxHits];
  double stof[MaxHits];
  double pKurama[MaxHits];
  double qKurama[MaxHits];
  double m2[MaxHits];
  double resP[MaxHits];
  double vpx[NumOfLayersVP];
  double vpy[NumOfLayersVP];
  double vpseg[NumOfLayersVP];

  double xtgtKurama[MaxHits];
  double ytgtKurama[MaxHits];
  double utgtKurama[MaxHits];
  double vtgtKurama[MaxHits];
  double thetaKurama[MaxHits];
  double phiKurama[MaxHits];

  double xtofKurama[MaxHits];
  double ytofKurama[MaxHits];
  double utofKurama[MaxHits];
  double vtofKurama[MaxHits];
  double tofsegKurama[MaxHits];

  std::vector< std::vector<double> > resL;
  std::vector< std::vector<double> > resG;

  double xsacKurama[MaxHits];
  double ysacKurama[MaxHits];

  // Calib
  enum eParticle { Pion, Kaon, Proton, nParticle };
  double tTofCalc[nParticle];
  double utTofSeg[NumOfSegTOF];
  double dtTofSeg[NumOfSegTOF];
  double udeTofSeg[NumOfSegTOF];
  double ddeTofSeg[NumOfSegTOF];
  double tofua[NumOfSegTOF];
  double tofda[NumOfSegTOF];

};

//______________________________________________________________________________
namespace root
{
  Event  event;
  TH1   *h[MaxHist];
  TTree *tree;
}


//______________________________________________________________________________
bool
EventKuramaTracking::ProcessingBegin( void )
{
  InitializeEvent();
  return true;
}

//______________________________________________________________________________
bool
EventKuramaTracking::ProcessingNormal( void )
{
  static const std::string func_name("["+classname+"::"+__func__+"]");

#if HodoCut
  static const double MinDeBH2   = gUser.GetParameter("DeBH2", 0);
  static const double MaxDeBH2   = gUser.GetParameter("DeBH2", 1);
  static const double MinDeBH1   = gUser.GetParameter("DeBH1", 0);
  static const double MaxDeBH1   = gUser.GetParameter("DeBH1", 1);
  static const double MinBeamToF = gUser.GetParameter("BTOF",  1);
  static const double MaxBeamToF = gUser.GetParameter("BTOF",  1);
  static const double MinDeTOF   = gUser.GetParameter("DeTOF",      0);
  static const double MaxDeTOF   = gUser.GetParameter("DeTOF",      1);
  static const double MinTimeTOF = gUser.GetParameter("TimeTOF",    0);
  static const double MaxTimeTOF = gUser.GetParameter("TimeTOF",    1);
#endif

  static const double MinTimeL1  = gUser.GetParameter("TimeL1",     0);
  static const double MaxTimeL1  = gUser.GetParameter("TimeL1",     1);
  static const double dTOfs      = gUser.GetParameter("dTOfs",      0);
  static const double MinTotSDC2 = gUser.GetParameter("MinTotSDC2", 0);
  static const double MinTotSDC3 = gUser.GetParameter("MinTotSDC3", 0);

  static const double MaxMultiHitSdcIn  = gUser.GetParameter("MaxMultiHitSdcIn");
  static const double MaxMultiHitSdcOut = gUser.GetParameter("MaxMultiHitSdcOut");

  static const double OffsetToF = gUser.GetParameter("OffsetToF");

  rawData = new RawData;
  rawData->DecodeHits();

  gRM.Decode();

  event.evnum = gRM.EventNumber();

  //TrigFlag
  {
    const HodoRHitContainer &cont=rawData->GetTrigRawHC();
    int trignhits = 0;
    int nh=cont.size();
    for( int i=0; i<nh; ++i ){
      HodoRawHit *hit=cont[i];
      int seg = hit->SegmentId()+1;
      int tdc = hit->GetTdc1();
      if( tdc ){
	event.trigpat[trignhits++] = seg;
	event.trigflag[seg-1]      = tdc;
      }
    }
    event.trignhits = trignhits;
  }

  HF1( 1, 0. );

  // if( event.trigflag[SpillEndFlag] ) return true;

  HF1( 1, 1. );

  //////////////BH2 Analysis
  hodoAna->DecodeBH2Hits(rawData);
  int nhBh2 = hodoAna->GetNHitsBH2();
  event.nhBh2 = nhBh2;
#if HodoCut
  if( nhBh2==0 ) return true;
#endif
  double time0 = -999.;
  //////////////BH2 Analysis
  double min_time = -999.;
  for( int i=0; i<nhBh2; ++i ){
    BH2Hit *hit = hodoAna->GetHitBH2(i);
    if(!hit) continue;
    double seg = hit->SegmentId()+1;
    double mt  = hit->MeanTime();
    double cmt = hit->CMeanTime();
    double ct0 = hit->CTime0();
    double de  = hit->DeltaE();
#if HodoCut
    if( de<MinDeBH2 || MaxDeBH2<de ) continue;
#endif
    event.tBh2[i]   = cmt;
    event.t0Bh2[i]  = ct0;
    event.deBh2[i]  = de;
    event.Bh2Seg[i] = seg;
    if( std::abs(mt)<std::abs(min_time) ){
      min_time = mt;
      time0    = ct0;
    }
  }
  event.time0 = time0;

  //////////////BH1 Analysis
  hodoAna->DecodeBH1Hits(rawData);
  int nhBh1 = hodoAna->GetNHitsBH1();
  event.nhBh1 = nhBh1;
#if HodoCut
  if( nhBh1==0 ) return true;
#endif

  HF1( 1, 2. );

  double btof0 = -999.;
  for(int i=0; i<nhBh1; ++i){
    Hodo2Hit *hit = hodoAna->GetHitBH1(i);
    if(!hit) continue;
    int    seg  = hit->SegmentId()+1;
    double cmt  = hit->CMeanTime();
    double dE   = hit->DeltaE();
    double btof = cmt - time0;
#if HodoCut
    if( dE<MinDeBH1 || MaxDeBH1<dE ) continue;
    if( btof<MinBeamToF && MaxBeamToF<btof ) continue;
#endif
    event.Bh1Seg[i] = seg;
    event.tBh1[i]   = cmt;
    event.deBh1[i]  = dE;
    if( std::abs(btof)<std::abs(btof0) ){
      btof0 = btof;
    }
  }

  event.btof = btof0;

  //////////////SAC
  hodoAna->DecodeSACHits(rawData);
  int nhSac = hodoAna->GetNHitsSAC();
  event.nhSac = nhSac;
  for(int i=0; i<nhSac; ++i){
    Hodo1Hit *hit = hodoAna->GetHitSAC(i);
    if(!hit) continue;
    int    seg  = hit->SegmentId()+1;
    double cmt  = hit->CTime();
    double dE   = hit->DeltaE();
    event.SacSeg[i] = seg;
    event.tSac[i]   = cmt;
    event.deSac[i]  = dE;
  }
  {
    int nc = hodoAna->GetNClustersSAC();
    event.nhSac_khodo = nc;
    for( int i=0; i<nc; ++i ){
      HodoCluster *cl = hodoAna->GetClusterSAC(i);
      if( !cl ) continue;
      event.tSac_khodo[i]   = cl->CMeanTime();
    }
  }


  HF1( 1, 3. );

  HodoClusterContainer TOFCont;
  //////////////Tof Analysis
  hodoAna->DecodeTOFHits( rawData );
  //hodoAna->TimeCutTOF(7, 25);
  int nhTof = hodoAna->GetNClustersTOF();
  event.nhTof = nhTof;
  {
#if HodoCut
    int nhOk = 0;
#endif
    for( int i=0; i<nhTof; ++i ){
      HodoCluster *hit = hodoAna->GetClusterTOF(i);
      double seg = hit->MeanSeg()+1;
      double cmt = hit->CMeanTime();
      double dt  = hit->TimeDif();
      double de   = hit->DeltaE();
      event.TofSeg[i] = seg;
      event.tTof[i]   = cmt;//stof;
      event.dtTof[i]  = dt;
      event.deTof[i]  = de;
      // for PHC
      // HF2( 100*seg+30000+81, ua, stof );
      // HF2( 100*seg+30000+82, da, stof );
      // HF2( 100*seg+30000+83, ua, (time0-OffsetTof)-ut );
      // HF2( 100*seg+30000+84, da, (time0-OffsetTof)-dt );
      TOFCont.push_back( hit );
#if HodoCut
      if( MinDeTOF<de  && de<MaxDeTOF  &&
	  MinTimeTOF<stof && stof<MaxTimeTOF ){
	++nhOk;
      }
#endif
    }

#if HodoCut
    if( nhOk<1 ) return true;
#endif
  }

  HF1( 1, 4. );

  // Trigger flag
  bool flag_tof_stop = false;
  {
    static const int device_id    = gUnpacker.get_device_id("TFlag");
    static const int data_type_id = gUnpacker.get_data_id("TFlag", "tdc");

    int mhit = gUnpacker.get_entries(device_id, 0, kTofTiming, 0, data_type_id);
    for(int m = 0; m<mhit; ++m){
      int tof_timing = gUnpacker.get(device_id, 0, kTofTiming, 0, data_type_id, m);
      if(!(MinTimeL1 < tof_timing && tof_timing < MaxTimeL1)) flag_tof_stop = true;
    }// for(m)
  }

  HF1( 1, 6. );

  HF1( 1, 10. );

  DCAna->DecodeSdcInHits( rawData );

  double offset = flag_tof_stop ? 0 : dTOfs;
  DCAna->DecodeSdcOutHits( rawData, offset );
  DCAna->TotCutSDC2( MinTotSDC2 );
  DCAna->TotCutSDC3( MinTotSDC3 );

  double multi_SdcIn  = 0.;
  ////////////// SdcIn number of hit layer
  {
    int nlSdcIn = 0;
    for( int layer=1; layer<=NumOfLayersSdcIn; ++layer ){
      const DCHitContainer &contSdcIn =DCAna->GetSdcInHC(layer);
      int nhSdcIn = contSdcIn.size();
      if( nhSdcIn==1 ){
	DCHit *hit = contSdcIn[0];
	double wpos = hit->GetWirePosition();
	event.wposSdcIn[layer-1] = wpos;
      }
      multi_SdcIn += double(nhSdcIn);
      if( nhSdcIn>0 ) nlSdcIn++;
    }
    event.nlSdcIn   = nlSdcIn;
    event.nlKurama += nlSdcIn;
  }
  if( multi_SdcIn/double(NumOfLayersSdcIn) > MaxMultiHitSdcIn ){
    // return true;
  }

  double multi_SdcOut = 0.;
  ////////////// SdcOut number of hit layer
  {
    int nlSdcOut = 0;
    for( int layer=1; layer<=NumOfLayersSdcOut; ++layer ){
      const DCHitContainer &contSdcOut =DCAna->GetSdcOutHC(layer);
      int nhSdcOut=contSdcOut.size();
      if( nhSdcOut==1 ){
	DCHit *hit = contSdcOut[0];
	double wpos = hit->GetWirePosition();
	event.wposSdcOut[layer-1] = wpos;
      }
      multi_SdcOut += double(nhSdcOut);
      if( nhSdcOut>0 ) nlSdcOut++;
    }
    event.nlSdcOut = nlSdcOut;
    event.nlKurama += nlSdcOut;
  }
  if( multi_SdcOut/double(NumOfLayersSdcOut) > MaxMultiHitSdcOut ){
    // return true;
  }

  HF1( 1, 11. );


  // std::cout << "==========TrackSearch SdcIn============" << std::endl;
  DCAna->TrackSearchSdcIn();
  DCAna->ChiSqrCutSdcIn(50.);  
  int ntSdcIn = DCAna->GetNtracksSdcIn();
  if( MaxHits<ntSdcIn ){
    std::cout << "#W " << func_name << " "
	      << "too many ntSdcIn " << ntSdcIn << "/" << MaxHits << std::endl;
    ntSdcIn = MaxHits;
  }
  event.ntSdcIn = ntSdcIn;
  HF1( 10, double(ntSdcIn) );
  int much_combi = DCAna->MuchCombinationSdcIn();
  event.much = much_combi;
  for( int it=0; it<ntSdcIn; ++it ){
    DCLocalTrack *tp=DCAna->GetTrackSdcIn(it);
    int nh=tp->GetNHit();
    double chisqr=tp->GetChiSquare();
    double x0=tp->GetX0(), y0=tp->GetY0();
    double u0=tp->GetU0(), v0=tp->GetV0();
    HF1( 11, double(nh) );
    HF1( 12, chisqr );
    HF1( 14, x0 ); HF1( 15, y0 );
    HF1( 16, u0 ); HF1( 17, v0 );
    HF2( 18, x0, u0 ); HF2( 19, y0, v0 );
    HF2( 20, x0, y0 );
    event.nhSdcIn[it] = nh;
    event.chisqrSdcIn[it] = chisqr;
    event.x0SdcIn[it] = x0;
    event.y0SdcIn[it] = y0;
    event.u0SdcIn[it] = u0;
    event.v0SdcIn[it] = v0;
    for( int ih=0; ih<nh; ++ih ){
      DCLTrackHit *hit=tp->GetHit(ih);

      int layerId = hit->GetLayer();
      HF1( 13, hit->GetLayer() );
      double wire = hit->GetWire();
      double dt=hit->GetDriftTime(), dl=hit->GetDriftLength();
      HF1( 100*layerId+1, wire-0.5 );
      HF1( 100*layerId+2, dt );
      HF1( 100*layerId+3, dl );
      double xcal=hit->GetXcal(), ycal=hit->GetYcal();
      double pos=hit->GetLocalHitPos(), res=hit->GetResidual();
      HF1( 100*layerId+4, pos );
      HF1( 100*layerId+5, res );
      HF2( 100*layerId+6, pos, res );
      HF2( 100*layerId+7, xcal, ycal);
      for( int i=0; i<NumOfLayersSdcIn; ++i ){
	if( i==layerId-1 ) event.resL[i].push_back( res );
      }
    }
  }
  if( ntSdcIn<1 ) return true;
  //  if( !(ntSdcIn==1) ) return true;

  HF1( 1, 12. );

#if 0
  //////////////SdcIn vs Tof cut for Proton event
  {
    int ntOk=0;
    for( int it=0; it<ntSdcIn; ++it ){
      DCLocalTrack *tp=DCAna->GetTrackSdcIn(it);
      if(!tp) continue;

      int nh=tp->GetNHit();
      double chisqr=tp->GetChiSquare();
      double u0=tp->GetU0(), v0=tp->GetV0();
      double x0=tp->GetX0(), y0=tp->GetY0();

      bool condTof=false;
      for( int j=0; j<ncTof; ++j ){
	HodoCluster *clTof=hodoAna->GetClusterTOF(j);
	if( !clTof || !clTof->GoodForAnalysis() ) continue;
	double ttof=clTof->CMeanTime()-time0;
	//------------------------Cut
	if( MinModTimeTof< ttof+14.0*u0 && ttof+14.0*u0 <MaxModTimeTof )
	  condTof=true;
      }
      if( condTof ){
	++ntOk;
	for( int j=0; j<ncTof; ++j ){
	  HodoCluster *clTof=hodoAna->GetClusterTOF(j);
	  if( !clTof || !clTof->GoodForAnalysis() ) continue;
	  double ttof=clTof->CMeanTime()-time0;
	}
	// if(ntOk>0) tp->GoodForTracking( false );
      }
      else {
	// tp->GoodForTracking( false );
      }
    }
    // if( ntOk<1 ) return true;
  }
#endif

  HF1( 1, 13. );

  //////////////SdcOut tracking
  //std::cout << "==========TrackSearch SdcOut============" << std::endl;
  
  if(flag_tof_stop){
#if UseTOF
    DCAna->TrackSearchSdcOut( TOFCont );
#else
    DCAna->TrackSearchSdcOut();
#endif
  }else{
    DCAna->TrackSearchSdcOut();
  }

  DCAna->ChiSqrCutSdcOut(50.);  
  int ntSdcOut = DCAna->GetNtracksSdcOut();  

  if( MaxHits<ntSdcOut ){
    std::cout << "#W " << func_name << " "
	      << "too many ntSdcOut " << ntSdcOut << "/" << MaxHits << std::endl;
    ntSdcOut = MaxHits;
  }

  event.ntSdcOut=ntSdcOut;
  HF1( 30, double(ntSdcOut) );
  for( int it=0; it<ntSdcOut; ++it ){
    DCLocalTrack *tp=DCAna->GetTrackSdcOut(it);
    int nh=tp->GetNHit();
    double chisqr=tp->GetChiSquare();
    double u0=tp->GetU0(), v0=tp->GetV0();
    double x0=tp->GetX0(), y0=tp->GetY0();
    HF1( 31, double(nh) );
    HF1( 32, chisqr );
    HF1( 34, x0 ); HF1( 35, y0 );
    HF1( 36, u0 ); HF1( 37, v0 );
    HF2( 38, x0, u0 ); HF2( 39, y0, v0 );
    HF2( 40, x0, y0 );
    event.nhSdcOut[it] = nh;
    event.chisqrSdcOut[it] = chisqr;
    event.x0SdcOut[it] = x0;
    event.y0SdcOut[it] = y0;
    event.u0SdcOut[it] = u0;
    event.v0SdcOut[it] = v0;
    for( int ih=0; ih<nh; ++ih ){
      DCLTrackHit *hit=tp->GetHit(ih);
      int layerId = hit->GetLayer();

      if( hit->GetLayer()>79 ) layerId -= 62;
      else if( hit->GetLayer()>40 ) layerId -= 15;
      else if( hit->GetLayer()>30 ) layerId -= 21;
      //std::cout << "layerId :" << layerId << std::endl; 

      HF1( 33, hit->GetLayer() );
      double wire=hit->GetWire();
      double dt=hit->GetDriftTime(), dl=hit->GetDriftLength();
      HF1( 100*layerId+1, wire-0.5 );
      HF1( 100*layerId+2, dt );
      HF1( 100*layerId+3, dl );
      double xcal=hit->GetXcal(), ycal=hit->GetYcal();
      double pos=hit->GetLocalHitPos(), res=hit->GetResidual();
      HF1( 100*layerId+4, pos );
      HF1( 100*layerId+5, res );
      HF2( 100*layerId+6, pos, res );
      HF2( 100*layerId+7, xcal, ycal);
      for( int i=0; i<NumOfLayersSdcOut+2; ++i ){
	if( i==layerId-NumOfLayersSdcIn-1 ){
	  event.resL[i+NumOfLayersSdcIn].push_back( res );
	}
      }
    }
  }


  if( ntSdcOut<1 ) return true;

  HF1( 1, 14. );

  for( int i1=0; i1<ntSdcIn; ++i1 ){
    DCLocalTrack *trSdcIn=DCAna->GetTrackSdcIn(i1);
    double xin=trSdcIn->GetX0(), yin=trSdcIn->GetY0();
    double uin=trSdcIn->GetU0(), vin=trSdcIn->GetV0();
    for( int i2=0; i2<ntSdcOut; ++i2 ){
      DCLocalTrack *trSdcOut=DCAna->GetTrackSdcOut(i2);
      double xout=trSdcOut->GetX0(), yout=trSdcOut->GetY0();
      double uout=trSdcOut->GetU0(), vout=trSdcOut->GetV0();
      HF2( 20001, xin, xout ); HF2( 20002, yin, yout );
      HF2( 20003, uin, uout ); HF2( 20004, vin, vout );
    }
  }

  HF1( 1, 20. );

  if( ntSdcIn*ntSdcOut > 4 ) return true;

  HF1( 1, 21. );

  //////////////KURAMA Tracking
  DCAna->TrackSearchKurama();
  int ntKurama = DCAna->GetNTracksKurama();
  if( MaxHits<ntKurama ){
    std::cout << "#W " << func_name << " "
	      << "too many ntKurama " << ntKurama << "/" << MaxHits << std::endl;
    ntKurama = MaxHits;
  }
  event.ntKurama = ntKurama;
  HF1( 50, double(ntKurama) );

  for( int i=0; i<ntKurama; ++i ){
    KuramaTrack *tp=DCAna->GetKuramaTrack(i);
    if(!tp) continue;
    int nh=tp->GetNHits();
    double chisqr=tp->chisqr();
    ThreeVector Pos = tp->PrimaryPosition();
    ThreeVector Mom = tp->PrimaryMomentum();
    // hddaq::cout << std::fixed
    // 		<< "Pos = " << Pos << std::endl
    // 		<< "Mom = " << Mom << std::endl;
    double path = tp->PathLengthToTOF();
    double xt = Pos.x(), yt = Pos.y();
    double p = Mom.Mag();
    double q = tp->Polarity();
    double ut = Mom.x()/Mom.z(), vt = Mom.y()/Mom.z();
    double cost  = 1./std::sqrt(1.+ut*ut+vt*vt);
    double theta = std::acos(cost)*math::Rad2Deg();
    double phi   = atan2( ut, vt );
    double initial_momentum = tp->GetInitialMomentum();
    double tof_seg = tp->TofSeg();
    HF1( 51, double(nh) );
    HF1( 52, chisqr );
    HF1( 54, xt ); HF1( 55, yt ); HF1( 56, ut ); HF1( 57,vt );
    HF2( 58, xt, ut ); HF2( 59, yt, vt ); HF2( 60, xt, yt );
    HF1( 61, p ); HF1( 62, path );

    event.nhKurama[i] = nh;
    event.chisqrKurama[i] = chisqr;
    event.path[i] = path;
    event.pKurama[i] = p;
    event.qKurama[i] = q;
    event.xtgtKurama[i] = xt;
    event.ytgtKurama[i] = yt;
    event.utgtKurama[i] = ut;
    event.vtgtKurama[i] = vt;
    event.thetaKurama[i] = theta;
    event.phiKurama[i]   = phi;
    event.resP[i] = p - initial_momentum;

    if(ntKurama == 1){
      for(int l = 0; l<NumOfLayersVP; ++l){
	double x, y;
	tp->GetTrajectoryLocalPosition(21 + l, x, y);

//  int seg ;
//  seg = gGeom.CalcWireNumber(21 + l,x);
  double m_offset = 18.;
  double m_dd = 10.5;
  double m_w0 = 32.5;

  double dw = ( (x-m_offset)/m_dd ) + m_w0;
  int    iw = int(dw);
  if( (dw-double(iw))>0.5 ){
    iw+=1;
  }
  
  event.vpx[l] = x;
  event.vpy[l] = y;
  event.vpseg[l] = iw;
      }// for(l)
    }

    const ThreeVector& posTof = tp->TofPos();
    const ThreeVector& momTof = tp->TofMom();
    event.xtofKurama[i] = posTof.x();
    event.ytofKurama[i] = posTof.y();
    event.utofKurama[i] = momTof.x()/momTof.z();
    event.vtofKurama[i] = momTof.y()/momTof.z();

    ///// w/  TOF
    event.tofsegKurama[i] = tof_seg;
    ///// w/o TOF
    // TVector2 vecTof( posTof.x(), posTof.z() );
    // vecTof -= TVector2( 250., 2015. );
    // double sign = math::Sign( vecTof.X() );
    // double TofSegKurama = sign*vecTof.Mod()/75.+12.5;
    // event.tofsegKurama[i] = math::Round( TofSegKurama )
#if 0
    // std::cout << "posTof " << posTof << std::endl;
    // std::cout << "momTof " << momTof << std::endl;
    std::cout << std::setw(10) << vecTof.X()
	      << std::setw(10) << vecTof.Y()
	      << std::setw(10) << sign*vecTof.Mod()
	      << std::setw(10) << TofSegKurama << std::endl;
#endif
    // double minres = 1.0e10;
    // int    TofSeg = -9999;
    double time   = -9999.;
    for( int j=0; j<nhTof; ++j ){
      Hodo2Hit *hit = hodoAna->GetHitTOF(j);
      if( !hit ) continue;
      int seg  = hit->SegmentId()+1;
      // w/  TOF
      if( (int)tof_seg == seg ){
	time = hit->CMeanTime()-time0+OffsetToF;
      }
      // w/o TOF
      // double res  = std::abs( tof_seg - seg );
      // if( res<minres ){
      // 	minres = res;
      // 	TofSeg = seg;
      // 	time   = hit->CMeanTime()-time0+OffsetToF;
      // }
    }
    event.stof[i] = time;
    if( time>0. ){
      double m2 = Kinematics::MassSquare( p, path, time );
      HF1( 63, m2 );
      event.m2[i] = m2;
# if 0
      std::ios::fmtflags pre_flags     = std::cout.flags();
      std::size_t        pre_precision = std::cout.precision();
      std::cout.setf( std::ios::fixed );
      std::cout.precision(5);
      std::cout << "#D " << func_name << std::endl
		<< "   Mom  = " << p     << std::endl
		<< "   Path = " << path << std::endl
		<< "   Time = " << time  << std::endl
		<< "   m2   = " << m2    << std::endl;
      std::cout.flags( pre_flags );
      std::cout.precision( pre_precision );
# endif
    }

    for( int j=0; j<nh; ++j ){
      TrackHit *hit=tp->GetHit(j);
      if(!hit) continue;
      int layerId = hit->GetLayer();
      if( hit->GetLayer()>79 ) layerId -= 62;
      else if( hit->GetLayer()>40 ) layerId -= 15;
      else if( hit->GetLayer()>30 ) layerId -= 21;
      
      HF1( 53, hit->GetLayer() );
      double wire = hit->GetHit()->GetWire();
      double dt   = hit->GetHit()->GetDriftTime();
      double dl   = hit->GetHit()->GetDriftLength();
      double pos  = hit->GetCalLPos();
      double res  = hit->GetResidual();
      DCLTrackHit *lhit = hit->GetHit();
      double xcal = lhit->GetXcal();
      double ycal = lhit->GetYcal();
      HF1( 100*layerId+11, double(wire)-0.5 );
      double wp   = lhit->GetWirePosition();
      HF1( 100*layerId+12, dt );
      HF1( 100*layerId+13, dl );
      HF1( 100*layerId+14, pos );

      if( nh>17 && q<=0. && chisqr<200. ){
      	HF1( 100*layerId+15, res );
	HF2( 100*layerId+16, pos, res );
      }
      HF2( 100*layerId+17, xcal, ycal );
      if ( std::abs(dl-std::abs(xcal-wp))<2.0 ){
	HF2( 100*layerId+22, dt, std::abs(xcal-wp));
      }
      for( int l=0; l<NumOfLayersSdcIn; ++l ){
	if( l==layerId-1 )
	  event.resG[l].push_back(res);
      }
      for( int l=0; l<NumOfLayersSdcOut+2; ++l ){
	if( l==layerId-1-NumOfLayersSdcIn )
	  event.resG[l+NumOfLayersSdcIn].push_back(res);
      }
    }

    DCLocalTrack *trSdcIn  = tp->GetLocalTrackIn();
    DCLocalTrack *trSdcOut = tp->GetLocalTrackOut();
    if(trSdcIn){
      int nhSdcIn=trSdcIn->GetNHit();
      double x0in=trSdcIn->GetX0(), y0in=trSdcIn->GetY0();
      double u0in=trSdcIn->GetU0(), v0in=trSdcIn->GetV0();
      double chiin=trSdcIn->GetChiSquare();
      HF1( 21, double(nhSdcIn) ); HF1( 22, chiin );
      HF1( 24, x0in ); HF1( 25, y0in ); HF1( 26, u0in ); HF1( 27, v0in );
      HF2( 28, x0in, u0in ); HF2( 29, y0in, v0in );
      for( int jin=0; jin<nhSdcIn; ++jin ){
	int layer=trSdcIn->GetHit(jin)->GetLayer();
	HF1( 23, layer );
      }
    }
    if(trSdcOut){
      int nhSdcOut=trSdcOut->GetNHit();
      double x0out=trSdcOut->GetX(zTOF), y0out=trSdcOut->GetY(zTOF);
      double u0out=trSdcOut->GetU0(), v0out=trSdcOut->GetV0();
      double chiout=trSdcOut->GetChiSquare();
      HF1( 41, double(nhSdcOut) ); HF1( 42, chiout );
      HF1( 44, x0out ); HF1( 45, y0out ); HF1( 46, u0out ); HF1( 47, v0out );
      HF2( 48, x0out, u0out ); HF2( 49, y0out, v0out );
      for( int jout=0; jout<nhSdcOut; ++jout ){
	int layer=trSdcOut->GetHit(jout)->GetLayer();
	HF1( 43, layer );
      }
    }
  }

  for( int i=0; i<ntKurama; ++i ){
    KuramaTrack *tp=DCAna->GetKuramaTrack(i);
    if(!tp) continue;
    double x = 0;
    double y = 0;
    if ( tp->GetTrajectoryLocalPosition( 21, x, y ) ) {
      event.xsacKurama[i] = x;
      event.ysacKurama[i] = y;
    }
  }

  for( int i=0; i<ntKurama; ++i ){
    KuramaTrack *tp=DCAna->GetKuramaTrack(i);
    if(!tp) continue;
    DCLocalTrack *trSdcIn =tp->GetLocalTrackIn();
    DCLocalTrack *trSdcOut=tp->GetLocalTrackOut();
    if( !trSdcIn || !trSdcOut ) continue;
    double yin=trSdcIn->GetY(500.), vin=trSdcIn->GetV0();
    double yout=trSdcOut->GetY(3800.), vout=trSdcOut->GetV0();
    HF2( 20021, yin, yout ); HF2( 20022, vin, vout );
    HF2( 20023, vin, yout ); HF2( 20024, vout, yin );
  }

  if( ntKurama==0 ) return true;
  KuramaTrack *track = DCAna->GetKuramaTrack(0);
  double path = track->PathLengthToTOF();
  double p    = track->PrimaryMomentum().Mag();
  //double tTof[Event::nParticle];
  double calt[Event::nParticle] = {
    Kinematics::CalcTimeOfFlight( p, path, pdg::PionMass() ),
    Kinematics::CalcTimeOfFlight( p, path, pdg::KaonMass() ),
    Kinematics::CalcTimeOfFlight( p, path, pdg::ProtonMass() )
  };
  for( int i=0; i<Event::nParticle; ++i ){
    event.tTofCalc[i] = calt[i];
  }
  // TOF
  {
    int nh = hodoAna->GetNHitsTOF();
    for( int i=0; i<nh; ++i ){
      Hodo2Hit *hit=hodoAna->GetHitTOF(i);
      if(!hit) continue;
      int seg=hit->SegmentId()+1;
      double tu = hit->GetTUp(), td=hit->GetTDown();
      // double ctu=hit->GetCTUp(), ctd=hit->GetCTDown();
      double cmt=hit->CMeanTime();//, t= cmt-time0+OffsetToF;//cmt-time0;
      double ude=hit->GetAUp(), dde=hit->GetADown();
      // double de=hit->DeltaE();
      // double m2 = Kinematics::MassSquare( p, path, t );
      // event.tofmt[seg-1] = hit->MeanTime();
      event.utTofSeg[seg-1]  =  tu - time0 + OffsetToF;
      event.dtTofSeg[seg-1]  =  td - time0 + OffsetToF;
      // event.uctTofSeg[seg-1] = ctu - time0 + offset;
      // event.dctTofSeg[seg-1] = ctd - time0 + offset;
      event.udeTofSeg[seg-1] = ude;
      event.ddeTofSeg[seg-1] = dde;
      // event.ctTofSeg[seg-1]  = t;
      // event.deTofSeg[seg-1]  = de;
      HF2( 30000+100*seg+83, ude, calt[Event::Pion]+time0-OffsetToF-cmt );
      HF2( 30000+100*seg+84, dde, calt[Event::Pion]+time0-OffsetToF-cmt );
      HF2( 30000+100*seg+83, ude, calt[Event::Pion]+time0-OffsetToF-tu );
      HF2( 30000+100*seg+84, dde, calt[Event::Pion]+time0-OffsetToF-td );
    }

    const HodoRHitContainer &cont=rawData->GetTOFRawHC();
    int NofHit = cont.size();
    for(int i = 0; i<NofHit; ++i){
      HodoRawHit *hit = cont[i];
      int seg = hit->SegmentId();
      event.tofua[seg] = hit->GetAdcUp();
      event.tofda[seg] = hit->GetAdcDown();
    }
  }

  HF1( 1, 22. );

  return true;
}

//______________________________________________________________________________
void
EventKuramaTracking::InitializeEvent( void )
{
  event.ntSdcIn  = 0;
  event.nlSdcIn  = 0;
  event.ntSdcOut = 0;
  event.nlSdcOut = 0;
  event.ntKurama = 0;
  event.nlKurama = 0;
  event.nhBh2    = 0;
  event.nhBh1    = 0;
  event.nhSac    = 0;
  event.nhTof    = 0;
  event.much     = -1;

  event.time0 = -9999.;
  event.btof  = -9999.;

  for(int i = 0; i<NumOfLayersVP; ++i){
    event.vpx[i] = -9999;
    event.vpy[i] = -9999;
  }

  for( int it=0; it<NumOfSegTrig; it++){
    event.trigpat[it] = -1;
    event.trigflag[it] = -1;
  }

  for( int it=0; it<MaxHits; it++){
    event.Bh2Seg[it] = -1;
    event.tBh2[it] = -9999.;
    event.deBh2[it] = -9999.;

    event.Bh1Seg[it] = -1;
    event.tBh1[it] = -9999.;
    event.deBh1[it] = -9999.;

    event.SacSeg[it] = -1;
    event.tSac[it] = -9999.;
    event.deSac[it] = -9999.;

    event.TofSeg[it] = -1;
    event.tTof[it] = -9999.;
    event.deTof[it] = -9999.;
  }
  for( int it=0; it<NumOfSegSAC; it++){
    for(int m = 0; m<MaxDepth; ++m){
      event.tSac_khodo[MaxDepth*it+m]   = -9999.;
    }
  }

  for( int it=0; it<NumOfLayersSdcIn; ++it ){
    event.wposSdcIn[it]  = -9999.;
  }
  for( int it=0; it<NumOfLayersSdcOut; ++it ){
    event.wposSdcOut[it] = -9999.;
  }

  for( int it=0; it<MaxHits; it++){
    event.nhSdcIn[it]     = 0;
    event.chisqrSdcIn[it] = -9999.;
    event.x0SdcIn[it] = -9999.;
    event.y0SdcIn[it] = -9999.;
    event.u0SdcIn[it] = -9999.;
    event.v0SdcIn[it] = -9999.;
  }

  for( int it=0; it<MaxHits; it++){
    event.nhSdcOut[it]     = 0;
    event.chisqrSdcOut[it] = -9999.;
    event.x0SdcOut[it] = -9999.;
    event.y0SdcOut[it] = -9999.;
    event.u0SdcOut[it] = -9999.;
    event.v0SdcOut[it] = -9999.;
  }

  for( int it=0; it<MaxHits; it++){
    event.nhKurama[it]     = 0;
    event.chisqrKurama[it] = -9999.;
    event.stof[it]         = -9999.;
    event.path[it]         = -9999.;
    event.pKurama[it]      = -9999.;
    event.qKurama[it]      = -9999.;
    event.m2[it]           = -9999.;

    event.xtgtKurama[it]  = -9999.;
    event.ytgtKurama[it]  = -9999.;
    event.utgtKurama[it]  = -9999.;
    event.vtgtKurama[it]  = -9999.;
    event.thetaKurama[it] = -9999.;
    event.phiKurama[it]   = -9999.;
    event.resP[it]        = -9999.;
    event.xsacKurama[it]  = -9999.;
    event.ysacKurama[it]  = -9999.;
    event.xtofKurama[it]  = -9999.;
    event.ytofKurama[it]  = -9999.;
    event.utofKurama[it]  = -9999.;
    event.vtofKurama[it]  = -9999.;
    event.tofsegKurama[it] = -9999.;
  }

  for( int i=0; i<NumOfLayersSdcIn+NumOfLayersSdcOut+2; ++i ){
    event.resL[i].clear();
    event.resG[i].clear();
  }

  for( int i=0; i<Event::nParticle; ++i ){
    event.tTofCalc[i] = -9999.;
  }

  for( int i=0; i<NumOfSegTOF; ++i ){
    // event.tofmt[i] = -9999.;
    event.utTofSeg[i]  = -9999.;
    event.dtTofSeg[i]  = -9999.;
    // event.ctuTofSeg[i] = -9999.;
    // event.ctdTofSeg[i] = -9999.;
    // event.ctTofSeg[i]  = -9999.;
    event.udeTofSeg[i] = -9999.;
    event.ddeTofSeg[i] = -9999.;
    // event.deTofSeg[i]  = -9999.;
    event.tofua[i]     = -9999.;
    event.tofda[i]     = -9999.;
  }
}

//______________________________________________________________________________
bool
EventKuramaTracking::ProcessingEnd( void )
{
  tree->Fill();
  return true;
}

//______________________________________________________________________________
VEvent*
ConfMan::EventAllocator( void )
{
  return new EventKuramaTracking;
}

//______________________________________________________________________________
namespace
{
  const int    NBinDTSDC1 =  90;
  const double MinDTSDC1  = -10.;
  const double MaxDTSDC1  =  80.;
  const int    NBinDLSDC1 =  100;
  const double MinDLSDC1  = -0.5;
  const double MaxDLSDC1  =  3.0;

  const int    NBinDTSDC2 =  220;
  const double MinDTSDC2  = -20.;
  const double MaxDTSDC2  = 200.;
  const int    NBinDLSDC2 =  100;
  const double MinDLSDC2  = -0.5;
  const double MaxDLSDC2  =  4.5;

  const int    NBinDTSDC3 =  400;
  const double MinDTSDC3  = -100.;
  const double MaxDTSDC3  =  300.;
  const int    NBinDLSDC3 =  100;
  const double MinDLSDC3  = -5.0;
  const double MaxDLSDC3  = 15.0;
}
//______________________________________________________________________________
bool
ConfMan:: InitializeHistograms( void )
{
  HB1( 1, "Status", 30, 0., 30. );

  HB1( 10, "#Tracks SdcIn", 10, 0., 10. );
  HB1( 11, "#Hits of Track SdcIn", 15, 0., 15. );
  HB1( 12, "Chisqr SdcIn", 500, 0., 50. );
  HB1( 13, "LayerId SdcIn", 15, 0., 15. );
  HB1( 14, "X0 SdcIn", 400, -100., 100. );
  HB1( 15, "Y0 SdcIn", 400, -100., 100. );
  HB1( 16, "U0 SdcIn", 200, -0.20, 0.20 );
  HB1( 17, "V0 SdcIn", 200, -0.20, 0.20 );
  HB2( 18, "U0%X0 SdcIn", 100, -100., 100., 100, -0.20, 0.20 );
  HB2( 19, "V0%Y0 SdcIn", 100, -100., 100., 100, -0.20, 0.20 );
  HB2( 20, "X0%Y0 SdcIn", 100, -100., 100., 100, -100., 100. );

  HB1( 21, "#Hits of Track SdcIn [KuramaTrack]", 15, 0., 15. );
  HB1( 22, "Chisqr SdcIn [KuramaTrack]", 500, 0., 50. );
  HB1( 23, "LayerId SdcIn [KuramaTrack]", 15, 0., 15. );
  HB1( 24, "X0 SdcIn [KuramaTrack]", 400, -100., 100. );
  HB1( 25, "Y0 SdcIn [KuramaTrack]", 400, -100., 100. );
  HB1( 26, "U0 SdcIn [KuramaTrack]", 200, -0.20, 0.20 );
  HB1( 27, "V0 SdcIn [KuramaTrack]", 200, -0.20, 0.20 );
  HB2( 28, "U0%X0 SdcIn [KuramaTrack]", 100, -100., 100., 100, -0.20, 0.20 );
  HB2( 29, "V0%Y0 SdcIn [KuramaTrack]", 100, -100., 100., 100, -0.20, 0.20 );
  //HB2( 30, "X0%Y0 SdcIn [KuramaTrack]", 100, -100., 100., 100, -100., 100. );

  HB1( 30, "#Tracks SdcOut", 10, 0., 10. );
  HB1( 31, "#Hits of Track SdcOut", 20, 0., 20. );
  HB1( 32, "Chisqr SdcOut", 500, 0., 50. );
  HB1( 33, "LayerId SdcOut", 20, 30., 50. );
  HB1( 34, "X0 SdcOut", 1400, -1200., 1200. );
  HB1( 35, "Y0 SdcOut", 1000, -500., 500. );
  HB1( 36, "U0 SdcOut",  700, -0.35, 0.35 );
  HB1( 37, "V0 SdcOut",  200, -0.20, 0.20 );
  HB2( 38, "U0%X0 SdcOut", 120, -1200., 1200., 100, -0.40, 0.40 );
  HB2( 39, "V0%Y0 SdcOut", 100, -500., 500., 100, -0.20, 0.20 );
  HB2( 40, "X0%Y0 SdcOut", 100, -1200., 1200., 100, -500., 500. );

  HB1( 41, "#Hits of Track SdcOut [KuramaTrack]", 20, 0., 20. );
  HB1( 42, "Chisqr SdcOut [KuramaTrack]", 500, 0., 50. );
  HB1( 43, "LayerId SdcOut [KuramaTrack]", 20, 30., 50. );
  HB1( 44, "X0 SdcOut [KuramaTrack]", 1400, -1200., 1200. );
  HB1( 45, "Y0 SdcOut [KuramaTrack]", 1000, -500., 500. );
  HB1( 46, "U0 SdcOut [KuramaTrack]",  700, -0.35, 0.35 );
  HB1( 47, "V0 SdcOut [KuramaTrack]",  200, -0.10, 0.10 );
  HB2( 48, "U0%X0 SdcOut [KuramaTrack]", 120, -600., 600., 100, -0.40, 0.40 );
  HB2( 49, "V0%Y0 SdcOut [KuramaTrack]", 100, -500., 500., 100, -0.10, 0.10 );
  //HB2( 50, "X0%Y0 SdcOut [KuramaTrack]", 100, -700., 700., 100, -500., 500. );

  HB1( 50, "#Tracks KURAMA", 10, 0., 10. );
  HB1( 51, "#Hits of KuramaTrack", 50, 0., 50. );
  HB1( 52, "Chisqr KuramaTrack", 500, 0., 50. );
  HB1( 53, "LayerId KuramaTrack", 90, 0., 90. );
  HB1( 54, "Xtgt KuramaTrack", 200, -100., 100. );
  HB1( 55, "Ytgt KuramaTrack", 200, -100., 100. );
  HB1( 56, "Utgt KuramaTrack", 300, -0.30, 0.30 );
  HB1( 57, "Vtgt KuramaTrack", 300, -0.20, 0.20 );
  HB2( 58, "U%Xtgt KuramaTrack", 100, -100., 100., 100, -0.25, 0.25 );
  HB2( 59, "V%Ytgt KuramaTrack", 100, -100., 100., 100, -0.10, 0.10 );
  HB2( 60, "Y%Xtgt KuramaTrack", 100, -100., 100., 100, -100., 100. );
  HB1( 61, "P KuramaTrack", 500, 0.00, 2.50 );
  HB1( 62, "PathLength KuramaTrack", 600, 3000., 4000. );
  HB1( 63, "MassSqr", 600, -0.4, 1.4 );

  // SDC1
  for( int i=1; i<=NumOfLayersSDC1; ++i ){
    TString title1 = Form("HitPat Sdc1_%d", i);
    TString title2 = Form("DriftTime Sdc1_%d", i);
    TString title3 = Form("DriftLength Sdc1_%d", i);
    TString title4 = Form("Position Sdc1_%d", i);
    TString title5 = Form("Residual Sdc1_%d", i);
    TString title6 = Form("Resid%%Pos Sdc1_%d", i);
    TString title7 = Form("Y%%Xcal Sdc1_%d", i);
    HB1( 100*i+1, title1, 96, 0., 96. );
    HB1( 100*i+2, title2, NBinDTSDC1, MinDTSDC1, MaxDTSDC1 );
    HB1( 100*i+3, title3, NBinDLSDC1, MinDLSDC1, MaxDLSDC1 );
    HB1( 100*i+4, title4, 500, -100., 100. );
    HB1( 100*i+5, title5, 200, -2.0, 2.0 );
    HB2( 100*i+6, title6, 100, -100., 100., 100, -2.0, 2.0 );
    HB2( 100*i+7, title7, 100, -100., 100., 100, -50., 50. );
    title1 += " [KuramaTrack]";
    title2 += " [KuramaTrack]";
    title3 += " [KuramaTrack]";
    title4 += " [KuramaTrack]";
    title5 += " [KuramaTrack]";
    title6 += " [KuramaTrack]";
    title7 += " [KuramaTrack]";
    TString title22 = Form("DriftLength%%DriftTime Sdc%d [KuramaTrack]", i);
    HB1( 100*i+11, title1, 96, 0., 96. );
    HB1( 100*i+12, title2, NBinDTSDC1, MinDTSDC1, MaxDTSDC1 );
    HB1( 100*i+13, title3, NBinDLSDC1, MinDLSDC1, MaxDLSDC1 );
    HB1( 100*i+14, title4, 500, -100., 100. );
    HB1( 100*i+15, title5, 200, -2.0, 2.0 );
    HB2( 100*i+16, title6, 100, -100., 100., 100, -2.0, 2.0 );
    HB2( 100*i+17, title7, 100, -100., 100., 100, -50., 50. );
    HB2( 100*i+22, title22, NBinDTSDC1, MinDTSDC1, MaxDTSDC1, NBinDLSDC1, MinDLSDC1, MaxDLSDC1 );
  }
  
  //SFT
  for( int i=NumOfLayersSDC1+1; i<=NumOfLayersSdcIn; ++i ){
    TString title1 = Form("HitPat Sft%d", i-NumOfLayersSDC1);
    TString title4 = Form("Position Sft%d", i-NumOfLayersSDC1);
    TString title5 = Form("Residual Sft%d", i-NumOfLayersSDC1);
    TString title6 = Form("Resid%%Pos Sft%d", i-NumOfLayersSDC1);
    TString title7 = Form("Y%%Xcal Sft%d", i-NumOfLayersSDC1);
    HB1( 100*i+1, title1, 70, 0., 70. );
    HB1( 100*i+4, title4, 800, -400., 400. );
    HB1( 100*i+5, title5, 500, -5.0, 5.0 );
    HB2( 100*i+6, title6, 100, -600., 600., 100, -5.0, 5.0 );
    HB2( 100*i+7, title7, 100, -600., 600., 100, -600., 600. );
    title1 += " [KuramaTrack]";
    title4 += " [KuramaTrack]";
    title5 += " [KuramaTrack]";
    title6 += " [KuramaTrack]";
    title7 += " [KuramaTrack]";
    HB1( 100*i+11, title1, 70, 0., 70. );
    HB1( 100*i+14, title4, 800, -400., 400. );
    HB1( 100*i+15, title5, 500, -5.0, 5.0 );
    HB2( 100*i+16, title6, 100, -600., 600., 100, -5.0, 5.0 );
    HB2( 100*i+17, title7, 100, -600., 600., 100, -600., 600. );
  }

  // SDC2
  for( int i=NumOfLayersSdcIn+1; i<=(NumOfLayersSdcIn+NumOfLayersSDC2); ++i ){
    TString title1 = Form("HitPat Sdc2_%d", i-NumOfLayersSdcIn);
    TString title2 = Form("DriftTime Sdc2_%d", i-NumOfLayersSdcIn);
    TString title3 = Form("DriftLength Sdc2_%d", i-NumOfLayersSdcIn);
    TString title4 = Form("Position Sdc2_%d", i-NumOfLayersSdcIn);
    TString title5 = Form("Residual Sdc2_%d", i-NumOfLayersSdcIn);
    TString title6 = Form("Resid%%Pos Sdc2_%d", i-NumOfLayersSdcIn);
    TString title7 = Form("Y%%Xcal Sdc2_%d", i-NumOfLayersSdcIn);
    HB1( 100*i+1, title1, 112, 0., 112. );
    HB1( 100*i+2, title2, NBinDTSDC2, MinDTSDC2, MaxDTSDC2 );
    HB1( 100*i+3, title3, NBinDLSDC2, MinDLSDC2, MaxDLSDC2 );
    HB1( 100*i+4, title4, 1000, -600., 600. );
    HB1( 100*i+5, title5, 200, -2.0, 2.0 );
    HB2( 100*i+6, title6, 100, -600., 600., 100, -2.0, 2.0 );
    HB2( 100*i+7, title7, 100, -600., 600., 100, -600., 600. );
    title1 += " [KuramaTrack]";
    title2 += " [KuramaTrack]";
    title3 += " [KuramaTrack]";
    title4 += " [KuramaTrack]";
    title5 += " [KuramaTrack]";
    title6 += " [KuramaTrack]";
    title7 += " [KuramaTrack]";
    TString title22 = Form("DriftLength%%DriftTime Sdc2_%d [KuramaTrack]", i-NumOfLayersSdcIn);
    HB1( 100*i+11, title1, 112, 0., 112. );
    HB1( 100*i+12, title2, NBinDTSDC2, MinDTSDC2, MaxDTSDC2 );
    HB1( 100*i+13, title3, NBinDLSDC2, MinDLSDC2, MaxDLSDC2 );
    HB1( 100*i+14, title4, 1000, -600., 600. );
    HB1( 100*i+15, title5, 200, -2.0, 2.0 );
    HB2( 100*i+16, title6, 100, -600., 600., 100, -2.0, 2.0 );
    HB2( 100*i+17, title7, 100, -600., 600., 100, -600., 600. );
    HB2( 100*i+22, title22, NBinDTSDC2, MinDTSDC2, MaxDTSDC2, NBinDLSDC2, MinDLSDC2, MaxDLSDC2 );
  }

  // SDC3
  for( int i=NumOfLayersSdcIn+NumOfLayersSDC2+1;
       i<=(NumOfLayersSdcIn+NumOfLayersSDC2+NumOfLayersSDC3) ; ++i ){
    TString title1 = Form("HitPat Sdc3_%d", i-(NumOfLayersSdcIn+NumOfLayersSDC2));
    TString title2 = Form("DriftTime Sdc3_%d", i-(NumOfLayersSdcIn+NumOfLayersSDC2));
    TString title3 = Form("DriftLength Sdc3_%d", i-(NumOfLayersSdcIn+NumOfLayersSDC2));
    TString title4 = Form("Position Sdc3_%d", i-(NumOfLayersSdcIn+NumOfLayersSDC2));
    TString title5 = Form("Residual Sdc3_%d", i-(NumOfLayersSdcIn+NumOfLayersSDC2));
    TString title6 = Form("Resid%%Pos Sdc3_%d", i-(NumOfLayersSdcIn+NumOfLayersSDC2));
    TString title7 = Form("Y%%Xcal Sdc3_%d", i-(NumOfLayersSdcIn+NumOfLayersSDC2));
    HB1( 100*i+1, title1, 120, 0., 120. );
    HB1( 100*i+2, title2, NBinDTSDC3, MinDTSDC3, MaxDTSDC3 );
    HB1( 100*i+3, title3, NBinDLSDC3, MinDLSDC3, MaxDLSDC3 );
    HB1( 100*i+4, title4, 1000, -600., 600. );
    HB1( 100*i+5, title5, 200, -2.0, 2.0 );
    HB2( 100*i+6, title6, 100, -600., 600., 100, -1.0, 1.0 );
    HB2( 100*i+7, title7, 100, -600., 600., 100, -600., 600. );
    title1 += " [KuramaTrack]";
    title2 += " [KuramaTrack]";
    title3 += " [KuramaTrack]";
    title4 += " [KuramaTrack]";
    title5 += " [KuramaTrack]";
    title6 += " [KuramaTrack]";
    title7 += " [KuramaTrack]";
    TString title22 = Form("DriftLength%%DriftTime Sdc3_%d [KuramaTrack]", i-(NumOfLayersSdcIn+NumOfLayersSDC2));
    HB1( 100*i+11, title1, 120, 0., 120. );
    HB1( 100*i+12, title2, NBinDTSDC3, MinDTSDC3, MaxDTSDC3 );
    HB1( 100*i+13, title3, NBinDLSDC3, MinDLSDC3, MaxDLSDC3 );
    HB1( 100*i+14, title4, 1000, -600., 600. );
    HB1( 100*i+15, title5, 200, -2.0, 2.0 );
    HB2( 100*i+16, title6, 100, -600., 600., 100, -2.0, 2.0 );
    HB2( 100*i+17, title7, 100, -600., 600., 100, -600., 600. );
    HB2( 100*i+22, title22, NBinDTSDC3, MinDTSDC3, MaxDTSDC3, NBinDLSDC3, MinDLSDC3, MaxDLSDC3 );
  }
  /////////////////////

  // FBT1, 2
  for( int i=NumOfLayersSdcIn+NumOfLayersSDC2+NumOfLayersSDC3+1;
       i<=(NumOfLayersSdcIn+NumOfLayersSdcOut); ++i ){
    TString title1 = Form("HitPat Fbt%d", i-(NumOfLayersSdcIn+NumOfLayersSDC2+NumOfLayersSDC3));
    TString title4 = Form("Position Fbt%d", i-(NumOfLayersSdcIn+NumOfLayersSDC2+NumOfLayersSDC3));
    TString title5 = Form("Residual Fbt%d", i-(NumOfLayersSdcIn+NumOfLayersSDC2+NumOfLayersSDC3));
    TString title6 = Form("Resid%%Pos Fbt%d", i-(NumOfLayersSdcIn+NumOfLayersSDC2+NumOfLayersSDC3));
    TString title7 = Form("Y%%Xcal Fbt%d", i-(NumOfLayersSdcIn+NumOfLayersSDC2+NumOfLayersSDC3));
    HB1( 100*i+1, title1, 70, 0., 70. );
    HB1( 100*i+4, title4, 800, -400., 400. );
    HB1( 100*i+5, title5, 200, -2.0, 2.0 );
    HB2( 100*i+6, title6, 100, -600., 600., 100, -1.0, 1.0 );
    HB2( 100*i+7, title7, 100, -600., 600., 100, -600., 600. );
    title1 += " [KuramaTrack]";
    title4 += " [KuramaTrack]";
    title5 += " [KuramaTrack]";
    title6 += " [KuramaTrack]";
    title7 += " [KuramaTrack]";
    HB1( 100*i+11, title1, 70, 0., 70. );
    HB1( 100*i+14, title4, 800, -400., 400. );
    HB1( 100*i+15, title5, 200, -2.0, 2.0 );
    HB2( 100*i+16, title6, 100, -600., 600., 100, -2.0, 2.0 );
    HB2( 100*i+17, title7, 100, -600., 600., 100, -600., 600. );
  }


  // TOF in SdcOut/KuramaTracking
  for( int i=NumOfLayersSdcIn+NumOfLayersSdcOut+1;
       i<=NumOfLayersSdcIn+NumOfLayersSdcOut+2; ++i ){
    TString title1 = Form("HitPat Tof%d", i-(NumOfLayersSdcIn+NumOfLayersSdcOut));
    TString title4 = Form("Position Tof%d", i-(NumOfLayersSdcIn+NumOfLayersSdcOut));
    TString title5 = Form("Residual Tof%d", i-(NumOfLayersSdcIn+NumOfLayersSdcOut));
    TString title6 = Form("Resid%%Pos Tof%d", i-(NumOfLayersSdcIn+NumOfLayersSdcOut));
    TString title7 = Form("Y%%Xcal Tof%d", i-(NumOfLayersSdcIn+NumOfLayersSdcOut));
    HB1( 100*i+1, title1, 200, 0., 200. );
    HB1( 100*i+4, title4, 1000, -1000., 1000. );
    HB1( 100*i+5, title5, 200, -20., 20. );
    HB2( 100*i+6, title6, 100, -1000., 1000., 100, -200., 200. );
    HB2( 100*i+7, title6, 100, -1000., 1000., 100, -1000., 1000. );
    title1 += " [KuramaTrack]";
    title4 += " [KuramaTrack]";
    title5 += " [KuramaTrack]";
    title6 += " [KuramaTrack]";
    title7 += " [KuramaTrack]";
    HB1( 100*i+11, title1, 200, 0., 200. );
    HB1( 100*i+14, title4, 1000, -1000., 1000. );
    HB1( 100*i+15, title5, 200, -20., 20. );
    HB2( 100*i+16, title6, 100, -1000., 1000., 100, -200., 200. );
    HB2( 100*i+17, title7, 100, -1000., 1000., 100, -1000., 1000. );
  }

  HB2( 20001, "Xout%Xin", 100, -200., 200., 100, -200., 200. );
  HB2( 20002, "Yout%Yin", 100, -200., 200., 100, -200., 200. );
  HB2( 20003, "Uout%Uin", 100, -0.5,  0.5,  100, -0.5,  0.5  );
  HB2( 20004, "Vin%Vout", 100, -0.1,  0.1,  100, -0.1,  0.1  );

  HB2( 20021, "Yout%Yin [KuramaTrack]", 100, -150., 150., 120, -300., 300. );
  HB2( 20022, "Vout%Vin [KuramaTrack]", 100, -0.05, 0.05, 100, -0.1, 0.1 );
  HB2( 20023, "Yout%Vin [KuramaTrack]", 100, -0.05, 0.05, 100, -300., 300. );
  HB2( 20024, "Yin%Vout [KuramaTrack]", 100, -0.10, 0.10, 100, -150., 150. );

  ////////////////////////////////////////////
  //Tree
  HBTree( "kurama","tree of KuramaTracking" );
  tree->Branch("evnum",     &event.evnum,    "evnum/I");
  tree->Branch("trigpat",    event.trigpat,  Form("trigpat[%d]/I", NumOfSegTrig));
  tree->Branch("trigflag",   event.trigflag, Form("trigflag[%d]/I", NumOfSegTrig));

  //Hodoscope
  tree->Branch("nhBh2",   &event.nhBh2,   "nhBh2/I");
  tree->Branch("Bh2Seg",   event.Bh2Seg,  "Bh2Seg[nhBh2]/D");
  tree->Branch("tBh2",     event.tBh2,    "tBh2[nhBh2]/D");
  tree->Branch("deBh2",    event.deBh2,   "deBh2[nhBh2]/D");
  tree->Branch("time0",   &event.time0,   "time0/D");

  tree->Branch("nhBh1",   &event.nhBh1,   "nhBh1/I");
  tree->Branch("Bh1Seg",   event.Bh1Seg,  "Bh1Seg[nhBh1]/D");
  tree->Branch("tBh1",     event.tBh1,    "tBh1[nhBh1]/D");
  tree->Branch("deBh1",    event.deBh1,   "deBh1[nhBh1]/D");
  tree->Branch("btof",    &event.btof,    "btof/D");

  tree->Branch("nhSac",   &event.nhSac,   "nhSac/I");
  tree->Branch("nhSac_khodo",   &event.nhSac_khodo,   "nhSac_khodo/I");
  tree->Branch("SacSeg",   event.SacSeg,  "SacSeg[nhSac]/D");
  tree->Branch("tSac",     event.tSac,    "tSac[nhSac]/D");
  tree->Branch("tSac_khodo",     event.tSac_khodo,    "tSac[nhSac_khodo]/D");
  tree->Branch("deSac",    event.deSac,   "deSac[nhSac]/D");

  tree->Branch("nhTof",   &event.nhTof,   "nhTof/I");
  tree->Branch("TofSeg",   event.TofSeg,  "TofSeg[nhTof]/D");
  tree->Branch("tTof",     event.tTof,    "tTof[nhTof]/D");
  tree->Branch("dtTof",    event.dtTof,   "dtTof[nhTof]/D");
  tree->Branch("deTof",    event.deTof,   "deTof[nhTof]/D");

  tree->Branch("wposSdcIn",  event.wposSdcIn,  Form("wposSdcIn[%d]/D", NumOfLayersSdcIn));
  tree->Branch("wposSdcOut", event.wposSdcOut, Form("wposSdcOut[%d]/D", NumOfLayersSdcOut));

  //Tracking
  tree->Branch("ntSdcIn",    &event.ntSdcIn,     "ntSdcIn/I");
  tree->Branch("much",       &event.much,        "much/I");
  tree->Branch("nlSdcIn",    &event.nlSdcIn,     "nlSdcIn/I");
  tree->Branch("nhSdcIn",     event.nhSdcIn,     "nhSdcIn[ntSdcIn]/I");
  tree->Branch("chisqrSdcIn", event.chisqrSdcIn, "chisqrSdcIn[ntSdcIn]/D");
  tree->Branch("x0SdcIn",     event.x0SdcIn,     "x0SdcIn[ntSdcIn]/D");
  tree->Branch("y0SdcIn",     event.y0SdcIn,     "y0SdcIn[ntSdcIn]/D");
  tree->Branch("u0SdcIn",     event.u0SdcIn,     "u0SdcIn[ntSdcIn]/D");
  tree->Branch("v0SdcIn",     event.v0SdcIn,     "v0SdcIn[ntSdcIn]/D");

  tree->Branch("ntSdcOut",   &event.ntSdcOut,     "ntSdcOut/I");
  tree->Branch("nlSdcOut",   &event.nlSdcOut,     "nlSdcOut/I");
  tree->Branch("nhSdcOut",    event.nhSdcOut,     "nhSdcOut[ntSdcOut]/I");
  tree->Branch("chisqrSdcOut",event.chisqrSdcOut, "chisqrSdcOut[ntSdcOut]/D");
  tree->Branch("x0SdcOut",    event.x0SdcOut,     "x0SdcOut[ntSdcOut]/D");
  tree->Branch("y0SdcOut",    event.y0SdcOut,     "y0SdcOut[ntSdcOut]/D");
  tree->Branch("u0SdcOut",    event.u0SdcOut,     "u0SdcOut[ntSdcOut]/D");
  tree->Branch("v0SdcOut",    event.v0SdcOut,     "v0SdcOut[ntSdcOut]/D");

  // KURAMA Tracking
  tree->Branch("ntKurama",    &event.ntKurama,     "ntKurama/I");
  tree->Branch("nlKurama",    &event.nlKurama,     "nlKurama/I");
  tree->Branch("nhKurama",     event.nhKurama,     "nhKurama[ntKurama]/I");
  tree->Branch("chisqrKurama", event.chisqrKurama, "chisqrKurama[ntKurama]/D");
  tree->Branch("stof",         event.stof,         "stof[ntKurama]/D");
  tree->Branch("path",         event.path,         "path[ntKurama]/D");
  tree->Branch("pKurama",      event.pKurama,      "pKurama[ntKurama]/D");
  tree->Branch("qKurama",      event.qKurama,      "qKurama[ntKurama]/D");
  tree->Branch("m2",           event.m2,           "m2[ntKurama]/D");

  tree->Branch("xtgtKurama",   event.xtgtKurama,   "xtgtKurama[ntKurama]/D");
  tree->Branch("ytgtKurama",   event.ytgtKurama,   "ytgtKurama[ntKurama]/D");
  tree->Branch("utgtKurama",   event.utgtKurama,   "utgtKurama[ntKurama]/D");
  tree->Branch("vtgtKurama",   event.vtgtKurama,   "vtgtKurama[ntKurama]/D");

  tree->Branch("thetaKurama",  event.thetaKurama,  "thetaKurama[ntKurama]/D");
  tree->Branch("phiKurama",    event.phiKurama,    "phiKurama[ntKurama]/D");
  tree->Branch("resP",    event.resP,   "resP[ntKurama]/D");

  tree->Branch("xsacKurama",   event.xsacKurama,   "xsacKurama[ntKurama]/D");
  tree->Branch("ysacKurama",   event.ysacKurama,   "ysacKurama[ntKurama]/D");

  tree->Branch("xtofKurama",   event.xtofKurama,   "xtofKurama[ntKurama]/D");
  tree->Branch("ytofKurama",   event.ytofKurama,   "ytofKurama[ntKurama]/D");
  tree->Branch("utofKurama",   event.utofKurama,   "utofKurama[ntKurama]/D");
  tree->Branch("vtofKurama",   event.vtofKurama,   "vtofKurama[ntKurama]/D");
  tree->Branch("tofsegKurama", event.tofsegKurama, "tofsegKurama[ntKurama]/D");

  tree->Branch("vpx",          event.vpx,          Form("vpx[%d]/D", NumOfLayersVP));
  tree->Branch("vpy",          event.vpy,          Form("vpy[%d]/D", NumOfLayersVP));
  tree->Branch("vpseg",        event.vpseg,        Form("vpseg[%d]/I", NumOfLayersVP));

  event.resL.resize(NumOfLayersSdcIn+NumOfLayersSdcOut+2);
  event.resG.resize(NumOfLayersSdcIn+NumOfLayersSdcOut+2);
  // tree->Branch( "resL", &event.resL );
  // tree->Branch( "resG", &event.resG );
  for( int i=0; i<NumOfLayersSdcIn; ++i ){
    tree->Branch( Form("ResL%d",i+ 1), &event.resL[i] );
  }

  for( int i=0; i<NumOfLayersSdcOut; ++i ){
    tree->Branch( Form("ResL%d",i+31), &event.resL[i+NumOfLayersSdcIn] );
  }

  tree->Branch( "ResL41", &event.resL[NumOfLayersSdcIn+NumOfLayersSdcOut] );
  tree->Branch( "ResL42", &event.resL[NumOfLayersSdcIn+NumOfLayersSdcOut+1] );

  for( int i=0; i<NumOfLayersSdcIn; ++i ){
    tree->Branch( Form("ResG%d",i+ 1), &event.resG[i] );
  }

  for( int i=0; i<NumOfLayersSdcOut; ++i ){
    tree->Branch( Form("ResG%d",i+31), &event.resG[i+NumOfLayersSdcIn] );
  }

  tree->Branch( "ResG41", &event.resG[NumOfLayersSdcIn+NumOfLayersSdcOut] );
  tree->Branch( "ResG42", &event.resG[NumOfLayersSdcIn+NumOfLayersSdcOut+1] );

  tree->Branch("tTofCalc",  event.tTofCalc,  "tTofCalc[3]/D");
  tree->Branch("utTofSeg",  event.utTofSeg,  Form( "utTofSeg[%d]/D", NumOfSegTOF ) );
  tree->Branch("dtTofSeg",  event.dtTofSeg,  Form( "dtTofSeg[%d]/D", NumOfSegTOF ) );
  tree->Branch("udeTofSeg", event.udeTofSeg, Form( "udeTofSeg[%d]/D", NumOfSegTOF ) );
  tree->Branch("ddeTofSeg", event.ddeTofSeg, Form( "ddeTofSeg[%d]/D", NumOfSegTOF ) );
  tree->Branch("tofua",     event.tofua,     Form( "tofua[%d]/D", NumOfSegTOF ) );
  tree->Branch("tofda",     event.tofda,     Form( "tofda[%d]/D", NumOfSegTOF ) );

  HPrint();
  return true;
}

//______________________________________________________________________________
bool
ConfMan::InitializeParameterFiles( void )
{
  return
    ( InitializeParameter<DCGeomMan>("DCGEO")        &&
      InitializeParameter<DCDriftParamMan>("DCDRFT") &&
      InitializeParameter<DCTdcCalibMan>("DCTDC")    &&
      InitializeParameter<HodoParamMan>("HDPRM")     &&
      InitializeParameter<HodoPHCMan>("HDPHC")       &&
      InitializeParameter<FieldMan>("FLDMAP")        &&
      InitializeParameter<UserParamMan>("USER")      );
}

//______________________________________________________________________________
bool
ConfMan::FinalizeProcess( void )
{
  return true;
}
