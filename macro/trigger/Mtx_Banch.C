#include <iostream>
#include <string>
#include <vector>

#include <fstream>
#include <TApplication.h>
#include <TROOT.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TString.h>
#include <TTree.h>
#include <TFile.h>
#include <TSystem.h>
#include <TH1.h>
#include <TH2.h>

//using namespace std;

#include "DetectorID.hh"

const char* Month[] =
{
  "zero",
  "jan",
  "feb",
  "mar",
  "apr",
  "may",
  "jun",
  "jly",
  "agt",
  "sep",
  "oct",
  "nov",
  "dec"
};

const char* TriggerFlag[]=
{
  "Bh21K     ",
  "Bh22K     ",
  "Bh23K     ",
  "Bh24K     ",
  "Bh25K     ",
  "Bh26K     ",
  "Bh27K     ",
  "Bh28K     ",
  "Bh2K      ",
  "ElseOr    ",
  "Beam      ",
  "BeamTof   ",
  "BeamPi    ",
  "BeamP     ",
  "Coin1     ",
  "Coin2     ",
  "E03       ",
  "Bh2KPs    ",
  "BeamPs    ",
  "BeamTofPs ",
  "BeamPiPs  ",
  "BeamPPs   ",
  "Coin1Ps   ",
  "Coin2Ps   ",
  "E03Ps     ",
  "Clock     ",
  "Reserve2  ",
  "SpillEnd  ",
  "Matrix    ",
  "MstAccept ",
  "MstClear  ",
  "TofTiming "
};

bool eq3(int a,int b,int c){
  if( a!= b ) return false;
  if( b!= c ) return false;
  if( c!= a ) return false;

  return true;
}

