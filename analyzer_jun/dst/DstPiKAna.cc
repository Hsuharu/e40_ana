/**
 *  file: DstPiKAna.cc
 *  date: 2017.04.10
 *
 */

#include <cmath>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>

#include <filesystem_util.hh>

#include "CatchSignal.hh"
#include "ConfMan.hh"
#include "RootHelper.hh"
#include "DatabasePDG.hh"
#include "DetectorID.hh"
#include "RawData.hh"
#include "DCRawHit.hh"
#include "KuramaLib.hh"
#include "K18TrackD2U.hh"
#include "FiberCluster.hh"
#include "NuclearMass.hh"
#include "MathTools.hh"
#include "MsTParamMan.hh"
#include "UserParamMan.hh"

#include "DstHelper.hh"

namespace
{
  using namespace root;
  using namespace dst;
  const std::string& class_name("DstPiKAna");
  ConfMan&            gConf = ConfMan::GetInstance();
//  const DCGeomMan&    gGeom = DCGeomMan::GetInstance();
  // const MsTParamMan&  gMsT  = MsTParamMan::GetInstance();
  const UserParamMan& gUser = UserParamMan::GetInstance();
}

namespace dst
{
  enum kArgc
    {
      kProcess, kConfFile,
      kKuramaTracking, kK18Tracking, kHodoscope, kEasiroc,
      kOutFile, nArgc
    };
  std::vector<TString> ArgName =
    { "[Process]", "[ConfFile]", "[KuramaTracking]",
      "[K18Tracking]", "[Hodoscope]", "[Easiroc]",
      "[OutFile]" };
  std::vector<TString> TreeName =
    { "", "", "kurama", "k18track", "hodo", "ea0c", "" };
  std::vector<TFile*> TFileCont;
  std::vector<TTree*> TTreeCont;

  const double pB_offset   = 1.000;
  const double pS_offset   = 1.000;
  const double pK18_offset = 0.000;
  const double pKURAMA_offset = 0.000;
  const double x_off = 0.000;
  const double y_off = 0.000;
  const double u_off = 0.000;
  const double v_off = 0.000;
}

//_____________________________________________________________________
struct Event
{
  int runnum;
  int evnum;
  int spill;

  //Trigger
  int trigpat[NumOfSegTrig];
  int trigflag[NumOfSegTrig];

  //Hodoscope
  int    nhBh1;
  int    csBh1[NumOfSegBH1];
  double Bh1Seg[NumOfSegBH1];
  double tBh1[NumOfSegBH1];
  double dtBh1[NumOfSegBH1];
  double deBh1[NumOfSegBH1];
  double btof[NumOfSegBH1];

  int    nhBh2;
  int    csBh2[NumOfSegBH2];
  double Bh2Seg[NumOfSegBH2];
  double tBh2[NumOfSegBH2];
  double t0Bh2[NumOfSegBH2];
  double dtBh2[NumOfSegBH2];
  double deBh2[NumOfSegBH2];

  int    nhTof;
  int    csTof[NumOfSegTOF];
  double TofSeg[NumOfSegTOF];
  double tTof[NumOfSegTOF];
  double dtTof[NumOfSegTOF];
  double deTof[NumOfSegTOF];

  //Fiber
  int    nhBft;
  int    csBft[NumOfSegBFT];
  double tBft[NumOfSegBFT];
  double wBft[NumOfSegBFT];
  double BftPos[NumOfSegBFT];
  double BftSeg[NumOfSegBFT];
  int    nhSch;
  int    csSch[NumOfSegSCH];
  double tSch[NumOfSegSCH];
  double wSch[NumOfSegSCH];
  double SchPos[NumOfSegSCH];
  double SchSeg[NumOfSegSCH];
  double delta_x[NumOfSegSCH];
  double delta_seg[NumOfSegSCH];
  
  int    nhSftX;
  double SftXSeg[NumOfSegSFT_X];

  //DC Beam
  int ntBcOut;
  int nlBcOut;
  int nhBcOut[MaxHits];
  double chisqrBcOut[MaxHits];
  double x0BcOut[MaxHits];
  double y0BcOut[MaxHits];
  double u0BcOut[MaxHits];
  double v0BcOut[MaxHits];
  double xtgtBcOut[MaxHits];
  double ytgtBcOut[MaxHits];
  double xbh2BcOut[MaxHits];
  double ybh2BcOut[MaxHits];

  int    ntK18;
  int    nhK18[MaxHits];
  double chisqrK18[MaxHits];
  double pK18[MaxHits];
  double xtgtK18[MaxHits];
  double ytgtK18[MaxHits];
  double utgtK18[MaxHits];
  double vtgtK18[MaxHits];
  double thetaK18[MaxHits];

  //DC KURAMA
  int ntSdcIn;
  int nlSdcIn;
  int nhSdcIn[MaxHits];
  double chisqrSdcIn[MaxHits];
  double x0SdcIn[MaxHits];
  double y0SdcIn[MaxHits];
  double u0SdcIn[MaxHits];
  double v0SdcIn[MaxHits];

  int ntSdcOut;
  int nlSdcOut;
  int nhSdcOut[MaxHits];
  double chisqrSdcOut[MaxHits];
  double u0SdcOut[MaxHits];
  double v0SdcOut[MaxHits];
  double x0SdcOut[MaxHits];
  double y0SdcOut[MaxHits];

  int    ntKurama;
  int    nhKurama[MaxHits];
  double chisqrKurama[MaxHits];
  double stof[MaxHits];
  double path[MaxHits];
  double pKurama[MaxHits];
  double qKurama[MaxHits];
  double m2[MaxHits];
  double xtgtKurama[MaxHits];
  double ytgtKurama[MaxHits];
  double utgtKurama[MaxHits];
  double vtgtKurama[MaxHits];
  double thetaKurama[MaxHits];
  double xtofKurama[MaxHits];
  double ytofKurama[MaxHits];
  double utofKurama[MaxHits];
  double vtofKurama[MaxHits];
  double tofsegKurama[MaxHits];
  double sftxsegKurama;
  double vpx[NumOfLayersVP*MaxHits];
  double vpy[NumOfLayersVP*MaxHits];
  double vpseg[NumOfLayersVP];

  //Reaction
  int    nPi;
  int    nK;
  int    nPiK;
  double vtx[MaxHits];
  double vty[MaxHits];
  double vtz[MaxHits];
  double closeDist[MaxHits];
  double theta[MaxHits];
  double MissMass[MaxHits];
  double MissMassCorr[MaxHits];
  double MissMassCorrDE[MaxHits];
  double thetaCM[MaxHits];
  double costCM[MaxHits];

  double xpi[MaxHits];
  double ypi[MaxHits];
  double upi[MaxHits];
  double vpi[MaxHits];
  double xk[MaxHits];
  double yk[MaxHits];
  double uk[MaxHits];
  double vk[MaxHits];

  double pOrg[MaxHits];
  double pCalc[MaxHits];
  double pCorr[MaxHits];
  double pCorrDE[MaxHits];
};

//_____________________________________________________________________
struct Src
{
  int runnum;
  int evnum;
  int spill;

  //Trigger
  int trigpat[NumOfSegTrig];
  int trigflag[NumOfSegTrig];

  //Hodoscope
  int    nhBh1;
  int    csBh1[NumOfSegBH1];
  double Bh1Seg[NumOfSegBH1];
  double tBh1[NumOfSegBH1];
  double dtBh1[NumOfSegBH1];
  double deBh1[NumOfSegBH1];
  double btof[NumOfSegBH1];

  int    nhBh2;
  int    csBh2[NumOfSegBH2];
  double Bh2Seg[NumOfSegBH2];
  double tBh2[NumOfSegBH2];
  double t0Bh2[NumOfSegBH2];
  double dtBh2[NumOfSegBH2];
  double deBh2[NumOfSegBH2];

  double Time0Seg;
  double deTime0;
  double Time0;
  double CTime0;

  int    nhTof;
  int    csTof[NumOfSegTOF];
  double TofSeg[NumOfSegTOF];
  double tTof[NumOfSegTOF];
  double dtTof[NumOfSegTOF];
  double deTof[NumOfSegTOF];

  //Fiber
  int    nhBft;
  int    csBft[NumOfSegBFT];
  double tBft[NumOfSegBFT];
  double wBft[NumOfSegBFT];
  double BftPos[NumOfSegBFT];
  int    nhSch;
  // int    sch_hitpat[NumOfSegSCH];
  int    csSch[NumOfSegSCH];
  double tSch[NumOfSegSCH];
  double wSch[NumOfSegSCH];
  double SchPos[NumOfSegSCH];
  double SchSeg[NumOfSegSCH];
  int    nhSftX;
  double SftXSeg[NumOfSegSFT_X];
  int    nhFbh;

  //DC Beam
  int ntBcOut;
  int nlBcOut;
  int nhBcOut[MaxHits];
  double chisqrBcOut[MaxHits];
  double x0BcOut[MaxHits];
  double y0BcOut[MaxHits];
  double u0BcOut[MaxHits];
  double v0BcOut[MaxHits];
  double xtgtBcOut[MaxHits];
  double ytgtBcOut[MaxHits];
  double xbh2BcOut[MaxHits];
  double ybh2BcOut[MaxHits];

  int    ntK18;
  int    nhK18[MaxHits];
  double chisqrK18[MaxHits];
  double pK18[MaxHits];
  double xtgtK18[MaxHits];
  double ytgtK18[MaxHits];
  double utgtK18[MaxHits];
  double vtgtK18[MaxHits];
  double thetaK18[MaxHits];

  //DC KURAMA
  int much;
  int ntSdcIn;
  int nlSdcIn;
  int nhSdcIn[MaxHits];
  double chisqrSdcIn[MaxHits];
  double x0SdcIn[MaxHits];
  double y0SdcIn[MaxHits];
  double u0SdcIn[MaxHits];
  double v0SdcIn[MaxHits];

  int ntSdcOut;
  int nlSdcOut;
  int nhSdcOut[MaxHits];
  double chisqrSdcOut[MaxHits];
  double u0SdcOut[MaxHits];
  double v0SdcOut[MaxHits];
  double x0SdcOut[MaxHits];
  double y0SdcOut[MaxHits];

  int    ntKurama;
  int    nhKurama[MaxHits];
  double chisqrKurama[MaxHits];
  double stof[MaxHits];
  double path[MaxHits];
  double pKurama[MaxHits];
  double qKurama[MaxHits];
  double m2[MaxHits];
  double xtgtKurama[MaxHits];
  double ytgtKurama[MaxHits];
  double utgtKurama[MaxHits];
  double vtgtKurama[MaxHits];
  double thetaKurama[MaxHits];
  double xtofKurama[MaxHits];
  double ytofKurama[MaxHits];
  double utofKurama[MaxHits];
  double vtofKurama[MaxHits];
  double tofsegKurama[MaxHits];
  double sftxsegKurama;
  double vpx[NumOfLayersVP];
  double vpy[NumOfLayersVP];
  double vpseg[NumOfLayersVP];
};

