/**
 *  file: UserK1.8Tracking.cc
 *  date: 2017.04.10
 *
 */

#include <cmath>
#include <iostream>
#include <sstream>

#include "BH2Cluster.hh"
#include "BH2Hit.hh"
#include "ConfMan.hh"
#include "DCAnalyzer.hh"
#include "DCGeomMan.hh"
#include "DCRawHit.hh"
#include "DetectorID.hh"
#include "RMAnalyzer.hh"
#include "FiberCluster.hh"
#include "FiberHit.hh"
#include "Hodo1Hit.hh"
#include "Hodo2Hit.hh"
#include "HodoCluster.hh"
#include "HodoAnalyzer.hh"
#include "HodoParamMan.hh"
#include "HodoPHCMan.hh"
#include "HodoRawHit.hh"
#include "K18TrackD2U.hh"
#include "BH1Match.hh"
#include "BH2Filter.hh"
#include "KuramaLib.hh"
#include "MathTools.hh"
#include "RawData.hh"
#include "RootHelper.hh"
#include "UnpackerManager.hh"
#include "VEvent.hh"

#define HodoCut 0 // with BH1/BH2
#define TimeCut 1 // in cluster analysis

namespace
{
  using namespace root;
  const std::string& class_name("EventK18Tracking");
  RMAnalyzer&         gRM   = RMAnalyzer::GetInstance();
  const UserParamMan& gUser = UserParamMan::GetInstance();
  BH2Filter&          gFilter = BH2Filter::GetInstance();
  BH1Match&           gBH1Mth = BH1Match::GetInstance();
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
class EventK18Tracking : public VEvent
{
private:
  RawData      *rawData;
  DCAnalyzer   *DCAna;
  HodoAnalyzer *hodoAna;

public:
        EventK18Tracking( void );
       ~EventK18Tracking( void );
  bool  ProcessingBegin();
  bool  ProcessingEnd();
  bool  ProcessingNormal();
  bool  InitializeHistograms();
  void  InitializeEvent();
};

//______________________________________________________________________________
EventK18Tracking::EventK18Tracking( void )
  : VEvent(),
    rawData(0),
    DCAna( new DCAnalyzer ),
    hodoAna( new HodoAnalyzer )
{
}

//______________________________________________________________________________
EventK18Tracking::~EventK18Tracking( void )
{
  if( hodoAna ) delete hodoAna;
  if( DCAna )   delete DCAna;
  if( rawData ) delete rawData;
}

//______________________________________________________________________________
struct Event
{
  int evnum;

  int trignhits;
  int trigpat[NumOfSegTrig];
  int trigflag[NumOfSegTrig];

  // Time0
  double Time0Seg;
  double deTime0;
  double Time0;
  double CTime0;

  // BFT
  int    bft_ncl;
  int    bft_ncl_bh1mth;
  int    bft_clsize[NumOfSegBFT];
  double bft_ctime[NumOfSegBFT];
  double bft_clpos[NumOfSegBFT];
  int    bft_bh1mth[NumOfSegBFT];

  // BcOut
  int nlBcOut;
  int ntBcOut;
  int nhBcOut[MaxHits];
  double chisqrBcOut[MaxHits];
  double x0BcOut[MaxHits];
  double y0BcOut[MaxHits];
  double u0BcOut[MaxHits];
  double v0BcOut[MaxHits];

  // K18
  int ntK18;
  int nhK18[MaxHits];
  double p_2nd[MaxHits];
  double p_3rd[MaxHits];
  double delta_2nd[MaxHits];
  double delta_3rd[MaxHits];

  double xin[MaxHits];
  double yin[MaxHits];
  double uin[MaxHits];
  double vin[MaxHits];

  double chisqrK18[MaxHits];
  double xtgtK18[MaxHits];
  double ytgtK18[MaxHits];
  double utgtK18[MaxHits];
  double vtgtK18[MaxHits];

