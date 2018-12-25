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

void SAC_Efficiency(int month,int runnum){
//////////////////////////////////////////////////////////
//   This file has been automatically generated 
//     (Fri Dec 21 01:38:49 2018 by ROOT version6.10/08)
//   from TTree kurama/tree of KuramaTracking
//   found on file: rootfile/run05078_KuramaTracking.root
//////////////////////////////////////////////////////////

  gStyle->SetOptStat(1111110); 
  gStyle->SetOptFit(1); 

//Reset ROOT and connect tree file
   gROOT->Reset();
   gROOT->Reset();
   TString anadir=Form("%s/work/e40/ana",std::getenv("HOME")); 
   TString pdf = Form("%s/pdf/trigger/SAC_Efficiency_run%05d.pdf", anadir.Data(),runnum);
   TString pdfDhire = Form("%s/pdf/trigger", anadir.Data());
//   TFile *f = new TFile(Form("%s/analyzer_%s/rootfile/trigf19_tofht.root", anadir.Data(),Month[month]),"READ");
   TFile *f = new TFile(Form("%s/analyzer_%s/rootfile/run%05d_KuramaTracking.root", anadir.Data(),Month[month],runnum),"READ");
   TTree *kurama;
    f->GetObject("kurama",kurama);

// Declaration of leaves types-----------------------------------------------------------------------
   Int_t           evnum;
   Int_t           trigpat[32];
   Int_t           trigflag[32];
   Int_t           nhBh2;
   Double_t        Bh2Seg[8];
   Double_t        tBh2[8];
   Double_t        deBh2[8];
   Double_t        time0;
   Int_t           nhBh1;
   Double_t        Bh1Seg[11];
   Double_t        tBh1[11];
   Double_t        deBh1[11];
   Double_t        btof;
   Int_t           nhSac;
   Double_t        SacSeg[4];
   Double_t        tSac[4];
   Double_t        deSac[4];
   Int_t           nhTof;
   Double_t        TofSeg[12];
   Double_t        tTof[12];
   Double_t        dtTof[12];
   Double_t        deTof[12];
   Double_t        wposSdcIn[9];
   Double_t        wposSdcOut[16];
   Int_t           ntSdcIn;
   Int_t           much;
   Int_t           nlSdcIn;
   Int_t           nhSdcIn[8];
   Double_t        chisqrSdcIn[8];
   Double_t        x0SdcIn[8];
   Double_t        y0SdcIn[8];
   Double_t        u0SdcIn[8];
   Double_t        v0SdcIn[8];
   Int_t           ntSdcOut;
   Int_t           nlSdcOut;
   Int_t           nhSdcOut[3];
   Double_t        chisqrSdcOut[3];
   Double_t        x0SdcOut[3];
   Double_t        y0SdcOut[3];
   Double_t        u0SdcOut[3];
   Double_t        v0SdcOut[3];
   Int_t           ntKurama;
   Int_t           nlKurama;
   Int_t           nhKurama[4];
   Double_t        chisqrKurama[4];
   Double_t        stof[4];
   Double_t        path[4];
   Double_t        pKurama[4];
   Double_t        qKurama[4];
   Double_t        m2[4];
   Double_t        xtgtKurama[4];
   Double_t        ytgtKurama[4];
   Double_t        utgtKurama[4];
   Double_t        vtgtKurama[4];
   Double_t        thetaKurama[4];
   Double_t        phiKurama[4];
   Double_t        resP[4];
   Double_t        xsacKurama[4];
   Double_t        ysacKurama[4];
   Double_t        xtofKurama[4];
   Double_t        ytofKurama[4];
   Double_t        utofKurama[4];
   Double_t        vtofKurama[4];
   Double_t        tofsegKurama[4];
   Double_t        vpx[5];
   Double_t        vpy[5];
//   vector<double>  ResL1;
//   vector<double>  ResL2;
//   vector<double>  ResL3;
//   vector<double>  ResL4;
//   vector<double>  ResL5;
//   vector<double>  ResL6;
//   vector<double>  ResL7;
//   vector<double>  ResL8;
//   vector<double>  ResL9;
//   vector<double>  ResL31;
//   vector<double>  ResL32;
//   vector<double>  ResL33;
//   vector<double>  ResL34;
//   vector<double>  ResL35;
//   vector<double>  ResL36;
//   vector<double>  ResL37;
//   vector<double>  ResL38;
//   vector<double>  ResL39;
//   vector<double>  ResL40;
//   vector<double>  ResL41;
//   vector<double>  ResL42;
//   vector<double>  ResL43;
//   vector<double>  ResL44;
//   vector<double>  ResL45;
//   vector<double>  ResL46;
//   vector<double>  ResG1;
//   vector<double>  ResG2;
//   vector<double>  ResG3;
//   vector<double>  ResG4;
//   vector<double>  ResG5;
//   vector<double>  ResG6;
//   vector<double>  ResG7;
//   vector<double>  ResG8;
//   vector<double>  ResG9;
//   vector<double>  ResG31;
//   vector<double>  ResG32;
//   vector<double>  ResG33;
//   vector<double>  ResG34;
//   vector<double>  ResG35;
//   vector<double>  ResG36;
//   vector<double>  ResG37;
//   vector<double>  ResG38;
//   vector<double>  ResG39;
//   vector<double>  ResG40;
//   vector<double>  ResG41;
//   vector<double>  ResG43;
//   vector<double>  ResG44;
//   vector<double>  ResG45;
//   vector<double>  ResG46;
//   vector<double>  ResG42;
   Double_t        tTofCalc[3];
   Double_t        utTofSeg[24];
   Double_t        dtTofSeg[24];
   Double_t        udeTofSeg[24];
   Double_t        ddeTofSeg[24];
   Double_t        tofua[24];
   Double_t        tofda[24];

// Select Branch ------------------------------------------------------------------------------------
   kurama->SetBranchStatus("*", 0);
   kurama->SetBranchStatus("evnum");
   kurama->SetBranchStatus("trigpat");
   kurama->SetBranchStatus("trigflag");
//   kurama->SetBranchStatus("nhBh2",&nhBh2);
//   kurama->SetBranchStatus("Bh2Seg",Bh2Seg);
//   kurama->SetBranchStatus("tBh2",tBh2);
//   kurama->SetBranchStatus("deBh2",deBh2);
//   kurama->SetBranchStatus("time0",&time0);
//   kurama->SetBranchStatus("nhBh1",&nhBh1);
//   kurama->SetBranchStatus("Bh1Seg",Bh1Seg);
//   kurama->SetBranchStatus("tBh1",tBh1);
//   kurama->SetBranchStatus("deBh1",deBh1);
//   kurama->SetBranchStatus("btof",&btof);
   kurama->SetBranchStatus("nhSac");
   kurama->SetBranchStatus("SacSeg");
   kurama->SetBranchStatus("tSac");
   kurama->SetBranchStatus("deSac");
//   kurama->SetBranchStatus("nhTof",&nhTof);
//   kurama->SetBranchStatus("TofSeg",TofSeg);
//   kurama->SetBranchStatus("tTof",tTof);
//   kurama->SetBranchStatus("dtTof",dtTof);
//   kurama->SetBranchStatus("deTof",deTof);
//   kurama->SetBranchStatus("wposSdcIn",wposSdcIn);
//   kurama->SetBranchStatus("wposSdcOut",wposSdcOut);
//   kurama->SetBranchStatus("ntSdcIn",&ntSdcIn);
//   kurama->SetBranchStatus("much",&much);
//   kurama->SetBranchStatus("nlSdcIn",&nlSdcIn);
//   kurama->SetBranchStatus("nhSdcIn",nhSdcIn);
//   kurama->SetBranchStatus("chisqrSdcIn",chisqrSdcIn);
//   kurama->SetBranchStatus("x0SdcIn",x0SdcIn);
//   kurama->SetBranchStatus("y0SdcIn",y0SdcIn);
//   kurama->SetBranchStatus("u0SdcIn",u0SdcIn);
//   kurama->SetBranchStatus("v0SdcIn",v0SdcIn);
//   kurama->SetBranchStatus("ntSdcOut",&ntSdcOut);
//   kurama->SetBranchStatus("nlSdcOut",&nlSdcOut);
//   kurama->SetBranchStatus("nhSdcOut",nhSdcOut);
//   kurama->SetBranchStatus("chisqrSdcOut",chisqrSdcOut);
//   kurama->SetBranchStatus("x0SdcOut",x0SdcOut);
//   kurama->SetBranchStatus("y0SdcOut",y0SdcOut);
//   kurama->SetBranchStatus("u0SdcOut",u0SdcOut);
//   kurama->SetBranchStatus("v0SdcOut",v0SdcOut);
   kurama->SetBranchStatus("ntKurama");
//   kurama->SetBranchStatus("nlKurama",&nlKurama);
//   kurama->SetBranchStatus("nhKurama",nhKurama);
   kurama->SetBranchStatus("chisqrKurama");
//   kurama->SetBranchStatus("path",path);
   kurama->SetBranchStatus("pKurama");
   kurama->SetBranchStatus("stof");
   kurama->SetBranchStatus("qKurama");
   kurama->SetBranchStatus("m2");
//   kurama->SetBranchStatus("xtgtKurama",xtgtKurama);
//   kurama->SetBranchStatus("ytgtKurama",ytgtKurama);
//   kurama->SetBranchStatus("utgtKurama",utgtKurama);
//   kurama->SetBranchStatus("vtgtKurama",vtgtKurama);
   kurama->SetBranchStatus("thetaKurama");
//   kurama->SetBranchStatus("phiKurama",phiKurama);
//   kurama->SetBranchStatus("resP",resP);
   kurama->SetBranchStatus("xsacKurama");
   kurama->SetBranchStatus("ysacKurama");
//   kurama->SetBranchStatus("xtofKurama",xtofKurama);
//   kurama->SetBranchStatus("ytofKurama",ytofKurama);
//   kurama->SetBranchStatus("utofKurama",utofKurama);
//   kurama->SetBranchStatus("vtofKurama",vtofKurama);
//   kurama->SetBranchStatus("tofsegKurama",tofsegKurama);
   kurama->SetBranchStatus("vpx");
   kurama->SetBranchStatus("vpy");
//   kurama->SetBranchStatus("ResL1",&ResL1);
//   kurama->SetBranchStatus("ResL2",&ResL2);
//   kurama->SetBranchStatus("ResL3",&ResL3);
//   kurama->SetBranchStatus("ResL4",&ResL4);
//   kurama->SetBranchStatus("ResL5",&ResL5);
//   kurama->SetBranchStatus("ResL6",&ResL6);
//   kurama->SetBranchStatus("ResL7",&ResL7);
//   kurama->SetBranchStatus("ResL8",&ResL8);
//   kurama->SetBranchStatus("ResL9",&ResL9);
//   kurama->SetBranchStatus("ResL31",&ResL31);
//   kurama->SetBranchStatus("ResL32",&ResL32);
//   kurama->SetBranchStatus("ResL33",&ResL33);
//   kurama->SetBranchStatus("ResL34",&ResL34);
//   kurama->SetBranchStatus("ResL35",&ResL35);
//   kurama->SetBranchStatus("ResL36",&ResL36);
//   kurama->SetBranchStatus("ResL37",&ResL37);
//   kurama->SetBranchStatus("ResL38",&ResL38);
//   kurama->SetBranchStatus("ResL39",&ResL39);
//   kurama->SetBranchStatus("ResL40",&ResL40);
//   kurama->SetBranchStatus("ResL41",&ResL41);
//   kurama->SetBranchStatus("ResL43",&ResL43);
//   kurama->SetBranchStatus("ResL44",&ResL44);
//   kurama->SetBranchStatus("ResL45",&ResL45);
//   kurama->SetBranchStatus("ResL46",&ResL46);
//   kurama->SetBranchStatus("ResL42",&ResL42);
//   kurama->SetBranchStatus("ResG1",&ResG1);
//   kurama->SetBranchStatus("ResG2",&ResG2);
//   kurama->SetBranchStatus("ResG3",&ResG3);
//   kurama->SetBranchStatus("ResG4",&ResG4);
//   kurama->SetBranchStatus("ResG5",&ResG5);
//   kurama->SetBranchStatus("ResG6",&ResG6);
//   kurama->SetBranchStatus("ResG7",&ResG7);
//   kurama->SetBranchStatus("ResG8",&ResG8);
//   kurama->SetBranchStatus("ResG9",&ResG9);
//   kurama->SetBranchStatus("ResG31",&ResG31);
//   kurama->SetBranchStatus("ResG32",&ResG32);
//   kurama->SetBranchStatus("ResG33",&ResG33);
//   kurama->SetBranchStatus("ResG34",&ResG34);
//   kurama->SetBranchStatus("ResG35",&ResG35);
//   kurama->SetBranchStatus("ResG36",&ResG36);
//   kurama->SetBranchStatus("ResG37",&ResG37);
//   kurama->SetBranchStatus("ResG38",&ResG38);
//   kurama->SetBranchStatus("ResG39",&ResG39);
//   kurama->SetBranchStatus("ResG40",&ResG40);
//   kurama->SetBranchStatus("ResG43",&ResG43);
//   kurama->SetBranchStatus("ResG44",&ResG44);
//   kurama->SetBranchStatus("ResG45",&ResG45);
//   kurama->SetBranchStatus("ResG46",&ResG46);
//   kurama->SetBranchStatus("ResG41",&ResG41);
//   kurama->SetBranchStatus("ResG42",&ResG42);
//   kurama->SetBranchStatus("tTofCalc",tTofCalc);
//   kurama->SetBranchStatus("utTofSeg",utTofSeg);
//   kurama->SetBranchStatus("dtTofSeg",dtTofSeg);
//   kurama->SetBranchStatus("udeTofSeg",udeTofSeg);
//   kurama->SetBranchStatus("ddeTofSeg",ddeTofSeg);
//   kurama->SetBranchStatus("tofua",tofua);
//   kurama->SetBranchStatus("tofda",tofda);


// Set branch addresses -----------------------------------------------------------------------------
   kurama->SetBranchAddress("evnum",&evnum);
   kurama->SetBranchAddress("trigpat",trigpat);
   kurama->SetBranchAddress("trigflag",trigflag);
//   kurama->SetBranchAddress("nhBh2",&nhBh2);
//   kurama->SetBranchAddress("Bh2Seg",Bh2Seg);
//   kurama->SetBranchAddress("tBh2",tBh2);
//   kurama->SetBranchAddress("deBh2",deBh2);
//   kurama->SetBranchAddress("time0",&time0);
//   kurama->SetBranchAddress("nhBh1",&nhBh1);
//   kurama->SetBranchAddress("Bh1Seg",Bh1Seg);
//   kurama->SetBranchAddress("tBh1",tBh1);
//   kurama->SetBranchAddress("deBh1",deBh1);
//   kurama->SetBranchAddress("btof",&btof);
   kurama->SetBranchAddress("nhSac",&nhSac);
   kurama->SetBranchAddress("SacSeg",SacSeg);
   kurama->SetBranchAddress("tSac",tSac);
   kurama->SetBranchAddress("deSac",deSac);
//   kurama->SetBranchAddress("nhTof",&nhTof);
//   kurama->SetBranchAddress("TofSeg",TofSeg);
//   kurama->SetBranchAddress("tTof",tTof);
//   kurama->SetBranchAddress("dtTof",dtTof);
//   kurama->SetBranchAddress("deTof",deTof);
//   kurama->SetBranchAddress("wposSdcIn",wposSdcIn);
//   kurama->SetBranchAddress("wposSdcOut",wposSdcOut);
//   kurama->SetBranchAddress("ntSdcIn",&ntSdcIn);
//   kurama->SetBranchAddress("much",&much);
//   kurama->SetBranchAddress("nlSdcIn",&nlSdcIn);
//   kurama->SetBranchAddress("nhSdcIn",nhSdcIn);
//   kurama->SetBranchAddress("chisqrSdcIn",chisqrSdcIn);
//   kurama->SetBranchAddress("x0SdcIn",x0SdcIn);
//   kurama->SetBranchAddress("y0SdcIn",y0SdcIn);
//   kurama->SetBranchAddress("u0SdcIn",u0SdcIn);
//   kurama->SetBranchAddress("v0SdcIn",v0SdcIn);
//   kurama->SetBranchAddress("ntSdcOut",&ntSdcOut);
//   kurama->SetBranchAddress("nlSdcOut",&nlSdcOut);
//   kurama->SetBranchAddress("nhSdcOut",nhSdcOut);
//   kurama->SetBranchAddress("chisqrSdcOut",chisqrSdcOut);
//   kurama->SetBranchAddress("x0SdcOut",x0SdcOut);
//   kurama->SetBranchAddress("y0SdcOut",y0SdcOut);
//   kurama->SetBranchAddress("u0SdcOut",u0SdcOut);
//   kurama->SetBranchAddress("v0SdcOut",v0SdcOut);
   kurama->SetBranchAddress("ntKurama",&ntKurama);
//   kurama->SetBranchAddress("nlKurama",&nlKurama);
//   kurama->SetBranchAddress("nhKurama",nhKurama);
   kurama->SetBranchAddress("chisqrKurama",chisqrKurama);
   kurama->SetBranchAddress("stof",stof);
//   kurama->SetBranchAddress("path",path);
   kurama->SetBranchAddress("pKurama",pKurama);
   kurama->SetBranchAddress("qKurama",qKurama);
   kurama->SetBranchAddress("m2",m2);
//   kurama->SetBranchAddress("xtgtKurama",xtgtKurama);
//   kurama->SetBranchAddress("ytgtKurama",ytgtKurama);
//   kurama->SetBranchAddress("utgtKurama",utgtKurama);
//   kurama->SetBranchAddress("vtgtKurama",vtgtKurama);
   kurama->SetBranchAddress("thetaKurama",thetaKurama);
//   kurama->SetBranchAddress("phiKurama",phiKurama);
//   kurama->SetBranchAddress("resP",resP);
   kurama->SetBranchAddress("xsacKurama",xsacKurama);
   kurama->SetBranchAddress("ysacKurama",ysacKurama);
//   kurama->SetBranchAddress("xtofKurama",xtofKurama);
//   kurama->SetBranchAddress("ytofKurama",ytofKurama);
//   kurama->SetBranchAddress("utofKurama",utofKurama);
//   kurama->SetBranchAddress("vtofKurama",vtofKurama);
//   kurama->SetBranchAddress("tofsegKurama",tofsegKurama);
   kurama->SetBranchAddress("vpx",vpx);
   kurama->SetBranchAddress("vpy",vpy);
//   kurama->SetBranchAddress("ResL1",&ResL1);
//   kurama->SetBranchAddress("ResL2",&ResL2);
//   kurama->SetBranchAddress("ResL3",&ResL3);
//   kurama->SetBranchAddress("ResL4",&ResL4);
//   kurama->SetBranchAddress("ResL5",&ResL5);
//   kurama->SetBranchAddress("ResL6",&ResL6);
//   kurama->SetBranchAddress("ResL7",&ResL7);
//   kurama->SetBranchAddress("ResL8",&ResL8);
//   kurama->SetBranchAddress("ResL9",&ResL9);
//   kurama->SetBranchAddress("ResL31",&ResL31);
//   kurama->SetBranchAddress("ResL32",&ResL32);
//   kurama->SetBranchAddress("ResL33",&ResL33);
//   kurama->SetBranchAddress("ResL34",&ResL34);
//   kurama->SetBranchAddress("ResL35",&ResL35);
//   kurama->SetBranchAddress("ResL36",&ResL36);
//   kurama->SetBranchAddress("ResL37",&ResL37);
//   kurama->SetBranchAddress("ResL38",&ResL38);
//   kurama->SetBranchAddress("ResL39",&ResL39);
//   kurama->SetBranchAddress("ResL40",&ResL40);
//   kurama->SetBranchAddress("ResL41",&ResL41);
//   kurama->SetBranchAddress("ResL43",&ResL43);
//   kurama->SetBranchAddress("ResL44",&ResL44);
//   kurama->SetBranchAddress("ResL45",&ResL45);
//   kurama->SetBranchAddress("ResL46",&ResL46);
//   kurama->SetBranchAddress("ResL42",&ResL42);
//   kurama->SetBranchAddress("ResG1",&ResG1);
//   kurama->SetBranchAddress("ResG2",&ResG2);
//   kurama->SetBranchAddress("ResG3",&ResG3);
//   kurama->SetBranchAddress("ResG4",&ResG4);
//   kurama->SetBranchAddress("ResG5",&ResG5);
//   kurama->SetBranchAddress("ResG6",&ResG6);
//   kurama->SetBranchAddress("ResG7",&ResG7);
//   kurama->SetBranchAddress("ResG8",&ResG8);
//   kurama->SetBranchAddress("ResG9",&ResG9);
//   kurama->SetBranchAddress("ResG31",&ResG31);
//   kurama->SetBranchAddress("ResG32",&ResG32);
//   kurama->SetBranchAddress("ResG33",&ResG33);
//   kurama->SetBranchAddress("ResG34",&ResG34);
//   kurama->SetBranchAddress("ResG35",&ResG35);
//   kurama->SetBranchAddress("ResG36",&ResG36);
//   kurama->SetBranchAddress("ResG37",&ResG37);
//   kurama->SetBranchAddress("ResG38",&ResG38);
//   kurama->SetBranchAddress("ResG39",&ResG39);
//   kurama->SetBranchAddress("ResG40",&ResG40);
//   kurama->SetBranchAddress("ResG43",&ResG43);
//   kurama->SetBranchAddress("ResG44",&ResG44);
//   kurama->SetBranchAddress("ResG45",&ResG45);
//   kurama->SetBranchAddress("ResG46",&ResG46);
//   kurama->SetBranchAddress("ResG41",&ResG41);
//   kurama->SetBranchAddress("ResG42",&ResG42);
//   kurama->SetBranchAddress("tTofCalc",tTofCalc);
//   kurama->SetBranchAddress("utTofSeg",utTofSeg);
//   kurama->SetBranchAddress("dtTofSeg",dtTofSeg);
//   kurama->SetBranchAddress("udeTofSeg",udeTofSeg);
//   kurama->SetBranchAddress("ddeTofSeg",ddeTofSeg);
//   kurama->SetBranchAddress("tofua",tofua);
//   kurama->SetBranchAddress("tofda",tofda);

//     This is the loop skeleton
//       To read only selected branches, Insert statements like:
// kurama->SetBranchStatus("*",0);  // disable all branches
// TTreePlayer->SetBranchStatus("branchname",1);  // activate branchname

//
//-para def-----------------------------------------------------------------------------------------
   double HULMHTDCCalib = -0.8333;

   int Hist1Max = 0;
   int Hist2Max = 0;

   int chisqr = 0;
   chisqr = 100;

   int hit=0;
   int total=0;
   double eff=0.;

//-hist def-----------------------------------------------------------------------------------------
   Hist1Max = 30;
   Hist2Max = 11;
   TH1D *Hist1[Hist1Max];
   TH2D *Hist2[Hist2Max];

//    Hist1[0]= new TH1D(Form("Hist1 %s",TriggerFlag[i]),Form("Hist1 %s",TriggerFlag[i]),1000,0,2100);
    Hist1[0 ]= new TH1D("ThetaKurama","ThetaKurama",100,0,40);
    Hist1[1 ]= new TH1D("pKurama","pKurama",100,0,2);
    Hist1[2 ]= new TH1D("pKurama Cut1","pKurama Cut1",100,0,2);
    Hist1[3 ]= new TH1D("m2","m2",100,-0.4,1.4);
    Hist1[4 ]= new TH1D("m2 Cut1","m2 Cut1",100,-0.4,1.4);
    Hist1[5 ]= new TH1D("chisqrKurama","chisqrKurama",100,0,200);
    Hist1[6 ]= new TH1D("qKurama","qKurama",6,-3,3);
    Hist1[7 ]= new TH1D("xsacKurama     ","xsacKurama     ",100,-400,400);
    Hist1[8 ]= new TH1D("xsacKurama Cut1","xsacKurama Cut1",100,-400,400);
    Hist1[9 ]= new TH1D("ysacKurama     ","ysacKurama     ",100,-400,400);
    Hist1[10]= new TH1D("ysacKurama Cut1","ysacKurama Cut1",100,-400,400);
    Hist1[11]= new TH1D("xsacKurama Cut2","xsacKurama Cut2",100,-400,400);
    Hist1[12]= new TH1D("ysacKurama Cut2","ysacKurama Cut2",100,-400,400);
//    for(int i=0; i<4; i++){
//      Hist1[13+i]= new TH1D(Form("tSac Room%d",i),Form("tSac Room%d",i),1000,-2000,2000);
//      Hist1[18+i]= new TH1D(Form("tSac Cut2 Room%d",i),Form("tSac Cut2 Room%d",i),1000,-2000,2000);
//    } // tSac by Room
    Hist1[13]= new TH1D("tSac Or  ","tSac Or  ",1000,-1500,500);
    Hist1[14]= new TH1D("tSac Or Cut2","tSac Or Cut2",1000,-1500,500);
    Hist1[15]= new TH1D(Form("Trigger Flag %s  ",TriggerFlag[19]),Form("Trigger Flag %s  ",TriggerFlag[19]),2000,0,2000);
    Hist1[16]= new TH1D(Form("Trigger Flag %s Cut2",TriggerFlag[19]),Form("Trigger Flag %s Cut2",TriggerFlag[19]),2000,0,2000);
//    Hist1[15]= new TH1D(Form("Trigger Flag %s  ",TriggerFlag[17]),Form("Trigger Flag %s  ",TriggerFlag[17]),2000,0,2000);
//    Hist1[16]= new TH1D(Form("Trigger Flag %s Cut2",TriggerFlag[17]),Form("Trigger Flag %s Cut2",TriggerFlag[17]),2000,0,2000);
    Hist1[17]= new TH1D("xsacKurama Cut3","xsacKurama Cut3",100,-400,400);
    Hist1[18]= new TH1D("ysacKurama Cut3","ysacKurama Cut3",100,-400,400);
    Hist1[19]= new TH1D("pKurama Cut3","pKurama Cut3",100,0,2);
    Hist1[20]= new TH1D("m2 Cut3","m2 Cut3",100,-0.4,1.4);
    Hist1[21]= new TH1D("tSac Or Cut3","tSac Or Cut3",1000,-1500,500);
    Hist1[22]= new TH1D("xsacKurama Cut4","xsacKurama Cut4",100,-400,400);
    Hist1[23]= new TH1D("ysacKurama Cut4","ysacKurama Cut4",100,-400,400);
    Hist1[24]= new TH1D("pKurama Cut4","pKurama Cut4",100,0,2);
    Hist1[25]= new TH1D("m2 Cut4","m2 Cut4",100,-0.4,1.4);
    Hist1[26]= new TH1D("xsacKurama Cut Ver 4","xsacKurama Cut Ver 4",100,-400,400);
    Hist1[27]= new TH1D("ysacKurama Cut Ver 4","ysacKurama Cut Ver 4",100,-400,400);
    Hist1[28]= new TH1D("pKurama Cut Ver 4","pKurama Cut Ver 4",100,0,2);
    Hist1[29]= new TH1D("m2 Cut Ver 4","m2 Cut Ver 4",100,-0.4,1.4);


    Hist2[0]= new TH2D("pKurama % ThetaKurama","pKurama % ThetaKurama",100,0,40,100,0,2);
    Hist2[1]= new TH2D("pKurama % m2",     "pKurama % m2 "    ,100,-0.4,1.4,100,0,2);
    Hist2[2]= new TH2D("pKurama % m2 Cut1","pKurama % m2 Cut1",100,-0.4,1.4,100,0,2);
    Hist2[3]= new TH2D("ysacKurama % xsacKurama     ","ysacKurama % xsacKurama     ",100,-400,400,100,-400,400);
    Hist2[4]= new TH2D("ysacKurama % xsacKurama Cut1","ysacKurama % xsacKurama Cut1",100,-400,400,100,-400,400);
    Hist2[5]= new TH2D("pKurama % m2 Cut3","pKurama % m2 Cut3",100,-0.4,1.4,100,0,2);
    Hist2[6]= new TH2D("ysacKurama % xsacKurama Cut3","ysacKurama % xsacKurama Cut3",100,-400,400,100,-400,400);
    Hist2[7]= new TH2D("pKurama % m2 Cut4","pKurama % m2 Cut4",100,-0.4,1.4,100,0,2);
    Hist2[8]= new TH2D("ysacKurama % xsacKurama Cut4","ysacKurama % xsacKurama Cut4",100,-400,400,100,-400,400);
    Hist2[9]= new TH2D("pKurama % m2 Cut Ver 4","pKurama % m2 Cut Ver 4",100,-0.4,1.4,100,0,2);
    Hist2[10]= new TH2D("ysacKurama % xsacKurama Cut Ver 4","ysacKurama % xsacKurama Cut Ver 4",100,-400,400,100,-400,400);

//-Legend def --------------------------------------------------------------------------------------

//-Event Loop --------------------------------------------------------------------------------------
   Long64_t nentries = kurama->GetEntries();
//   Long64_t nentries = 10000;

//-Event Loop First --------
   Long64_t nbytes = 0;
   for (Long64_t s=0; s<nentries;s++) {
     nbytes += kurama->GetEntry(s);
     Hist1[15]->Fill(trigflag[19]);
//     Hist1[15]->Fill(trigflag[17]);
     for(int i=0; i<ntKurama; i++){
       Hist1[1]->Fill(pKurama[i]);
       Hist1[3]->Fill(m2[i]);
       Hist2[1]->Fill(m2[i],pKurama[i]);
       Hist1[5]->Fill(chisqrKurama[i]);
       Hist1[6]->Fill(qKurama[i]);
       Hist1[7]->Fill(xsacKurama[i]);
       Hist1[9]->Fill(ysacKurama[i]);
       Hist2[3]->Fill(xsacKurama[i],ysacKurama[i]);

       if(chisqrKurama[i]<chisqr&&qKurama[i]>0&&ntKurama==1){
         Hist1[2]->Fill(pKurama[i]);
         Hist1[4]->Fill(m2[i]);
         Hist2[2]->Fill(m2[i],pKurama[i]);
         Hist2[4]->Fill(xsacKurama[i],ysacKurama[i]);
         Hist1[8]->Fill(xsacKurama[i]);
         Hist1[10]->Fill(ysacKurama[i]);
         Hist1[16]->Fill(trigflag[19]);
//         Hist1[16]->Fill(trigflag[17]);
       } // Cut1
       if(chisqrKurama[i]<chisqr&&qKurama[i]>0){
         Hist1[11]->Fill(xsacKurama[i]);
         Hist1[12]->Fill(ysacKurama[i]);
       } // Cut2
       if(m2[i]<0)continue;
       if(m2[i]>0.1)continue;
       Hist1[0]->Fill(thetaKurama[i]);
       Hist2[0]->Fill(thetaKurama[i],pKurama[i]);
     } 
    for(int i=0; i<nhSac; i++){
      int SacSegNum= SacSeg[nhSac];
       Hist1[13]->Fill(tSac[nhSac]);
       if(chisqrKurama[i]<chisqr&&qKurama[i]>0&&ntKurama==1){
       Hist1[14]->Fill(tSac[nhSac]);
       }//Cut2
    } // tSac by Room
   } 

// Peak & Gate Make -----
   TF1 *FitFunc1 = new TF1("FitFunc1","gaus");
   FitFunc1->SetParameters(1000,-400,5);
   double MaximumBintSac=0.;
   double tSacGateMin   =0.;
   double tSacGateMax   =0.;
   MaximumBintSac=Hist1[13]->GetXaxis()->GetBinCenter(Hist1[13]->GetMaximumBin());
   Hist1[13]->Fit("FitFunc1","","",MaximumBintSac-4,MaximumBintSac+4);
   Hist1[13]->SetAxisRange(MaximumBintSac-50,MaximumBintSac+80,"X");
   tSacGateMin=FitFunc1->GetParameter(1) - 15 ;//FitFunc1->GetParameter(2);
   tSacGateMax=FitFunc1->GetParameter(1) + 15 ;//FitFunc1->GetParameter(2);
   std::cout << "SAC Time Gate Min \t" << tSacGateMin << std::endl;
   std::cout << "SAC Time Gate Max \t" << tSacGateMax << std::endl;

   double tSacGateMin_Cut2   =0.;
   double tSacGateMax_Cut2   =0.;
   MaximumBintSac=Hist1[14]->GetXaxis()->GetBinCenter(Hist1[14]->GetMaximumBin());
   Hist1[14]->Fit("FitFunc1","","",MaximumBintSac-4,MaximumBintSac+4);
   Hist1[14]->SetAxisRange(MaximumBintSac-50,MaximumBintSac+80,"X");
   tSacGateMin_Cut2=FitFunc1->GetParameter(1) - 15; //FitFunc1->GetParameter(2);
   tSacGateMax_Cut2=FitFunc1->GetParameter(1) + 15; //FitFunc1->GetParameter(2);

   double MaximumBin=0.;
   double trigflag19GateMin   =0.;
   double trigflag19GateMax   =0.;
   MaximumBin=Hist1[15]->GetXaxis()->GetBinCenter(Hist1[15]->GetMaximumBin());
   Hist1[15]->Fit("FitFunc1","","",MaximumBin-4,MaximumBin+4);
   Hist1[15]->SetAxisRange(MaximumBin-50,MaximumBin+80,"X");
   trigflag19GateMin=FitFunc1->GetParameter(1) - 15; //FitFunc1->GetParameter(2);
   trigflag19GateMax=FitFunc1->GetParameter(1) + 15; //FitFunc1->GetParameter(2);
//   double trigflag17GateMin   =0.;
//   double trigflag17GateMax   =0.;
//   MaximumBin=Hist1[15]->GetXaxis()->GetBinCenter(Hist1[15]->GetMaximumBin());
//   Hist1[15]->Fit("FitFunc1","","",MaximumBin-4,MaximumBin+4);
//   Hist1[15]->SetAxisRange(MaximumBin-50,MaximumBin+80,"X");
//   trigflag17GateMin=FitFunc1->GetParameter(1) - 15; //FitFunc1->GetParameter(2);
//   trigflag17GateMax=FitFunc1->GetParameter(1) + 15; //FitFunc1->GetParameter(2);

   MaximumBin=Hist1[16]->GetXaxis()->GetBinCenter(Hist1[16]->GetMaximumBin());
   Hist1[16]->Fit("FitFunc1","","",MaximumBin-4,MaximumBin+4);
   Hist1[16]->SetAxisRange(MaximumBin-50,MaximumBin+80,"X");

   double xsacKuramaGateMin = -200;
   double xsacKuramaGateMax =  240;
   double ysacKuramaGateMin = -180;
   double ysacKuramaGateMax =  180;

//-Event Loop Second --------
   nbytes = 0;
   for (Long64_t s=0; s<nentries;s++) {
     nbytes += kurama->GetEntry(s);
//     for(int i=0; i<ntKurama; i++){
//       Hist1[1]->Fill(pKurama[i]);
//       Hist1[3]->Fill(m2[i]);
//       Hist2[1]->Fill(m2[i],pKurama[i]);
//       Hist1[5]->Fill(chisqrKurama[i]);
//       Hist1[6]->Fill(qKurama[i]);
//       Hist1[7]->Fill(xsacKurama[i]);
//       Hist1[9]->Fill(ysacKurama[i]);
//       Hist2[3]->Fill(xsacKurama[i],ysacKurama[i]);
//
//       if(chisqrKurama[i]<chisqr&&qKurama[i]>0&&ntKurama==1){
//         Hist1[2]->Fill(pKurama[i]);
//         Hist1[4]->Fill(m2[i]);
//         Hist2[2]->Fill(m2[i],pKurama[i]);
//         Hist2[4]->Fill(xsacKurama[i],ysacKurama[i]);
//         Hist1[8]->Fill(xsacKurama[i]);
//         Hist1[10]->Fill(ysacKurama[i]);
//         Hist1[16]->Fill(trigflag[19]);
//       } // Cut1
//       if(chisqrKurama[i]<chisqr&&qKurama[i]>0){
//         Hist1[11]->Fill(xsacKurama[i]);
//         Hist1[12]->Fill(ysacKurama[i]);
//       } // Cut2
//       if(m2[i]<0)continue;
//       if(m2[i]>0.1)continue;
//       Hist1[0]->Fill(thetaKurama[i]);
//       Hist2[0]->Fill(thetaKurama[i],pKurama[i]);
//     } 
//    for(int i=0; i<nhSac; i++){
//      int SacSegNum= SacSeg[nhSac];
//       Hist1[13]->Fill(tSac[nhSac]);
     if(ntKurama!=1) continue;
     if(chisqrKurama[0]>chisqr) continue;
     if(
//       chisqrKurama[ntKurama]<chisqr &&
         qKurama[0]>0&&
//         ntKurama==1 &&
//         nhSac==1//&&
         xsacKurama[0]>xsacKuramaGateMin&&
         xsacKurama[0]<xsacKuramaGateMax&&
         ysacKurama[0]>ysacKuramaGateMin&&
         ysacKurama[0]<ysacKuramaGateMax&&
//         tSac[nhSac]>tSacGateMin&&
//         tSac[nhSac]<tSacGateMax&&
         m2[0]>0&&
         m2[0]<0.25&&
         pKurama[0]>0.2&&
         pKurama[0]<1.2//&&
//         trigflag[19]>trigflag19GateMin&&
//         trigflag[19]<trigflag19GateMax
       ){
       int n_hit=0;
       for(int i=0; i<nhSac; i++){
         if( tSac[i]>tSacGateMin && tSac[i]<tSacGateMax){
           Hist1[21]->Fill(tSac[i]);
           n_hit +=1;
         }
       }
       if(n_hit!=0){
         hit += 1;
         Hist1[22]->Fill(xsacKurama[0]);
         Hist1[23]->Fill(ysacKurama[0]);
         Hist1[24]->Fill(pKurama[0]);
         Hist1[25]->Fill(m2[0]);
         Hist2[7]->Fill(m2[0],pKurama[0]);
         Hist2[8]->Fill(xsacKurama[0],ysacKurama[0]);
       }else{  // Cut4
         Hist1[26]->Fill(xsacKurama[0]);
         Hist1[27]->Fill(ysacKurama[0]);
         Hist1[28]->Fill(pKurama[0]);
         Hist1[29]->Fill(m2[0]);
         Hist2[9]->Fill(m2[0],pKurama[0]);
         Hist2[10]->Fill(xsacKurama[0],ysacKurama[0]);
       } // Cut_Ver_4
       total += 1;

       Hist1[17]->Fill(xsacKurama[0]);
       Hist1[18]->Fill(ysacKurama[0]);
       Hist1[19]->Fill(pKurama[0]);
       Hist1[20]->Fill(m2[0]);
       Hist2[5]->Fill(m2[0],pKurama[0]);
       Hist2[6]->Fill(xsacKurama[0],ysacKurama[0]);
     } // Cut3
//    } // tSac by Room
   } 

   eff = (double)hit/total;

// Peak & Gate Make -----
   MaximumBintSac=0.;
   MaximumBintSac=Hist1[21]->GetXaxis()->GetBinCenter(Hist1[21]->GetMaximumBin());
   Hist1[21]->Fit("FitFunc1","","",MaximumBintSac-4,MaximumBintSac+4);
   Hist1[21]->SetAxisRange(MaximumBintSac-50,MaximumBintSac+80,"X");


//-Canvas def---------------------------------------------------------------------------------------

  TCanvas *c1 = new TCanvas("c1","c1",1200,900);
   c1->Print(pdf+"["); 
//-Hist Draw----------------------------------------------------------------------------------------
   c1->cd();
   for(int i=0; i<Hist1Max; i++){
   if(i==15 || i==16) gPad->SetLogy(1);
   Hist1[i]->Draw();
   c1->Print(pdf);
   c1->Print(Form("%s/SAC_Efficiency_run%05d_Hist1_%03d.pdf",pdfDhire.Data(),runnum,i));
   if(i==15 || i==16) gPad->SetLogy(0);
   }
   for(int i=0; i<Hist2Max; i++){
   Hist2[i]->Draw("colz");
   c1->Print(pdf);
   c1->Print(Form("%s/SAC_Efficiency_run%05d_Hist2_%03d.pdf",pdfDhire.Data(),runnum,i));
   }

std::cout << "hit \t" << hit << std::endl; 
std::cout << "total \t" << total << std::endl; 
std::cout << "eff \t" << eff << std::endl; 


   c1->Print(pdf+"]"); 


}
