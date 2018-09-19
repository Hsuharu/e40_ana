/**
 *  file: UserSdcInTracking.cc
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
#include "KuramaLib.hh"
#include "MathTools.hh"
#include "RawData.hh"
#include "RootHelper.hh"
#include "UnpackerManager.hh"
#include "VEvent.hh"

#define HodoCut     0
#define BcOutCut    0
#define MaxMultiCut 0

namespace
{
  using namespace root;
  const std::string& classname("EventSdcInTracking");
  RMAnalyzer&         gRM   = RMAnalyzer::GetInstance();
  const UserParamMan& gUser = UserParamMan::GetInstance();
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
class EventSdcInTracking : public VEvent
{
private:
  RawData      *rawData;
  DCAnalyzer   *DCAna;
  HodoAnalyzer *hodoAna;

public:
        EventSdcInTracking( void );
       ~EventSdcInTracking( void );
  bool  ProcessingBegin( void );
  bool  ProcessingEnd( void );
  bool  ProcessingNormal( void );
  bool  InitializeHistograms( void );
  void  InitializeEvent( void );
};

//______________________________________________________________________________
EventSdcInTracking::EventSdcInTracking( void )
  : VEvent(),
    rawData(0),
    DCAna( new DCAnalyzer ),
    hodoAna( new HodoAnalyzer )
{
}

//______________________________________________________________________________
EventSdcInTracking::~EventSdcInTracking( void )
{
  if( DCAna )   delete DCAna;
  if( hodoAna ) delete hodoAna;
  if( rawData ) delete rawData;
}

//______________________________________________________________________________
bool
EventSdcInTracking::ProcessingBegin( void )
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

  double btof;
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
  double deTof[MaxHits];

  int ntBcOut;

  // double ssdtime[NumOfSegSSDT];

  int nlayer;
  int nhSdcIn[NumOfLayersSdcIn];
  int tdc1st[NumOfLayersSdcIn][MaxHits];
  double pos[NumOfLayersSdcIn][MaxHits];

  int ntrack;
  int    much;
  double chisqr[MaxHits];
  double x0[MaxHits];
  double y0[MaxHits];
  double u0[MaxHits];
  double v0[MaxHits];

  // // SsdPreTracking
  // int    ntSsdX;
  // int    nhSsdX[MaxHits];
  // double chisqrSsdX[MaxHits];
  // double x0SsdX[MaxHits];
  // double u0SsdX[MaxHits];
  // int    ntSsdY;
  // int    nhSsdY[MaxHits];
  // double chisqrSsdY[MaxHits];
  // double y0SsdY[MaxHits];
  // double v0SsdY[MaxHits];

  // // SsdIn
  // int    ntSsdIn;
  // double chisqrSsdIn[MaxHits];
  // double x0SsdIn[MaxHits];
  // double y0SsdIn[MaxHits];
  // double u0SsdIn[MaxHits];
  // double v0SsdIn[MaxHits];

  // double deKaon[NumOfLayersSsdIn][MaxHits];
  // double deXi[NumOfLayersSsdIn][MaxHits];
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
EventSdcInTracking::ProcessingNormal( void )
{
  const std::string func_name("["+classname+"::"+__func__+"]");

#if HodoCut
  static const double MinDeBH2   = gUser.GetParameter("DeBH2", 0);
  static const double MaxDeBH2   = gUser.GetParameter("DeBH2", 1);
  static const double MinDeBH1   = gUser.GetParameter("DeBH1", 0);
  static const double MaxDeBH1   = gUser.GetParameter("DeBH1", 1);
  static const double MinBeamToF = gUser.GetParameter("BTOF",  1);
  static const double MaxBeamToF = gUser.GetParameter("BTOF",  1);
#endif
#if MaxMultiCut
  static const double MaxMultiHitBcOut = gUser.GetParameter("MaxMultiHitBcOut");
  static const double MaxMultiHitSdcIn = gUser.GetParameter("MaxMultiHitSdcIn");
#endif
  // static const double MinDeSSDKaon = gUser.GetParameter("DeSSDKaon", 0);
  // static const double MaxDeSSDKaon = gUser.GetParameter("DeSSDKaon", 1);
  // static const double MinDeSSDXi   = gUser.GetParameter("DeSSDXi",   0);
  // static const double MaxDeSSDXi   = gUser.GetParameter("DeSSDXi",   1);
  // static const double MinTimeSSD = gUser.GetParameter("TimeSSD", 0);
  // static const double MaxTimeSSD = gUser.GetParameter("TimeSSD", 1);
  // static const double MaxChisqrSSD = gUser.GetParameter("MaxChisqrSSD", 0);

  rawData = new RawData;
  rawData->DecodeHits();

  gRM.Decode();

  event.evnum = gRM.EventNumber();

  // Trigger Flag
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

  // //SSDT
  // std::vector<double> t0Ssd( NumOfSegSSDT, 0. );
  // {
  //   hodoAna->DecodeSSDTHits( rawData );
  //   int nh = hodoAna->GetNHitsSSDT();
  //   for( int i=0; i<nh; ++i ){
  //     Hodo1Hit *hit = hodoAna->GetHitSSDT(i);
  //     if(!hit) continue;
  //     int    seg   = hit->SegmentId()+1;
  //     double time  = hit->Time();
  //     t0Ssd[seg-1] = time;
  //     event.ssdtime[seg-1] = time;
  //   }
  // }

  //////////////BH2 time 0
  hodoAna->DecodeBH2Hits(rawData);
  int nhBh2 = hodoAna->GetNHitsBH2();
  event.nhBh2 = nhBh2;
#if HodoCut
  if( nhBh2==0 ) return true;
#endif
  HF1( 1, 2 );

  double time0 = -999.;
  //////////////BH2 Analysis
  for( int i=0; i<nhBh2; ++i ){
    BH2Hit *hit = hodoAna->GetHitBH2(i);
    if(!hit) continue;
    double seg = hit->SegmentId()+1;
    double cmt = hit->CMeanTime();
    double ct0 = hit->CTime0();
    double dE  = hit->DeltaE();
    double min_time = -999.;
#if HodoCut
    if( dE2<MinDeBH2 || MaxDeBH2<dE )
      continue;
#endif
    event.tBh2[i]   = cmt;
    event.deBh2[i]  = dE;
    event.Bh2Seg[i] = seg;
    if( std::abs(cmt)<std::abs(min_time) ){
      min_time = cmt;
      time0    = ct0;
    }
  }

  HF1( 1, 3. );

  //////////////BH1 Analysis
  hodoAna->DecodeBH1Hits(rawData);
  int nhBh1 = hodoAna->GetNHitsBH1();
  event.nhBh1 = nhBh1;
#if HodoCut
  if( nhBh1==0 ) return true;
#endif
  HF1( 1, 4 );

  double btof0 = -999.;
  for(int i=0; i<nhBh1; ++i){
    Hodo2Hit *hit = hodoAna->GetHitBH1(i);
    if(!hit) continue;
    double cmt  = hit->CMeanTime();
    double dE   = hit->DeltaE();
    double btof = cmt - time0;
#if HodoCut
    if( dE<MinDeltaEBH1 || MaxDeltaEBH1<dE )
      continue;
    if( btof<MinBeamToF || MaxBeamToF<btof )
      continue
#endif
    event.tBh1[i]  = cmt;
    event.deBh1[i] = dE;
    if( std::abs(btof)<std::abs(btof0) ){
      btof0 = btof;
    }
  }

  event.btof = btof0;

  HF1( 1, 5. );

  hodoAna->DecodeTOFHits(rawData);
  int nhTof = hodoAna->GetNHitsTOF();
  event.nhTof = nhTof;
  for(int i=0; i<nhTof; ++i){
    Hodo2Hit *hit = hodoAna->GetHitTOF(i);
    if(!hit) continue;
    double cmt  = hit->CMeanTime();
    double dE   = hit->DeltaE();
    event.tTof[i]  = cmt;
    event.deTof[i] = dE;
  }

  HF1( 1, 9. );

  DCAna->DecodeRawHits( rawData );

  //BC3&BC4
  double multi_BcOut=0.;
  {
    for( int layer=1; layer<=NumOfLayersBcOut; ++layer ){
      const DCHitContainer &contOut =DCAna->GetBcOutHC(layer);
      int nhOut=contOut.size();
      multi_BcOut += double(nhOut);
    }
  }
#if MaxMultiCut
  if( multi_BcOut/double(NumOfLayersBcOut) > MaxMultiHitBcOut ){
    return true;
  }
#endif

#if 0
  {
    // Bc Out
    //  std::cout << "==========TrackSearch BcOut============" << std::endl;
    int ntOk = 0;
    DCAna->TrackSearchBcOut();
    int ntBcOut = DCAna->GetNtracksBcOut();
    if( MaxHits<ntBcOut ){
      std::cout << "#W " << func_name << " "
		<< "too many ntBcOut " << ntBcOut << "/" << MaxHits << std::endl;
      ntBcOut = MaxHits;
    }
    event.ntBcOut = ntBcOut;
    for( int it=0; it<ntBcOut; ++it ){
      DCLocalTrack *tp=DCAna->GetTrackBcOut(it);
      double chisqr=tp->GetChiSquare();
      if( chisqr<20. ) ntOk++;
    }
#if BcOutCut
    if( ntOk==0 ) return true;
#endif
  }
#endif

  //////////////SdcIn number of hit layer
  HF1( 1, 10. );
  double multi_SdcIn=0.;
  {
    for( int layer=1; layer<=NumOfLayersSdcIn; ++layer ){
      // const DCHitContainer &contIn =DCAna->GetSdcInHC(layer - 1);
      const DCHitContainer &contIn =DCAna->GetSdcInHC(layer);
      int nhSdcIn=contIn.size();
      event.nhSdcIn[layer-1] = nhSdcIn;
      if( nhSdcIn>0 ) ++event.nlayer;
      multi_SdcIn += double(nhSdcIn);
      HF1( 100*layer, nhSdcIn );
      int plane_eff = (layer-1)*3;
      bool fl_valid_sig = false;
      int tdchits=0;
      for( int i=0; i<nhSdcIn; ++i ){
	DCHit *hit=contIn[i];
	double wire=hit->GetWire();
	HF1( 100*layer+1, wire-0.5 );
	int nhtdc = hit->GetTdcSize();
	int tdc1st = -1;
	for( int k=0; k<nhtdc; k++ ){
	  int tdc = hit->GetTdcVal(k);
	  if( tdc > tdc1st ){
	    tdc1st = tdc;
	    tdchits++;
	    fl_valid_sig = true;
	  }
	}
	event.tdc1st[layer-1][i] = tdc1st;
	if( i<MaxHits && nhtdc==1 ) {
	  event.pos[layer-1][i] = hit->GetWirePosition();
	  // if ( layer == 3 || layer == 6 || layer == 7 ) {
	  //   std::cout << "layer: " << layer << '\t'
	  // 	      << "pos: " << hit->GetWirePosition() << std::endl;
	  // }
	}

	HF1( 100*layer+2, tdc1st );
	HF1( 10000*layer+int(wire), tdc1st );
	HF1( 100*layer+9, tdchits );
	int nhdt = hit->GetDriftTimeSize();
	for( int k=0; k<nhdt; k++ ){
	  double dt = hit->GetDriftTime(k);
	  HF1( 100*layer+3, dt );
	  HF1( 10000*layer+1000+int(wire), dt );
	}

	int nhdl = hit->GetDriftTimeSize();
	for( int k=0; k<nhdl; k++ ){
	  double dl = hit->GetDriftLength(k);
	  HF1( 100*layer+4, dl );
	}
      }

      if( fl_valid_sig ) ++plane_eff;

      HF1(38, plane_eff);
    }
  }

#if MaxMultiCut
  if( multi_SdcIn/double(NumOfLayersSdcIn) > MaxMultiHitSdcIn )
   return true;
#endif

  HF1( 1, 11. );

#if 1
  // std::cout << "==========TrackSearch SdcIn============" << std::endl;
  DCAna->TrackSearchSdcIn();
  int ntSdcIn = DCAna->GetNtracksSdcIn();
  if( MaxHits<ntSdcIn ){
    std::cout << "#W " << func_name << " "
	      << "too many ntSdcIn " << ntSdcIn << "/" << MaxHits << std::endl;
    ntSdcIn = MaxHits;
  }
  event.ntrack = ntSdcIn;
  // int much_combi = DCAna->MuchCombinationSdcIn();
  // event.much = much_combi;
  HF1( 10, double(ntSdcIn) );
  for( int it=0; it<ntSdcIn; ++it ){
    DCLocalTrack *tp=DCAna->GetTrackSdcIn(it);
    int nh=tp->GetNHit();
    double chisqr=tp->GetChiSquare();

    double x0=tp->GetX0(), y0=tp->GetY0();
    double u0=tp->GetU0(), v0=tp->GetV0();

    double cost = 1./std::sqrt(1.+u0*u0+v0*v0);
    double theta = std::acos(cost)*math::Rad2Deg();

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

    double xtgt=tp->GetX(0), ytgt=tp->GetY(0);
    double utgt=u0, vtgt=v0;
    HF1( 21, xtgt ); HF1( 22, ytgt );
    HF1( 23, utgt ); HF1( 24, vtgt );
    HF2( 25, xtgt, utgt ); HF2( 26, ytgt, vtgt );
    HF2( 27, xtgt, ytgt );

    double xbac=tp->GetX(-815.0), ybac=tp->GetY(-815.0);
    double ubac=u0, vbac=v0;
    HF1( 31, xbac ); HF1( 32, ybac );
    HF1( 33, ubac ); HF1( 34, vbac );
    HF2( 35, xbac, ubac ); HF2( 36, ybac, vbac );
    HF2( 37, xbac, ybac );

    for( int ih=0; ih<nh; ++ih ){
      DCLTrackHit *hit=tp->GetHit(ih);
      if( !hit ) continue;
      int layerId = hit->GetLayer();
      HF1( 13, layerId );
      // if( hit->IsSsd() && layerId>=7 && layerId<=10 ){
      // 	double de  = hit->GetDe();
      // 	event.deKaon[layerId-7][it]  = de;
      // }
      double wire=hit->GetWire();
      double dt=hit->GetDriftTime(), dl=hit->GetDriftLength();
      HF1( 100*layerId+11, wire-0.5 );
      HF1( 100*layerId+12, dt );
      HF1( 100*layerId+13, dl );
      HF1( 10000*layerId+ 5000 +int(wire), dt);
      double xcal=hit->GetXcal(), ycal=hit->GetYcal();
      double pos=hit->GetLocalHitPos(), res=hit->GetResidual();
      HF1( 100*layerId+14, pos );
      HF1( 100*layerId+15, res );
      HF2( 100*layerId+16, pos, res );
      HF2( 100*layerId+17, xcal, ycal);
      //      HF1( 100000*layerId+50000+wire, res);
      double wp=hit->GetWirePosition();
      double sign=1.;
      if( pos-wp<0. ) sign=-1;
      HF2( 100*layerId+18, sign*dl, res );
      double xlcal=hit->GetLocalCalPos();
      HF2( 100*layerId+19, dt, xlcal-wp);

      if (theta>=0 && theta<15)
	HF1( 100*layerId+71, res );
      else if (theta>=15 && theta<30)
	HF1( 100*layerId+72, res );
      else if (theta>=30 && theta<45)
	HF1( 100*layerId+73, res );
      else if (theta>=45)
	HF1( 100*layerId+74, res );

      if (std::abs(dl-std::abs(xlcal-wp))<2.0) {
	HFProf( 100*layerId+20, dt, std::abs(xlcal-wp));
	HF2( 100*layerId+22, dt, std::abs(xlcal-wp));
	HFProf( 100000*layerId+3000+int(wire), xlcal-wp,dt);
	HF2( 100000*layerId+4000+int(wire), xlcal-wp,dt);
      }
    }
  }

  HF1( 1, 12. );
#endif

  return true;
}

//______________________________________________________________________________
void
EventSdcInTracking::InitializeEvent( void )
{
  event.evnum     = 0;
  event.trignhits = 0;
  event.ntBcOut   = 0;
  event.nlayer    = 0;
  event.ntrack    = 0;
  event.nhBh2     = 0;
  event.nhBh1     = 0;
  event.nhTof     = 0;
  event.btof      = -999.;
  // event.ntSsdIn   = 0;
  event.much      = -1;
  // event.ntSsdX    = 0;
  // event.ntSsdY    = 0;

  // for( int it=0; it<NumOfSegSSDT; ++it ){
  //   event.ssdtime[it] = -9999.;
  // }

  for( int it=0; it<MaxHits; it++){
    event.Bh2Seg[it] = -1;
    event.tBh2[it] = -9999.;
    event.deBh2[it] = -9999.;

    event.Bh1Seg[it] = -1;
    event.tBh1[it] = -9999.;
    event.deBh1[it] = -9999.;

    event.TofSeg[it] = -1;
    event.tTof[it] = -9999.;
    event.deTof[it] = -9999.;
  }

  for( int it=0; it<MaxHits; it++){
    event.chisqr[it] = -1.0;
    event.x0[it] = -9999.0;
    event.y0[it] = -9999.0;
    event.u0[it] = -9999.0;
    event.v0[it] = -9999.0;
  }

  for( int it=0; it<NumOfSegTrig; it++){
    event.trigpat[it] = -1;
    event.trigflag[it] = -1;
  }

  for(int layer = 0; layer<NumOfLayersSdcIn; ++layer){
    event.nhSdcIn[layer] = 0;
    for( int that=0; that<MaxHits; ++that ){
      event.tdc1st[layer][that] = -9999;
      event.pos[layer][that] = -9999.;
    }
  }

  // for( int it=0; it<MaxHits; it++){
  //   event.nhSsdX[it]     = 0;
  //   event.chisqrSsdX[it] = -9999.;
  //   event.x0SsdX[it]     = -9999.;
  //   event.u0SsdX[it]     = -9999.;
  //   event.nhSsdY[it]     = 0;
  //   event.chisqrSsdY[it] = -9999.;
  //   event.y0SsdY[it]     = -9999.;
  //   event.v0SsdY[it]     = -9999.;

  //   event.chisqrSsdIn[it] = -1.0;
  //   event.x0SsdIn[it] = -9999.;
  //   event.y0SsdIn[it] = -9999.;
  //   event.u0SsdIn[it] = -9999.;
  //   event.v0SsdIn[it] = -9999.;
  //   for( int ih=0; ih<NumOfLayersSsdIn; ih++){
  //     event.deKaon[ih][it] = -9999.;
  //     event.deXi[ih][it]   = -9999.;
  //   }
  // }
}

//______________________________________________________________________________
bool
EventSdcInTracking::ProcessingEnd( void )
{
  tree->Fill();
  return true;
}

//______________________________________________________________________________
VEvent*
ConfMan::EventAllocator( void )
{
  return new EventSdcInTracking;
}

//______________________________________________________________________________
namespace
{
  const int NbinTdc   = 1000;
  const double MinTdc =  200.;
  const double MaxTdc = 1200.;

  const int NbinDT   =  180;
  const double MinDT =  -30.;
  const double MaxDT =  150.;

  const int NbinDL   =  90;
  const double MinDL = -0.5;
  const double MaxDL =  4.0;

  const int NbinRes   =  200;
  const double MinRes = -1.;
  const double MaxRes =  1.;
}

//______________________________________________________________________________
bool
ConfMan:: InitializeHistograms( void )
{
  HB1( 1, "Status", 20, 0., 20. );

  // SdcInTracking
  for( int i=1; i<=NumOfLayersSdcIn; ++i ){

    std::string tag;
    int nwire = 0;
    double mintdc = 0., maxtdc = 0.;
    switch ( i ) {
    case 7:
      tag = "SFT-V";
      nwire = NumOfSegSFT_UV;
      mintdc = -10.;
      maxtdc = 10.;
      break;
    case 8:
      tag = "SFT-U";
      nwire = NumOfSegSFT_UV;
      mintdc = -10.;
      maxtdc = 10.;
      break;
    case 9:
      tag = "SFT-X";
      nwire = 2*NumOfSegSFT_X;
      mintdc = -10.;
      maxtdc = 10.;
      break;
    default:
      tag = "SDC1";
      nwire = MaxWireSDC1;
      mintdc = MinTdc;
      maxtdc = MaxTdc;
      break;
    }

    TString title0 = Form("#Hits %s#%2d", tag.c_str(), i);
    TString title1 = Form("Hitpat %s#%2d", tag.c_str(), i);
    TString title2 = Form("Tdc %s#%2d", tag.c_str(), i);
    TString title3 = Form("Drift Time %s#%2d", tag.c_str(), i);
    TString title4 = Form("Drift Length %s#%2d", tag.c_str(), i);
    TString title9 = Form("#Hits w/ TDC cut %s#%2d", tag.c_str(), i);
    HB1( 100*i+0, title0, nwire+1, 0., double(nwire+1) );
    HB1( 100*i+1, title1, nwire, 0., double(nwire) );
    HB1( 100*i+2, title2, NbinTdc, mintdc, maxtdc );
    HB1( 100*i+3, title3, NbinDT, MinDT, MaxDT );
    HB1( 100*i+4, title4, NbinDL, MinDL, MaxDL );
    HB1( 100*i+9, title9, nwire+1, 0., double(nwire+1) );
    for ( int wire=1; wire<=nwire; wire++ ){
      TString title11 = Form("Tdc %s#%2d  Wire#%4d", tag.c_str(), i, wire);
      TString title12 = Form("DriftTime %s#%2d Wire#%4d", tag.c_str(), i, wire);
      TString title13 = Form("DriftLength %s#%2d Wire#%d", tag.c_str(), i, wire);
      TString title14 = Form("DriftTime %s#%2d Wire#%4d [Track]", tag.c_str(), i, wire);
      HB1( 10000*i+wire, title11, NbinTdc, mintdc, maxtdc );
      HB1( 10000*i+1000+wire, title12, NbinDT, MinDT, MaxDT );
      HB1( 10000*i+2000+wire, title13, NbinDL, MinDL, MaxDL );
      HB1( 10000*i+5000+wire, title14, NbinDT, MinDT, MaxDT );
    }
  }

  // Tracking Histgrams
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
  HB2( 20, "X0%Y0 SdcIn", 100, -100., 100., 100, -100, 100 );

  HB1( 21, "Xtgt SdcIn", 400, -100., 100. );
  HB1( 22, "Ytgt SdcIn", 400, -100., 100. );
  HB1( 23, "Utgt SdcIn", 200, -0.20, 0.20 );
  HB1( 24, "Vtgt SdcIn", 200, -0.20, 0.20 );
  HB2( 25, "Utgt%Xtgt SdcIn", 100, -100., 100., 100, -0.20, 0.20 );
  HB2( 26, "Vtgt%Ytgt SdcIn", 100, -100., 100., 100, -0.20, 0.20 );
  HB2( 27, "Xtgt%Ytgt SdcIn", 100, -100., 100., 100, -100, 100 );

  HB1( 31, "Xbac SdcIn", 400, -100., 100. );
  HB1( 32, "Ybac SdcIn", 400, -100., 100. );
  HB1( 33, "Ubac SdcIn", 200, -0.20, 0.20 );
  HB1( 34, "Vbac SdcIn", 200, -0.20, 0.20 );
  HB2( 35, "Ubac%Xbac SdcIn", 100, -100., 100., 100, -0.20, 0.20 );
  HB2( 36, "Vbac%Ybac SdcIn", 100, -100., 100., 100, -0.20, 0.20 );
  HB2( 37, "Xbac%Ybac SdcIn", 100, -100., 100., 100, -100, 100 );

  // Plane eff
  HB1( 38, "Plane Eff", 30, 0, 30);

  for( int i=1; i<=NumOfLayersSdcIn; ++i ){

    std::string tag;
    int nwire = 0;
    switch ( i ) {
    case 7:
      tag = "SFT-U";
      nwire = NumOfSegSFT_UV;
      break;
    case 8:
      tag = "SFT-V";
      nwire = NumOfSegSFT_UV;
      break;
    case 9:
      tag = "SFT-X";
      nwire = 2*NumOfSegSFT_X;
      break;
    default:
      tag = "SDC1";
      nwire = MaxWireSDC1;
      break;
    }

    TString title11 = Form("HitPat SdcIn%2d [Track]", i);
    TString title12 = Form("DriftTime SdcIn%2d [Track]", i);
    TString title13 = Form("DriftLength SdcIn%2d [Track]", i);
    TString title14 = Form("Position SdcIn%2d", i);
    TString title15 = Form("Residual SdcIn%2d", i);
    TString title16 = Form("Resid%%Pos SdcIn%2d", i);
    TString title17 = Form("Y%%Xcal SdcIn%2d", i);
    TString title18 = Form("Res%%DL SdcIn%2d", i);
    TString title19 = Form("HitPos%%DriftTime SdcIn%2d", i);
    TString title20 = Form("DriftLength%%DriftTime SdcIn%2d", i);
    TString title21 = title15 + " [w/o Self]";
    TString title22 = title20;
    TString title71 = Form("Residual SdcIn%2d (0<theta<15)", i);
    TString title72 = Form("Residual SdcIn%2d (15<theta<30)", i);
    TString title73 = Form("Residual SdcIn%2d (30<theta<45)", i);
    TString title74 = Form("Residual SdcIn%2d (45<theta)", i);
    HB1( 100*i+11, title11, MaxWireSDC1, 0., double(nwire) );
    HB1( 100*i+12, title12, NbinDT, MinDT, MaxDT );
    HB1( 100*i+13, title13, NbinDL, MinDL, MaxDL );
    HB1( 100*i+14, title14, 100, -250., 250. );
    HB1( 100*i+15, title15, NbinRes, MinRes, MaxRes );
    HB2( 100*i+16, title16, 250, -250., 250., NbinRes, MinRes, MaxRes );
    HB2( 100*i+17, title17, 100, -250., 250., 100, -250., 250. );
    HB2( 100*i+18, title18, 100, -3., 3., NbinRes, MinRes, MaxRes );
    HB2( 100*i+19, title19, NbinDT, MinDT, MaxDT, 100, -4., 4. );
    HBProf( 100*i+20, title20, NbinDT, MinDT, MaxDT, MinDL, MaxDL );
    HB2( 100*i+22, title22, NbinDT, MinDT, MaxDT, NbinDL, MinDL, MaxDL );
    HB1( 100*i+21, title21, 200, -5.0, 5.0 );
    HB1( 100*i+71, title71, 200, -5.0, 5.0 );
    HB1( 100*i+72, title72, 200, -5.0, 5.0 );
    HB1( 100*i+73, title73, 200, -5.0, 5.0 );
    HB1( 100*i+74, title74, 200, -5.0, 5.0 );

    for (int j=1; j<=nwire; j++) {
      TString title = Form("XT of Layer %2d Wire #%4d", i, j);
      HBProf( 100000*i+3000+j, title, 100, -4., 4., -5, 50 );
      HB2( 100000*i+4000+j, title, 100, -4., 4., 40, -5., 50. );
    }
  }

  ////////////////////////////////////////////
  //Tree
  HBTree("sdcin","tree of SdcInTracking");
  tree->Branch("evnum",     &event.evnum,     "evnum/I");
  tree->Branch("trignhits", &event.trignhits, "trignhits/I");
  tree->Branch("trigpat",    event.trigpat,   "trigpat[20]/I");
  tree->Branch("trigflag",   event.trigflag,  Form("trigflag[%d]/I", NumOfSegTrig));

  //Hodoscope
  tree->Branch("nhBh2",   &event.nhBh2,   "nhBh2/I");
  tree->Branch("Bh2Seg",   event.Bh2Seg,  "Bh2Seg[nhBh2]/D");
  tree->Branch("tBh2",     event.tBh2,    "tBh2[nhBh2]/D");
  tree->Branch("deBh2",    event.deBh2,   "deBh2[nhBh2]/D");

  tree->Branch("nhBh1",   &event.nhBh1,   "nhBh1/I");
  tree->Branch("Bh1Seg",   event.Bh1Seg,  "Bh1Seg[nhBh1]/D");
  tree->Branch("tBh1",     event.tBh1,    "tBh1[nhBh1]/D");
  tree->Branch("deBh1",    event.deBh1,   "deBh1[nhBh1]/D");
  tree->Branch("btof",    &event.btof,    "btof/D");

  tree->Branch("nhTof",   &event.nhTof,   "nhTof/I");
  tree->Branch("TofSeg",   event.TofSeg,  "TofSeg[nhTof]/D");
  tree->Branch("tTof",     event.tTof,    "tTof[nhTof]/D");
  tree->Branch("deTof",    event.deTof,   "deTof[nhTof]/D");

  tree->Branch("ntBcOut", &event.ntBcOut, "ntBcOut/I");

  tree->Branch("nhSdcIn",  &event.nhSdcIn,  Form( "nhSdcIn[%d]/I",
						  NumOfLayersSdcIn ) );
  tree->Branch("tdc1st",    event.tdc1st,   Form( "tdc1st[%d][%d]/I",
						  NumOfLayersSdcIn, MaxHits ) );

  tree->Branch("nlayer",   &event.nlayer,   "nlayer/I");
  tree->Branch("ntrack",   &event.ntrack,   "ntrack/I");
  tree->Branch("much",     &event.much,     "much/I");
  tree->Branch("chisqr",    event.chisqr,   "chisqr[ntrack]/D");
  tree->Branch("x0",        event.x0,       "x0[ntrack]/D");
  tree->Branch("y0",        event.y0,       "y0[ntrack]/D");
  tree->Branch("u0",        event.u0,       "u0[ntrack]/D");
  tree->Branch("v0",        event.v0,       "v0[ntrack]/D");

  // TString layer_name[NumOfLayersSdcIn] =
  //   { "ssd1y0", "ssd1x0", "ssd1y1", "ssd1x1",
  //     "ssd2x0", "ssd2y0", "ssd2x1", "ssd2y1",
  //     "sdc1v0", "sdc1v1", "sdc1x0", "sdc1x1", "sdc1u0", "sdc1u1" };
  TString layer_name[NumOfLayersSdcIn] =
    { "sftu", "sftv", "sftx",
      "sdc1v0", "sdc1v1", "sdc1x0", "sdc1x1", "sdc1u0", "sdc1u1" };
  for( int i=0; i<NumOfLayersSdcIn; ++i ){
    TString name = Form("%s_pos", layer_name[i].Data() );
    TString type = Form("%s_pos[%d]/D", layer_name[i].Data(), MaxHits );
    tree->Branch( name, event.pos[i], type );
  }

  // tree->Branch("ntSsdX",     &event.ntSsdX,     "ntSsdX/I");
  // tree->Branch("nhSsdX",      event.nhSsdX,     "nhSsdX[ntSsdX]/I");
  // tree->Branch("chisqrSsdX",  event.chisqrSsdX, "chisqrSsdX[ntSsdX]/D");
  // tree->Branch("x0SsdX",      event.x0SsdX,     "x0SsdX[ntSsdX]/D");
  // tree->Branch("u0SsdX",      event.u0SsdX,     "u0SsdX[ntSsdX]/D");

  // tree->Branch("ntSsdY",     &event.ntSsdY,     "ntSsdY/I");
  // tree->Branch("nhSsdY",      event.nhSsdY,     "nhSsdY[ntSsdY]/I");
  // tree->Branch("chisqrSsdY",  event.chisqrSsdY, "chisqrSsdY[ntSsdY]/D");
  // tree->Branch("y0SsdY",      event.y0SsdY,     "y0SsdY[ntSsdY]/D");
  // tree->Branch("v0SsdY",      event.v0SsdY,     "v0SsdY[ntSsdY]/D");

  // tree->Branch("ntSsdIn",     &event.ntSsdIn,     "ntSsdIn/I");
  // tree->Branch("chisqrSsdIn",  event.chisqrSsdIn, "chisqrSsdIn[ntSsdIn]/D");
  // tree->Branch("x0SsdIn",      event.x0SsdIn,     "x0SsdIn[ntSsdIn]/D");
  // tree->Branch("y0SsdIn",      event.y0SsdIn,     "y0SsdIn[ntSsdIn]/D");
  // tree->Branch("u0SsdIn",      event.u0SsdIn,     "u0SsdIn[ntSsdIn]/D");
  // tree->Branch("v0SsdIn",      event.v0SsdIn,     "v0SsdIn[ntSsdIn]/D");
  // tree->Branch("deKaon",       event.deKaon,      Form("deKaon[%d][%d]/D",
  // 						       NumOfLayersSsdIn, MaxHits ) );
  // tree->Branch("deXi",         event.deXi,        Form("deXi[%d][%d]/D",
  // 						       NumOfLayersSsdIn, MaxHits ) );
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
      // InitializeParameter<SsdParamMan>("SSDPRM")     &&
      InitializeParameter<UserParamMan>("USER")      );
}

//______________________________________________________________________________
bool
ConfMan::FinalizeProcess( void )
{
  return true;
}