  double theta[MaxHits];
  double phi[MaxHits];
};

//______________________________________________________________________________
namespace root
{
  Event event;
  TH1   *h[MaxHist];
  TTree *tree;
  const int BFTHid = 10000;
  enum eParticle
    {
      kKaon, kPion, nParticle
    };
}

//______________________________________________________________________________
bool
EventK18Tracking::ProcessingBegin( void )
{
  InitializeEvent();
  return true;
}

//______________________________________________________________________________
bool
EventK18Tracking::ProcessingNormal( void )
{
  const std::string funcname("["+class_name+"::"+__func__+"]");

#if HodoCut
  static const double MinDeBH2   = gUser.GetParameter("DeBH2", 0);
  static const double MaxDeBH2   = gUser.GetParameter("DeBH2", 1);
  static const double MinDeBH1   = gUser.GetParameter("DeBH1", 0);
  static const double MaxDeBH1   = gUser.GetParameter("DeBH1", 1);
  static const double MinBeamToF = gUser.GetParameter("BTOF",  1);
  static const double MaxBeamToF = gUser.GetParameter("BTOF",  1);
#endif
#if TimeCut
  static const double MinTimeBFT = gUser.GetParameter("TimeBFT", 0);
  static const double MaxTimeBFT = gUser.GetParameter("TimeBFT", 1);
#endif
  // static const double MaxMultiHitBcOut = gUser.GetParameter("MaxMultiHitBcOut");

  rawData = new RawData;
  rawData->DecodeHits();

  gRM.Decode();

  event.evnum = gRM.EventNumber();

  HF1( 1, 0. );

  //Misc
  {
    const HodoRHitContainer &cont = rawData->GetTrigRawHC();
    int trignhits = 0;
    int nh = cont.size();
    for( int i=0; i<nh; ++i ){
      HodoRawHit *hit = cont[i];
      int seg = hit->SegmentId()+1;
      int tdc = hit->GetTdc1();
      if( tdc ){
	event.trigpat[trignhits++] = seg;
	event.trigflag[seg-1]      = tdc;
	HF1( 100, seg-1 );
	HF1( 100+seg, tdc );
      }
    }
    event.trignhits = trignhits;
  }

  // if( event.trigflag[SpillEndFlag] ) return true;

  HF1(1, 1);

  ////////// BH2 time 0
  hodoAna->DecodeBH2Hits(rawData);
  int nhBh2 = hodoAna->GetNHitsBH2();
#if HodoCut
  if(nhBh2==0) return true;
#endif
  HF1(1, 2);

  //////////////BH2 Analysis
  BH2Cluster *cl_time0 = hodoAna->GetTime0BH2Cluster();
  if(cl_time0){
    event.Time0Seg = cl_time0->MeanSeg()+1;
    event.deTime0  = cl_time0->DeltaE();
    event.Time0    = cl_time0->Time0();
    event.CTime0   = cl_time0->CTime0();
  }else{
    return true;
  }

  HF1(1, 3);

  ////////// BH1 Analysis
  hodoAna->DecodeBH1Hits(rawData);
  int nhBh1 = hodoAna->GetNHitsBH1();
#if HodoCut
  if(nhBh1==0) return true;
#endif
  HF1(1, 4);

  double btof0_seg = -1;
  HodoCluster* cl_btof0 = event.Time0Seg > 0? hodoAna->GetBtof0BH1Cluster(event.CTime0) : NULL;
  if(cl_btof0){
    btof0_seg = cl_btof0->MeanSeg();
  }

  HF1(1, 5);

  HF1(1, 6);

  std::vector<double> xCand;
  ////////// BFT
  {
    hodoAna->DecodeBFTHits(rawData);
    // Fiber Cluster
    int ncl_raw = hodoAna->GetNClustersBFT();
#if TimeCut
    hodoAna->TimeCutBFT( MinTimeBFT, MaxTimeBFT );
#endif
    int ncl = hodoAna->GetNClustersBFT();
    event.bft_ncl = ncl;
    HF1( BFTHid +100, ncl_raw );
    HF1( BFTHid +101, ncl );
    for(int i=0; i<ncl; ++i){
      FiberCluster *cl = hodoAna->GetClusterBFT(i);
      if(!cl) continue;
      double clsize = cl->ClusterSize();
      double ctime  = cl->CMeanTime();
      double pos    = cl->MeanPosition();
      // double width  = cl->Width();

      event.bft_clsize[i] = clsize;
      event.bft_ctime[i]  = ctime;
      event.bft_clpos[i]  = pos;
      
      if(btof0_seg > 0 && ncl != 1){
	if(gBH1Mth.Judge(pos, btof0_seg)){
	  event.bft_bh1mth[i] = 1;
	  xCand.push_back( pos );
	}
      }else{
	xCand.push_back( pos );
      }

      HF1( BFTHid +102, clsize );
      HF1( BFTHid +103, ctime );
      HF1( BFTHid +104, pos );
    }

    event.bft_ncl_bh1mth = xCand.size();
    HF1( BFTHid + 105, event.bft_ncl_bh1mth);
  }

  HF1( 1, 7.);
  if(xCand.size()!=1) return true;
  HF1( 1, 10. );

  DCAna->DecodeRawHits( rawData );
  ////////////// BC3&4 number of hit in one layer not 0
  double multi_BcOut=0.;
  {
    int nlBcOut = 0;
    for( int layer=1; layer<=NumOfLayersBcOut; ++layer ){
      const DCHitContainer &contBcOut = DCAna->GetBcOutHC(layer);
      int nhBcOut = contBcOut.size();
      multi_BcOut += double(nhBcOut);
      if( nhBcOut>0 ) nlBcOut++;
    }
    event.nlBcOut = nlBcOut;
  }

  // if( multi_BcOut/double(NumOfLayersBcOut) > MaxMultiHitBcOut ) return true;

  HF1( 1, 11. );

  //////////////BCOut tracking
  BH2Filter::FilterList cands;
  gFilter.Apply((Int_t)event.Time0Seg-1, *DCAna, cands);
  DCAna->TrackSearchBcOut( cands, event.Time0Seg-1 );
  DCAna->ChiSqrCutBcOut(10);

  int ntBcOut = DCAna->GetNtracksBcOut();
  event.ntBcOut = ntBcOut;
  if(ntBcOut > MaxHits){
    std::cout << "#W " << funcname
	      << " Too many BcOut tracks : ntBcOut = "
	      << ntBcOut << std::endl;
    ntBcOut = MaxHits;
  }
  HF1( 30, double(ntBcOut) );
  for( int it=0; it<ntBcOut; ++it ){
    DCLocalTrack *tp = DCAna->GetTrackBcOut(it);
    int nh = tp->GetNHit();
    double chisqr = tp->GetChiSquare();
    double u0 = tp->GetU0(),  v0 = tp->GetV0();
    double x0 = tp->GetX(0.), y0 = tp->GetY(0.);

    HF1( 31, double(nh) );
    HF1( 32, chisqr );
    HF1( 34, x0 ); HF1( 35, y0 );
    HF1( 36, u0 ); HF1( 37, v0 );
    HF2( 38, x0, u0 ); HF2( 39, y0, v0 );
    HF2( 40, x0, y0 );

    event.nhBcOut[it] = nh;
    event.chisqrBcOut[it] = chisqr;
    event.x0BcOut[it] = x0;
    event.y0BcOut[it] = y0;
    event.u0BcOut[it] = u0;
    event.v0BcOut[it] = v0;

    for( int ih=0; ih<nh; ++ih ){
      DCLTrackHit *hit=tp->GetHit(ih);
      int layerId=hit->GetLayer()-100;
      HF1( 33, layerId );
    }
  }
  if( ntBcOut==0 ) return true;

  HF1( 1, 12. );

  HF1( 1, 20. );
  ////////// K18Tracking D2U
  DCAna->TrackSearchK18D2U(xCand);
  int ntK18 = DCAna->GetNTracksK18D2U();
  if(ntK18 > MaxHits){
    std::cout << "#W " << funcname << " too many ntK18 "
	      << ntK18 << "/" << MaxHits << std::endl;
    ntK18 = MaxHits;
  }
  event.ntK18 = ntK18;
  HF1( 50, double(ntK18) );
  for( int i=0; i<ntK18; ++i ){
    K18TrackD2U *tp=DCAna->GetK18TrackD2U(i);
    if(!tp) continue;
    DCLocalTrack *track = tp->TrackOut();
    std::size_t nh = track->GetNHit();
    double chisqr = track->GetChiSquare();

    double xin=tp->Xin(), yin=tp->Yin();
    double uin=tp->Uin(), vin=tp->Vin();

    double xt=tp->Xtgt(), yt=tp->Ytgt();
    double ut=tp->Utgt(), vt=tp->Vtgt();
    double p_2nd=tp->P();
    double p_3rd=tp->P3rd();
    double delta_2nd=tp->Delta();
    double delta_3rd=tp->Delta3rd();
    double cost = 1./std::sqrt(1.+ut*ut+vt*vt);
    double theta = std::acos(cost)*math::Rad2Deg();
    double phi   = atan2( ut, vt );

    HF1( 54, xt ); HF1( 55, yt ); HF1( 56, ut ); HF1( 57,vt );
    HF2( 58, xt, ut ); HF2( 59, yt, vt ); HF2( 60, xt, yt );
    HF1( 61, p_3rd ); HF1( 62, delta_3rd );

    event.p_2nd[i] = p_2nd;
    event.p_3rd[i] = p_3rd;
    event.delta_2nd[i] = delta_2nd;
    event.delta_3rd[i] = delta_3rd;

    event.xin[i] = xin;
    event.yin[i] = yin;
    event.uin[i] = uin;
    event.vin[i] = vin;

    event.nhK18[i]     = nh;
    event.chisqrK18[i] = chisqr;
    event.xtgtK18[i]   = xt;
    event.ytgtK18[i]   = yt;
    event.utgtK18[i]   = ut;
    event.vtgtK18[i]   = vt;
    event.theta[i] = theta;
    event.phi[i]   = phi;
  }

  HF1( 1, 22. );

  return true;
}

//______________________________________________________________________________
bool
EventK18Tracking::ProcessingEnd( void )
{
  tree->Fill();
  return true;
}

//______________________________________________________________________________
void
EventK18Tracking::InitializeEvent( void )
{
  event.evnum     =  0;
  event.trignhits =  0;
  event.bft_ncl   =  0;
  event.bft_ncl_bh1mth =  0;
  event.nlBcOut   =  0;
  event.ntBcOut   =  0;
  event.ntK18     =  0;

  event.Time0Seg  = -1;
  event.deTime0   = -1;
  event.Time0     = -999;
  event.CTime0    = -999;

  for( int it=0; it<NumOfSegTrig; it++){
    event.trigpat[it]  = -1;
    event.trigflag[it] = -1;
  }

  for( int it=0; it<NumOfSegBFT; it++){
    event.bft_clsize[it] = -999;
    event.bft_ctime[it]  = -999.;
    event.bft_clpos[it]  = -999.;
    event.bft_bh1mth[it] = 0;
  }

  for(int i = 0; i<MaxHits; ++i){
    event.nhBcOut[i] = 0;
    event.chisqrBcOut[i] = -999.;
    event.x0BcOut[i] = -999.;
    event.y0BcOut[i] = -999.;
    event.u0BcOut[i] = -999.;
    event.v0BcOut[i] = -999.;

    event.p_2nd[i] = -999.;
    event.p_3rd[i] = -999.;
    event.delta_2nd[i] = -999.;
    event.delta_3rd[i] = -999.;

    event.xin[i] = -999.;
    event.yin[i] = -999.;
    event.uin[i] = -999.;
    event.vin[i] = -999.;

    event.nhK18[i]   = 0;
    event.chisqrK18[i] = -999.;
    event.xtgtK18[i] = -999.;
    event.ytgtK18[i] = -999.;
    event.utgtK18[i] = -999.;
    event.vtgtK18[i] = -999.;

    event.theta[i] = -999.;
    event.phi[i] = -999.;
  }
}

//______________________________________________________________________________
VEvent*
ConfMan::EventAllocator( void )
{
  return new EventK18Tracking;
}

//______________________________________________________________________________
namespace
{
  // const int NbinAdc = 1024;
  // const double MinAdc  =    0.;
  // const double MaxAdc  = 4096.;

