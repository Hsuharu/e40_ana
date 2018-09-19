/**
 *  file: UserBcOutTracking.cc
 *  date: 2017.04.10
 *
 */

#include <cmath>
#include <iomanip>
#include <iostream>
#include <set>
#include <sstream>
#include <string>

#include "ConfMan.hh"
#include "DCRawHit.hh"
#include "DetectorID.hh"
#include "RMAnalyzer.hh"
#include "MathTools.hh"
#include "RootHelper.hh"
#include "KuramaLib.hh"
#include "RawData.hh"
#include "UnpackerManager.hh"
#include "VEvent.hh"
#include "BH2Filter.hh"

#define HodoCut 0

namespace
{
  using namespace root;
  const std::string& classname("BcOutTracking");
  RMAnalyzer&         gRM     = RMAnalyzer::GetInstance();
  const UserParamMan& gUser   = UserParamMan::GetInstance();
  BH2Filter&          gFilter = BH2Filter::GetInstance();
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
class EventBcOutTracking : public VEvent
{
private:
  RawData      *rawData;
  DCAnalyzer   *DCAna;
  HodoAnalyzer *hodoAna;

public:
        EventBcOutTracking( void );
       ~EventBcOutTracking( void );
  bool  ProcessingBegin( void );
  bool  ProcessingEnd( void );
  bool  ProcessingNormal( void );
  bool  InitializeHistograms( void );
  void  InitializeEvent( void );
};

//______________________________________________________________________________
EventBcOutTracking::EventBcOutTracking( void )
  : VEvent(),
    rawData(0),
    DCAna( new DCAnalyzer ),
    hodoAna( new HodoAnalyzer )
{
}

//______________________________________________________________________________
EventBcOutTracking::~EventBcOutTracking( void )
{
  if( DCAna )   delete DCAna;
  if( hodoAna ) delete hodoAna;
  if( rawData ) delete rawData;
}

//______________________________________________________________________________
bool
EventBcOutTracking::ProcessingBegin( void )
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

  //BH1
  int nhBh1;
  double tBh1[NumOfSegBH1];
  double deBh1[NumOfSegBH1];
  double Bh1Seg[NumOfSegBH1];

  //BH2
  int nhBh2;
  double tBh2[NumOfSegBH2];
  double deBh2[NumOfSegBH2];
  double Bh2Seg[NumOfSegBH2];

  // Time0
  double Time0Seg;
  double deTime0;
  double Time0;
  double CTime0;

  //Beam
  int pid;
  double btof;

  // BcOut
  int nhit[NumOfLayersBcOut];

  // BcOutTracking
  int ntrack;
  double chisqr[MaxHits];
  double x_Bh2[MaxHits];
  double x0[MaxHits];
  double y0[MaxHits];
  double u0[MaxHits];
  double v0[MaxHits];
  double pos[NumOfLayersBcOut][MaxHits];

};

//______________________________________________________________________________
namespace root
{
  Event event;
  TH1   *h[MaxHist];
  TTree *tree;
  enum eParticle
    {
      kKaon, kPion, nParticle
    };
}

//______________________________________________________________________________
bool
EventBcOutTracking::ProcessingNormal( void )
{
  static const std::string funcname("["+classname+"::"+__func__+"]");

#if HodoCut
  static const double MinDeBH2   = gUser.GetParameter("DeBH2", 0);
  static const double MaxDeBH2   = gUser.GetParameter("DeBH2", 1);
  static const double MinDeBH1   = gUser.GetParameter("DeBH1", 0);
  static const double MaxDeBH1   = gUser.GetParameter("DeBH1", 1);
  static const double MinBeamToF = gUser.GetParameter("BTOF",  1);
  static const double MaxBeamToF = gUser.GetParameter("BTOF",  1);
#endif
  static const double MaxMultiHitBcOut = gUser.GetParameter("MaxMultiHitBcOut");

  rawData = new RawData;
  rawData->DecodeHits();

  gRM.Decode();

  event.evnum = gRM.EventNumber();

  // Trigger Flag
  int trigflag[NumOfSegTrig] = {};
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
      }
    }
    event.trignhits = trignhits;
  }
  HF1( 1, 0. );

  if( trigflag[SpillEndFlag] ) return true;

  HF1( 1, 1. );

 //////////////BH2 time 0
  hodoAna->DecodeBH2Hits(rawData);
  int nhBh2 = hodoAna->GetNHitsBH2();
  event.nhBh2 = nhBh2;
