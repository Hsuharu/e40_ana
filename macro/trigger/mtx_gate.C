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
void mtx_gate(int month, int runnum){
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
   TString pdf = Form("%s/pdf/trigger/mtx_gate_run%05d.pdf", anadir.Data(),runnum);
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

//-hist def-----------------------------------------------------------------------------------------
//-Trigger Flag -------

  TH1D *TrigPatAll= new TH1D("TrigPatAll","TrigPatAll",32,0,32);

  TH1D *TrigFlag[32];
  for(int i=0;i<32;i++){
    TrigFlag[i]= new TH1D(Form("TrigFlag %s",TriggerFlag[i]),Form("TrigFlag %s",TriggerFlag[i]),1000,0,2100);
  }
  
//-Tof ----------------
  TH1D *TofNhits = new TH1D("TofNhits","TofNhits",20,0,20);
  TH1D *TrigFlag28NhitsDepthCut= new TH1D("MtxFlag TdcCut & MtxFlg & Nhits=1 & MaxDepth#1 Cut","MtxFlag TdcCut & MtxFlg & Nhits=1 & MaxDepth#1 Cut",1800,-1800,0);
  TH1D *TofMtOrMtxFlgNhitsCut = new TH1D("TofMtOr TdcCut & MtxFlg & Nhits=1 Cut","TofMtOr TdcCut & MtxFlg & Nhits=1 Cut",100,-10,90);
  TH1D *TrigFlag28NhitsCut= new TH1D("MtxFlag TdcCut & MtxFlg & Nhits=1 Cut","MtxFlag TdcCut & MtxFlg & Nhits=1 Cut",1800,-1800,0);

  TH1D *TofMt[NumOfSegTOF];
//  TH1D *TofMtCut[NumOfSegTOF];
//  TH1D *TofMtMtxFlgNhitsDepthCut[NumOfSegTOF];
  for(int i=0;i<NumOfSegTOF;i++){
    TofMt[i]= new TH1D(Form("TofMt%d",i+1),Form("TofMt%d",i+1),100,-10,90);
//    TofMtCut[i]= new TH1D(Form("TofMtCut%d",i+1),Form("TofMtCut%d",i+1),100,-10,90);
//    TofMtMtxFlgNhitsDepthCut[i] = new TH1D(Form("TofMt%d TdcCut & MtxFlg & Nhits=1 & MaxDepth#1 Cut",i+1),Form("TofMt%d TdcCut & MtxFlg & Nhits=1 & MaxDepth#1 Cut",i+1),100,-10,90);
  }

  TH1D *TofHitPatNhitsCut = new TH1D("TofHitPat Cut:Nhits","TofHitPat Cut:Nhits",NumOfSegTOF,0,NumOfSegTOF);
  TH1D *TofMtOr = new TH1D("TofMtOr","TofMtOr",100,-10,90);
  TH1D *TofMtOrCut = new TH1D("TofMtOrCut","TofMtOrCut",100,-10,90);
  TH1D *TofMtOrDepthPat = new TH1D("TofMtOrDepthPat","TofMtOrDepthPat",10,0,10);
  TH1D *TofMtOrAllDepthPat = new TH1D("TofMtOrAllDepthPat","TofMtOrAllDepthPat",10,0,10);
  TH1D *TofMtOrMtxFlgCut = new TH1D("TofMtOr TdcCut & MtxFlgCut","TofMtOr TdcCut & MtxFlgCut",100,-10,90);
  TH1D *TofMtOrMtxFlgNhitsDepthCut = new TH1D("TofMtOr TdcCut & MtxFlg & Nhits=1 & MaxDepth#1 Cut","TofMtOr TdcCut & MtxFlg & Nhits=1 & MaxDepth#1 Cut",100,-10,90);

//-Sch ----------------
  TH1D *SchNhits = new TH1D("SchNhits","SchNhits",20,0,20);
  TH1D *SchHitpat = new TH1D("SchHitpat","SchHitpat",65,0,65);
  TH1D *SchNhitsCut = new TH1D("SchNhitsCut:nhits=1 & Maxdepth =1","SchNhitsCut:nhits=1 & Maxdepth =1",20,0,20);
  TH1D *SchTdc = new TH1D("SchTdc","SchTdc",100,0,1000);
  TH1D *SchTdcCut = new TH1D("SchTdcCut:nhits=1 & Maxdepth =1","SchTdcCut:nhits=1 & Maxdepth =1",100,0,1000);
  TH1D *SchTdcCut2 = new TH1D("SchTdcCut2: Sch&TOF-> nhits=1 & Maxdepth =1","SchTdcCut2: Sch&TOF-> nhits=1 & Maxdepth =1",100,0,1000);
  TH1D *SchTimeCut2 = new TH1D("SchTimeCut2: Sch&TOF-> nhits=1 & Maxdepth =1","SchTimeCut2: Sch&TOF-> nhits=1 & Maxdepth =1",100,-500,-300);

// TrigFlag - Matrix Detector----------
  TH1D *MatrixFlag_Tof = new TH1D("Matrix Flag - TofMtOr","Matrix Flag - TofMtOr",2000,-1000,1000);
  TH1D *MatrixFlag_Sch = new TH1D("Matrix Flag - SchOr",  "Matrix Flag - SchOr",  2000,-1000,1000);
  TH1D *MatrixFlag_Sft = new TH1D("Matrix Flag - SftOr",  "Matrix Flag - SftOr",  2000,-1000,1000);


// Sch - Tof ----------
  TH1D *SchTof = new TH1D("Sch-Tof Cut2: Sch&TOF-> nhits=1 & Maxdepth =1","Sch-Tof Cut2: Sch&TOF-> nhits=1 & Maxdepth =1",100,-500,-300);
  TH1D *SchTofCut3 = new TH1D("Sch-Tof Cut3: Sch&TOF-> nhits=1 & Maxdepth =1 & ntKurama=1","Sch-Tof Cut3: Sch&TOF-> nhits=1 & Maxdepth =1 & ntKurama=1",100,-500,-300);
  TH1D *SchTofCut3_KTime0 = new TH1D("TSch-TTof Cut3 & 0<m2&m2<1","Sch-Tof Cut3 & 0<m2&m2<1",100,-500,-300);
  TH1D *SchTofCut3_KTime0_GOMI = new TH1D("TSch-TTof Cut3 & 1<m2&m2<0","Sch-Tof Cut3 & 1<m2&m2<0",100,-500,-300);
  TH1D *SchTofKCut = new TH1D("Sch-Tof KCut: Cut3 & 0.1<m2&m2<0.4","Sch-Tof KCut: Cut3 & 0.1<m2&m2<0.4",50,-420,-370);
  TH1D *SchTofPiCut = new TH1D("Sch-Tof PiCut: Cut3 & 0<m2&m2<0.1","Sch-Tof PiCut: Cut3 & 0<m2&m2<0.1",50,-420,-370);
  TH1D *SchTofPCut = new TH1D("Sch-Tof PCut: Cut3 & 0.6<m2&m2<1","Sch-Tof PCut: Cut3 & 0.6<m2&m2<1",50,-420,-370);
  TH1D *SchTofKCut_KTime0  = new TH1D("Sch-Tof KTime0 KCut: Cut3 & 0.1<m2&m2<0.4","Sch-Tof KTime0 KCut: Cut3 & 0.1<m2&m2<0.4",50,-25,25);
  TH1D *SchTofPiCut_KTime0 = new TH1D("Sch-Tof KTime0 PiCut: Cut3 & 0<m2&m2<0.1", "Sch-Tof KTime0 PiCut: Cut3 & 0<m2&m2<0.1", 50,-25,25);
  TH1D *SchTofPCut_KTime0  = new TH1D("Sch-Tof KTime0 PCut: Cut3 & 0.6<m2&m2<1",  "Sch-Tof KTime0 PCut: Cut3 & 0.6<m2&m2<1",  50,-25,25);
  TH2D *SchTofCut3_m2 = new TH2D("Sch-Tof vs m2 Cut3: Sch&TOF-> nhits=1 & Maxdepth =1 & ntKurama=1","Sch-Tof vs m2 Cut3: Sch&TOF-> nhits=1 & Maxdepth =1 & ntKurama=1",50,-420,-370,50,-0.2,1.2);
  TH2D *SchTofCut3_pKurama = new TH2D("Sch-Tof vs pKurama Cut3: Sch&TOF-> nhits=1 & Maxdepth =1 & ntKurama=1","Sch-Tof vs pKurama Cut3: Sch&TOF-> nhits=1 & Maxdepth =1 & ntKurama=1",50,-420,-370,50,0,1.2);

//-Legend def --------------------------------------------------------------------------------------
//  TLegend *Leg1 = new TLegend(0.1,0.7,0.48,0.9);
  TLegend *Leg1 = new TLegend(0.78,0.775,0.98,0.935);

   Long64_t nentries = k0hodo->GetEntries();

   Long64_t nbytes = 0;
   for (Long64_t s=0; s<nentries;s++) {
     nbytes += k0hodo->GetEntry(s);
     if(trigpat[17]<=0) continue;
     for(int i=0; i<32; i++){
       TrigPatAll->Fill(trigpat[i]);
     }

     for(int i=0; i<32; i++){
       TrigFlag[i]->Fill(trigflag[i]);
     }

     TofNhits->Fill(tofnhits);

     for(int i=0; i<NumOfSegTOF; i++){
       bool flag=false;
       for(int j=0; j<16; j++){
         TofMt[i]->Fill(tofmt[i][j]);
         TofMtOr->Fill(tofmt[i][j]);
         if(tofmt[i][j]==-999){
           if(!flag){
             if(j!=0){
               if(tofnhits!=1) continue;
               TofMtOrDepthPat->Fill(j);
               if(j==1){
                 if(trigflag[28]>0){
                   TofHitPatNhitsCut->Fill(i);
//                   TofMtMtxFlgNhitsDepthCut[i]->Fill(tofmt[i][0]);
                   TofMtOrMtxFlgNhitsDepthCut->Fill(tofmt[i][0]);
                   TrigFlag28NhitsDepthCut->Fill(HULMHTDCCalib*trigflag[28]);
                   MatrixFlag_Tof->Fill(HULMHTDCCalib*trigflag[28]-tofmt[i][0]);
                   for(int k=0; k<NumOfSegSCH; k++){
                     if(sch_nhits!=1) continue;
                     if(sch_depth[k]!=1) continue;
                     if(sch_hitpat[0]!=k) continue;
                     SchTdcCut2->Fill(sch_tdc[k][0]);
                     SchTimeCut2->Fill(HULMHTDCCalib*sch_tdc[k][0]);
                     SchTof->Fill(HULMHTDCCalib*sch_tdc[k][0]-tofmt[i][0]);
                     if(ntKurama==1){
                       SchTofCut3_m2->Fill(HULMHTDCCalib*sch_tdc[k][0]-tofmt[i][0],m2[ntKurama]);
                       SchTofCut3_pKurama->Fill(HULMHTDCCalib*sch_tdc[k][0]-tofmt[i][0],pKurama[ntKurama]);
                       SchTofCut3->Fill(HULMHTDCCalib*sch_tdc[k][0]-tofmt[i][0]);
                       if(0<m2[ntKurama]&&m2[ntKurama]<0.1){
                         SchTofPiCut->Fill(HULMHTDCCalib*sch_tdc[k][0]-tofmt[i][0]);
                       }
                       if(0.1<m2[ntKurama]&&m2[ntKurama]<0.4){
                         SchTofKCut->Fill(HULMHTDCCalib*sch_tdc[k][0]-tofmt[i][0]);
                       }
                       if(0.4<m2[ntKurama]&&m2[ntKurama]<1){
                         SchTofPCut->Fill(HULMHTDCCalib*sch_tdc[k][0]-tofmt[i][0]);
                       }
                     }
                   }
                 }
               }
             }
             flag=true;
           }
         }else{
//           TofMtCut[i]->Fill(tofmt[i][j]);
           TofMtOrCut->Fill(tofmt[i][j]);
           if(trigflag[28]>0){
             TofMtOrMtxFlgCut->Fill(tofmt[i][j]);
               if(tofnhits!=1) continue;
               TofMtOrAllDepthPat->Fill(j+1);
               TofMtOrMtxFlgNhitsCut->Fill(tofmt[i][j]);
               TrigFlag28NhitsCut->Fill(HULMHTDCCalib*trigflag[28]);
           }
         }
       }
     }
     //Sch ----
     for(int i=0; i<26; i++){
       SchHitpat->Fill(sch_hitpat[i]);
     }
     SchNhits->Fill(sch_nhits);
     for(int i=0; i<NumOfSegSCH; i++){
       for(int j=0; j<16; j++){
         SchTdc->Fill(sch_tdc[i][j]);
       }
       if(sch_nhits!=1) continue;
       if(sch_depth[i]!=1) continue;
       if(sch_hitpat[0]!=i) continue;
       MatrixFlag_Sch->Fill(HULMHTDCCalib*trigflag[28]-sch_tdc[i][0]);
       SchNhitsCut->Fill(sch_nhits);
       SchTdcCut->Fill(sch_tdc[i][0]);
     }

//     //Sft ----
//     for(int i=0; i<26; i++){
//       SchHitpat->Fill(sch_hitpat[i]);
//     }
//     SchNhits->Fill(sch_nhits);
//     for(int i=0; i<NumOfSegSCH; i++){
//       for(int j=0; j<16; j++){
//         SchTdc->Fill(sch_tdc[i][j]);
//       }
//       if(sch_nhits!=1) continue;
//       if(sch_depth[i]!=1) continue;
//       if(sch_hitpat[0]!=i) continue;
//       SchNhitsCut->Fill(sch_nhits);
//       SchTdcCut->Fill(sch_tdc[i][0]);
//     }
   }

//-Canvas def---------------------------------------------------------------------------------------
  TCanvas *c1 = new TCanvas("c1","c1",1200,900);
  TCanvas *c2 = new TCanvas("c2","c2",1200,900);
  TCanvas *c3 = new TCanvas("c3","c3",1200,900);
  TCanvas *c4 = new TCanvas("c4","c4",1200,900);
  TCanvas *c5 = new TCanvas("c5","c5",1200,900);
  TCanvas *c6 = new TCanvas("c6","c6",1200,900);

//  c1->Divide();
  c2->Divide(6,3);
  c3->Divide(4,4);
  c4->Divide(4,3);
  c5->Divide(2,2);
  c6->Divide(2,2);

   c1->Print(pdf+"["); 
//-Hist Draw----------------------------------------------------------------------------------------
   c1->cd();
   TrigPatAll->Draw();
   c1->Print(pdf);

//   for(int i=0; i<4; i++){
//     for(int j=0; j<4; j++){
//       c5->cd(j+1);
//       TrigFlag[i*4+j]->Draw();
//     }
//     c5->Print(pdf);
//   }

   c1->cd();
   TrigFlag[8]->Draw();
   c1->Print(pdf);

   TrigFlag[9]->Draw();
   c1->Print(pdf);

   TrigFlag[28]->Draw();
   c1->Print(pdf);

   TrigFlag[28]->SetAxisRange(900,1050,"X");
   TrigFlag[28]->Draw();
   c1->Print(pdf);

   TofNhits->Draw();
   c1->Print(pdf);

   for(int j=0; j<2; j++){
     for(int i=0; i<12; i++){
       c4->cd(i+1);
       TofMt[j*12+i]->Draw();
     }
    c4->Print(pdf);
   }

   c1->cd();
   TofMtOr->Draw();
   c1->Print(pdf);

   c1->cd();
   TofMtOrDepthPat->Draw();
   c1->Print(pdf);

   TofMtOrAllDepthPat->Draw();
   c1->Print(pdf);

   TofHitPatNhitsCut->Draw();
   c1->Print(pdf);

   c1->cd();
   TofMtOrCut->Draw();
   c1->Print(pdf);

   TofMtOrMtxFlgCut->Draw();
   c1->Print(pdf);

   c6->cd(1);
   TrigFlag28NhitsCut->SetAxisRange(-840,-740,"X");
   TrigFlag28NhitsCut->Draw();
   c6->cd(2);
   TofMtOrMtxFlgNhitsCut->Draw();
   c6->Print(pdf);

   c6->cd(1);
   TrigFlag28NhitsDepthCut->SetAxisRange(-840,-740,"X");
   TrigFlag28NhitsDepthCut->Draw();
   c6->cd(2);
   TofMtOrMtxFlgNhitsDepthCut->Draw();
   c6->cd(3);
   c6->Print(pdf);

//Sch Draw ----
   c1->cd();
   SchNhits->Draw();
   c1->Print(pdf);
   SchHitpat->Draw();
   c1->Print(pdf);
   SchNhitsCut->Draw();
   c1->Print(pdf);
   SchTdc->Draw();
   c1->Print(pdf);
   SchTdcCut->Draw();
   c1->Print(pdf);
   SchTdcCut2->Draw();
   c1->Print(pdf);
   SchTimeCut2->Draw();
   c1->Print(pdf);
   
//Sch-Tof Draw ----
   SchTof->Draw();
   c1->Print(pdf);

   SchTofCut3->Draw();
   c1->Print(pdf);

   SchTofPiCut->Draw();
   c1->Print(pdf);


//Matrix-Detevtor Draw ----

   double MaxBinValue=0.;
   MaxBinValue=MatrixFlag_Tof->GetXaxis()->GetBinCenter(MatrixFlag_Tof->GetMaximumBin());
   MatrixFlag_Tof->Draw();
   c1->Print(pdf);
   MatrixFlag_Tof->SetAxisRange(MaxBinValue-25,MaxBinValue+25,"X");
   MatrixFlag_Tof->Draw();
   c1->Print(pdf);

   MaxBinValue=MatrixFlag_Sch->GetXaxis()->GetBinCenter(MatrixFlag_Sch->GetMaximumBin());
   MatrixFlag_Sch->Draw();
   c1->Print(pdf);
   MatrixFlag_Sch->SetAxisRange(MaxBinValue-25,MaxBinValue+25,"X");
   MatrixFlag_Sch->Draw();
   c1->Print(pdf);

// Time Calib by KaonTime to 0----------------------------------------------------------------------
   TF1 *FitFunc1 = new TF1("FitFunc1","gaus");
   FitFunc1->SetParameters(1000,-400,5);
   double MaximumBin=0.;
   double SchTofKTime0=0.;
   MaximumBin=SchTofKCut->GetXaxis()->GetBinCenter(SchTofKCut->GetMaximumBin());
   std::cout << MaximumBin << std::endl;
   SchTofKCut->Fit("FitFunc1","","",MaximumBin-5,MaximumBin+5);
   SchTofKCut->Draw();
   SchTofKTime0=FitFunc1->GetParameter(1);

   c1->Print(pdf);
   SchTofPCut->Draw();
   c1->Print(pdf);


// KTime0 Calib
   for (Long64_t s=0; s<nentries;s++) {
     nbytes += k0hodo->GetEntry(s);
     if(trigpat[17]<=0) continue;
     for(int i=0; i<NumOfSegTOF; i++){
       bool flag=false;
       for(int j=0; j<16; j++){
         if(tofmt[i][j]==-999){
           if(!flag){
             if(j!=0){
               if(tofnhits!=1) continue;
               if(j==1){
                 if(trigflag[28]>0){
                   for(int k=0; k<NumOfSegSCH; k++){
                     if(sch_nhits!=1) continue;
                     if(sch_depth[k]!=1) continue;
                     if(sch_hitpat[0]!=k) continue;
                     if(ntKurama==1){
                       if(0<m2[ntKurama]&&m2[ntKurama]<0.1){
                         SchTofPiCut_KTime0->Fill(HULMHTDCCalib*sch_tdc[k][0]-tofmt[i][0]-SchTofKTime0);
                       }
                       if(0.1<m2[ntKurama]&&m2[ntKurama]<0.4){
                         SchTofKCut_KTime0->Fill(HULMHTDCCalib*sch_tdc[k][0]-tofmt[i][0]-SchTofKTime0);
                       }
                       if(0.4<m2[ntKurama]&&m2[ntKurama]<1){
                         SchTofPCut_KTime0->Fill(HULMHTDCCalib*sch_tdc[k][0]-tofmt[i][0]-SchTofKTime0);
                       }
                       if(0<m2[ntKurama]&&m2[ntKurama]<1){
                         SchTofCut3_KTime0->Fill(HULMHTDCCalib*sch_tdc[k][0]-tofmt[i][0]-SchTofKTime0);
                       }else{
                         SchTofCut3_KTime0_GOMI->Fill(HULMHTDCCalib*sch_tdc[k][0]-tofmt[i][0]-SchTofKTime0);
                       }
                     }
                   }
                 }
               }
             }
             flag=true;
           }
         }
       }
     }
   }


   SchTofPiCut_KTime0->Draw();
   c1->Print(pdf);
   SchTofKCut_KTime0->Draw();
   c1->Print(pdf);
   SchTofPCut_KTime0->Draw();
   c1->Print(pdf);
   SchTofCut3_m2->Draw("colz");
   c1->Print(pdf);
   SchTofCut3_pKurama->Draw("colz");
   c1->Print(pdf);

   gPad->SetLogy(1);
   SchTofCut3_KTime0->Draw();
   c1->Print(pdf);
   SchTofCut3_KTime0_GOMI->Draw();
   c1->Print(pdf);
   gPad->SetLogy(0);

   SchTofPCut_KTime0->SetStats(0);
   SchTofPiCut_KTime0->SetStats(0);
   SchTofKCut_KTime0->SetStats(0);
   SchTofPCut_KTime0->SetLineColor(3);
   SchTofPCut_KTime0->Draw();
   SchTofKCut_KTime0->Draw("same");
   SchTofPiCut_KTime0->SetLineColor(2);
   SchTofPiCut_KTime0->Draw("same");

   Leg1->AddEntry(SchTofPiCut_KTime0, "Pion"  ,"f");
   Leg1->AddEntry(SchTofKCut_KTime0,  "Kaon"  ,"f");
   Leg1->AddEntry(SchTofPCut_KTime0,  "Proton","f");
   Leg1->Draw();
   c1->Print(pdf);
   c1->Print(pdf+"]"); 


}