//_____________________________________________________________________
namespace root
{
  Event  event;
  Src    src;
  TH1   *h[MaxHist];
  TTree *tree;
}

//_____________________________________________________________________
int
main( int argc, char **argv )
{
  std::vector<std::string> arg( argv, argv+argc );

  if( !CheckArg( arg ) )
    return EXIT_FAILURE;
  if( !DstOpen( arg ) )
    return EXIT_FAILURE;
  if( !gConf.Initialize( arg[kConfFile] ) )
    return EXIT_FAILURE;

  int nevent = GetEntries( TTreeCont );

  CatchSignal::Set();

  int ievent = 0;
  for( ; ievent<nevent && !CatchSignal::Stop(); ++ievent ){
    InitializeEvent();
    if( DstRead( ievent ) ) tree->Fill();
  }

  std::cout << "#D Event Number: " << std::setw(6)
	    << ievent << std::endl;

  DstClose();

  return EXIT_SUCCESS;
}

//_____________________________________________________________________
bool
dst::InitializeEvent( void )
{
  event.runnum     = 0;
  event.evnum      = 0;
  event.spill      = 0;

  //Trigger
  for( int it=0; it<NumOfSegTrig; ++it ){
    event.trigpat[it]  = -1;
    event.trigflag[it] = -1;
  }

  //Hodoscope
  event.nhBh2  = 0;
  event.nhBh1  = 0;
  event.nhTof  = 0;

  for( int it=0; it<NumOfSegBH1; it++ ){
    event.csBh1[it]  = 0;
    event.Bh1Seg[it] = -1;
    event.tBh1[it]   = -9999.;
    event.dtBh1[it]  = -9999.;
    event.deBh1[it]  = -9999.;
    event.btof[it]   = -9999.;
  }
  for( int it=0; it<NumOfSegBH2; it++ ){
    event.csBh2[it]  = 0;
    event.Bh2Seg[it] = -1;
    event.tBh2[it]   = -9999.;
    event.t0Bh2[it]  = -9999.;
    event.dtBh2[it]  = -9999.;
    event.deBh2[it]  = -9999.;
  }
  for( int it=0; it<NumOfSegTOF; it++ ){
    event.csTof[it]  = 0;
    event.TofSeg[it] = -1;
    event.tTof[it]   = -9999.;
    event.dtTof[it]  = -9999.;
    event.deTof[it]  = -9999.;
  }

  //Fiber
  event.nhBft = 0;
  event.nhSch = 0;
  for( int it=0; it<NumOfSegBFT; it++ ){
    event.csBft[it] = -999;
    event.tBft[it]  = -999.;
    event.wBft[it]   = -999.;
    event.BftPos[it]  = -999.;
  }
  for( int it=0; it<NumOfSegSCH; it++ ){
    event.csSch[it] = -999;
    event.tSch[it]  = -999.;
    event.wSch[it]   = -999.;
    event.SchPos[it]  = -999.;
    event.SchSeg[it]  = -999.;
    event.delta_x[it]  = -999.;
    event.delta_seg[it]  = -999.;
  }
  event.nhSftX = 0;
  for( int it=0; it<NumOfSegSFT_X; it++ ){
    event.SftXSeg[it]  = -999.;
  }

  //DC
  event.nlBcOut  = 0;
  event.nlSdcIn  = 0;
  event.nlSdcOut = 0;
  event.ntBcOut  = 0;
  event.ntSdcIn  = 0;
  event.ntSdcOut = 0;
  event.ntK18    = 0;
  event.ntKurama = 0;

  //Beam DC
  for( int it=0; it<MaxHits; it++){
    event.nhBcOut[it]     = 0;
    event.chisqrBcOut[it] = -1.0;
    event.x0BcOut[it] = -9999.0;
    event.y0BcOut[it] = -9999.0;
    event.u0BcOut[it] = -9999.0;
    event.v0BcOut[it] = -9999.0;

    event.xtgtBcOut[it] = -9999.0;
    event.ytgtBcOut[it] = -9999.0;
    event.xbh2BcOut[it] = -9999.0;
    event.ybh2BcOut[it] = -9999.0;
  }

  for( int it=0; it<MaxHits; it++){
    event.nhK18[it]     = 0;
    event.chisqrK18[it] = -1.0;
    event.xtgtK18[it] = -9999.;
    event.ytgtK18[it] = -9999.;
    event.utgtK18[it] = -9999.;
    event.vtgtK18[it] = -9999.;
    event.pK18[it]    = -9999.;
    event.thetaK18[it] = -9999.;
  }

  //KURAMA DC
  for( int it=0; it<MaxHits; it++){
    event.nhSdcIn[it]     = 0;
    event.chisqrSdcIn[it] = -1.;
    event.x0SdcIn[it] = -9999.;
    event.y0SdcIn[it] = -9999.;
    event.u0SdcIn[it] = -9999.;
    event.v0SdcIn[it] = -9999.;

    event.nhSdcOut[it]     = 0;
    event.chisqrSdcOut[it] = -1.;
    event.u0SdcOut[it] = -9999.;
    event.v0SdcOut[it] = -9999.;
    event.x0SdcOut[it] = -9999.;
    event.y0SdcOut[it] = -9999.;

    event.nhKurama[it]     = 0;
    event.chisqrKurama[it] = -1.;
    event.xtgtKurama[it]   = -9999.;
    event.ytgtKurama[it]   = -9999.;
    event.utgtKurama[it]   = -9999.;
    event.vtgtKurama[it]   = -9999.;
    event.pKurama[it]      = -9999.;
    event.qKurama[it]      = -9999.;
    event.stof[it]         = -9999.;
    event.path[it]         = -9999.;
    event.m2[it]           = -9999.;
    event.thetaKurama[it]  = -9999.;
    event.xtofKurama[it]   = -9999.;
    event.ytofKurama[it]   = -9999.;
    event.utofKurama[it]   = -9999.;
    event.vtofKurama[it]   = -9999.;
    event.tofsegKurama[it] = -9999.;
  }

  event.sftxsegKurama = -9999.;
  
  for ( int l = 0; l < NumOfLayersVP; ++l ) {
      event.vpx[l] = -9999.;
      event.vpy[l] = -9999.;
      event.vpseg[l] = -9999.;
  }

  //Reaction
  event.nPi = 0;
  event.nK = 0;
  event.nPiK = 0;

  for( int it=0; it<MaxHits; ++it ){
    event.vtx[it]       = -9999.;
    event.vty[it]       = -9999.;
    event.vtz[it]       = -9999.;
    event.closeDist[it] = -9999.;
    event.theta[it]     = -9999.;
    event.thetaCM[it]   = -9999.;
    event.costCM[it]    = -9999.;
    event.MissMass[it]  = -9999.;
    event.MissMassCorr[it]  = -9999.;
    event.MissMassCorrDE[it]  = -9999.;

    event.xpi[it] = -9999.0;
    event.ypi[it] = -9999.0;
    event.upi[it] = -9999.0;
    event.vpi[it] = -9999.0;
    event.xk[it] = -9999.0;
    event.yk[it] = -9999.0;
    event.uk[it] = -9999.0;
    event.vk[it] = -9999.0;
    event.pOrg[it] = -9999.0;
    event.pCalc[it] = -9999.0;
    event.pCorr[it] = -9999.0;
    event.pCorrDE[it] = -9999.0;
  }

  return true;
}

//_____________________________________________________________________
bool
dst::DstOpen( std::vector<std::string> arg )
{
  int open_file = 0;
  int open_tree = 0;
  for( std::size_t i=0; i<nArgc; ++i ){
    if( i==kProcess || i==kConfFile || i==kOutFile ) continue;
    open_file += OpenFile( TFileCont[i], arg[i] );
    open_tree += OpenTree( TFileCont[i], TTreeCont[i], TreeName[i] );
  }

  if( open_file!=open_tree || open_file!=nArgc-3 )
    return false;
  if( !CheckEntries( TTreeCont ) )
    return false;

  TFileCont[kOutFile] = new TFile( arg[kOutFile].c_str(), "recreate" );

  return true;
}

