/**
 *  file: DstKuramaHodoscope.cc
 *  date: 2017.04.10
 *
 */

#include <iomanip>
#include <iostream>
#include <cstdlib>
#include <cmath>

#include <filesystem_util.hh>

#include "CatchSignal.hh"
#include "ConfMan.hh"
#include "Kinematics.hh"
#include "DCGeomMan.hh"
#include "DatabasePDG.hh"
#include "DetectorID.hh"
#include "MathTools.hh"
#include "RootHelper.hh"
#include "UserParamMan.hh"

#include "DstHelper.hh"

namespace
{
  using namespace root;
  using namespace dst;
  const std::string& class_name("DstKuramaHodoscope");
  ConfMan&            gConf = ConfMan::GetInstance();
  const DCGeomMan&    gGeom = DCGeomMan::GetInstance();
  const UserParamMan& gUser = UserParamMan::GetInstance();
}

namespace dst
{
  enum kArgc
    {
      kProcess, kConfFile,
      kKuramaTracking, kHodoscope, kOutFile, nArgc
    };
  std::vector<TString> ArgName =
    { "[Process]", "[ConfFile]", "[KuramaTracking]",
      "[Hodoscope]", "[OutFile]" };
  std::vector<TString> TreeName =
    { "", "", "kurama", "hodo", "" };
  std::vector<TFile*> TFileCont;
  std::vector<TTree*> TTreeCont;
}

//_____________________________________________________________________
struct Event
{
  int status;

  // KuramaTracking
  int ntKurama;
  double path[MaxHits];
  double pKurama[MaxHits];
  double qKurama[MaxHits];
  double chisqrKurama[MaxHits];
  double xtgtKurama[MaxHits];
  double ytgtKurama[MaxHits];
  double utgtKurama[MaxHits];
  double vtgtKurama[MaxHits];
  double thetaKurama[MaxHits];
  double vpx[NumOfLayersVP*MaxHits];
  double vpy[NumOfLayersVP*MaxHits];

  // Hodoscope
  int trigflag[NumOfSegTrig];
  int trigpat[NumOfSegTrig];

  int nhBh1;
  int csBh1[NumOfSegBH1*MaxDepth];
  double Bh1Seg[NumOfSegBH1*MaxDepth];
  double tBh1[NumOfSegBH1*MaxDepth];
  double dtBh1[NumOfSegBH1*MaxDepth];
  double deBh1[NumOfSegBH1*MaxDepth];

  int nhBh2;
  int csBh2[NumOfSegBH2*MaxDepth];
  double Bh2Seg[NumOfSegBH2*MaxDepth];
  double tBh2[NumOfSegBH2*MaxDepth];
  double dtBh2[NumOfSegBH2*MaxDepth];
  double t0Bh2[NumOfSegBH2*MaxDepth];
  double deBh2[NumOfSegBH2*MaxDepth];

  int    nhSac;
  int    csSac[NumOfSegSAC*MaxDepth];
  double SacSeg[NumOfSegSAC*MaxDepth];
  double tSac[NumOfSegSAC*MaxDepth];
  double deSac[NumOfSegSAC*MaxDepth];

  int nhTof;
  int csTof[NumOfSegTOF];
  double TofSeg[NumOfSegTOF];
  double tTof[NumOfSegTOF];
  double dtTof[NumOfSegTOF];
  double deTof[NumOfSegTOF];

  double btof[NumOfSegBH1*MaxDepth];

  // KuramaHodoscope
  int    m2Combi;
  double beta[MaxHits];
  double stof[MaxHits];
  double m2[MaxHits];

  enum eParticle { Pion, Kaon, Proton, nParticle };
  double tTofCalc[nParticle];
  double utTofSeg[NumOfSegTOF];
  double dtTofSeg[NumOfSegTOF];
  double udeTofSeg[NumOfSegTOF];
  double ddeTofSeg[NumOfSegTOF];
  double tofua[NumOfSegTOF];
  double tofda[NumOfSegTOF];

};

//_____________________________________________________________________
struct Src
{
  int trigflag[NumOfSegTrig];
  int trigpat[NumOfSegTrig];

