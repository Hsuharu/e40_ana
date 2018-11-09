/**
 *  file: UserSdcOutTracking.cc
 *  date: 2017.04.10
 *
 */

#include <cmath>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

#include "ConfMan.hh"
#include "DCRawHit.hh"
#include "DetectorID.hh"
#include "RMAnalyzer.hh"
#include "RootHelper.hh"
#include "KuramaLib.hh"
#include "RawData.hh"
#include "UnpackerManager.hh"
#include "VEvent.hh"

#define HodoCut     0
#define MaxMultiCut 0
#define UseTOF      1 // use TOF for SdcOutTracking
//#define UseTOF      0 // don't use TOF for SdcOutTracking

namespace
{
  using namespace root;
  const std::string& classname("EventSdcOutTracking");
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
class EventSdcOutTracking : public VEvent
{
private:
  RawData      *rawData;
  DCAnalyzer   *DCAna;
  HodoAnalyzer *hodoAna;

public:
        EventSdcOutTracking( void );
       ~EventSdcOutTracking( void );
  bool  ProcessingBegin( void );
  bool  ProcessingEnd( void );
  bool  ProcessingNormal( void );
  bool  InitializeHistograms( void );
  void  InitializeEvent( void );
};

//______________________________________________________________________________
EventSdcOutTracking::EventSdcOutTracking( void )
  : VEvent(),
    rawData(0),
    DCAna( new DCAnalyzer ),
    hodoAna( new HodoAnalyzer )
{
}

//______________________________________________________________________________
EventSdcOutTracking::~EventSdcOutTracking( void )
{
  if( DCAna )   delete DCAna;
  if( hodoAna ) delete hodoAna;
  if( rawData ) delete rawData;
}

//______________________________________________________________________________
bool
EventSdcOutTracking::ProcessingBegin( void )
{
  InitializeEvent();
  return true;
}

//______________________________________________________________________________
struct Event
{
  int evnum;

  int trignhits;
  int trigpat[NumOfSegTrig];
  int trigflag[NumOfSegTrig];

  int nhBh2;
  double Bh2Seg[MaxHits];
  double tBh2[MaxHits];
  double deBh2[MaxHits];

  int nhBh1;
  double Bh1Seg[MaxHits];
  double tBh1[MaxHits];
  double deBh1[MaxHits];

  int nhTof;
  double TofSeg[MaxHits];
  double tTof[MaxHits];
  double dtTof[MaxHits];
  double deTof[MaxHits];

  double btof[MaxHits];
  double stof[MaxHits];

  int nhit[NumOfLayersSdcOut+2];
  int nlayer;
  double wpos[NumOfLayersSdcOut+2][MaxHits];
  double pos[NumOfLayersSdcOut+2][MaxHits];

  int tdc[MaxHits];

