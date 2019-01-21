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

void Mtx_Banch2(int month, int runnum){
  //Matrix Patern txt file PATH -----------------------------------------------------------------------
  TString anadir=Form("%s/work/e40/ana",std::getenv("HOME")); 
  TString filein1=Form("%s/analyzer_%s/param/MATRIXSFT/SFT_table.txt.2018Jun.3_1",anadir.Data(),Month[month] ); 

  std::ifstream fin1(filein1);

  // Param Vector Dif ----------------------------------------------------------------------
  std::vector<std::vector<int>> Mtx_prm; 
  std::string line;
  int preSCH = 0;
  std::vector<std::vector<int>> sch_tof; 
  std::vector<int> SCH_Seg; 
  std::vector<int> TOF_Min; 
  std::vector<int> TOF_Max; 


  // Error Out ----------------------------------------------------------------------------------------
  if(fin1.fail() ){
    std::cerr << "file1" << std::endl;
    exit(0); 
  }  

  if( !eq3(SCH_Seg.size(),TOF_Min.size(),TOF_Max.size()) ){
    std::cerr << "Size Not Same" << std::endl;
  }

  while(std::getline(fin1, line)){
    double sch=-1, tof=-1, sft_min=-1, sft_max=-1;
    std::istringstream input_line( line );
    std::vector<int> inner;
    if( input_line >> sch >> tof >> sft_min >> sft_max ){
      inner.push_back(sch);
      inner.push_back(tof);
      inner.push_back(sft_min-11);
      inner.push_back(sft_max-1);
      Mtx_prm.push_back(inner);
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
  TString pdf = Form("%s/pdf/trigger/Mtx_Banch2_run%05d.pdf", anadir.Data(),runnum);
  TString pdfDhire = Form("%s/pdf/trigger", anadir.Data());
//  TFile *f = new TFile(Form("%s/analyzer_%s/rootfile/run%05d_Matrix.root", anadir.Data(),Month[month], runnum),"READ");
  TFile *f = new TFile(Form("%s/analyzer_%s/rootfile/run%05d_DstPiKAna2.root", anadir.Data(),Month[month], runnum),"READ");
  TTree *pik;
  f->GetObject("pik",pik);

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
//  Int_t           tofnhits;
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
//  Int_t           sch_nhits;
//  Int_t           sch_hitpat[36];
//  Double_t        sch_tdc[64][16];
//  Double_t        sch_trailing[64][16];
//  Double_t        sch_tot[64][16];
  Double_t        sch_time[64][16];
  Int_t           sch_depth[64];
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
   Double_t        vtx[12];
   Double_t        vty[12];
   Double_t        vtz[12];
   Double_t        MissMass[12];
   Int_t           ntKurama;
   Double_t        chisqrKurama[4];
   Double_t        pKurama[4];
   Double_t        qKurama[4];
   Double_t        m2[4];

  // Set branch atatus.
  pik->SetBranchStatus("*",0);  // disable all branches
    pik->SetBranchStatus("evnum");
  //  pik->SetBranchStatus("spill");
  //  pik->SetBranchStatus("trignhits");
  //  pik->SetBranchStatus("trigpat");
    pik->SetBranchStatus("trigflag");
  //   pik->SetBranchStatus("bh2nhits");
  //   pik->SetBranchStatus("bh2hitpat");
  //   pik->SetBranchStatus("bh2ua");
  //   pik->SetBranchStatus("bh2ut");
  //   pik->SetBranchStatus("bh2da");
  //   pik->SetBranchStatus("bh2dt");
  //   pik->SetBranchStatus("fpga_bh2mtnhits");
  //   pik->SetBranchStatus("fpga_bh2mthitpat");
  //   pik->SetBranchStatus("fpga_bh2mt");
//    pik->SetBranchStatus("tofnhits");
  //  pik->SetBranchStatus("tofhitpat");
  //  pik->SetBranchStatus("tofua");
  //  pik->SetBranchStatus("tofut");
  //  pik->SetBranchStatus("tofda");
  //  pik->SetBranchStatus("tofdt");
  //   pik->SetBranchStatus("bh2mt");
  //   pik->SetBranchStatus("bh2de");
  pik->SetBranchStatus("tofmt");
  //  pik->SetBranchStatus("tofde");
  //   pik->SetBranchStatus("t0");
  //   pik->SetBranchStatus("ct0");
  //   pik->SetBranchStatus("btof");
  //   pik->SetBranchStatus("cbtof");
  //   pik->SetBranchStatus("Time0Seg");
  //   pik->SetBranchStatus("deTime0");
  //   pik->SetBranchStatus("Time0");
  //   pik->SetBranchStatus("CTime0");
  //   pik->SetBranchStatus("Btof0Seg");
  //   pik->SetBranchStatus("deBtof0");
  //   pik->SetBranchStatus("Btof0");
  //   pik->SetBranchStatus("CBtof0");
//    pik->SetBranchStatus("sch_nhits");
    pik->SetBranchStatus("sch_hitpat");
  //  pik->SetBranchStatus("sch_tdc");
  //  pik->SetBranchStatus("sch_trailing");
  //  pik->SetBranchStatus("sch_tot");
  pik->SetBranchStatus("sch_time");
    pik->SetBranchStatus("sch_depth");
  //  pik->SetBranchStatus("sftx_utdc");
  //  pik->SetBranchStatus("sftx_dtdc");
  //  pik->SetBranchStatus("sftx_utrailing");
  //  pik->SetBranchStatus("sftx_dtrailing");
  //  pik->SetBranchStatus("sftx_utot");
  //  pik->SetBranchStatus("sftx_dtot");
  pik->SetBranchStatus("sftx_utime");
  pik->SetBranchStatus("sftx_dtime");
    pik->SetBranchStatus("sftx_udepth");
    pik->SetBranchStatus("sftx_ddepth");
   pik->SetBranchStatus("ntKurama");
   pik->SetBranchStatus("chisqrKurama");
   pik->SetBranchStatus("pKurama");
   pik->SetBranchStatus("qKurama");
   pik->SetBranchStatus("m2");
   pik->SetBranchStatus("vtx");
   pik->SetBranchStatus("vty");
   pik->SetBranchStatus("vtz");
   pik->SetBranchStatus("MissMass");


  // Set branch addresses.
    pik->SetBranchAddress("evnum",&evnum);
  //  pik->SetBranchAddress("spill",&spill);
  //  pik->SetBranchAddress("trignhits",&trignhits);
  //  pik->SetBranchAddress("trigpat",trigpat);
    pik->SetBranchAddress("trigflag",trigflag);
  //  pik->SetBranchAddress("bh2nhits",&bh2nhits);
  //  pik->SetBranchAddress("bh2hitpat",bh2hitpat);
  //  pik->SetBranchAddress("bh2ua",bh2ua);
  //  pik->SetBranchAddress("bh2ut",bh2ut);
  //  pik->SetBranchAddress("bh2da",bh2da);
  //  pik->SetBranchAddress("bh2dt",bh2dt);
  //  pik->SetBranchAddress("fpga_bh2mtnhits",&fpga_bh2mtnhits);
  //  pik->SetBranchAddress("fpga_bh2mthitpat",fpga_bh2mthitpat);
  //  pik->SetBranchAddress("fpga_bh2mt",fpga_bh2mt);
//    pik->SetBranchAddress("tofnhits",&tofnhits);
  //  pik->SetBranchAddress("tofhitpat",tofhitpat);
  //  pik->SetBranchAddress("tofua",tofua);
  //  pik->SetBranchAddress("tofut",tofut);
  //  pik->SetBranchAddress("tofda",tofda);
  //  pik->SetBranchAddress("tofdt",tofdt);
  //  pik->SetBranchAddress("bh2mt",bh2mt);
  //  pik->SetBranchAddress("bh2de",bh2de);
  pik->SetBranchAddress("tofmt",tofmt);
  //  pik->SetBranchAddress("tofde",tofde);
  //  pik->SetBranchAddress("t0",t0);
  //  pik->SetBranchAddress("ct0",ct0);
  //  pik->SetBranchAddress("btof",btof);
  //  pik->SetBranchAddress("cbtof",cbtof);
  //  pik->SetBranchAddress("Time0Seg",&Time0Seg);
  //  pik->SetBranchAddress("deTime0",&deTime0);
  //  pik->SetBranchAddress("Time0",&Time0);
  //  pik->SetBranchAddress("CTime0",&CTime0);
  //  pik->SetBranchAddress("Btof0Seg",&Btof0Seg);
  //  pik->SetBranchAddress("deBtof0",&deBtof0);
  //  pik->SetBranchAddress("Btof0",&Btof0);
  //  pik->SetBranchAddress("CBtof0",&CBtof0);
  //  pik->SetBranchAddress("sch_tdc",sch_tdc);
  //  pik->SetBranchAddress("sch_trailing",sch_trailing);
  //  pik->SetBranchAddress("sch_tot",sch_tot);
  pik->SetBranchAddress("sch_time",sch_time);
    pik->SetBranchAddress("sch_depth",sch_depth);
  //  pik->SetBranchAddress("sftx_utdc",sftx_utdc);
  //  pik->SetBranchAddress("sftx_dtdc",sftx_dtdc);
  //  pik->SetBranchAddress("sftx_utrailing",sftx_utrailing);
  //  pik->SetBranchAddress("sftx_dtrailing",sftx_dtrailing);
  //  pik->SetBranchAddress("sftx_utot",sftx_utot);
  //  pik->SetBranchAddress("sftx_dtot",sftx_dtot);
  pik->SetBranchAddress("sftx_utime",sftx_utime);
  pik->SetBranchAddress("sftx_dtime",sftx_dtime);
    pik->SetBranchAddress("sftx_udepth",sftx_udepth);
    pik->SetBranchAddress("sftx_ddepth",sftx_ddepth);
     pik->SetBranchAddress("ntKurama",&ntKurama);
     pik->SetBranchAddress("chisqrKurama",chisqrKurama);
     pik->SetBranchAddress("pKurama",pKurama);
     pik->SetBranchAddress("qKurama",qKurama);
     pik->SetBranchAddress("m2",m2);
     pik->SetBranchAddress("vtx",vtx);
     pik->SetBranchAddress("vty",vty);
     pik->SetBranchAddress("vtz",vtz);
     pik->SetBranchAddress("MissMass",MissMass);


  //-para def-----------------------------------------------------------------------------------------
  double HULMHTDCCalib = -0.8333;
  double MaxBinValue=0.;

  int nGate = 6;
  int Gate[] = {15,20,30,40,60,120};

  double TofMid = 10.;
  double SchMid = 0.;
  double SftMid = 0.;

  int Hist1Max = 0;
  int Hist2Max = 0;

  int SigmaCount;
  int Count1[nGate];
  int Count1_MtxFlg[nGate];
  double MtxEfficiency[nGate];
  double MtxEfficiency_MtxFlg[nGate];
  double x[nGate];
  for(int n=0; n<nGate; n++){
    Count1[n] = 0;
    Count1_MtxFlg[n] = 0;
    MtxEfficiency[n] = 0.;
    MtxEfficiency_MtxFlg[n] = 0.;
    x[n] = (double)nGate-n-1;
  }


  //-hist def-----------------------------------------------------------------------------------------
  Hist1Max = 69;
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
  Hist1[35] = new TH1D("TofMtOr","TofMtOr",200,-100,100);
  Hist1[52] = new TH1D("TofMtOr Gate1","TofMtOr Gate1",200,-100,100);
  Hist1[53] = new TH1D("TofMtOr Gate2","TofMtOr Gate2",200,-100,100);
  Hist1[54] = new TH1D("TofMtOr Gate3","TofMtOr Gate3",200,-100,100);
  Hist1[55] = new TH1D("TofMtOr Gate4","TofMtOr Gate4",200,-100,100);
  Hist1[56] = new TH1D("TofMtOr Gate5","TofMtOr Gate5",200,-100,100);

  //-Sch ----------------
  Hist1[36]= new TH1D("Sch Nhits" ,"Sch Nhits" ,20,0,20);
  Hist1[37]= new TH1D("Sch Hitpat","Sch Hitpat",65,0,65);
  Hist1[38]= new TH1D("Sch Depthpat","Sch Depthpat",65,0,65);
  Hist1[39]= new TH1D("Sch Time"   ,"Sch Time"   ,200,-100,100);
  Hist1[57] = new TH1D("Sch Time Gate1","Sch Time Gate1",200,-100,100);
  Hist1[58] = new TH1D("Sch Time Gate2","Sch Time Gate2",200,-100,100);
  Hist1[59] = new TH1D("Sch Time Gate3","Sch Time Gate3",200,-100,100);
  Hist1[60] = new TH1D("Sch Time Gate4","Sch Time Gate4",200,-100,100);
  Hist1[61] = new TH1D("Sch Time Gate5","Sch Time Gate5",200,-100,100);

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
  Hist1[51] = new TH1D("SftXTime","SftXTime",200,-100,100);
  Hist1[61] = new TH1D("SftX Time Gate1","SftX Time Gate1",200,-100,100);
  Hist1[62] = new TH1D("SftX Time Gate2","SftX Time Gate2",200,-100,100);
  Hist1[63] = new TH1D("SftX Time Gate3","SftX Time Gate3",200,-100,100);
  Hist1[64] = new TH1D("SftX Time Gate4","SftX Time Gate4",200,-100,100);
  Hist1[65] = new TH1D("SftX Time Gate5","SftX Time Gate5",200,-100,100);
  
  Hist1[66] = new TH1D("Sch Time TofFlag","Sch Time TofFlag",200,-100,100);
  Hist1[67] = new TH1D("SftX Time TofFlag","SftX Time TofFlag",200,-100,100);

  Hist1[68] = new TH1D("MissMass Sigma","MissMass Sigma",100,0.8,1.4);

  //-Event Loop --------------------------------------------------------------------------------------
    Long64_t nentries = pik->GetEntries();
    Long64_t nentries_MtxFlg = 0;
//  Long64_t nentries =10000;

  for (Long64_t s=0; s<nentries;s++){
    pik->GetEntry(s);
    if(s%(nentries/10) ==0){
      std::cout << ( ((double)s)/nentries *100 ) << "%\t" << s << "/" << nentries << "\r"  << std::endl;
    }
    // Trigger Flag -----------------------
    for(int i=0; i<32; i++){
      Hist1[i]->Fill(trigflag[i]);
    }

//    Hist1[32]->Fill(tofnhits);

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
//    Hist1[36]->Fill(sch_nhits);
//    for(int i=0; i<sch_nhits; i++){
//      Hist1[37]->Fill(sch_hitpat[i]);
//    }
    for(int i=0; i<NumOfSegSCH; i++){
      Hist1[38]->Fill(sch_depth[i]);
      for(int k=0; k<16; k++){
        if(sch_time[i][k]==-999) continue;
        Hist1[39]->Fill(sch_time[i][k]);
        if(TofFlag){
          Hist1[66]->Fill(sch_time[i][k]);
        }
      }
    }

    // Sft X ------------------------------
//    Hist1[40]->Fill(sftx_unhits);
//    Hist1[41]->Fill(sftx_dnhits);
//    Hist1[42]->Fill(sftx_unhits);
//    Hist1[42]->Fill(sftx_dnhits);
//    for(int i=0; i<94; i++){
//      Hist1[43]->Fill(sftx_uhitpat[i]);
//      Hist1[45]->Fill(sftx_uhitpat[i]);
//    }
//    for(int i=0; i<49; i++){
//      Hist1[44]->Fill(sftx_dhitpat[i]+0.5);
//      Hist1[45]->Fill(sftx_dhitpat[i]+0.5);
//    }
    for(int i=0; i<NumOfSegSFT_X; i++){
      for(int j=0; j<16; j++){
        if(sftx_utime[i][j]!=-999){
          Hist1[49]->Fill(sftx_utime[i][j]);
          Hist1[51]->Fill(sftx_utime[i][j]);
          if(TofFlag){
            Hist1[67]->Fill(sftx_utime[i][j]);
          }
        }
        if(sftx_dtime[i][j]!=-999){
          Hist1[50]->Fill(sftx_dtime[i][j]);
          Hist1[51]->Fill(sftx_dtime[i][j]);
          if(TofFlag){
            Hist1[65]->Fill(sftx_dtime[i][j]);
          }
        }
      }
    }

    bool Flag1[nGate];
    bool Flag2[nGate];
    bool Flag3[nGate];
    bool Flag1_MtxFlg[nGate];
    bool Flag2_MtxFlg[nGate];
    bool Flag3_MtxFlg[nGate];
    for(int n=0; n<nGate; n++){
      Flag1[n] = false;
      Flag2[n] = false;
      Flag3[n] = false;
      Flag1_MtxFlg[n] = false;
      Flag2_MtxFlg[n] = false;
      Flag3_MtxFlg[n] = false;
    }

//    // Mtx Pattern ----------------------------
//    for(int l=0; l < Mtx_prm.size(); l++){
//      int i = 0;
//      int j = 0;
//      int min = 0;
//      int max = 0;
//      i = Mtx_prm.at(l).at(1);
//      j = Mtx_prm.at(l).at(0);
//      min = Mtx_prm.at(l).at(2);
//      max = Mtx_prm.at(l).at(3) + 1;
//        for(int m=0; m<16 ;m++){
//          if( tofmt[i][m] != -999.0 ){ 
//            Flag1[5]=true;
//            if(trigflag[28]>0) Flag1_MtxFlg[5]=true;
//          }
//        }
//        for(int m=0; m<sch_depth[j] ;m++){
//          if( sch_time[j][m]!= -999. ){
//            Flag2[5]=true;
//            if(trigflag[28]>0) Flag2_MtxFlg[5]=true;
//          }
//        }
//        for(int k = min; k < max; k++){
//          for(int m=0; m<sftx_udepth[k] ;m++){
//            if( sftx_utime[k][m] != -999. ){
//              Flag3[5]=true;
//              if(trigflag[28]>0) Flag3_MtxFlg[5]=true;
//            }
//          }
//          for(int m=0; m<sftx_ddepth[k] ;m++){
//            if( sftx_dtime[k][m] != -999. ){
//              Flag3[5]=true;
//              if(trigflag[28]>0) Flag3_MtxFlg[5]=true;
//            }
//          }
//        }
////      std::cout << i << "\t" << j <<  "\t" << min << "\t" << max << "\t" << std::endl;
//      for(int n=0; n<nGate; n++){
////          if(!Flag1[n] && tofmt[i][m]      > (double)TofMid - Gate[n] && tofmt[i][m]     < (double)TofMid + Gate[n] ) Flag1[n]=true;
////          if(!Flag2[n] && sch_time[j][m]   > (double)SchMid - Gate[n] && sch_time[j][m]  < (double)SchMid + Gate[n] ) Flag2[n]=true;
////          for(int k = min; k < max; k++){
////            if(!Flag3[n] &&  sftx_utime[k][m] > (double)SftMid - Gate[n] && sftx_utime[k][m]< (double)SftMid + Gate[n] ) Flag3[n]=true;
////            if(!Flag3[n] &&  sftx_dtime[k][m] > (double)SftMid - Gate[n] && sftx_dtime[k][m]< (double)SftMid + Gate[n] ) Flag3[n]=true;
////          }
//        for(int m=0; m<16 ;m++){
//          if( tofmt[i][m]      > (double)TofMid - Gate[n] && tofmt[i][m]     < (double)TofMid + Gate[n] ){ 
//            Hist1[52+n]->Fill(tofmt[i][m]);
//            Flag1[n]=true;
//            if(trigflag[28]>0) Flag1_MtxFlg[n]=true;
//          }
//        }
//        for(int m=0; m<sch_depth[j] ;m++){
//          if( sch_time[j][m]   > (double)SchMid - Gate[n] && sch_time[j][m]  < (double)SchMid + Gate[n] ){
//            Hist1[57+n]->Fill(sch_time[j][m]);
//            Flag2[n]=true;
//            if(trigflag[28]>0) Flag2_MtxFlg[n]=true;
//          }
//        }
//        for(int k = min; k < max; k++){
//          for(int m=0; m<sftx_udepth[k] ;m++){
//            if( sftx_utime[k][m] > (double)SftMid - Gate[n] && sftx_utime[k][m]< (double)SftMid + Gate[n] ){
//              Hist1[61+n]->Fill(sftx_utime[k][m]);
//              Flag3[n]=true;
//              if(trigflag[28]>0) Flag3_MtxFlg[n]=true;
//            }
//          }
//          for(int m=0; m<sftx_ddepth[k] ;m++){
//            if( sftx_dtime[k][m] > (double)SftMid - Gate[n] && sftx_dtime[k][m]< (double)SftMid + Gate[n] ){ 
//              Hist1[61+n]->Fill(sftx_dtime[k][m]);
//              Flag3[n]=true;
//              if(trigflag[28]>0) Flag3_MtxFlg[n]=true;
//            }
//          }
//        }
//      }
//    }

    // Mtx Pattern ----------------------------
    if(m2[0]>0.15 && m2[0]<0.35 && qKurama[0]>0 && pKurama[0]<0.9){ 
      if( vtx[0]>-20 && vtx[0]<20 && vty[0]>-20 && vty[0]<20 && vtz[0]>-200 && vtz[0]<200 ){
        Hist1[68]->Fill(MissMass[0]);
        SigmaCount+=1;
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
              Flag1[5]=true;
              if(trigflag[28]>0) Flag1_MtxFlg[5]=true;
            }
          }
          for(int m=0; m<sch_depth[j] ;m++){
            if( sch_time[j][m]!= -999. ){
              Flag2[5]=true;
              if(trigflag[28]>0) Flag2_MtxFlg[5]=true;
            }
          }
          for(int k = min; k < max; k++){
            for(int m=0; m<sftx_udepth[k] ;m++){
              if( sftx_utime[k][m] != -999. ){
                Flag3[5]=true;
                if(trigflag[28]>0) Flag3_MtxFlg[5]=true;
              }
            }
            for(int m=0; m<sftx_ddepth[k] ;m++){
              if( sftx_dtime[k][m] != -999. ){
                Flag3[5]=true;
                if(trigflag[28]>0) Flag3_MtxFlg[5]=true;
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
                Hist1[52+n]->Fill(tofmt[i][m]);
                Flag1[n]=true;
                if(trigflag[28]>0) Flag1_MtxFlg[n]=true;
              }
            }
            for(int m=0; m<sch_depth[j] ;m++){
              if( sch_time[j][m]   > (double)SchMid - Gate[n] && sch_time[j][m]  < (double)SchMid + Gate[n] ){
                Hist1[57+n]->Fill(sch_time[j][m]);
                Flag2[n]=true;
                if(trigflag[28]>0) Flag2_MtxFlg[n]=true;
              }
            }
            for(int k = min; k < max; k++){
              for(int m=0; m<sftx_udepth[k] ;m++){
                if( sftx_utime[k][m] > (double)SftMid - Gate[n] && sftx_utime[k][m]< (double)SftMid + Gate[n] ){
                  Hist1[61+n]->Fill(sftx_utime[k][m]);
                  Flag3[n]=true;
                  if(trigflag[28]>0) Flag3_MtxFlg[n]=true;
                }
              }
              for(int m=0; m<sftx_ddepth[k] ;m++){
                if( sftx_dtime[k][m] > (double)SftMid - Gate[n] && sftx_dtime[k][m]< (double)SftMid + Gate[n] ){ 
                  Hist1[61+n]->Fill(sftx_dtime[k][m]);
                  Flag3[n]=true;
                  if(trigflag[28]>0) Flag3_MtxFlg[n]=true;
                }
              }
            }
          }
        }
      }
    }

    for(int n=0; n<nGate; n++){
      if(Flag1[n]&&Flag2[n]&&Flag3[n]){
        Count1[n]+=1;
      }
      if(Flag1_MtxFlg[n]&&Flag2_MtxFlg[n]&&Flag3_MtxFlg[n]){
        Count1_MtxFlg[n]+=1;
      }
    }
    if(trigflag[28]>0) nentries_MtxFlg++;
  }

  //-Canvas def---------------------------------------------------------------------------------------
  TCanvas *c1 = new TCanvas("c1","c1",1200,900);
