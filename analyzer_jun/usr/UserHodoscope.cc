/**
 *  file: UserHodoscope.cc
 *  date: 2017.04.10
 *
 */

#include <cmath>
#include <iostream>
#include <sstream>

#include "BH2Cluster.hh"
#include "BH2Hit.hh"
#include "ConfMan.hh"
#include "DetectorID.hh"
#include "RMAnalyzer.hh"
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

namespace
{
  using namespace root;
  const std::string& class_name("EventHodoscope");
  RMAnalyzer& gRM = RMAnalyzer::GetInstance();
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
class EventHodoscope : public VEvent
{
private:
  RawData      *rawData;
  HodoAnalyzer *hodoAna;

public:
        EventHodoscope( void );
       ~EventHodoscope( void );
  bool  ProcessingBegin( void );
  bool  ProcessingEnd( void );
  bool  ProcessingNormal( void );
  bool  InitializeHistograms( void );
  void  InitializeEvent( void );
};

//______________________________________________________________________________
EventHodoscope::EventHodoscope( void )
  : VEvent(),
    rawData(0),
    hodoAna(new HodoAnalyzer)
{
}

//______________________________________________________________________________
EventHodoscope::~EventHodoscope( void )
{
  delete hodoAna;
  delete rawData;
}

//______________________________________________________________________________
struct Event
{
  int evnum;
  int spill;

  int trignhits;
  int trigpat[NumOfSegTrig];
  int trigflag[NumOfSegTrig];

  int bh1nhits;
  int bh1hitpat[MaxHits];
  double bh1ua[NumOfSegBH1];
  double bh1ut[NumOfSegBH1][MaxDepth];
  double bh1da[NumOfSegBH1];
  double bh1dt[NumOfSegBH1][MaxDepth];

  int bh2nhits;
  int bh2hitpat[MaxHits];
  double bh2ua[NumOfSegBH2];
  double bh2ut[NumOfSegBH2][MaxDepth];
  double bh2da[NumOfSegBH2];
  double bh2dt[NumOfSegBH2][MaxDepth];

  int fpga_bh2mtnhits;
  int fpga_bh2mthitpat[MaxHits];
  double fpga_bh2mt[NumOfSegBH2][MaxDepth];

  int sacnhits;
  int sachitpat[MaxHits];
  double saca[NumOfSegSAC];
  double sact[NumOfSegSAC][MaxDepth];

  int tofnhits;
  int tofhitpat[MaxHits];
  double tofua[NumOfSegTOF];
  double tofut[NumOfSegTOF][MaxDepth];
  double tofda[NumOfSegTOF];
  double tofdt[NumOfSegTOF][MaxDepth];
 
  int tofhtnhits;
  int tofhthitpat[MaxHits];
  double tofhtt[NumOfSegTOF][MaxDepth];

  int lcnhits;
  int lchitpat[MaxHits];
  double lct[NumOfSegLC][MaxDepth];

  ////////// Normalized
  double bh1mt[NumOfSegBH1][MaxDepth];
  double bh1cmt[NumOfSegBH1][MaxDepth];
  double bh1de[NumOfSegBH1];

  double bh2mt[NumOfSegBH2][MaxDepth];
  double bh2cmt[NumOfSegBH2][MaxDepth];
  double bh2de[NumOfSegBH2];
  
  double sacmt[NumOfSegSAC][MaxDepth];
  double sacde[NumOfSegSAC];

  double t0[NumOfSegBH2][MaxDepth];
  double ct0[NumOfSegBH2][MaxDepth];
  double btof[NumOfSegBH1][NumOfSegBH2];
  double cbtof[NumOfSegBH1][NumOfSegBH2];

  double tofmt[NumOfSegTOF][MaxDepth];
  double tofde[NumOfSegTOF];

  double tofhtmt[NumOfSegTOF][MaxDepth];

  double lcmt[NumOfSegLC][MaxDepth];

  // Time0
  double Time0Seg;
  double deTime0;
  double Time0;
  double CTime0;

  // Btof0 BH1
  double Btof0Seg;
  double deBtof0;
  double Btof0;
  double CBtof0;
};

//______________________________________________________________________________
struct Dst
{
  int evnum;
  int spill;

  int trignhits;
  int trigpat[NumOfSegTrig];
  int trigflag[NumOfSegTrig];

  int    nhBh1;
  int    csBh1[NumOfSegBH1*MaxDepth];
  double Bh1Seg[NumOfSegBH1*MaxDepth];
  double tBh1[NumOfSegBH1*MaxDepth];
  double dtBh1[NumOfSegBH1*MaxDepth];
  double deBh1[NumOfSegBH1*MaxDepth];
  double btof[NumOfSegBH1*MaxDepth];
  double cbtof[NumOfSegBH1*MaxDepth];

  // Btof0 BH1
  double Btof0Seg;
  double deBtof0;
  double Btof0;
  double CBtof0;

  int    nhBh2;
  int    csBh2[NumOfSegBH2*MaxDepth];
  double Bh2Seg[NumOfSegBH2*MaxDepth];
  double tBh2[NumOfSegBH2*MaxDepth];
  double t0Bh2[NumOfSegBH2*MaxDepth];
  double dtBh2[NumOfSegBH2*MaxDepth];
  double deBh2[NumOfSegBH2*MaxDepth];

  // Time0
  double Time0Seg;
  double deTime0;
  double Time0;
  double CTime0;

  int    nhTof;
  int    csTof[NumOfSegTOF*MaxDepth];
  double TofSeg[NumOfSegTOF*MaxDepth];
  double tTof[NumOfSegTOF*MaxDepth];
  double dtTof[NumOfSegTOF*MaxDepth];
  double deTof[NumOfSegTOF*MaxDepth];

  int    nhHtTof;
  int    csHtTof[NumOfSegTOF*MaxDepth];
  double HtTofSeg[NumOfSegTOF*MaxDepth];
  double tHtTof[NumOfSegTOF*MaxDepth];

  int    nhLc;
  int    csLc[NumOfSegLC*MaxDepth];
  double LcSeg[NumOfSegLC*MaxDepth];
  double tLc[NumOfSegLC*MaxDepth];

  int    nhSac;
  int    csSac[NumOfSegSAC*MaxDepth];
  double SacSeg[NumOfSegSAC*MaxDepth];
  double tSac[NumOfSegSAC*MaxDepth];
  double deSac[NumOfSegSAC*MaxDepth];

