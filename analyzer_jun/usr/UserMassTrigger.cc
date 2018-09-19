/**
 *  file: UserMassTrigger.cc
 *  date: 2017.04.10
 *
 */

#include "VEvent.hh"

#include <iostream>
#include <sstream>
#include <cmath>

#include "BH2Cluster.hh"
#include "BH2Hit.hh"
#include "ConfMan.hh"
#include "DetectorID.hh"
#include "DCAnalyzer.hh"
#include "RMAnalyzer.hh"
#include "Hodo1Hit.hh"
#include "Hodo2Hit.hh"
#include "HodoAnalyzer.hh"
#include "HodoCluster.hh"
#include "HodoPHCMan.hh"
#include "HodoParamMan.hh"
#include "HodoRawHit.hh"
#include "KuramaLib.hh"
#include "MsTParamMan.hh"
#include "RawData.hh"
#include "RootHelper.hh"
#include "UserParamMan.hh"
#include "UnpackerManager.hh"

namespace
{
  using namespace root;
  const std::string& class_name("MassTrigger");
  RMAnalyzer&         gRM          = RMAnalyzer::GetInstance();
  const MsTParamMan&  gMsT         = MsTParamMan::GetInstance();
  const UserParamMan& gUser        = UserParamMan::GetInstance();
  const hddaq::unpacker::UnpackerManager& gUnpacker
  = hddaq::unpacker::GUnpacker::get_instance();
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
class EventMassTrigger : public VEvent
{
private:
  RawData      *rawData;
  DCAnalyzer   *DCAna;
  HodoAnalyzer *hodoAna;

public:
        EventMassTrigger( void );
       ~EventMassTrigger( void );
  bool ProcessingBegin( void );
  bool ProcessingEnd( void );
  bool ProcessingNormal( void );
  bool InitializeHistograms( void );
  void InitializeEvent( void );
};

//______________________________________________________________________________
EventMassTrigger::EventMassTrigger( void )
  : VEvent(),
    rawData(0),
    DCAna( new DCAnalyzer ),
    hodoAna(new HodoAnalyzer)
{
}

//______________________________________________________________________________
EventMassTrigger::~EventMassTrigger( void )
{
  delete hodoAna;
  delete DCAna;
  delete rawData;
}

//______________________________________________________________________________
bool
EventMassTrigger::ProcessingBegin( void )
{
  InitializeEvent();
  return true;
}

//______________________________________________________________________________
struct Event
{
  int evnum;

  int trigpat[NumOfSegTrig];
  int trigflag[NumOfSegTrig];

  // MsT
  int mst_clear;
  int mst_accept;
  int mst_final_clear;
  int mst_consolation_accept;
  int mst_fast_clear;
  int mst_level2;
  int mst_no_decision;

  int mst_ntof;
  int mst_tof[NumOfSegTOF];
  int mst_tof_tdc[NumOfSegTOF][MaxDepth];
  int mst_nsch;
  int mst_sch[NumOfSegSCH];
  int mst_sch_tdc[NumOfSegSCH][MaxDepth];

  // Software MsT
  int soft_accept;

  // Hodo
  int tofnhits;
  int tofhitpat[MaxHits];
  double tofua[NumOfSegTOF];
  double tofut[NumOfSegTOF];
  double tofda[NumOfSegTOF];
  double tofdt[NumOfSegTOF];