  // const int NbinTdc = 1024;
  // const double MinTdc  =    0.;
  // const double MaxTdc  = 4096.;

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
  HB1(  1, "Status",  30,   0., 30. );
  HB1( 100, "Trigger HitPat", NumOfSegTrig, 0., double(NumOfSegTrig) );
  for(int i=0; i<NumOfSegTrig; ++i){
    HB1( 100+i+1, Form("Trigger Flag %d", i+1), 0x1000, 0, 0x1000 );
  }

  //BFT
  HB1( BFTHid +21, "BFT CTime U",     NbinTime, MinTime, MaxTime );
  HB1( BFTHid +22, "BFT CTime D",     NbinTime, MinTime, MaxTime );
  HB2( BFTHid +23, "BFT CTime/Tot U", NbinTot, MinTot, MaxTot, NbinTime, MinTime, MaxTime );
  HB2( BFTHid +24, "BFT CTime/Tot D", NbinTot, MinTot, MaxTot, NbinTime, MinTime, MaxTime );

  HB1( BFTHid +100, "BFT NCluster [Raw]", 100, 0, 100 );
  HB1( BFTHid +101, "BFT NCluster [TimeCut]", 10, 0, 10 );
  HB1( BFTHid +102, "BFT Cluster Size", 5, 0, 5 );
  HB1( BFTHid +103, "BFT CTime (Cluster)", NbinTime, MinTime, MaxTime );
  HB1( BFTHid +104, "BFT Cluster Position",
       NumOfSegBFT, -0.5*(double)NumOfSegBFT, 0.5*(double)NumOfSegBFT );
  HB1( BFTHid +105, "BFT NCluster [TimeCut && BH1Matching]", 10, 0, 10 );