#if HodoCut
  if( nhBh2==0 ) return true;
#endif
  HF1( 1, 2 );

  double time0    = -999.;
  //////////////BH2 Analysis
  for( int i=0; i<nhBh2; ++i ){
    BH2Hit *hit = hodoAna->GetHitBH2(i);
    if(!hit) continue;
    double seg = hit->SegmentId()+1;
    double  mt = hit->MeanTime();
    double cmt = hit->CMeanTime();
    double ct0 = hit->CTime0();
    double dE  = hit->DeltaE();

#if HodoCut
    if( dE<MinDeBH2 || MaxDeBH2<dE ) continue;
#endif
    event.tBh2[i]   = cmt;
    event.deBh2[i]  = dE;
    event.Bh2Seg[i] = seg;
  }

  BH2Cluster *cl_time0 = hodoAna->GetTime0BH2Cluster();
  if(cl_time0){
    event.Time0Seg = cl_time0->MeanSeg()+1;
    event.deTime0  = cl_time0->DeltaE();
    event.Time0    = cl_time0->Time0();
    event.CTime0   = cl_time0->CTime0();
    time0          = cl_time0->CTime0();
  }else{
    return true;
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

  for(int i=0; i<nhBh1; ++i){
    Hodo2Hit *hit = hodoAna->GetHitBH1(i);
    if(!hit) continue;
    double cmt  = hit->CMeanTime();
    double dE   = hit->DeltaE();
#if HodoCut
    if( dE<MinDeBH1 || MaxDeBH1<dE ) continue;
    if( btof<MinBeamToF || MaxBeamToF<btof ) continue;
#endif
    event.tBh1[i]  = cmt;
    event.deBh1[i] = dE;
  }

  double btof0 = -999.;
  HodoCluster* cl_btof0 = event.Time0Seg > 0? hodoAna->GetBtof0BH1Cluster(event.CTime0) : NULL;
  if(cl_btof0) btof0 = cl_btof0->CMeanTime() - time0;
  event.btof = btof0;

  HF1( 1, 5. );

  HF1( 1, 10. );

  //////////////BC3&4 number of hit layer
  DCAna->DecodeRawHits( rawData );
  DCAna->DriftTimeCutBC34(-10, 50);
  //  DCAna->MakeBH2DCHit(event.Time0Seg-1);

  //BC3&BC4
  double multi_BcOut=0.;
  double multiplicity[] = {0, 0};

  struct hit_info{
    double dt;
    double pos;
  };
  
  {
    for( int layer=1; layer<=NumOfLayersBcOut; ++layer ){
      const DCHitContainer &contOut =DCAna->GetBcOutHC(layer);
      int nhOut=contOut.size();
      event.nhit[layer-1] = nhOut;
      if(layer == 1)  multiplicity[0] = nhOut;
      if(layer == 12) multiplicity[1] = nhOut;
      multi_BcOut += double(nhOut);

      HF1( 100*layer, nhOut );

      int plane_eff = (layer-1)*3;
      bool fl_valid_sig = false;

      std::vector<hit_info> hit_cont;
      for( int i=0; i<nhOut; ++i ){
	DCHit *hit=contOut[i];
	double wire=hit->GetWire();

	HF1( 100*layer+1, wire-0.5 );

	int nhtdc = hit->GetTdcSize();
	int tdc1st = -1;
	for( int k=0; k<nhtdc; k++ ){
	  int tdc = hit->GetTdcVal(k);
	  if( tdc > tdc1st ){
	    tdc1st=tdc;
	    fl_valid_sig = true;
	  }
	}

	if( i<MaxHits )
	  event.pos[layer-1][i] = hit->GetWirePosition();

	HF1( 100*layer+2, tdc1st );
	HF1( 10000*layer+int(wire), tdc1st );

	int nhdt = hit->GetDriftTimeSize();
	for( int k=0; k<nhdt; k++ ){
	  double dt = hit->GetDriftTime(k);
	  HF1( 100*layer+3, dt );
	  HF1( 10000*layer+1000+int(wire), dt );

	  double tot = hit->GetTot(k);
	  HF1( 100*layer+5, tot);
	  
	  hit_info one_hit;
	  one_hit.dt  = dt;
	  one_hit.pos = wire;
	  
	  hit_cont.push_back(one_hit);
	}
	int nhdl = hit->GetDriftTimeSize();
	for( int k=0; k<nhdl; k++ ){
	  double dl = hit->GetDriftLength(k);
	  HF1( 100*layer+4, dl );
	}
      }
      if(fl_valid_sig){
	++plane_eff;
      }else{
      }
      HF1(38, plane_eff);

      std::sort(hit_cont.begin(), hit_cont.end(),
		[](const hit_info& a_info, const hit_info& b_info)->bool
		{return (a_info.dt < b_info.dt);});
      
      for(int i = 1; i<hit_cont.size(); ++i){
	HF1( 100*layer+6, hit_cont.at(i).dt -hit_cont.at(0).dt );
	HF1( 100*layer+7, hit_cont.at(i).pos-hit_cont.at(0).pos );
      }
    }// for(layer)
  }
  HF2(41, multiplicity[0], multiplicity[1]);

  if( multi_BcOut/double(NumOfLayersBcOut) > MaxMultiHitBcOut )
    return true;

  HF1( 1, 11. );

#if 1
  // Bc Out
  //  std::cout << "==========TrackSearch BcOut============" << std::endl;
  BH2Filter::FilterList cands;
  gFilter.Apply((Int_t)event.Time0Seg-1, *DCAna, cands);
  bool status_tracking = DCAna->TrackSearchBcOut( cands, event.Time0Seg-1 );
  //  bool status_tracking = DCAna->TrackSearchBcOut( cands, -1 );
  //  bool status_tracking = DCAna->TrackSearchBcOut(-1);
  DCAna->ChiSqrCutBcOut(10);

  int nt=DCAna->GetNtracksBcOut();
  event.ntrack=nt;
  HF1( 10, double(nt) );
  HF1( 40, status_tracking? double(nt) : -1);
  for( int it=0; it<nt; ++it ){
    DCLocalTrack *tp=DCAna->GetTrackBcOut(it);

    int nh=tp->GetNHit();
    double chisqr=tp->GetChiSquare();
    double x0=tp->GetX0(), y0=tp->GetY0();
    double u0=tp->GetU0(), v0=tp->GetV0();

    double cost = 1./sqrt(1.+u0*u0+v0*v0);
    double theta = acos(cost)*math::Rad2Deg();

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

    double xtgt=tp->GetX(1800.), ytgt=tp->GetY(1800.);
    double utgt=u0, vtgt=v0;
    HF1( 21, xtgt ); HF1( 22, ytgt );
    HF1( 23, utgt ); HF1( 24, vtgt );
    HF2( 25, xtgt, utgt ); HF2( 26, ytgt, vtgt );
    HF2( 27, xtgt, ytgt );

    double xbac=tp->GetX(603.), ybac=tp->GetY(885.);
    double ubac=u0, vbac=v0;
    HF1( 31, xbac ); HF1( 32, ybac );
    HF1( 33, ubac ); HF1( 34, vbac );
    HF2( 35, xbac, ubac ); HF2( 36, ybac, vbac );
    HF2( 37, xbac, ybac );

    double Xangle = -1000*std::atan(u0);

    HF2(51, -tp->GetX(245.), Xangle);
    HF2(52, -tp->GetX(600.), Xangle);
    HF2(53, -tp->GetX(1200.), Xangle);
    HF2(54, -tp->GetX(1600.), Xangle);

    HF2(61, tp->GetX(600.), tp->GetX(245.));
    HF2(62, tp->GetX(1200.), tp->GetX(245.));
    HF2(63, tp->GetX(1600.), tp->GetX(245.));

    for( int ih=0; ih<nh; ++ih ){
      DCLTrackHit *hit=tp->GetHit(ih);
      int layerId=hit->GetLayer()-112;

      HF1( 13, layerId );
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
	HFProf( 100*layerId+20, dt, std::abs(xlcal-wp));
	HF2( 100*layerId+22, dt, std::abs(xlcal-wp));
	HFProf( 100000*layerId+3000+int(wire), xlcal-wp,dt);
	HF2( 100000*layerId+4000+int(wire), xlcal-wp,dt);
      }
    }
  }