  // int schnhits;
  // int schhitpat[MaxDepths];
  // double schua[NumOfSegSCH];
  // double schut[NumOfSegSCH];
  // double schda[NumOfSegSCH];
  // double schdt[NumOfSegSCH];

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
EventMassTrigger::ProcessingNormal( void )
{
  static const std::string func_name("["+class_name+"::"+__func__+"]");

  rawData = new RawData;
  rawData->DecodeHits();

  gRM.Decode();

  event.evnum = gRM.EventNumber();

  bool hard_accept = true;
  bool soft_accept = true;;

  // trig flag for Mass Trigger
  {
    static const int device_id = gUnpacker.get_device_id("MsT");
    static const int plane_id  = gUnpacker.get_plane_id("MsT", "tag");
    if(gUnpacker.get_entries(device_id, plane_id, 0, 0, 0)){
      event.mst_clear              = gUnpacker.get(device_id, plane_id, 0, 0, mstClear);
      event.mst_accept             = gUnpacker.get(device_id, plane_id, 0, 0, mstAccept);
      event.mst_final_clear        = gUnpacker.get(device_id, plane_id, 0, 0, finalClear);
      event.mst_consolation_accept = gUnpacker.get(device_id, plane_id, 0, 0, cosolationAccept);
      event.mst_fast_clear         = gUnpacker.get(device_id, plane_id, 0, 0, fastClear);
      event.mst_level2             = gUnpacker.get(device_id, plane_id, 0, 0, level2);
      event.mst_no_decision        = gUnpacker.get(device_id, plane_id, 0, 0, noDecision);

      if( event.mst_accept == 1 ) hard_accept = true;
      HF2( 100, event.mst_accept, event.mst_clear );
    }
  }

  // MsT HR-TDC (TOF)
  {
    static const int device_id = gUnpacker.get_device_id("MsT");
    static const int tof_id    = gUnpacker.get_plane_id("MsT", "TOF");
    static const int sch_id    = gUnpacker.get_plane_id("MsT", "SCH");

    int index = 0;
    for(int seg = 0; seg<NumOfSegTOF; ++seg){
      int mhit = gUnpacker.get_entries(device_id, tof_id, seg, 0, 0);
      for(int m = 0; m<mhit; ++m){
	event.mst_tof[index] = seg+1;
	int tof_tdc = gUnpacker.get(device_id, tof_id, seg, 0, 0, m);
	event.mst_tof_tdc[seg][m] = tof_tdc;

	HF1( 1000+seg+1, tof_tdc );
	if(m == 0) HF1( 102, seg+1 );
	if( event.mst_accept == 1 ) HF1( 1100+seg+1, tof_tdc );
	if( event.mst_clear==1 )    HF1( 1200+seg+1, tof_tdc );

	for(int seg2 = 0; seg2<NumOfSegSCH; ++seg2){
	  int mhit2 = gUnpacker.get_entries(device_id, sch_id, seg, 0, 0);
	  for(int m2 = 0; m2<mhit2; ++m2){
	    //	    soft_accept = gMsT.IsAccept( seg, seg2, tof_tdc ) ? soft_accept & true : false;

	    HF1( 10000+(seg2+1)*100+seg+1, tof_tdc );
	    if( event.mst_accept==1 ) HF1( 20000+(seg2+1)*100+seg+1, tof_tdc );
	  }// for(m2)
	}// for(seg2)
      }// for(m)
      if(mhit) ++index;

    }// for(seg)

    event.mst_ntof = index;
  }

  event.soft_accept = soft_accept;
  HF2( 50, hard_accept, soft_accept );

  // CAMAC SCH Coin
  {
    static const int device_id = gUnpacker.get_device_id("MsT");
    static const int sch_id    = gUnpacker.get_plane_id("MsT", "SCH");
    int index = 0;
    for(int seg = 0; seg<NumOfSegSCH; ++seg){
      int mhit = gUnpacker.get_entries(device_id, sch_id, seg, 0, 0);
      for(int m = 0; m<mhit; ++m){
	event.mst_sch[index] = seg+1;
	int sch_tdc = gUnpacker.get(device_id, sch_id, seg, 0, 0, m);
	event.mst_sch_tdc[seg][m] = sch_tdc;

	HF1( 103, seg );
      }// for(m)

      if(mhit) index++;
    }// for(seg)

    event.mst_nsch = index;
  }

  //TOF
  int tof_nhits=0;
  {
    const HodoRHitContainer &cont=rawData->GetTOFRawHC();
    int nh = cont.size();
    for( int i=0; i<nh; ++i ){
      HodoRawHit *hit = cont[i];
      int seg = hit->SegmentId()+1;
      int Au=hit->GetAdcUp(), Ad=hit->GetAdcDown();
      int Tu=hit->GetTdcUp(), Td=hit->GetTdcDown();
      //Tree
      if( Tu>0 || Td>0 ){
	event.tofhitpat[tof_nhits++]= seg;
      }
      event.tofua[seg-1] = Au;
      event.tofut[seg-1] = Tu;
      event.tofda[seg-1] = Ad;
      event.tofdt[seg-1] = Td;
    }
  }
  event.tofnhits = tof_nhits;

  return true;
}

//______________________________________________________________________________
void
EventMassTrigger::InitializeEvent( void )
{
  event.evnum      = -1;

  event.mst_clear              = -1;
  event.mst_accept             = -1;
  event.mst_final_clear        = -1;
  event.mst_consolation_accept = -1;
  event.mst_fast_clear         = -1;
  event.mst_level2             = -1;
  event.mst_no_decision        = -1;

  event.soft_accept = -1;

  event.mst_ntof   = 0;
  event.mst_nsch   = 0;
  event.tofnhits   = 0;

  for( int i=0; i<NumOfSegTOF; ++i ){
    event.mst_tof[i] = -1;
    for(int m = 0; m<MaxDepth; ++m){
      event.mst_tof_tdc[i][m] = -1;
    }
  }
  for( int i=0; i<NumOfSegSCH; ++i ){
    event.mst_sch[i] = -1;
    for(int m = 0; m<MaxDepth; ++m){
      event.mst_sch_tdc[i][m] = -1;
    }
  }

  for( int it=0; it<NumOfSegTOF; ++it ){
    event.tofhitpat[it] = -1;
    event.tofua[it] = -9999.;
    event.tofda[it] = -9999.;
    event.tofut[it] = -9999.;
    event.tofdt[it] = -9999.;
  }

  for( int it=0; it<NumOfSegTrig; ++it ){
    event.trigpat[it] = -1;
    event.trigflag[it] = -1;
  }
}

//______________________________________________________________________________
bool
EventMassTrigger::ProcessingEnd( void )
{
  tree->Fill();
  return true;
}

//______________________________________________________________________________
VEvent*
ConfMan::EventAllocator( void )
{
  return new EventMassTrigger;
}

//______________________________________________________________________________
namespace
{
  const int NbinHrTdc    = 50000;
  const double MinHrTdc  =      0.;
  const double MaxHrTdc  = 200000.;

