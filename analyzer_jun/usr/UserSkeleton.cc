/**
 *  file: UserSkeleton.cc
 *  date: 2017.04.10
 *
 */

#include <iostream>
#include <sstream>
#include <cmath>

#include "ConfMan.hh"
#include "DetectorID.hh"
#include "RMAnalyzer.hh"
#include "RootHelper.hh"
#include "HodoRawHit.hh"
#include "KuramaLib.hh"
#include "RawData.hh"
#include "UnpackerManager.hh"
#include "VEvent.hh"

namespace
{
  using namespace root;
  const std::string& classname("EventSkeleton");
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
class EventSkeleton : public VEvent
{
private:
  RawData *rawData;

public:
        EventSkeleton( void );
       ~EventSkeleton( void );
  bool  ProcessingBegin( void );
  bool  ProcessingEnd( void );
  bool  ProcessingNormal( void );
  bool  InitializeHistograms( void );
  void  InitializeEvent( void );
};

//______________________________________________________________________________
EventSkeleton::EventSkeleton( void )
  : VEvent(),
    rawData(0)
{
}

//______________________________________________________________________________
EventSkeleton::~EventSkeleton( void )
{
  if (rawData) delete rawData;
}

//______________________________________________________________________________
struct Event
{
  int runnum;
  int evnum;
  int spill;
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
EventSkeleton::ProcessingBegin( void )
{
  InitializeEvent();
  return true;
}

//______________________________________________________________________________
bool
EventSkeleton::ProcessingNormal( void )
{
  // rawData = new RawData;
  // rawData->DecodeHits();

  gRM.Decode();

  event.runnum = gRM.RunNumber();
  event.evnum  = gRM.EventNumber();
  event.spill  = gRM.SpillNumber();

  for( int i=0; i<100; ++i ){
    HF1( i, (double)i );
  }

  return true;
}

//______________________________________________________________________________
bool
EventSkeleton::ProcessingEnd( void )
{
  tree->Fill();
  return true;
}

//______________________________________________________________________________
void
EventSkeleton::InitializeEvent( void )
{
  event.evnum = -1;
}

//______________________________________________________________________________
VEvent*
ConfMan::EventAllocator( void )
{
  return new EventSkeleton;
}

//______________________________________________________________________________
namespace
{
  const int    NBin = 100;
  const double Min  =   0.;
  const double Max  = 100.;
}

//______________________________________________________________________________
bool
ConfMan::InitializeHistograms( void )
{
  for( int i=0; i<100; ++i ){
    HB1( i, Form("hist %d", i ), 100, 0., 100. );
  }

  HBTree("skeleton","tree of Skeleton");
  tree->Branch("runnum", &event.runnum, "runnum/I");
  tree->Branch("evnum",  &event.evnum,  "evnum/I");
  tree->Branch("spill",  &event.spill,  "spill/I");

  HPrint();
  return true;
}

//______________________________________________________________________________
bool
ConfMan::InitializeParameterFiles( void )
{
  return
    ( InitializeParameter<DCGeomMan>("DCGEO")    &&
      InitializeParameter<HodoParamMan>("HDPRM") );
}

//______________________________________________________________________________
bool
ConfMan::FinalizeProcess( void )
{
  return true;
}
