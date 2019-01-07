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
void Mtx_Banch(int month, int runnum){
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
  int Gate4 = 15;

  int Hist1Max = 0;
  int Hist2Max = 0;

  int Hist1Max_All = 0;
  int Hist2Max_All = 0;

  //-hist def-----------------------------------------------------------------------------------------
  Hist1Max = 81;
  Hist2Max = 12;
  TH1D *Hist1[Hist1Max];
  TH2D *Hist2[Hist2Max];

  Hist1Max_All = 3;
  Hist2Max_All = 3;
  TH1D *Hist1_All[Hist1Max_All];
  TH2D *Hist2_All[Hist2Max_All];

  //-Trigger Flag -------
  for(int i=0;i<32;i++){
    Hist1[i]= new TH1D(Form("TrigFlag %s",TriggerFlag[i]),Form("TrigFlag %s",TriggerFlag[i]),1000,0,2100);
  }
  //-Tof ----------------
  Hist1[32] = new TH1D("TofMtOr Nhits","TofMtOr Nhits",20,0,20);
  Hist1[33] = new TH1D("TofMtOr Hitpat","TofMtOr Hitpat",25,0,24);
  Hist1[34] = new TH1D("TofMtOr DepthPat","TofMtOrDepthPat",20,0,20);
  Hist1[35] = new TH1D("TofMtOr","TofMtOr",100,-10,90);

  //-Sch ----------------
  Hist1[36]= new TH1D("Sch Nhits" ,"Sch Nhits" ,20,0,20);
  Hist1[37]= new TH1D("Sch Hitpat","Sch Hitpat",65,0,65);
  Hist1[38]= new TH1D("Sch Depthpat","Sch Depthpat",65,0,65);
  Hist1[39]= new TH1D("Sch Tdc"   ,"Sch Tdc"   ,100,0,1000);
  Hist1[40]= new TH1D("Sch Time"   ,"Sch Time"   ,100,-100,100);

  //-SftX ----------------
  Hist1[41] = new TH1D("SftX U Nhits","SftX U Nhits",50,0,50);
  Hist1[42] = new TH1D("SftX D Nhits","SftX D Nhits",50,0,50);
  Hist1[43] = new TH1D("SftXNhits","SftXNhits",50,0,50);
  Hist1[44] = new TH1D("SftX U Hitpat","SftX U Hitpat",256,0,256);
  Hist1[45] = new TH1D("SftX D Hitpat","SftX D Hitpat",256,0,256);
  Hist1[46] = new TH1D("SftXHitpat","SftXHitpat",256,0,256);
  Hist1[47] = new TH1D("SftX U Tdc","SftX U Tdc",1000,0,1000);
  Hist1[48] = new TH1D("SftX D Tdc","SftX D Tdc",1000,0,1000);
  Hist1[49] = new TH1D("SftXTdc","SftXTdc",1000,0,1000);
  Hist1[50] = new TH1D("SftX U Time","SftX U Time",200,-100,100);
  Hist1[51] = new TH1D("SftX D Time","SftX D Time",200,-100,100);
  Hist1[52] = new TH1D("SftXTime","SftXTime",200,-100,100);

//-Legend def --------------------------------------------------------------------------------------
//  TLegend *Leg1 = new TLegend(0.1,0.7,0.48,0.9);
  TLegend *Leg1 = new TLegend(0.78,0.775,0.98,0.935);
  TLegend *Leg2 = new TLegend(0.78,0.775,0.98,0.935);

//-Event Loop --------------------------------------------------------------------------------------
  Long64_t nentries = mtx->GetEntries();
//  Long64_t nentries =10000;

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
        if(sch_tdc[i][k]==-999) continue;
        if(sch_time[i][k]==-999) continue;
        Hist1[39]->Fill(sch_tdc[i][k]);
        Hist1[40]->Fill(sch_time[i][k]);
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
          Hist1[50]->Fill(sftx_utime[i][j]);
          Hist1[52]->Fill(sftx_utime[i][j]);
        }
        if(sftx_dtdc[i][j]!=-999){
          Hist1[48]->Fill(sftx_dtdc[i][j]);
          Hist1[49]->Fill(sftx_dtdc[i][j]);
          Hist1[51]->Fill(sftx_dtime[i][j]);
          Hist1[52]->Fill(sftx_dtime[i][j]);
        }
      }
    }
  }

  //-Canvas def---------------------------------------------------------------------------------------
  TCanvas *c1 = new TCanvas("c1","c1",1200,900);

//  c1->Divide();

//-Hist Draw----------------------------------------------------------------------------------------

//  c1->Print(pdf+"["); 
//  c1->cd();
//  for(int i=0; i<Hist1Max; i++){
//    //   if(i==15 || i==16 || i==38) gPad->SetLogy(1);
//    Hist1[i]->Draw();
//    c1->Print(pdf);
//    c1->Print(Form("%s/mtx_banch_run%05d_Hist1_%03d.pdf",pdfDhire.Data(),runnum,i));
//    //   if(i==15 || i==16 || i==38) gPad->SetLogy(0);
//  }
//  for(int i=0; i<Hist2Max; i++){
//  Hist2[i]->Draw("colz");
//  c1->Print(pdf);
//  c1->Print(Form("%s/mtx_banch_run%05d_Hist2_%03d.pdf",pdfDhire.Data(),runnum,i));
//  }
//  c1->Print(pdf+"]"); 

  c1->cd();
  c1->Print(pdf_All+"["); 
  for(int i=0; i<Hist1Max_All; i++){
    //   if(i==15 || i==16 || i==38) gPad->SetLogy(1);
    Hist1_All[i]->Draw();
    c1->Print(pdf_All);
    c1->Print(Form("%s/mtx_banch_run%05d_Hist1_All_%03d.pdf",pdfDhire.Data(),runnum,i));
    //   if(i==15 || i==16 || i==38) gPad->SetLogy(0);
  }
  c1->Print(pdf_All+"]"); 


}