#endif

  HF1( 1, 12. );

  return true;
}

//______________________________________________________________________________
void
EventBcOutTracking::InitializeEvent( void )
{
  event.evnum     = 0;
  event.ntrack    = -999;
  event.trignhits = 0;
  event.pid       = -1;
  event.btof      = -999.;

  event.Time0Seg  = -1;
  event.deTime0   = -1;
  event.Time0     = -999;
  event.CTime0    = -999;

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

  for ( int it=0; it<NumOfLayersBcOut; ++it ){
    event.nhit[it] = 0;
    for( int that=0; that<MaxHits; ++that ){
      event.pos[it][that] = -9999.;
    }
  }
}

//______________________________________________________________________________
bool
EventBcOutTracking::ProcessingEnd( void )
{
  tree->Fill();
  return true;
}

//______________________________________________________________________________
VEvent*
ConfMan::EventAllocator( void )
{
  return new EventBcOutTracking;
}

//______________________________________________________________________________
namespace
{
  const int NbinBcOutTdc   = 1000;
  const double MinBcOutTdc =  200.;
  const double MaxBcOutTdc = 1200.;

  const int NbinBcOutDT   =  100;
  const double MinBcOutDT =  -10.;
  const double MaxBcOutDT =   90.;

  const int NbinBcOutDL   = 50;
  const double MinBcOutDL =  -0.5;
  const double MaxBcOutDL =   2.0;
}
//______________________________________________________________________________
bool
ConfMan:: InitializeHistograms( void )
{
  HB1( 1, "Status", 20, 0., 20. );

  //***********************Chamber
  // BC3
  for( int i=1; i<=NumOfLayersBc; ++i ){
    TString title0 = Form("#Hits BC3#%2d", i);
    TString title1 = Form("Hitpat BC3#%2d", i);
    TString title2 = Form("Tdc BC3#%2d", i);
    TString title3 = Form("Drift Time BC3#%2d", i);
    TString title4 = Form("Drift Length BC3#%2d", i);
    TString title5 = Form("TOT BC3#%2d", i);
    TString title6 = Form("Time interval from 1st hit BC3#%2d", i);
    TString title7 = Form("Position interval from 1st hit BC3#%2d", i);
    HB1( 100*i+0, title0, MaxWireBC3+1, 0., double(MaxWireBC3+1) );
    HB1( 100*i+1, title1, MaxWireBC3+1, 0., double(MaxWireBC3+1) );
    HB1( 100*i+2, title2, NbinBcOutTdc, MinBcOutTdc, MaxBcOutTdc );
    HB1( 100*i+3, title3, NbinBcOutDT, MinBcOutDT, MaxBcOutDT );
    HB1( 100*i+4, title4, NbinBcOutDL, MinBcOutDL, MaxBcOutDL );
    HB1( 100*i+5, title5, 300,    0, 300 );
    HB1( 100*i+6, title6, 60,     0, 60 );
    HB1( 100*i+7, title7, 64,   -32, 32 );
    for (int wire=1; wire<=MaxWireBC3; wire++) {
      TString title10 = Form("Tdc BC3#%2d Wire#%d", i, wire);
      TString title11 = Form("Drift Time BC3#%2d Wire#%d", i, wire);
      TString title12 = Form("Drift Length BC3#%2d Wire#%d", i, wire);
      TString title15 = Form("Drift Time BC3#%2d Wire#%d [Track]", i, wire);
      HB1( 10000*i+wire, title10, NbinBcOutTdc, MinBcOutTdc, MaxBcOutTdc );
      HB1( 10000*i+1000+wire, title11, NbinBcOutDT, MinBcOutDT, MaxBcOutDT );
      HB1( 10000*i+2000+wire, title12, NbinBcOutDL, MinBcOutDL, MaxBcOutDL );
      HB1( 10000*i+5000+wire, title15, NbinBcOutDT, MinBcOutDT, MaxBcOutDT );
    }
  }

  // BC4
  for( int i=1; i<=NumOfLayersBc+1; ++i ){
    TString title0 = Form("#Hits BC4#%2d", i);
    TString title1 = Form("Hitpat BC4#%2d", i);
    TString title2 = Form("Tdc BC4#%2d", i);
    TString title3 = Form("Drift Time BC4#%2d", i);
    TString title4 = Form("Drift Length BC4#%2d", i);
    TString title5 = Form("TOT BC4#%2d", i);
    TString title6 = Form("Time interval from 1st hit BC4#%2d", i);
    TString title7 = Form("Position interval from 1st hit BC4#%2d", i);
    HB1( 100*(i+6)+0, title0, MaxWireBC4+1, 0., double(MaxWireBC4+1) );
    HB1( 100*(i+6)+1, title1, MaxWireBC4+1, 0., double(MaxWireBC4+1) );
    HB1( 100*(i+6)+2, title2, NbinBcOutTdc, MinBcOutTdc, MaxBcOutTdc );
    HB1( 100*(i+6)+3, title3, NbinBcOutDT, MinBcOutDT, MaxBcOutDT );
    HB1( 100*(i+6)+4, title4, NbinBcOutDL, MinBcOutDL, MaxBcOutDL );
    HB1( 100*(i+6)+5, title5, 300,    0, 300 );
    HB1( 100*(i+6)+6, title6, 60,     0, 60 );
    HB1( 100*(i+6)+7, title7, 64,   -32, 32 );
    for (int wire=1; wire<=MaxWireBC4; wire++) {
      TString title10 = Form("Tdc BC4#%2d Wire#%d", i, wire);
      TString title11 = Form("Drift Time BC4#%2d Wire#%d", i, wire);
      TString title12 = Form("Drift Length BC4#%2d Wire#%d", i, wire);
      TString title15 = Form("Drift Time BC4#%2d Wire#%d [Track]", i, wire);
      HB1( 10000*(i+6)+wire, title10, NbinBcOutTdc, MinBcOutTdc, MaxBcOutTdc );
      HB1( 10000*(i+6)+1000+wire, title11, NbinBcOutDT, MinBcOutDT, MaxBcOutDT );
      HB1( 10000*(i+6)+2000+wire, title12, NbinBcOutDL, MinBcOutDL, MaxBcOutDL );
      HB1( 10000*(i+6)+5000+wire, title15, NbinBcOutDT, MinBcOutDT, MaxBcOutDT );
    }
  }

  // Tracking Histgrams
  HB1( 10, "#Tracks BcOut", 10, 0., 10. );
  HB1( 11, "#Hits of Track BcOut", 15, 0., 15. );
  HB1( 12, "Chisqr BcOut", 500, 0., 50. );
  HB1( 13, "LayerId BcOut", 15, 0., 15. );
  HB1( 14, "X0 BcOut", 400, -100., 100. );
  HB1( 15, "Y0 BcOut", 400, -100., 100. );
  HB1( 16, "U0 BcOut", 200, -0.20, 0.20 );
  HB1( 17, "V0 BcOut", 200, -0.20, 0.20 );
  HB2( 18, "U0%X0 BcOut", 100, -100., 100., 100, -0.20, 0.20 );
  HB2( 19, "V0%Y0 BcOut", 100, -100., 100., 100, -0.20, 0.20 );
  HB2( 20, "X0%Y0 BcOut", 100, -100., 100., 100, -100, 100 );

  HB1( 21, "Xtgt BcOut", 400, -100., 100. );
  HB1( 22, "Ytgt BcOut", 400, -100., 100. );
  HB1( 23, "Utgt BcOut", 200, -0.20, 0.20 );
  HB1( 24, "Vtgt BcOut", 200, -0.20, 0.20 );
  HB2( 25, "Utgt%Xtgt BcOut", 100, -100., 100., 100, -0.20, 0.20 );
  HB2( 26, "Vtgt%Ytgt BcOut", 100, -100., 100., 100, -0.20, 0.20 );
  HB2( 27, "Xtgt%Ytgt BcOut", 100, -100., 100., 100, -100, 100 );

  HB1( 31, "Xbac BcOut", 400, -100., 100. );
  HB1( 32, "Ybac BcOut", 400, -100., 100. );
  HB1( 33, "Ubac BcOut", 200, -0.20, 0.20 );
  HB1( 34, "Vbac BcOut", 200, -0.20, 0.20 );
  HB2( 35, "Ubac%Xbac BcOut", 100, -100., 100., 100, -0.20, 0.20 );
  HB2( 36, "Vbac%Ybac BcOut", 100, -100., 100., 100, -0.20, 0.20 );
  HB2( 37, "Xbac%Ybac BcOut", 100, -100., 100., 100, -100, 100 );
  HB1( 38, "Plane Eff", 36, 0, 36);

  HB2( 51, "X-X' 245 BcOut", 400, -100., 100., 120, -60, 60);
  HB2( 52, "X-X' 600 BcOut", 400, -100., 100., 120, -60, 60);
  HB2( 53, "X-X' 1200 BcOut", 400, -100., 100., 120, -60, 60);
  HB2( 54, "X-X' 1600 BcOut", 400, -100., 100., 120, -60, 60);

  HB2( 61, "X-X 600 BcOut", 400, -100., 100., 400, -100, 100);
  HB2( 62, "X-X 1200 BcOut", 400, -100., 100., 400, -100, 100);
  HB2( 63, "X-X 1600 BcOut", 400, -100., 100., 400, -100, 100);

  // Analysis status
  HB1( 40, "Tacking status", 11, -1., 10. );
  HB2( 41, "BC3X0/BC4X1", 20, 0, 20, 20, 0, 20);

  for( int i=1; i<=NumOfLayersBcOut; ++i ){
    TString title11 = Form("HitPat BcOut%2d [Track]", i);
    TString title12 = Form("DriftTime BcOut%2d [Track]", i);
    TString title13 = Form("DriftLength BcOut%2d [Track]", i);
    TString title14 = Form("Position BcOut%2d", i);
    TString title15 = Form("Residual BcOut%2d", i);
    TString title16 = Form("Resid%%Pos BcOut%2d", i);
    TString title17 = Form("Y%%Xcal BcOut%2d", i);
    TString title18 = Form("Res%%dl BcOut%2d", i);
    TString title19 = Form("HitPos%%DriftTime BcOut%2d", i);
    TString title20 = Form("DriftLength%%DriftTime BcOut%2d", i);
    TString title21 = title15 + " [w/o Self]";
    TString title22 = title20;
    TString title40 = Form("TOT BcOut%2d [Track]", i);
    TString title71 = Form("Residual BcOut%2d (0<theta<15)", i);
    TString title72 = Form("Residual BcOut%2d (15<theta<30)", i);
    TString title73 = Form("Residual BcOut%2d (30<theta<45)", i);
    TString title74 = Form("Residual BcOut%2d (45<theta)", i);
    HB1( 100*i+11, title11, 64, 0., 64. );
    HB1( 100*i+12, title12, 160, -10, 150 );
    HB1( 100*i+13, title13, 50, -0.5, 3);
    HB1( 100*i+14, title14, 100, -250., 250. );
    HB1( 100*i+15, title15, 400, -2.0, 2.0 );
    HB2( 100*i+16, title16, 250, -250., 250., 100, -1.0, 1.0 );
    HB2( 100*i+17, title17, 100, -250., 250., 100, -250., 250. );
    HB2( 100*i+18, title18, 100, -3., 3., 100, -1.0, 1.0 );
    HB2( 100*i+19, title19, 100, -5., 100., 100, -3, 3);
    HBProf( 100*i+20, title20, 100, -5., 50., 0., 12. );
    HB2( 100*i+22, title22,
	 NbinBcOutDT, MinBcOutDT, MaxBcOutDT,
	 NbinBcOutDL, MinBcOutDL, MaxBcOutDL );
    HB1( 100*i+21, title21, 200, -5.0, 5.0 );
    HB1( 100*i+40, title40, 300,    0, 300 );
    HB1( 100*i+71, title71, 200, -5.0, 5.0 );
    HB1( 100*i+72, title72, 200, -5.0, 5.0 );
    HB1( 100*i+73, title73, 200, -5.0, 5.0 );
    HB1( 100*i+74, title74, 200, -5.0, 5.0 );
    for (int j=1; j<=64; j++) {
      TString title = Form("XT of Layer %2d Wire #%4d", i, j);
      HBProf( 100000*i+3000+j, title, 100, -4., 4., -5., 40. );
      HB2( 100000*i+4000+j, title, 100, -4., 4., 100, -5., 40. );
    }
  }

  ////////////////////////////////////////////
  //Tree
  HBTree( "bcout","tree of BcOutTracking" );
  tree->Branch("evnum",     &event.evnum,     "evnum/I");

  tree->Branch("trignhits", &event.trignhits, "trignhits/I");
  tree->Branch("trigpat",    event.trigpat,   Form("trigpat[%d]/I", NumOfSegTrig));
  tree->Branch("trigflag",   event.trigflag,  Form("trigflag[%d]/I", NumOfSegTrig));

  //Hodoscope
  tree->Branch("nhBh1",    &event.nhBh1,   "nhBh1/I");
  tree->Branch("tBh1",      event.tBh1,    Form("tBh1[%d]/I",   NumOfSegBH1));
  tree->Branch("deBh1",     event.deBh1,   Form("deBh1[%d]/I",  NumOfSegBH1));
  tree->Branch("Bh1Seg",    event.Bh1Seg,  Form("Bh1Seg[%d]/I", NumOfSegBH1));

  tree->Branch("nhBh2",    &event.nhBh2,   "nhBh2/I");
  tree->Branch("tBh2",      event.tBh2,    Form("tBh2[%d]/I",   NumOfSegBH2));
  tree->Branch("deBh2",     event.deBh2,   Form("deBh2[%d]/I",  NumOfSegBH2));
  tree->Branch("Bh2Seg",    event.Bh2Seg,  Form("Bh2Seg[%d]/I", NumOfSegBH2));

  tree->Branch("Time0Seg", &event.Time0Seg,  "Time0Seg/D");
  tree->Branch("deTime0",  &event.deTime0,   "deTime0/D");
  tree->Branch("Time0",    &event.Time0,     "Time0/D");
  tree->Branch("CTime0",   &event.CTime0,    "CTime0/D");

  tree->Branch("pid",      &event.pid,      "pid/I");
  tree->Branch("btof",     &event.btof,     "btof/D");

  tree->Branch("nhit",     &event.nhit,     Form("nhit[%d]/I", NumOfLayersBcOut ) );

  tree->Branch("ntrack",   &event.ntrack,   "ntrack/I");
  tree->Branch("chisqr",    event.chisqr,   "chisqr[ntrack]/D");
  tree->Branch("x0",        event.x0,       "x0[ntrack]/D");
  tree->Branch("y0",        event.y0,       "y0[ntrack]/D");
  tree->Branch("u0",        event.u0,       "u0[ntrack]/D");
  tree->Branch("v0",        event.v0,       "v0[ntrack]/D");

  TString layer_name[NumOfLayersBcOut] =
    { "bc3x0", "bc3x1", "bc3v0", "bc3v1", "bc3u0", "bc3u1",
      "bc4u0", "bc4u1", "bc4v0", "bc4v1", "bc4x0", "bc4x1" };
  for( int i=0; i<NumOfLayersBcOut; ++i ){
    tree->Branch( Form("%s_pos", layer_name[i].Data() ), event.pos[i],
		   Form("%s_pos[%d]/D", layer_name[i].Data(), MaxHits ) );
  }

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
      InitializeParameter<UserParamMan>("USER")      );
}

//______________________________________________________________________________
bool
ConfMan::FinalizeProcess( void )
{
  return true;
}
