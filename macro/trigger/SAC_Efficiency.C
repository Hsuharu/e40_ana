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

void SAC_Efficiency(int month){
//////////////////////////////////////////////////////////
//   This file has been automatically generated 
//     (Mon Dec 17 17:22:31 2018 by ROOT version6.10/08)
//   from TTree khodo/tree of DstKuramaHodoscope
//   found on file: analyzer_jun/rootfile/trigf19.root
//////////////////////////////////////////////////////////


  gStyle->SetOptStat(1111110); 
  gStyle->SetOptFit(1); 

//Reset ROOT and connect tree file
   gROOT->Reset();
   TString anadir=Form("%s/work/e40/ana",std::getenv("HOME")); 
   TString pdf = Form("%s/pdf/trigger/SAC_Efficiency_trig19.pdf", anadir.Data());
   TFile *f = new TFile(Form("%s/analyzer_%s/rootfile/trig19.root", anadir.Data(),Month[month],"READ");
   TTree *khodo;
    f->GetObject("khodo",khodo);

//Declaration of leaves types
   Int_t           trigflag[32];
   Int_t           trigpat[32];
   Int_t           status;
   Int_t           ntKurama;
   Double_t        path[4];
   Double_t        pKurama[4];
   Double_t        qKurama[4];
   Double_t        chisqrKurama[4];
   Double_t        xtgtKurama[4];
   Double_t        ytgtKurama[4];
   Double_t        utgtKurama[4];
   Double_t        vtgtKurama[4];
   Double_t        thetaKurama[4];
   Double_t        vpx[5];
   Double_t        vpy[5];
   Double_t        tTofCalc[3];
   Int_t           nhBh1;
   Double_t        csBh1[6];
   Double_t        Bh1Seg[6];
   Double_t        tBh1[6];
   Double_t        dtBh1[6];
   Double_t        deBh1[6];
   Double_t        btof[6];
   Int_t           nhBh2;
   Double_t        csBh2[4];
   Double_t        Bh2Seg[4];
   Double_t        tBh2[4];
   Double_t        dtBh2[4];
   Double_t        t0Bh2[4];
   Double_t        deBh2[4];
   Int_t           nhSac;
   Double_t        csSac[29];
   Double_t        SacSeg[29];
   Double_t        tSac[29];
   Double_t        deSac[29];
   Int_t           nhTof;
   Double_t        csTof[20];
   Double_t        TofSeg[20];
   Double_t        tTof[20];
   Double_t        dtTof[20];
   Double_t        deTof[20];
   Int_t           m2Combi;
   Double_t        beta[36];
   Double_t        stof[36];
   Double_t        m2[36];

   // Set branch addresses.
   khodo->SetBranchAddress("trigflag",trigflag);
   khodo->SetBranchAddress("trigpat",trigpat);
   khodo->SetBranchAddress("status",&status);
   khodo->SetBranchAddress("ntKurama",&ntKurama);
   khodo->SetBranchAddress("path",path);
   khodo->SetBranchAddress("pKurama",pKurama);
   khodo->SetBranchAddress("qKurama",qKurama);
   khodo->SetBranchAddress("chisqrKurama",chisqrKurama);
   khodo->SetBranchAddress("xtgtKurama",xtgtKurama);
   khodo->SetBranchAddress("ytgtKurama",ytgtKurama);
   khodo->SetBranchAddress("utgtKurama",utgtKurama);
   khodo->SetBranchAddress("vtgtKurama",vtgtKurama);
   khodo->SetBranchAddress("thetaKurama",thetaKurama);
   khodo->SetBranchAddress("vpx",vpx);
   khodo->SetBranchAddress("vpy",vpy);
   khodo->SetBranchAddress("tTofCalc",tTofCalc);
   khodo->SetBranchAddress("nhBh1",&nhBh1);
   khodo->SetBranchAddress("csBh1",csBh1);
   khodo->SetBranchAddress("Bh1Seg",Bh1Seg);
   khodo->SetBranchAddress("tBh1",tBh1);
   khodo->SetBranchAddress("dtBh1",dtBh1);
   khodo->SetBranchAddress("deBh1",deBh1);
   khodo->SetBranchAddress("btof",btof);
   khodo->SetBranchAddress("nhBh2",&nhBh2);
   khodo->SetBranchAddress("csBh2",csBh2);
   khodo->SetBranchAddress("Bh2Seg",Bh2Seg);
   khodo->SetBranchAddress("tBh2",tBh2);
   khodo->SetBranchAddress("dtBh2",dtBh2);
   khodo->SetBranchAddress("t0Bh2",t0Bh2);
   khodo->SetBranchAddress("deBh2",deBh2);
   khodo->SetBranchAddress("nhSac",&nhSac);
   khodo->SetBranchAddress("csSac",csSac);
   khodo->SetBranchAddress("SacSeg",SacSeg);
   khodo->SetBranchAddress("tSac",tSac);
   khodo->SetBranchAddress("deSac",deSac);
   khodo->SetBranchAddress("nhTof",&nhTof);
   khodo->SetBranchAddress("csTof",csTof);
   khodo->SetBranchAddress("TofSeg",TofSeg);
   khodo->SetBranchAddress("tTof",tTof);
   khodo->SetBranchAddress("dtTof",dtTof);
   khodo->SetBranchAddress("deTof",deTof);
   khodo->SetBranchAddress("m2Combi",&m2Combi);
   khodo->SetBranchAddress("beta",beta);
   khodo->SetBranchAddress("stof",stof);
   khodo->SetBranchAddress("m2",m2);


//-para def-----------------------------------------------------------------------------------------
   double HULMHTDCCalib = -0.8333;

//-hist def-----------------------------------------------------------------------------------------

//-Legend def --------------------------------------------------------------------------------------

//-Event Loop --------------------------------------------------------------------------------------
   Long64_t nentries = khodo->GetEntries();

   Long64_t nbytes = 0;
   for (Long64_t s=0; s<nentries;s++) {
      nbytes += khodo->GetEntry(i);
   }


//-Canvas def---------------------------------------------------------------------------------------

  TCanvas *c1 = new TCanvas("c1","c1",1200,900);
//-Hist Draw----------------------------------------------------------------------------------------




}
