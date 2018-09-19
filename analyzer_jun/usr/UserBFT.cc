/**
 *  file: UserBFT.cc
 *  date: 2017.04.10
 *
 */

#include <cmath>
#include <iostream>
#include <sstream>

#include "BH2Cluster.hh"
#include "BH2Hit.hh"
#include "ConfMan.hh"
#include "DCGeomMan.hh"
#include "DetectorID.hh"
#include "RMAnalyzer.hh"
#include "FiberCluster.hh"
#include "FiberHit.hh"
#include "Hodo1Hit.hh"
#include "Hodo2Hit.hh"
#include "HodoAnalyzer.hh"
#include "HodoCluster.hh"
#include "HodoParamMan.hh"
#include "HodoPHCMan.hh"
#include "HodoRawHit.hh"
#include "KuramaLib.hh"
#include "RawData.hh"
#include "RootHelper.hh"
#include "UnpackerManager.hh"
#include "VEvent.hh"

#define HodoCut 0 // with BH1/BH2
#define TimeCut 0 // in cluster analysis

namespace
{
  using namespace root;
  const std::string& class_name("EventBFT");
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
class EventBFT : public VEvent
{
private:
  RawData      *rawData;
  DCAnalyzer   *DCAna;
  HodoAnalyzer *hodoAna;

public:
        EventBFT( void );
       ~EventBFT( void );
  bool  ProcessingBegin( void );
  bool  ProcessingEnd( void );
  bool  ProcessingNormal( void );
  bool  InitializeHistograms( void );
  void  InitializeEvent( void );
};

//______________________________________________________________________________
EventBFT::EventBFT( void )
  : VEvent(),
    rawData(0),
    DCAna( new DCAnalyzer ),
    hodoAna( new HodoAnalyzer )
{
}

//______________________________________________________________________________
EventBFT::~EventBFT( void )
{
  if ( hodoAna ){
    delete hodoAna;
    hodoAna = NULL;
  }
  if ( DCAna ){
    delete DCAna;
    DCAna   = NULL;
  }
  if ( rawData ){
    delete rawData;
    rawData = NULL;
  }
}

//______________________________________________________________________________
struct Event
{
  int evnum;

  int trigpat[NumOfSegTrig];
  int trigflag[NumOfSegTrig];

  // Fiber Hit
  int    nhits;
  int    unhits;
  int    dnhits;
  int    uhitpat[NumOfSegBFT];
  int    dhitpat[NumOfSegBFT];
  double utdc[NumOfSegBFT][MaxDepth];
  double dtdc[NumOfSegBFT][MaxDepth];
  double utrailing[NumOfSegBFT][MaxDepth];
  double dtrailing[NumOfSegBFT][MaxDepth];
  double utot[NumOfSegBFT][MaxDepth];
  double dtot[NumOfSegBFT][MaxDepth];
  int    udepth[NumOfSegBFT];
  int    ddepth[NumOfSegBFT];