  const int NbinLrTdc    = 50;
  const double MinLrTdc  =  0.;
  const double MaxLrTdc  = 50.;
}

//______________________________________________________________________________
bool
ConfMan::InitializeHistograms( void )
{
  HB1( 1, "Status", 20, 0., 20. );
  HB1( 10, "Trigger HitPat", NumOfSegTrig, 0., (double)NumOfSegTrig );
  for( int i=0; i<NumOfSegTrig; ++i ){
    HB1( 11+i, Form("Trigger Flag %d", i+1 ),
	 NumOfSegTrig, 0., (double)NumOfSegTrig );
  }
  HB2( 50, "Hard Flag % Soft Flag", 3, 0., 3., 3, 0., 3. );
  HB1( 80, "BTOF", 300, -5., 5. );
  HB2( 100, "MsT Clear % Accept", 4, -1, 3, 4, -1, 3 );
  HB1( 102, "TOF hitpattern from TDC",
       NumOfSegTOF, 0., (double)NumOfSegTOF );
  HB1( 103, "SCH hitpattern from CoinReg",
       NumOfSegSCH, 0., (double)NumOfSegSCH );
  for( int i=0; i<NumOfSegTOF; ++i ){
    HB1( 1000+i+1, "MsT TOF TDC", NbinHrTdc, MinHrTdc, MaxHrTdc);
    HB1( 1100+i+1, "MsT TOF TDC [Accept]", NbinHrTdc, MinHrTdc, MaxHrTdc );
    HB1( 1200+i+1, "MsT TOF TDC [Clear]",  NbinHrTdc, MinHrTdc, MaxHrTdc );
    for( int j=0; j<NumOfSegSCH; ++j ){
      HB1( 10000+(j+1)*100+i+1,
	   Form("MsT TDC TOF-%d SCH-%d", i+1, j+1 ),
	   NbinHrTdc, MinHrTdc, MaxHrTdc );
      HB1( 20000+(j+1)*100+i+1,
	   Form("MsT TDC TOF-%d SCH-%d [accept]", i+1, j+1 ),
	   NbinHrTdc, MinHrTdc, MaxHrTdc );
    }
  }

  ////////////////////////////////////////////
  //Tree
  HBTree("mst","tree of Mass Trigger");
  tree->Branch("evnum",      &event.evnum,      "evnum/I");
  tree->Branch("trigpat",     event.trigpat,    Form("trigpat[%d]/I", NumOfSegTrig));
  tree->Branch("trigflag",    event.trigflag,   Form("trigflag[%d]/I", NumOfSegTrig));

  tree->Branch("mst_clear",               &event.mst_clear,              "mst_clear/I");
  tree->Branch("mst_accept",              &event.mst_accept,             "mst_accept/I");
  tree->Branch("mst_final_clear",         &event.mst_final_clear,        "mst_final_clear/I");
  tree->Branch("mst_consolation_accept",  &event.mst_consolation_accept, "mst_consolation_accept/I");
  tree->Branch("mst_fast_clear",          &event.mst_fast_clear,         "mst_fast_clear/I");
  tree->Branch("mst_level2",              &event.mst_level2,             "mst_level2/I");
  tree->Branch("mst_mst_no_decision",     &event.mst_no_decision,        "mst_no_decision/I");
  tree->Branch("soft_accept",             &event.soft_accept,            "mst_accept/I");

  tree->Branch("mst_ntof",   &event.mst_ntof,    "mst_ntof/I" );
  tree->Branch("mst_tof_tdc", event.mst_tof_tdc, Form( "mst_tof_tdc[%d][%d]/I", NumOfSegTOF, MaxDepth ) );
  tree->Branch("mst_tof",     event.mst_tof,     Form( "mst_tof[%d]/I", NumOfSegTOF ) );
  tree->Branch("mst_nsch",   &event.mst_nsch,    "mst_nsch/I" );
  tree->Branch("mst_sch",     event.mst_sch,     Form( "mst_sch[%d]/I", NumOfSegSCH ) );
  tree->Branch("mst_sch_tdc", event.mst_sch_tdc, Form( "mst_sch_tdc[%d][%d]/I", NumOfSegSCH, MaxDepth ) );

  // TOF
  tree->Branch("tofnhits",   &event.tofnhits,   "tofnhits/I");
  tree->Branch("tofhitpat",   event.tofhitpat,  "tofhitpat[32]/I");
  tree->Branch("tofua",       event.tofua,      "tofua[32]/D");
  tree->Branch("tofut",       event.tofut,      "tofut[32]/D");
  tree->Branch("tofda",       event.tofda,      "tofda[32]/D");
  tree->Branch("tofdt",       event.tofdt,      "tofdt[32]/D");

  // SCH
  // tree->Branch("schnhits",   &event.schnhits,   "schnhits/I");
  // tree->Branch("schhitpat",   event.schhitpat,  "schhitpat[32]/I");
  // tree->Branch("schua",       event.schua,      "schua[28]/D");
  // tree->Branch("schut",       event.schut,      "schut[28]/D");
  // tree->Branch("schda",       event.schda,      "schda[28]/D");
  // tree->Branch("schdt",       event.schdt,      "schdt[28]/D");

  HPrint();
  return true;
}

//______________________________________________________________________________
bool
ConfMan::InitializeParameterFiles( void )
{
  return
    ( InitializeParameter<DCGeomMan>("DCGEO")         &&
      InitializeParameter<DCDriftParamMan>("DCDRFT")  &&
      InitializeParameter<DCTdcCalibMan>("DCTDC")     &&
      InitializeParameter<HodoParamMan>("HDPRM")      &&
      InitializeParameter<HodoPHCMan>("HDPHC")        &&
      InitializeParameter<MsTParamMan>("MASS")        &&
      InitializeParameter<UserParamMan>("USER")       );
}

//______________________________________________________________________________
bool
ConfMan::FinalizeProcess( void )
{
  return true;
}