//_____________________________________________________________________
bool
dst::DstRead( int ievent )
{
  static const std::string func_name("["+class_name+"::"+__func__+"]");

  static const double OffsetToF  = gUser.GetParameter("OffsetToF");

  static const double KaonMass    = pdg::KaonMass();
  static const double PionMass    = pdg::PionMass();
  static const double ProtonMass  = pdg::ProtonMass();
  static const double SigmaNMass  = pdg::SigmaNMass();

  if( ievent%10000==0 ){
    std::cout << "#D " << func_name << " Event Number: "
	      << std::setw(6) << ievent << std::endl;
  }

  GetEntry(ievent);

  event.runnum   = src.runnum;
  event.evnum    = src.evnum;
  event.spill    = src.spill;

  event.ntBcOut  = src.ntBcOut;
  event.ntSdcIn  = src.ntSdcIn;
  event.ntSdcOut = src.ntSdcOut;
  event.ntKurama = src.ntKurama;
  event.ntK18    = src.ntK18;
  event.nhBft    = src.nhBft;
  event.nhBh1    = src.nhBh1;
  event.nhBh2    = src.nhBh2;
  event.nhSch    = src.nhSch;
  event.nhSftX    = src.nhSftX;
  event.nhTof    = src.nhTof;

  const int ntBcOut  = event.ntBcOut;
  const int ntSdcIn  = event.ntSdcIn;
  const int ntSdcOut = event.ntSdcOut;
  const int ntKurama = event.ntKurama;
  const int ntK18    = event.ntK18;
  const int nhBft    = event.nhBft;
  const int nhBh1    = event.nhBh1;
  const int nhBh2    = event.nhBh2;
  const int nhSch    = event.nhSch;
  const int nhSftX    = event.nhSftX;
  const int nhTof    = event.nhTof;

#if 0
  std::cout << "#D DebugPrint" << std::endl
	    << " event  : " << std::setw(6) << ievent   << std::endl
	    << " BcOut  : " << std::setw(6) << ntBcOut  << std::endl
	    << " SdcIn  : " << std::setw(6) << ntSdcIn  << std::endl
	    << " SdcOut : " << std::setw(6) << ntSdcOut << std::endl
	    << " Kurama : " << std::setw(6) << ntKurama << std::endl
	    << " K18    : " << std::setw(6) << ntK18    << std::endl
	    << " BFT    : " << std::setw(6) << nhBft    << std::endl
	    << " BH1    : " << std::setw(6) << nhBh1    << std::endl
	    << " BH2    : " << std::setw(6) << nhBh2    << std::endl
	    << " SCH    : " << std::setw(6) << nhSch    << std::endl
	    << " TOF    : " << std::setw(6) << nhTof    << std::endl
	    << std::endl;
#endif

  // TFlag
  for(int i=0;i<NumOfSegTrig;++i){
    int tdc = src.trigflag[i];
    if( tdc<=0 ) continue;
    event.trigpat[i]  = i + 1;
    event.trigflag[i] = tdc;
  }

  HF1( 1, 0. );

  // if( event.ntKurama==0 ) return true;
  // HF1( 1, 1. );
  // if( event.ntK18==0 ) return true;
  // HF1( 1, 2. );
  // if( event.nhBh1==0 ) return true;
  // HF1( 1, 3. );
  // if( event.nhBh2==0 ) return true;
  // HF1( 1, 4. );
  // if( event.nhTof==0 ) return true;
  // HF1( 1, 5. );
  // if( event.nhSch==0 ) return true;
  // HF1( 1, 6. );
  // if( event.nhFbh==0 ) return true;
  // HF1( 1, 7. );

  std::vector <ThreeVector> PiPCont, PiXCont;
  std::vector <ThreeVector> KPCont,  KXCont;

  // BFT
  for( int i=0; i<nhBft; ++i ){
    event.csBft[i]  = src.csBft[i];
    event.tBft[i]   = src.tBft[i];
    event.wBft[i]   = src.wBft[i];
    event.BftPos[i] = src.BftPos[i];
  }

  // BH1
  for( int i=0; i<nhBh1; ++i ){
    event.csBh1[i]  = src.csBh1[i];
    event.Bh1Seg[i] = src.Bh1Seg[i];
    event.tBh1[i]   = src.tBh1[i];
    event.dtBh1[i]  = src.dtBh1[i];
    event.deBh1[i]  = src.deBh1[i];
    event.btof[i]   = src.btof[i];
  }

  // BH2
  double time0 = src.Time0;
  for( int i=0; i<nhBh2; ++i ){
    event.csBh2[i]  = src.csBh2[i];
    event.Bh2Seg[i] = src.Bh2Seg[i];
    event.tBh2[i]   = src.tBh2[i];
    event.t0Bh2[i]  = src.t0Bh2[i];
    event.dtBh2[i]  = src.dtBh2[i];
    event.deBh2[i]  = src.deBh2[i];
  }

  // SCH
  for( int i=0; i<nhSch; ++i ){
    event.csSch[i]  = src.csSch[i];
    event.tSch[i]   = src.tSch[i];
    event.wSch[i]   = src.wSch[i];
    event.SchPos[i] = src.SchPos[i];
    event.SchSeg[i] = src.SchSeg[i];
    event.delta_x[i] = src.vpx[1]-src.SchPos[i];
    event.delta_seg[i] = src.vpseg[1]-src.SchSeg[i];
  }
  for( int i=0; i<nhSftX; ++i ){
    event.SftXSeg[i] = src.SftXSeg[i];
  }

  // TOF
  for( int i=0; i<nhTof; ++i ){
    event.csTof[i]  = src.csTof[i];
    event.TofSeg[i] = src.TofSeg[i];
    event.tTof[i]   = src.tTof[i];
    event.dtTof[i]  = src.dtTof[i];
    event.deTof[i]  = src.deTof[i];
  }

  ////////// BcOut
  event.nlBcOut = src.nlBcOut;
  for( int it=0; it<ntBcOut; ++it ){
    event.nhBcOut[it]     = src.nhBcOut[it];
    event.chisqrBcOut[it] = src.chisqrBcOut[it];
    event.x0BcOut[it]     = src.x0BcOut[it];
    event.y0BcOut[it]     = src.y0BcOut[it];
    event.u0BcOut[it]     = src.u0BcOut[it];
    event.v0BcOut[it]     = src.v0BcOut[it];
  }

  ////////// SdcIn
  event.nlSdcIn = src.nlSdcIn;
  for( int it=0; it<ntSdcIn; ++it ){
    event.nhSdcIn[it]     = src.nhSdcIn[it];
    event.chisqrSdcIn[it] = src.chisqrSdcIn[it];
    event.x0SdcIn[it]     = src.x0SdcIn[it];
    event.y0SdcIn[it]     = src.y0SdcIn[it];
    event.u0SdcIn[it]     = src.u0SdcIn[it];
    event.v0SdcIn[it]     = src.v0SdcIn[it];
  }

  ////////// SdcOut
  event.nlSdcOut = src.nlSdcOut;
  for( int it=0; it<ntSdcOut; ++it ){
    event.nhSdcOut[it]     = src.nhSdcOut[it];
    event.chisqrSdcOut[it] = src.chisqrSdcOut[it];
    event.x0SdcOut[it]     = src.x0SdcOut[it];
    event.y0SdcOut[it]     = src.y0SdcOut[it];
    event.u0SdcOut[it]     = src.u0SdcOut[it];
    event.v0SdcOut[it]     = src.v0SdcOut[it];
  }

  ////////// K+
  for( int itKurama=0; itKurama<ntKurama; ++itKurama ){
    int nh= src.nhKurama[itKurama];
    double chisqr = src.chisqrKurama[itKurama];
    double p = src.pKurama[itKurama];
    double x = src.xtgtKurama[itKurama];
    double y = src.ytgtKurama[itKurama];
    double u = src.utgtKurama[itKurama];
    double v = src.vtgtKurama[itKurama];
    double theta = src.thetaKurama[itKurama];
    double pt = p/std::sqrt(1.+u*u+v*v);
    ThreeVector Pos( x, y, 0. );
    ThreeVector Mom( pt*u, pt*v, pt );
    if( std::isnan( Pos.Mag() ) ) continue;
    //Calibration
    ThreeVector PosCorr( x+x_off, y+y_off, 0. );
    ThreeVector MomCorr( pt*(u+u_off), pt*(v+v_off), pt );
    double path = src.path[itKurama];
    double xt = PosCorr.x();
    double yt = PosCorr.y();
    double zt = PosCorr.z();
    double pCorr = MomCorr.Mag();
    double q  = src.qKurama[itKurama];
    double ut = xt/zt;
    double vt = yt/zt;

    // SdcOut vs TOF
    double TofSegKurama = src.tofsegKurama[itKurama];
    double stof = -9999.;
    double m2   = -9999.;
    // w/  TOF

    bool fl_matching = false;
    for( int j=0; j<nhTof; ++j ){
      double seg = src.TofSeg[j];
      if( seg == TofSegKurama ){
	// event.tTof[i]  = src.tTof[j];
	// event.dtTof[i] = src.dtTof[j];
	// event.deTof[i] = src.deTof[j];
	stof  = src.tTof[j] - time0 + OffsetToF;
	m2 = Kinematics::MassSquare( pCorr, path, stof );
	fl_matching = true;
      }
    }
    if ( !fl_matching ) {
      for( int j=0; j<nhTof; ++j ){
	double seg = src.TofSeg[j];
	if ( seg == TofSegKurama ) { continue; }
	if( std::abs( seg - TofSegKurama ) < 2 ){
	  // event.tTof[i]  = src.tTof[j];
	  // event.dtTof[i] = src.dtTof[j];
	  // event.deTof[i] = src.deTof[j];
	  stof  = src.tTof[j] - time0 + OffsetToF;
	  m2 = Kinematics::MassSquare( pCorr, path, stof );
	}
      }
    }

    // w/o TOF
    // double minres = 1.0e10;
    // for( int j=0; j<nhTof; ++j ){
    //   double seg = src.TofSeg[j];
    //   double res = TofSegKurama - seg;
    //   if( std::abs( res ) < minres && std::abs( res ) < 1. ){
    // 	minres = res;
    // 	stof = src.tTof[j] - time0 + OffsetToF;
    //   }
    // }
    event.nhKurama[itKurama]   = nh;
    event.chisqrKurama[itKurama] = chisqr;
    event.pKurama[itKurama] = p;
    event.qKurama[itKurama] = q;
    event.xtgtKurama[itKurama] = x;
    event.ytgtKurama[itKurama] = y;
    event.utgtKurama[itKurama] = u;
    event.vtgtKurama[itKurama] = v;
    event.thetaKurama[itKurama] = theta;
    event.stof[itKurama] = stof;
    event.path[itKurama] = path;
    event.m2[itKurama] = m2;
    event.tofsegKurama[itKurama] = src.tofsegKurama[itKurama];
    if ( src.ntKurama == 1 ) {
      for ( int l = 0; l < NumOfLayersVP; ++l ) {
        event.vpx[l] = src.vpx[l];
        event.vpy[l] = src.vpy[l];
        event.vpseg[l] = src.vpseg[l];
      }
    event.sftxsegKurama = src.sftxsegKurama;
    }
    HF1( 3202, double(nh) );
    HF1( 3203, chisqr );
    HF1( 3204, xt ); HF1( 3205, yt );
    HF1( 3206, ut ); HF1( 3207, vt );
    HF2( 3208, xt, ut ); HF2( 3209, yt, vt );
    HF2( 3210, xt, yt );
    HF1( 3211, pCorr );
    HF1( 3212, path );

    HF1( 3213, m2 );

    //     double xTof=(clTof->MeanSeg()-7.5)*70.;
    //     double yTof=(clTof->TimeDif())*800./12.;
    //     HF2( 4011, clTof->MeanSeg()-0.5, xtof );
    //     HF2( 4013, clTof->TimeDif(), ytof );
    //     HF1( 4015, xtof-xTof ); HF1( 4017, ytof-yTof );
    //     HF2( 4019, xtof-xTof, ytof-yTof );

    //       double ttof=clTof->CMeanTime()-time0,
    //       HF1( 322, clTof->ClusterSize() );
    //       HF1( 323, clTof->MeanSeg()-0.5 );
    //       HF1( 324, ttof );
    //       HF1( 325, clTof->DeltaE() );
    //       double u0in=trIn->GetU0();
    //       HF2( 4001, u0in, ttof ); HF2( 4003, u0in, ttof+12.5*u0in );
    HF1( 4202, double(nh) );
    HF1( 4203, chisqr );
    HF1( 4204, xt ); HF1( 4205, yt );
    HF1( 4206, ut ); HF1( 4207, vt );
    HF2( 4208, xt, ut ); HF2( 4209, yt, vt );
    HF2( 4210, xt, yt );
    HF1( 4211, pCorr );
    HF1( 4212, path );
    KXCont.push_back( PosCorr );
    KPCont.push_back( MomCorr );
  }

  if( KPCont.size()==0 ) return true;

  HF1( 1, 8. );

  ////////// pi
  for( int itK18=0; itK18<ntK18; ++itK18 ){
    int nh = src.nhK18[itK18];
    double chisqr = src.chisqrK18[itK18];
    //Calibration
    double p = src.pK18[itK18]*pB_offset+pK18_offset;
    double x = src.xtgtK18[itK18];
    double y = src.ytgtK18[itK18];
    double u = src.utgtK18[itK18];
    double v = src.vtgtK18[itK18];
    event.nhK18[itK18]     = nh;
    event.chisqrK18[itK18] = chisqr;
    event.pK18[itK18]      = p;
    event.xtgtK18[itK18]   = x;
    event.ytgtK18[itK18]   = y;
    event.utgtK18[itK18]   = u;
    event.vtgtK18[itK18]   = v;
    // double loss_bh2 = 1.09392e-3;
    // p = p - loss_bh2;
    double pt=p/std::sqrt(1.+u*u+v*v);
    ThreeVector Pos( x, y, 0. );
    ThreeVector Mom( pt*u, pt*v, pt );
    //double xo=trOut->GetX0(), yo=trOut->GetY0();
    HF1( 4104, p );
    HF1( 4105, x ); HF1( 4106, y );
    //HF1( 4107, xo ); HF1( 4108, yo ); HF1( 4109, u ); HF1( 4110, v );

    PiPCont.push_back(Mom); PiXCont.push_back(Pos);
  }

  if( PiPCont.size()==0 ) return true;

  HF1( 1, 9. );

  //MissingMass
  int nPi = PiPCont.size();
  int nK  = KPCont.size();
  event.nPi = nPi;
  event.nK  = nK;
  event.nPiK = nPi*nK;
  HF1( 4101, double(nPi));
  HF1( 4201, double(nK) );
  int npik=0;
  for( int ikp=0; ikp<nK; ++ikp ){
    ThreeVector pkp = KPCont[ikp], xkp = KXCont[ikp];
    for( int ipi=0; ipi<nPi; ++ipi ){
      ThreeVector ppi  = PiPCont[ipi], xpi = PiXCont[ipi];
      ThreeVector vert = Kinematics::VertexPoint( xpi, xkp, ppi, pkp );
      // std::cout << "vertex : " << vert << " " << vert.Mag() << std::endl;
      double closedist = Kinematics::closeDist( xpi, xkp, ppi, pkp );

      double us = pkp.x()/pkp.z(), vs = pkp.y()/pkp.z();
      double ub = ppi.x()/ppi.z(), vb = ppi.y()/ppi.z();
      double cost = ppi*pkp/(ppi.Mag()*pkp.Mag());

      double pk0   = pkp.Mag();
      double pCorr = pk0;

      ThreeVector pkpCorr( pCorr*pkp.x()/pkp.Mag(),
			   pCorr*pkp.y()/pkp.Mag(),
			   pCorr*pkp.z()/pkp.Mag() );

      //      ThreeVector ppiCorrDE = Kinematics::CorrElossIn( ppi, xpi, vert, PionMass );
      //      ThreeVector pkpCorrDE = Kinematics::CorrElossOut( pkpCorr, xkp, vert, KaonMass );

      LorentzVector LvPi( ppi, std::sqrt( PionMass*PionMass+ppi.Mag2() ) );
      //      LorentzVector LvPiCorrDE( ppiCorrDE, sqrt( PionMass*PionMass+ppiCorrDE.Mag2() ) );

      LorentzVector LvKp( pkp, std::sqrt( KaonMass*KaonMass+pkp.Mag2() ) );
      LorentzVector LvKpCorr( pkpCorr, std::sqrt( KaonMass*KaonMass+pkpCorr.Mag2() ) );
      //      LorentzVector LvKpCorrDE( pkpCorrDE, std::sqrt( KaonMass*KaonMass+pkpCorrDE.Mag2() ) );

      LorentzVector LvC( 0., 0., 0., ProtonMass );
      LorentzVector LvCore( 0., 0., 0., 0. );

      LorentzVector LvRc       = LvPi+LvC-LvKp;
      LorentzVector LvRcCorr   = LvPi+LvC-LvKpCorr;
      //      LorentzVector LvRcCorrDE = LvPiCorrDE+LvC-LvKpCorrDE;
      double MisMass       = LvRc.Mag();//-LvC.Mag();
      double MisMassCorr   = LvRcCorr.Mag();//-LvC.Mag();
      //      double MisMassCorrDE = LvRcCorrDE.Mag();//-LvC.Mag();

      //Primary frame
      LorentzVector PrimaryLv = LvPi+LvC;
      double TotalEnergyCM = PrimaryLv.Mag();
      ThreeVector beta( 1/PrimaryLv.E()*PrimaryLv.Vect() );

      //CM
      double TotalMomCM
	= 0.5*std::sqrt(( TotalEnergyCM*TotalEnergyCM
			  -( KaonMass+SigmaNMass )*( KaonMass+SigmaNMass ))
			*( TotalEnergyCM*TotalEnergyCM
			   -( KaonMass-SigmaNMass )*( KaonMass-SigmaNMass )))/TotalEnergyCM;

      double costLab = cost;
      double cottLab = costLab/std::sqrt(1.-costLab*costLab);
      double bt=beta.Mag(), gamma=1./std::sqrt(1.-bt*bt);
      double gbep=gamma*bt*std::sqrt(TotalMomCM*TotalMomCM+KaonMass*KaonMass)/TotalMomCM;
      double a  = gamma*gamma+cottLab*cottLab;
      double bp = gamma*gbep;
      double c  = gbep*gbep-cottLab*cottLab;
      double dd = bp*bp-a*c;

      if( dd<0. ){
	std::cerr << "dd<0." << std::endl;
	dd = 0.;
      }

      double costCM = (std::sqrt(dd)-bp)/a;
      if( costCM>1. || costCM<-1. ){
	std::cerr << "costCM>1. || costCM<-1." << std::endl;
	costCM=-1.;
      }
      double sintCM  = std::sqrt(1.-costCM*costCM);
      double KaonMom = TotalMomCM*sintCM/std::sqrt(1.-costLab*costLab);

      if (npik<MaxHits) {
	event.vtx[npik]=vert.x();
	event.vty[npik]=vert.y();
	event.vtz[npik]=vert.z();
	event.closeDist[npik] = closedist;
	event.theta[npik]     = std::acos(cost)*math::Rad2Deg();
	event.thetaCM[npik]   = std::acos(costCM)*math::Rad2Deg();
	event.costCM[npik]    = costCM;

	event.MissMass[npik]       = MisMass;
	event.MissMassCorr[npik]   = MisMassCorr;
	//	event.MissMassCorrDE[npik] = MisMassCorrDE;
	event.MissMassCorrDE[npik] = 0;

	event.xk[npik] = xkp.x();
	event.yk[npik] = xkp.y();
	event.uk[npik] = us;
	event.vk[npik] = vs;

	event.xpi[npik] = xpi.x();
	event.ypi[npik] = xpi.y();
	event.upi[npik] = ub;
	event.vpi[npik] = vb;
	event.pOrg[npik] = pk0;
	event.pCalc[npik] = KaonMom;
	event.pCorr[npik] = pCorr;
	//	event.pCorrDE[npik] = pkpCorrDE.Mag();
	event.pCorrDE[npik] = 0;
	npik++;
      } else {
	std::cout << "#W npik: "<< npik << " exceeding MaxHits: " << MaxHits << std::endl;
      }

      HF1( 5001, vert.z() );

      HF1( 5002, MisMass );
      HF2( 5011, MisMass, us );
      HF2( 5012, MisMass, vs );
      HF2( 5013, MisMass, ub );
      HF2( 5014, MisMass, vb );
    }
  }

  HF1( 1, 10. );

  //Final Hodoscope histograms
  for( int i=0; i<nhBh2; ++i ){
    HF1( 152, event.csBh2[i] );
    HF1( 153, event.Bh2Seg[i] );
    HF1( 154, event.tBh2[i] );
    HF1( 155, event.deBh2[i] );
  }

  for( int i=0; i<nhBh1; ++i ){
    HF1( 252, event.csBh1[i] );
    HF1( 253, event.Bh1Seg[i] );
    HF1( 254, event.tBh1[i] );
    HF1( 255, event.deBh1[i] );
  }

  for( int i=0; i<nhTof; ++i ){
    HF1( 352, event.csTof[i] );
    HF1( 353, event.TofSeg[i] );
    HF1( 354, event.tTof[i] );
    HF1( 355, event.deTof[i] );
  }

  return true;
}