  // BcOut
  HB1( 30, "#Tracks BcOut", 10, 0., 10. );
  HB1( 31, "#Hits of Track BcOut", 20, 0., 20. );
  HB1( 32, "Chisqr BcOut", 500, 0., 50. );
  HB1( 33, "LayerId BcOut", 15, 12., 27. );
  HB1( 34, "X0 BcOut", 400, -100., 100. );
  HB1( 35, "Y0 BcOut", 400, -100., 100. );
  HB1( 36, "U0 BcOut",  200, -0.20, 0.20 );
  HB1( 37, "V0 BcOut",  200, -0.20, 0.20 );
  HB2( 38, "U0%X0 BcOut", 100, -100., 100., 100, -0.20, 0.20 );
  HB2( 39, "V0%Y0 BcOut", 100, -100., 100., 100, -0.20, 0.20 );
  HB2( 40, "X0%Y0 BcOut", 100, -100., 100., 100, -100., 100. );

  // K18
  HB1( 50, "#Tracks K18", 20, 0., 20. );
  HB1( 51, "#Hits of K18Track", 30, 0., 30. );
  HB1( 52, "Chisqr K18Track", 500, 0., 100. );
  HB1( 53, "LayerId K18Track", 50, 0., 50. );
  HB1( 54, "Xtgt K18Track", 200, -100., 100. );
  HB1( 55, "Ytgt K18Track", 200, -100., 100. );
  HB1( 56, "Utgt K18Track", 300, -0.30, 0.30 );
  HB1( 57, "Vtgt K18Track", 300, -0.20, 0.20 );
  HB2( 58, "U%Xtgt K18Track", 100, -100., 100., 100, -0.25, 0.25 );
  HB2( 59, "V%Ytgt K18Track", 100, -100., 100., 100, -0.10, 0.10 );
  HB2( 60, "Y%Xtgt K18Track", 100, -100., 100., 100, -100., 100. );
  HB1( 61, "P K18Track", 500, 0.50, 2.0 );
  HB1( 62, "dP K18Track", 200, -0.1, 0.1 );