  // Fiber Cluster
  int ncl;
  int clsize[NumOfSegBFT];
  double ctime[NumOfSegBFT];
};

//______________________________________________________________________________
namespace root
{
  Event event;
  TH1   *h[MaxHist];
  TTree *tree;
}

//______________________________________________________________________________
bool
EventBFT::ProcessingBegin( void )
{
  InitializeEvent();
  return true;
}

//______________________________________________________________________________
bool
EventBFT::ProcessingNormal( void )
{
  static const std::string func_name("["+class_name+"::"+__func__+"]");

#if HodoCut
  static const double MinDeBH2   = gUser.GetParameter("DeBH2", 0);
  static const double MaxDeBH2   = gUser.GetParameter("DeBH2", 1);
  static const double MinDeBH1   = gUser.GetParameter("DeBH1", 0);
  static const double MaxDeBH1   = gUser.GetParameter("DeBH1", 1);
  static const double MinBeamToF = gUser.GetParameter("BTOF",  1);
  static const double MaxBeamToF = gUser.GetParameter("BTOF",  1);
#endif
  static const double MinTdcBFT  = gUser.GetParameter("TdcBFT",  0);
  static const double MaxTdcBFT  = gUser.GetParameter("TdcBFT",  1);
#if TimeCut
    static const double MinTimeBFT = gUser.GetParameter("TimeBFT", 0);
    static const double MaxTimeBFT = gUser.GetParameter("TimeBFT", 1);
#endif

  rawData = new RawData;
  rawData->DecodeHits();

  gRM.Decode();

  int evnum = gRM.EventNumber();
  event.evnum = evnum;

  //**************************************************************************
  //******************RawData

  // Trigger Flag
  {
    const HodoRHitContainer &cont=rawData->GetTrigRawHC();
    int nh=cont.size();
    for( int i=0; i<nh; ++i ){
      HodoRawHit *hit=cont[i];
      int seg = hit->SegmentId()+1;
      int tdc = hit->GetTdc1();
      if( tdc ){
	event.trigpat[i]      = seg;
	event.trigflag[seg-1] = tdc;
      }
    }
  }

  HF1(1, 0);
  // if( trigflag[SpillEndFlag] ) return true;
  HF1(1, 1);

  // BH2 time 0
  hodoAna->DecodeBH2Hits(rawData);
  int ncBh2=hodoAna->GetNClustersBH2();
#if HodoCut
  if(ncBh2==0) return true;
#endif
  HF1(1, 2);
  //////////////BH2 Analysis
  BH2Cluster *clBH2Time0=hodoAna->GetClusterBH2(0);
  double time0=clBH2Time0->CTime0();

  {
    int ncOk=0;
    double mint=clBH2Time0->CMeanTime();
    for( int i=0; i<ncBh2; ++i ){
      BH2Cluster *cl=hodoAna->GetClusterBH2(i);
      double t     = cl->CMeanTime();
#if HodoCut
      double dEbh2 = cl->DeltaE();
      if( dEbh2<MinDeBH2 || MaxDeBH2<dEbh2 )
	continue;
#endif
      ++ncOk;
      if( std::abs(t)<std::abs(mint) ){
	clBH2Time0 = cl;
	mint=t; time0=clBH2Time0->CTime0();
      }
    }
  }

  HF1(1, 3);

  //////////////BH1 Analysis
  hodoAna->DecodeBH1Hits(rawData);
  int ncBh1=hodoAna->GetNClustersBH1();
#if HodoCut
  if(ncBh1==0) return true;
#endif
  HF1(1, 4);

  HodoCluster* clBH1Time0 = hodoAna->GetClusterBH1(0);
  {
    int ncOk=0;
    double min_tof = clBH1Time0->CMeanTime() - time0;
    for( int i=0; i<ncBh1; ++i ){
      HodoCluster *cl=hodoAna->GetClusterBH1(i);
      double btof= cl->CMeanTime()-time0;
#if HodoCut
      double dEbh1 = cl->DeltaE();
      if( dEbh1<MinDeBH1 || MaxDeBH1<dEbh1 )
	continue;
      if( btof<MinBeamToF || MaxBeamToF<btof )
	continue;
#endif
      ++ncOk;
      if( std::abs(btof)<std::abs(min_tof) ){
	clBH1Time0 = cl;
	min_tof = btof;
      }
    }
  }

  HF1(1, 5);

  HF1(1, 6);

  ////////// BFT
  {
    hodoAna->DecodeBFTHits(rawData);
    // Fiber Hit
    int unhits = 0;
    int dnhits = 0;
    for(int plane = 0; plane<NumOfPlaneBFT; ++plane){
      int nhit = hodoAna->GetNHitsBFT(plane);
      for(int i=0; i<nhit; ++i){
	const FiberHit* hit = hodoAna->GetHitBFT(plane, i);
	if(!hit) continue;
	int mhit  = hit->GetNumOfHit();
	int seg   = hit->SegmentId();
	enum { U, D };
	if(plane==U) event.udepth[seg] = mhit;
	if(plane==D) event.ddepth[seg] = mhit;

	int prev = 0;
	for(int m = 0; m<mhit; ++m){
	  double leading  = hit->GetLeading(m);
	  double trailing = hit->GetTrailing(m);
	  double ctime    = hit->GetCTime(m);
	  double width    = hit->GetWidth(m);
	  if(leading==prev||width==0) continue;
	  prev = leading;
	  HF1 (100*(plane+1)+3, leading);
	  HF1 (100*(plane+1)+4, width);
	  HF1 (10000*(plane+1)+seg+1, leading);
	  HF1 (10000*(plane+1)+1000+seg+1, width);
	  if(seg==141) HF2 (0, evnum, width);
	  HF2 (100*(plane+1)+5, seg, leading);
	  HF2 (100*(plane+1)+6, seg, width);

	  HF1 (1000*(plane+1) +1, ctime);
	  HF2 (1000*(plane+1) +3, width, ctime);
	  if(plane==U){
	    event.utdc[seg][m]      = leading;
	    event.utrailing[seg][m] = trailing;
	    event.utot[seg][m]      = width;
	  }
	  if(plane==D){
	    event.dtdc[seg][m]      = leading;
	    event.dtrailing[seg][m] = trailing;
	    event.dtot[seg][m]      = width;
	  }
	  if( MinTdcBFT<leading && leading<MaxTdcBFT ){
	    HF1(100*(plane+1)+2, seg+0.5);
	    if(plane==U) event.uhitpat[unhits++] = seg;
	    if(plane==D) event.dhitpat[dnhits++] = seg;
	  }
	}
      }
    }
    HF1(100+1, unhits);
    HF1(200+1, dnhits);
    HF1(300+1, unhits+dnhits);
    event.unhits = unhits;
    event.dnhits = dnhits;
    event.nhits = unhits + dnhits;

    // Fiber Cluster
#if TimeCut
    hodoAna->TimeCutBFT( MinTimeBFT, MaxTimeBFT );
#endif
    int ncl = hodoAna->GetNClustersBFT();
    event.ncl = ncl;
    for(int i=0; i<ncl; ++i){
      FiberCluster *cl = hodoAna->GetClusterBFT(i);
      if(!cl) continue;
      double size  = cl->ClusterSize();
      // double pos   = cl->MeanPosition();
      double ctime = cl->CMeanTime();
      // double tot   = cl->MeanPosition();
      // double width = cl->Width();
      event.clsize[i] = size;
      event.ctime[i]  = ctime;
    }
  }

  return true;
}

//______________________________________________________________________________
bool
EventBFT::ProcessingEnd( void )
{
  tree->Fill();
  return true;
}

//______________________________________________________________________________
void
EventBFT::InitializeEvent( void )
{
  event.evnum  = 0;
  event.nhits  = 0;
  event.unhits = 0;
  event.dnhits = 0;
  event.ncl    = 0;

  for( int it=0; it<NumOfSegTrig; ++it ){
    event.trigpat[it]  = -1;
    event.trigflag[it] = -1;
  }

  for( int s=0; s<NumOfSegBFT; s++ ){
    event.uhitpat[s] = -999;
    event.dhitpat[s] = -999;
    event.udepth[s]  = 0;
    event.ddepth[s]  = 0;
    for( int m=0; m<MaxDepth; ++m ){
      event.utdc[s][m] = -999.;
      event.dtdc[s][m] = -999.;
      event.utrailing[s][m] = -999.;
      event.dtrailing[s][m] = -999.;
      event.utot[s][m] = -999.;
      event.dtot[s][m] = -999.;
    }
  }
  for( int it=0; it<NumOfSegBFT; ++it ){
    event.clsize[it] = -999;
    event.ctime[it]  = -999.;
  }
}

//______________________________________________________________________________
VEvent*
ConfMan::EventAllocator( void )
{
  return new EventBFT;
}

//______________________________________________________________________________
namespace
{
  const int    NbinTdc = 1000;
  const double MinTdc  =    0.;
  const double MaxTdc  = 1000.;

