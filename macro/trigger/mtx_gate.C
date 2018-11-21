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


void mtx_gate(int month, int runnum){
//////////////////////////////////////////////////////////
//   This file has been automatically generated 
//     (Wed Nov 21 14:24:46 2018 by ROOT version6.10/08)
//   from TTree k0hodo/tree of DstKuramaEasirocHodoscope
//   found on file: analyzer_jun/rootfile/run05126_DstKuramaEasirocHodoscope.root
//////////////////////////////////////////////////////////

  gStyle->SetOptStat(1111110); 
  gStyle->SetOptFit(1); 

//Reset ROOT and connect tree file
   gROOT->Reset();
   TString anadir=Form("%s/work/e40/ana",std::getenv("HOME")); 
   TString pdf = Form("%s/pdf/trigger/mtx_tof_%05d.pdf", anadir.Data(),runnum);
   TFile *f = new TFile(Form("%s/analyzer_%s/rootfile/run%05d_DstKuramEasirocHodoscope.root", anadir.Data(),Month[month], runnum),"READ");
   TTree *k0hodo;
    f->GetObject("k0hodo",k0hodo);

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
   Double_t        csBh1[5];
   Double_t        Bh1Seg[5];
   Double_t        tBh1[5];
   Double_t        dtBh1[5];
   Double_t        deBh1[5];
   Double_t        btof[5];
   Int_t           nhBh2;
   Double_t        csBh2[4];
   Double_t        Bh2Seg[4];
   Double_t        tBh2[4];
   Double_t        dtBh2[4];
   Double_t        t0Bh2[4];
   Double_t        deBh2[4];
   Int_t           nhSac;
   Double_t        csSac[41];
   Double_t        SacSeg[41];
   Double_t        tSac[41];
   Double_t        deSac[41];
   Int_t           nhTof;
   Double_t        csTof[17];
   Double_t        TofSeg[17];
   Double_t        tTof[17];
   Double_t        dtTof[17];
   Double_t        deTof[17];
   Int_t           nhBft;
   Int_t           csBft[15];
   Double_t        tBft[15];
   Double_t        wBft[15];
   Double_t        BftPos[15];
   Int_t           nhSch;
   Int_t           csSch[25];
   Double_t        tSch[25];
   Double_t        wSch[25];
   Double_t        SchPos[25];
   Int_t           m2Combi;
   Double_t        beta[36];
   Double_t        stof[36];
   Double_t        m2[36];

   // Set branch addresses.
   k0hodo->SetBranchAddress("trigflag",trigflag);
   k0hodo->SetBranchAddress("trigpat",trigpat);
   k0hodo->SetBranchAddress("status",&status);
   k0hodo->SetBranchAddress("ntKurama",&ntKurama);
   k0hodo->SetBranchAddress("path",path);
   k0hodo->SetBranchAddress("pKurama",pKurama);
   k0hodo->SetBranchAddress("qKurama",qKurama);
   k0hodo->SetBranchAddress("chisqrKurama",chisqrKurama);
   k0hodo->SetBranchAddress("xtgtKurama",xtgtKurama);
   k0hodo->SetBranchAddress("ytgtKurama",ytgtKurama);
   k0hodo->SetBranchAddress("utgtKurama",utgtKurama);
   k0hodo->SetBranchAddress("vtgtKurama",vtgtKurama);
   k0hodo->SetBranchAddress("thetaKurama",thetaKurama);
   k0hodo->SetBranchAddress("vpx",vpx);
   k0hodo->SetBranchAddress("vpy",vpy);
   k0hodo->SetBranchAddress("tTofCalc",tTofCalc);
   k0hodo->SetBranchAddress("nhBh1",&nhBh1);
   k0hodo->SetBranchAddress("csBh1",csBh1);
   k0hodo->SetBranchAddress("Bh1Seg",Bh1Seg);
   k0hodo->SetBranchAddress("tBh1",tBh1);
   k0hodo->SetBranchAddress("dtBh1",dtBh1);
   k0hodo->SetBranchAddress("deBh1",deBh1);
   k0hodo->SetBranchAddress("btof",btof);
   k0hodo->SetBranchAddress("nhBh2",&nhBh2);
   k0hodo->SetBranchAddress("csBh2",csBh2);
   k0hodo->SetBranchAddress("Bh2Seg",Bh2Seg);
   k0hodo->SetBranchAddress("tBh2",tBh2);
   k0hodo->SetBranchAddress("dtBh2",dtBh2);
   k0hodo->SetBranchAddress("t0Bh2",t0Bh2);
   k0hodo->SetBranchAddress("deBh2",deBh2);
   k0hodo->SetBranchAddress("nhSac",&nhSac);
   k0hodo->SetBranchAddress("csSac",csSac);
   k0hodo->SetBranchAddress("SacSeg",SacSeg);
   k0hodo->SetBranchAddress("tSac",tSac);
   k0hodo->SetBranchAddress("deSac",deSac);
   k0hodo->SetBranchAddress("nhTof",&nhTof);
   k0hodo->SetBranchAddress("csTof",csTof);
   k0hodo->SetBranchAddress("TofSeg",TofSeg);
   k0hodo->SetBranchAddress("tTof",tTof);
   k0hodo->SetBranchAddress("dtTof",dtTof);
   k0hodo->SetBranchAddress("deTof",deTof);
   k0hodo->SetBranchAddress("nhBft",&nhBft);
   k0hodo->SetBranchAddress("csBft",csBft);
   k0hodo->SetBranchAddress("tBft",tBft);
   k0hodo->SetBranchAddress("wBft",wBft);
   k0hodo->SetBranchAddress("BftPos",BftPos);
   k0hodo->SetBranchAddress("nhSch",&nhSch);
   k0hodo->SetBranchAddress("csSch",csSch);
   k0hodo->SetBranchAddress("tSch",tSch);
   k0hodo->SetBranchAddress("wSch",wSch);
   k0hodo->SetBranchAddress("SchPos",SchPos);
   k0hodo->SetBranchAddress("m2Combi",&m2Combi);
   k0hodo->SetBranchAddress("beta",beta);
   k0hodo->SetBranchAddress("stof",stof);
   k0hodo->SetBranchAddress("m2",m2);

//     This is the loop skeleton
//       To read only selected branches, Insert statements like:
// k0hodo->SetBranchStatus("*",0);  // disable all branches
// TTreePlayer->SetBranchStatus("branchname",1);  // activate branchname

   Long64_t nentries = k0hodo->GetEntries();

   Long64_t nbytes = 0;
//   for (Long64_t i=0; i<nentries;i++) {
//      nbytes += k0hodo->GetEntry(i);
//   }
}