  int    ntKurama;
  double path[MaxHits];
  double pKurama[MaxHits];
  double qKurama[MaxHits];
  double chisqrKurama[MaxHits];
  double xtgtKurama[MaxHits];
  double ytgtKurama[MaxHits];
  double utgtKurama[MaxHits];
  double vtgtKurama[MaxHits];
  double thetaKurama[MaxHits];
  double vpx[NumOfLayersVP];
  double vpy[NumOfLayersVP];

  int    nhBh1;
  int    csBh1[NumOfSegBH1*MaxDepth];
  double Bh1Seg[NumOfSegBH1*MaxDepth];
  double tBh1[NumOfSegBH1*MaxDepth];
  double dtBh1[NumOfSegBH1*MaxDepth];
  double deBh1[NumOfSegBH1*MaxDepth];

  int    nhBh2;
  int    csBh2[NumOfSegBH2*MaxDepth];
  double Bh2Seg[NumOfSegBH2*MaxDepth];
  double tBh2[NumOfSegBH2*MaxDepth];
  double dtBh2[NumOfSegBH2*MaxDepth];
  double t0Bh2[NumOfSegBH2*MaxDepth];
  double deBh2[NumOfSegBH2*MaxDepth];
  
  double Time0Seg;
  double deTime0;
  double Time0;
  double CTime0;

  int    nhSac;
  int    csSac[NumOfSegSAC*MaxDepth];
  double SacSeg[NumOfSegSAC*MaxDepth];
  double tSac[NumOfSegSAC*MaxDepth];
  double deSac[NumOfSegSAC*MaxDepth];

  int    nhTof;
  int    csTof[NumOfSegTOF];
  double TofSeg[NumOfSegTOF];
  double tTof[NumOfSegTOF];
  double dtTof[NumOfSegTOF];
  double deTof[NumOfSegTOF];

