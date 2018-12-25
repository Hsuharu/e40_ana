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
void mtx_timing(int month, int runnum){
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
   TString pdf = Form("%s/pdf/trigger/mtx_timing_run%05d.pdf", anadir.Data(),runnum);
   TString pdfDhire = Form("%s/pdf/trigger", anadir.Data());
   TFile *f = new TFile(Form("%s/analyzer_%s/rootfile/run%05d_DstKuramaEasirocHodoscope.root", anadir.Data(),Month[month], runnum),"READ");
   TTree *k0hodo;
    f->GetObject("k0hodo",k0hodo);

//Declaration of leaves types
   Int_t           trigflag[32];
   Int_t           trigpat[32];
//   Int_t           status;
   Int_t           ntKurama;
//   Double_t        path[4];
   Double_t        pKurama[4];
   Double_t        qKurama[4];
//   Double_t        chisqrKurama[4];
//   Double_t        xtgtKurama[4];
//   Double_t        ytgtKurama[4];
//   Double_t        utgtKurama[4];
//   Double_t        vtgtKurama[4];
//   Double_t        thetaKurama[4];
//   Double_t        vpx[5];
//   Double_t        vpy[5];
//   Double_t        tTofCalc[3];
//   Int_t           nhBh1;
//   Double_t        csBh1[5];
//   Double_t        Bh1Seg[5];
//   Double_t        tBh1[5];
//   Double_t        dtBh1[5];
//   Double_t        deBh1[5];
//   Double_t        btof[5];
//   Int_t           nhBh2;
//   Double_t        csBh2[4];
//   Double_t        Bh2Seg[4];
//   Double_t        tBh2[4];
//   Double_t        dtBh2[4];
//   Double_t        t0Bh2[4];
//   Double_t        deBh2[4];
//   Int_t           nhSac;
//   Double_t        csSac[41];
//   Double_t        SacSeg[41];
//   Double_t        tSac[41];
//   Double_t        deSac[41];
//   Int_t           nhTof;
//   Double_t        csTof[17];
//   Double_t        TofSeg[17];
//   Double_t        tTof[17];
//   Double_t        dtTof[17];
//   Double_t        deTof[17];
   Int_t           tofnhits;
   Int_t           tofhitpat[24];
   Double_t        tofmt[24][16];
//   Int_t           nhBft;
//   Int_t           csBft[15];
//   Double_t        tBft[15];
//   Double_t        wBft[15];
//   Double_t        BftPos[15];
   Int_t           sch_nhits;
   Int_t           sch_hitpat[26];
   Double_t        sch_tdc[64][16];
//   Double_t        sch_trailing[64][16];
//   Double_t        sch_tot[64][16];
   Int_t           sch_depth[64];
   Int_t           nhSch;
//   Int_t           csSch[25];
//   Double_t        tSch[25];
//   Double_t        wSch[25];
//   Double_t        SchPos[25];
   Int_t           sftx_nhits;
   Int_t           sftx_unhits;
   Int_t           sftx_dnhits;
   Int_t           sftx_uhitpat[94];
   Int_t           sftx_dhitpat[49];
   Double_t        sftx_utdc[256][16];
   Double_t        sftx_dtdc[256][16];
//   Double_t        sftx_utrailing[256][16];
//   Double_t        sftx_dtrailing[256][16];
//   Double_t        sftx_utot[256][16];
//   Double_t        sftx_dtot[256][16];
   Int_t           sftx_udepth[256];
   Int_t           sftx_ddepth[256];
//   Int_t           sftx_ncl;
//   Int_t           sftx_clsize[29];
//   Double_t        sftx_ctime[29];
//   Double_t        sftx_ctot[29];
//   Double_t        sftx_clpos[29];
   Int_t           m2Combi;
//   Double_t        beta[36];
//   Double_t        stof[36];
   Double_t        m2[36];

   // Set branch status    
   k0hodo->SetBranchStatus("trigflag");
   k0hodo->SetBranchStatus("trigpat");
//   k0hodo->SetBranchStatus("status");
   k0hodo->SetBranchStatus("ntKurama");
//   k0hodo->SetBranchStatus("path");
   k0hodo->SetBranchStatus("pKurama");
   k0hodo->SetBranchStatus("qKurama");
//   k0hodo->SetBranchStatus("chisqrKurama");
//   k0hodo->SetBranchStatus("xtgtKurama");
//   k0hodo->SetBranchStatus("ytgtKurama");
//   k0hodo->SetBranchStatus("utgtKurama");
//   k0hodo->SetBranchStatus("vtgtKurama");
//   k0hodo->SetBranchStatus("thetaKurama");
//   k0hodo->SetBranchStatus("vpx");
//   k0hodo->SetBranchStatus("vpy");
//   k0hodo->SetBranchStatus("tTofCalc");
//   k0hodo->SetBranchStatus("nhBh1");
//   k0hodo->SetBranchStatus("csBh1");
//   k0hodo->SetBranchStatus("Bh1Seg");
//   k0hodo->SetBranchStatus("tBh1");
//   k0hodo->SetBranchStatus("dtBh1");
//   k0hodo->SetBranchStatus("deBh1");
//   k0hodo->SetBranchStatus("btof");
//   k0hodo->SetBranchStatus("nhBh2");
//   k0hodo->SetBranchStatus("csBh2");
//   k0hodo->SetBranchStatus("Bh2Seg");
//   k0hodo->SetBranchStatus("tBh2");
//   k0hodo->SetBranchStatus("dtBh2");
//   k0hodo->SetBranchStatus("t0Bh2");
//   k0hodo->SetBranchStatus("deBh2");
//   k0hodo->SetBranchStatus("nhSac");
//   k0hodo->SetBranchStatus("csSac");
//   k0hodo->SetBranchStatus("SacSeg");
//   k0hodo->SetBranchStatus("tSac");
//   k0hodo->SetBranchStatus("deSac");
//   k0hodo->SetBranchStatus("nhTof");
//   k0hodo->SetBranchStatus("csTof");
//   k0hodo->SetBranchStatus("TofSeg");
//   k0hodo->SetBranchStatus("tTof");
//   k0hodo->SetBranchStatus("dtTof");
//   k0hodo->SetBranchStatus("deTof");
   k0hodo->SetBranchStatus("tofnhits");
   k0hodo->SetBranchStatus("tofhitpat");
   k0hodo->SetBranchStatus("tofmt");
//   k0hodo->SetBranchStatus("nhBft");
//   k0hodo->SetBranchStatus("csBft");
//   k0hodo->SetBranchStatus("tBft");
//   k0hodo->SetBranchStatus("wBft");
//   k0hodo->SetBranchStatus("BftPos");
   k0hodo->SetBranchStatus("sch_nhits");
   k0hodo->SetBranchStatus("sch_hitpat");
   k0hodo->SetBranchStatus("sch_tdc");
//   k0hodo->SetBranchStatus("sch_trailing");
//   k0hodo->SetBranchStatus("sch_tot");
   k0hodo->SetBranchStatus("sch_depth");
//   k0hodo->SetBranchStatus("nhSch");
//   k0hodo->SetBranchStatus("csSch");
//   k0hodo->SetBranchStatus("tSch");
//   k0hodo->SetBranchStatus("wSch");
//   k0hodo->SetBranchStatus("SchPos");
   k0hodo->SetBranchStatus("sftx_nhits");
   k0hodo->SetBranchStatus("sftx_unhits");
   k0hodo->SetBranchStatus("sftx_dnhits");
   k0hodo->SetBranchStatus("sftx_uhitpat");
   k0hodo->SetBranchStatus("sftx_dhitpat");
   k0hodo->SetBranchStatus("sftx_utdc");
   k0hodo->SetBranchStatus("sftx_dtdc");
//   k0hodo->SetBranchStatus("sftx_utrailing");
//   k0hodo->SetBranchStatus("sftx_dtrailing");
//   k0hodo->SetBranchStatus("sftx_utot");
//   k0hodo->SetBranchStatus("sftx_dtot");
   k0hodo->SetBranchStatus("sftx_udepth");
   k0hodo->SetBranchStatus("sftx_ddepth");
//   k0hodo->SetBranchStatus("sftx_ncl");
//   k0hodo->SetBranchStatus("sftx_clsize");
//   k0hodo->SetBranchStatus("sftx_ctime");
//   k0hodo->SetBranchStatus("sftx_ctot");
//   k0hodo->SetBranchStatus("sftx_clpos");
   k0hodo->SetBranchStatus("m2Combi");
//   k0hodo->SetBranchStatus("beta");
//   k0hodo->SetBranchStatus("stof");
   k0hodo->SetBranchStatus("m2");

   // Set branch addresses.
   k0hodo->SetBranchAddress("trigflag",trigflag);
   k0hodo->SetBranchAddress("trigpat",trigpat);
//   k0hodo->SetBranchAddress("status",&status);
   k0hodo->SetBranchAddress("ntKurama",&ntKurama);
//   k0hodo->SetBranchAddress("path",path);
   k0hodo->SetBranchAddress("pKurama",pKurama);
   k0hodo->SetBranchAddress("qKurama",qKurama);
//   k0hodo->SetBranchAddress("chisqrKurama",chisqrKurama);
//   k0hodo->SetBranchAddress("xtgtKurama",xtgtKurama);
//   k0hodo->SetBranchAddress("ytgtKurama",ytgtKurama);
//   k0hodo->SetBranchAddress("utgtKurama",utgtKurama);
//   k0hodo->SetBranchAddress("vtgtKurama",vtgtKurama);
//   k0hodo->SetBranchAddress("thetaKurama",thetaKurama);
//   k0hodo->SetBranchAddress("vpx",vpx);
//   k0hodo->SetBranchAddress("vpy",vpy);
//   k0hodo->SetBranchAddress("tTofCalc",tTofCalc);
//   k0hodo->SetBranchAddress("nhBh1",&nhBh1);
//   k0hodo->SetBranchAddress("csBh1",csBh1);
//   k0hodo->SetBranchAddress("Bh1Seg",Bh1Seg);
//   k0hodo->SetBranchAddress("tBh1",tBh1);
//   k0hodo->SetBranchAddress("dtBh1",dtBh1);
//   k0hodo->SetBranchAddress("deBh1",deBh1);
//   k0hodo->SetBranchAddress("btof",btof);
//   k0hodo->SetBranchAddress("nhBh2",&nhBh2);
//   k0hodo->SetBranchAddress("csBh2",csBh2);
//   k0hodo->SetBranchAddress("Bh2Seg",Bh2Seg);
//   k0hodo->SetBranchAddress("tBh2",tBh2);
//   k0hodo->SetBranchAddress("dtBh2",dtBh2);
//   k0hodo->SetBranchAddress("t0Bh2",t0Bh2);
//   k0hodo->SetBranchAddress("deBh2",deBh2);
//   k0hodo->SetBranchAddress("nhSac",&nhSac);
//   k0hodo->SetBranchAddress("csSac",csSac);
//   k0hodo->SetBranchAddress("SacSeg",SacSeg);
//   k0hodo->SetBranchAddress("tSac",tSac);
//   k0hodo->SetBranchAddress("deSac",deSac);
//   k0hodo->SetBranchAddress("nhTof",&nhTof);
//   k0hodo->SetBranchAddress("csTof",csTof);
//   k0hodo->SetBranchAddress("TofSeg",TofSeg);
//   k0hodo->SetBranchAddress("tTof",tTof);
//   k0hodo->SetBranchAddress("dtTof",dtTof);
//   k0hodo->SetBranchAddress("deTof",deTof);
   k0hodo->SetBranchAddress("tofnhits",&tofnhits);
   k0hodo->SetBranchAddress("tofhitpat",tofhitpat);
   k0hodo->SetBranchAddress("tofmt",tofmt);
//   k0hodo->SetBranchAddress("nhBft",&nhBft);
//   k0hodo->SetBranchAddress("csBft",csBft);
//   k0hodo->SetBranchAddress("tBft",tBft);
//   k0hodo->SetBranchAddress("wBft",wBft);
//   k0hodo->SetBranchAddress("BftPos",BftPos);
   k0hodo->SetBranchAddress("sch_nhits",&sch_nhits);
   k0hodo->SetBranchAddress("sch_hitpat",sch_hitpat);
   k0hodo->SetBranchAddress("sch_tdc",sch_tdc);
//   k0hodo->SetBranchAddress("sch_trailing",sch_trailing);
//   k0hodo->SetBranchAddress("sch_tot",sch_tot);
   k0hodo->SetBranchAddress("sch_depth",sch_depth);
//   k0hodo->SetBranchAddress("nhSch",&nhSch);
//   k0hodo->SetBranchAddress("csSch",csSch);
//   k0hodo->SetBranchAddress("tSch",tSch);
//   k0hodo->SetBranchAddress("wSch",wSch);
//   k0hodo->SetBranchAddress("SchPos",SchPos);
   k0hodo->SetBranchAddress("sftx_nhits",&sftx_nhits);
   k0hodo->SetBranchAddress("sftx_unhits",&sftx_unhits);
   k0hodo->SetBranchAddress("sftx_dnhits",&sftx_dnhits);
   k0hodo->SetBranchAddress("sftx_uhitpat",sftx_uhitpat);
   k0hodo->SetBranchAddress("sftx_dhitpat",sftx_dhitpat);
   k0hodo->SetBranchAddress("sftx_utdc",sftx_utdc);
   k0hodo->SetBranchAddress("sftx_dtdc",sftx_dtdc);
//   k0hodo->SetBranchAddress("sftx_utrailing",sftx_utrailing);
//   k0hodo->SetBranchAddress("sftx_dtrailing",sftx_dtrailing);
//   k0hodo->SetBranchAddress("sftx_utot",sftx_utot);
//   k0hodo->SetBranchAddress("sftx_dtot",sftx_dtot);
   k0hodo->SetBranchAddress("sftx_udepth",sftx_udepth);
   k0hodo->SetBranchAddress("sftx_ddepth",sftx_ddepth);
//   k0hodo->SetBranchAddress("sftx_ncl",&sftx_ncl);
//   k0hodo->SetBranchAddress("sftx_clsize",sftx_clsize);
//   k0hodo->SetBranchAddress("sftx_ctime",sftx_ctime);
//   k0hodo->SetBranchAddress("sftx_ctot",sftx_ctot);
//   k0hodo->SetBranchAddress("sftx_clpos",sftx_clpos);
   k0hodo->SetBranchAddress("m2Combi",&m2Combi);
//   k0hodo->SetBranchAddress("beta",beta);
//   k0hodo->SetBranchAddress("stof",stof);
   k0hodo->SetBranchAddress("m2",m2);

//     This is the loop skeleton
//       To read only selected branches, Insert statements like:
// k0hodo->SetBranchStatus("*",0);  // disable all branches
// TTreePlayer->SetBranchStatus("branchname",1);  // activate branchname

//-para def-----------------------------------------------------------------------------------------
   double HULMHTDCCalib = -0.8333;
   double MaxBinValue=0.;

   int Hist1Max = 0;
   int Hist2Max = 0;

//-hist def-----------------------------------------------------------------------------------------
   Hist1Max = 50;
//   Hist2Max = 15;
   TH1D *Hist1[Hist1Max];
//   TH2D *Hist2[Hist2Max];

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

//-Sch ----------------
  Hist1[37]= new TH1D("Sch Nhits" ,"Sch Nhits" ,20,0,20);
  Hist1[38]= new TH1D("Sch Hitpat","Sch Hitpat",65,0,65);
  Hist1[39]= new TH1D("Sch Depthpat","Sch Depthpat",65,0,65);
  Hist1[40]= new TH1D("Sch Tdc"   ,"Sch Tdc"   ,100,0,1000);

//-Sft ----------------
  Hist1[41] = new TH1D("SftX U Nhits","Sft U Nhits",50,0,50);
  Hist1[42] = new TH1D("SftX D Nhits","Sft D Nhits",50,0,50);
  Hist1[43] = new TH1D("SftNhits","SftNhits",50,0,50);
  Hist1[44] = new TH1D("Sft U Hitpat","Sft U Hitpat",256*2,0,256);
  Hist1[45] = new TH1D("Sft D Hitpat","Sft D Hitpat",256*2,0,256);
  Hist1[46] = new TH1D("SftHitpat","SftHitpat",256*2,0,256);
  Hist1[47] = new TH1D("Sft U Tdc","Sft U Tdc",1000,0,1000);
  Hist1[48] = new TH1D("Sft D Tdc","Sft D Tdc",1000,0,1000);
  Hist1[49] = new TH1D("SftTdc","SftTdc",1000,0,1000);

  TH1D *SftX_U_NhitsCut  = new TH1D("SftX U Nhits Cut","Sft U Nhits Cut",50,0,50);
  TH1D *SftX_D_NhitsCut  = new TH1D("SftX D Nhits Cut","Sft D Nhits",50,0,50);
  TH1D *SftXNhitsCut     = new TH1D("SftNhits Cut","SftNhits Cut",50,0,50);
  TH1D *SftX_U_HitpatCut = new TH1D("Sft U Hitpat Cut","Sft U Hitpat Cut",256*2,0,256);
  TH1D *SftX_D_HitpatCut = new TH1D("Sft D Hitpat Cut","Sft D Hitpat Cut",256*2,0,256);
  TH1D *SftXHitpatCut = new TH1D("SftHitpat Cut","SftHitpat Cut",256*2,0,256);
  TH1D *SftX_U_TdcCut = new TH1D("Sft U Tdc Cut","Sft U Tdc Cut",1000,0,1000);
  TH1D *SftX_D_TdcCut = new TH1D("Sft D Tdc Cut","Sft D Tdc",1000,0,1000);
  TH1D *SftXTdcCut = new TH1D("SftTdc Cut","SftTdc Cut",1000,0,1000);

  TH1D *SftX_U_NhitsCut2 = new TH1D("SftX U Nhits Cut2","Sft U Nhits Cut2",50,0,50);
  TH1D *SftX_D_NhitsCut2 = new TH1D("SftX D Nhits Cut2","Sft D Nhits",50,0,50);
  TH1D *SftXNhitsCut2 = new TH1D("SftNhits Cut2","SftNhits Cut2",50,0,50);
  TH1D *SftX_U_HitpatCut2 = new TH1D("Sft U Hitpat Cut2","Sft U Hitpat Cut2",256*2,0,256);
  TH1D *SftX_D_HitpatCut2 = new TH1D("Sft D Hitpat Cut2","Sft D Hitpat Cut2",256*2,0,256);
  TH1D *SftXHitpatCut2 = new TH1D("SftHitpat Cut2","SftHitpat Cut2",256*2,0,256);
  TH1D *SftX_U_TdcCut2 = new TH1D("Sft U Tdc Cut2","Sft U Tdc Cut2",1000,0,1000);
  TH1D *SftX_D_TdcCut2 = new TH1D("Sft D Tdc Cut2","Sft D Tdc Cut2",1000,0,1000);
  TH1D *SftXTdcCut2 = new TH1D("SftTdc Cut2","SftTdc Cut2",1000,0,1000);


//    Hist1[0 ]= new TH1D("m2","m2",100,0,40);
//    Hist1[1 ]= new TH1D("pKurama","pKurama",100,0,2);
//
//    Hist2[0]= new TH2D("pKurama % m2",     "pKurama % m2 "    ,100,-0.4,1.4,100,0,2);



// TrigFlag - Matrix Detector----------
  TH1D *MatrixFlag_Tof = new TH1D("Matrix Flag - TofMtOr","Matrix Flag - TofMtOr",2000,-1000,1000);
  TH1D *MatrixFlag_Sch = new TH1D("Matrix Flag - SchOr",  "Matrix Flag - SchOr",  2000,-2000,0);
  TH1D *MatrixFlag_SftX = new TH1D("Matrix Flag - SftXOr",  "Matrix Flag - SftXOr",  2000,-2000,0);


// Sch - Tof ----------
  TH1D *SchTof = new TH1D("Sch-Tof Cut2: Sch&TOF-> nhits=1 & Maxdepth =1","Sch-Tof Cut2: Sch&TOF-> nhits=1 & Maxdepth =1",500,-800,-300);
  TH1D *SchTofCut3 = new TH1D("Sch-Tof Cut3: Sch&TOF-> nhits=1 & Maxdepth =1 & ntKurama=1","Sch-Tof Cut3: Sch&TOF-> nhits=1 & Maxdepth =1 & ntKurama=1",100,-800,-300);
  TH1D *SchTofCut3_KTime0 = new TH1D("TSch-TTof Cut3 & 0<m2&m2<1","Sch-Tof Cut3 & 0<m2&m2<1",50,-25,25);
  TH1D *SchTofCut3_KTime0_GOMI = new TH1D("TSch-TTof Cut3 & 1<m2&m2<0","Sch-Tof Cut3 & 1<m2&m2<0",200,-100,100);
  TH1D *SchTofKCut = new TH1D("Sch-Tof KCut: Cut3 & 0.1<m2&m2<0.4","Sch-Tof KCut: Cut3 & 0.1<m2&m2<0.4",800,-800,0);
  TH1D *SchTofPiCut = new TH1D("Sch-Tof PiCut: Cut3 & 0<m2&m2<0.1","Sch-Tof PiCut: Cut3 & 0<m2&m2<0.1",800,-800,0);
  TH1D *SchTofPCut = new TH1D("Sch-Tof PCut: Cut3 & 0.6<m2&m2<1","Sch-Tof PCut: Cut3 & 0.6<m2&m2<1",800,-800,0);
  TH1D *SchTofKCut_KTime0  = new TH1D("Sch-Tof KTime0 KCut: Cut3 & 0.1<m2&m2<0.4","Sch-Tof KTime0 KCut: Cut3 & 0.1<m2&m2<0.4",50,-25,25);
  TH1D *SchTofPiCut_KTime0 = new TH1D("Sch-Tof KTime0 PiCut: Cut3 & 0<m2&m2<0.1", "Sch-Tof KTime0 PiCut: Cut3 & 0<m2&m2<0.1", 50,-25,25);
  TH1D *SchTofPCut_KTime0  = new TH1D("Sch-Tof KTime0 PCut: Cut3 & 0.6<m2&m2<1",  "Sch-Tof KTime0 PCut: Cut3 & 0.6<m2&m2<1",  50,-25,25);
  TH2D *SchTofCut3_m2 = new TH2D("Sch-Tof vs m2 Cut3: Sch&TOF-> nhits=1 & Maxdepth =1 & ntKurama=1","Sch-Tof vs m2 Cut3: Sch&TOF-> nhits=1 & Maxdepth =1 & ntKurama=1",400,-800,-400,50,-0.2,1.2);
  TH2D *SchTofCut3_pKurama = new TH2D("Sch-Tof vs pKurama Cut3: Sch&TOF-> nhits=1 & Maxdepth =1 & ntKurama=1","Sch-Tof vs pKurama Cut3: Sch&TOF-> nhits=1 & Maxdepth =1 & ntKurama=1",400,-800,-400,50,0,2);
  TH2D *SchTofKCut_KTime0_pKurama  = new TH2D("Sch-Tof KTime0 vs pKurama KCut: Cut3 & 0.1<m2&m2<0.4","Sch-Tof KTime0 KCut: Cut3 & 0.1<m2&m2<0.4",50,-25,25,50,0,2);
  TH2D *SchTofPiCut_KTime0_pKurama = new TH2D("Sch-Tof KTime0 vs pKurama PiCut: Cut3 & 0<m2&m2<0.1", "Sch-Tof KTime0 PiCut: Cut3 & 0<m2&m2<0.1", 50,-25,25,50,0,2);
  TH2D *SchTofPCut_KTime0_pKurama  = new TH2D("Sch-Tof KTime0 vs pKurama PCut: Cut3 & 0.6<m2&m2<1",  "Sch-Tof KTime0 PCut: Cut3 & 0.6<m2&m2<1",  50,-25,25,50,0,2);

// Sft - Tof ----------
  TH1D *SftXTof = new TH1D("Sft-Tof Cut2: Sft&TOF-> nhits=1 & Maxdepth =1","Sft-Tof Cut2: Sft&TOF-> nhits=1 & Maxdepth =1",1000,-1000,0);
  TH1D *SftXTofCut3 = new TH1D("SftX-Tof Cut3: SftX&TOF-> nhits=1 & Maxdepth =1 & ntKurama=1","SftX-Tof Cut3: SftX&TOF-> nhits=1 & Maxdepth =1 & ntKurama=1",100,-800,-300);
  TH1D *SftXTofCut3_KTime0 = new TH1D("TSftX-TTof Cut3 & 0<m2&m2<1","SftX-Tof Cut3 & 0<m2&m2<1",50,-25,25);
  TH1D *SftXTofCut3_KTime0_GOMI = new TH1D("TSftX-TTof Cut3 & 1<m2&m2<0","SftX-Tof Cut3 & 1<m2&m2<0",200,-100,100);
  TH1D *SftXTofKCut = new TH1D("SftX-Tof KCut: Cut3 & 0.1<m2&m2<0.4","SftX-Tof KCut: Cut3 & 0.1<m2&m2<0.4",800,-800,0);
  TH1D *SftXTofPiCut = new TH1D("SftX-Tof PiCut: Cut3 & 0<m2&m2<0.1","SftX-Tof PiCut: Cut3 & 0<m2&m2<0.1",800,-800,0);
  TH1D *SftXTofPCut = new TH1D("SftX-Tof PCut: Cut3 & 0.6<m2&m2<1","SftX-Tof PCut: Cut3 & 0.6<m2&m2<1",800,-800,0);
  TH1D *SftXTofKCut_KTime0  = new TH1D("SftX-Tof KTime0 KCut: Cut3 & 0.1<m2&m2<0.4","SftX-Tof KTime0 KCut: Cut3 & 0.1<m2&m2<0.4",50,-25,25);
  TH1D *SftXTofPiCut_KTime0 = new TH1D("SftX-Tof KTime0 PiCut: Cut3 & 0<m2&m2<0.1", "SftX-Tof KTime0 PiCut: Cut3 & 0<m2&m2<0.1", 50,-25,25);
  TH1D *SftXTofPCut_KTime0  = new TH1D("SftX-Tof KTime0 PCut: Cut3 & 0.6<m2&m2<1",  "SftX-Tof KTime0 PCut: Cut3 & 0.6<m2&m2<1",  50,-25,25);
  TH2D *SftXTofCut3_m2 = new TH2D("SftX-Tof vs m2 Cut3: SftX&TOF-> nhits=1 & Maxdepth =1 & ntKurama=1","SftX-Tof vs m2 Cut3: SftX&TOF-> nhits=1 & Maxdepth =1 & ntKurama=1",400,-800,-400,50,-0.2,1.2);
  TH2D *SftXTofCut3_pKurama = new TH2D("SftX-Tof vs pKurama Cut3: SftX&TOF-> nhits=1 & Maxdepth =1 & ntKurama=1","SftX-Tof vs pKurama Cut3: SftX&TOF-> nhits=1 & Maxdepth =1 & ntKurama=1",400,-800,-400,50,0,2);
  TH2D *SftXTofKCut_KTime0_pKurama  = new TH2D("SftX-Tof KTime0 vs pKurama KCut: Cut3 & 0.1<m2&m2<0.4","SftX-Tof KTime0 KCut: Cut3 & 0.1<m2&m2<0.4",50,-25,25,50,0,2);
  TH2D *SftXTofPiCut_KTime0_pKurama = new TH2D("SftX-Tof KTime0 vs pKurama PiCut: Cut3 & 0<m2&m2<0.1", "SftX-Tof KTime0 PiCut: Cut3 & 0<m2&m2<0.1", 50,-25,25,50,0,2);
  TH2D *SftXTofPCut_KTime0_pKurama  = new TH2D("SftX-Tof KTime0 vs pKurama PCut: Cut3 & 0.6<m2&m2<1",  "SftX-Tof KTime0 PCut: Cut3 & 0.6<m2&m2<1",  50,-25,25,50,0,2);

// m2 - momentum ...------
//-Legend def --------------------------------------------------------------------------------------
//  TLegend *Leg1 = new TLegend(0.1,0.7,0.48,0.9);
  TLegend *Leg1 = new TLegend(0.78,0.775,0.98,0.935);
  TLegend *Leg2 = new TLegend(0.78,0.775,0.98,0.935);

   Long64_t nentries = k0hodo->GetEntries();
//   Long64_t nentries =10000;
//   Long64_t nbytes = 0;
//   for (Long64_t s=0; s<nentries;s++) {
//     nbytes += k0hodo->GetEntry(s);
//     if(trigpat[17]<=0) continue;
//
//     for(int i=0; i<32; i++){
//       TrigFlag[i]->Fill(trigflag[i]);
//     }
//
//     TofNhits->Fill(tofnhits);
//
//     for(int i=0; i<NumOfSegTOF; i++){
//       bool flag=false;
//       for(int j=0; j<16; j++){
//         TofMtOr->Fill(tofmt[i][j]);
//         if(tofmt[i][j]==-999){
//           if(!flag){
//             if(j!=0){
//               if(tofnhits!=1) continue;
//               TofMtOrDepthPat->Fill(j);
//               if(j==1){
//                 if(trigflag[28]>0){
//                   MatrixFlag_Tof->Fill(HULMHTDCCalib*trigflag[28]-tofmt[i][0]);
//                   for(int k=0; k<NumOfSegSCH; k++){
//                     if(sch_nhits!=1) continue;
//                     if(sch_depth[k]!=1) continue;
//                     if(sch_hitpat[0]!=k) continue;
//                     SchTdcCut2->Fill(sch_tdc[k][0]);
//                     SchTimeCut2->Fill(-sch_tdc[k][0]);
//                     SchTof->Fill(-sch_tdc[k][0]-tofmt[i][0]);
//                     if(ntKurama==1){
//                       SchTofCut3_m2->Fill(-sch_tdc[k][0]-tofmt[i][0],m2[0]);
//                       SchTofCut3_pKurama->Fill(-sch_tdc[k][0]-tofmt[i][0],pKurama[0]);
//                       SchTofCut3->Fill(-sch_tdc[k][0]-tofmt[i][0]);
//                       if(0<m2[0]&&m2[0]<0.1){
//                         SchTofPiCut->Fill(-sch_tdc[k][0]-tofmt[i][0]);
//                       }
//                       if(0.1<m2[0]&&m2[0]<0.4){
//                         SchTofKCut->Fill(-sch_tdc[k][0]-tofmt[i][0]);
//                       }
//                       if(0.6<m2[0]&&m2[0]<1){
//                         SchTofPCut->Fill(-sch_tdc[k][0]-tofmt[i][0]);
//                       }
//                     }
//                   }
//                   for(int k=0; k<NumOfSegSFT_X; k++){
//                     if(sftx_unhits==1&&sftx_dnhits==0){
//                       if(sftx_udepth[k]!=1) continue;
//                       if(sftx_uhitpat[0]!=k) continue;
//                       SftX_U_NhitsCut2->Fill(sftx_unhits);
//                       SftXNhitsCut2->Fill(sftx_unhits);
//                       SftX_U_HitpatCut2->Fill(sftx_uhitpat[0]);
//                       SftXHitpatCut2->Fill(sftx_uhitpat[0]);
//                       SftX_U_TdcCut2->Fill(sftx_utdc[k][0]);
//                       SftXTdcCut2->Fill(sftx_utdc[k][0]);
//                       SftXTof->Fill(HULMHTDCCalib*sftx_utdc[k][0]-tofmt[k][0]);
//                       if(ntKurama==1){
//                         if(0<m2[0]&&m2[0]<0.1)    SftXTofPiCut->Fill(HULMHTDCCalib*sftx_utdc[k][0]-tofmt[i][0]);
//                         if(0.1<m2[0]&&m2[0]<0.4)  SftXTofKCut->Fill(HULMHTDCCalib*sftx_utdc[k][0]-tofmt[i][0]);
//                         if(0.6<m2[0]&&m2[0]<1)    SftXTofPCut->Fill(HULMHTDCCalib*sftx_utdc[k][0]-tofmt[i][0]);
//                       }
//                     }else if(sftx_unhits==0&&sftx_dnhits==1){
//                       if(sftx_ddepth[k]!=1) continue;
//                       if(sftx_dhitpat[0]!=k) continue;
//                       SftX_D_NhitsCut2->Fill(sftx_dnhits);
//                       SftXNhitsCut2->Fill(sftx_dnhits);
//                       SftX_D_HitpatCut2->Fill(sftx_dhitpat[0]+0.5);
//                       SftXHitpatCut2->Fill(sftx_dhitpat[0]+0.5);
//                       SftX_D_TdcCut2->Fill(sftx_dtdc[k][0]);
//                       SftXTdcCut2->Fill(sftx_dtdc[k][0]);
//                       SftXTof->Fill(HULMHTDCCalib*sftx_dtdc[k][0]-tofmt[k][0]);
//                       if(ntKurama==1){
//                         if(0<m2[0]&&m2[0]<0.1)    SftXTofPiCut->Fill(HULMHTDCCalib*sftx_dtdc[k][0]-tofmt[i][0]);
//                         if(0.1<m2[0]&&m2[0]<0.4)  SftXTofKCut->Fill(HULMHTDCCalib*sftx_dtdc[k][0]-tofmt[i][0]);
//                         if(0.6<m2[0]&&m2[0]<1)    SftXTofPCut->Fill(HULMHTDCCalib*sftx_dtdc[k][0]-tofmt[i][0]);
//                       }
//                     }
//                   }
//                 }
//               }
//             }
//             flag=true;
//           }
//         }else{
//           TofMtOrCut->Fill(tofmt[i][j]);
//         }
//       }
//     }
//   }
//

   Long64_t nbytes = 0;
   for (Long64_t s=0; s<nentries;s++) {
     nbytes += k0hodo->GetEntry(s);
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
         if(tofmt[i][1]!=-999)   continue;
         Hist1[36]->Fill(tofmt[i][0]);
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
         if(sch_nhits!=1) continue;
         if(sch_depth[i]!=1) continue;
         if(sch_hitpat[0]!=i) continue;
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
         }
         if(sftx_dtdc[i][j]!=-999){
           Hist1[48]->Fill(sftx_dtdc[i][j]);
           Hist1[49]->Fill(sftx_dtdc[i][j]);
         }
         if(sftx_unhits==1&&sftx_dnhits==0){
           if(sftx_udepth[i]!=1) continue;
           if(sftx_uhitpat[0]!=i) continue;
         }else if(sftx_unhits==0&&sftx_dnhits==1){
           if(sftx_ddepth[i]!=1) continue;
           if(sftx_dhitpat[0]!=i) continue;
         }
       }
     }
   }

