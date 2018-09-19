/**
 *  file: UserVMECalib.cc
 *  date: 2017.04.10
 *
 */

#include <iostream>
#include <sstream>
#include <cmath>

#include "RMAnalyzer.hh"
#include "ConfMan.hh"
#include "RootHelper.hh"
#include "DetectorID.hh"
#include "RawData.hh"
#include "HodoRawHit.hh"
#include "UserParamMan.hh"
#include "VEvent.hh"

namespace
{
  using namespace root;
  const std::string& class_name("EventVmeCalib");
  RMAnalyzer& gRM = RMAnalyzer::GetInstance();
}

//_____________________________________________________________________
VEvent::VEvent( void )
{
}

//_____________________________________________________________________
VEvent::~VEvent( void )
{
}

//______________________________________________________________________________
class EventVMECalib : public VEvent
{
private:
  RawData      *rawData;

public:
        EventVMECalib( void );
       ~EventVMECalib( void );
  bool  ProcessingBegin( void );
  bool  ProcessingEnd( void );
  bool  ProcessingNormal( void );
  bool  InitializeHistograms( void );
  void  InitializeEvent( void );
};

//_____________________________________________________________________
EventVMECalib::EventVMECalib( void )
  : VEvent(),
    rawData(0)
{
}

//_____________________________________________________________________
EventVMECalib::~EventVMECalib( void )
{
  if( rawData ) delete rawData;
}

//_____________________________________________________________________
struct Event
{
  int evnum;
  int vmenhits;
  int vmehitpat[NumOfPlaneVmeCalib][NumOfSegVmeCalib];
  double vmea[NumOfPlaneVmeCalib][NumOfSegVmeCalib];
  double vmet[NumOfPlaneVmeCalib][NumOfSegVmeCalib];
};

namespace root
{
  Event event;
  TH1   *h[MaxHist];
  TTree *tree;
  enum eDetHid { Hid  = 10000 };
}

//______________________________________________________________________________
bool
EventVMECalib::ProcessingBegin( void )
{
  InitializeEvent();
  return true;
}

//______________________________________________________________________________
bool
EventVMECalib::ProcessingNormal( void )
{
  static const std::string func_name("["+class_name+"::"+__func__+"()]");

  rawData = new RawData;
  // rawData->DecodeHits();
  rawData->DecodeCalibHits();

  gRM.Decode();

  int evnum = gRM.EventNumber();
  event.evnum = evnum;

  HF1(1, 0);

  HF1(1, 1);

  // VmeCalib
  {
    int nhits = 0;
    const HodoRHitContainer &cont = rawData->GetVmeCalibRawHC();
    int nh = cont.size();
    HF1( Hid +0, double(nh) );
    for( int i=0; i<nh; ++i ){
      HodoRawHit *hit = cont[i];
      int plane = hit->PlaneId()+1;
      int seg   = hit->SegmentId()+1;
      HF1( Hid*plane +1, seg-0.5 );
      int A = hit->GetAdcUp();
      int T = hit->GetTdcUp();
      HF2( Hid*plane +3, seg-0.5, A );
      HF2( Hid*plane +4, seg-0.5, T );

      //Tree
      event.vmea[plane-1][seg-1] = A;
      event.vmet[plane-1][seg-1] = T;
      if( T>0 ) event.vmehitpat[plane-1][nhits++] = seg;
      //Up
      HF1( Hid*plane +100*seg +1, double(A) );
      if( T>0 ){
	HF1( Hid*plane +100*seg +2, double(T) );
	HF1( Hid*plane +100*seg +3, double(A) );
      }
      else{
	HF1( Hid*plane +100*seg +4, double(A) );
      }
      //HitPat
      if( T>0 ){
	++nhits; HF1( Hid*plane +2, seg-0.5 );
      }
    }
    HF1( Hid +2, double(nh) );
    event.vmenhits = nhits;
  }

  return true;
}