  //tree
  HBTree( "k18track","Data Summary Table of K18Tracking" );
  // Trigger Flag
  tree->Branch("evnum",     &event.evnum,     "evnum/I");
  tree->Branch("trignhits", &event.trignhits, "trignhits/I");
  tree->Branch("trigpat",    event.trigpat,   "trigpat[trignhits]/I");
  tree->Branch("trigflag",   event.trigflag,  Form("trigflag[%d]/I",NumOfSegTrig));

  tree->Branch("Time0Seg", &event.Time0Seg,  "Time0Seg/D");
  tree->Branch("deTime0",  &event.deTime0,   "deTime0/D");
  tree->Branch("Time0",    &event.Time0,     "Time0/D");
  tree->Branch("CTime0",   &event.CTime0,    "CTime0/D");

  //BFT
  tree->Branch("bft_ncl",        &event.bft_ncl,    "bft_ncl/I");
  tree->Branch("bft_ncl_bh1mth", &event.bft_ncl_bh1mth, "bft_ncl_bh1mth/I");
  tree->Branch("bft_clsize",      event.bft_clsize, "bft_clsize[bft_ncl]/I");
  tree->Branch("bft_ctime",       event.bft_ctime,  "bft_ctime[bft_ncl]/D");
  tree->Branch("bft_clpos",       event.bft_clpos,  "bft_clpos[bft_ncl]/D");
  tree->Branch("bft_bh1mth",      event.bft_bh1mth, "bft_bh1mth[bft_ncl]/I");