  ////////// for HodoParam
  double utTofSeg[NumOfSegTOF];
  double dtTofSeg[NumOfSegTOF];
  double udeTofSeg[NumOfSegTOF];
  double ddeTofSeg[NumOfSegTOF];

};

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
  event.status   = 0;
  event.ntKurama = 0;
  event.nhBh1    = 0;
  event.nhBh2    = 0;
  event.nhSac    = 0;
  event.nhTof    = 0;
  event.m2Combi  = 0;

  for( int i=0; i<NumOfSegTrig; ++i ){
    event.trigflag[i] = -999;
    event.trigpat[i]  = -999;
  }

  for( int i=0; i<Event::nParticle; ++i ){
    event.tTofCalc[i] = -9999.;
  }

  for(int i=0;i<MaxHits;++i){
    event.path[i]         = -9999.;
    event.pKurama[i]      = -9999.;
    event.qKurama[i]      = -9999.;
    event.chisqrKurama[i] = -9999.;
    event.xtgtKurama[i]  = -9999.;
    event.ytgtKurama[i]  = -9999.;
    event.utgtKurama[i]  = -9999.;
    event.vtgtKurama[i]  = -9999.;
    event.thetaKurama[i] = -9999.;
  }

  for ( int l = 0; l < NumOfLayersVP; ++l ) {
      event.vpx[l] = -9999.;
      event.vpy[l] = -9999.;
  }

  for(int i=0;i<NumOfSegBH1*MaxDepth;++i){
    event.Bh1Seg[i] = -1;
    event.csBh1[i]  = 0;
    event.tBh1[i]   = -9999.;
    event.dtBh1[i]  = -9999.;
    event.deBh1[i]  = -9999.;
    event.btof[i]   = -9999.;
  }

  for(int i=0;i<NumOfSegBH2*MaxDepth;++i){
    event.Bh2Seg[i] = -1;
    event.csBh2[i]  = 0;
    event.tBh2[i]   = -9999.;
    event.dtBh2[i]  = -9999.;
    event.t0Bh2[i]  = -9999.;
    event.deBh2[i]  = -9999.;
  }

  for(int i=0;i<NumOfSegSAC*MaxDepth;++i){
    event.SacSeg[i] = -1;
    event.csSac[i]  = 0;
    event.tSac[i]   = -9999.;
    event.deSac[i]  = -9999.;
  }

  for(int i=0;i<NumOfSegTOF;++i){
    event.TofSeg[i] = -1;
    event.csTof[i]  = 0;
    event.tTof[i]   = -9999.;
    event.dtTof[i]  = -9999.;
    event.deTof[i]  = -9999.;
  }

  for( int i=0; i<MaxHits; ++i ){
    event.beta[i]  = -9999.;
    event.stof[i]  = -9999.;
    event.m2[i]    = -9999.;
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

  static const double OffsetToF = gUser.GetParameter("OffsetToF");

  if( ievent%10000==0 ){
    std::cout << "#D Event Number: "
	      << std::setw(6) << ievent << std::endl;
  }

  GetEntry(ievent);

  HF1( 1, event.status++ );

  event.ntKurama = src.ntKurama;
  event.nhBh1    = src.nhBh1;
  event.nhBh2    = src.nhBh2;
  event.nhSac    = src.nhSac;
  event.nhTof    = src.nhTof;

#if 0
  std::cout<<"[event]: "<<std::setw(6)<<ievent<<" ";
  std::cout<<"[ntKurama]: "<<std::setw(2)<<src.ntKurama<<" ";
  std::cout<<"[nhBh1]: "<<std::setw(2)<<src.nhBh1<<" ";
  std::cout<<"[nhBh2]: "<<std::setw(2)<<src.nhBh2<<" ";
  // std::cout<<"[nhSac]: "<<std::setw(2)<<src.nhSac<<" ";
  std::cout<<"[nhTof]: "<<std::setw(2)<<src.nhTof<<" "<<std::endl;
#endif

  for(int i=0;i<NumOfSegTrig;++i){
    int tdc = src.trigflag[i];
    if( tdc<=0 ) continue;
    event.trigpat[i]  = i + 1;
    event.trigflag[i] = tdc;
  }

//  if( event.trigflag[19]<=0 ) return false;

  if( event.nhBh1<=0 ) return true;
  HF1( 1, event.status++ );

  if( event.nhBh2<=0 ) return true;
  HF1( 1, event.status++ );

  if( event.nhTof<=0 ) return true;
  HF1( 1, event.status++ );

  if( event.ntKurama<=0 ) return true;
  if( event.ntKurama>MaxHits )
    event.ntKurama = MaxHits;

  HF1( 1, event.status++ );

  double time0 = src.CTime0;
  for( int i=0; i<src.nhBh2; ++i ){
    event.Bh2Seg[i] = src.Bh2Seg[i];
    event.tBh2[i]   = src.tBh2[i];
    event.t0Bh2[i]  = src.t0Bh2[i];
    event.deBh2[i]  = src.deBh2[i];
  }

  ////////// for BeamTof
  for( int i=0; i<src.nhBh1; ++i ){
    event.Bh1Seg[i] = src.Bh1Seg[i];
    event.tBh1[i]   = src.tBh1[i];
    event.deBh1[i]  = src.deBh1[i];
    event.btof[i]   = src.tBh1[i] - time0;
  }

  for( int i=0; i<src.nhSac; ++i ){
    event.SacSeg[i] = src.SacSeg[i];
    event.tSac[i]   = src.tSac[i];
    event.deSac[i]  = src.deSac[i];
  }

  int m2Combi = event.nhTof*event.ntKurama;
  if( m2Combi>MaxHits || m2Combi<0 ){
    std::cout << func_name << " too much m2Combi : " << m2Combi << std::endl;
    return false;
  }
  event.m2Combi = m2Combi;

  HF1( 1, event.status++ );
  int mm=0;
  for( int it=0; it<src.ntKurama; ++it ){
    event.path[it]    = src.path[it];
    event.pKurama[it] = src.pKurama[it];
    event.qKurama[it] = src.qKurama[it];
    event.xtgtKurama[it] = src.xtgtKurama[it];
    event.ytgtKurama[it] = src.ytgtKurama[it];
    event.utgtKurama[it] = src.utgtKurama[it];
    event.vtgtKurama[it] = src.vtgtKurama[it];
    event.thetaKurama[it] = src.thetaKurama[it];
    if ( src.ntKurama == 1 ) {
      for ( int l = 0; l < NumOfLayersVP; ++l ) {
	event.vpx[l] = src.vpx[l];
	event.vpy[l] = src.vpy[l];
      }
    }
    event.tTofCalc[Event::Pion] =
      Kinematics::CalcTimeOfFlight( event.pKurama[it],
				    event.path[it],
				    pdg::PionMass() );
    event.tTofCalc[Event::Kaon] =
      Kinematics::CalcTimeOfFlight( event.pKurama[it],
				    event.path[it],
				    pdg::KaonMass() );
    event.tTofCalc[Event::Proton] =
      Kinematics::CalcTimeOfFlight( event.pKurama[it],
				    event.path[it],
				    pdg::ProtonMass() );
    event.chisqrKurama[it] = src.chisqrKurama[it];

    HF1( 10, event.pKurama[it] );
    for( int itof=0; itof<src.nhTof; ++itof ){
      event.csTof[itof]  = src.csTof[itof];
      event.TofSeg[itof] = src.TofSeg[itof];
      event.tTof[itof]   = src.tTof[itof];
      event.dtTof[itof]  = src.dtTof[itof];
      event.deTof[itof]  = src.deTof[itof];
      int tofseg = (int)src.TofSeg[itof];
      HF1( 20000+tofseg*100, src.dtTof[itof] );

      ////////// TimeCut
      double stof = event.tTof[itof] - time0 + OffsetToF;
      double beta = event.path[it]/stof/math::C();
      event.beta[mm] = beta;
      event.stof[mm] = stof;// - event.tTofCalc[0];
      event.m2[mm]   =
	Kinematics::MassSquare( event.pKurama[it], event.path[it], stof );

#if 0
      std::cout << "#D DebugPrint() Event : " << ievent << std::endl
		<< std::setprecision(3) << std::fixed
		<< "   pKurama : " << event.pKurama[it] << std::endl;
#endif

      for( int ip=0; ip<Event::nParticle; ++ip ){
	HF2( 10000+ip+1, tofseg, stof-event.tTofCalc[ip] );
	HF1( 10000+tofseg*100+ip+1, stof-event.tTofCalc[ip] );
      }

      HF1( 11, event.m2[mm] );
      HF2( 20, event.m2[mm], event.pKurama[it] );

      ++mm;
    }
  }

  HF1( 1, event.status++ );

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
  HB1( 1, "Status", 21, 0., 21. );

  TString name[Event::nParticle] = { "Pion", "Kaon", "Proton" };

  for( int ip=0; ip<Event::nParticle; ++ip ){
    HB2( 10000+ip+1,
	 Form("TofTime-%sTime %% TofSeg", name[ip].Data() ),
	 NumOfSegTOF, 0., (double)NumOfSegTOF, 500, -25., 25. );
  }
  for( int i=0; i<NumOfSegTOF; ++i ){
    for( int ip=0; ip<Event::nParticle; ++ip ){
      HB1( 10000+(i+1)*100+ip+1,
	   Form("Tof-%d TofTime-%sTime", i+1, name[ip].Data() ),
	   500, -25., 25. );
    }

    HB1( 20000+(i+1)*100, Form("Tof TimeDiff U-D %d", i+1 ),
    	 500, -25., 25. );

  }
  HB1( 10, "pKurama",    280,  0.0, 2.8 );
  HB1( 11, "MassSquare", 180, -0.4, 1.4 );
  HB2( 20, "pKurama % MassSquare", 180, -0.4, 1.4, 280, 0.0, 2.8 );
  // for(int i=0;i<NumOfSegBH2;++i){
  //   HB1( 100+i, Form("m2[BH2 Seg.%d]", i+1),
  // 	 600, -0.2, 1.2);
  // }

  HBTree( "khodo", "tree of DstKuramaHodoscope" );
  tree->Branch("trigflag",   event.trigflag,  Form("trigflag[%d]/I", NumOfSegTrig) );
  tree->Branch("trigpat",    event.trigpat,   Form("trigpat[%d]/I", NumOfSegTrig) );
  tree->Branch("status",     &event.status,      "status/I");
  tree->Branch("ntKurama", &event.ntKurama,  "ntKurama/I");
  tree->Branch("path",      event.path,      "path[ntKurama]/D");
  tree->Branch("pKurama",   event.pKurama,   "pKurama[ntKurama]/D");
  tree->Branch("qKurama",   event.qKurama,   "qKurama[ntKurama]/D");
  tree->Branch("chisqrKurama", event.chisqrKurama, "chisqrKurama[ntKurama]/D");
  tree->Branch("xtgtKurama",    event.xtgtKurama,   "xtgtKurama[ntKurama]/D");
  tree->Branch("ytgtKurama",    event.ytgtKurama,   "ytgtKurama[ntKurama]/D");
  tree->Branch("utgtKurama",    event.utgtKurama,   "utgtKurama[ntKurama]/D");
  tree->Branch("vtgtKurama",    event.vtgtKurama,   "vtgtKurama[ntKurama]/D");
  tree->Branch("thetaKurama",   event.thetaKurama,  "thetaKurama[ntKurama]/D");
  tree->Branch("vpx", event.vpx, Form( "vpx[%d]/D", NumOfLayersVP ) );
  tree->Branch("vpy", event.vpy, Form( "vpy[%d]/D", NumOfLayersVP ) );

  tree->Branch("tTofCalc",  event.tTofCalc,  Form("tTofCalc[%d]/D",
  						  Event::nParticle ) );
  tree->Branch("nhBh1", &event.nhBh1, "nhBh1/I");
  tree->Branch("csBh1",  event.csBh1, "csBh1[nhBh1]/D");
  tree->Branch("Bh1Seg", event.Bh1Seg,"Bh1Seg[nhBh1]/D");
  tree->Branch("tBh1",   event.tBh1,  "tBh1[nhBh1]/D");
  tree->Branch("dtBh1",  event.dtBh1, "dtBh1[nhBh1]/D");
  tree->Branch("deBh1",  event.deBh1, "deBh1[nhBh1]/D");
  tree->Branch("btof",   event.btof, "btof[nhBh1]/D");

  tree->Branch("nhBh2", &event.nhBh2, "nhBh2/I");
  tree->Branch("csBh2",  event.csBh2, "csBh2[nhBh2]/D");
  tree->Branch("Bh2Seg", event.Bh2Seg,"Bh2Seg[nhBh2]/D");
  tree->Branch("tBh2",   event.tBh2,  "tBh2[nhBh2]/D");
  tree->Branch("dtBh2",  event.dtBh2, "dtBh2[nhBh2]/D");
  tree->Branch("t0Bh2",  event.t0Bh2, "t0Bh2[nhBh2]/D");
  tree->Branch("deBh2",  event.deBh2, "deBh2[nhBh2]/D");

  tree->Branch("nhSac",  &event.nhSac, "nhSac/I");
  tree->Branch("csSac",   event.csSac, "csSac[nhSac]/D");
  tree->Branch("SacSeg",  event.SacSeg,"SacSeg[nhSac]/D");
  tree->Branch("tSac",    event.tSac,  "tSac[nhSac]/D");
  tree->Branch("deSac",   event.deSac, "deSac[nhSac]/D");

  tree->Branch("nhTof",  &event.nhTof, "nhTof/I");
  tree->Branch("csTof",   event.csTof, "csTof[nhTof]/D");
  tree->Branch("TofSeg",  event.TofSeg,"TofSeg[nhTof]/D");
  tree->Branch("tTof",    event.tTof,  "tTof[nhTof]/D");
  tree->Branch("dtTof",   event.dtTof, "dtTof[nhTof]/D");
  tree->Branch("deTof",   event.deTof, "deTof[nhTof]/D");

  tree->Branch("m2Combi", &event.m2Combi, "m2Combi/I");
  tree->Branch("beta",     event.beta,    "beta[m2Combi]/D");
  tree->Branch("stof",     event.stof,    "stof[m2Combi]/D");
  tree->Branch("m2",       event.m2,      "m2[m2Combi]/D");

  ////////// Bring Address From Dst
  TTreeCont[kHodoscope]->SetBranchStatus("*", 0);
  TTreeCont[kHodoscope]->SetBranchStatus("trigflag",  1);
  TTreeCont[kHodoscope]->SetBranchStatus("trigpat",   1);
  TTreeCont[kHodoscope]->SetBranchStatus("nhBh1",     1);
  TTreeCont[kHodoscope]->SetBranchStatus("csBh1",     1);
  TTreeCont[kHodoscope]->SetBranchStatus("Bh1Seg",    1);
  TTreeCont[kHodoscope]->SetBranchStatus("tBh1",      1);
  TTreeCont[kHodoscope]->SetBranchStatus("dtBh1",     1);
  TTreeCont[kHodoscope]->SetBranchStatus("deBh1",     1);
  TTreeCont[kHodoscope]->SetBranchStatus("nhBh2",     1);
  TTreeCont[kHodoscope]->SetBranchStatus("csBh2",     1);
  TTreeCont[kHodoscope]->SetBranchStatus("Bh2Seg",    1);
  TTreeCont[kHodoscope]->SetBranchStatus("tBh2",      1);
  TTreeCont[kHodoscope]->SetBranchStatus("dtBh2",     1);
  TTreeCont[kHodoscope]->SetBranchStatus("t0Bh2",     1);
  TTreeCont[kHodoscope]->SetBranchStatus("deBh2",     1);
  TTreeCont[kHodoscope]->SetBranchStatus("nhSac",     1);
  TTreeCont[kHodoscope]->SetBranchStatus("csSac",     1);
  TTreeCont[kHodoscope]->SetBranchStatus("SacSeg",    1);
  TTreeCont[kHodoscope]->SetBranchStatus("tSac",      1);
  TTreeCont[kHodoscope]->SetBranchStatus("deSac",     1);
  TTreeCont[kHodoscope]->SetBranchStatus("nhTof",     1);
  TTreeCont[kHodoscope]->SetBranchStatus("csTof",     1);
  TTreeCont[kHodoscope]->SetBranchStatus("TofSeg",    1);
  TTreeCont[kHodoscope]->SetBranchStatus("tTof",      1);
  TTreeCont[kHodoscope]->SetBranchStatus("dtTof",     1);
  TTreeCont[kHodoscope]->SetBranchStatus("deTof",     1);
  TTreeCont[kHodoscope]->SetBranchStatus("utTofSeg",  1);
  TTreeCont[kHodoscope]->SetBranchStatus("dtTofSeg",  1);
  TTreeCont[kHodoscope]->SetBranchStatus("udeTofSeg", 1);
  TTreeCont[kHodoscope]->SetBranchStatus("ddeTofSeg", 1);
  TTreeCont[kHodoscope]->SetBranchStatus("Time0",     1);
  TTreeCont[kHodoscope]->SetBranchStatus("CTime0",    1);
  TTreeCont[kHodoscope]->SetBranchStatus("Time0Seg",  1);
  TTreeCont[kHodoscope]->SetBranchStatus("deTime0",   1);

  TTreeCont[kHodoscope]->SetBranchAddress("trigflag", src.trigflag);
  TTreeCont[kHodoscope]->SetBranchAddress("trigpat",  src.trigpat);
  TTreeCont[kHodoscope]->SetBranchAddress("nhBh1",  &src.nhBh1);
  TTreeCont[kHodoscope]->SetBranchAddress("csBh1",  src.csBh1);
  TTreeCont[kHodoscope]->SetBranchAddress("Bh1Seg", src.Bh1Seg);
  TTreeCont[kHodoscope]->SetBranchAddress("tBh1",   src.tBh1);
  TTreeCont[kHodoscope]->SetBranchAddress("dtBh1",  src.dtBh1);
  TTreeCont[kHodoscope]->SetBranchAddress("deBh1",  src.deBh1);
  TTreeCont[kHodoscope]->SetBranchAddress("nhBh2", &src.nhBh2);
  TTreeCont[kHodoscope]->SetBranchAddress("csBh2",  src.csBh2);
  TTreeCont[kHodoscope]->SetBranchAddress("Bh2Seg",src.Bh2Seg);
  TTreeCont[kHodoscope]->SetBranchAddress("tBh2",  src.tBh2);
  TTreeCont[kHodoscope]->SetBranchAddress("dtBh2", src.dtBh2);
  TTreeCont[kHodoscope]->SetBranchAddress("t0Bh2", src.t0Bh2);
  TTreeCont[kHodoscope]->SetBranchAddress("deBh2", src.deBh2);
  TTreeCont[kHodoscope]->SetBranchAddress("nhSac", &src.nhSac);
  TTreeCont[kHodoscope]->SetBranchAddress("csSac", src.csSac);
  TTreeCont[kHodoscope]->SetBranchAddress("SacSeg",src.SacSeg);
  TTreeCont[kHodoscope]->SetBranchAddress("tSac",  src.tSac);
  TTreeCont[kHodoscope]->SetBranchAddress("deSac", src.deSac);
  TTreeCont[kHodoscope]->SetBranchAddress("nhTof", &src.nhTof);
  TTreeCont[kHodoscope]->SetBranchAddress("csTof", src.csTof);
  TTreeCont[kHodoscope]->SetBranchAddress("TofSeg",src.TofSeg);
  TTreeCont[kHodoscope]->SetBranchAddress("tTof",  src.tTof);
  TTreeCont[kHodoscope]->SetBranchAddress("dtTof", src.dtTof);
  TTreeCont[kHodoscope]->SetBranchAddress("deTof", src.deTof);
  TTreeCont[kHodoscope]->SetBranchAddress("utTofSeg",  src.utTofSeg);
  TTreeCont[kHodoscope]->SetBranchAddress("dtTofSeg",  src.dtTofSeg);
  TTreeCont[kHodoscope]->SetBranchAddress("udeTofSeg", src.udeTofSeg);
  TTreeCont[kHodoscope]->SetBranchAddress("ddeTofSeg", src.ddeTofSeg);
  TTreeCont[kHodoscope]->SetBranchAddress("Time0",    &src.Time0);
  TTreeCont[kHodoscope]->SetBranchAddress("CTime0",   &src.CTime0);
  TTreeCont[kHodoscope]->SetBranchAddress("Time0Seg", &src.Time0Seg);
  TTreeCont[kHodoscope]->SetBranchAddress("deTime0",  &src.deTime0);

  TTreeCont[kKuramaTracking]->SetBranchStatus("*",      0);
  TTreeCont[kKuramaTracking]->SetBranchStatus("ntKurama",     1);
  TTreeCont[kKuramaTracking]->SetBranchStatus("path",         1);
  TTreeCont[kKuramaTracking]->SetBranchStatus("pKurama",      1);
  TTreeCont[kKuramaTracking]->SetBranchStatus("qKurama",      1);
  TTreeCont[kKuramaTracking]->SetBranchStatus("chisqrKurama", 1);
  TTreeCont[kKuramaTracking]->SetBranchStatus("thetaKurama",  1);
  TTreeCont[kKuramaTracking]->SetBranchStatus("xtgtKurama",   1);
  TTreeCont[kKuramaTracking]->SetBranchStatus("ytgtKurama",   1);
  TTreeCont[kKuramaTracking]->SetBranchStatus("utgtKurama",   1);
  TTreeCont[kKuramaTracking]->SetBranchStatus("vtgtKurama",   1);
  TTreeCont[kKuramaTracking]->SetBranchStatus("vpx",          1);
  TTreeCont[kKuramaTracking]->SetBranchStatus("vpy",          1);

  TTreeCont[kKuramaTracking]->SetBranchAddress("ntKurama", &src.ntKurama);
  TTreeCont[kKuramaTracking]->SetBranchAddress("path",     src.path);
  TTreeCont[kKuramaTracking]->SetBranchAddress("pKurama",  src.pKurama);
  TTreeCont[kKuramaTracking]->SetBranchAddress("qKurama",  src.qKurama);
  TTreeCont[kKuramaTracking]->SetBranchAddress("chisqrKurama", src.chisqrKurama);
  TTreeCont[kKuramaTracking]->SetBranchAddress("thetaKurama", src.thetaKurama);
  TTreeCont[kKuramaTracking]->SetBranchAddress("xtgtKurama", src.xtgtKurama);
  TTreeCont[kKuramaTracking]->SetBranchAddress("ytgtKurama", src.ytgtKurama);
  TTreeCont[kKuramaTracking]->SetBranchAddress("utgtKurama", src.utgtKurama);
  TTreeCont[kKuramaTracking]->SetBranchAddress("vtgtKurama", src.vtgtKurama);
  TTreeCont[kKuramaTracking]->SetBranchAddress("vpx",        src.vpx);
  TTreeCont[kKuramaTracking]->SetBranchAddress("vpy",        src.vpy);

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