  // for HodoParam
  double utTofSeg[NumOfSegTOF][MaxDepth];
  double dtTofSeg[NumOfSegTOF][MaxDepth];
  double udeTofSeg[NumOfSegTOF];
  double ddeTofSeg[NumOfSegTOF];


};

//______________________________________________________________________________
namespace root
{
  Event  event;
  Dst    dst;
  TH1   *h[MaxHist];
  TTree *tree;
  TTree *hodo;
  enum eDetHid {
    BH1Hid  = 10000,
    BH2Hid  = 20000,
    SACHid  = 30000,
    TOFHid  = 40000,
    LCHid   = 50000,
    HtTOFHid= 60000
  };
}

//______________________________________________________________________________
bool
EventHodoscope::ProcessingBegin( void )
{
  InitializeEvent();
  return true;
}

//______________________________________________________________________________
bool
EventHodoscope::ProcessingNormal( void )
{
  static const std::string func_name("["+class_name+"::"+__func__+"()]");

  rawData = new RawData;
  rawData->DecodeHits();

  gRM.Decode();

  event.evnum = gRM.EventNumber();
  event.evnum = gRM.EventNumber();
  event.spill = gRM.SpillNumber();
  dst.evnum   = gRM.EventNumber();
  dst.spill   = gRM.SpillNumber();

  HF1(1, 0);

  //**************************************************************************
  //****************** RawData

  // Trig
  {
    int trignhits = 0;
    const HodoRHitContainer &cont = rawData->GetTrigRawHC();
    int nh = cont.size();
    for(int i=0; i<nh; ++i){
      HodoRawHit *hit = cont[i];
      int seg = hit->SegmentId()+1;
      int tdc = hit->GetTdc1();
      if( tdc>0 ){
	event.trigpat[trignhits] = seg;
	event.trigflag[seg-1]    = tdc;
	dst.trigpat[trignhits]   = seg;
	dst.trigflag[seg-1]      = tdc;
	HF1( 10, seg-1 );
	HF1( 10+seg, tdc );
	trignhits++;
      }
    }
    event.trignhits = trignhits;
    dst.trignhits   = trignhits;
  }

  // if( event.trigflag[SpillEndTrig]>0 )  return true;

  HF1(1, 1);

  // BH1
  {
    int bh1_nhits = 0;
    const HodoRHitContainer &cont = rawData->GetBH1RawHC();
    int nh = cont.size();
    HF1( BH1Hid +0, double(nh) );
    int nh1 = 0, nh2 = 0;
    for( int i=0; i<nh; ++i ){
      HodoRawHit *hit = cont[i];
      int seg = hit->SegmentId()+1;
      HF1( BH1Hid +1, seg-0.5 );
      int Au = hit->GetAdcUp(), Ad = hit->GetAdcDown();
      int Tu = hit->GetTdcUp(), Td = hit->GetTdcDown();
      event.bh1ua[seg-1] = Au;
      event.bh1da[seg-1] = Ad;

      //Up
      {
	HF1( BH1Hid +100*seg +1, double(Au) );
	if( Tu>0 ){
	  HF1( BH1Hid +100*seg +5, double(Au) );
	}
	else{
	  HF1( BH1Hid +100*seg +7, double(Au) );
	}

	int n_mhit = hit->GetSizeTdcUp();
	for(int m = 0; m<n_mhit; ++m){
	  int T = hit->GetTdcUp(m);
	  if(T > 0) HF1( BH1Hid +100*seg +3, double(T) );
	  event.bh1ut[seg-1][m] = T;
	}// for(m)
      }

      //Down
      {
	HF1( BH1Hid +100*seg +2, double(Ad) );
	if( Td>0 ){
	  HF1( BH1Hid +100*seg +6, double(Ad) );
	}
	else{
	  HF1( BH1Hid +100*seg +8, double(Ad) );
	}

	int n_mhit = hit->GetSizeTdcDown();
	for(int m = 0; m<n_mhit; ++m){
	  int T = hit->GetTdcDown(m);
	  if(T > 0) HF1( BH1Hid +100*seg +4, double(T) );
	  event.bh1dt[seg-1][m] = T;
	}// for(m)
      }

      //HitPat
      if( Tu>0 && Td>0 ){
	event.bh1hitpat[bh1_nhits] = seg;
	bh1_nhits++;
      }
      if( Tu>0 || Td>0 ){
	++nh1; HF1( BH1Hid +3, seg-0.5 );
      }
      if( Tu>0 && Td>0 ){
	++nh2; HF1( BH1Hid +5, seg-0.5 );
      }
    }
    HF1( BH1Hid +2, double(nh1) ); HF1( BH1Hid +4, double(nh2) );
    event.bh1nhits = bh1_nhits;
  }

  // BH2
  {
    int bh2_nhits = 0;
    const HodoRHitContainer &cont = rawData->GetBH2RawHC();
    int nh = cont.size();
    HF1( BH2Hid, double(nh) );
    int nh1 = 0, nh2 = 0;
    for( int i=0; i<nh; ++i ){
      HodoRawHit *hit = cont[i];
      int seg = hit->SegmentId()+1;
      HF1( BH2Hid +1, seg-0.5 );
      int Au = hit->GetAdcUp(), Ad = hit->GetAdcDown();
      int Tu = hit->GetTdcUp(), Td = hit->GetTdcDown();
      event.bh2ua[seg-1] = Au;
      event.bh2da[seg-1] = Ad;

      //Up
      {
	HF1( BH2Hid +100*seg +1, double(Au) );
	if( Tu>0 ){

	  HF1( BH2Hid +100*seg +5, double(Au) );
	}
	else{
	  HF1( BH2Hid +100*seg +7, double(Au) );
	}
	
	int n_mhit = hit->GetSizeTdcUp();
	for(int m = 0; m<n_mhit; ++m){
	  int T = hit->GetTdcUp(m);
	  if(T > 0) HF1( BH2Hid +100*seg +3, double(T) );
	  event.bh2ut[seg-1][m] = T;
	}// for(m)
      }

      //Down
      {
	HF1( BH2Hid +100*seg +2, double(Ad) );
	if( Td>0 ){
	  HF1( BH2Hid +100*seg +6, double(Ad) );
	}
	else{
	  HF1( BH2Hid +100*seg +8, double(Ad) );
	}

	int n_mhit = hit->GetSizeTdcDown();
	for(int m = 0; m<n_mhit; ++m){
	  int T = hit->GetTdcDown(m);
	  if(T > 0) HF1( BH2Hid +100*seg +4, double(T) );
	  event.bh2dt[seg-1][m] = T;
	}// for(m)
      }


      //HitPat
      if( Tu>0 && Td>0 ){
	event.bh2hitpat[bh2_nhits] = seg;
	bh2_nhits++;
      }
      if( Tu>0 || Td>0 ){
	++nh1; HF1( BH2Hid +3, seg-0.5 );
      }
      if( Tu>0 && Td>0 ){
	++nh2; HF1( BH2Hid +5, seg-0.5 );
      }
    }
    HF1( BH2Hid +2, double(nh1) ); HF1( BH2Hid +4, double(nh2) );
    event.bh2nhits = bh2_nhits;
  }

#if 1
  // FPGA BH2MT
  {
    int bh2_nhits = 0;
    const HodoRHitContainer &cont = rawData->GetFpgaBH2MtRawHC();
    int nh = cont.size();
    //    HF1( BH2Hid +0, double(nh) );
    for( int i=0; i<nh; ++i ){
      HodoRawHit *hit = cont[i];
      int seg = hit->SegmentId()+1;
      //      HF1( BH2Hid +1, seg-0.5 );
      int mhit1 = hit->GetSizeTdcUp();
      if( mhit1>0 ){
	event.fpga_bh2mthitpat[bh2_nhits] = seg;
	bh2_nhits++;
      }

      // Up
      for(int m = 0; m<mhit1; ++m){
	int Tu = hit->GetTdcUp(m);
	event.fpga_bh2mt[seg-1][m] = Tu;
      }
    }
    event.fpga_bh2mtnhits = bh2_nhits;
  }
#endif

  // SAC
  {
    int sac_nhits = 0;
    const HodoRHitContainer &cont = rawData->GetSACRawHC();
    int nh = cont.size();
    HF1( SACHid, double(nh) );
    int nh1 = 0;
    for( int i=0; i<nh; ++i ){
      HodoRawHit *hit = cont[i];
      int seg = hit->SegmentId()+1;
      HF1( SACHid+1, seg-0.5 );
      int A = hit->GetAdcUp();
      int T = hit->GetTdcUp();
      event.saca[seg-1] = A;

      //Up
      {
	HF1( SACHid+100*seg+1, double(A) );
	if( T>0 ){
	  HF1( SACHid+100*seg+5, double(A) );
	}
	else{
	  HF1( SACHid+100*seg+7, double(A) );
	}
	
	int n_mhit = hit->GetSizeTdcUp();
	for(int m = 0; m<n_mhit; ++m){
	  int T = hit->GetTdcUp(m);
	  if(T > 0) HF1( SACHid+100*seg+3, double(T) );
	  event.sact[seg-1][m] = T;
	}// for(m)
      }

      //hitpat
      if( T>0 ) event.sachitpat[sac_nhits++]= seg;
      if( T>0 ){
  	++nh1; HF1( SACHid+3, seg-0.5 );
      }
    }
    HF1( SACHid+2, double(nh1) );
    event.sacnhits = sac_nhits;
  }

  // TOF
  {
    int tof_nhits = 0;
    const HodoRHitContainer &cont = rawData->GetTOFRawHC();
    int nh = cont.size();
    HF1( TOFHid, double(nh) );
    int nh1 = 0, nh2 = 0;
    for( int i=0; i<nh; ++i ){
      HodoRawHit *hit = cont[i];
      int seg = hit->SegmentId()+1;
      HF1( TOFHid+1, seg-0.5 );
      int Au = hit->GetAdcUp(), Ad = hit->GetAdcDown();
      int Tu = hit->GetTdcUp(), Td = hit->GetTdcDown();
      event.tofua[seg-1] = Au;
      event.tofda[seg-1] = Ad;

      //Up
      {
	HF1( TOFHid+100*seg+1, double(Au) );
	if( Tu>0 ){
	  HF1( TOFHid+100*seg+5, double(Au) );
	}
	else{
	  HF1( TOFHid+100*seg+7, double(Au) );
	}
      
	int n_mhit = hit->GetSizeTdcUp();
	for(int m = 0; m<n_mhit; ++m){
	  int T = hit->GetTdcUp(m);
	  if(T > 0) HF1( TOFHid +100*seg +3, double(T));
	  event.tofut[seg-1][m] = T;
	}// for(m)
      }
      
      //Down
      {
	HF1( TOFHid+100*seg+2, double(Ad) );
	if( Td>0 ){
	  HF1( TOFHid+100*seg+6, double(Ad) );
	}
	else{
	  HF1( TOFHid+100*seg+8, double(Ad) );
	}

	int n_mhit = hit->GetSizeTdcDown();
	for(int m = 0; m<n_mhit; ++m){
	  int T = hit->GetTdcDown(m);
	  if(T > 0) HF1( TOFHid +100*seg +4, double(T));
	  event.tofdt[seg-1][m] = T;
	}// for(m)
      }

      if( Tu >0 && Td>0 ){
	event.tofhitpat[tof_nhits] = seg;
	tof_nhits++;
      }

      //Hitpat
      if( Tu>0 || Td>0 ){
	++nh1; HF1( TOFHid+3, seg-0.5 );
      }
      if( Tu>0 && Td>0 ){
	++nh2; HF1( TOFHid+5, seg-0.5 );
      }
    }
    HF1( TOFHid+2, double(nh1) ); HF1( TOFHid+4, double(nh2) );
    event.tofnhits = tof_nhits;
  }

  // HtTOF
  {
    int tofht_nhits = 0;
    const HodoRHitContainer &cont = rawData->GetHtTOFRawHC();
    int nh = cont.size();
    HF1( HtTOFHid, double(nh) );
    int nh1 = 0;
    for( int i=0; i<nh; ++i ){
      HodoRawHit *hit = cont[i];
      int seg = hit->SegmentId()+1;
      HF1( HtTOFHid+1, seg-0.5 );
      int Tm = hit->GetTdcUp();

      //Mt
      {
	int n_mhit = hit->GetSizeTdcUp();
	for(int m = 0; m<n_mhit; ++m){
	  int T = hit->GetTdcUp(m);
	  if(T > 0) HF1( HtTOFHid+100*seg+3, double(T) );
	  event.tofhtt[seg-1][m] = T;
	}// for(m)
      }

      //Hitpat
      if( Tm >0 ){
	event.tofhthitpat[tofht_nhits] = seg;
	tofht_nhits++;
      }
      if( Tm>0 ){
	++nh1; HF1( HtTOFHid+3, seg-0.5 );
      }
    }
    HF1( HtTOFHid+2, double(nh1) );
    event.tofhtnhits = tofht_nhits;
  }

  // LC
  {
    int lc_nhits = 0;
    const HodoRHitContainer &cont = rawData->GetLCRawHC();
    int nh = cont.size();
    HF1( LCHid, double(nh) );
    int nh1 = 0;
    for( int i=0; i<nh; ++i ){
      HodoRawHit *hit = cont[i];
      int seg = hit->SegmentId()+1;
      HF1( LCHid+1, seg-0.5 );
      int Tm = hit->GetTdcUp();

      //Mt
      {
	int n_mhit = hit->GetSizeTdcUp();
	for(int m = 0; m<n_mhit; ++m){
	  int T = hit->GetTdcUp(m);
	  if(T > 0) HF1( LCHid+100*seg+3, double(T) );
	  event.lct[seg-1][m] = T;
	}// for(m)
      }

      //Hitpat
      if( Tm >0 ){
	event.lchitpat[lc_nhits] = seg;
	lc_nhits++;
      }
      if( Tm>0 ){
	++nh1; HF1( LCHid+3, seg-0.5 );
      }
    }
    HF1( LCHid+2, double(nh1) );
    event.lcnhits = lc_nhits;
  }


  //**************************************************************************
  //****************** NormalizedData

  //BH1
  hodoAna->DecodeBH1Hits( rawData );
  //  hodoAna->TimeCutBH1(-10, 10);
  hodoAna->TimeCutBH1(-2, 2);
  {
    int nh = hodoAna->GetNHitsBH1();
    HF1( BH1Hid+10, double(nh) );
    int nh2 = 0;
    for( int i=0; i<nh; ++i ){
      Hodo2Hit *hit = hodoAna->GetHitBH1(i);
      if(!hit) continue;
      int seg = hit->SegmentId()+1;
      
      int n_mhit = hit->GetNumOfHit();
      for(int m = 0; m<n_mhit; ++m){
	HF1( BH1Hid+11, seg-0.5 );

	double au  = hit->GetAUp(),    ad = hit->GetADown();
	double tu  = hit->GetTUp(m),   td = hit->GetTDown(m);
	double ctu = hit->GetCTUp(m), ctd = hit->GetCTDown(m);
	double mt  = hit->MeanTime(m),cmt = hit->CMeanTime(m);
	double de  = hit->DeltaE();
	event.bh1mt[seg-1][m] = mt;
	event.bh1de[seg-1]    = de;
	HF1( BH1Hid+100*seg+11, tu );      HF1( BH1Hid+100*seg+12, td );
	HF1( BH1Hid+100*seg+13, mt );      
	HF1( BH1Hid+100*seg+17, ctu );     HF1( BH1Hid+100*seg+18, ctd );
	HF1( BH1Hid+100*seg+19, cmt );     HF1( BH1Hid+100*seg+20, ctu-ctd );
	HF2( BH1Hid+100*seg+21, tu, au );  HF2( BH1Hid+100*seg+22, td, ad );
	HF2( BH1Hid+100*seg+23, ctu, au ); HF2( BH1Hid+100*seg+24, ctd, ad );
	HF1( BH1Hid+12, cmt );
	
	if( m == 0){
	  HF1( BH1Hid+100*seg+14, au );    HF1( BH1Hid+100*seg+15, ad );
	  HF1( BH1Hid+100*seg+16, de );    HF1( BH1Hid+13, de );
	}

	if( de>0.5 ){
	  ++nh2; HF1( BH1Hid+15, seg-0.5 );
	  HF1( BH1Hid+16, cmt );
	}
      }
    }

    HF1( BH1Hid+14, double(nh2) );
    for( int i1=0; i1<nh; ++i1 ){
      Hodo2Hit *hit1 = hodoAna->GetHitBH1(i1);
      if( !hit1 || hit1->DeltaE()<=0.5 ) continue;
      int seg1 = hit1->SegmentId()+1;
      for( int i2=0; i2<nh; ++i2 ){
	if( i1==i2 ) continue;
	Hodo2Hit *hit2=hodoAna->GetHitBH1(i2);
	if( !hit2 || hit2->DeltaE()<=0.5 ) continue;
	int seg2 = hit2->SegmentId()+1;

	if( 1 == hit1->GetNumOfHit() && 1 == hit2->GetNumOfHit()){
	  double ct1 = hit1->CMeanTime(), ct2 = hit2->CMeanTime();
	  HF2( BH1Hid+21, seg1-0.5, seg2-0.5 );
	  HF2( BH1Hid+22, ct1, ct2 );
	  HF1( BH1Hid+23, ct2-ct1 );
	  if( std::abs(ct2-ct1)<2.0 ){
	    HF2( BH1Hid+24, seg1-0.5, seg2-0.5 );
	  }
	}
      }//for(i2)
    }//for(i1)
  }

  // BH2
  hodoAna->DecodeBH2Hits( rawData );
  hodoAna->TimeCutBH2(-2, 2);
  {
    int nh = hodoAna->GetNHitsBH2();
    HF1( BH2Hid+10, double(nh) );
    int nh2 = 0;
    for( int i=0; i<nh; ++i ){
      BH2Hit *hit = hodoAna->GetHitBH2(i);
      if(!hit) continue;
      int seg = hit->SegmentId()+1;

      int n_mhit = hit->GetNumOfHit();
      for(int m = 0; m<n_mhit; ++m){
	HF1( BH2Hid+11, seg-0.5 );
	double au  = hit->GetAUp(),   ad  = hit->GetADown();
	double tu  = hit->GetTUp(m),  td  = hit->GetTDown(m);
	double ctu = hit->GetCTUp(m), ctd = hit->GetCTDown(m);
	double mt  = hit->MeanTime(m),cmt = hit->CMeanTime(m);
	double de  = hit->DeltaE();
	double ut0  = hit->UTime0(m), dt0  = hit->DTime0(m);
	double uct0 = hit->UCTime0(m),dct0 = hit->DCTime0(m);
	double t0   = hit->Time0(m),  ct0  = hit->CTime0(m);
	event.bh2mt[seg-1][m] = mt;
	event.bh2de[seg-1]    = de;
	event.t0[seg-1][m]    = t0;
	event.ct0[seg-1][m]   = ct0;
	HF1( BH2Hid+100*seg+11, tu );      HF1( BH2Hid+100*seg+12, td );
	HF1( BH2Hid+100*seg+13, mt );      
	HF1( BH2Hid+100*seg+17, ctu );     HF1( BH2Hid+100*seg+18, ctd );
	HF1( BH2Hid+100*seg+19, cmt );     HF1( BH2Hid+100*seg+20, ctu-ctd );
	HF1( BH2Hid+100*seg+21, ut0 );     HF1( BH2Hid+100*seg+22, dt0 );
	HF1( BH2Hid+100*seg+23, uct0 );    HF1( BH2Hid+100*seg+24, dct0 );
	HF1( BH2Hid+100*seg+25, t0 );      HF1( BH2Hid+100*seg+26, ct0 );
	HF2( BH2Hid+100*seg+27, tu, au );  HF2( BH2Hid+100*seg+28, td, ad );
	HF2( BH2Hid+100*seg+29, ctu, au ); HF2( BH2Hid+100*seg+30, ctd, ad );

	// HF1( BH2Hid+100*seg+11, tu ); HF1( BH2Hid+100*seg+13, mt );
	// HF1( BH2Hid+100*seg+14, au ); HF1( BH2Hid+100*seg+16, de );
	// HF1( BH2Hid+100*seg+17, ctu ); HF1( BH2Hid+100*seg+19, cmt );
	// HF2( BH2Hid+100*seg+21, tu, au ); HF2( BH2Hid+100*seg+23, ctu, au );
	// HF1( BH2Hid+12, cmt );

	if( m == 0){
	  HF1( BH2Hid+100*seg+14, au );	   HF1( BH2Hid+100*seg+15, ad );
	  HF1( BH2Hid+100*seg+16, de );    HF1( BH2Hid+13, de );
	}

	if( de>0.5 ){
	  ++nh2; HF1( BH2Hid+15, seg-0.5 ); HF1( BH2Hid+16, cmt );
	}
      }
    }//for(i)
    HF1( BH2Hid+14, double(nh2) );
    for( int i1=0; i1<nh; ++i1 ){
      BH2Hit *hit1 = hodoAna->GetHitBH2(i1);
      if( !hit1 || hit1->DeltaE()<=0.5 ) continue;
      int seg1 = hit1->SegmentId()+1;
      for( int i2=0; i2<nh; ++i2 ){
	if( i1==i2 ) continue;
	BH2Hit *hit2 = hodoAna->GetHitBH2(i2);
	if( !hit2 || hit2->DeltaE()<=0.5 ) continue;
	int seg2 = hit2->SegmentId()+1;

	if( 1 == hit1->GetNumOfHit() && 1 == hit2->GetNumOfHit()){
	  double ct1 = hit1->CMeanTime(), ct2 = hit2->CMeanTime();
	  HF2( BH2Hid+21, seg1-0.5, seg2-0.5 );
	  HF2( BH2Hid+22, ct1, ct2 );
	  HF1( BH2Hid+23, ct2-ct1 );
	  if( std::abs(ct2-ct1)<2.0 ){
	    HF2( BH2Hid+24, seg1-0.5, seg2-0.5 );
	  }
	}
      }//for(i2)
    }//for(i1)

    int nc=hodoAna->GetNClustersBH2();
    HF1( BH2Hid+30, double(nc) );
    int nc2=0;

    for( int i=0; i<nc; ++i ){
      BH2Cluster *cluster=hodoAna->GetClusterBH2(i);
      if(!cluster) continue;
      int cs=cluster->ClusterSize();
      double ms = cluster->MeanSeg()+1;
      double cmt= cluster->CMeanTime();
      double de = cluster->DeltaE();
      double mt = cluster->MeanTime();
      HF1( BH2Hid+31, double(cs) );
      HF1( BH2Hid+32, ms-0.5 );
      HF1( BH2Hid+33, cmt ); HF1( BH2Hid+34, de );
      if( de>0.5 ){
	++nc2; HF1( BH2Hid+36, cmt );
      }

      for( int i2=0; i2<nc; ++i2 ){
	if( i2==i ) continue;
	BH2Cluster *cl2=hodoAna->GetClusterBH2(i2);
	if(!cl2) continue;
	double ms2=cl2->MeanSeg()+1, cmt2=cl2->CMeanTime(),
	  de2=cl2->DeltaE();
	if( de<=0.5 || de2<=0.5 ) continue;
	HF2( BH2Hid+41, ms-0.5, ms2-0.5 );
	HF2( BH2Hid+42, cmt, cmt2 );
	HF1( BH2Hid+43, cmt2-cmt );
	if( std::abs(cmt2-cmt)<2.0 ){
	  HF2( BH2Hid+44, ms-0.5, ms2-0.5 );
	}
      }//for(i2)
    }//for(i)
    HF1( BH2Hid+35, double(nc2) );
    
    BH2Cluster *cl_time0 = hodoAna->GetTime0BH2Cluster();
    if(cl_time0){
      event.Time0Seg = cl_time0->MeanSeg()+1;
      event.deTime0  = cl_time0->DeltaE();
      event.Time0    = cl_time0->Time0();
      event.CTime0   = cl_time0->CTime0();
    
      dst.Time0Seg = cl_time0->MeanSeg()+1;
      dst.deTime0  = cl_time0->DeltaE();
      dst.Time0    = cl_time0->Time0();
      dst.CTime0   = cl_time0->CTime0();
    }

    // BTOF0 segment
    HodoCluster *cl_btof0 = dst.Time0Seg > 0? hodoAna->GetBtof0BH1Cluster(dst.CTime0) : NULL;
    if(cl_btof0){
      event.Btof0Seg = cl_btof0->MeanSeg()+1;
      event.deBtof0  = cl_btof0->DeltaE();
      event.Btof0    = cl_btof0->MeanTime()  - dst.Time0;
      event.CBtof0   = cl_btof0->CMeanTime() - dst.CTime0;

      dst.Btof0Seg = cl_btof0->MeanSeg()+1;
      dst.deBtof0  = cl_btof0->DeltaE();
      dst.Btof0    = cl_btof0->MeanTime()  - dst.Time0;
      dst.CBtof0   = cl_btof0->CMeanTime() - dst.CTime0;
    }
  }

  // BH1 with BH2 gate
  {
    int nhbh2 = hodoAna->GetNHitsBH2();
    if( nhbh2 ){
      int    seg2 = hodoAna->GetHitBH2(0)->SegmentId()+1;
      int n_mhit2 = hodoAna->GetHitBH2(0)->GetNumOfHit();
      for(int m2 = 0; m2<n_mhit2; ++m2){
	double mt2  = hodoAna->GetHitBH2(0)->CTime0(m2);
	int    nh   = hodoAna->GetNHitsBH1();
	for( int i=0; i<nh; ++i ){
	  Hodo2Hit *hit = hodoAna->GetHitBH1(i);
	  if(!hit) continue;

	  int n_mhit1 = hit->GetNumOfHit();
	  for(int m1 = 0; m1<n_mhit1; ++m1){
	    int seg1 = hit->SegmentId()+1;
	    double tu1 = hit->GetTUp(m1), td1 = hit->GetTDown(m1);
	    double mt1 = hit->MeanTime(m1);
	    HF1( BH1Hid+100*seg1+1100+21+seg2*10, tu1 );
	    HF1( BH1Hid+100*seg1+1100+22+seg2*10, td1 );
	    HF1( BH1Hid+100*seg1+1100+23+seg2*10, mt1 );

	    //For BH1vsBH2 Correlation
	    HF2( BH1Hid+100*seg1+2200+21+seg2*10, tu1, mt2 );
	    HF2( BH1Hid+100*seg1+2200+22+seg2*10, td1, mt2 );
	    HF2( BH1Hid+100*seg1+2200+23+seg2*10, mt1, mt2 );
	  }// for(m1)
	}// for(bh1:seg)
      }// for(m2)
    }
    for( int i2=0; i2<nhbh2; ++i2 ){
      int    seg2 = hodoAna->GetHitBH2(i2)->SegmentId()+1;
      int n_mhit2 = hodoAna->GetHitBH2(0)->GetNumOfHit();
      for(int m2 = 0; m2<n_mhit2; ++m2){
	double ct0  = hodoAna->GetHitBH2(i2)->CTime0();
	double t0   = hodoAna->GetHitBH2(i2)->Time0();
	int nhbh1=hodoAna->GetNHitsBH1();
	for( int i1=0; i1<nhbh1; ++i1 ){
	  Hodo2Hit *hit=hodoAna->GetHitBH1(i1);
	  if(!hit) continue;

	  int n_mhit1 = hit->GetNumOfHit();
	  for(int m1 = 0; m1<n_mhit1; ++m1){
	    int seg1=hit->SegmentId()+1;
	    double  mt1  = hit->MeanTime(m1);
	    double cmt1  = hit->CMeanTime(m1);
	    double  btof =  mt1 -  t0;
	    double cbtof = cmt1 - ct0;
	    event.btof[seg1-1][seg2-1]  =  btof;
	    event.cbtof[seg1-1][seg2-1] = cbtof;
	    HF1( BH1Hid+100*seg1+1100+24+seg2*10, mt1-ct0 );
	    HF1( BH1Hid+100*seg1+2200+104, mt1-ct0 );

	    if(seg1==5){
	      HF1( 30+seg2, mt1-ct0);
	    }
	  }// for(m1)
	}// for(bh1:seg)
      }// for(m2)
    }// for(bh2:seg)
  }

  // BH1-BH2
  {
    int nhbh1 = hodoAna->GetNHitsBH1();
    int nhbh2 = hodoAna->GetNHitsBH2();
    for( int i2=0; i2<nhbh2; ++i2 ){
      BH2Hit *hit2 = hodoAna->GetHitBH2(i2);
      if( !hit2 ) continue;

      int n_mhit2 = hit2->GetNumOfHit();
      int    seg2 = hit2->SegmentId()+1;
      double de2  = hit2->DeltaE();
      for(int m2 = 0; m2<n_mhit2; ++m2){
	double t0      = hit2->Time0(m2);

	for(int i1=0; i1<nhbh1; ++i1 ){
	  Hodo2Hit *hit1 = hodoAna->GetHitBH1(i1);
	  if( !hit1 ) continue;

	  int n_mhit1  = hit1->GetNumOfHit();
	  int    seg1  = hit1->SegmentId()+1;
	  double de1   = hit1->DeltaE();

	  for(int m1 = 0; m1<n_mhit1; ++m1){
	    double mt1   = hit1->MeanTime(m1);
	    HF1( 201, mt1-t0 );
	    HF2( 202, seg1-0.5, seg2-0.5 );
	    //For BH1vsBH2 Correlation
	    HF2( 203, t0, mt1 );
	    HF1( 204, mt1 );
	    HF1( 205, t0 );

	    if( de1>0.5 && de2>0.5 ){
	      HF1( 211, mt1-t0 );
	      HF2( 212, seg1-0.5, seg2-0.5 );
	    }
	  }// for(m1)
	}// for(bh1:seg)
      }// for(m2)
    }// for(bh2:seg)
  }

#if 1
  // BH1-BH2 PHC
  {
    int nh1 = hodoAna->GetNHitsBH1();
    int nh2 = hodoAna->GetNHitsBH2();
    for( int i2=0; i2<nh2; ++i2 ){
      BH2Hit *hit2 = hodoAna->GetHitBH2(i2);
      int     seg2 = hit2->SegmentId()+1;
      double  au2  = hit2->GetAUp(),  ad2  = hit2->GetADown();

      int n_mhit2  = hit2->GetNumOfHit();
      for(int m2 = 0; m2<n_mhit2; ++m2){
	double  tu2  = hit2->GetTUp(m2),  td2  = hit2->GetTDown(m2);
	double  ctu2 = hit2->GetCTUp(m2), ctd2 = hit2->GetCTDown(m2);
	// double  t0   = hit2->Time0();
	double  ct0  = hit2->CTime0(m2);
	double  tofs = ct0-(ctu2+ctd2)/2.;
	for( int i1=0; i1<nh1; ++i1 ){
	  Hodo2Hit *hit1 = hodoAna->GetHitBH1(i1);
	  int       seg1 = hit1->SegmentId()+1;
	  double    au1  = hit1->GetAUp(),  ad1  = hit1->GetADown();

	  int    n_mhit1 = hit1->GetNumOfHit();
	  for(int m1 = 0; m1<n_mhit1; ++m1){
	    double    tu1  = hit1->GetTUp(m1),  td1  = hit1->GetTDown(m1);
	    double    ctu1 = hit1->GetCTUp(m1), ctd1 = hit1->GetCTDown(m1);
	    double    cmt1 = hit1->CMeanTime(m1);
	    // if( event.trigflag[kKBeam]<=0 ) continue;
	    // if( event.trigflag[kKIn]<=0 ) continue;
	    HF2( 100*seg1+BH1Hid+81, au1, 2.*ct0-ctu1-ctd1 );
	    HF2( 100*seg1+BH1Hid+82, ad1, 2.*ct0-ctu1-ctd1 );
	    HF2( 100*seg1+BH1Hid+83, au1, ct0-tu1 );
	    HF2( 100*seg1+BH1Hid+84, ad1, ct0-td1 );
	    HF2( 100*seg2+BH2Hid+81, au2, 2.*(cmt1-tofs)-ctu2-ctd2 );
	    HF2( 100*seg2+BH2Hid+82, ad2, 2.*(cmt1-tofs)-ctu2-ctd2 );
	    HF2( 100*seg2+BH2Hid+83, au2, (cmt1-tofs)-tu2 );
	    HF2( 100*seg2+BH2Hid+84, ad2, (cmt1-tofs)-td2 );
	  }// for(m1)
	}// for(bh1:seg)
      }// for(m2)
    }// for(bh2:seg)
  }
#endif

  // SAC
  {
    hodoAna->DecodeSACHits( rawData );
    int nh=hodoAna->GetNHitsSAC();
    dst.nhSac = nh;
    HF1( SACHid+10, double(nh) );
    for( int i=0; i<nh; ++i ){
      Hodo1Hit *hit=hodoAna->GetHitSAC(i);
      if(!hit) continue;
      int seg=hit->SegmentId()+1;
      HF1( SACHid+11, seg-0.5 );
      double a=hit->GetA();
      event.sacde[seg-1]  = a;

      int n_mhit = hit->GetNumOfHit();
      for(int m = 0; m<n_mhit; ++m){
	double t=hit->GetT(m), ct=hit->GetCT(m);
	event.sacmt[i][m] = ct;
	HF1( SACHid+100*seg+11, t);
	HF1( SACHid+100*seg+12, a);
	HF1( SACHid+100*seg+13, ct);
      }
    }
  }

  // TOF
  hodoAna->DecodeTOFHits( rawData );
  {
    int nh = hodoAna->GetNHitsTOF();
    HF1( TOFHid+10, double(nh) );
    int nh2 = 0;
    for( int i=0; i<nh; ++i ){
      Hodo2Hit *hit = hodoAna->GetHitTOF(i);
      if(!hit) continue;
      int seg = hit->SegmentId()+1;
      
      int n_mhit = hit->GetNumOfHit();
      for(int m = 0; m<n_mhit; ++m){
	HF1( TOFHid+11, seg-0.5 );

	double au  = hit->GetAUp(),   ad  = hit->GetADown();
	double tu  = hit->GetTUp(),   td  = hit->GetTDown();
	double ctu = hit->GetCTUp(),  ctd = hit->GetCTDown();
	double mt  = hit->MeanTime(), cmt = hit->CMeanTime();
	double de  = hit->DeltaE();
	event.tofmt[seg-1][m] = mt;
	event.tofde[seg-1]    = de;
	HF1( TOFHid+100*seg+11, tu );      HF1( TOFHid+100*seg+12, td );
	HF1( TOFHid+100*seg+13, mt );      
	HF1( TOFHid+100*seg+17, ctu );     HF1( TOFHid+100*seg+18, ctd );
	HF1( TOFHid+100*seg+19, cmt );     HF1( TOFHid+100*seg+20, ctu-ctd );
	HF2( TOFHid+100*seg+21, tu, au );  HF2( TOFHid+100*seg+22, td, ad );
	HF2( TOFHid+100*seg+23, ctu, au ); HF2( TOFHid+100*seg+24, ctd, ad );
	HF1( TOFHid+12, cmt );             

	dst.utTofSeg[seg-1][m]  = tu; dst.dtTofSeg[seg-1][m]  = td;
	dst.udeTofSeg[seg-1]    = au; dst.ddeTofSeg[seg-1]    = ad;

	if( m == 0){
	  HF1( TOFHid+100*seg+14, au );    HF1( TOFHid+100*seg+15, ad );
	  HF1( TOFHid+100*seg+16, de );    HF1( TOFHid+13, de );
	}

	if( de>0.5 ){
	  HF1( TOFHid+15, seg-0.5 );
	  ++nh2;	  
	}
      }
    }

    HF1( TOFHid+14, double(nh2) );
    for( int i1=0; i1<nh; ++i1 ){
      Hodo2Hit *hit1 = hodoAna->GetHitTOF(i1);
      if( !hit1 || hit1->DeltaE()<=0.5 ) continue;
      int seg1 = hit1->SegmentId()+1;
      for( int i2=0; i2<nh; ++i2 ){
	if( i1==i2 ) continue;
	Hodo2Hit *hit2 = hodoAna->GetHitTOF(i2);
	if( !hit2 || hit2->DeltaE()<=0.5 ) continue;
	int seg2 = hit2->SegmentId()+1;
	
	if( 1 == hit1->GetNumOfHit() && 1 == hit2->GetNumOfHit()){
	  double ct1 = hit1->CMeanTime(), ct2 = hit2->CMeanTime();
	  HF2( TOFHid+21, seg1-0.5, seg2-0.5 );
	  HF2( TOFHid+22, ct1, ct2 );
	  HF1( TOFHid+23, ct2-ct1 );
	  if( std::abs(ct2-ct1)<3.0 ){
	    HF2( TOFHid+24, seg1-0.5, seg2-0.5 );
	  }
	}//for(i2)
      }//for(i1)
    }

    int nc = hodoAna->GetNClustersTOF();
    HF1( TOFHid+30, double(nc) );
    for( int i=0; i<nc; ++i ){
      HodoCluster *cluster = hodoAna->GetClusterTOF(i);
      if(!cluster) continue;
      int cs = cluster->ClusterSize();
      double ms  = cluster->MeanSeg()+1;
      double cmt = cluster->CMeanTime();
      double de  = cluster->DeltaE();
      HF1( TOFHid+31, double(cs) );
      HF1( TOFHid+32, ms-0.5 );
      HF1( TOFHid+33, cmt ); HF1( TOFHid+34, de );
    }
  }

  // TOF-HT
  hodoAna->DecodeHtTOFHits( rawData );
  {
    int nh = hodoAna->GetNHitsHtTOF();
    HF1( HtTOFHid+10, double(nh) );
    int nh2 = 0;
    for( int i=0; i<nh; ++i ){
      Hodo1Hit *hit = hodoAna->GetHitHtTOF(i);
      if(!hit) continue;
      int seg = hit->SegmentId()+1;
      HF1( HtTOFHid+11, seg-0.5 );

      int n_mhit = hit->GetNumOfHit();
      for(int m = 0; m<n_mhit; ++m){
	double mt  = hit->MeanTime(m), cmt = hit->CMeanTime(m);
	event.tofhtmt[seg-1][m]  = mt;

	HF1( HtTOFHid+100*seg+13, mt );
	HF1( HtTOFHid+100*seg+19, cmt );
	HF1( HtTOFHid+12, cmt );
      }// for(m)

      HF1( HtTOFHid+14, double(nh2) );
    }

    for( int i1=0; i1<nh; ++i1 ){
      Hodo1Hit *hit1 = hodoAna->GetHitHtTOF(i1);
      if( !hit1 ) continue;
      int seg1 = hit1->SegmentId()+1;

      int n_mhit1 = hit1->GetNumOfHit();
      for(int m1 = 0; m1<n_mhit1; ++m1){
	for( int i2=0; i2<nh; ++i2 ){
	  if( i1==i2 ) continue;
	  Hodo1Hit *hit2 = hodoAna->GetHitHtTOF(i2);
	  if( !hit2 ) continue;

	  int seg2 = hit2->SegmentId()+1;
	  int n_mhit2 = hit2->GetNumOfHit();
	  for(int m2 = 0; m2<n_mhit2; ++m2){
	    double ct1 = hit1->CMeanTime(m1), ct2 = hit2->CMeanTime(m2);
	    HF2( HtTOFHid+21, seg1-0.5, seg2-0.5 );
	    HF2( HtTOFHid+22, ct1, ct2 );
	    HF1( HtTOFHid+23, ct2-ct1 );
	    if( std::abs(ct2-ct1)<3.0 ){
	      HF2( HtTOFHid+24, seg1-0.5, seg2-0.5 );
	    }
	  }// for(m2)
	}// for(seg2)
      }// for(m1)
    }// for(seg1)

    int nc = hodoAna->GetNClustersHtTOF();
    HF1( HtTOFHid+30, double(nc) );
    for( int i=0; i<nc; ++i ){
      HodoCluster *cluster = hodoAna->GetClusterHtTOF(i);
      if(!cluster) continue;
      int cs = cluster->ClusterSize();
      double ms  = cluster->MeanSeg()+1;
      double cmt = cluster->CMeanTime();
      HF1( HtTOFHid+31, double(cs) );
      HF1( HtTOFHid+32, ms-0.5 );
      HF1( HtTOFHid+33, cmt );
    }
  }

  // LC
  hodoAna->DecodeLCHits( rawData );
  {
    int nh = hodoAna->GetNHitsLC();
    HF1( LCHid+10, double(nh) );
    int nh2 = 0;
    for( int i=0; i<nh; ++i ){
      Hodo1Hit *hit = hodoAna->GetHitLC(i);
      if(!hit) continue;
      int seg = hit->SegmentId()+1;
      HF1( LCHid+11, seg-0.5 );

      int n_mhit = hit->GetNumOfHit();
      for(int m = 0; m<n_mhit; ++m){
	double mt  = hit->MeanTime(m), cmt = hit->CMeanTime(m);
	event.lcmt[seg-1][m]  = mt;

	HF1( LCHid+100*seg+13, mt );
	HF1( LCHid+100*seg+19, cmt );
	HF1( LCHid+12, cmt );
      }// for(m)

      HF1( LCHid+14, double(nh2) );
    }

    for( int i1=0; i1<nh; ++i1 ){
      Hodo1Hit *hit1 = hodoAna->GetHitLC(i1);
      if( !hit1 ) continue;
      int seg1 = hit1->SegmentId()+1;

      int n_mhit1 = hit1->GetNumOfHit();
      for(int m1 = 0; m1<n_mhit1; ++m1){
	for( int i2=0; i2<nh; ++i2 ){
	  if( i1==i2 ) continue;
	  Hodo1Hit *hit2 = hodoAna->GetHitLC(i2);
	  if( !hit2 ) continue;

	  int seg2 = hit2->SegmentId()+1;
	  int n_mhit2 = hit2->GetNumOfHit();
	  for(int m2 = 0; m2<n_mhit2; ++m2){
	    double ct1 = hit1->CMeanTime(m1), ct2 = hit2->CMeanTime(m2);
	    HF2( LCHid+21, seg1-0.5, seg2-0.5 );
	    HF2( LCHid+22, ct1, ct2 );
	    HF1( LCHid+23, ct2-ct1 );
	    if( std::abs(ct2-ct1)<3.0 ){
	      HF2( LCHid+24, seg1-0.5, seg2-0.5 );
	    }
	  }// for(m2)
	}// for(seg2)
      }// for(m1)
    }// for(seg1)

    int nc = hodoAna->GetNClustersLC();
    HF1( LCHid+30, double(nc) );
    for( int i=0; i<nc; ++i ){
      HodoCluster *cluster = hodoAna->GetClusterLC(i);
      if(!cluster) continue;
      int cs = cluster->ClusterSize();
      double ms  = cluster->MeanSeg()+1;
      double cmt = cluster->CMeanTime();
      HF1( LCHid+31, double(cs) );
      HF1( LCHid+32, ms-0.5 );
      HF1( LCHid+33, cmt );
    }
  }

  ////////// Dst
  {
    int nc = hodoAna->GetNClustersBH1();
    dst.nhBh1 = nc;
    for( int i=0; i<nc; ++i ){
      HodoCluster *cl = hodoAna->GetClusterBH1(i);
      if( !cl ) continue;
      dst.csBh1[i]  = cl->ClusterSize();
      dst.Bh1Seg[i] = cl->MeanSeg()+1;
      dst.tBh1[i]   = cl->CMeanTime();
      dst.dtBh1[i]  = cl->TimeDif();
      dst.deBh1[i]  = cl->DeltaE();

      int nc2 = hodoAna->GetNClustersBH2();
      for( int i2=0; i2<nc2; ++i2 ){
	BH2Cluster *cl2 = hodoAna->GetClusterBH2(i2);
	if( !cl2 ) continue;
	double btof  = cl->MeanTime()  - dst.Time0;
	double cbtof = cl->CMeanTime() - dst.CTime0;

	dst.btof[i]  = btof;
	dst.cbtof[i] = cbtof;
      }
    }
  }
  
  {
    int nc = hodoAna->GetNClustersBH2();
    dst.nhBh2 = nc;
    for( int i=0; i<nc; ++i ){
      BH2Cluster *cl = hodoAna->GetClusterBH2(i);
      if( !cl ) continue;
      dst.csBh2[i]  = cl->ClusterSize();
      dst.Bh2Seg[i] = cl->MeanSeg()+1;
      dst.tBh2[i]   = cl->CMeanTime();
      dst.t0Bh2[i]  = cl->CTime0();
      dst.dtBh2[i]  = cl->TimeDif();
      dst.deBh2[i]  = cl->DeltaE();
    }
  }

  {
    int nc = hodoAna->GetNClustersSAC();
    dst.nhSac = nc;
    for( int i=0; i<nc; ++i ){
      HodoCluster *cl = hodoAna->GetClusterSAC(i);
      if( !cl ) continue;
      dst.csSac[i]  = cl->ClusterSize();
      dst.SacSeg[i] = cl->MeanSeg()+1;
      dst.tSac[i]   = cl->CMeanTime();
      dst.deSac[i]  = cl->DeltaE();
    }
  }

  {
    int nc = hodoAna->GetNClustersTOF();
    dst.nhTof = nc;
    for( int i=0; i<nc; ++i ){
      HodoCluster *cl = hodoAna->GetClusterTOF(i);
      if( !cl ) continue;
      dst.csTof[i]  = cl->ClusterSize();
      dst.TofSeg[i] = cl->MeanSeg()+1;
      dst.tTof[i]   = cl->CMeanTime();
      dst.dtTof[i]  = cl->TimeDif();
      dst.deTof[i]  = cl->DeltaE();
    }
  }

  {
    int nc = hodoAna->GetNClustersHtTOF();
    dst.nhHtTof = nc;
    for( int i=0; i<nc; ++i ){
      HodoCluster *cl = hodoAna->GetClusterHtTOF(i);
      if( !cl ) continue;
      dst.csHtTof[i]  = cl->ClusterSize();
      dst.HtTofSeg[i] = cl->MeanSeg()+1;
      dst.tHtTof[i]   = cl->CMeanTime();
    }
  }

  {
    int nc = hodoAna->GetNClustersLC();
    dst.nhLc = nc;
    for( int i=0; i<nc; ++i ){
      HodoCluster *cl = hodoAna->GetClusterLC(i);
      if( !cl ) continue;
      dst.csLc[i]  = cl->ClusterSize();
      dst.LcSeg[i] = cl->MeanSeg()+1;
      dst.tLc[i]   = cl->CMeanTime();
    }
  }

#if 0
  // BH1 (for parameter tuning)
  if(dst.Time0Seg==4){
    const HodoRHitContainer &cont = rawData->GetBH1RawHC();
    int nh = cont.size();
    for( int i=0; i<nh; ++i ){
      HodoRawHit *hit = cont[i];
      int seg = hit->SegmentId()+1;

      //Up
      {
	int n_mhit = hit->GetSizeTdcUp();
	for(int m = 0; m<n_mhit; ++m){
	  int T = hit->GetTdcUp(m);
	  if(T > 0) HF1( BH1Hid +100*seg +9, double(T) );
	}// for(m)
      }

      //Down
      {
	int n_mhit = hit->GetSizeTdcDown();
	for(int m = 0; m<n_mhit; ++m){
	  int T = hit->GetTdcDown(m);
	  if(T > 0) HF1( BH1Hid +100*seg +10, double(T) );
	}// for(m)
      }
    }
  }// (Raw BH1 TDC for parameter tuning)
#endif

  return true;
}

//______________________________________________________________________________
bool
EventHodoscope::ProcessingEnd( void )
{
  tree->Fill();
  hodo->Fill();
  return true;
}

//______________________________________________________________________________
void
EventHodoscope::InitializeEvent( void )
{
  event.evnum     = 0;
  event.spill     = 0;
  event.trignhits = 0;
  event.bh1nhits  = 0;
  event.bh2nhits  = 0;
  event.fpga_bh2mtnhits  = 0;
  event.sacnhits  = 0;
  event.tofnhits  = 0;
  event.tofhtnhits  = 0;
  event.lcnhits  = 0;

  dst.nhBh1  = 0;
  dst.nhBh2  = 0;
  dst.nhSac  = 0;
  dst.nhTof  = 0;
  dst.nhHtTof  = 0;
  dst.nhLc  = 0;

  event.Time0Seg = -999;
  event.deTime0  = -999;
  event.Time0    = -999;
  event.CTime0   = -999;

  event.Btof0Seg = -999;
  event.deBtof0  = -999;
  event.Btof0    = -999;
  event.CBtof0   = -999;

  dst.evnum     = 0;
  dst.spill     = 0;

  dst.Time0Seg = -999;
  dst.deTime0  = -999;
  dst.Time0    = -999;
  dst.CTime0   = -999;

  dst.Btof0Seg = -999;
  dst.deBtof0  = -999;
  dst.Btof0    = -999;
  dst.CBtof0   = -999;

  for( int it=0; it<NumOfSegTrig; ++it ){
    event.trigpat[it]  = -1;
    event.trigflag[it] = -1;

    dst.trigpat[it]  = -1;
    dst.trigflag[it] = -1;
  }

  for( int it=0; it<MaxHits; ++it ){
    event.bh1hitpat[it]  = -1;
    event.bh2hitpat[it]  = -1;
    event.fpga_bh2mthitpat[it]  = -1;
    event.sachitpat[it]  = -1;
    event.tofhitpat[it]  = -1;
    event.tofhthitpat[it]  = -1;
    event.lchitpat[it]  = -1;
  }

  for( int it=0; it<NumOfSegBH1; ++it ){
    event.bh1ua[it] = -9999.;
    event.bh1da[it] = -9999.;
    event.bh1de[it] = -9999.;


    for( int that=0; that<NumOfSegBH2; ++that ){
      event.btof[it][that]  = -9999.;
      event.cbtof[it][that] = -9999.;
    }

    for(int m = 0; m<MaxDepth; ++m){
      event.bh1ut[it][m] = -9999.;
      event.bh1dt[it][m] = -9999.;
      event.bh1mt[it][m] = -9999.;

      dst.csBh1[MaxDepth*it + m]  = 0;
      dst.Bh1Seg[MaxDepth*it + m] = -1.;
      dst.tBh1[MaxDepth*it + m]   = -9999.;
      dst.dtBh1[MaxDepth*it + m]  = -9999.;
      dst.deBh1[MaxDepth*it + m]  = -9999.;
      dst.btof[MaxDepth*it + m]   = -9999.;
      dst.cbtof[MaxDepth*it + m]  = -9999.;

    }
  }

  for( int it=0; it<NumOfSegBH2; ++it ){
    event.bh2ua[it] = -9999.;
    event.bh2da[it] = -9999.;
    event.bh2de[it] = -9999.;


    for(int m = 0; m<MaxDepth; ++m){
      event.bh2ut[it][m] = -9999.;
      event.bh2dt[it][m] = -9999.;
      event.bh2mt[it][m] = -9999.;

      event.t0[it][m]    = -9999.;
      event.ct0[it][m]   = -9999.;

      dst.csBh2[MaxDepth*it + m]  = 0;
      dst.Bh2Seg[MaxDepth*it + m] = -1.;
      dst.tBh2[MaxDepth*it + m]   = -9999.;
      dst.t0Bh2[MaxDepth*it + m]  = -9999.;
      dst.dtBh2[MaxDepth*it + m]  = -9999.;
      dst.deBh2[MaxDepth*it + m]  = -9999.;
    }
  }

  for( int it=0; it<NumOfSegSAC; it++){
    event.saca[it] = -9999.;
    dst.SacSeg[it] = -9999.;
    dst.deSac[it]  = -9999.;

    for(int m = 0; m<MaxDepth; ++m){
      event.sact[it][m] = -9999.;
      dst.tSac[MaxDepth*it+m]   = -9999.;
    }
  }

  for( int it=0; it<NumOfSegTOF; it++){
    event.tofua[it] = -9999.;
    event.tofda[it] = -9999.;
    event.tofde[it]  = -999.0;

    dst.udeTofSeg[it] = -9999.;
    dst.ddeTofSeg[it] = -9999.;

    for(int m = 0; m<MaxDepth; ++m){
      event.tofut[it][m] = -9999.;
      event.tofdt[it][m] = -9999.;
      event.tofmt[it][m] = -999.0;

      dst.utTofSeg[it][m]  = -9999.;
      dst.dtTofSeg[it][m]  = -9999.;

      dst.csTof[MaxDepth*it + m]  = 0;
      dst.TofSeg[MaxDepth*it + m] = -1;
      dst.tTof[MaxDepth*it + m]   = -9999.;
      dst.dtTof[MaxDepth*it + m]  = -9999.;
      dst.deTof[MaxDepth*it + m]  = -9999.;      
    }
  }

  for( int it=0; it<NumOfSegTOF; it++){
    for(int m = 0; m<MaxDepth; ++m){
      event.tofhtt[it][m] = -9999;
      event.tofhtmt[it][m] = -9999;

      dst.csHtTof[MaxDepth*it + m]  = 0;
      dst.HtTofSeg[MaxDepth*it + m] = -1;
      dst.tHtTof[MaxDepth*it + m]   = -9999;
    }
  }

  for( int it=0; it<NumOfSegLC; it++){

    for(int m = 0; m<MaxDepth; ++m){
      event.lct[it][m]   = -9999.;
      event.lcmt[it][m]  = -999.0;

      dst.csLc[MaxDepth*it + m]  = 0;
      dst.LcSeg[MaxDepth*it + m] = -1;
      dst.tLc[MaxDepth*it + m]   = -9999.;
    }
  }
}

//______________________________________________________________________________
VEvent*
ConfMan::EventAllocator( void )
{
  return new EventHodoscope;
}

//______________________________________________________________________________
namespace
{
  const int    NbinAdc = 4096;
  const double MinAdc  =    0.;
  const double MaxAdc  = 4096.;