void Mtx_Banch(int month, int runnum){

  gStyle->SetOptTitle(0);
  gStyle->SetLabelSize(0.04,"XYZ");
  gStyle->SetTitleSize(0.05,"XYZ");
  gStyle->SetTitleOffset(1.2,"X");
  gStyle->SetTitleOffset(1.3,"Y");
  gStyle->SetPadLeftMargin(0.16);
  gStyle->SetPadBottomMargin(0.16);

  //Matrix Patern txt file PATH -----------------------------------------------------------------------
  TString anadir=Form("%s/work/e40/ana",std::getenv("HOME")); 
  TString filein1=Form("%s/analyzer_%s/param/MATRIXSFT/SFT_table.txt.2018Jun.3_1",anadir.Data(),Month[month] ); 
  TString filein2=Form("%s/analyzer_%s/param/MATRIXSFT/SFT_Newtable.txt.2019Jan.1_2",anadir.Data(),Month[month] ); 

  std::ifstream fin1(filein1);
  std::ifstream fin2(filein2);

  // Param Vector Dif ----------------------------------------------------------------------
  std::vector<std::vector<int>> Mtx_prm; 
  std::string line;
  int preSCH = 0;
  std::vector<std::vector<int>> sch_tof; 
  std::vector<int> SCH_Seg; 
  std::vector<int> TOF_Min; 
  std::vector<int> TOF_Max; 

  std::vector<std::vector<int>> Mtx_prm2; 
  std::string line2;
  int preSCH2 = 0;
  std::vector<std::vector<int>> sch_tof2; 
  std::vector<int> SCH_Seg2; 
  std::vector<int> TOF_Min2; 
  std::vector<int> TOF_Max2; 


  // Error Out ----------------------------------------------------------------------------------------
  if(fin1.fail() ||  fin2.fail() ){
    std::cerr << "file1 or file2" << std::endl;
    exit(0); 
  }  

  if( !eq3(SCH_Seg.size(),TOF_Min.size(),TOF_Max.size()) ){
    std::cerr << "Size Not Same" << std::endl;
  }

  if( !eq3(SCH_Seg2.size(),TOF_Min2.size(),TOF_Max2.size()) ){
    std::cerr << "Size Not Same 2" << std::endl;
  }

  while(std::getline(fin1, line)){
    double sch=-1, tof=-1, sft_min=-1, sft_max=-1;
    std::istringstream input_line( line );
    std::vector<int> inner;
    if( input_line >> sch >> tof >> sft_min >> sft_max ){
      inner.push_back(sch);
      inner.push_back(tof);
      if((int)sft_min%32==0){
        inner.push_back(sft_min-10);
      }else{
        inner.push_back(sft_min-11);
      }
      inner.push_back(sft_max-1);
      Mtx_prm.push_back(inner);
    }
  }

  while(std::getline(fin2, line2)){
    double sch=-1, tof=-1, sft_min=-1, sft_max=-1;
    std::istringstream input_line( line2 );
    std::vector<int> inner;
    if( input_line >> sch >> tof >> sft_min >> sft_max ){
      inner.push_back(sch);
      inner.push_back(tof);
      if((int)sft_min%32==0){
        inner.push_back(sft_min-10);
      }else{
        inner.push_back(sft_min-11);
      }
      inner.push_back(sft_max-1);
      Mtx_prm2.push_back(inner);
    }
  }

  //  for(int i=0; i<Mtx_prm.size(); i++){
  //    if(i==0){
  //      SCH_Seg.push_back( Mtx_prm.at(i).at(0) );
  //      TOF_Min.push_back( Mtx_prm.at(i).at(1) );
  //    }else{
  //      if(i==Mtx_prm.size()-1){
  //        TOF_Max.push_back( Mtx_prm.at(i).at(1) );
  //      }else if(Mtx_prm.at(i).at(0)!=Mtx_prm.at(i-1).at(0)){
  //        SCH_Seg.push_back( Mtx_prm.at(i).at(0) );
  //        TOF_Max.push_back( Mtx_prm.at(i-1).at(1) );
  //        TOF_Min.push_back( Mtx_prm.at(i).at(1) );
  //      }
  //    }
  //  }

  gStyle->SetOptStat(1111110); 
  gStyle->SetOptFit(1); 


  //Reset ROOT and connect tree file
  gROOT->Reset();
  //   TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("rootfile/run05126_DstKuramaEasirocHodoscope.root");
  //  TString anadir=Form("%s/work/e40/ana",std::getenv("HOME")); 
  TString pdf = Form("%s/pdf/trigger/Mtx_Banch_run%05d.pdf", anadir.Data(),runnum);
  TString pdfDhire = Form("%s/pdf/trigger", anadir.Data());
  TFile *f = new TFile(Form("%s/analyzer_%s/rootfile/run%05d_Matrix.root", anadir.Data(),Month[month], runnum),"READ");
  TTree *mtx;
  f->GetObject("mtx",mtx);

  //Declaration of leaves types
  Int_t           evnum;
  //  Int_t           spill;
  //  Int_t           trignhits;
  //  Int_t           trigpat[17];
  Int_t           trigflag[32];
  //  Int_t           bh2nhits;
  //  Int_t           bh2hitpat[8];
  //  Double_t        bh2ua[8];
  //  Double_t        bh2ut[8][16];
  //  Double_t        bh2da[8];
  //  Double_t        bh2dt[8][16];
  //  Int_t           fpga_bh2mtnhits;
  //  Int_t           fpga_bh2mthitpat[8][16];
  //  Double_t        fpga_bh2mt[8][16];
  Int_t           tofnhits;
  //  Int_t           tofhitpat[24];
  //  Double_t        tofua[24];
  //  Double_t        tofut[24][16];
  //  Double_t        tofda[24];
  //  Double_t        tofdt[24][16];
  //  Double_t        bh2mt[8][16];
  //  Double_t        bh2de[8];
  Double_t        tofmt[24][16];
  //  Double_t        tofde[24];
  //  Double_t        t0[8][16];
  //  Double_t        ct0[8][16];
  //  Double_t        btof[11][8];
  //  Double_t        cbtof[11][8];
  //  Double_t        Time0Seg;
  //  Double_t        deTime0;
  //  Double_t        Time0;
  //  Double_t        CTime0;
  //  Double_t        Btof0Seg;
  //  Double_t        deBtof0;
  //  Double_t        Btof0;
  //  Double_t        CBtof0;
  Int_t           sch_nhits;
  Int_t           sch_hitpat[36];
  //  Double_t        sch_tdc[64][16];
  //  Double_t        sch_trailing[64][16];
  //  Double_t        sch_tot[64][16];
  Double_t        sch_time[64][16];
  Int_t           sch_depth[64];
  Int_t           sftx_nhits;
  Int_t           sftx_unhits;
  Int_t           sftx_dnhits;
  Int_t           sftx_uhitpat[123];
  Int_t           sftx_dhitpat[140];
  //  Double_t        sftx_utdc[256][16];
  //  Double_t        sftx_dtdc[256][16];
  //  Double_t        sftx_utrailing[256][16];
  //  Double_t        sftx_dtrailing[256][16];
  //  Double_t        sftx_utot[256][16];
  //  Double_t        sftx_dtot[256][16];
  Double_t        sftx_utime[256][16];
  Double_t        sftx_dtime[256][16];
  Int_t           sftx_udepth[256];
  Int_t           sftx_ddepth[256];

  // Set branch atatus.
  mtx->SetBranchStatus("*",0);  // disable all branches
  mtx->SetBranchStatus("evnum");
  //  mtx->SetBranchStatus("spill");
  //  mtx->SetBranchStatus("trignhits");
  //  mtx->SetBranchStatus("trigpat");
  mtx->SetBranchStatus("trigflag");
  //   mtx->SetBranchStatus("bh2nhits");
  //   mtx->SetBranchStatus("bh2hitpat");
  //   mtx->SetBranchStatus("bh2ua");
  //   mtx->SetBranchStatus("bh2ut");
  //   mtx->SetBranchStatus("bh2da");
  //   mtx->SetBranchStatus("bh2dt");
  //   mtx->SetBranchStatus("fpga_bh2mtnhits");
  //   mtx->SetBranchStatus("fpga_bh2mthitpat");
  //   mtx->SetBranchStatus("fpga_bh2mt");
  mtx->SetBranchStatus("tofnhits");
  //  mtx->SetBranchStatus("tofhitpat");
  //  mtx->SetBranchStatus("tofua");
  //  mtx->SetBranchStatus("tofut");
  //  mtx->SetBranchStatus("tofda");
  //  mtx->SetBranchStatus("tofdt");
  //   mtx->SetBranchStatus("bh2mt");
  //   mtx->SetBranchStatus("bh2de");
  mtx->SetBranchStatus("tofmt");
  //  mtx->SetBranchStatus("tofde");
  //   mtx->SetBranchStatus("t0");
  //   mtx->SetBranchStatus("ct0");
  //   mtx->SetBranchStatus("btof");
  //   mtx->SetBranchStatus("cbtof");
  //   mtx->SetBranchStatus("Time0Seg");
  //   mtx->SetBranchStatus("deTime0");
  //   mtx->SetBranchStatus("Time0");
  //   mtx->SetBranchStatus("CTime0");
  //   mtx->SetBranchStatus("Btof0Seg");
  //   mtx->SetBranchStatus("deBtof0");
  //   mtx->SetBranchStatus("Btof0");
  //   mtx->SetBranchStatus("CBtof0");
  mtx->SetBranchStatus("sch_nhits");
  mtx->SetBranchStatus("sch_hitpat");
  //  mtx->SetBranchStatus("sch_tdc");
  //  mtx->SetBranchStatus("sch_trailing");
  //  mtx->SetBranchStatus("sch_tot");
  mtx->SetBranchStatus("sch_time");
  mtx->SetBranchStatus("sch_depth");
  mtx->SetBranchStatus("sftx_nhits");
  mtx->SetBranchStatus("sftx_unhits");
  mtx->SetBranchStatus("sftx_dnhits");
  mtx->SetBranchStatus("sftx_uhitpat");
  mtx->SetBranchStatus("sftx_dhitpat");
  //  mtx->SetBranchStatus("sftx_utdc");
  //  mtx->SetBranchStatus("sftx_dtdc");
  //  mtx->SetBranchStatus("sftx_utrailing");
  //  mtx->SetBranchStatus("sftx_dtrailing");
  //  mtx->SetBranchStatus("sftx_utot");
  //  mtx->SetBranchStatus("sftx_dtot");
  mtx->SetBranchStatus("sftx_utime");
  mtx->SetBranchStatus("sftx_dtime");
  mtx->SetBranchStatus("sftx_udepth");
  mtx->SetBranchStatus("sftx_ddepth");


  // Set branch addresses.
  mtx->SetBranchAddress("evnum",&evnum);
  //  mtx->SetBranchAddress("spill",&spill);
  //  mtx->SetBranchAddress("trignhits",&trignhits);
  //  mtx->SetBranchAddress("trigpat",trigpat);
  mtx->SetBranchAddress("trigflag",trigflag);
  //  mtx->SetBranchAddress("bh2nhits",&bh2nhits);
  //  mtx->SetBranchAddress("bh2hitpat",bh2hitpat);
  //  mtx->SetBranchAddress("bh2ua",bh2ua);
  //  mtx->SetBranchAddress("bh2ut",bh2ut);
  //  mtx->SetBranchAddress("bh2da",bh2da);
  //  mtx->SetBranchAddress("bh2dt",bh2dt);
  //  mtx->SetBranchAddress("fpga_bh2mtnhits",&fpga_bh2mtnhits);
  //  mtx->SetBranchAddress("fpga_bh2mthitpat",fpga_bh2mthitpat);
  //  mtx->SetBranchAddress("fpga_bh2mt",fpga_bh2mt);
  mtx->SetBranchAddress("tofnhits",&tofnhits);
  //  mtx->SetBranchAddress("tofhitpat",tofhitpat);
  //  mtx->SetBranchAddress("tofua",tofua);
  //  mtx->SetBranchAddress("tofut",tofut);
  //  mtx->SetBranchAddress("tofda",tofda);
  //  mtx->SetBranchAddress("tofdt",tofdt);
  //  mtx->SetBranchAddress("bh2mt",bh2mt);
  //  mtx->SetBranchAddress("bh2de",bh2de);
  mtx->SetBranchAddress("tofmt",tofmt);
  //  mtx->SetBranchAddress("tofde",tofde);
  //  mtx->SetBranchAddress("t0",t0);
  //  mtx->SetBranchAddress("ct0",ct0);
  //  mtx->SetBranchAddress("btof",btof);
  //  mtx->SetBranchAddress("cbtof",cbtof);
  //  mtx->SetBranchAddress("Time0Seg",&Time0Seg);
  //  mtx->SetBranchAddress("deTime0",&deTime0);
  //  mtx->SetBranchAddress("Time0",&Time0);
  //  mtx->SetBranchAddress("CTime0",&CTime0);
  //  mtx->SetBranchAddress("Btof0Seg",&Btof0Seg);
  //  mtx->SetBranchAddress("deBtof0",&deBtof0);
  //  mtx->SetBranchAddress("Btof0",&Btof0);
  //  mtx->SetBranchAddress("CBtof0",&CBtof0);
  mtx->SetBranchAddress("sch_nhits",&sch_nhits);
  mtx->SetBranchAddress("sch_hitpat",sch_hitpat);
  //  mtx->SetBranchAddress("sch_tdc",sch_tdc);
  //  mtx->SetBranchAddress("sch_trailing",sch_trailing);
  //  mtx->SetBranchAddress("sch_tot",sch_tot);
  mtx->SetBranchAddress("sch_time",sch_time);
  mtx->SetBranchAddress("sch_depth",sch_depth);
  mtx->SetBranchAddress("sftx_nhits",&sftx_nhits);
  mtx->SetBranchAddress("sftx_unhits",&sftx_unhits);
  mtx->SetBranchAddress("sftx_dnhits",&sftx_dnhits);
  mtx->SetBranchAddress("sftx_uhitpat",sftx_uhitpat);
  mtx->SetBranchAddress("sftx_dhitpat",sftx_dhitpat);
  //  mtx->SetBranchAddress("sftx_utdc",sftx_utdc);
  //  mtx->SetBranchAddress("sftx_dtdc",sftx_dtdc);
  //  mtx->SetBranchAddress("sftx_utrailing",sftx_utrailing);
  //  mtx->SetBranchAddress("sftx_dtrailing",sftx_dtrailing);
  //  mtx->SetBranchAddress("sftx_utot",sftx_utot);
  //  mtx->SetBranchAddress("sftx_dtot",sftx_dtot);
  mtx->SetBranchAddress("sftx_utime",sftx_utime);
  mtx->SetBranchAddress("sftx_dtime",sftx_dtime);
  mtx->SetBranchAddress("sftx_udepth",sftx_udepth);
  mtx->SetBranchAddress("sftx_ddepth",sftx_ddepth);


  //-para def-----------------------------------------------------------------------------------------
  double HULMHTDCCalib = -0.8333;
  double MaxBinValue=0.;

  int nGate = 15;
//  int Gate[] = {1,5,10,15,20,30,40,60,120};
  int  Gate[] = {1,5,10,15,20,30,40,50,60,70,80,90,100,110,120};
  double Gate_d[] = {1.,5.,10.,15.,20.,30.,40.,50.,60.,70.,80.,90.,100.,110.,120.};

  double TofMid = 10.;
  double SchMid = 0.;
  double SftMid = 0.;

  int Hist1Max = 0;
  int Hist2Max = 0;

  int Count1[nGate+1];
  int Count1_MtxFlg[nGate+1];
  int Count1_2[nGate+1];
  int Count1_2_MtxFlg[nGate+1];
  double MtxEfficiency[nGate];
  double MtxEfficiency_MtxFlg[nGate];
  double MtxEfficiency_2_MtxFlg[nGate];
  double MtxEfficiency_Gate[nGate];
  double MtxEfficiency_OldGate[nGate];
  double x[nGate];
  double x2[nGate+1];
  for(int n=0; n<nGate; n++){
    Count1[n] = 0;
    Count1_MtxFlg[n] = 0;
    Count1_2[n] = 0;
    Count1_2_MtxFlg[n] = 0;
    MtxEfficiency[n] = 0.;
    MtxEfficiency_Gate[n] = 0.;
    MtxEfficiency_OldGate[n] = 0.;
    MtxEfficiency_MtxFlg[n] = 0.;
    MtxEfficiency_2_MtxFlg[n] = 0.;
    x[n] = (double)nGate-n-1;
    x2[n] = (double)nGate-n;
  }
    Count1[nGate] = 0;
    Count1_MtxFlg[nGate] = 0;
    MtxEfficiency_2_MtxFlg[nGate] = 0.;
    x2[nGate] = 0;


  //-hist def-----------------------------------------------------------------------------------------
  Hist1Max = 72;
  TH1D *Hist1[Hist1Max];
  TH2D *Hist2[Hist2Max];


  //-Trigger Flag -------
  for(int i=0;i<32;i++){
    Hist1[i]= new TH1D(Form("TrigFlag %s",TriggerFlag[i]),Form("TrigFlag %s",TriggerFlag[i]),1000,0,2100);
  }
  //-Tof ----------------
  Hist1[32] = new TH1D("TofMtOr Nhits","TofMtOr Nhits",20,0,20);
  Hist1[33] = new TH1D("TofMtOr Hitpat","TofMtOr Hitpat",25,0,24);
  Hist1[34] = new TH1D("TofMtOr DepthPat","TofMtOrDepthPat",20,0,20);
  Hist1[35] = new TH1D("TofMtOr","TofMtOr;TofMt[ns];Counts",200,-100,100);
  Hist1[52] = new TH1D("TofMtOr Gate1","TofMtOr Gate1",200,-100,100);
  Hist1[53] = new TH1D("TofMtOr Gate2","TofMtOr Gate2",200,-100,100);
  Hist1[54] = new TH1D("TofMtOr Gate3","TofMtOr Gate3",200,-100,100);
  Hist1[55] = new TH1D("TofMtOr Gate4","TofMtOr Gate4",200,-100,100);
  Hist1[56] = new TH1D("TofMtOr Gate5","TofMtOr Gate5",200,-100,100);
  Hist1[57] = new TH1D("TofMtOr Gate6","TofMtOr Gate6",200,-100,100);

  //-Sch ----------------
  Hist1[36]= new TH1D("Sch Nhits" ,"Sch Nhits" ,20,0,20);
  Hist1[37]= new TH1D("Sch Hitpat","Sch Hitpat",65,0,65);
  Hist1[38]= new TH1D("Sch Depthpat","Sch Depthpat",65,0,65);
  Hist1[39]= new TH1D("Sch Time"   ,"Sch Time;SCH time[ns];Counts"   ,200,-100,100);
  Hist1[58] = new TH1D("Sch Time Gate1","Sch Time Gate1",200,-100,100);
  Hist1[59] = new TH1D("Sch Time Gate2","Sch Time Gate2",200,-100,100);
  Hist1[60] = new TH1D("Sch Time Gate3","Sch Time Gate3",200,-100,100);
  Hist1[61] = new TH1D("Sch Time Gate4","Sch Time Gate4",200,-100,100);
  Hist1[62] = new TH1D("Sch Time Gate5","Sch Time Gate5",200,-100,100);
  Hist1[63] = new TH1D("Sch Time Gate6","Sch Time Gate6",200,-100,100);

  //-SftX ----------------
  Hist1[40] = new TH1D("SftX U Nhits","SftX U Nhits",50,0,50);
  Hist1[41] = new TH1D("SftX D Nhits","SftX D Nhits",50,0,50);
  Hist1[42] = new TH1D("SftXNhits","SftXNhits",50,0,50);
  Hist1[43] = new TH1D("SftX U Hitpat","SftX U Hitpat",256,0,256);
  Hist1[44] = new TH1D("SftX D Hitpat","SftX D Hitpat",256,0,256);
  Hist1[45] = new TH1D("SftXHitpat","SftXHitpat",256,0,256);
  Hist1[46] = new TH1D("SftX U Tdc","SftX U Tdc",1000,0,1000);
  Hist1[47] = new TH1D("SftX D Tdc","SftX D Tdc",1000,0,1000);
  Hist1[48] = new TH1D("SftXTdc","SftXTdc",1000,0,1000);
  Hist1[49] = new TH1D("SftX U Time","SftX U Time",200,-100,100);
  Hist1[50] = new TH1D("SftX D Time","SftX D Time",200,-100,100);
  Hist1[51] = new TH1D("SftXTime","SftXTime;SFT X time[ns];Counts",200,-100,100);
  Hist1[64] = new TH1D("SftX Time Gate1","SftX Time Gate1",200,-100,100);
  Hist1[65] = new TH1D("SftX Time Gate2","SftX Time Gate2",200,-100,100);
  Hist1[66] = new TH1D("SftX Time Gate3","SftX Time Gate3",200,-100,100);
  Hist1[67] = new TH1D("SftX Time Gate4","SftX Time Gate4",200,-100,100);
  Hist1[68] = new TH1D("SftX Time Gate5","SftX Time Gate5",200,-100,100);
  Hist1[69] = new TH1D("SftX Time Gate6","SftX Time Gate6",200,-100,100);

  Hist1[70] = new TH1D("Sch Time TofFlag","Sch Time TofFlag",200,-100,100);
  Hist1[71] = new TH1D("SftX Time TofFlag","SftX Time TofFlag",200,-100,100);

  //-Event Loop --------------------------------------------------------------------------------------
//  Long64_t nentries = mtx->GetEntries();
  Long64_t nentries_MtxFlg = 0;
    Long64_t nentries =10000;

  for (Long64_t s=0; s<nentries;s++){
    mtx->GetEntry(s);
    if(s%(nentries/10) ==0){
      std::cout << ( ((double)s)/nentries *100 ) << "%\t" << s << "/" << nentries << "\r"  << std::endl;
    }
    // Trigger Flag -----------------------
    for(int i=0; i<32; i++){
      Hist1[i]->Fill(trigflag[i]);
    }

    Hist1[32]->Fill(tofnhits);

    bool TofFlag = false;
    // TofMtOr ----------------------------
    for(int i=0; i<NumOfSegTOF; i++){
      for(int j=0; j<16; j++){
        if(tofmt[i][j]==-999)   continue;
        Hist1[33]->Fill(i);
        Hist1[34]->Fill(j);
        Hist1[35]->Fill(tofmt[i][j]);
        if(tofmt[i][j]>25&&tofmt[i][j]<35){
          TofFlag = true;
        }
      }
    }

    // Sch --------------------------------
    Hist1[36]->Fill(sch_nhits);
    for(int i=0; i<sch_nhits; i++){
      Hist1[37]->Fill(sch_hitpat[i]);
    }
    for(int i=0; i<NumOfSegSCH; i++){
      Hist1[38]->Fill(sch_depth[i]);
      for(int k=0; k<16; k++){
        if(sch_time[i][k]==-999) continue;
        Hist1[39]->Fill(sch_time[i][k]);
        if(TofFlag){
          Hist1[70]->Fill(sch_time[i][k]);
        }
      }
    }

    // Sft X ------------------------------
    Hist1[40]->Fill(sftx_unhits);
    Hist1[41]->Fill(sftx_dnhits);
    Hist1[42]->Fill(sftx_unhits);
    Hist1[42]->Fill(sftx_dnhits);
    for(int i=0; i<94; i++){
      Hist1[43]->Fill(sftx_uhitpat[i]);
      Hist1[45]->Fill(sftx_uhitpat[i]);
    }
    for(int i=0; i<49; i++){
      Hist1[44]->Fill(sftx_dhitpat[i]+0.5);
      Hist1[45]->Fill(sftx_dhitpat[i]+0.5);
    }
    for(int i=0; i<NumOfSegSFT_X; i++){
      for(int j=0; j<16; j++){
        if(sftx_utime[i][j]!=-999){
          Hist1[49]->Fill(sftx_utime[i][j]);
          Hist1[51]->Fill(sftx_utime[i][j]);
          if(TofFlag){
            Hist1[71]->Fill(sftx_utime[i][j]);
          }
        }
        if(sftx_dtime[i][j]!=-999){
          Hist1[50]->Fill(sftx_dtime[i][j]);
          Hist1[51]->Fill(sftx_dtime[i][j]);
          if(TofFlag){
            Hist1[71]->Fill(sftx_dtime[i][j]);
          }
        }
      }
    }

    bool Flag[nGate+1];
    bool Flag1[nGate+1];
    bool Flag2[nGate+1];
    bool Flag3[nGate+1];
    bool Flag_2[nGate+1];
    bool Flag1_2[nGate+1];
    bool Flag2_2[nGate+1];
    bool Flag3_2[nGate+1];
    bool Flag_MtxFlg[nGate+1];
    bool Flag1_MtxFlg[nGate+1];
    bool Flag2_MtxFlg[nGate+1];
    bool Flag3_MtxFlg[nGate+1];
    bool Flag_2_MtxFlg[nGate+1];
    bool Flag1_2_MtxFlg[nGate+1];
    bool Flag2_2_MtxFlg[nGate+1];
    bool Flag3_2_MtxFlg[nGate+1];
    for(int n=0; n<nGate+1; n++){
      Flag[n] = false;
      Flag1[n] = false;
      Flag2[n] = false;
      Flag3[n] = false;
      Flag_MtxFlg[n] = false;
      Flag1_MtxFlg[n] = false;
      Flag2_MtxFlg[n] = false;
      Flag3_MtxFlg[n] = false;
      Flag_2[n] = false;
      Flag1_2[n] = false;
      Flag2_2[n] = false;
      Flag3_2[n] = false;
      Flag_2_MtxFlg[n] = false;
      Flag1_2_MtxFlg[n] = false;
      Flag2_2_MtxFlg[n] = false;
      Flag3_2_MtxFlg[n] = false;
    }

    // Mtx Pattern ----------------------------
    for(int l=0; l < Mtx_prm.size(); l++){
      int i = 0;
      int j = 0;
      int min = 0;
      int max = 0;
      i = Mtx_prm.at(l).at(1);
      j = Mtx_prm.at(l).at(0);
      min = Mtx_prm.at(l).at(2);
      max = Mtx_prm.at(l).at(3) + 1;
      for(int m=0; m<16 ;m++){
        if( tofmt[i][m] != -999.0 ){ 
          Flag1[nGate]=true;
          if(trigflag[28]>0) Flag1_MtxFlg[nGate]=true;
        }
      }
      for(int m=0; m<sch_depth[j] ;m++){
        if( sch_time[j][m]!= -999. ){
          Flag2[nGate]=true;
          if(trigflag[28]>0) Flag2_MtxFlg[nGate]=true;
        }
      }
      for(int k = min; k < max; k++){
        for(int m=0; m<sftx_udepth[k] ;m++){
          if( sftx_utime[k][m] != -999. ){
            Flag3[nGate]=true;
            if(trigflag[28]>0) Flag3_MtxFlg[nGate]=true;
          }
        }
        for(int m=0; m<sftx_ddepth[k] ;m++){
          if( sftx_dtime[k][m] != -999. ){
            Flag3[nGate]=true;
            if(trigflag[28]>0) Flag3_MtxFlg[nGate]=true;
          }
        }
      }
      //      std::cout << i << "\t" << j <<  "\t" << min << "\t" << max << "\t" << std::endl;
      for(int n=0; n<nGate; n++){
        //          if(!Flag1[n] && tofmt[i][m]      > (double)TofMid - Gate[n] && tofmt[i][m]     < (double)TofMid + Gate[n] ) Flag1[n]=true;
        //          if(!Flag2[n] && sch_time[j][m]   > (double)SchMid - Gate[n] && sch_time[j][m]  < (double)SchMid + Gate[n] ) Flag2[n]=true;
        //          for(int k = min; k < max; k++){
        //            if(!Flag3[n] &&  sftx_utime[k][m] > (double)SftMid - Gate[n] && sftx_utime[k][m]< (double)SftMid + Gate[n] ) Flag3[n]=true;
        //            if(!Flag3[n] &&  sftx_dtime[k][m] > (double)SftMid - Gate[n] && sftx_dtime[k][m]< (double)SftMid + Gate[n] ) Flag3[n]=true;
        //          }
        for(int m=0; m<16 ;m++){
          if( tofmt[i][m]      > (double)TofMid - Gate[n] && tofmt[i][m]     < (double)TofMid + Gate[n] ){ 
//            Hist1[52+n]->Fill(tofmt[i][m]);
            Flag1[n]=true;
            if(trigflag[28]>0) Flag1_MtxFlg[n]=true;
          }
        }
        for(int m=0; m<sch_depth[j] ;m++){
          if( sch_time[j][m]   > (double)SchMid - Gate[n] && sch_time[j][m]  < (double)SchMid + Gate[n] ){
//            Hist1[57+n]->Fill(sch_time[j][m]);
            Flag2[n]=true;
            if(trigflag[28]>0) Flag2_MtxFlg[n]=true;
          }
        }
        for(int k = min; k < max; k++){
          for(int m=0; m<sftx_udepth[k] ;m++){
            if( sftx_utime[k][m] > (double)SftMid - Gate[n] && sftx_utime[k][m]< (double)SftMid + Gate[n] ){
//              Hist1[61+n]->Fill(sftx_utime[k][m]);
              Flag3[n]=true;
              if(trigflag[28]>0) Flag3_MtxFlg[n]=true;
            }
          }
          for(int m=0; m<sftx_ddepth[k] ;m++){
            if( sftx_dtime[k][m] > (double)SftMid - Gate[n] && sftx_dtime[k][m]< (double)SftMid + Gate[n] ){ 
//              Hist1[61+n]->Fill(sftx_dtime[k][m]);
              Flag3[n]=true;
              if(trigflag[28]>0) Flag3_MtxFlg[n]=true;
            }
          }
        }
      }
      for(int n=0; n<nGate+1; n++){
        if(Flag1[n]&&Flag2[n]&&Flag3[n]){
          Flag[n]=true;
        }
        if(Flag1_MtxFlg[n]&&Flag2_MtxFlg[n]&&Flag3_MtxFlg[n]){
          Flag_MtxFlg[n]=true;
        }
      }
      for(int n=0; n<nGate+1; n++){
        Flag1[n] = false;
        Flag2[n] = false;
        Flag3[n] = false;
        Flag1_MtxFlg[n] = false;
        Flag2_MtxFlg[n] = false;
        Flag3_MtxFlg[n] = false;
      }
    }

    // Mtx Pattern2 ----------------------------
    for(int l=0; l < Mtx_prm2.size(); l++){
      int i = 0;
      int j = 0;
      int min = 0;
      int max = 0;
      i = Mtx_prm2.at(l).at(1);
      j = Mtx_prm2.at(l).at(0);
      min = Mtx_prm2.at(l).at(2);
      max = Mtx_prm2.at(l).at(3) + 1;
      for(int m=0; m<16 ;m++){
        if( tofmt[i][m] != -999.0 ){ 
          Flag1_2[nGate]=true;
          if(trigflag[28]>0) Flag1_2_MtxFlg[nGate]=true;
        }
      }
      for(int m=0; m<sch_depth[j] ;m++){
        if( sch_time[j][m]!= -999. ){
          Flag2_2[nGate]=true;
          if(trigflag[28]>0) Flag2_2_MtxFlg[nGate]=true;
        }
      }
      for(int k = min; k < max; k++){
        for(int m=0; m<sftx_udepth[k] ;m++){
          if( sftx_utime[k][m] != -999. ){
            Flag3_2[nGate]=true;
            if(trigflag[28]>0) Flag3_2_MtxFlg[nGate]=true;
          }
        }
        for(int m=0; m<sftx_ddepth[k] ;m++){
          if( sftx_dtime[k][m] != -999. ){
            Flag3_2[nGate]=true;
            if(trigflag[28]>0) Flag3_2_MtxFlg[nGate]=true;
          }
        }
      }
      for(int n=0; n<nGate; n++){
        for(int m=0; m<16 ;m++){
          if( tofmt[i][m]      > (double)TofMid - Gate[n] && tofmt[i][m]     < (double)TofMid + Gate[n] ){ 
            Flag1_2[n]=true;
            if(trigflag[28]>0) Flag1_2_MtxFlg[n]=true;
          }
        }
        for(int m=0; m<sch_depth[j] ;m++){
          if( sch_time[j][m]   > (double)SchMid - Gate[n] && sch_time[j][m]  < (double)SchMid + Gate[n] ){
            Flag2_2[n]=true;
            if(trigflag[28]>0) Flag2_2_MtxFlg[n]=true;
          }
        }
        for(int k = min; k < max; k++){
          for(int m=0; m<sftx_udepth[k] ;m++){
            if( sftx_utime[k][m] > (double)SftMid - Gate[n] && sftx_utime[k][m]< (double)SftMid + Gate[n] ){
              Flag3_2[n]=true;
              if(trigflag[28]>0) Flag3_2_MtxFlg[n]=true;
            }
          }
          for(int m=0; m<sftx_ddepth[k] ;m++){
            if( sftx_dtime[k][m] > (double)SftMid - Gate[n] && sftx_dtime[k][m]< (double)SftMid + Gate[n] ){ 
              Flag3_2[n]=true;
              if(trigflag[28]>0) Flag3_2_MtxFlg[n]=true;
            }
          }
        }
      }
      for(int n=0; n<nGate+1; n++){
        if(Flag1_2[n]&&Flag2_2[n]&&Flag3_2[n]){
          Flag_2[n]=true;
        }
        if(Flag1_2_MtxFlg[n]&&Flag2_2_MtxFlg[n]&&Flag3_2_MtxFlg[n]){
          Flag_2_MtxFlg[n]=true;
        }
      }
      for(int n=0; n<nGate+1; n++){
        Flag1_2[n] = false;
        Flag2_2[n] = false;
        Flag3_2[n] = false;
        Flag1_2_MtxFlg[n] = false;
        Flag2_2_MtxFlg[n] = false;
        Flag3_2_MtxFlg[n] = false;
      }
    }

    for(int n=0; n<nGate+1; n++){
      if(Flag[n]){
        Count1[n]+=1;
      }
      if(Flag_MtxFlg[n]){
        Count1_MtxFlg[n]+=1;
      }
    }

    for(int n=0; n<nGate+1; n++){
      if(Flag_2[n]){
        Count1_2[n]+=1;
      }
      if(Flag_2_MtxFlg[n]){
        Count1_2_MtxFlg[n]+=1;
      }
    }
  }

  //-Canvas def---------------------------------------------------------------------------------------
  TCanvas *c1 = new TCanvas("c1","c1",1200,900);
  //-Hist Draw----------------------------------------------------------------------------------------

  c1->Print(pdf+"["); 
  c1->cd();

  for(int i=0; i<Hist1Max; i++){
    //   if(i==15 || i==16 || i==38) gPad->SetLogy(1);
//    Hist1[i]->GetXaxis()->SetLabelSize(0.05);
//    Hist1[i]->GetYaxis()->SetLabelSize(0.05);
//    Hist1[i]->GetXaxis()->SetTitleSize(0.05);
//    Hist1[i]->GetYaxis()->SetTitleSize(0.05);
//    Hist1[i]->GetYaxis()->SetDecimals(3);
  gStyle->SetOptStat(0);
    Hist1[i]->Draw();
    c1->Print(pdf);
    c1->Print(Form("%s/Mtx_Banch_run%05d_Hist1_%03d.pdf",pdfDhire.Data(),runnum,i));
    //   if(i==15 || i==16 || i==38) gPad->SetLogy(0);
    
  }
  //  for(int i=0; i<Hist2Max; i++){
  //  Hist2[i]->Draw("colz");
  //  c1->Print(pdf);
  //  c1->Print(Form("%s/Mtx_Banch_run%05d_Hist2_%03d.pdf",pdfDhire.Data(),runnum,i));
  //  }

  for(int n=0; n<nGate; n++){
    //    MtxEfficiency[n]= (double)Count1[n]/nentries;
    //    std::cout << "Total Event# is " << nentries << "\t" << Form("Count%d# is ",n+1) << Count1[n] << "\t" << "Efficiency is " << MtxEfficiency[n] << std::endl;
    MtxEfficiency[n]= (double)Count1[n]/Count1[nGate-1];
    std::cout << "Total Event# is " << Count1[nGate-1] << "\t" << Form("Count%d# is ",n+1) << Count1[n] << "\t" << "Efficiency is " << MtxEfficiency[n] << std::endl;
  }
  for(int n=0; n<nGate; n++){
    //    MtxEfficiency_MtxFlg[n]= (double)Count1_MtxFlg[n]/nentries_MtxFlg;
    MtxEfficiency_MtxFlg[n]= (double)Count1_MtxFlg[n]/ Count1_MtxFlg[nGate];
    std::cout << "Total Event# is " << nentries_MtxFlg << "\t" << Form("Count%d_MtxFlg# is ",nGate) << Count1_MtxFlg[nGate]  << "\t" << Form("Count%d_MtxFlg# is ",n+1) << Count1_MtxFlg[n] << "\t" << "Efficiency is " << MtxEfficiency_MtxFlg[n] << std::endl;
  }
  for(int n=0; n<nGate+1; n++){
    if(n==nGate){
      MtxEfficiency_2_MtxFlg[n]= (double)Count1_MtxFlg[n-1]/ Count1_MtxFlg[nGate];
      std::cout << "Total Event# is " << Count1_MtxFlg[nGate-1] << "\t" <<  Form("Count%d_MtxFlg# is ",n+1) << Count1_MtxFlg[n] << "\t" << "Efficiency is " << MtxEfficiency_2_MtxFlg[n] << std::endl;
    }else{
      MtxEfficiency_2_MtxFlg[n]= (double)Count1_2_MtxFlg[n]/ Count1_MtxFlg[nGate];
      std::cout << "Total Event# is " << Count1_MtxFlg[nGate-1] << "\t" <<  Form("Count%d_MtxFlg# is ",n+1) << Count1_2_MtxFlg[n] << "\t" << "Efficiency is " << MtxEfficiency_2_MtxFlg[n] << std::endl;
    }
  }
  for(int n=0; n<nGate; n++){
    MtxEfficiency_OldGate[n]= (double)Count1_MtxFlg[n]/ Count1_MtxFlg[nGate];
    std::cout << "Total Event# is " << Count1_MtxFlg[nGate] << "\t" <<  Form("Count%d_MtxFlg# is ",n+1) << Count1_MtxFlg[n] << "\t" << "Efficiency is " << MtxEfficiency_OldGate[n] << std::endl;
    MtxEfficiency_Gate[n]= (double)Count1_2_MtxFlg[n]/ Count1_MtxFlg[nGate];
    std::cout << "Total Event# is " << Count1_MtxFlg[nGate] << "\t" <<  Form("Count%d_MtxFlg# is ",n+1) << Count1_2_MtxFlg[n] << "\t" << "Efficiency is " << MtxEfficiency_Gate[n] << std::endl;
  }

  c1->SetGrid();
  c1->SetGridx();
  c1->SetGridy();

  TGraph *g1 = new TGraph(nGate, x, MtxEfficiency);
  TGraph *g2 = new TGraph(nGate, x, MtxEfficiency_MtxFlg);
  TGraph *g3 = new TGraph(nGate+1, x2, MtxEfficiency_2_MtxFlg);
  TGraph *g4 = new TGraph(nGate, Gate_d, MtxEfficiency_Gate);
  TGraph *g5 = new TGraph(nGate, Gate_d, MtxEfficiency_OldGate);
  g1->SetMarkerStyle(8);
  g1->SetMarkerColor(2);
  g1->SetMarkerSize(2);
  g1->GetXaxis()->SetRangeUser(0,5.5);
  g1->GetYaxis()->SetRangeUser(0,1);
  g1->Draw("AP");

  c1->Print(pdf);
  c1->Print(Form("%s/Mtx_Banch_run%05d_Graph.pdf",pdfDhire.Data(),runnum));

  g2->SetMarkerStyle(8);
  g2->SetMarkerColor(2);
  g2->SetMarkerSize(2);
  g2->GetXaxis()->SetRangeUser(0,5.5);
  g2->GetYaxis()->SetRangeUser(0,1);
  g2->Draw("AP");

  c1->Print(pdf);
  c1->Print(Form("%s/Mtx_Banch_run%05d_Graph_MtxFlg.pdf",pdfDhire.Data(),runnum));

  g3->SetMarkerStyle(8);
  g3->SetMarkerColor(2);
  g3->SetMarkerSize(2);
  g3->GetXaxis()->SetRangeUser(0,6.5);
  g3->GetYaxis()->SetRangeUser(0,1);
  g3->Draw("AP");

  c1->Print(pdf);
  c1->Print(Form("%s/Mtx_Banch_run%05d_Graph_MtxFlg_NewPat.pdf",pdfDhire.Data(),runnum));

  g4->SetMarkerStyle(8);
  g4->SetMarkerColor(1);
  g4->SetMarkerSize(2);
  g4->GetXaxis()->SetRangeUser(0,Gate[nGate-1]+10);
  g4->GetYaxis()->SetRangeUser(0,1);
  g4->GetXaxis()->SetTitle("Gate [ns]");
  g4->GetYaxis()->SetTitle("Accept");
  g4->GetYaxis()->SetDecimals(2);
  g4->Draw("AP");

  c1->Print(pdf);
  c1->Print(Form("%s/Mtx_Banch_run%05d_Graph_MtxFlg_NewPat_Accept.pdf",pdfDhire.Data(),runnum));

  g5->SetMarkerStyle(8);
  g5->SetMarkerColor(1);
  g5->SetMarkerSize(2);
  g5->GetXaxis()->SetRangeUser(0,Gate[nGate-1]+10);
  g5->GetYaxis()->SetRangeUser(0,1);
  g5->GetXaxis()->SetTitle("Gate [ns]");
  g5->GetYaxis()->SetTitle("Accept");
  g5->GetYaxis()->SetDecimals(2);
  g5->Draw("AP");

  c1->Print(pdf);
  c1->Print(Form("%s/Mtx_Banch_run%05d_Graph_MtxFlg_OldPat_Accept.pdf",pdfDhire.Data(),runnum));


  g5->Draw("AP");
  g4->SetMarkerColor(2);
  g4->SetMarkerStyle(8);
  g4->SetMarkerSize(2);
  g4->Draw("P");

  c1->Print(pdf);
  c1->Print(Form("%s/Mtx_Banch_run%05d_Graph_MtxFlg_OldAndNewPat_Accept.pdf",pdfDhire.Data(),runnum));

  std::ofstream fout1;
  fout1.open(Form("%s/dat/trigger/GateAccept.txt", anadir.Data()));
  for(int i=0; i<nGate; i++){
    fout1 << Gate_d[i] << "\t" << MtxEfficiency_Gate[i] << std::endl;
  }

  c1->Print(pdf+"]"); 

}