  const int    NbinTot =  136;
  const double MinTot  =   -8.;
  const double MaxTot  =  128.;

  const int    NbinTime = 1000;
  const double MinTime  = -500.;
  const double MaxTime  =  500.;
}
//______________________________________________________________________________
bool
ConfMan:: InitializeHistograms( void )
{
  HB1( 1, "Status", 20, 0., 20. );
  HB1( 2, "analys flag", 20, 0., 20. );

  HB1 (10, "ntrack", 10, 0, 10);
  HB1 (15, "Residual Cl", 200, -10, 10);
  HB1 (16, "nc BFT w BH1 cut", 10, 0, 10);
  HB2( 17, "Time0 cor w/ Bh1", 24, 0, 12, 160, -80, 80);

  //BFT
  HB1( 100+1, "N hits U",   NumOfSegBFT, 0., (double)NumOfSegBFT );
  HB1( 100+2, "Hit pat U",  NumOfSegBFT, 0., (double)NumOfSegBFT );
  HB1( 100+3, "Tdc U",      NbinTdc, MinTdc, MaxTdc );
  HB1( 100+4, "Tot U",      NbinTot, MinTot, MaxTot );
  HB2( 100+5, "Tdc U%Seg",  NumOfSegBFT, 0., (double)NumOfSegBFT, NbinTdc, MinTdc, MaxTdc );
  HB2( 100+6, "Tot U%Seg",  NumOfSegBFT, 0., (double)NumOfSegBFT, NbinTot, MinTot, MaxTot );
  HB1( 200+1, "N hits D",   NumOfSegBFT, 0., (double)NumOfSegBFT );
  HB1( 200+2, "Hit pat D",  NumOfSegBFT, 0., (double)NumOfSegBFT );
  HB1( 200+3, "Tdc D",      NbinTdc, MinTdc, MaxTdc );
  HB1( 200+4, "Tot D",      NbinTot, MinTot, MaxTot );
  HB2( 200+5, "Tdc D%Seg",  NumOfSegBFT, 0., (double)NumOfSegBFT, NbinTdc, MinTdc, MaxTdc );
  HB2( 200+6, "Tot D%Seg",  NumOfSegBFT, 0., (double)NumOfSegBFT, NbinTot, MinTot, MaxTot );
  HB1( 300+1, "N hits BFT", NumOfSegBFT, 0., (double)NumOfSegBFT );
  for(int i=0; i<NumOfSegBFT; i++){
    HB1( 10000+i+1, Form("Tdc U ch%d", i+1), NbinTdc, MinTdc, MaxTdc );
    HB1( 11000+i+1, Form("Tot U ch%d", i+1), NbinTot, MinTot, MaxTot );
    HB1( 20000+i+1, Form("Tdc D ch%d", i+1), NbinTdc, MinTdc, MaxTdc );
    HB1( 21000+i+1, Form("Tot D ch%d", i+1), NbinTot, MinTot, MaxTot );
  }

  HB1 ( 1000 +1, "ctime U", NbinTime, MinTime, MaxTime );
  HB1 ( 1000 +2, "hit profile U", NumOfSegBFT, -(double)NumOfSegBFT/2, (double)NumOfSegBFT/2 );
  HB2 ( 1000 +3, "cor tdc/tot U", 100,1,100, 100,-50,50 );
  HB1 ( 2000 +1, "ctime D", NbinTime, MinTime, MaxTime );
  HB1 ( 2000 +2, "hit profile D", NumOfSegBFT, -(double)NumOfSegBFT/2, (double)NumOfSegBFT/2 );
  HB2 ( 2000 +3, "cor tdc/tot D", 100,1,100, 100,-50,50);

  HB1 (5000+0, "N of Cluster", 500, 0, 500);
  HB1 (5000+1, "clsize", 5, 0, 5);
  HB1 (5000+2, "cmt", 100, -50, 50);
  HB1 (5000+3, "pos", 320, -80, 80);

  // BH1
  HB1( 10000, "nhvalid", 10,0,10);

  //Tree
  HBTree( "tree","tree of Counter" );
  tree->Branch("evnum",    &event.evnum,    "evnum/I");
  tree->Branch("trigpat",   event.trigpat,  Form("trigpat[%d]/I", NumOfSegTrig));
  tree->Branch("trigflag",  event.trigflag, Form("trigflag[%d]/I", NumOfSegTrig));

  tree->Branch("nhits",     &event.nhits,        "nhits/I");
  tree->Branch("unhits",    &event.unhits,       "unhits/I");
  tree->Branch("dnhits",    &event.dnhits,       "dnhits/I");
  tree->Branch("uhitpat",    event.uhitpat,      "uhitpat[unhits]/I");
  tree->Branch("dhitpat",    event.dhitpat,      "dhitpat[dnhits]/I");
  tree->Branch("utdc",       event.utdc,         Form("utdc[%d][%d]/D",
						      NumOfSegBFT, MaxDepth));
  tree->Branch("dtdc",       event.dtdc,         Form("dtdc[%d][%d]/D",
						      NumOfSegBFT, MaxDepth));
  tree->Branch("utrailing",  event.utrailing,    Form("utrailing[%d][%d]/D",
						      NumOfSegBFT, MaxDepth));
  tree->Branch("dtrailing",  event.dtrailing,    Form("dtrailing[%d][%d]/D",
						      NumOfSegBFT, MaxDepth));
  tree->Branch("utot",       event.utot,         Form("utot[%d][%d]/D",
						      NumOfSegBFT, MaxDepth));
  tree->Branch("dtot",       event.dtot,         Form("dtot[%d][%d]/D",
						      NumOfSegBFT, MaxDepth));
  tree->Branch("udepth",     event.udepth,       Form("udepth[%d]/I", NumOfSegBFT));
  tree->Branch("ddepth",     event.ddepth,       Form("ddepth[%d]/I", NumOfSegBFT));
  tree->Branch("ncl",       &event.ncl,          "ncl/I");
  tree->Branch("clsize",     event.clsize,       "clsize[ncl]/I");
  tree->Branch("ctime",      event.ctime,        "ctime[ncl]/D");

  HPrint();
  return true;
}

//______________________________________________________________________________
bool
ConfMan::InitializeParameterFiles( void )
{
  return
    ( InitializeParameter<DCGeomMan>("DCGEO")    &&
      InitializeParameter<HodoParamMan>("HDPRM") &&
      InitializeParameter<HodoPHCMan>("HDPHC")   &&
      InitializeParameter<UserParamMan>("USER")  );
}

//______________________________________________________________________________
bool
ConfMan::FinalizeProcess( void )
{
  return true;
}