  const int    NbinTdc = 4096;
  const double MinTdc  =    0.;
  const double MaxTdc  = 4096.;

  const int    NbinTdcHr = 4e5/20;
  const double MinTdcHr  =  0.;
  const double MaxTdcHr  = 4e5;
}

//______________________________________________________________________________
bool
ConfMan::InitializeHistograms( void )
{
  HB1(  1, "Status", 20, 0., 20. );
  HB1( 10, "Trigger HitPat", NumOfSegTrig, 0., double(NumOfSegTrig) );
  for(int i=0; i<NumOfSegTrig; ++i){
    HB1( 10+i+1, Form("Trigger Trig %d", i+1), 0x1000, 0, 0x1000 );
  }

  // BH1
  // Rawdata
  HB1( BH1Hid +0, "#Hits BH1",        NumOfSegBH1+1, 0., double(NumOfSegBH1+1) );
  HB1( BH1Hid +1, "Hitpat BH1",       NumOfSegBH1,   0., double(NumOfSegBH1)   );
  HB1( BH1Hid +2, "#Hits BH1(Tor)",   NumOfSegBH1+1, 0., double(NumOfSegBH1+1) );
  HB1( BH1Hid +3, "Hitpat BH1(Tor)",  NumOfSegBH1,   0., double(NumOfSegBH1)   );
  HB1( BH1Hid +4, "#Hits BH1(Tand)",  NumOfSegBH1+1, 0., double(NumOfSegBH1+1) );
  HB1( BH1Hid +5, "Hitpat BH1(Tand)", NumOfSegBH1,   0., double(NumOfSegBH1)   );

  for( int i=1; i<=NumOfSegBH1; ++i ){
    TString title1 = Form("BH1-%d UpAdc", i);
    TString title2 = Form("BH1-%d DownAdc", i);
    TString title3 = Form("BH1-%d UpTdc", i);
    TString title4 = Form("BH1-%d DownTdc", i);
    TString title5 = Form("BH1-%d UpAdc(w Tdc)", i);
    TString title6 = Form("BH1-%d DownAdc(w Tdc)", i);
    TString title7 = Form("BH1-%d UpAdc(w/o Tdc)", i);
    TString title8 = Form("BH1-%d DownAdc(w/o Tdc)", i);
    TString title9 = Form("BH1-%d UpTdc (Time0Seg==4)", i);
    TString title10= Form("BH1-%d DownTdc (Time0Seg==4)", i);
    HB1( BH1Hid +100*i +1, title1, NbinAdc,   MinAdc,   MaxAdc );
    HB1( BH1Hid +100*i +2, title2, NbinAdc,   MinAdc,   MaxAdc );
    HB1( BH1Hid +100*i +3, title3, NbinTdcHr, MinTdcHr, MaxTdcHr );
    HB1( BH1Hid +100*i +4, title4, NbinTdcHr, MinTdcHr, MaxTdcHr );
    HB1( BH1Hid +100*i +5, title5, NbinAdc,   MinAdc,   MaxAdc );
    HB1( BH1Hid +100*i +6, title6, NbinAdc,   MinAdc,   MaxAdc );
    HB1( BH1Hid +100*i +7, title7, NbinAdc,   MinAdc,   MaxAdc );
    HB1( BH1Hid +100*i +8, title8, NbinAdc,   MinAdc,   MaxAdc );
    HB1( BH1Hid +100*i +9, title9, NbinTdcHr, MinTdcHr, MaxTdcHr );
    HB1( BH1Hid +100*i +10,title10,NbinTdcHr, MinTdcHr, MaxTdcHr );
  }

  //BH1 Normalized
  HB1( BH1Hid +10, "#Hits BH1[Hodo]",  NumOfSegBH1+1, 0., double(NumOfSegBH1+1) );
  HB1( BH1Hid +11, "Hitpat BH1[Hodo]", NumOfSegBH1,   0., double(NumOfSegBH1)   );
  HB1( BH1Hid +12, "CMeanTime BH1", 200, -10., 10. );
  HB1( BH1Hid +13, "dE BH1", 200, -0.5, 4.5 );
  HB1( BH1Hid +14, "#Hits BH1[HodoGood]",  NumOfSegBH1+1, 0., double(NumOfSegBH1+1) );
  HB1( BH1Hid +15, "Hitpat BH1[HodoGood]", NumOfSegBH1,   0., double(NumOfSegBH1)   );
  HB1( BH1Hid +16, "CMeanTime BH1[HodoGood]", 200, -10., 10. );

  for( int i=1; i<=NumOfSegBH1; ++i ){
    TString title11 = Form("BH1-%d Up Time", i);
    TString title12 = Form("BH1-%d Down Time", i);
    TString title13 = Form("BH1-%d MeanTime", i);
    TString title14 = Form("BH1-%d Up dE", i);
    TString title15 = Form("BH1-%d Down dE", i);
    TString title16 = Form("BH1-%d dE", i);
    TString title17 = Form("BH1-%d Up CTime", i);
    TString title18 = Form("BH1-%d Down CTime", i);
    TString title19 = Form("BH1-%d CMeanTime", i);
    TString title20 = Form("BH1-%d Tup-Tdown", i);
    TString title21 = Form("BH1-%d Up dE%%Time", i);
    TString title22 = Form("BH1-%d Down dE%%Time", i);
    TString title23 = Form("BH1-%d Up dE%%CTime", i);
    TString title24 = Form("BH1-%d Down dE%%CTime", i);
    HB1( BH1Hid +100*i +11, title11, 200, -10., 10. );
    HB1( BH1Hid +100*i +12, title12, 200, -10., 10. );
    HB1( BH1Hid +100*i +13, title13, 200, -10., 10. );
    HB1( BH1Hid +100*i +14, title14, 200, -0.5, 4.5 );
    HB1( BH1Hid +100*i +15, title15, 200, -0.5, 4.5 );
    HB1( BH1Hid +100*i +16, title16, 200, -0.5, 4.5 );
    HB1( BH1Hid +100*i +17, title17, 200, -10., 10. );
    HB1( BH1Hid +100*i +18, title18, 200, -10., 10. );
    HB1( BH1Hid +100*i +19, title19, 200, -10., 10. );
    HB1( BH1Hid +100*i +20, title20, 200, -5.0, 5.0 );
    HB2( BH1Hid +100*i +21, title21, 100, -10., 10., 100, -0.5, 4.5 );
    HB2( BH1Hid +100*i +22, title22, 100, -10., 10., 100, -0.5, 4.5 );
    HB2( BH1Hid +100*i +23, title23, 100, -10., 10., 100, -0.5, 4.5 );
    HB2( BH1Hid +100*i +24, title24, 100, -10., 10., 100, -0.5, 4.5 );

    //For BH1vsBH2 Correlation
    HB2( BH1Hid +100*i +2200 +21, Form("BH1-%d BH2 Up MT%%MT", i),
	 100, -10., 10., 100, -10., 10. );
    HB2( BH1Hid +100*i +2200 +22, Form("BH1-%d BH2 Down MT%%MT", i),
	 100, -10., 10., 100, -10., 10. );
    HB2( BH1Hid +100*i +2200 +23, Form("BH1-%d BH2 MeanTime MT%%MT", i),
	 100, -10., 10., 100, -10., 10. );
  }
  for( int i=1; i<=NumOfSegBH1; ++i ){
    TString title1 = Form("BH1-%d Up Time [BH2]", i);
    HB1( BH1Hid +1100 +100*i +31, title1, 200, -10., 10. );
    HB1( BH1Hid +1100 +100*i +41, title1, 200, -10., 10. );
    HB1( BH1Hid +1100 +100*i +51, title1, 200, -10., 10. );
    HB1( BH1Hid +1100 +100*i +61, title1, 200, -10., 10. );
    HB1( BH1Hid +1100 +100*i +71, title1, 200, -10., 10. );
    HB1( BH1Hid +1100 +100*i +81, title1, 200, -10., 10. );
    HB1( BH1Hid +1100 +100*i +91, title1, 200, -10., 10. );
    TString title2 = Form("BH1-%d Down Time [BH2]", i);
    HB1( BH1Hid +1100 +100*i +32, title2, 200, -10., 10. );
    HB1( BH1Hid +1100 +100*i +42, title2, 200, -10., 10. );
    HB1( BH1Hid +1100 +100*i +52, title2, 200, -10., 10. );
    HB1( BH1Hid +1100 +100*i +62, title2, 200, -10., 10. );
    HB1( BH1Hid +1100 +100*i +72, title2, 200, -10., 10. );
    HB1( BH1Hid +1100 +100*i +82, title2, 200, -10., 10. );
    HB1( BH1Hid +1100 +100*i +92, title2, 200, -10., 10. );
    TString title3 = Form("BH1-%d MeanTime [BH2]", i);
    HB1( BH1Hid +1100 +100*i +33, title3, 200, -10., 10. );
    HB1( BH1Hid +1100 +100*i +43, title3, 200, -10., 10. );
    HB1( BH1Hid +1100 +100*i +53, title3, 200, -10., 10. );
    HB1( BH1Hid +1100 +100*i +63, title3, 200, -10., 10. );
    HB1( BH1Hid +1100 +100*i +73, title3, 200, -10., 10. );
    HB1( BH1Hid +1100 +100*i +83, title3, 200, -10., 10. );
    HB1( BH1Hid +1100 +100*i +93, title3, 200, -10., 10. );
    HB1( BH1Hid +1100 +100*i +103, title3, 200, -10., 10. );
    TString title4 = Form("BH1-%d MeanTime-BH2MeamTime", i);
    HB1( BH1Hid +1100 +100*i +34, title4, 200, -10., 10. );
    HB1( BH1Hid +1100 +100*i +44, title4, 200, -10., 10. );
    HB1( BH1Hid +1100 +100*i +54, title4, 200, -10., 10. );
    HB1( BH1Hid +1100 +100*i +64, title4, 200, -10., 10. );
    HB1( BH1Hid +1100 +100*i +74, title4, 200, -10., 10. );
    HB1( BH1Hid +1100 +100*i +84, title4, 200, -10., 10. );
    HB1( BH1Hid +1100 +100*i +94, title4, 200, -10., 10. );
    HB1( BH1Hid +1100 +100*i +104, title4, 200, -10., 10. );
    HB1( BH1Hid +100*i +2200 +114, title4, 200, -10., 10. );
  }

  HB2( BH1Hid +21, "BH1HitPat%BH1HitPat[HodoGood]", NumOfSegBH1,   0., double(NumOfSegBH1),
       NumOfSegBH1,   0., double(NumOfSegBH1) );
  HB2( BH1Hid +22, "CMeanTimeBH1%CMeanTimeBH1[HodoGood]",
       100, -5., 5., 100, -5., 5. );
  HB1( BH1Hid +23, "TDiff BH1[HodoGood]", 200, -10., 10. );
  HB2( BH1Hid +24, "BH1HitPat%BH1HitPat[HodoGood2]", NumOfSegBH1,   0., double(NumOfSegBH1),
       NumOfSegBH1,   0., double(NumOfSegBH1) );
  HB1( BH1Hid +30, "#Clusters BH1", NumOfSegBH1+1, 0., double(NumOfSegBH1+1) );
  HB1( BH1Hid +31, "ClusterSize BH1", 5, 0., 5. );
  HB1( BH1Hid +32, "HitPat Cluster BH1", 2*NumOfSegBH1, 0., double(NumOfSegBH1) );
  HB1( BH1Hid +33, "CMeamTime Cluster BH1", 200, -10., 10. );
  HB1( BH1Hid +34, "DeltaE Cluster BH1", 100, -0.5, 4.5 );
  HB1( BH1Hid +35, "#Clusters BH1(AdcGood)", NumOfSegBH1+1, 0., double(NumOfSegBH1+1) );
  HB1( BH1Hid +36, "CMeamTime Cluster BH1(AdcGood)", 200, -10., 10. );

  HB2( BH1Hid +41, "BH1ClP%BH1ClP",  NumOfSegBH1,   0., double(NumOfSegBH1),
       NumOfSegBH1,   0., double(NumOfSegBH1) );
  HB2( BH1Hid +42, "CMeanTimeBH1%CMeanTimeBH1[Cluster]",
       100, -5., 5., 100, -5., 5. );
  HB1( BH1Hid +43, "TDiff BH1[Cluster]", 200, -10., 10. );
  HB2( BH1Hid +44, "BH1ClP%BH1ClP[AdcGood]",  NumOfSegBH1,   0., double(NumOfSegBH1),
       NumOfSegBH1,   0., double(NumOfSegBH1) );

  // BH2
  HB1( BH2Hid +0, "#Hits BH2",        NumOfSegBH2+1, 0., double(NumOfSegBH2+1) );
  HB1( BH2Hid +1, "Hitpat BH2",       NumOfSegBH2,   0., double(NumOfSegBH2)   );
  HB1( BH2Hid +2, "#Hits BH2(Tor)",   NumOfSegBH2+1, 0., double(NumOfSegBH2+1) );
  HB1( BH2Hid +3, "Hitpat BH2(Tor)",  NumOfSegBH2,   0., double(NumOfSegBH2)   );
  HB1( BH2Hid +4, "#Hits BH2(Tand)",  NumOfSegBH2+1, 0., double(NumOfSegBH2+1) );
  HB1( BH2Hid +5, "Hitpat BH2(Tand)", NumOfSegBH2,   0., double(NumOfSegBH2)   );

  for( int i=1; i<=NumOfSegBH2; ++i ){
    TString title1 = Form("BH2-%d UpAdc", i);
    TString title2 = Form("BH2-%d DownAdc", i);
    TString title3 = Form("BH2-%d UpTdc", i);
    TString title4 = Form("BH2-%d DownTdc", i);
    TString title5 = Form("BH2-%d UpAdc(w Tdc)", i);
    TString title6 = Form("BH2-%d DownAdc(w Tdc)", i);
    TString title7 = Form("BH2-%d UpAdc(w/o Tdc)", i);
    TString title8 = Form("BH2-%d DownAdc(w/o Tdc)", i);
    HB1( BH2Hid +100*i +1, title1, NbinAdc,   MinAdc,   MaxAdc );
    HB1( BH2Hid +100*i +2, title2, NbinAdc,   MinAdc,   MaxAdc );
    HB1( BH2Hid +100*i +3, title3, NbinTdcHr, MinTdcHr, MaxTdcHr );
    HB1( BH2Hid +100*i +4, title4, NbinTdcHr, MinTdcHr, MaxTdcHr );
    HB1( BH2Hid +100*i +5, title5, NbinAdc,   MinAdc,   MaxAdc );
    HB1( BH2Hid +100*i +6, title6, NbinAdc,   MinAdc,   MaxAdc );
    HB1( BH2Hid +100*i +7, title7, NbinAdc,   MinAdc,   MaxAdc );
    HB1( BH2Hid +100*i +8, title8, NbinAdc,   MinAdc,   MaxAdc );
  }
  HB1( BH2Hid +10, "#Hits BH2[Hodo]",  NumOfSegBH2+1, 0., double(NumOfSegBH2+1) );
  HB1( BH2Hid +11, "Hitpat BH2[Hodo]", NumOfSegBH2,   0., double(NumOfSegBH2)   );
  HB1( BH2Hid +12, "CMeanTime BH2", 200, -10., 10. );
  HB1( BH2Hid +13, "dE BH2", 200, -0.5, 4.5 );
  HB1( BH2Hid +14, "#Hits BH2[HodoGood]",  NumOfSegBH2+1, 0., double(NumOfSegBH2+1) );
  HB1( BH2Hid +15, "Hitpat BH2[HodoGood]", NumOfSegBH2,   0., double(NumOfSegBH2)   );
  HB1( BH2Hid +16, "CMeanTime BH2[HodoGood]", 200, -10., 10. );

  for( int i=1; i<=NumOfSegBH2; ++i ){
    TString title11 = Form("BH2-%d Up Time", i);
    TString title12 = Form("BH2-%d Down Time", i);
    TString title13 = Form("BH2-%d MeanTime", i);
    TString title14 = Form("BH2-%d Up dE", i);
    TString title15 = Form("BH2-%d Down dE", i);
    TString title16 = Form("BH2-%d dE", i);
    TString title17 = Form("BH2-%d Up CTime", i);
    TString title18 = Form("BH2-%d Down CTime", i);
    TString title19 = Form("BH2-%d CMeanTime", i);
    TString title20 = Form("BH2-%d Tup-Tdown", i);
    TString title21 = Form("BH2-%d Up Time0", i);
    TString title22 = Form("BH2-%d Down Time0", i);
    TString title23 = Form("BH2-%d Up CTime", i);
    TString title24 = Form("BH2-%d Down CTime", i);
    TString title25 = Form("BH2-%d MeanTime0", i);
    TString title26 = Form("BH2-%d CMeanTime0", i);
    TString title27 = Form("BH2-%d Up dE%%Time", i);
    TString title28 = Form("BH2-%d Down dE%%Time", i);
    TString title29 = Form("BH2-%d Up dE%%CTime", i);
    TString title30 = Form("BH2-%d Down dE%%CTime", i);
    HB1( BH2Hid +100*i +11, title11, 200, -10., 10. );
    HB1( BH2Hid +100*i +12, title12, 200, -10., 10. );
    HB1( BH2Hid +100*i +13, title13, 200, -10., 10. );
    HB1( BH2Hid +100*i +14, title14, 200, -0.5, 4.5 );
    HB1( BH2Hid +100*i +15, title15, 200, -0.5, 4.5 );
    HB1( BH2Hid +100*i +16, title16, 200, -0.5, 4.5 );
    HB1( BH2Hid +100*i +17, title17, 200, -10., 10. );
    HB1( BH2Hid +100*i +18, title18, 200, -10., 10. );
    HB1( BH2Hid +100*i +19, title19, 200, -10., 10. );
    HB1( BH2Hid +100*i +20, title20, 200, -5.0, 5.0 );
    HB1( BH2Hid +100*i +21, title21, 200, -10., 10. );
    HB1( BH2Hid +100*i +22, title22, 200, -10., 10. );
    HB1( BH2Hid +100*i +23, title23, 200, -10., 10. );
    HB1( BH2Hid +100*i +24, title24, 200, -10., 10. );
    HB1( BH2Hid +100*i +25, title25, 200, -10., 10. );
    HB1( BH2Hid +100*i +26, title26, 200, -10., 10. );
    HB2( BH2Hid +100*i +27, title27, 100, -10., 10., 100, -0.5, 4.5 );
    HB2( BH2Hid +100*i +28, title28, 100, -10., 10., 100, -0.5, 4.5 );
    HB2( BH2Hid +100*i +29, title29, 100, -10., 10., 100, -0.5, 4.5 );
    HB2( BH2Hid +100*i +30, title30, 100, -10., 10., 100, -0.5, 4.5 );
  }

  HB2( BH2Hid +21, "BH2HitPat%BH2HitPat[HodoGood]", NumOfSegBH2,   0., double(NumOfSegBH2),
       NumOfSegBH2,   0., double(NumOfSegBH2) );
  HB2( BH2Hid +22, "CMeanTimeBH2%CMeanTimeBH2[HodoGood]",
       100, -2.5, 2.5, 100, -2.5, 2.5 );
  HB1( BH2Hid +23, "TDiff BH2[HodoGood]", 200, -10., 10. );
  HB2( BH2Hid +24, "BH2HitPat%BH2HitPat[HodoGood2]", NumOfSegBH2,   0., double(NumOfSegBH2),
       NumOfSegBH2,   0., double(NumOfSegBH2) );

  HB1( BH2Hid +30, "#Clusters BH2", NumOfSegBH2+1, 0., double(NumOfSegBH2+1) );
  HB1( BH2Hid +31, "ClusterSize BH2", 5, 0., 5. );
  HB1( BH2Hid +32, "HitPat Cluster BH2", 2*NumOfSegBH2, 0., double(NumOfSegBH2) );
  HB1( BH2Hid +33, "CMeamTime Cluster BH2", 200, -10., 10. );
  HB1( BH2Hid +34, "DeltaE Cluster BH2", 100, -0.5, 4.5 );
  HB1( BH2Hid +35, "#Clusters BH2(ADCGood)", NumOfSegBH2+1, 0., double(NumOfSegBH2+1) );
  HB1( BH2Hid +36, "CMeamTime Cluster BH2(ADCGood)", 200, -10., 10. );

  HB2( BH2Hid +41, "BH2ClP%BH2ClP", NumOfSegBH2,   0., double(NumOfSegBH2),
       NumOfSegBH2,   0., double(NumOfSegBH2) );
  HB2( BH2Hid +42, "CMeanTimeBH2%CMeanTimeBH2[Cluster]",
       100, -2.5, 2.5, 100, -2.5, 2.5 );
  HB1( BH2Hid +43, "TDiff BH2[Cluster]", 200, -10., 10. );
  HB2( BH2Hid +44, "BH2ClP%BH2ClP(ADCGood)", NumOfSegBH2,   0., double(NumOfSegBH2),
       NumOfSegBH2,   0., double(NumOfSegBH2) );

  HB1( 201, "TimeDif BH1-BH2", 200, -10., 10. );
  HB2( 202, "SegBH2%SegBH1",NumOfSegBH1,   0., double(NumOfSegBH1),
       NumOfSegBH2,   0., double(NumOfSegBH2) );
  //For BH1vsBH2 Corr
  HB2( 203, "MTBH2%MTBH1", 200, -10., 10., 200, -10., 10. );
  HB1( 204, "MTBH1", 200, -10., 10.);
  HB1( 205, "MTBH2", 200, -10., 10.);

  HB1( 211, "TimeDif BH1-BH2(GoodAdc)", 200, -10., 10. );
  HB2( 212, "SegBH2%SegBH1(GoodAdc)",NumOfSegBH1,   0., double(NumOfSegBH1),
       NumOfSegBH2,   0., double(NumOfSegBH2) );

  // BH1-BH2 PHC
  for( int i=1; i<=NumOfSegBH1; ++i ){
    TString title1 = Form("BH1-%dU CT-TOF%%dE", i);
    TString title2 = Form("BH1-%dD CT-TOF%%dE", i);
    TString title3 = Form("BH1-%dU  T-TOF%%dE", i);
    TString title4 = Form("BH1-%dD  T-TOF%%dE", i);
    HB2( BH1Hid +100*i +81, title1, 100, -0.5, 4.5, 100, -10., 10. );
    HB2( BH1Hid +100*i +82, title2, 100, -0.5, 4.5, 100, -10., 10. );
    HB2( BH1Hid +100*i +83, title3, 100, -0.5, 4.5, 100, -10., 10. );
    HB2( BH1Hid +100*i +84, title4, 100, -0.5, 4.5, 100, -10., 10. );
  }
  for( int i=1; i<=NumOfSegBH2; ++i ){
    TString title1 = Form("BH2-%dU CT-TOF%%dE", i);
    TString title2 = Form("BH2-%dD CT-TOF%%dE", i);
    TString title3 = Form("BH2-%dU  T-TOF%%dE", i);
    TString title4 = Form("BH2-%dD  T-TOF%%dE", i);
    HB2( BH2Hid +100*i +81, title1, 100, -0.5, 4.5, 100, -10., 10. );
    HB2( BH2Hid +100*i +82, title2, 100, -0.5, 4.5, 100, -10., 10. );
    HB2( BH2Hid +100*i +83, title3, 100, -0.5, 4.5, 100, -10., 10. );
    HB2( BH2Hid +100*i +84, title4, 100, -0.5, 4.5, 100, -10., 10. );
  }

  // SAC
  HB1( SACHid +0, "#Hits SAC",        NumOfSegSAC+1, 0., double(NumOfSegSAC+1) );
  HB1( SACHid +1, "Hitpat SAC",       NumOfSegSAC,   0., double(NumOfSegSAC)   );
  HB1( SACHid +2, "#Hits SAC(Tor)",   NumOfSegSAC+1, 0., double(NumOfSegSAC+1) );
  HB1( SACHid +3, "Hitpat SAC(Tor)",  NumOfSegSAC,   0., double(NumOfSegSAC)   );
  HB1( SACHid +4, "#Hits SAC(Tand)",  NumOfSegSAC+1, 0., double(NumOfSegSAC+1) );
  HB1( SACHid +5, "Hitpat SAC(Tand)", NumOfSegSAC,   0., double(NumOfSegSAC)   );
  for( int i=1; i<=NumOfSegSAC; ++i ){
    TString title1 = Form("SAC-%d UpAdc", i);
    TString title3 = Form("SAC-%d UpTdc", i);
    TString title5 = Form("SAC-%d UpAdc(w Tdc)", i);
    TString title7 = Form("SAC-%d UpAdc(w/o Tdc)", i);
    HB1( SACHid +100*i +1, title1, NbinTdc, MinTdc, MaxTdc );
    HB1( SACHid +100*i +3, title3, NbinTdc, MinTdc, MaxTdc );
    HB1( SACHid +100*i +5, title5, NbinAdc, MinAdc, MaxAdc );
    HB1( SACHid +100*i +7, title7, NbinAdc, MinAdc, MaxAdc );
  }
  HB1( SACHid +10, "#Hits SAC[Hodo]",     NumOfSegSAC+1, 0., double(NumOfSegSAC+1) );
  HB1( SACHid +11, "Hitpat SAC[Hodo]",    NumOfSegSAC,   0., double(NumOfSegSAC)   );
  for( int i=1; i<=NumOfSegSAC; ++i ){
    TString title1 = Form("SAC-%d Time", i);
    TString title3 = Form("SAC-%d dE", i);
    TString title5 = Form("SAC-%d CTime", i);
    HB1( SACHid +100*i +11, title1, 500, -5., 45. );
    HB1( SACHid +100*i +12, title3, 200, -0.5, 4.5 );
    HB1( SACHid +100*i +13, title5, 500, -5., 45. );
  }

  // TOF
  HB1( TOFHid +0, "#Hits TOF",        NumOfSegTOF+1, 0., double(NumOfSegTOF+1) );
  HB1( TOFHid +1, "Hitpat TOF",       NumOfSegTOF,   0., double(NumOfSegTOF)   );
  HB1( TOFHid +2, "#Hits TOF(Tor)",   NumOfSegTOF+1, 0., double(NumOfSegTOF+1) );
  HB1( TOFHid +3, "Hitpat TOF(Tor)",  NumOfSegTOF,   0., double(NumOfSegTOF)   );
  HB1( TOFHid +4, "#Hits TOF(Tand)",  NumOfSegTOF+1, 0., double(NumOfSegTOF+1) );
  HB1( TOFHid +5, "Hitpat TOF(Tand)", NumOfSegTOF,   0., double(NumOfSegTOF)   );

  for( int i=1; i<=NumOfSegTOF; ++i ){
    TString title1 = Form("TOF-%d UpAdc", i);
    TString title2 = Form("TOF-%d DownAdc", i);
    TString title3 = Form("TOF-%d UpTdc", i);
    TString title4 = Form("TOF-%d DownTdc", i);
    TString title5 = Form("TOF-%d UpAdc(w Tdc)", i);
    TString title6 = Form("TOF-%d DownAdc(w Tdc)", i);
    TString title7 = Form("TOF-%d UpAdc(w/o Tdc)", i);
    TString title8 = Form("TOF-%d DownAdc(w/o Tdc)", i);
    HB1( TOFHid +100*i +1, title1, NbinAdc, MinAdc, MaxAdc );
    HB1( TOFHid +100*i +2, title2, NbinAdc, MinAdc, MaxAdc );
    HB1( TOFHid +100*i +3, title3, NbinTdcHr, MinTdcHr, MaxTdcHr );
    HB1( TOFHid +100*i +4, title4, NbinTdcHr, MinTdcHr, MaxTdcHr );
    HB1( TOFHid +100*i +5, title5, NbinAdc, MinAdc, MaxAdc );
    HB1( TOFHid +100*i +6, title6, NbinAdc, MinAdc, MaxAdc );
    HB1( TOFHid +100*i +7, title7, NbinAdc, MinAdc, MaxAdc );
    HB1( TOFHid +100*i +8, title8, NbinAdc, MinAdc, MaxAdc );
  }

  HB1( TOFHid +10, "#Hits Tof[Hodo]",  NumOfSegTOF+1, 0., double(NumOfSegTOF+1) );
  HB1( TOFHid +11, "Hitpat Tof[Hodo]", NumOfSegTOF,   0., double(NumOfSegTOF)   );
  HB1( TOFHid +12, "CMeanTime Tof", 500, -5., 45. );
  HB1( TOFHid +13, "dE Tof", 200, -0.5, 4.5 );
  HB1( TOFHid +14, "#Hits Tof[HodoGood]",  NumOfSegTOF+1, 0., double(NumOfSegTOF+1) );
  HB1( TOFHid +15, "Hitpat Tof[HodoGood]", NumOfSegTOF,   0., double(NumOfSegTOF)   );

  for( int i=1; i<=NumOfSegTOF; ++i ){
    TString title11 = Form("TOF-%d Up Time", i);
    TString title12 = Form("TOF-%d Down Time", i);
    TString title13 = Form("TOF-%d MeanTime", i);
    TString title14 = Form("TOF-%d Up dE", i);
    TString title15 = Form("TOF-%d Down dE", i);
    TString title16 = Form("TOF-%d dE", i);
    TString title17 = Form("TOF-%d Up CTime", i);
    TString title18 = Form("TOF-%d Down CTime", i);
    TString title19 = Form("TOF-%d CMeanTime", i);
    TString title20 = Form("TOF-%d Tup-Tdown", i);
    HB1( TOFHid +100*i +11, title11, 500, -5., 45. );
    HB1( TOFHid +100*i +12, title12, 500, -5., 45. );
    HB1( TOFHid +100*i +13, title13, 500, -5., 45. );
    HB1( TOFHid +100*i +14, title14, 200, -0.5, 4.5 );
    HB1( TOFHid +100*i +15, title15, 200, -0.5, 4.5 );
    HB1( TOFHid +100*i +16, title16, 200, -0.5, 4.5 );
    HB1( TOFHid +100*i +17, title17, 500, -5., 45. );
    HB1( TOFHid +100*i +18, title18, 500, -5., 45. );
    HB1( TOFHid +100*i +19, title19, 500, -5., 45. );
    HB1( TOFHid +100*i +20, title20, 200, -10.0, 10.0 );
  }

  HB2( TOFHid +21, "TofHitPat%TofHitPat[HodoGood]", NumOfSegTOF,   0., double(NumOfSegTOF),
       NumOfSegTOF,   0., double(NumOfSegTOF) );
  HB2( TOFHid +22, "CMeanTimeTof%CMeanTimeTof[HodoGood]",
       120, 10., 40., 120, 10., 40. );
  HB1( TOFHid +23, "TDiff Tof[HodoGood]", 200, -10., 10. );
  HB2( TOFHid +24, "TofHitPat%TofHitPat[HodoGood2]", NumOfSegTOF,   0., double(NumOfSegTOF),
       NumOfSegTOF,   0., double(NumOfSegTOF) );

  HB1( TOFHid +30, "#Clusters Tof", NumOfSegTOF+1, 0., double(NumOfSegTOF+1) );
  HB1( TOFHid +31, "ClusterSize Tof", 5, 0., 5. );
  HB1( TOFHid +32, "HitPat Cluster Tof", 2*NumOfSegTOF, 0., double(NumOfSegTOF) );
  HB1( TOFHid +33, "CMeamTime Cluster Tof", 500, -5., 45. );
  HB1( TOFHid +34, "DeltaE Cluster Tof", 100, -0.5, 4.5 );

  // HtTOF
  HB1( HtTOFHid +0, "#Hits HtTOF",        NumOfSegTOF+1, 0., double(NumOfSegTOF+1) );
  HB1( HtTOFHid +1, "Hitpat HtTOF",       NumOfSegTOF,   0., double(NumOfSegTOF)   );
  HB1( HtTOFHid +2, "#Hits HtTOF(Tor)",   NumOfSegTOF+1, 0., double(NumOfSegTOF+1) );
  HB1( HtTOFHid +3, "Hitpat HtTOF(Tor)",  NumOfSegTOF,   0., double(NumOfSegTOF)   );
  HB1( HtTOFHid +4, "#Hits HtTOF(Tand)",  NumOfSegTOF+1, 0., double(NumOfSegTOF+1) );
  HB1( HtTOFHid +5, "Hitpat HtTOF(Tand)", NumOfSegTOF,   0., double(NumOfSegTOF)   );

  for( int i=1; i<=NumOfSegTOF; ++i ){
    TString title1 = Form("HtTOF-%d UpAdc", i);
    TString title2 = Form("HtTOF-%d DownAdc", i);
    TString title3 = Form("HtTOF-%d UpTdc", i);
    TString title4 = Form("HtTOF-%d DownTdc", i);
    TString title5 = Form("HtTOF-%d UpAdc(w Tdc)", i);
    TString title6 = Form("HtTOF-%d DownAdc(w Tdc)", i);
    TString title7 = Form("HtTOF-%d UpAdc(w/o Tdc)", i);
    TString title8 = Form("HtTOF-%d DownAdc(w/o Tdc)", i);
    HB1( HtTOFHid +100*i +1, title1, NbinTdc, MinTdc, MaxTdc );
    HB1( HtTOFHid +100*i +2, title2, NbinTdc, MinTdc, MaxTdc );
    HB1( HtTOFHid +100*i +3, title3, NbinTdc, MinTdc, MaxTdc );
    HB1( HtTOFHid +100*i +4, title4, NbinTdc, MinTdc, MaxTdc );
    HB1( HtTOFHid +100*i +5, title5, NbinAdc, MinAdc, MaxAdc );
    HB1( HtTOFHid +100*i +6, title6, NbinAdc, MinAdc, MaxAdc );
    HB1( HtTOFHid +100*i +7, title7, NbinAdc, MinAdc, MaxAdc );
    HB1( HtTOFHid +100*i +8, title8, NbinAdc, MinAdc, MaxAdc );
  }

  HB1( HtTOFHid +10, "#Hits Lc[Hodo]",  NumOfSegTOF+1, 0., double(NumOfSegTOF+1) );
  HB1( HtTOFHid +11, "Hitpat Lc[Hodo]", NumOfSegTOF,   0., double(NumOfSegTOF)   );
  HB1( HtTOFHid +12, "CMeanTime Lc", 500, -5., 45. );
  HB1( HtTOFHid +13, "dE Lc", 200, -0.5, 4.5 );
  HB1( HtTOFHid +14, "#Hits Lc[HodoGood]",  NumOfSegTOF+1, 0., double(NumOfSegTOF+1) );
  HB1( HtTOFHid +15, "Hitpat Lc[HodoGood]", NumOfSegTOF,   0., double(NumOfSegTOF)   );

  for( int i=1; i<=NumOfSegTOF; ++i ){
    TString title11 = Form("HtTOF-%d Up Time", i);
    TString title12 = Form("HtTOF-%d Down Time", i);
    TString title13 = Form("HtTOF-%d MeanTime", i);
    TString title14 = Form("HtTOF-%d Up dE", i);
    TString title15 = Form("HtTOF-%d Down dE", i);
    TString title16 = Form("HtTOF-%d dE", i);
    TString title17 = Form("HtTOF-%d Up CTime", i);
    TString title18 = Form("HtTOF-%d Down CTime", i);
    TString title19 = Form("HtTOF-%d CMeanTime", i);
    TString title20 = Form("HtTOF-%d Tup-Tdown", i);
    HB1( HtTOFHid +100*i +11, title11, 500, -5., 45. );
    HB1( HtTOFHid +100*i +12, title12, 500, -5., 45. );
    HB1( HtTOFHid +100*i +13, title13, 500, -5., 45. );
    HB1( HtTOFHid +100*i +14, title14, 200, -0.5, 4.5 );
    HB1( HtTOFHid +100*i +15, title15, 200, -0.5, 4.5 );
    HB1( HtTOFHid +100*i +16, title16, 200, -0.5, 4.5 );
    HB1( HtTOFHid +100*i +17, title17, 500, -5., 45. );
    HB1( HtTOFHid +100*i +18, title18, 500, -5., 45. );
    HB1( HtTOFHid +100*i +19, title19, 500, -5., 45. );
    HB1( HtTOFHid +100*i +20, title20, 200, -10.0, 10.0 );
  }

  HB2( HtTOFHid +21, "LcHitPat%LcHitPat[HodoGood]", NumOfSegTOF,   0., double(NumOfSegTOF),
       NumOfSegTOF,   0., double(NumOfSegTOF) );
  HB2( HtTOFHid +22, "CMeanTimeLc%CMeanTimeLc[HodoGood]",
       120, 10., 40., 120, 10., 40. );
  HB1( HtTOFHid +23, "TDiff Lc[HodoGood]", 200, -10., 10. );
  HB2( HtTOFHid +24, "LcHitPat%LcHitPat[HodoGood2]", NumOfSegTOF,   0., double(NumOfSegTOF),
       NumOfSegTOF,   0., double(NumOfSegTOF) );

  HB1( HtTOFHid +30, "#Clusters Lc", NumOfSegTOF+1, 0., double(NumOfSegTOF+1) );
  HB1( HtTOFHid +31, "ClusterSize Lc", 5, 0., 5. );
  HB1( HtTOFHid +32, "HitPat Cluster Lc", 2*NumOfSegTOF, 0., double(NumOfSegTOF) );
  HB1( HtTOFHid +33, "CMeamTime Cluster Lc", 500, -5., 45. );
  HB1( HtTOFHid +34, "DeltaE Cluster Lc", 100, -0.5, 4.5 );

  // LC
  HB1( LCHid +0, "#Hits LC",        NumOfSegLC+1, 0., double(NumOfSegLC+1) );
  HB1( LCHid +1, "Hitpat LC",       NumOfSegLC,   0., double(NumOfSegLC)   );
  HB1( LCHid +2, "#Hits LC(Tor)",   NumOfSegLC+1, 0., double(NumOfSegLC+1) );
  HB1( LCHid +3, "Hitpat LC(Tor)",  NumOfSegLC,   0., double(NumOfSegLC)   );
  HB1( LCHid +4, "#Hits LC(Tand)",  NumOfSegLC+1, 0., double(NumOfSegLC+1) );
  HB1( LCHid +5, "Hitpat LC(Tand)", NumOfSegLC,   0., double(NumOfSegLC)   );

  for( int i=1; i<=NumOfSegLC; ++i ){
    TString title1 = Form("LC-%d UpAdc", i);
    TString title2 = Form("LC-%d DownAdc", i);
    TString title3 = Form("LC-%d UpTdc", i);
    TString title4 = Form("LC-%d DownTdc", i);
    TString title5 = Form("LC-%d UpAdc(w Tdc)", i);
    TString title6 = Form("LC-%d DownAdc(w Tdc)", i);
    TString title7 = Form("LC-%d UpAdc(w/o Tdc)", i);
    TString title8 = Form("LC-%d DownAdc(w/o Tdc)", i);
    HB1( LCHid +100*i +1, title1, NbinTdc, MinTdc, MaxTdc );
    HB1( LCHid +100*i +2, title2, NbinTdc, MinTdc, MaxTdc );
    HB1( LCHid +100*i +3, title3, NbinTdc, MinTdc, MaxTdc );
    HB1( LCHid +100*i +4, title4, NbinTdc, MinTdc, MaxTdc );
    HB1( LCHid +100*i +5, title5, NbinAdc, MinAdc, MaxAdc );
    HB1( LCHid +100*i +6, title6, NbinAdc, MinAdc, MaxAdc );
    HB1( LCHid +100*i +7, title7, NbinAdc, MinAdc, MaxAdc );
    HB1( LCHid +100*i +8, title8, NbinAdc, MinAdc, MaxAdc );
  }

  HB1( LCHid +10, "#Hits Lc[Hodo]",  NumOfSegLC+1, 0., double(NumOfSegLC+1) );
  HB1( LCHid +11, "Hitpat Lc[Hodo]", NumOfSegLC,   0., double(NumOfSegLC)   );
  HB1( LCHid +12, "CMeanTime Lc", 500, -5., 45. );
  HB1( LCHid +13, "dE Lc", 200, -0.5, 4.5 );
  HB1( LCHid +14, "#Hits Lc[HodoGood]",  NumOfSegLC+1, 0., double(NumOfSegLC+1) );
  HB1( LCHid +15, "Hitpat Lc[HodoGood]", NumOfSegLC,   0., double(NumOfSegLC)   );

  for( int i=1; i<=NumOfSegLC; ++i ){
    TString title11 = Form("LC-%d Up Time", i);
    TString title12 = Form("LC-%d Down Time", i);
    TString title13 = Form("LC-%d MeanTime", i);
    TString title14 = Form("LC-%d Up dE", i);
    TString title15 = Form("LC-%d Down dE", i);
    TString title16 = Form("LC-%d dE", i);
    TString title17 = Form("LC-%d Up CTime", i);
    TString title18 = Form("LC-%d Down CTime", i);
    TString title19 = Form("LC-%d CMeanTime", i);
    TString title20 = Form("LC-%d Tup-Tdown", i);
    HB1( LCHid +100*i +11, title11, 500, -5., 45. );
    HB1( LCHid +100*i +12, title12, 500, -5., 45. );
    HB1( LCHid +100*i +13, title13, 500, -5., 45. );
    HB1( LCHid +100*i +14, title14, 200, -0.5, 4.5 );
    HB1( LCHid +100*i +15, title15, 200, -0.5, 4.5 );
    HB1( LCHid +100*i +16, title16, 200, -0.5, 4.5 );
    HB1( LCHid +100*i +17, title17, 500, -5., 45. );
    HB1( LCHid +100*i +18, title18, 500, -5., 45. );
    HB1( LCHid +100*i +19, title19, 500, -5., 45. );
    HB1( LCHid +100*i +20, title20, 200, -10.0, 10.0 );
  }

  HB2( LCHid +21, "LcHitPat%LcHitPat[HodoGood]", NumOfSegLC,   0., double(NumOfSegLC),
       NumOfSegLC,   0., double(NumOfSegLC) );
  HB2( LCHid +22, "CMeanTimeLc%CMeanTimeLc[HodoGood]",
       120, 10., 40., 120, 10., 40. );
  HB1( LCHid +23, "TDiff Lc[HodoGood]", 200, -10., 10. );
  HB2( LCHid +24, "LcHitPat%LcHitPat[HodoGood2]", NumOfSegLC,   0., double(NumOfSegLC),
       NumOfSegLC,   0., double(NumOfSegLC) );

  HB1( LCHid +30, "#Clusters Lc", NumOfSegLC+1, 0., double(NumOfSegLC+1) );
  HB1( LCHid +31, "ClusterSize Lc", 5, 0., 5. );
  HB1( LCHid +32, "HitPat Cluster Lc", 2*NumOfSegLC, 0., double(NumOfSegLC) );
  HB1( LCHid +33, "CMeamTime Cluster Lc", 500, -5., 45. );
  HB1( LCHid +34, "DeltaE Cluster Lc", 100, -0.5, 4.5 );

  ////////////////////////////////////////////
  //Tree
  HBTree( "tree","tree of Counter" );
  tree->Branch("evnum",     &event.evnum,     "evnum/I");
  tree->Branch("spill",     &event.spill,     "spill/I");
  //Trig
  tree->Branch("trignhits", &event.trignhits, "trignhits/I");
  tree->Branch("trigpat",    event.trigpat,   "trigpat[trignhits]/I");
  tree->Branch("trigflag",   event.trigflag,  Form("trigflag[%d]/I", NumOfSegTrig));

  //BH1
  tree->Branch("bh1nhits",   &event.bh1nhits,    "bh1nhits/I");
  tree->Branch("bh1hitpat",   event.bh1hitpat,   Form("bh1hitpat[%d]/I",NumOfSegBH1));
  tree->Branch("bh1ua",       event.bh1ua,       Form("bh1ua[%d]/D", NumOfSegBH1));
  tree->Branch("bh1ut",       event.bh1ut,       Form("bh1ut[%d][%d]/D", NumOfSegBH1, MaxDepth));
  tree->Branch("bh1da",       event.bh1da,       Form("bh1da[%d]/D", NumOfSegBH1));
  tree->Branch("bh1dt",       event.bh1dt,       Form("bh1dt[%d][%d]/D", NumOfSegBH1, MaxDepth));

  //BH2
  tree->Branch("bh2nhits",   &event.bh2nhits,    "bh2nhits/I");
  tree->Branch("bh2hitpat",   event.bh2hitpat,   Form("bh2hitpat[%d]/I", NumOfSegBH2));
  tree->Branch("bh2ua",       event.bh2ua,       Form("bh2ua[%d]/D", NumOfSegBH2));
  tree->Branch("bh2ut",       event.bh2ut,       Form("bh2ut[%d][%d]/D", NumOfSegBH2, MaxDepth));
  tree->Branch("bh2da",       event.bh2da,       Form("bh2da[%d]/D", NumOfSegBH2));
  tree->Branch("bh2dt",       event.bh2dt,       Form("bh2dt[%d][%d]/D", NumOfSegBH2, MaxDepth));

  //FPGA BH2MT
  tree->Branch("fpga_bh2mtnhits",   &event.fpga_bh2mtnhits,    "fpga_bh2mtnhits/I");
  tree->Branch("fpga_bh2mthitpat",   event.fpga_bh2mthitpat,   Form("fpga_bh2mthitpat[%d][%d]/I",NumOfSegBH2, MaxDepth));
  tree->Branch("fpga_bh2mt",       event.fpga_bh2mt,       Form("fpga_bh2mt[%d][%d]/D", NumOfSegBH2, MaxDepth));

  //SAC
  tree->Branch("sacnhits",   &event.sacnhits,   "sacnhits/I");
  tree->Branch("sachitpat",   event.sachitpat,  Form("sachitpat[%d]/I", NumOfSegSAC));
  tree->Branch("saca",        event.saca,       Form("saca[%d]/D", NumOfSegSAC));
  tree->Branch("sact",        event.sact,       Form("sact[%d][%d]/D", NumOfSegSAC, MaxDepth));
  //TOF
  tree->Branch("tofnhits",   &event.tofnhits,   "tofnhits/I");
  tree->Branch("tofhitpat",   event.tofhitpat,  Form("tofhitpat[%d]/I", NumOfSegTOF));
  tree->Branch("tofua",       event.tofua,      Form("tofua[%d]/D", NumOfSegTOF));
  tree->Branch("tofut",       event.tofut,      Form("tofut[%d][%d]/D", NumOfSegTOF, MaxDepth));
  tree->Branch("tofda",       event.tofda,      Form("tofda[%d]/D", NumOfSegTOF));
  tree->Branch("tofdt",       event.tofdt,      Form("tofdt[%d][%d]/D", NumOfSegTOF, MaxDepth));
  //TOF-HT
  tree->Branch("tofhtnhits",   &event.tofhtnhits,   "tofhtnhits/I");
  tree->Branch("tofhthitpat",   event.tofhthitpat,  Form("tofhthitpat[%d]/I", NumOfSegTOF));
  tree->Branch("tofhtt" ,       event.tofhtt,       Form("tofhtt[%d][%d]/D", NumOfSegTOF, MaxDepth));
  //LC
  tree->Branch("lcnhits",   &event.lcnhits,   "lcnhits/I");
  tree->Branch("lchitpat",   event.lchitpat,  Form("lchitpat[%d]/I", NumOfSegLC));
  tree->Branch("lct" ,       event.lct,       Form("lct[%d][%d]/D", NumOfSegLC, MaxDepth));

  //Normalized data
  tree->Branch("bh1mt",     event.bh1mt,     Form("bh1mt[%d][%d]/D", NumOfSegBH1, MaxDepth));
  tree->Branch("bh1de",     event.bh1de,     Form("bh1de[%d]/D", NumOfSegBH1));
  tree->Branch("bh2mt",     event.bh2mt,     Form("bh2mt[%d][%d]/D", NumOfSegBH2, MaxDepth));
  tree->Branch("bh2de",     event.bh2de,     Form("bh2de[%d]/D", NumOfSegBH2));
  tree->Branch("sacmt",     event.sacmt,     Form("sacmt[%d][%d]/D", NumOfSegSAC, MaxDepth));
  tree->Branch("sacde",     event.sacde,     Form("sacde[%d]/D", NumOfSegSAC));

  tree->Branch("tofmt",     event.tofmt,     Form("tofmt[%d][%d]/D", NumOfSegTOF, MaxDepth));
  tree->Branch("tofde",     event.tofde,     Form("tofde[%d]/D", NumOfSegTOF));
  tree->Branch("tofhtmt",   event.tofhtmt,   Form("tofhtmt[%d][%d]/D", NumOfSegTOF, MaxDepth));
  tree->Branch("lcmt",      event.lcmt,      Form("lcmt[%d][%d]/D", NumOfSegLC, MaxDepth));

  tree->Branch("t0",        event.t0,        Form("t0[%d][%d]/D",  NumOfSegBH2, MaxDepth));
  tree->Branch("ct0",       event.ct0,       Form("ct0[%d][%d]/D", NumOfSegBH2, MaxDepth));
  tree->Branch("btof",      event.btof,      Form("btof[%d][%d]/D",  NumOfSegBH1, NumOfSegBH2));
  tree->Branch("cbtof",     event.cbtof,     Form("cbtof[%d][%d]/D", NumOfSegBH1, NumOfSegBH2));

  tree->Branch("Time0Seg", &event.Time0Seg,  "Time0Seg/D");
  tree->Branch("deTime0",  &event.deTime0,   "deTime0/D");
  tree->Branch("Time0",    &event.Time0,     "Time0/D");
  tree->Branch("CTime0",   &event.CTime0,    "CTime0/D");

  tree->Branch("Btof0Seg", &event.Btof0Seg,  "Btof0Seg/D");
  tree->Branch("deBtof0",  &event.deBtof0,   "deBtof0/D");
  tree->Branch("Btof0",    &event.Btof0,     "Btof0/D");
  tree->Branch("CBtof0",   &event.CBtof0,    "CBtof0/D");

  ////////////////////////////////////////////
  //Dst
  hodo = new TTree( "hodo","Data Summary Table of Hodoscope" );
  hodo->Branch("evnum",     &dst.evnum,     "evnum/I");
  hodo->Branch("spill",     &dst.spill,     "spill/I");
  hodo->Branch("trignhits", &dst.trignhits, "trignhits/I");
  hodo->Branch("trigpat",    dst.trigpat,   "trigpat[trignhits]/I");
  hodo->Branch("trigflag",   dst.trigflag,  Form("trigflag[%d]/I", NumOfSegTrig));
  hodo->Branch("nhBh1",     &dst.nhBh1,     "nhBh1/I");
  hodo->Branch("csBh1",      dst.csBh1,     "csBh1[nhBh1]/I");
  hodo->Branch("Bh1Seg",     dst.Bh1Seg,    "Bh1Seg[nhBh1]/D");
  hodo->Branch("tBh1",       dst.tBh1,      "tBh1[nhBh1]/D");
  hodo->Branch("dtBh1",      dst.dtBh1,     "dtBh1[nhBh1]/D");
  hodo->Branch("deBh1",      dst.deBh1,     "deBh1[nhBh1]/D");

  hodo->Branch("nhBh2",     &dst.nhBh2,     "nhBh2/I");
  hodo->Branch("csBh2",      dst.csBh2,     "csBh2[nhBh2]/I");
  hodo->Branch("Bh2Seg",     dst.Bh2Seg,    "Bh2Seg[nhBh2]/D");
  hodo->Branch("tBh2",       dst.tBh2,      "tBh2[nhBh2]/D");
  hodo->Branch("t0Bh2",      dst.t0Bh2,     "t0Bh2[nhBh2]/D");
  hodo->Branch("dtBh2",      dst.dtBh2,     "dtBh2[nhBh2]/D");
  hodo->Branch("deBh2",      dst.deBh2,     "deBh2[nhBh2]/D");

  hodo->Branch("btof",       dst.btof,      "btof[nhBh1]/D");
  hodo->Branch("cbtof",      dst.cbtof,     "cbtof[nhBh1]/D");

  hodo->Branch("Btof0Seg",  &dst.Btof0Seg,  "Btof0Seg/D");
  hodo->Branch("deBtof0",   &dst.deBtof0,   "deBtof0/D");
  hodo->Branch("Btof0",     &dst.Btof0,     "Btof0/D");
  hodo->Branch("CBtof0",    &dst.CBtof0,    "CBtof0/D");

  hodo->Branch("Time0Seg",  &dst.Time0Seg,  "Time0Seg/D");
  hodo->Branch("deTime0",   &dst.deTime0,   "deTime0/D");
  hodo->Branch("Time0",     &dst.Time0,     "Time0/D");
  hodo->Branch("CTime0",    &dst.CTime0,    "CTime0/D");

  hodo->Branch("nhSac",     &dst.nhSac,     "nhSac/I");
  hodo->Branch("SacSeg",     dst.SacSeg,    "SacSeg[nhSac]/D");
  hodo->Branch("tSac",       dst.tSac,      "tSac[nhSac]/D");
  hodo->Branch("deSac",      dst.deSac,     "deSac[nhSac]/D");

  hodo->Branch("nhTof",     &dst.nhTof,     "nhTof/I");
  hodo->Branch("csTof",      dst.csTof,     "csTof[nhTof]/I");
  hodo->Branch("TofSeg",     dst.TofSeg,    "TofSeg[nhTof]/D");
  hodo->Branch("tTof",       dst.tTof,      "tTof[nhTof]/D");
  hodo->Branch("dtTof",      dst.dtTof,     "dtTof[nhTof]/D");
  hodo->Branch("deTof",      dst.deTof,     "deTof[nhTof]/D");

  hodo->Branch("nhHtTof",     &dst.nhHtTof,     "nhHtTof/I");
  hodo->Branch("csHtTof",      dst.csHtTof,     "csHtTof[nhHtTof]/I");
  hodo->Branch("HtTofSeg",     dst.HtTofSeg,    "HtTofSeg[nhHtTof]/D");
  hodo->Branch("tHtTof",       dst.tHtTof,      "tHtTof[nhHtTof]/D");

  hodo->Branch("nhLc",     &dst.nhLc,     "nhLc/I");
  hodo->Branch("csLc",      dst.csLc,     "csLc[nhLc]/I");
  hodo->Branch("LcSeg",     dst.LcSeg,    "LcSeg[nhLc]/D");
  hodo->Branch("tLc",       dst.tLc,      "tLc[nhLc]/D");

  hodo->Branch("utTofSeg",   dst.utTofSeg,
	       Form("utTofSeg[%d][%d]/D", NumOfSegTOF, MaxDepth) );
  hodo->Branch("dtTofSeg",   dst.dtTofSeg,
	       Form("dtTofSeg[%d]/D", NumOfSegTOF) );
  hodo->Branch("udeTofSeg",  dst.udeTofSeg,
	       Form("udeTofSeg[%d][%d]/D", NumOfSegTOF, MaxDepth) );
  hodo->Branch("ddeTofSeg",  dst.ddeTofSeg,
	       Form("ddeTofSeg[%d]/D", NumOfSegTOF) );

  HPrint();
  return true;
}

//______________________________________________________________________________
bool
ConfMan::InitializeParameterFiles( void )
{
  return
    ( InitializeParameter<HodoParamMan>("HDPRM") &&
      InitializeParameter<HodoPHCMan>("HDPHC")   &&
      InitializeParameter<UserParamMan>("USER")  );
}

//______________________________________________________________________________
bool
ConfMan::FinalizeProcess( void )
{
  return true;
}