//______________________________________________________________________________
bool
EventVMECalib::ProcessingEnd( void )
{
  tree->Fill();
  return true;
}

//______________________________________________________________________________
void
EventVMECalib::InitializeEvent( void )
{
  event.evnum     = 0;
  event.vmenhits = 0;

  for( int it=0; it<NumOfPlaneVmeCalib; ++it ){
    for( int that=0; that<NumOfSegVmeCalib; ++that ){
      event.vmehitpat[it][that] = -1;
      event.vmea[it][that]      = -999.;
      event.vmet[it][that]      = -999.;
    }
  }

}

//______________________________________________________________________________
VEvent*
ConfMan::EventAllocator( void )
{
  return new EventVMECalib;
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
}

//______________________________________________________________________________
bool
ConfMan::InitializeHistograms( void )
{
  HB1(  1, "Status", 20, 0., 20. );

  // VmeCalib
  HB1( Hid +0, "#Hits VmeCalib", NumOfSegVmeCalib+1, 0., double(NumOfSegVmeCalib+1) );
  for( int p=1; p<=NumOfPlaneVmeCalib; ++p ){
    HB1( Hid*p +1, Form( "Hitpat VmeCalib-%d", p ),
	 NumOfSegVmeCalib, 0., double(NumOfSegVmeCalib) );
    HB1( Hid*p +2, Form( "Hitpat VmeCalib-%d (w/T)", p ),
	 NumOfSegVmeCalib, 0., double(NumOfSegVmeCalib) );
  }

  for( int p=1; p<=NumOfPlaneVmeCalib; ++p ){
    HB2( Hid*p +3, Form( "VmeCalib-%d Adc%%Ch", p ),
	 NumOfSegVmeCalib, 0., double(NumOfSegVmeCalib), NbinAdc, MinAdc, MaxAdc );
    HB2( Hid*p +4, Form( "VmeCalib-%d Tdc%%Ch", p ),
	 NumOfSegVmeCalib, 0., double(NumOfSegVmeCalib), NbinTdc, MinTdc, MaxTdc );

    for( int i=1; i<=NumOfSegVmeCalib; ++i ){
      HB1( Hid*p +100*i +1, Form( "VmeCalib-%d ch%02d Adc", p, i ), NbinAdc, MinAdc, MaxAdc );
      HB1( Hid*p +100*i +2, Form( "VmeCalib-%d ch%02d Tdc", p, i ), NbinTdc, MinTdc, MaxTdc );
      HB1( Hid*p +100*i +3, Form( "VmeCalib-%d ch%02d Adc(w/Tdc)", p, i ), NbinAdc, MinAdc, MaxAdc );
      HB1( Hid*p +100*i +4, Form( "VmeCalib-%d ch%02d Adc(w/oTdc)", p, i ), NbinAdc, MinAdc, MaxAdc );
    }
  }

  ////////////////////////////////////////////
  //Tree
  HBTree("tree","tree of Counter");
  tree->Branch("evnum",     &event.evnum,     "evnum/I");
  tree->Branch("vmenhits",  &event.vmenhits,  "vmenhits/I");
  tree->Branch("vmehitpat",  event.vmehitpat, Form("vmehitpat[%d][%d]/I",
						   NumOfPlaneVmeCalib, NumOfSegVmeCalib));
  tree->Branch("vmea",       event.vmea,      Form("vmea[%d][%d]/D",
						   NumOfPlaneVmeCalib, NumOfSegVmeCalib));
  tree->Branch("vmet",       event.vmet,      Form("vmet[%d][%d]/D",
						   NumOfPlaneVmeCalib, NumOfSegVmeCalib));

  return true;
}

//______________________________________________________________________________
bool
ConfMan::InitializeParameterFiles( void )
{
  return InitializeParameter<UserParamMan>("USER");
}

//______________________________________________________________________________
bool
ConfMan::FinalizeProcess( void )
{
  return true;
}