//_____________________________________________________________________
bool
dst::DstClose( void )
{
  TFileCont[kOutFile]->Write();
  std::cout << "#D Close : " << TFileCont[kOutFile]->GetName() << std::endl;
  TFileCont[kOutFile]->Close();

  const std::size_t n = TFileCont.size();
  for( std::size_t i=0; i<n; ++i ){
    if( TTreeCont[i] ) delete TTreeCont[i];
    if( TFileCont[i] ) delete TFileCont[i];
  }
  return true;
}

//_____________________________________________________________________
bool
ConfMan::InitializeHistograms( void )
{
  HB1( 1, "Status", 60, 0., 60. );

  HB1( 101, "#Clusters BH2",   7, 0., 7. );
  HB1( 102, "ClusterSize BH2", 7, 0., 7. );
  HB1( 103, "HitPat BH2", 10, 0., 10. );
  HB1( 104, "MeanTime BH2", 200, -10., 10. );
  HB1( 105, "Delta-E BH2", 200, -0.5, 4.5 );

  HB1( 112, "ClusterSize BH2", 7, 0., 7. );
  HB1( 113, "HitPat BH2", 10, 0., 10. );
  HB1( 114, "MeanTime BH2", 200, -10., 10. );
  HB1( 115, "Delta-E BH2", 200, -0.5, 4.5 );

  HB1( 122, "ClusterSize BH2 [T0]", 7, 0., 7. );
  HB1( 123, "HitPat BH2 [T0]", 10, 0., 10. );
  HB1( 124, "MeanTime BH2 [T0]", 200, -10., 10. );
  HB1( 125, "Delta-E BH2 [T0]", 200, -0.5, 4.5 );

  HB1( 152, "ClusterSize BH2 [kk]", 7, 0., 7. );
  HB1( 153, "HitPat BH2 [kk]", 10, 0., 10. );
  HB1( 154, "MeanTime BH2 [kk]", 200, -10., 10. );
  HB1( 155, "Delta-E BH2 [kk]", 200, -0.5, 4.5 );

  HB1( 201, "#Clusters BH1",  11, 0., 11. );
  HB1( 202, "ClusterSize BH1",11, 0., 11. );
  HB1( 203, "HitPat BH1", 11, 0., 11. );
  HB1( 204, "MeanTime BH1", 200, -10., 10. );
  HB1( 205, "Delta-E BH1", 200, -0.5, 4.5 );
  HB1( 206, "Beam ToF", 200, -10., 10. );

  HB1( 211, "#Clusters BH1 [pi]",  11, 0., 11. );
  HB1( 212, "ClusterSize BH1 [pi]",11, 0., 11. );
  HB1( 213, "HitPat BH1 [pi]", 11, 0., 11. );
  HB1( 214, "MeanTime BH1 [pi]", 200, -10., 10. );
  HB1( 215, "Delta-E BH1 [pi]", 200, -0.5, 4.5 );

  HB1( 252, "ClusterSize BH1 [kk]",11, 0., 11. );
  HB1( 253, "HitPat BH1 [kk]", 11, 0., 11. );
  HB1( 254, "MeanTime BH1 [kk]", 200, -10., 10. );
  HB1( 255, "Delta-E BH1 [kk]", 200, -0.5, 4.5 );
  HB1( 256, "Beam ToF [kk]", 200, -10., 10. );

  HB1( 301, "#Clusters Tof",  32, 0., 32. );
  HB1( 302, "ClusterSize Tof",32, 0., 32. );
  HB1( 303, "HitPat Tof", 32, 0., 32. );
  HB1( 304, "TimeOfFlight Tof", 500, -50., 100. );
  HB1( 305, "Delta-E Tof", 200, -0.5, 4.5 );

  HB1( 311, "#Clusters Tof [Good]",  32, 0., 32. );
  HB1( 312, "ClusterSize Tof [Good]",32, 0., 32. );
  HB1( 313, "HitPat Tof [Good]", 32, 0., 32. );
  HB1( 314, "TimeOfFlight Tof [Good]", 500, -50., 100. );
  HB1( 315, "Delta-E Tof [Good]", 200, -0.5, 4.5 );

  HB1( 352, "ClusterSize Tof [kk]",32, 0., 32. );
  HB1( 353, "HitPat Tof [kk]", 32, 0., 32. );
  HB1( 354, "TimeOfFlight Tof [kk]", 500, -50., 100. );
  HB1( 355, "Delta-E Tof [kk]", 200, -0.5, 4.5 );
  HB2( 501, "SegLC%SegTOF", 32, 0., 32., 28, 0., 28. );

  HB1( 1001, "#Tracks SdcIn", 10, 0., 10. );
  HB1( 1002, "#Hits SdcIn", 20, 0., 20. );
  HB1( 1003, "Chisqr SdcIn", 200, 0., 100. );
  HB1( 1004, "X0 SdcIn", 500, -200., 200. );
  HB1( 1005, "Y0 SdcIn", 500, -200., 200. );
  HB1( 1006, "U0 SdcIn",  700, -0.35, 0.35 );
  HB1( 1007, "V0 SdcIn",  400, -0.20, 0.20 );
  HB2( 1008, "X0%U0 SdcIn", 120, -200., 200., 100, -0.35, 0.35 );
  HB2( 1009, "Y0%V0 SdcIn", 100, -200., 200., 100, -0.20, 0.20 );
  HB2( 1010, "X0%Y0 SdcIn", 100, -200., 200., 100, -200., 200. );

  HB1( 1101, "#Tracks BcOut", 10, 0., 10. );
  HB1( 1102, "#Hits BcOut", 20, 0., 20. );
  HB1( 1103, "Chisqr BcOut", 200, 0., 100. );
  HB1( 1104, "X0 BcOut", 500, -200., 200. );
  HB1( 1105, "Y0 BcOut", 500, -200., 200. );
  HB1( 1106, "U0 BcOut",  700, -0.35, 0.35 );
  HB1( 1107, "V0 BcOut",  400, -0.20, 0.20 );
  HB2( 1108, "X0%U0 BcOut", 120, -200., 200., 100, -0.35, 0.35 );
  HB2( 1109, "Y0%V0 BcOut", 100, -200., 200., 100, -0.20, 0.20 );
  HB2( 1110, "X0%Y0 BcOut", 100, -200., 200., 100, -200., 200. );
  HB1( 1111, "Xtgt BcOut", 500, -200., 200. );
  HB1( 1112, "Ytgt BcOut", 500, -200., 200. );
  HB2( 1113, "Xtgt%Ytgt BcOut", 100, -200., 200., 100, -200., 200. );

  HB1( 1201, "#Tracks SdcOut", 10, 0., 10. );
  HB1( 1202, "#Hits SdcOut", 20, 0., 20. );
  HB1( 1203, "Chisqr SdcOut", 200, 0., 100. );
  HB1( 1204, "X0 SdcOut", 600, -1200., 1200. );
  HB1( 1205, "Y0 SdcOut", 600, -600., 600. );
  HB1( 1206, "U0 SdcOut",  700, -0.35, 0.35 );
  HB1( 1207, "V0 SdcOut",  400, -0.20, 0.20 );
  HB2( 1208, "X0%U0 SdcOut", 120, -1200., 1200., 100, -0.35, 0.35 );
  HB2( 1209, "Y0%V0 SdcOut", 100,  -600.,  600., 100, -0.20, 0.20 );
  HB2( 1210, "X0%Y0 SdcOut", 100, -1200., 1200., 100, -600., 600. );

  HB1( 2201, "#Tracks K18", 10, 0., 10. );
  HB1( 2202, "#Hits K18", 30, 0., 30. );
  HB1( 2203, "Chisqr K18", 500, 0., 50. );
  HB1( 2204, "P K18", 1000, 0.5, 2.0 );
  HB1( 2251, "#Tracks K18 [Good]", 10, 0., 10. );

  HB1( 3001, "#Tracks Kurama", 10, 0., 10. );
  HB1( 3002, "#Hits Kurama", 30, 0., 30. );
  HB1( 3003, "Chisqr Kurama", 500, 0., 500. );
  HB1( 3004, "Xtgt Kurama", 500, -200., 200. );
  HB1( 3005, "Ytgt Kurama", 500, -100., 100. );
  HB1( 3006, "Utgt Kurama", 400, -0.35, 0.35 );
  HB1( 3007, "Vtgt Kurama", 200, -0.20, 0.20 );
  HB2( 3008, "Xtgt%U Kurama", 100, -200., 200., 100, -0.35, 0.35 );
  HB2( 3009, "Ytgt%V Kurama", 100, -100., 100., 100, -0.20, 0.20 );
  HB2( 3010, "Xtgt%Ytgt Kurama", 100, -200., 200., 100, -100., 100. );
  HB1( 3011, "P Kurama", 200, 0.0, 1.0 );
  HB1( 3012, "PathLength Kurama", 600, 3000., 6000. );
  HB1( 3013, "MassSqr", 600, -1.2, 1.2 );

  HB1( 3101, "#Tracks Kurama [Good]", 10, 0., 10. );
  HB1( 3102, "#Hits Kurama [Good]", 30, 0., 30. );
  HB1( 3103, "Chisqr Kurama [Good]", 500, 0., 500. );
  HB1( 3104, "Xtgt Kurama [Good]", 500, -200., 200. );
  HB1( 3105, "Ytgt Kurama [Good]", 500, -100., 100. );
  HB1( 3106, "Utgt Kurama [Good]", 700, -0.35, 0.35 );
  HB1( 3107, "Vtgt Kurama [Good]", 400, -0.20, 0.20 );
  HB2( 3108, "Xtgt%U Kurama [Good]", 100, -200., 200., 100, -0.35, 0.35 );
  HB2( 3109, "Ytgt%V Kurama [Good]", 100, -100., 100., 100, -0.20, 0.20 );
  HB2( 3110, "Xtgt%Ytgt Kurama [Good]", 100, -200., 200., 100, -100., 100. );
  HB1( 3111, "P Kurama [Good]", 200, 0.0, 1.0 );
  HB1( 3112, "PathLength Kurama [Good]", 600, 3000., 6000. );
  HB1( 3113, "MassSqr", 600, -1.2, 1.2 );

  HB1( 3201, "#Tracks Kurama [Good2]", 10, 0., 10. );
  HB1( 3202, "#Hits Kurama [Good2]", 30, 0., 30. );
  HB1( 3203, "Chisqr Kurama [Good2]", 500, 0., 500. );
  HB1( 3204, "Xtgt Kurama [Good2]", 500, -200., 200. );
  HB1( 3205, "Ytgt Kurama [Good2]", 500, -100., 100. );
  HB1( 3206, "Utgt Kurama [Good2]", 700, -0.35, 0.35 );
  HB1( 3207, "Vtgt Kurama [Good2]", 400, -0.20, 0.20 );
  HB2( 3208, "Xtgt%U Kurama [Good2]", 100, -200., 200., 100, -0.35, 0.35 );
  HB2( 3209, "Ytgt%V Kurama [Good2]", 100, -100., 100., 100, -0.20, 0.20 );
  HB2( 3210, "Xtgt%Ytgt Kurama [Good2]", 100, -200., 200., 100, -100., 100. );
  HB1( 3211, "P Kurama [Good2]", 200, 0.0, 1.0 );
  HB1( 3212, "PathLength Kurama [Good2]", 600, 3000., 6000. );
  HB1( 3213, "MassSqr", 600, -1.2, 1.2 );

  HB1( 4101, "#Tracks K18 [KuramaP]", 10, 0., 10. );
  HB1( 4102, "#Hits K18 [KuramaP]", 30, 0., 30. );
  HB1( 4103, "Chisqr K18 [KuramaP]", 500, 0., 50. );
  HB1( 4104, "P K18 [KuramaP]", 500, 0.5, 2.0 );
  HB1( 4105, "Xtgt K18 [KuramaP]", 500, -200., 200. );
  HB1( 4106, "Ytgt K18 [KuramaP]", 500, -100., 100. );
  HB1( 4107, "Xout K18 [KuramaP]", 500, -200., 200. );
  HB1( 4108, "Yout K18 [KuramaP]", 500, -100., 100. );
  HB1( 4109, "Uout K18 [KuramaP]", 400, -0.35, 0.35 );
  HB1( 4110, "Vout K18 [KuramaP]", 200, -0.20, 0.20 );
  HB1( 4111, "Xin  K18 [KuramaP]", 500, -100., 100. );
  HB1( 4112, "Yin  K18 [KuramaP]", 500, -100., 100. );
  HB1( 4113, "Uin  K18 [KuramaP]", 400, -0.35, 0.35 );
  HB1( 4114, "Vin  K18 [KuramaP]", 200, -0.20, 0.20 );

  HB1( 4201, "#Tracks Kurama [Proton]", 10, 0., 10. );
  HB1( 4202, "#Hits Kurama [Proton]", 30, 0., 30. );
  HB1( 4203, "Chisqr Kurama [Proton]", 500, 0., 500. );
  HB1( 4204, "Xtgt Kurama [Proton]", 500, -200., 200. );
  HB1( 4205, "Ytgt Kurama [Proton]", 500, -100., 100. );
  HB1( 4206, "Utgt Kurama [Proton]", 700, -0.35, 0.35 );
  HB1( 4207, "Vtgt Kurama [Proton]", 400, -0.20, 0.20 );
  HB2( 4208, "Xtgt%U Kurama [Proton]", 100, -200., 200., 100, -0.35, 0.35 );
  HB2( 4209, "Ytgt%V Kurama [Proton]", 100, -100., 100., 100, -0.20, 0.20 );
  HB2( 4210, "Xtgt%Ytgt Kurama [Proton]", 100, -200., 200., 100, -100., 100. );
  HB1( 4211, "P Kurama [Proton]", 200, 0.0, 1.0 );
  HB1( 4212, "PathLength Kurama [Proton]", 600, 3000., 6000. );
  HB1( 4213, "MassSqr", 600, -1.2, 1.2 );

  HB1( 5001, "Zvert [KK]", 1000, -1000., 1000. );
  HB1( 5002, "MissingMass [KK]", 1000, 0.0, 2.0 );

  HB2( 5011, "MissingMass%Us", 200, 0.0, 2.50, 100, -0.40, 0.40 );
  HB2( 5012, "MissingMass%Vs", 200, 0.0, 2.50, 100, -0.20, 0.20 );
  HB2( 5013, "MissingMass%Ub", 200, 0.0, 2.50, 100, -0.30, 0.30 );
  HB2( 5014, "MissingMass%Vb", 200, 0.0, 2.50, 100, -0.10, 0.10 );

  ////////////////////////////////////////////
  //Tree
  HBTree("pik","tree of PiKAna");
  tree->Branch("runnum", &event.runnum, "runnum/I");
  tree->Branch("evnum",  &event.evnum,  "evnum/I");
  tree->Branch("spill",  &event.spill,  "spill/I");
  //Trigger
  tree->Branch("trigpat",   event.trigpat,  Form( "trigpat[%d]/I", NumOfSegTrig ) );
  tree->Branch("trigflag",  event.trigflag, Form( "trigflag[%d]/I", NumOfSegTrig ) );

  //Hodoscope
  tree->Branch("nhBh1",   &event.nhBh1,   "nhBh1/I");
  tree->Branch("csBh1",    event.csBh1,   "csBh1[nhBh1]/I");
  tree->Branch("Bh1Seg",   event.Bh1Seg,  "Bh1Seg[nhBh1]/D");
  tree->Branch("tBh1",     event.tBh1,    "tBh1[nhBh1]/D");
  tree->Branch("dtBh1",    event.dtBh1,   "dtBh1[nhBh1]/D");
  tree->Branch("deBh1",    event.deBh1,   "deBh1[nhBh1]/D");
  tree->Branch("btof",     event.btof,    "btof[nhBh1]/D");

  tree->Branch("nhBh2",   &event.nhBh2,   "nhBh2/I");
  tree->Branch("csBh2",    event.csBh2,   "csBh2[nhBh2]/I");
  tree->Branch("Bh2Seg",   event.Bh2Seg,  "Bh2Seg[nhBh2]/D");
  tree->Branch("tBh2",     event.tBh2,    "tBh2[nhBh2]/D");
  tree->Branch("t0Bh2",    event.t0Bh2,   "t0Bh2[nhBh2]/D");
  tree->Branch("dtBh2",    event.dtBh2,   "dtBh2[nhBh2]/D");
  tree->Branch("deBh2",    event.deBh2,   "deBh2[nhBh2]/D");

  tree->Branch("nhTof",   &event.nhTof,   "nhTof/I");
  tree->Branch("csTof",    event.csTof,   "csTof[nhTof]/I");
  tree->Branch("TofSeg",   event.TofSeg,  "TofSeg[nhTof]/D");
  tree->Branch("tTof",     event.tTof,    "tTof[nhTof]/D");
  tree->Branch("dtTof",    event.dtTof,   "dtTof[nhTof]/D");
  tree->Branch("deTof",    event.deTof,   "deTof[nhTof]/D");

  //Fiber
  tree->Branch("nhBft",  &event.nhBft,  "nhBft/I");
  tree->Branch("csBft",   event.csBft,  "csBft[nhBft]/I");
  tree->Branch("tBft",    event.tBft,   "tBft[nhBft]/D");
  tree->Branch("wBft",    event.wBft,   "wBft[nhBft]/D");
  tree->Branch("BftPos",  event.BftPos, "BftPos[nhBft]/D");
  tree->Branch("nhSch",  &event.nhSch,  "nhSch/I");
  tree->Branch("csSch",   event.csSch,  "csSch[nhSch]/I");
  tree->Branch("tSch",    event.tSch,   "tSch[nhSch]/D");
  tree->Branch("wSch",    event.wSch,   "wSch[nhSch]/D");
  tree->Branch("SchPos",  event.SchPos, "SchPos[nhSch]/D");
  tree->Branch("SchSeg",  event.SchSeg, "SchSeg[nhSch]/D");
  tree->Branch("delta_x", event.delta_x,  "delta_x[nhSch]/D" );
  tree->Branch("delta_seg", event.delta_seg,  "delta_seg[nhSch]/D" );
  tree->Branch("nhSftX",  &event.nhSftX,  "nhSftX/I");
  tree->Branch("SftXSeg",  event.SftXSeg, "SftXSeg[nhSftX]/D");

  //Beam DC
  tree->Branch("nlBcOut",   &event.nlBcOut,     "nlBcOut/I");
  tree->Branch("ntBcOut",   &event.ntBcOut,     "ntBcOut/I");
  tree->Branch("nhBcOut",    event.nhBcOut,     "nhBcOut[ntBcOut]/I");
  tree->Branch("chisqrBcOut",event.chisqrBcOut, "chisqrBcOut[ntBcOut]/D");
  tree->Branch("x0BcOut",    event.x0BcOut,     "x0BcOut[ntBcOut]/D");
  tree->Branch("y0BcOut",    event.y0BcOut,     "y0BcOut[ntBcOut]/D");
  tree->Branch("u0BcOut",    event.u0BcOut,     "u0BcOut[ntBcOut]/D");
  tree->Branch("v0BcOut",    event.v0BcOut,     "v0BcOut[ntBcOut]/D");
  tree->Branch("xtgtBcOut",  event.xtgtBcOut,   "xtgtBcOut[ntBcOut]/D");
  tree->Branch("ytgtBcOut",  event.ytgtBcOut,   "ytgtBcOut[ntBcOut]/D");
  tree->Branch("xbh2BcOut",  event.xbh2BcOut,   "xbh2BcOut[ntBcOut]/D");
  tree->Branch("ybh2BcOut",  event.ybh2BcOut,   "ybh2BcOut[ntBcOut]/D");

  tree->Branch("ntK18",      &event.ntK18,     "ntK18/I");
  tree->Branch("nhK18",       event.nhK18,     "nhK18[ntK18]/I");
  tree->Branch("chisqrK18",   event.chisqrK18, "chisqrK18[ntK18]/D");
  tree->Branch("pK18",        event.pK18,      "pK18[ntK18]/D");
  tree->Branch("xtgtK18",     event.xtgtK18,   "xtgtK18[ntK18]/D");
  tree->Branch("ytgtK18",     event.ytgtK18,   "ytgtK18[ntK18]/D");
  tree->Branch("utgtK18",     event.utgtK18,   "utgtK18[ntK18]/D");
  tree->Branch("vtgtK18",     event.vtgtK18,   "vtgtK18[ntK18]/D");
  tree->Branch("thetaK18",    event.thetaK18,  "thetaK18[ntK18]/D");

  //KURAMA
  tree->Branch("nlSdcIn",    &event.nlSdcIn,     "nlSdcIn/I");
  tree->Branch("ntSdcIn",    &event.ntSdcIn,     "ntSdcIn/I");
  tree->Branch("nhSdcIn",     event.nhSdcIn,     "nhSdcIn[ntSdcIn]/I");
  tree->Branch("chisqrSdcIn", event.chisqrSdcIn, "chisqrSdcIn[ntSdcIn]/D");
  tree->Branch("x0SdcIn",     event.x0SdcIn,     "x0SdcIn[ntSdcIn]/D");
  tree->Branch("y0SdcIn",     event.y0SdcIn,     "y0SdcIn[ntSdcIn]/D");
  tree->Branch("u0SdcIn",     event.u0SdcIn,     "u0SdcIn[ntSdcIn]/D");
  tree->Branch("v0SdcIn",     event.v0SdcIn,     "v0SdcIn[ntSdcIn]/D");

  tree->Branch("nlSdcOut",   &event.nlSdcOut,     "nlSdcOut/I");
  tree->Branch("ntSdcOut",   &event.ntSdcOut,     "ntSdcOut/I");
  tree->Branch("nhSdcOut",    event.nhSdcOut,     "nhSdcOut[ntSdcOut]/I");
  tree->Branch("chisqrSdcOut",event.chisqrSdcOut, "chisqrOut[ntSdcOut]/D");
  tree->Branch("x0SdcOut",    event.x0SdcOut,     "x0SdcOut[ntSdcOut]/D");
  tree->Branch("y0SdcOut",    event.y0SdcOut,     "y0SdcOut[ntSdcOut]/D");
  tree->Branch("u0SdcOut",    event.u0SdcOut,     "u0SdcOut[ntSdcOut]/D");
  tree->Branch("v0SdcOut",    event.v0SdcOut,     "v0SdcOut[ntSdcOut]/D");

  tree->Branch("ntKurama",     &event.ntKurama,     "ntKurama/I");
  tree->Branch("nhKurama",      event.nhKurama,     "nhKurama[ntKurama]/I");
  tree->Branch("chisqrKurama",  event.chisqrKurama, "chisqrKurama[ntKurama]/D");
  tree->Branch("stof",          event.stof,         "stof[ntKurama]/D");
  tree->Branch("path",          event.path,         "path[ntKurama]/D");
  tree->Branch("pKurama",       event.pKurama,      "pKurama[ntKurama]/D");
  tree->Branch("qKurama",       event.qKurama,      "qKurama[ntKurama]/D");
  tree->Branch("m2",            event.m2,           "m2[ntKurama]/D");
  tree->Branch("xtgtKurama",    event.xtgtKurama,   "xtgtKurama[ntKurama]/D");
  tree->Branch("ytgtKurama",    event.ytgtKurama,   "ytgtKurama[ntKurama]/D");
  tree->Branch("utgtKurama",    event.utgtKurama,   "utgtKurama[ntKurama]/D");
  tree->Branch("vtgtKurama",    event.vtgtKurama,   "vtgtKurama[ntKurama]/D");
  tree->Branch("thetaKurama",   event.thetaKurama,  "thetaKurama[ntKurama]/D");
  tree->Branch("xtofKurama",    event.xtofKurama,   "xtofKurama[ntKurama]/D");
  tree->Branch("ytofKurama",    event.ytofKurama,   "ytofKurama[ntKurama]/D");
  tree->Branch("utofKurama",    event.utofKurama,   "utofKurama[ntKurama]/D");
  tree->Branch("vtofKurama",    event.vtofKurama,   "vtofKurama[ntKurama]/D");
  tree->Branch("tofsegKurama",  event.tofsegKurama, "tofsegKurama[ntKurama]/D");
  tree->Branch("sftxsegKurama",      &event.sftxsegKurama,        "sftxsegKurama/D");
  tree->Branch("vpx", event.vpx, Form( "vpx[%d]/D", NumOfLayersVP ) );
  tree->Branch("vpy", event.vpy, Form( "vpy[%d]/D", NumOfLayersVP ) );
  tree->Branch("vpseg", event.vpseg, Form( "vpseg[%d]/D", NumOfLayersVP ) );

  //Reaction
  tree->Branch("nPi",           &event.nPi,            "nPi/I");
  tree->Branch("nK",            &event.nK,             "nK/I");
  tree->Branch("nPiK",           &event.nPiK,          "nPiK/I");
  tree->Branch("vtx",            event.vtx,            "vtx[nPiK]/D");
  tree->Branch("vty",            event.vty,            "vty[nPiK]/D");
  tree->Branch("vtz",            event.vtz,            "vtz[nPiK]/D");
  tree->Branch("closeDist",      event.closeDist,      "closeDist[nPiK]/D");
  tree->Branch("theta",          event.theta,          "theta[nPiK]/D");
  tree->Branch("MissMass",       event.MissMass,       "MissMass[nPiK]/D");
  tree->Branch("MissMassCorr",   event.MissMassCorr,   "MissMassCorr[nPiK]/D");
  tree->Branch("MissMassCorrDE", event.MissMassCorrDE, "MissMassCorrDE[nPiK]/D");
  tree->Branch("thetaCM", event.thetaCM,  "thetaCM[nPiK]/D");
  tree->Branch("costCM",  event.costCM,   "costCM[nPiK]/D");

  tree->Branch("xpi",        event.xpi,      "xpi[nPiK]/D");
  tree->Branch("ypi",        event.ypi,      "ypi[nPiK]/D");
  tree->Branch("upi",        event.upi,      "upi[nPiK]/D");
  tree->Branch("vpi",        event.vpi,      "vpi[nPiK]/D");
  tree->Branch("xk",         event.xk,       "xk[nPiK]/D");
  tree->Branch("yk",         event.yk,       "yk[nPiK]/D");
  tree->Branch("uk",         event.uk,       "uk[nPiK]/D");
  tree->Branch("vk",         event.vk,       "vk[nPiK]/D");
  tree->Branch("pOrg",       event.pOrg,      "pOrg[nPiK]/D");
  tree->Branch("pCalc",      event.pCalc,     "pCalc[nPiK]/D");
  tree->Branch("pCorr",      event.pCorr,     "pCorr[nPiK]/D");
  tree->Branch("pCorrDE",    event.pCorrDE,   "pCorrDE[nPiK]/D");

  ////////// Bring Address From Dst
  TTreeCont[kHodoscope]->SetBranchStatus("*", 0);
  TTreeCont[kHodoscope]->SetBranchStatus("evnum",    1);
  TTreeCont[kHodoscope]->SetBranchStatus("spill",    1);
  TTreeCont[kHodoscope]->SetBranchStatus("trigflag", 1);
  TTreeCont[kHodoscope]->SetBranchStatus("trigpat",  1);
  TTreeCont[kHodoscope]->SetBranchStatus("nhBh1",    1);
  TTreeCont[kHodoscope]->SetBranchStatus("csBh1",    1);
  TTreeCont[kHodoscope]->SetBranchStatus("Bh1Seg",   1);
  TTreeCont[kHodoscope]->SetBranchStatus("tBh1",     1);
  TTreeCont[kHodoscope]->SetBranchStatus("dtBh1",    1);
  TTreeCont[kHodoscope]->SetBranchStatus("deBh1",    1);
  TTreeCont[kHodoscope]->SetBranchStatus("btof",     1);
  TTreeCont[kHodoscope]->SetBranchStatus("nhBh2",    1);
  TTreeCont[kHodoscope]->SetBranchStatus("csBh2",    1);
  TTreeCont[kHodoscope]->SetBranchStatus("Bh2Seg",   1);
  TTreeCont[kHodoscope]->SetBranchStatus("t0Bh2",    1);
  TTreeCont[kHodoscope]->SetBranchStatus("tBh2",     1);
  TTreeCont[kHodoscope]->SetBranchStatus("dtBh2",    1);
  TTreeCont[kHodoscope]->SetBranchStatus("deBh2",    1);
  TTreeCont[kHodoscope]->SetBranchStatus("Time0",    1);
  TTreeCont[kHodoscope]->SetBranchStatus("CTime0",   1);
  TTreeCont[kHodoscope]->SetBranchStatus("Time0Seg", 1);
  TTreeCont[kHodoscope]->SetBranchStatus("deTime0",  1);
  TTreeCont[kHodoscope]->SetBranchStatus("nhTof",    1);
  TTreeCont[kHodoscope]->SetBranchStatus("csTof",    1);
  TTreeCont[kHodoscope]->SetBranchStatus("TofSeg",   1);
  TTreeCont[kHodoscope]->SetBranchStatus("tTof",     1);
  TTreeCont[kHodoscope]->SetBranchStatus("dtTof",    1);
  TTreeCont[kHodoscope]->SetBranchStatus("deTof",    1);

  TTreeCont[kHodoscope]->SetBranchAddress("evnum",    &src.evnum);
  TTreeCont[kHodoscope]->SetBranchAddress("spill",    &src.spill);
  TTreeCont[kHodoscope]->SetBranchAddress("trigflag",  src.trigflag);
  TTreeCont[kHodoscope]->SetBranchAddress("trigpat",   src.trigpat);
  TTreeCont[kHodoscope]->SetBranchAddress("nhBh1",    &src.nhBh1);
  TTreeCont[kHodoscope]->SetBranchAddress("csBh1",     src.csBh1);
  TTreeCont[kHodoscope]->SetBranchAddress("Bh1Seg",    src.Bh1Seg);
  TTreeCont[kHodoscope]->SetBranchAddress("tBh1",      src.tBh1);
  TTreeCont[kHodoscope]->SetBranchAddress("dtBh1",     src.dtBh1);
  TTreeCont[kHodoscope]->SetBranchAddress("deBh1",     src.deBh1);
  TTreeCont[kHodoscope]->SetBranchAddress("btof",      src.btof);
  TTreeCont[kHodoscope]->SetBranchAddress("nhBh2",    &src.nhBh2);
  TTreeCont[kHodoscope]->SetBranchAddress("csBh2",     src.csBh2);
  TTreeCont[kHodoscope]->SetBranchAddress("Bh2Seg",    src.Bh2Seg);
  TTreeCont[kHodoscope]->SetBranchAddress("t0Bh2",     src.t0Bh2);
  TTreeCont[kHodoscope]->SetBranchAddress("tBh2",      src.tBh2);
  TTreeCont[kHodoscope]->SetBranchAddress("dtBh2",     src.dtBh2);
  TTreeCont[kHodoscope]->SetBranchAddress("deBh2",     src.deBh2);
  TTreeCont[kHodoscope]->SetBranchAddress("Time0",    &src.Time0);
  TTreeCont[kHodoscope]->SetBranchAddress("CTime0",   &src.CTime0);
  TTreeCont[kHodoscope]->SetBranchAddress("Time0Seg", &src.Time0Seg);
  TTreeCont[kHodoscope]->SetBranchAddress("deTime0",  &src.deTime0);
  TTreeCont[kHodoscope]->SetBranchAddress("nhTof",    &src.nhTof);
  TTreeCont[kHodoscope]->SetBranchAddress("csTof",     src.csTof);
  TTreeCont[kHodoscope]->SetBranchAddress("TofSeg",    src.TofSeg);
  TTreeCont[kHodoscope]->SetBranchAddress("tTof",      src.tTof);
  TTreeCont[kHodoscope]->SetBranchAddress("dtTof",     src.dtTof);
  TTreeCont[kHodoscope]->SetBranchAddress("deTof",     src.deTof);

  TTreeCont[kKuramaTracking]->SetBranchStatus("*", 0);
  TTreeCont[kKuramaTracking]->SetBranchStatus("ntSdcIn",      1);
  TTreeCont[kKuramaTracking]->SetBranchStatus("nlSdcIn",      1);
  TTreeCont[kKuramaTracking]->SetBranchStatus("nhSdcIn",      1);
  TTreeCont[kKuramaTracking]->SetBranchStatus("chisqrSdcIn",  1);
  TTreeCont[kKuramaTracking]->SetBranchStatus("x0SdcIn",      1);
  TTreeCont[kKuramaTracking]->SetBranchStatus("y0SdcIn",      1);
  TTreeCont[kKuramaTracking]->SetBranchStatus("u0SdcIn",      1);
  TTreeCont[kKuramaTracking]->SetBranchStatus("v0SdcIn",      1);
  TTreeCont[kKuramaTracking]->SetBranchStatus("ntSdcOut",     1);
  TTreeCont[kKuramaTracking]->SetBranchStatus("nhSdcOut",     1);
  TTreeCont[kKuramaTracking]->SetBranchStatus("chisqrSdcOut", 1);
  TTreeCont[kKuramaTracking]->SetBranchStatus("x0SdcOut",     1);
  TTreeCont[kKuramaTracking]->SetBranchStatus("y0SdcOut",     1);
  TTreeCont[kKuramaTracking]->SetBranchStatus("u0SdcOut",     1);
  TTreeCont[kKuramaTracking]->SetBranchStatus("v0SdcOut",     1);

  TTreeCont[kKuramaTracking]->SetBranchStatus("ntKurama",    1);
  TTreeCont[kKuramaTracking]->SetBranchStatus("nhKurama",    1);
  TTreeCont[kKuramaTracking]->SetBranchStatus("stof",        1);
  TTreeCont[kKuramaTracking]->SetBranchStatus("path",        1);
  TTreeCont[kKuramaTracking]->SetBranchStatus("pKurama",     1);
  TTreeCont[kKuramaTracking]->SetBranchStatus("qKurama",     1);
  TTreeCont[kKuramaTracking]->SetBranchStatus("chisqrKurama",1);
  TTreeCont[kKuramaTracking]->SetBranchStatus("xtgtKurama",  1);
  TTreeCont[kKuramaTracking]->SetBranchStatus("ytgtKurama",  1);
  TTreeCont[kKuramaTracking]->SetBranchStatus("utgtKurama",  1);
  TTreeCont[kKuramaTracking]->SetBranchStatus("vtgtKurama",  1);
  TTreeCont[kKuramaTracking]->SetBranchStatus("thetaKurama", 1);
  TTreeCont[kKuramaTracking]->SetBranchStatus("xtofKurama",  1);
  TTreeCont[kKuramaTracking]->SetBranchStatus("ytofKurama",  1);
  TTreeCont[kKuramaTracking]->SetBranchStatus("utofKurama",  1);
  TTreeCont[kKuramaTracking]->SetBranchStatus("vtofKurama",  1);
  TTreeCont[kKuramaTracking]->SetBranchStatus("tofsegKurama",1);
  TTreeCont[kKuramaTracking]->SetBranchStatus("sftxsegKurama",  1);
  TTreeCont[kKuramaTracking]->SetBranchStatus("vpx",          1);
  TTreeCont[kKuramaTracking]->SetBranchStatus("vpy",          1);
  TTreeCont[kKuramaTracking]->SetBranchStatus("vpseg",          1);

  TTreeCont[kKuramaTracking]->SetBranchAddress("ntSdcIn",      &src.ntSdcIn      );
  TTreeCont[kKuramaTracking]->SetBranchAddress("nlSdcIn",      &src.nlSdcIn      );
  TTreeCont[kKuramaTracking]->SetBranchAddress("nhSdcIn",       src.nhSdcIn      );
  TTreeCont[kKuramaTracking]->SetBranchAddress("chisqrSdcIn",   src.chisqrSdcIn  );
  TTreeCont[kKuramaTracking]->SetBranchAddress("x0SdcIn",       src.x0SdcIn      );
  TTreeCont[kKuramaTracking]->SetBranchAddress("y0SdcIn",       src.y0SdcIn      );
  TTreeCont[kKuramaTracking]->SetBranchAddress("u0SdcIn",       src.u0SdcIn      );
  TTreeCont[kKuramaTracking]->SetBranchAddress("v0SdcIn",       src.v0SdcIn      );
  TTreeCont[kKuramaTracking]->SetBranchAddress("ntSdcOut",     &src.ntSdcOut     );
  TTreeCont[kKuramaTracking]->SetBranchAddress("nhSdcOut",      src.nhSdcOut     );
  TTreeCont[kKuramaTracking]->SetBranchAddress("chisqrSdcOut",  src.chisqrSdcOut );
  TTreeCont[kKuramaTracking]->SetBranchAddress("x0SdcOut",      src.x0SdcOut     );
  TTreeCont[kKuramaTracking]->SetBranchAddress("y0SdcOut",      src.y0SdcOut     );
  TTreeCont[kKuramaTracking]->SetBranchAddress("u0SdcOut",      src.u0SdcOut     );
  TTreeCont[kKuramaTracking]->SetBranchAddress("v0SdcOut",      src.v0SdcOut     );

  TTreeCont[kKuramaTracking]->SetBranchAddress("ntKurama",    &src.ntKurama);
  TTreeCont[kKuramaTracking]->SetBranchAddress("nhKurama",     src.nhKurama);
  TTreeCont[kKuramaTracking]->SetBranchAddress("stof",         src.stof);
  TTreeCont[kKuramaTracking]->SetBranchAddress("path",         src.path);
  TTreeCont[kKuramaTracking]->SetBranchAddress("pKurama",      src.pKurama);
  TTreeCont[kKuramaTracking]->SetBranchAddress("qKurama",      src.qKurama);
  TTreeCont[kKuramaTracking]->SetBranchAddress("chisqrKurama", src.chisqrKurama);
  TTreeCont[kKuramaTracking]->SetBranchAddress("xtgtKurama",   src.xtgtKurama);
  TTreeCont[kKuramaTracking]->SetBranchAddress("ytgtKurama",   src.ytgtKurama);
  TTreeCont[kKuramaTracking]->SetBranchAddress("utgtKurama",   src.utgtKurama);
  TTreeCont[kKuramaTracking]->SetBranchAddress("vtgtKurama",   src.vtgtKurama);
  TTreeCont[kKuramaTracking]->SetBranchAddress("thetaKurama",  src.thetaKurama);
  TTreeCont[kKuramaTracking]->SetBranchAddress("xtofKurama",   src.xtofKurama);
  TTreeCont[kKuramaTracking]->SetBranchAddress("ytofKurama",   src.ytofKurama);
  TTreeCont[kKuramaTracking]->SetBranchAddress("utofKurama",   src.utofKurama);
  TTreeCont[kKuramaTracking]->SetBranchAddress("vtofKurama",   src.vtofKurama);
  TTreeCont[kKuramaTracking]->SetBranchAddress("tofsegKurama", src.tofsegKurama);
  TTreeCont[kKuramaTracking]->SetBranchAddress("sftxsegKurama", &src.sftxsegKurama);
  TTreeCont[kKuramaTracking]->SetBranchAddress("vpx",        src.vpx);
  TTreeCont[kKuramaTracking]->SetBranchAddress("vpy",        src.vpy);
  TTreeCont[kKuramaTracking]->SetBranchAddress("vpseg",        src.vpseg);

  TTreeCont[kK18Tracking]->SetBranchStatus("*", 0);
  TTreeCont[kK18Tracking]->SetBranchStatus("ntBcOut",     1);
  TTreeCont[kK18Tracking]->SetBranchStatus("nlBcOut",     1);
  TTreeCont[kK18Tracking]->SetBranchStatus("nhBcOut",     1);
  TTreeCont[kK18Tracking]->SetBranchStatus("chisqrBcOut", 1);
  TTreeCont[kK18Tracking]->SetBranchStatus("x0BcOut",     1);
  TTreeCont[kK18Tracking]->SetBranchStatus("y0BcOut",     1);
  TTreeCont[kK18Tracking]->SetBranchStatus("u0BcOut",     1);
  TTreeCont[kK18Tracking]->SetBranchStatus("v0BcOut",     1);

  TTreeCont[kK18Tracking]->SetBranchStatus("ntK18",       1);
  TTreeCont[kK18Tracking]->SetBranchStatus("nhK18",       1);
  TTreeCont[kK18Tracking]->SetBranchStatus("chisqrK18",   1);
  TTreeCont[kK18Tracking]->SetBranchStatus("p_3rd",       1);
  TTreeCont[kK18Tracking]->SetBranchStatus("xtgtK18",     1);
  TTreeCont[kK18Tracking]->SetBranchStatus("ytgtK18",     1);
  TTreeCont[kK18Tracking]->SetBranchStatus("utgtK18",     1);
  TTreeCont[kK18Tracking]->SetBranchStatus("vtgtK18",     1);

  TTreeCont[kK18Tracking]->SetBranchAddress("ntBcOut",     &src.ntBcOut     );
  TTreeCont[kK18Tracking]->SetBranchAddress("nlBcOut",     &src.nlBcOut     );
  TTreeCont[kK18Tracking]->SetBranchAddress("nhBcOut",      src.nhBcOut     );
  TTreeCont[kK18Tracking]->SetBranchAddress("chisqrBcOut",  src.chisqrBcOut );
  TTreeCont[kK18Tracking]->SetBranchAddress("x0BcOut",      src.x0BcOut     );
  TTreeCont[kK18Tracking]->SetBranchAddress("y0BcOut",      src.y0BcOut     );
  TTreeCont[kK18Tracking]->SetBranchAddress("u0BcOut",      src.u0BcOut     );
  TTreeCont[kK18Tracking]->SetBranchAddress("v0BcOut",      src.v0BcOut     );

  TTreeCont[kK18Tracking]->SetBranchAddress("ntK18", &src.ntK18);
  TTreeCont[kK18Tracking]->SetBranchAddress("nhK18", &src.nhK18);
  TTreeCont[kK18Tracking]->SetBranchAddress("chisqrK18", &src.chisqrK18);
  TTreeCont[kK18Tracking]->SetBranchAddress("p_3rd", &src.pK18);
  TTreeCont[kK18Tracking]->SetBranchAddress("xtgtK18", &src.xtgtK18);
  TTreeCont[kK18Tracking]->SetBranchAddress("ytgtK18", &src.ytgtK18);
  TTreeCont[kK18Tracking]->SetBranchAddress("utgtK18", &src.utgtK18);
  TTreeCont[kK18Tracking]->SetBranchAddress("vtgtK18", &src.vtgtK18);

  TTreeCont[kEasiroc]->SetBranchStatus("*",    0);
  TTreeCont[kEasiroc]->SetBranchStatus("bft_ncl",    1);
  TTreeCont[kEasiroc]->SetBranchStatus("bft_clsize", 1);
  TTreeCont[kEasiroc]->SetBranchStatus("bft_ctime",  1);
  TTreeCont[kEasiroc]->SetBranchStatus("bft_ctot",   1);
  TTreeCont[kEasiroc]->SetBranchStatus("bft_clpos",  1);
  TTreeCont[kEasiroc]->SetBranchStatus("sch_ncl",    1);
  TTreeCont[kEasiroc]->SetBranchStatus("sch_clsize", 1);
  TTreeCont[kEasiroc]->SetBranchStatus("sch_ctime",  1);
  TTreeCont[kEasiroc]->SetBranchStatus("sch_ctot",   1);
  TTreeCont[kEasiroc]->SetBranchStatus("sch_clpos",  1);
  TTreeCont[kEasiroc]->SetBranchStatus("sch_clseg", 1);
  TTreeCont[kEasiroc]->SetBranchStatus("sftx_clseg", 1);
  TTreeCont[kEasiroc]->SetBranchStatus("sftx_ncl",    1);

  TTreeCont[kEasiroc]->SetBranchAddress("bft_ncl",    &src.nhBft);
  TTreeCont[kEasiroc]->SetBranchAddress("bft_clsize", src.csBft);
  TTreeCont[kEasiroc]->SetBranchAddress("bft_ctime",  src.tBft);
  TTreeCont[kEasiroc]->SetBranchAddress("bft_ctot",   src.wBft);
  TTreeCont[kEasiroc]->SetBranchAddress("bft_clpos",  src.BftPos);
  TTreeCont[kEasiroc]->SetBranchAddress("sch_ncl",    &src.nhSch);
  TTreeCont[kEasiroc]->SetBranchAddress("sch_clsize", src.csSch);
  TTreeCont[kEasiroc]->SetBranchAddress("sch_ctime",  src.tSch);
  TTreeCont[kEasiroc]->SetBranchAddress("sch_ctot",   src.wSch);
  TTreeCont[kEasiroc]->SetBranchAddress("sch_clpos",  src.SchPos);
  TTreeCont[kEasiroc]->SetBranchAddress("sch_clseg",  src.SchSeg);
  TTreeCont[kEasiroc]->SetBranchAddress("sftx_ncl",    &src.nhSftX);
  TTreeCont[kEasiroc]->SetBranchAddress("sftx_clseg",  src.SftXSeg);

  return true;
}

//_____________________________________________________________________
bool
ConfMan::InitializeParameterFiles( void )
{
  return
    ( InitializeParameter<DCGeomMan>("DCGEO")   &&
      InitializeParameter<UserParamMan>("USER") );
}

//_____________________________________________________________________
bool
ConfMan::FinalizeProcess( void )
{
  return true;
}