  int ntrack;
  double chisqr[MaxHits];
  double x0[MaxHits];
  double y0[MaxHits];
  double u0[MaxHits];
  double v0[MaxHits];
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
EventSdcOutTracking::ProcessingNormal( void )
{
  static const std::string func_name("["+classname+"::"+__func__+"()]");

  static const double MinDeBH2   = gUser.GetParameter("DeBH2", 0);
  static const double MaxDeBH2   = gUser.GetParameter("DeBH2", 1);
  static const double MinDeBH1   = gUser.GetParameter("DeBH1", 0);
  static const double MaxDeBH1   = gUser.GetParameter("DeBH1", 1);
  static const double MinBeamToF = gUser.GetParameter("BTOF",  1);
  static const double MaxBeamToF = gUser.GetParameter("BTOF",  1);
  static const double MinDeTOF   = gUser.GetParameter("DeTOF",   0);
  static const double MaxDeTOF   = gUser.GetParameter("DeTOF",   1);
  static const double MinTimeTOF = gUser.GetParameter("TimeTOF", 0);
  static const double MaxTimeTOF = gUser.GetParameter("TimeTOF", 1);
//  static const double MinTimeFBT1 = gUser.GetParameter("TimeFBT1", 0);
//  static const double MaxTimeFBT1 = gUser.GetParameter("TimeFBT1", 1);
//  static const double MinTimeFBT2 = gUser.GetParameter("TimeFBT2", 0);
//  static const double MaxTimeFBT2 = gUser.GetParameter("TimeFBT2", 1);
  static const double dTOfs      = gUser.GetParameter("dTOfs",   0);
  static const double MinTimeL1  = gUser.GetParameter("TimeL1",  0);
  static const double MaxTimeL1  = gUser.GetParameter("TimeL1",  1);
  static const double MinTotSDC2 = gUser.GetParameter("MinTotSDC2", 0);
  static const double MinTotSDC3 = gUser.GetParameter("MinTotSDC3", 0);

#if MaxMultiCut
  static const double MaxMultiHitSdcOut = gUser.GetParameter("MaxMultiHitSdcOut");
#endif

  rawData = new RawData;
  rawData->DecodeHits();

  gRM.Decode();
  event.evnum = gRM.EventNumber();

  //Misc
  {
    const HodoRHitContainer &cont=rawData->GetTrigRawHC();
    int trignhits = 0;
    int nh=cont.size();
    for( int i=0; i<nh; ++i ){
      HodoRawHit *hit=cont[i];
      int seg = hit->SegmentId()+1;
      int tdc = hit->GetTdc1();
      if( tdc>0 ){
	event.trigpat[trignhits++] = seg;
	event.trigflag[seg-1]      = tdc;
      }
    }
    event.trignhits = trignhits;
  }

  HF1( 1, 0. );

  if( event.trigflag[SpillEndFlag]>0 ) return true;

  HF1( 1, 1. );

  //////////////BH2 Analysis
  hodoAna->DecodeBH2Hits(rawData);
  int nhBh2 = hodoAna->GetNHitsBH2();
  event.nhBh2 = nhBh2;
#if HodoCut
  if( nhBh2==0 ) return true;
#endif

  double time0 = -9999.;
  {
    int nhOk = 0;
    for( int i=0; i<nhBh2; ++i ){
      BH2Hit *hit = hodoAna->GetHitBH2(i);
      double ct0 = hit->CTime0();
      double de  = hit->DeltaE();
      double cmt = hit->CMeanTime();
      if( ct0 < time0 ) time0 = ct0;
      event.Bh2Seg[i] = hit->SegmentId()+1;
      event.tBh2[i]   = cmt;
      event.deBh2[i]  = de;
      if( MinDeBH2<de && de<MaxDeBH2 ){
	++nhOk;
      }
    }
#if HodoCut
    if( nhOk==0 ) return true;
#endif
  }

  //////////////BH1 Analysis
  hodoAna->DecodeBH1Hits(rawData);
  int nhBh1 = hodoAna->GetNHitsBH1();
  event.nhBh1 = nhBh1;
#if HodoCut
  if( nhBh1==0 ) return true;
#endif
  {
    int nhOk = 0;
    for( int i=0; i<nhBh1; ++i ){
      Hodo2Hit *hit = hodoAna->GetHitBH1(i);
      double cmt  = hit->CMeanTime();
      double de   = hit->DeltaE();
      double btof = cmt-time0;
      if( de<MinDeBH1 || MaxDeBH1<de )
	continue;
      event.Bh1Seg[i] = hit->SegmentId()+1;
      event.tBh1[i]   = cmt;
      event.deBh1[i]  = de;
      event.btof[i]   = btof;
      if( MinBeamToF<btof && btof<MaxBeamToF ){
	++nhOk;
      }
    }
#if HodoCut
    if( nhOk==0 ) return true;
#endif
  }

  HF1( 1, 2. );

  HodoClusterContainer TOFCont;
  //////////////Tof Analysis
  hodoAna->DecodeTOFHits( rawData );
  //  hodoAna->TimeCutTOF(7, 25);
  int nhTof = hodoAna->GetNClustersTOF();
#if HodoCut
  if( nhTof!=0 ) return true;
#endif
  event.nhTof = nhTof;
  {
    int nhOk = 0;
    for( int i=0; i<nhTof; ++i ){
      HodoCluster *hit = hodoAna->GetClusterTOF(i);
      if( !hit ) continue;
      double cmt  = hit->CMeanTime();
      double dt   = hit->TimeDif();
      double de   = hit->DeltaE();
      double stof = cmt-time0;
      event.TofSeg[i] = hit->MeanSeg()+1;
      event.tTof[i]   = cmt;
      event.dtTof[i]  = dt;
      event.deTof[i]  = de;
      event.stof[i]   = stof;
      TOFCont.push_back( hit );
      if( MinDeTOF<de  && de<MaxDeTOF  &&
	  MinTimeTOF<stof && stof<MaxTimeTOF ){
	++nhOk;
      }
    }
#if HodoCut
    if( nhOk==0 ) return true;
#endif
  }

  HF1( 1, 3. );

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

  HF1( 1, 4. );

  HF1( 1, 5. );

  HF1( 1, 6. );

#if 0
  static const double MaxMultiHitSdcIn  = gUser.GetParameter("MaxMultiHitSdcIn");
  //////////////SdcIn number of hit layer
  DCAna->DecodeSdcInHits( rawData );
  double multi_SdcIn=0.;
  for( int layer=1; layer<=NumOfLayersSdcIn; ++layer ){
    int nhIn = DCAna->GetSdcInHC(layer).size();
    multi_SdcIn += double(nhIn);
  }
# if MaxMultiCut
  if( multi_SdcIn/double(NumOfLayersSdcIn) > MaxMultiHitSdcIn )
   return true;
# endif
#endif

  HF1( 1, 10. );

  double offset = flag_tof_stop ? 0 : dTOfs;
  DCAna->DecodeSdcOutHits( rawData, offset );
  DCAna->TotCutSDC2( MinTotSDC2 );
  DCAna->TotCutSDC3( MinTotSDC3 );
  double multi_SdcOut = 0.;
  {
      for( int layer=1; layer<=NumOfLayersSdcOut; ++layer ) {
      //std::cout << "layer : " << layer << std::endl; 
	/*	if ( layer==9 )
	  hodoAna->TimeCutFBT1(0, 1, MinTimeFBT1, MaxTimeFBT1);
      if ( layer==10 )
	hodoAna->TimeCutFBT1(0, 0, MinTimeFBT1, MaxTimeFBT1);
      if ( layer==11 )
	hodoAna->TimeCutFBT1(1, 1, MinTimeFBT1, MaxTimeFBT1);
      if ( layer==12 )
	hodoAna->TimeCutFBT1(1, 0, MinTimeFBT1, MaxTimeFBT1);
      if ( layer==13 )
	hodoAna->TimeCutFBT2(0, 1, MinTimeFBT2, MaxTimeFBT2);
      if ( layer==14 )
	hodoAna->TimeCutFBT2(0, 0, MinTimeFBT2, MaxTimeFBT2);
      if ( layer==15 )
	hodoAna->TimeCutFBT2(1, 1, MinTimeFBT2, MaxTimeFBT2);
      if ( layer==16 )
	hodoAna->TimeCutFBT2(1, 0, MinTimeFBT2, MaxTimeFBT2);
	*/
      
      const DCHitContainer &contOut =DCAna->GetSdcOutHC(layer);
      int nhOut=contOut.size();
      if( nhOut>0 ) event.nlayer++;
      multi_SdcOut += double(nhOut);
      if( layer<10 )
	HF1( 100*layer, nhOut );
      event.nhit[layer-1] = nhOut;
      if( nhOut>MaxHits ){
	// std::cerr << "#W " << func_name << " too many hits "
	// 	  << nhOut << "/" << MaxHits << std::endl;
	nhOut = MaxHits;
      }

      for( int i=0; i<nhOut; ++i ){
	DCHit *hit=contOut[i];
	double wire=hit->GetWire();
	double wp=hit->GetWirePosition();
	HF1( 100*layer+1, wire-0.5 );
	int nhtdc = hit->GetTdcSize();
	if( nhtdc==1 ) {
	  event.wpos[layer-1][i] = wp;
	}// else { std::cout << "discrepancy..." << std::endl; }

	for( int k=0; k<nhtdc; k++ ){
	  //	for( int k=0; k<1; k++ ){
	  int tdc = hit->GetTdcVal(k);
	  HF1( 100*layer+2, tdc );
	  HF1( 10000*layer+int(wire), tdc );
	  HF2( 1000*layer, tdc, wire-0.5 );
	  if( layer == 1) event.tdc[k] = tdc;
	}
	int nhdt = hit->GetDriftTimeSize();
	for( int k=0; k<nhdt; k++ ){
	  double dt = hit->GetDriftTime(k);

	  if(flag_tof_stop) HF1( 100*layer+3, dt );
	  else              HF1( 100*layer+6, dt );
	  HF1( 10000*layer+1000+int(wire), dt );

	  double tot = hit->GetTot(k);
	  HF1( 100*layer+5, tot);
	}
	int nhdl = hit->GetDriftTimeSize();
	for( int k=0; k<nhdl; k++ ){
	  double dl = hit->GetDriftLength(k);
	  HF1( 100*layer+4, dl );
	}
      }
    }
  }

#if MaxMultiCut
  if( multi_SdcOut/double(NumOfLayersSdcOut) > MaxMultiHitSdcOut )
    return true;
#endif

  HF1( 1, 11. );

  // std::cout << "==========TrackSearch SdcOut============" << std::endl;
  if(flag_tof_stop){
#if UseTOF
    DCAna->TrackSearchSdcOut( TOFCont );
#else
    DCAna->TrackSearchSdcOut();
#endif
  }else{
    DCAna->TrackSearchSdcOut();
  }

#if 1
  DCAna->ChiSqrCutSdcOut(30.);
  int nt=DCAna->GetNtracksSdcOut();
  if( MaxHits<nt ){
    std::cout << "#W " << func_name << " "
	      << "too many ntSdcOut " << nt << "/" << MaxHits << std::endl;
    nt = MaxHits;
  }
  event.ntrack=nt;
  HF1( 10, double(nt) );
  for( int it=0; it<nt; ++it ){
    DCLocalTrack *tp=DCAna->GetTrackSdcOut(it);
    if(!tp) continue;
    int nh=tp->GetNHit();
    double chisqr    = tp->GetChiSquare();
    double chisqr1st = tp->GetChiSquare1st();
    double x0=tp->GetX0(), y0=tp->GetY0();
    double u0=tp->GetU0(), v0=tp->GetV0();
    double theta = tp->GetTheta();
    int    nitr  = tp->GetNIteration();
    event.chisqr[it]=chisqr;
    event.x0[it]=x0;
    event.y0[it]=y0;
    event.u0[it]=u0;
    event.v0[it]=v0;

    HF1( 11, double(nh) );
    HF1( 12, chisqr );
    HF1( 14, x0 ); HF1( 15, y0 );
    HF1( 16, u0 ); HF1( 17, v0 );
    HF2( 18, x0, u0 ); HF2( 19, y0, v0 );
    HF2( 20, x0, y0 );

    HF1( 28, nitr );
    HF1( 29, chisqr1st );
    HF1( 30, chisqr1st-chisqr );
    if( theta<=10. )
      HF1( 31, chisqr1st-chisqr );
    if( 10.<theta && theta<=20. )
      HF1( 32, chisqr1st-chisqr );
    if( 20.<theta && theta<=30. )
      HF1( 33, chisqr1st-chisqr );
    if( 30.<theta && theta<=40. )
      HF1( 34, chisqr1st-chisqr );
    if( 40.<theta )
      HF1( 35, chisqr1st-chisqr );

    double xtof=tp->GetX( zTOF ), ytof=tp->GetY( zTOF );
    double utof=u0, vtof=v0;
    HF1( 21, xtof ); HF1( 22, ytof );
    HF1( 23, utof ); HF1( 24, vtof );
    HF2( 25, xtof, utof ); HF2( 26, ytof, vtof );
    HF2( 27, xtof, ytof );
   
    bool FBT_flag = false;
    int n_fbt=0;
    
    for( int ih=0; ih<nh; ++ih ){
      DCLTrackHit *hit=tp->GetHit(ih);
      if(!hit) continue;

      int layerId = 0;
      layerId = hit->GetLayer()-30; 
      
      //if( layerId>10 ) layerId -=2;
      
      if( 10<layerId && layerId<20 ) layerId += 6; // 17 ~ TOF
      if( 49<layerId ) layerId -= 41; // 9 ~ FBT
      
      HF1( 13, hit->GetLayer() );

      if( 9<=layerId && layerId<=16 )
	++n_fbt;
      //if( n_fbt>2 )
      if( n_fbt>3 )
	FBT_flag = true;
      //      std::cout << "NumOfFBTLayers : " << n_fbt << std::endl;
      
      if( !FBT_flag ){
	HF1( 36, double(nh) );
	HF1( 37, chisqr );
      }
      if( FBT_flag ){
	HF1( 38, double(nh) );
	HF1( 39, chisqr );
      }
      
      double wire=hit->GetWire();
      double dt=hit->GetDriftTime(), dl=hit->GetDriftLength();
      HF1( 100*layerId+11, wire-0.5 );
      HF1( 100*layerId+12, dt );
      HF1( 100*layerId+13, dl );
      double xcal=hit->GetXcal(), ycal=hit->GetYcal();
      double pos=hit->GetLocalHitPos(), res=hit->GetResidual();
      HF1( 100*layerId+14, pos );
      HF1( 100*layerId+15, res );
      HF2( 100*layerId+16, pos, res );
      HF2( 100*layerId+17, xcal, ycal );
      //      HF1( 100000*layerId+50000+wire, res);
      double wp=hit->GetWirePosition();
      double sign=1.;
      if( pos-wp<0. ) sign=-1;
      HF2( 100*layerId+18, sign*dl, res );
      double xlcal=hit->GetLocalCalPos();
      HF2( 100*layerId+19, dt, xlcal-wp );

      HF2( 100*layerId+31, xcal, res );
      HF2( 100*layerId+32, ycal, res );
      HF2( 100*layerId+33, u0, res );
      HF2( 100*layerId+34, v0, res );
      
      double tot = hit->GetTot();
      HF1( 100*layerId+40, tot);

      if (theta>=0 && theta<15)
	HF1( 100*layerId+71, res );
      else if (theta>=15 && theta<30)
	HF1( 100*layerId+72, res );
      else if (theta>=30 && theta<45)
	HF1( 100*layerId+73, res );
      else if (theta>=45)
	HF1( 100*layerId+74, res );

      if (std::abs(dl-std::abs(xlcal-wp))<2.0) {
	HFProf( 100*layerId+20, dt, std::abs(xlcal-wp) );
	HF2( 100*layerId+22, dt, std::abs(xlcal-wp) );
	HFProf( 100000*layerId+3000+int(wire), xlcal-wp,dt );
	HF2( 100000*layerId+4000+int(wire), xlcal-wp,dt );
      }
    }
  }
#endif

  HF1( 1, 12. );

  return true;
}

//______________________________________________________________________________
void
EventSdcOutTracking::InitializeEvent( void )
{
  event.evnum     = 0;
  event.trignhits = 0;

  event.nlayer  = -1;
  event.ntrack  = -1;
  event.nhBh2   = -1;
  event.nhBh1   = -1;
  event.nhTof   = -1;

  for( int it=0; it<MaxHits; it++){
    event.Bh2Seg[it] = -1;
    event.tBh2[it]   = -9999.;
    event.deBh2[it]  = -9999.;

    event.Bh1Seg[it] = -1;
    event.tBh1[it]   = -9999.;
    event.deBh1[it]  = -9999.;
    event.btof[it]   = -9999.;
    event.stof[it]   = -9999.;

    event.TofSeg[it] = -1;
    event.tTof[it]   = -9999.;
    event.dtTof[it]  = -9999.;
    event.deTof[it]  = -9999.;
  }
  for( int it=0; it<NumOfLayersSdcOut; ++it ){
    event.nhit[it] = 0;
    for( int that=0; that<MaxHits; ++that ){
      event.wpos[it][that] = -9999.;
      event.pos[it][that] = -9999.;
    }
  }
  for( int it=0; it<MaxHits; ++it ){
    event.tdc[it]    = -1;

    event.chisqr[it] = -1.;
    event.x0[it] = -9999.;
    event.y0[it] = -9999.;
    event.u0[it] = -9999.;
    event.v0[it] = -9999.;
  }
  for( int it=0; it<NumOfSegTrig; it++){
    event.trigpat[it]  = -1;
    event.trigflag[it] = -1;
  }
}

//______________________________________________________________________________
bool
EventSdcOutTracking::ProcessingEnd( void )
{
  tree->Fill();
  return true;
}

//______________________________________________________________________________
VEvent*
ConfMan::EventAllocator( void )
{
  return new EventSdcOutTracking;
}

//______________________________________________________________________________
namespace
{
  // const int    NbinSdcOutTdc = 1000;
  // const double MinSdcOutTdc  =    0.;
  // const double MaxSdcOutTdc  = 1000.;
  const int    NbinSdcOutTdc = 2000;
  const double MinSdcOutTdc  =    0.;
  const double MaxSdcOutTdc  = 2000.;

