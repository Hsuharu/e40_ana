#include <iostream>
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

using namespace std;

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
  "dec",
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
//
void mtx_banch(int month, int runnum){
  //////////////////////////////////////////////////////////
  //   This file has been automatically generated 
  //     (Wed Nov 28 17:12:44 2018 by ROOT version6.10/08)
  //   from TTree k0hodo/tree of DstKuramaEasirocHodoscope
  //   found on file: rootfile/run05126_DstKuramaEasirocHodoscope.root
  //////////////////////////////////////////////////////////


  gStyle->SetOptStat(1111110); 
  gStyle->SetOptFit(1); 


  //Reset ROOT and connect tree file
  gROOT->Reset();
  //   TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("rootfile/run05126_DstKuramaEasirocHodoscope.root");
  TString anadir=Form("%s/work/e40/ana",std::getenv("HOME")); 
  TString pdf = Form("%s/pdf/trigger/mtx_banch_run%05d.pdf", anadir.Data(),runnum);
  TString pdfDhire = Form("%s/pdf/trigger", anadir.Data());
  TFile *f = new TFile(Form("%s/analyzer_%s/rootfile/run%05d_Matrix.root", anadir.Data(),Month[month], runnum),"READ");
  TTree *mtx;
  f->GetObject("mtx",mtx);

  //Declaration of leaves types
  Int_t           evnum;
  Int_t           spill;
  Int_t           trignhits;
  Int_t           trigpat[17];
  Int_t           trigflag[32];
  Int_t           bh2nhits;
  Int_t           bh2hitpat[8];
  Double_t        bh2ua[8];
  Double_t        bh2ut[8][16];
  Double_t        bh2da[8];
  Double_t        bh2dt[8][16];
  Int_t           fpga_bh2mtnhits;
  Int_t           fpga_bh2mthitpat[8][16];
  Double_t        fpga_bh2mt[8][16];
  Int_t           tofnhits;
  Int_t           tofhitpat[24];
  Double_t        tofua[24];
  Double_t        tofut[24][16];
  Double_t        tofda[24];
  Double_t        tofdt[24][16];
  Double_t        bh2mt[8][16];
  Double_t        bh2de[8];
  Double_t        tofmt[24][16];
  Double_t        tofde[24];
  Double_t        t0[8][16];
  Double_t        ct0[8][16];
  Double_t        btof[11][8];
  Double_t        cbtof[11][8];
  Double_t        Time0Seg;
  Double_t        deTime0;
  Double_t        Time0;
  Double_t        CTime0;
  Double_t        Btof0Seg;
  Double_t        deBtof0;
  Double_t        Btof0;
  Double_t        CBtof0;
  Int_t           sch_nhits;
  Int_t           sch_hitpat[36];
  Double_t        sch_tdc[64][16];
  Double_t        sch_trailing[64][16];
  Double_t        sch_tot[64][16];
  Double_t        sch_time[64][16];
  Int_t           sch_depth[64];
  Int_t           sftx_nhits;
  Int_t           sftx_unhits;
  Int_t           sftx_dnhits;
  Int_t           sftx_uhitpat[123];
  Int_t           sftx_dhitpat[140];
  Double_t        sftx_utdc[256][16];
  Double_t        sftx_dtdc[256][16];
  Double_t        sftx_utrailing[256][16];
  Double_t        sftx_dtrailing[256][16];
  Double_t        sftx_utot[256][16];
  Double_t        sftx_dtot[256][16];
  Double_t        sftx_utime[256][16];
  Double_t        sftx_dtime[256][16];
  Int_t           sftx_udepth[256];
  Int_t           sftx_ddepth[256];

  // Set branch atatus.
  mtx->SetBranchStatus("*",0);  // disable all branches
  mtx->SetBranchStatus("evnum");
  mtx->SetBranchStatus("spill");
  mtx->SetBranchStatus("trignhits");
  mtx->SetBranchStatus("trigpat");
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
  mtx->SetBranchStatus("tofhitpat");
  mtx->SetBranchStatus("tofua");
  mtx->SetBranchStatus("tofut");
  mtx->SetBranchStatus("tofda");
  mtx->SetBranchStatus("tofdt");
//   mtx->SetBranchStatus("bh2mt");
//   mtx->SetBranchStatus("bh2de");
  mtx->SetBranchStatus("tofmt");
  mtx->SetBranchStatus("tofde");
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
  mtx->SetBranchStatus("sch_tdc");
  mtx->SetBranchStatus("sch_trailing");
  mtx->SetBranchStatus("sch_tot");
  mtx->SetBranchStatus("sch_time");
  mtx->SetBranchStatus("sch_depth");
  mtx->SetBranchStatus("sftx_nhits");
  mtx->SetBranchStatus("sftx_unhits");
  mtx->SetBranchStatus("sftx_dnhits");
  mtx->SetBranchStatus("sftx_uhitpat");
  mtx->SetBranchStatus("sftx_dhitpat");
  mtx->SetBranchStatus("sftx_utdc");
  mtx->SetBranchStatus("sftx_dtdc");
  mtx->SetBranchStatus("sftx_utrailing");
  mtx->SetBranchStatus("sftx_dtrailing");
  mtx->SetBranchStatus("sftx_utot");
  mtx->SetBranchStatus("sftx_dtot");
  mtx->SetBranchStatus("sftx_utime");
  mtx->SetBranchStatus("sftx_dtime");
  mtx->SetBranchStatus("sftx_udepth");
  mtx->SetBranchStatus("sftx_ddepth");


  // Set branch addresses.
  mtx->SetBranchAddress("evnum",&evnum);
  mtx->SetBranchAddress("spill",&spill);
  mtx->SetBranchAddress("trignhits",&trignhits);
  mtx->SetBranchAddress("trigpat",trigpat);
  mtx->SetBranchAddress("trigflag",trigflag);
//   mtx->SetBranchAddress("bh2nhits",&bh2nhits);
//   mtx->SetBranchAddress("bh2hitpat",bh2hitpat);
//   mtx->SetBranchAddress("bh2ua",bh2ua);
//   mtx->SetBranchAddress("bh2ut",bh2ut);
//   mtx->SetBranchAddress("bh2da",bh2da);
//   mtx->SetBranchAddress("bh2dt",bh2dt);
//   mtx->SetBranchAddress("fpga_bh2mtnhits",&fpga_bh2mtnhits);
//   mtx->SetBranchAddress("fpga_bh2mthitpat",fpga_bh2mthitpat);
//   mtx->SetBranchAddress("fpga_bh2mt",fpga_bh2mt);
  mtx->SetBranchAddress("tofnhits",&tofnhits);
  mtx->SetBranchAddress("tofhitpat",tofhitpat);
  mtx->SetBranchAddress("tofua",tofua);
  mtx->SetBranchAddress("tofut",tofut);
  mtx->SetBranchAddress("tofda",tofda);
  mtx->SetBranchAddress("tofdt",tofdt);
//   mtx->SetBranchAddress("bh2mt",bh2mt);
//   mtx->SetBranchAddress("bh2de",bh2de);
  mtx->SetBranchAddress("tofmt",tofmt);
  mtx->SetBranchAddress("tofde",tofde);
//   mtx->SetBranchAddress("t0",t0);
//   mtx->SetBranchAddress("ct0",ct0);
//   mtx->SetBranchAddress("btof",btof);
//   mtx->SetBranchAddress("cbtof",cbtof);
//   mtx->SetBranchAddress("Time0Seg",&Time0Seg);
//   mtx->SetBranchAddress("deTime0",&deTime0);
//   mtx->SetBranchAddress("Time0",&Time0);
//   mtx->SetBranchAddress("CTime0",&CTime0);
//   mtx->SetBranchAddress("Btof0Seg",&Btof0Seg);
//   mtx->SetBranchAddress("deBtof0",&deBtof0);
//   mtx->SetBranchAddress("Btof0",&Btof0);
//   mtx->SetBranchAddress("CBtof0",&CBtof0);
  mtx->SetBranchAddress("sch_nhits",&sch_nhits);
  mtx->SetBranchAddress("sch_hitpat",sch_hitpat);
  mtx->SetBranchAddress("sch_tdc",sch_tdc);
  mtx->SetBranchAddress("sch_trailing",sch_trailing);
  mtx->SetBranchAddress("sch_tot",sch_tot);
  mtx->SetBranchAddress("sch_time",sch_time);
  mtx->SetBranchAddress("sch_depth",sch_depth);
  mtx->SetBranchAddress("sftx_nhits",&sftx_nhits);
  mtx->SetBranchAddress("sftx_unhits",&sftx_unhits);
  mtx->SetBranchAddress("sftx_dnhits",&sftx_dnhits);
  mtx->SetBranchAddress("sftx_uhitpat",sftx_uhitpat);
  mtx->SetBranchAddress("sftx_dhitpat",sftx_dhitpat);
  mtx->SetBranchAddress("sftx_utdc",sftx_utdc);
  mtx->SetBranchAddress("sftx_dtdc",sftx_dtdc);
  mtx->SetBranchAddress("sftx_utrailing",sftx_utrailing);
  mtx->SetBranchAddress("sftx_dtrailing",sftx_dtrailing);
  mtx->SetBranchAddress("sftx_utot",sftx_utot);
  mtx->SetBranchAddress("sftx_dtot",sftx_dtot);
  mtx->SetBranchAddress("sftx_utime",sftx_utime);
  mtx->SetBranchAddress("sftx_dtime",sftx_dtime);
  mtx->SetBranchAddress("sftx_udepth",sftx_udepth);
  mtx->SetBranchAddress("sftx_ddepth",sftx_ddepth);


  //-para def-----------------------------------------------------------------------------------------
  double HULMHTDCCalib = -0.8333;
  double MaxBinValue=0.;

  int Gate1 = 60;
  int Gate2 = 30;
  int Gate3 = 20;
  int Gate4 = 10;

  int Hist1Max = 0;
  int Hist2Max = 0;

  //-hist def-----------------------------------------------------------------------------------------
  Hist1Max = 81;
  Hist2Max = 4;
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
  Hist1[35] = new TH1D("TofMtOr","TofMtOr",100,-10,90);
  Hist1[36] = new TH1D("TofMtOr Cut1","TofMtOrCut1",100,-10,90);
  Hist1[50] = new TH1D("TofMtOr Hitpat Cut1","TofMtOr Hitpat Cut1",25,0,24);
  Hist1[67] = new TH1D("TofMtOr Hitpat Cut5","TofMtOr Hitpat Cut5",25,0,24);
  Hist1[68] = new TH1D("TofMtOr Cut5","TofMtOr Cut5",200,-100,100);
  Hist1[69] = new TH1D("TofMtOr Hitpat Cut6","TofMtOr Hitpat Cut6",25,0,24);
  Hist1[70] = new TH1D("TofMtOr Cut6","TofMtOr Cut6",200,-100,100);

  //-Sch ----------------
  Hist1[37]= new TH1D("Sch Nhits" ,"Sch Nhits" ,20,0,20);
  Hist1[38]= new TH1D("Sch Hitpat","Sch Hitpat",65,0,65);
  Hist1[39]= new TH1D("Sch Depthpat","Sch Depthpat",65,0,65);
  Hist1[40]= new TH1D("Sch Tdc"   ,"Sch Tdc"   ,100,0,1000);
  Hist1[51]= new TH1D("Sch Hitpat Cut2","Sch Hitpat Cut2",65,0,65);
  Hist1[52]= new TH1D("Sch Tdc Cut2"   ,"Sch Tdc Cut2"   ,100,0,1000);
  Hist1[59]= new TH1D("Sch Time"   ,"Sch Time"   ,100,-100,100);
  Hist1[60]= new TH1D("Sch Time Cut2"   ,"Sch Time Cut2"   ,100,-100,100);
  Hist1[71]= new TH1D("Sch Hitpat Cut5","Sch Hitpat Cut5",65,0,65);
  Hist1[72]= new TH1D("Sch Time Cut5"   ,"Sch Time Cut5"   ,100,-100,100);
  Hist1[73]= new TH1D("Sch Hitpat Cut6","Sch Hitpat Cut6",65,0,65);
  Hist1[74]= new TH1D("Sch Time Cut6"   ,"Sch Time Cut6"   ,100,-100,100);

  //-Sft ----------------
  Hist1[41] = new TH1D("SftX U Nhits","Sft U Nhits",50,0,50);
  Hist1[42] = new TH1D("SftX D Nhits","Sft D Nhits",50,0,50);
  Hist1[43] = new TH1D("SftNhits","SftNhits",50,0,50);
  Hist1[44] = new TH1D("Sft U Hitpat","Sft U Hitpat",256,0,256);
  Hist1[45] = new TH1D("Sft D Hitpat","Sft D Hitpat",256,0,256);
  Hist1[46] = new TH1D("SftHitpat","SftHitpat",256,0,256);
  Hist1[47] = new TH1D("Sft U Tdc","Sft U Tdc",1000,0,1000);
  Hist1[48] = new TH1D("Sft D Tdc","Sft D Tdc",1000,0,1000);
  Hist1[49] = new TH1D("SftTdc","SftTdc",1000,0,1000);
  Hist1[53] = new TH1D("Sft U Hitpat Cut3","Sft U Hitpat Cut3",256,0,256);
  Hist1[55] = new TH1D("SftHitpat Cut3 or Cut4","SftHitpat Cut3 or Cut4",256,0,256);
  Hist1[56] = new TH1D("Sft U Tdc Cut3","Sft U Tdc Cut3",1000,0,1000);
  Hist1[61] = new TH1D("Sft U Time","Sft U Time",200,-100,100);
  Hist1[62] = new TH1D("Sft D Time","Sft D Time",200,-100,100);
  Hist1[64] = new TH1D("Sft U Time Cut3","Sft U Time Cut3",200,-100,100);
  Hist1[58] = new TH1D("SftTdc Cut3","SftTdc Cut3",1000,0,1000);
  Hist1[54] = new TH1D("Sft D Hitpat Cut4","Sft D Hitpat Cut4",256,0,256);
  Hist1[57] = new TH1D("Sft D Tdc Cut4","Sft D Tdc Cut4",1000,0,1000);
  Hist1[65] = new TH1D("Sft D Time Cut4","Sft D Time Cut4",200,-100,100);
  Hist1[63] = new TH1D("SftTime","SftTime",200,-100,100);
  Hist1[66] = new TH1D("SftTime Cut3 or Cut4","SftTime Cut3 or Cut4",200,-100,100);
  Hist1[75] = new TH1D("Sft U Hitpat Cut5","Sft U Hitpat Cut5",256,0,256);
  Hist1[76] = new TH1D("Sft U Time Cut5","Sft U Time Cut5",200,-100,100);
  Hist1[77] = new TH1D("Sft D Hitpat Cut6","Sft D Hitpat Cut6",256,0,256);
  Hist1[78] = new TH1D("Sft D Time Cut6","Sft D Time Cut6",200,-100,100);
  Hist1[79] = new TH1D("SftHitpat Cut5 or Cut6","SftHitpat Cut5 or Cut6",256,0,256);
  Hist1[80] = new TH1D("SftTime Cut5 or Cut6","SftTime Cut5 or Cut6",200,-100,100);


  Hist2[0]= new TH2D("TofMtOr Time % Sch Time Cut5","TofMtOr Time % Sch Time Cut5",200,-100,100,200,-100,100);
  Hist2[1]= new TH2D("TofMtOr Time % Sch Time Cut6","TofMtOr Time % Sch Time Cut6",200,-100,100,200,-100,100);
  Hist2[2]= new TH2D("Sft U Time % Sch Time Cut5","Sft U Time % Sch Time Cut5",200,-100,100,200,-100,100);
  Hist2[3]= new TH2D("Sft D Time % Sch Time Cut6","Sft D Time % Sch Time Cut6",200,-100,100,200,-100,100);
  Hist2[4]= new TH2D("TofMtOr Time % Sch Time Cut7","TofMtOr Time % Sch Time Cut7",200,-100,100,200,-100,100);
  Hist2[5]= new TH2D("Sft U Time % Sch Time Cut7","Sft U Time % Sch Time Cut7",200,-100,100,200,-100,100);
  Hist2[6]= new TH2D("TofMtOr Time % Sch Time Cut8","TofMtOr Time % Sch Time Cut8",200,-100,100,200,-100,100);
  Hist2[7]= new TH2D("Sft U Time % Sch Time Cut8","Sft U Time % Sch Time Cut8",200,-100,100,200,-100,100);
  Hist2[8]= new TH2D("TofMtOr Time % Sch Time Cut9","TofMtOr Time % Sch Time Cut9",200,-100,100,200,-100,100);
  Hist2[9]= new TH2D("Sft U Time % Sch Time Cut9","Sft U Time % Sch Time Cut9",200,-100,100,200,-100,100);
  Hist2[10]= new TH2D("TofMtOr Time % Sch Time Cut10","TofMtOr Time % Sch Time Cut10",200,-100,100,200,-100,100);
  Hist2[11]= new TH2D("Sft U Time % Sch Time Cut10","Sft U Time % Sch Time Cut10",200,-100,100,200,-100,100);

  // m2 - momentum ...------

//-Legend def --------------------------------------------------------------------------------------
//  TLegend *Leg1 = new TLegend(0.1,0.7,0.48,0.9);
  TLegend *Leg1 = new TLegend(0.78,0.775,0.98,0.935);
  TLegend *Leg2 = new TLegend(0.78,0.775,0.98,0.935);

//-Event Loop --------------------------------------------------------------------------------------
//   Long64_t nentries = mtx->GetEntries();
  Long64_t nentries =10000;

  Long64_t nbytes = 0;
  for (Long64_t s=0; s<nentries;s++) {
    nbytes += mtx->GetEntry(s);
    if(trigflag[17]<=0) continue;
    if(trigflag[28]<=0) continue;

    // Trigger Flag -----------------------
    for(int i=0; i<32; i++){
      Hist1[i]->Fill(trigflag[i]);
    }

    Hist1[32]->Fill(tofnhits);

    // TofMtOr ----------------------------
    for(int i=0; i<NumOfSegTOF; i++){
      for(int j=0; j<16; j++){
        if(tofmt[i][j]==-999)   continue;
        Hist1[33]->Fill(i);
        Hist1[34]->Fill(j);
        Hist1[35]->Fill(tofmt[i][j]);
        if(tofnhits!=1)         continue;    
        if(tofmt[i][1]!=-999)   continue; //Cut1
        Hist1[36]->Fill(tofmt[i][0]);
        Hist1[50]->Fill(i);
      }
    }

    // Sch --------------------------------
    Hist1[37]->Fill(sch_nhits);
    for(int i=0; i<sch_nhits; i++){
      Hist1[38]->Fill(sch_hitpat[i]);
    }
    for(int i=0; i<NumOfSegSCH; i++){
      Hist1[39]->Fill(sch_depth[i]);
      for(int k=0; k<16; k++){
        if(sch_tdc[i][k]==-999) continue;
        Hist1[40]->Fill(sch_tdc[i][k]);
        Hist1[59]->Fill(sch_time[i][k]);
        if(sch_nhits!=1) continue;
        if(sch_depth[i]!=1) continue;
        if(sch_hitpat[0]!=i) continue; //Cut2
        Hist1[51]->Fill(i);
        Hist1[52]->Fill(sch_tdc[i][k]);
        Hist1[60]->Fill(sch_time[i][k]);
      }
    }

    // Sft X ------------------------------
    Hist1[41]->Fill(sftx_unhits);
    Hist1[42]->Fill(sftx_dnhits);
    Hist1[43]->Fill(sftx_unhits);
    Hist1[43]->Fill(sftx_dnhits);
    for(int i=0; i<94; i++){
      Hist1[44]->Fill(sftx_uhitpat[i]);
      Hist1[46]->Fill(sftx_uhitpat[i]);
    }
    for(int i=0; i<49; i++){
      Hist1[45]->Fill(sftx_dhitpat[i]+0.5);
      Hist1[46]->Fill(sftx_dhitpat[i]+0.5);
    }
    for(int i=0; i<NumOfSegSFT_X; i++){
      for(int j=0; j<16; j++){
        if(sftx_utdc[i][j]!=-999){
          Hist1[47]->Fill(sftx_utdc[i][j]);
          Hist1[49]->Fill(sftx_utdc[i][j]);
          Hist1[61]->Fill(sftx_utime[i][j]);
          Hist1[63]->Fill(sftx_utime[i][j]);
        }
        if(sftx_dtdc[i][j]!=-999){
          Hist1[48]->Fill(sftx_dtdc[i][j]);
          Hist1[49]->Fill(sftx_dtdc[i][j]);
          Hist1[62]->Fill(sftx_dtime[i][j]);
          Hist1[63]->Fill(sftx_dtime[i][j]);
        }
        if(sftx_unhits==1){ //Cut3
          if(sftx_udepth[i]!=1) continue;
          if(sftx_uhitpat[0]==i){
            Hist1[53]->Fill(i);
            Hist1[55]->Fill(i);
            Hist1[56]->Fill(sftx_utdc[i][j]);
            Hist1[58]->Fill(sftx_utdc[i][j]);
            Hist1[64]->Fill(sftx_utime[i][j]);
            Hist1[66]->Fill(sftx_utime[i][j]);
          }
        }
        if(sftx_dnhits==1){ //Cut4
          if(sftx_ddepth[i]!=1) continue;
          if(sftx_dhitpat[0]==i){
            Hist1[54]->Fill(i);
            Hist1[55]->Fill(i);
            Hist1[57]->Fill(sftx_dtdc[i][j]);
            Hist1[58]->Fill(sftx_dtdc[i][j]);
            Hist1[65]->Fill(sftx_dtime[i][j]);
            Hist1[66]->Fill(sftx_dtime[i][j]);
          }
        }
      }
    }

    // All Mtx Detector -------------------
    // TofMtOr --------------------
    for(int i=0; i<NumOfSegTOF; i++){
      for(int j=0; j<16; j++){
        if(tofmt[i][j]==-999)   continue;
        if(tofnhits!=1)         continue;    
        if(tofmt[i][1]!=-999)   continue;
        // Sch ------------------------
        for(int k=0; k<NumOfSegSCH; k++){
          for(int l=0; l<16; l++){
            if(sch_tdc[k][l]==-999) continue;
            if(sch_nhits!=1) continue;
            if(sch_depth[k]!=1) continue;
            if(sch_hitpat[0]!=k) continue;
            // Sft X ----------------------
            for(int m=0; m<NumOfSegSFT_X; m++){
              if(sftx_unhits==1){
                if(sftx_udepth[m]!=1) continue;
                if(sftx_uhitpat[0]==m){
                  Hist1[67]->Fill(i);
                  Hist1[68]->Fill(tofmt[i][0]);
                  Hist1[71]->Fill(k);
                  Hist1[72]->Fill(sch_time[k][0]);
                  Hist1[75]->Fill(m);
                  Hist1[79]->Fill(m);
                  Hist1[76]->Fill(sftx_utime[m][0]);
                  Hist1[80]->Fill(sftx_utime[m][0]);
                  Hist2[0]->Fill(sch_time[k][0],tofmt[i][0]);
                  Hist2[1]->Fill(sch_time[k][0],sftx_utime[m][0]);
                  if(   -Gate1<tofmt[i][0]     &&tofmt[i][0]     <Gate1
                     && -Gate1<sch_time[k][0]  &&tsch_time[k]    <Gate1
                     && -Gate1<sftx_utime[m][0]&&sftx_utime[m][0]<Gate1
                    ) continue; //Cut7
                  Hist2[4]->Fill(sch_time[k][0],tofmt[i][0]);
                  Hist2[5]->Fill(sch_time[k][0],sftx_utime[m][0]);
                  if(   -Gate2<tofmt[i][0]     &&tofmt[i][0]     <Gate2
                     && -Gate2<sch_time[k][0]  &&tsch_time[k]    <Gate2
                     && -Gate2<sftx_utime[m][0]&&sftx_utime[m][0]<Gate2
                    ) continue; //Cut8
                  Hist2[6]->Fill(sch_time[k][0],tofmt[i][0]);
                  Hist2[7]->Fill(sch_time[k][0],sftx_utime[m][0]);
                  if(   -Gate3<tofmt[i][0]     &&tofmt[i][0]     <Gate3
                     && -Gate3<sch_time[k][0]  &&tsch_time[k]    <Gate3
                     && -Gate3<sftx_utime[m][0]&&sftx_utime[m][0]<Gate3
                    ) continue; //Cut9
                  Hist2[8]->Fill(sch_time[k][0],tofmt[i][0]);
                  Hist2[9]->Fill(sch_time[k][0],sftx_utime[m][0]);
                  if(   -Gate4<tofmt[i][0]     &&tofmt[i][0]     <Gate4
                     && -Gate4<sch_time[k][0]  &&tsch_time[k]    <Gate4
                     && -Gate4<sftx_utime[m][0]&&sftx_utime[m][0]<Gate4
                    ) continue; //Cut10
                  Hist2[10]->Fill(sch_time[k][0],tofmt[i][0]);
                  Hist2[11]->Fill(sch_time[k][0],sftx_utime[m][0]);
                }
              }
              if(sftx_dnhits==1){
                if(sftx_ddepth[m]!=1) continue;
                if(sftx_dhitpat[0]==m){
                  Hist1[69]->Fill(i);
                  Hist1[70]->Fill(tofmt[i][0]);
                  Hist1[73]->Fill(k);
                  Hist1[74]->Fill(sch_time[k][0]);
                  Hist1[77]->Fill(m);
                  Hist1[79]->Fill(m);
                  Hist1[78]->Fill(sftx_dtime[m][0]);
                  Hist1[80]->Fill(sftx_dtime[m][0]);
                  Hist2[2]->Fill(sch_time[k][0],tofmt[i][0]);
                  Hist2[3]->Fill(sch_time[k][0],sftx_dtime[m][0]);
                }
              }
            }
          }
        }
      }
    }
  }

  //-Canvas def---------------------------------------------------------------------------------------
  TCanvas *c1 = new TCanvas("c1","c1",1200,900);

  //  c1->Divide();

  c1->Print(pdf+"["); 
  //-Hist Draw----------------------------------------------------------------------------------------
  c1->cd();
  for(int i=0; i<Hist1Max; i++){
    //   if(i==15 || i==16 || i==38) gPad->SetLogy(1);
    Hist1[i]->Draw();
    c1->Print(pdf);
    c1->Print(Form("%s/mtx_banch_run%05d_Hist1_%03d.pdf",pdfDhire.Data(),runnum,i));
    //   if(i==15 || i==16 || i==38) gPad->SetLogy(0);
  }
  for(int i=0; i<Hist2Max; i++){
  Hist2[i]->Draw("colz");
  c1->Print(pdf);
  c1->Print(Form("%s/mtx_banch_run%05d_Hist2_%03d.pdf",pdfDhire.Data(),runnum,i));
  }



  c1->Print(pdf+"]"); 

}