//     for(int k=0; k<NumOfSegSFT_X; k++){
//       if(sftx_unhits==1&&sftx_dnhits==0){
//         if(sftx_udepth[k]!=1) continue;
//         if(sftx_uhitpat[0]!=k) continue;
//         SftX_U_NhitsCut2->Fill(sftx_unhits);
//         SftXNhitsCut2->Fill(sftx_unhits);
//         SftX_U_HitpatCut2->Fill(sftx_uhitpat[0]);
//         SftXHitpatCut2->Fill(sftx_uhitpat[0]);
//         SftX_U_TdcCut2->Fill(sftx_utdc[k][0]);
//         SftXTdcCut2->Fill(sftx_utdc[k][0]);
//         SftXTof->Fill(HULMHTDCCalib*sftx_utdc[k][0]-tofmt[k][0]);
//       }else if(sftx_unhits==0&&sftx_dnhits==1){
//         if(sftx_ddepth[k]!=1) continue;
//         if(sftx_dhitpat[0]!=k) continue;
//         SftX_D_NhitsCut2->Fill(sftx_dnhits);
//         SftXNhitsCut2->Fill(sftx_dnhits);
//         SftX_D_HitpatCut2->Fill(sftx_dhitpat[0]+0.5);
//         SftXHitpatCut2->Fill(sftx_dhitpat[0]+0.5);
//         SftX_D_TdcCut2->Fill(sftx_dtdc[k][0]);
//         SftXTdcCut2->Fill(sftx_dtdc[k][0]);
//         SftXTof->Fill(HULMHTDCCalib*sftx_dtdc[k][0]-tofmt[k][0]);
//       }
//     }
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
   c1->Print(Form("%s/mtx_timing_run%05d_Hist1_%03d.pdf",pdfDhire.Data(),runnum,i));
//   if(i==15 || i==16 || i==38) gPad->SetLogy(0);
   }
//   for(int i=0; i<Hist2Max; i++){
//   Hist2[i]->Draw("colz");
//   c1->Print(pdf);
//   c1->Print(Form("%s/mtx_timing_run%05d_Hist2_%03d.pdf",pdfDhire.Data(),runnum,i));
//   }



   c1->Print(pdf+"]"); 

}