//-Hist Draw----------------------------------------------------------------------------------------

  c1->Print(pdf+"["); 
  c1->cd();
  for(int i=0; i<Hist1Max; i++){
    //   if(i==15 || i==16 || i==38) gPad->SetLogy(1);
    Hist1[i]->Draw();
    c1->Print(pdf);
    c1->Print(Form("%s/Mtx_Banch2_run%05d_Hist1_%03d.pdf",pdfDhire.Data(),runnum,i));
    //   if(i==15 || i==16 || i==38) gPad->SetLogy(0);
  }
//  for(int i=0; i<Hist2Max; i++){
//  Hist2[i]->Draw("colz");
//  c1->Print(pdf);
//  c1->Print(Form("%s/Mtx_Banch_run%05d_Hist2_%03d.pdf",pdfDhire.Data(),runnum,i));
//  }

  for(int n; n<nGate; n++){
//    MtxEfficiency[n]= (double)Count1[n]/nentries;
//    std::cout << "Total Event# is " << nentries << "\t" << Form("Count%d# is ",n+1) << Count1[n] << "\t" << "Efficiency is " << MtxEfficiency[n] << std::endl;
    MtxEfficiency[n]= (double)Count1[n]/Count1[nGate-1];
    std::cout << "Total Event# is " << Count1[nGate-1] << "\t" << Form("Count%d# is ",n+1) << Count1[n] << "\t" << "Efficiency is " << MtxEfficiency[n] << std::endl;
  }
  for(int n; n<nGate; n++){
//    MtxEfficiency_MtxFlg[n]= (double)Count1_MtxFlg[n]/nentries_MtxFlg;
    MtxEfficiency_MtxFlg[n]= (double)Count1_MtxFlg[n]/ Count1_MtxFlg[nGate-1];
//    std::cout << "Total Event# is " << nentries_MtxFlg << "\t" << Form("Count%d_MtxFlg# is ",nGate-1) << Count1_MtxFlg[nGate-1]  << "\t" << Form("Count%d_MtxFlg# is ",n+1) << Count1_MtxFlg[n] << "\t" << "Efficiency is " << MtxEfficiency_MtxFlg[n] << std::endl;
    std::cout << "Total Event# is " << SigmaCount << "\t" << Form("Count%d_MtxFlg# is ",nGate-1) << Count1_MtxFlg[nGate-1]  << "\t" << Form("Count%d_MtxFlg# is ",n+1) << Count1_MtxFlg[n] << "\t" << "Efficiency is " << MtxEfficiency_MtxFlg[n] << std::endl;
  }

  c1->SetGrid();
  c1->SetGridx();
  c1->SetGridy();

  TGraph *g1 = new TGraph(nGate, x, MtxEfficiency);
  TGraph *g2 = new TGraph(nGate, x, MtxEfficiency_MtxFlg);
  g1->SetMarkerStyle(8);
  g1->SetMarkerColor(2);
  g1->SetMarkerSize(2);
  g1->GetXaxis()->SetRangeUser(0,4.5);
  g1->GetYaxis()->SetRangeUser(0,1);
  g1->Draw("AP");

  c1->Print(pdf);
  c1->Print(Form("%s/Mtx_Banch2_run%05d_Graph.pdf",pdfDhire.Data(),runnum));

  g2->SetMarkerStyle(8);
  g2->SetMarkerColor(2);
  g2->SetMarkerSize(2);
  g2->GetXaxis()->SetRangeUser(0,4.5);
  g2->GetYaxis()->SetRangeUser(0,1);
  g2->Draw("AP");

  c1->Print(pdf);
  c1->Print(Form("%s/Mtx_Banch2_run%05d_Graph_MtxFlg.pdf",pdfDhire.Data(),runnum));

  c1->Print(pdf+"]"); 

}