  const int    NbinSDC2DT = 240;
  const double MinSDC2DT  = -50.;
  const double MaxSDC2DT  = 150.;
  const int    NbinSDC2DL =  90;
  const double MinSDC2DL  =  -2.;
  const double MaxSDC2DL  =   7.;

  const int    NbinSDC3DT = 480;
  const double MinSDC3DT  = -50.;
  const double MaxSDC3DT  = 350.;
  const int    NbinSDC3DL = 180;
  const double MinSDC3DL  =  -3.;
  const double MaxSDC3DL  =  15.;
}
//______________________________________________________________________________
bool
ConfMan::InitializeHistograms( void )
{
  HB1( 1, "Status", 20, 0., 20. );

  //***********************Chamber
  // SDC2
  for( int i=1; i<=NumOfLayersSDC2; ++i ){
    TString title0 = Form("#Hits SDC2#%2d", i);
    TString title1 = Form("Hitpat SDC2#%2d", i);
    TString title2 = Form("Tdc SDC2#%2d", i);
    TString title3 = Form("Drift Time SDC2#%2d", i);
    TString title4 = Form("Drift Length SDC2#%2d", i);
    TString title5 = Form("TOT SDC2#%2d", i);
    TString title6 = Form("Drift Time SDC2#%2d (BH2 timing)", i);
    HB1( 100*i+0, title0, MaxWireSDC2+1, 0., double(MaxWireSDC2+1) );
    HB1( 100*i+1, title1, MaxWireSDC2+1, 0., double(MaxWireSDC2+1) );
    HB1( 100*i+2, title2, NbinSdcOutTdc, MinSdcOutTdc, MaxSdcOutTdc );
    HB1( 100*i+3, title3, NbinSDC2DT, MinSDC2DT, MaxSDC2DT );
    HB1( 100*i+4, title4, NbinSDC2DL, MinSDC2DL, MaxSDC2DL );
    HB1( 100*i+5, title5, 360,        0,         300);
    HB1( 100*i+6, title6, NbinSDC2DT, MinSDC2DT, MaxSDC2DT );
    for ( int wire=1; wire<=MaxWireSDC2; wire++ ) {
      TString title11 = Form("Tdc SDC2#%2d Wire#%d", i, wire);
      TString title12 = Form("Drift Time SDC2#%2d Wire#%d", i, wire);
      TString title13 = Form("Drift Length SDC2#%2d Wire#%d", i, wire);
      HB1( 10000*i+wire, title11, NbinSdcOutTdc, MinSdcOutTdc, MaxSdcOutTdc );
      HB1( 10000*i+1000+wire, title12, NbinSDC2DT, MinSDC2DT, MaxSDC2DT );
      HB1( 10000*i+2000+wire, title13, NbinSDC2DL, MinSDC2DL, MaxSDC2DL );
    }
  }

  // SDC3
  for( int i=1; i<=NumOfLayersSDC3; ++i ){
    int MaxWire = ( i==1 || i==2 ) ? MaxWireSDC3Y : MaxWireSDC3X;
    TString title0 = Form("#Hits SDC3#%2d", i);
    TString title1 = Form("Hitpat SDC3#%2d", i);
    TString title2 = Form("Tdc SDC3#%2d", i);
    TString title3 = Form("Drift Time SDC3#%2d", i);
    TString title4 = Form("Drift Length SDC3#%2d", i);
    TString title5 = Form("TOT SDC2#%2d", i);
    TString title6 = Form("Drift Time SDC3#%2d (BH2 timing)", i);
    HB1( 100*(i+NumOfLayersSDC3)+0, title0, MaxWire+1, 0., double(MaxWire+1) );
    HB1( 100*(i+NumOfLayersSDC3)+1, title1, MaxWire+1, 0., double(MaxWire+1) );
    HB1( 100*(i+NumOfLayersSDC3)+2, title2, NbinSdcOutTdc, MinSdcOutTdc, MaxSdcOutTdc );
    HB1( 100*(i+NumOfLayersSDC3)+3, title3, NbinSDC3DT, MinSDC3DT, MaxSDC3DT );
    HB1( 100*(i+NumOfLayersSDC3)+4, title4, NbinSDC3DL, MinSDC3DL, MaxSDC3DL );
    HB1( 100*(i+NumOfLayersSDC3)+5, title5, 360,        0,         300);
    HB1( 100*(i+NumOfLayersSDC3)+6, title6, NbinSDC3DT, MinSDC3DT, MaxSDC3DT );
    for ( int wire=1; wire<=MaxWire; wire++ ) {
      TString title11 = Form("Tdc SDC3#%2d Wire#%d", i, wire);
      TString title12 = Form("Drift Time SDC3#%2d Wire#%d", i, wire);
      TString title13 = Form("Drift Length SDC3#%2d Wire#%d", i, wire);
      HB1( 10000*(i+4)+wire, title11, NbinSdcOutTdc, MinSdcOutTdc, MaxSdcOutTdc );
      HB1( 10000*(i+4)+1000+wire, title12, NbinSDC3DT, MinSDC3DT, MaxSDC3DT );
      HB1( 10000*(i+4)+2000+wire, title13, NbinSDC3DL, MinSDC3DL, MaxSDC3DL );
    }
  }

  // Tracking Histgrams
  HB1( 10, "#Tracks SdcOut", 10, 0., 10. );
  HB1( 11, "#Hits of Track SdcOut", 20, 0., 20. );
  HB1( 12, "Chisqr SdcOut", 500, 0., 50. );
  HB1( 13, "LayerId SdcOut", 60, 30., 90. );
  HB1( 14, "X0 SdcOut", 1400, -1200., 1200. );
  HB1( 15, "Y0 SdcOut", 1000, -500., 500. );
  HB1( 16, "U0 SdcOut", 200, -0.35, 0.35 );
  HB1( 17, "V0 SdcOut", 200, -0.20, 0.20 );
  HB2( 18, "U0%X0 SdcOut", 120, -1200., 1200., 100, -0.40, 0.40 );
  HB2( 19, "V0%Y0 SdcOut", 100, -500., 500., 100, -0.20, 0.20 );
  HB2( 20, "X0%Y0 SdcOut", 100, -1200., 1200., 100, -500, 500 );
  HB1( 21, "Xtof SdcOut", 1400, -1200., 1200. );
  HB1( 22, "Ytof SdcOut", 1000, -500., 500. );
  HB1( 23, "Utof SdcOut", 200, -0.35, 0.35 );
  HB1( 24, "Vtof SdcOut", 200, -0.20, 0.20 );
  HB2( 25, "Utof%Xtof SdcOut", 100, -1200., 1200., 100, -0.40, 0.40 );
  HB2( 26, "Vtof%Ytof SdcOut", 100, -500., 500., 100, -0.20, 0.20 );
  HB2( 27, "Xtof%Ytof SdcOut", 100, -1200., 1200., 100, -500, 500 );

  HB1( 28, "NIteration SdcOut", 100, 0., 100. );
  HB1( 29, "Chisqr1st SdcOut", 500, 0., 50. );
  HB1( 30, "Chisqr1st-Chisqr SdcOut", 500, 0., 10. );
  HB1( 31, "Chisqr1st-Chisqr SdcOut (0<theta<10)", 500, 0., 10. );
  HB1( 32, "Chisqr1st-Chisqr SdcOut (10<theta<20)", 500, 0., 10. );
  HB1( 33, "Chisqr1st-Chisqr SdcOut (20<theta<30)", 500, 0., 10. );
  HB1( 34, "Chisqr1st-Chisqr SdcOut (30<theta<40)", 500, 0., 10. );
  HB1( 35, "Chisqr1st-Chisqr SdcOut (40<theta)", 500, 0., 10. );
  HB1( 36, "#Hits of Track SdcOut(SDC)", 20, 0., 20. );
  HB1( 37, "Chisqr SdcOut(SDC)", 500, 0., 50. );
  HB1( 38, "#Hits of Track SdcOut(FBT)", 20, 0., 20. );
  HB1( 39, "Chisqr SdcOut(FBT)", 500, 0., 50. );

  //for( int i=1; i<=NumOfLayersSdcOut+2; ++i ){
  for( int i=1; i<=NumOfLayersSdcOut+4; ++i ){
    int MaxWire = 0;
    if( i==1 || i==2 || i==3 || i==4 )
      MaxWire = MaxWireSDC2;
    if( i==5 || i==6 )
      MaxWire = MaxWireSDC3Y;
    if( i==7 || i==8 )
      MaxWire = MaxWireSDC3X;
    if( i==9 || i==10 || i==11 || i==12 )
      MaxWire = MaxSegFBT1;
    if( i==13 || i==14 || i==15 || i==16 )
      MaxWire = MaxSegFBT2;
    if( i==17 || i==18 || i==19 || i==20 ) 
      MaxWire = NumOfSegTOF;
    
    HB2( 1000*i, Form("Wire%%Tdc for LayerId = %d", i),
	 NbinSdcOutTdc/4, MinSdcOutTdc, MaxSdcOutTdc,
	 MaxWire+1, 0., double(MaxWire+1) );

    double MaxDL=1., MaxDT=1.;
    if( i==1 || i==2 || i==3 || i==4 ){
      MaxDL = MaxSDC2DL;
      MaxDT = MaxSDC2DT;
    }
    if( i==5 || i==6 || i==7 || i==8 ){
      MaxDL = MaxSDC3DL;
      MaxDT = MaxSDC3DT;
    }
        if ( i == 9 || i == 10 ) {
    MaxDL = MaxSDC3DL;
    MaxDT = MaxSDC3DT;
    }

    TString title11 = Form("HitPat SdcOut%2d [Track]", i);
    TString title12 = Form("DriftTime SdcOut%2d [Track]", i);
    TString title13 = Form("DriftLength SdcOut%2d [Track]", i);
    TString title14 = Form("Position SdcOut%2d", i);
    TString title15 = Form("Residual SdcOut%2d", i);
    TString title16 = Form("Resid%%Pos SdcOut%2d", i);
    TString title17 = Form("Y%%Xcal SdcOut%2d", i);
    TString title18 = Form("Res%%DL SdcOut%2d", i);
    TString title19 = Form("HitPos%%DriftTime SdcOut%2d", i);
    TString title20 = Form("DriftLength%%DriftTime SdcOut%2d", i);
    TString title21 = title15 + " [w/o Self]";
    TString title22 = title20;
    TString title40 = Form("TOT SdcOut%2d [Track]", i);
    TString title71 = Form("Residual SdcOut%2d (0<theta<15)", i);
    TString title72 = Form("Residual SdcOut%2d (15<theta<30)", i);
    TString title73 = Form("Residual SdcOut%2d (30<theta<45)", i);
    TString title74 = Form("Residual SdcOut%2d (45<theta)", i);
    HB1( 100*i+11, title11, MaxWire, 0., MaxWire );
    HB1( 100*i+12, title12, 600, -100, 400 );
    HB1( 100*i+13, title13, 100, -5, MaxDL );
    HB1( 100*i+14, title14, 100, -1000., 1000. );
    //if( i<=NumOfLayersSdcOut )  
    if( i<=NumOfLayersSdcOut+4 )
      HB1( 100*i+15, title15, 1000, -5.0, 5.0 );
    else
      HB1( 100*i+15, title15, 1000, -1000.0, 1000.0 );
    //if( i<=NumOfLayersSdcOut )
    if( i<=NumOfLayersSdcOut+4 )
        HB2( 100*i+16, title16, 400, -1000., 1000., 100, -1.0, 1.0 );
    else
      HB2( 100*i+16, title16, 100, -1000., 1000., 100, -1000.0, 1000.0 );
    HB2( 100*i+17, title17, 100, -1000., 1000., 100, -1000., 1000. );
    if( i<=NumOfLayersSDC2 )
      HB2( 100*i+18, title18, 110, -5.5, 5.5, 100, -1.0, 1.0 );
    else
      HB2( 100*i+18, title18, 110, -11., 11., 100, -1.0, 1.0 );
    HB2( 100*i+19, title19, 200, -50., MaxDT, 200, -MaxDL, MaxDL );
    HBProf( 100*i+20, title20, 100, -50, 300, 0, MaxDL );
    HB2( 100*i+22, title22, 200, -50, MaxDT, 100, -0.5, MaxDL );
    HB1( 100*i+21, title21, 200, -5.0, 5.0 );
    HB2( 100*i+31, Form("Resid%%X SdcOut %d", i), 100, -1000., 1000., 100, -2., 2. );
    HB2( 100*i+32, Form("Resid%%Y SdcOut %d", i), 100, -1000., 1000., 100, -2., 2. );
    HB2( 100*i+33, Form("Resid%%U SdcOut %d", i), 100, -0.5, 0.5, 100, -2., 2. );
    HB2( 100*i+34, Form("Resid%%V SdcOut %d", i), 100, -0.5, 0.5, 100, -2., 2. );
    HB1( 100*i+40, title40, 360,    0, 300 );
    HB1( 100*i+71, title71, 200, -5.0, 5.0 );
    HB1( 100*i+72, title72, 200, -5.0, 5.0 );
    HB1( 100*i+73, title73, 200, -5.0, 5.0 );
    HB1( 100*i+74, title74, 200, -5.0, 5.0 );

    for (int j=1; j<=MaxWireSDC2; j++) {
      TString title = Form("XT of Layer %2d Wire #%4d", i, j);
      HBProf( 100000*i+3000+j, title, 100, -12., 12., -30, 300 );
      HB2( 100000*i+4000+j, title, 100, -12., 12., 100, -30., 300. );
    }
  }

  ////////////////////////////////////////////
  //Tree
  HBTree("sdcout","tree of SdcOutTracking");
  tree->Branch("evnum",     &event.evnum,     "evnum/I");
  tree->Branch("trignhits", &event.trignhits, "trignhits/I");
  tree->Branch("trigpat",    event.trigpat,   Form("trigpat[%d]/I", NumOfSegTrig));
  tree->Branch("trigflag",   event.trigflag,  Form("trigflag[%d]/I", NumOfSegTrig));

  tree->Branch("nhBh2",   &event.nhBh2,   "nhBh2/I");
  tree->Branch("Bh2Seg",   event.Bh2Seg,  "Bh2Seg[nhBh2]/D");
  tree->Branch("tBh2",     event.tBh2,    "tBh2[nhBh2]/D");
  tree->Branch("deBh2",    event.deBh2,   "deBh2[nhBh2]/D");

  tree->Branch("nhBh1",   &event.nhBh1,   "nhBh1/I");
  tree->Branch("Bh1Seg",   event.Bh1Seg,  "Bh1Seg[nhBh1]/D");
  tree->Branch("tBh1",     event.tBh1,    "tBh1[nhBh1]/D");
  tree->Branch("deBh1",    event.deBh1,   "deBh1[nhBh1]/D");

  tree->Branch("nhTof",   &event.nhTof,   "nhTof/I");
  tree->Branch("TofSeg",   event.TofSeg,  "TofSeg[nhTof]/D");
  tree->Branch("tTof",     event.tTof,    "tTof[nhTof]/D");
  tree->Branch("dtTof",    event.dtTof,   "dtTof[nhTof]/D");
  tree->Branch("deTof",    event.deTof,   "deTof[nhTof]/D");

  tree->Branch("btof",     event.btof,    "btof[nhBh1]/D");
  tree->Branch("stof",     event.stof,    "stof[nhTof]/D");

  tree->Branch("nhit",     &event.nhit,     Form("nhit[%d]/I",
						 NumOfLayersSdcOut));
  tree->Branch("nlayer",   &event.nlayer,   "nlayer/I");
  tree->Branch("wpos",     &event.wpos,     Form("wpos[%d][%d]/D",
						 NumOfLayersSdcOut, MaxHits));
  tree->Branch(" pos",     &event.pos,     Form("wpos[%d][%d]/D",
						 NumOfLayersSdcOut, MaxHits));
  tree->Branch("ntrack",   &event.ntrack,   "ntrack/I");
  tree->Branch("chisqr",    event.chisqr,   "chisqr[ntrack]/D");
  tree->Branch("x0",        event.x0,       "x0[ntrack]/D");
  tree->Branch("y0",        event.y0,       "y0[ntrack]/D");
  tree->Branch("u0",        event.u0,       "u0[ntrack]/D");
  tree->Branch("v0",        event.v0,       "v0[ntrack]/D");

  tree->Branch("tdc",    event.tdc,   Form("tdc[%d]/I", MaxHits));

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
      InitializeParameter<UserParamMan>("USER")      );
}

//______________________________________________________________________________
bool
ConfMan::FinalizeProcess( void )
{
  return true;
}