  // BcOut
  tree->Branch("nlBcOut",   &event.nlBcOut,     "nlBcOut/I");
  tree->Branch("ntBcOut",   &event.ntBcOut,     "ntBcOut/I");
  tree->Branch("nhBcOut",    event.nhBcOut,     "nhBcOut[ntBcOut]/I");
  tree->Branch("chisqrBcOut",event.chisqrBcOut, "chisqrIn[ntBcOut]/D");
  tree->Branch("x0BcOut",    event.x0BcOut,     "x0BcOut[ntBcOut]/D");
  tree->Branch("y0BcOut",    event.y0BcOut,     "y0BcOut[ntBcOut]/D");
  tree->Branch("u0BcOut",    event.u0BcOut,     "u0BcOut[ntBcOut]/D");
  tree->Branch("v0BcOut",    event.v0BcOut,     "v0BcOut[ntBcOut]/D");

  // K18
  tree->Branch("ntK18",      &event.ntK18,     "ntK18/I");
  tree->Branch("nhK18",       event.nhK18,     "nhK18[ntK18]/I");
  tree->Branch("chisqrK18",   event.chisqrK18, "chisqrK18[ntK18]/D");
  tree->Branch("p_2nd",       event.p_2nd,     "p_2nd[ntK18]/D");
  tree->Branch("p_3rd",       event.p_3rd,     "p_3rd[ntK18]/D");
  tree->Branch("delta_2nd",   event.delta_2nd, "delta_2nd[ntK18]/D");
  tree->Branch("delta_3rd",   event.delta_3rd, "delta_3rd[ntK18]/D");

  tree->Branch("xin",    event.xin,   "xin[ntK18]/D");
  tree->Branch("yin",    event.yin,   "yin[ntK18]/D");
  tree->Branch("uin",    event.uin,   "uin[ntK18]/D");
  tree->Branch("vin",    event.vin,   "vin[ntK18]/D");

  tree->Branch("xtgtK18",    event.xtgtK18,   "xtgtK18[ntK18]/D");
  tree->Branch("ytgtK18",    event.ytgtK18,   "ytgtK18[ntK18]/D");
  tree->Branch("utgtK18",    event.utgtK18,   "utgtK18[ntK18]/D");
  tree->Branch("vtgtK18",    event.vtgtK18,   "vtgtK18[ntK18]/D");

  tree->Branch("theta",   event.theta,  "theta[ntK18]/D");
  tree->Branch("phi",     event.phi,    "phi[ntK18]/D");

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
      InitializeParameter<BH2Filter>("BH2FLT")       &&
      InitializeParameter<BH1Match>("BH1MTH")        &&
      InitializeParameter<K18TransMatrix>("K18TM")   &&
      InitializeParameter<UserParamMan>("USER")      );
}

//______________________________________________________________________________
bool
ConfMan::FinalizeProcess( void )
{
  return true;
}
