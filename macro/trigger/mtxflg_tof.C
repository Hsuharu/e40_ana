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


void mtxflg_tof(int month, int runnum){
//////////////////////////////////////////////////////////
//   This file has been automatically generated 
//     (Fri Nov 16 14:55:11 2018 by ROOT version6.10/08)
//   from TTree tree/tree of Counter
//   found on file: rootfile/run05126_Trigger.root
//////////////////////////////////////////////////////////

  gStyle->SetOptStat(1111110); 
  gStyle->SetOptFit(1); 


//Reset ROOT and connect tree file
   gROOT->Reset();
//   TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("rootfile/run05126_Trigger.root");
   TString anadir=Form("%s/work/e40/ana",std::getenv("HOME")); 
   TString pdf = Form("%s/pdf/trigger/mtx_tof_%05d.pdf", anadir.Data(),runnum);
   TFile *f = new TFile(Form("%s/analyzer_%s/rootfile/run%05d_Trigger.root", anadir.Data(),Month[month], runnum),"READ");
   TTree *tree;
   f->GetObject("tree",tree);

//Declaration of leaves types
   Int_t           evnum;
   Int_t           spill;
   Int_t           trignhits;
   Int_t           trigpat[18];
   Int_t           trigflag[32];
   Int_t           bh1nhits;
   Int_t           bh1hitpat[11];
   Double_t        bh1ua[11];
   Double_t        bh1ut[11][16];
   Double_t        bh1da[11];
   Double_t        bh1dt[11][16];
   Int_t           bh2nhits;
   Int_t           bh2hitpat[8];
   Double_t        bh2ua[8];
   Double_t        bh2ut[8][16];
   Double_t        bh2da[8];
   Double_t        bh2dt[8][16];
   Int_t           fpga_bh2mtnhits;
   Int_t           fpga_bh2mthitpat[8][16];
   Double_t        fpga_bh2mt[8][16];
   Int_t           sacnhits;
   Int_t           sachitpat[4];
   Double_t        saca[4];
   Double_t        sact[4][16];
   Int_t           tofnhits;
   Int_t           tofhitpat[24];
   Double_t        tofua[24];
   Double_t        tofut[24][16];
   Double_t        tofda[24];
   Double_t        tofdt[24][16];
   Int_t           tofhtnhits;
   Int_t           tofhthitpat[24];
   Double_t        tofhtt[24][16];
   Int_t           lcnhits;
   Int_t           lchitpat[28];
   Double_t        lct[28][16];
   Double_t        bh1mt[11][16];
   Double_t        bh1de[11];
   Double_t        bh2mt[8][16];
   Double_t        bh2de[8];
   Double_t        sacmt[4][16];
   Double_t        sacde[4];
   Double_t        tofmt[24][16];
   Double_t        tofde[24];
   Double_t        tofhtmt[24][16];
   Double_t        lcmt[28][16];
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
   Int_t           sch_hitpat[26];
   Double_t        sch_tdc[64][16];
   Double_t        sch_trailing[64][16];
   Double_t        sch_tot[64][16];
   Int_t           sch_depth[64];
   Int_t           sch_ncl;
   Int_t           sch_clsize[25];
   Double_t        sch_ctime[25];
   Double_t        sch_ctot[25];
   Double_t        sch_clpos[25];
   Int_t           sftv_nhits;
   Int_t           sftv_hitpat[68];
   Double_t        sftv_tdc[320][16];
   Double_t        sftv_trailing[320][16];
   Double_t        sftv_tot[320][16];
   Int_t           sftv_depth[320];
   Int_t           sftv_ncl;
   Int_t           sftv_clsize[28];
   Double_t        sftv_ctime[28];
   Double_t        sftv_ctot[28];
   Double_t        sftv_clpos[28];
   Int_t           sftu_nhits;
   Int_t           sftu_hitpat[98];
   Double_t        sftu_tdc[320][16];
   Double_t        sftu_trailing[320][16];
   Double_t        sftu_tot[320][16];
   Int_t           sftu_depth[320];
   Int_t           sftu_ncl;
   Int_t           sftu_clsize[18];
   Double_t        sftu_ctime[18];
   Double_t        sftu_ctot[18];
   Double_t        sftu_clpos[18];
   Int_t           sftx_nhits;
   Int_t           sftx_unhits;
   Int_t           sftx_dnhits;
   Int_t           sftx_uhitpat[94];
   Int_t           sftx_dhitpat[69];
   Double_t        sftx_utdc[256][16];
   Double_t        sftx_dtdc[256][16];
   Double_t        sftx_utrailing[256][16];
   Double_t        sftx_dtrailing[256][16];
   Double_t        sftx_utot[256][16];
   Double_t        sftx_dtot[256][16];
   Int_t           sftx_udepth[256];
   Int_t           sftx_ddepth[256];
   Int_t           sftx_ncl;
   Int_t           sftx_clsize[30];
   Double_t        sftx_ctime[30];
   Double_t        sftx_ctot[30];
   Double_t        sftx_clpos[30];

   // Set branch addresses.
   tree->SetBranchAddress("evnum",&evnum);
   tree->SetBranchAddress("spill",&spill);
   tree->SetBranchAddress("trignhits",&trignhits);
   tree->SetBranchAddress("trigpat",trigpat);
   tree->SetBranchAddress("trigflag",trigflag);
   tree->SetBranchAddress("bh1nhits",&bh1nhits);
   tree->SetBranchAddress("bh1hitpat",bh1hitpat);
   tree->SetBranchAddress("bh1ua",bh1ua);
   tree->SetBranchAddress("bh1ut",bh1ut);
   tree->SetBranchAddress("bh1da",bh1da);
   tree->SetBranchAddress("bh1dt",bh1dt);
   tree->SetBranchAddress("bh2nhits",&bh2nhits);
   tree->SetBranchAddress("bh2hitpat",bh2hitpat);
   tree->SetBranchAddress("bh2ua",bh2ua);
   tree->SetBranchAddress("bh2ut",bh2ut);
   tree->SetBranchAddress("bh2da",bh2da);
   tree->SetBranchAddress("bh2dt",bh2dt);
   tree->SetBranchAddress("fpga_bh2mtnhits",&fpga_bh2mtnhits);
   tree->SetBranchAddress("fpga_bh2mthitpat",fpga_bh2mthitpat);
   tree->SetBranchAddress("fpga_bh2mt",fpga_bh2mt);
   tree->SetBranchAddress("sacnhits",&sacnhits);
   tree->SetBranchAddress("sachitpat",sachitpat);
   tree->SetBranchAddress("saca",saca);
   tree->SetBranchAddress("sact",sact);
   tree->SetBranchAddress("tofnhits",&tofnhits);
   tree->SetBranchAddress("tofhitpat",tofhitpat);
   tree->SetBranchAddress("tofua",tofua);
   tree->SetBranchAddress("tofut",tofut);
   tree->SetBranchAddress("tofda",tofda);
   tree->SetBranchAddress("tofdt",tofdt);
   tree->SetBranchAddress("tofhtnhits",&tofhtnhits);
   tree->SetBranchAddress("tofhthitpat",tofhthitpat);
   tree->SetBranchAddress("tofhtt",tofhtt);
   tree->SetBranchAddress("lcnhits",&lcnhits);
   tree->SetBranchAddress("lchitpat",lchitpat);
   tree->SetBranchAddress("lct",lct);
   tree->SetBranchAddress("bh1mt",bh1mt);
   tree->SetBranchAddress("bh1de",bh1de);
   tree->SetBranchAddress("bh2mt",bh2mt);
   tree->SetBranchAddress("bh2de",bh2de);
   tree->SetBranchAddress("sacmt",sacmt);
   tree->SetBranchAddress("sacde",sacde);
   tree->SetBranchAddress("tofmt",tofmt);
   tree->SetBranchAddress("tofde",tofde);
   tree->SetBranchAddress("tofhtmt",tofhtmt);
   tree->SetBranchAddress("lcmt",lcmt);
   tree->SetBranchAddress("t0",t0);
   tree->SetBranchAddress("ct0",ct0);
   tree->SetBranchAddress("btof",btof);
   tree->SetBranchAddress("cbtof",cbtof);
   tree->SetBranchAddress("Time0Seg",&Time0Seg);
   tree->SetBranchAddress("deTime0",&deTime0);
   tree->SetBranchAddress("Time0",&Time0);
   tree->SetBranchAddress("CTime0",&CTime0);
   tree->SetBranchAddress("Btof0Seg",&Btof0Seg);
   tree->SetBranchAddress("deBtof0",&deBtof0);
   tree->SetBranchAddress("Btof0",&Btof0);
   tree->SetBranchAddress("CBtof0",&CBtof0);
   tree->SetBranchAddress("sch_nhits",&sch_nhits);
   tree->SetBranchAddress("sch_hitpat",sch_hitpat);
   tree->SetBranchAddress("sch_tdc",sch_tdc);
   tree->SetBranchAddress("sch_trailing",sch_trailing);
   tree->SetBranchAddress("sch_tot",sch_tot);
   tree->SetBranchAddress("sch_depth",sch_depth);
   tree->SetBranchAddress("sch_ncl",&sch_ncl);
   tree->SetBranchAddress("sch_clsize",sch_clsize);
   tree->SetBranchAddress("sch_ctime",sch_ctime);
   tree->SetBranchAddress("sch_ctot",sch_ctot);
   tree->SetBranchAddress("sch_clpos",sch_clpos);
   tree->SetBranchAddress("sftv_nhits",&sftv_nhits);
   tree->SetBranchAddress("sftv_hitpat",sftv_hitpat);
   tree->SetBranchAddress("sftv_tdc",sftv_tdc);
   tree->SetBranchAddress("sftv_trailing",sftv_trailing);
   tree->SetBranchAddress("sftv_tot",sftv_tot);
   tree->SetBranchAddress("sftv_depth",sftv_depth);
   tree->SetBranchAddress("sftv_ncl",&sftv_ncl);
   tree->SetBranchAddress("sftv_clsize",sftv_clsize);
   tree->SetBranchAddress("sftv_ctime",sftv_ctime);
   tree->SetBranchAddress("sftv_ctot",sftv_ctot);
   tree->SetBranchAddress("sftv_clpos",sftv_clpos);
   tree->SetBranchAddress("sftu_nhits",&sftu_nhits);
   tree->SetBranchAddress("sftu_hitpat",sftu_hitpat);
   tree->SetBranchAddress("sftu_tdc",sftu_tdc);
   tree->SetBranchAddress("sftu_trailing",sftu_trailing);
   tree->SetBranchAddress("sftu_tot",sftu_tot);
   tree->SetBranchAddress("sftu_depth",sftu_depth);
   tree->SetBranchAddress("sftu_ncl",&sftu_ncl);
   tree->SetBranchAddress("sftu_clsize",sftu_clsize);
   tree->SetBranchAddress("sftu_ctime",sftu_ctime);
   tree->SetBranchAddress("sftu_ctot",sftu_ctot);
   tree->SetBranchAddress("sftu_clpos",sftu_clpos);
   tree->SetBranchAddress("sftx_nhits",&sftx_nhits);
   tree->SetBranchAddress("sftx_unhits",&sftx_unhits);
   tree->SetBranchAddress("sftx_dnhits",&sftx_dnhits);
   tree->SetBranchAddress("sftx_uhitpat",sftx_uhitpat);
   tree->SetBranchAddress("sftx_dhitpat",sftx_dhitpat);
   tree->SetBranchAddress("sftx_utdc",sftx_utdc);
   tree->SetBranchAddress("sftx_dtdc",sftx_dtdc);
   tree->SetBranchAddress("sftx_utrailing",sftx_utrailing);
   tree->SetBranchAddress("sftx_dtrailing",sftx_dtrailing);
   tree->SetBranchAddress("sftx_utot",sftx_utot);
   tree->SetBranchAddress("sftx_dtot",sftx_dtot);
   tree->SetBranchAddress("sftx_udepth",sftx_udepth);
   tree->SetBranchAddress("sftx_ddepth",sftx_ddepth);
   tree->SetBranchAddress("sftx_ncl",&sftx_ncl);
   tree->SetBranchAddress("sftx_clsize",sftx_clsize);
   tree->SetBranchAddress("sftx_ctime",sftx_ctime);
   tree->SetBranchAddress("sftx_ctot",sftx_ctot);
   tree->SetBranchAddress("sftx_clpos",sftx_clpos);

//     This is the loop skeleton
//       To read only selected branches, Insert statements like:
// tree->SetBranchStatus("*",0);  // disable all branches
// TTreePlayer->SetBranchStatus("branchname",1);  // activate branchname



//-para def-----------------------------------------------------------------------------------------

//-hist def-----------------------------------------------------------------------------------------
//-Trigger Flag -------
  TH1D *TrigNhits = new TH1D("TrigNhits","TrigNhits",20,0,20);

  TH1D *TrigPat[18];
  for(int i=0;i<18;i++){
    TrigPat[i]= new TH1D(Form("TrigPat%d",i+1),Form("TrigPat%d",i+1),32,0,32);
  }

  TH1D *TrigFlag[32];
  TH1D *TrigFlagCut[32];
  for(int i=0;i<32;i++){
    TrigFlag[i]= new TH1D(Form("TrigFlag %s",TriggerFlag[i]),Form("TrigFlag %s",TriggerFlag[i]),1000,0,2100);
    TrigFlagCut[i]= new TH1D(Form("TrigFlagCut %s",TriggerFlag[i]),Form("TrigFlagCut %s",TriggerFlag[i]),1000,-2100,0);
  }
  
//-Tof ----------------
  TH1D *TofNhits = new TH1D("TofNhits","TofNhits",20,0,20);

  TH1D *TofMt[NumOfSegTOF];
  TH1D *TofMtCut[NumOfSegTOF];
  TH1D *TofSegMultiplicity[NumOfSegTOF];
  TH1D *TofHitPat[NumOfSegTOF];
  for(int i=0;i<NumOfSegTOF;i++){
    TofMt[i]= new TH1D(Form("TofMt%d",i+1),Form("TofMt%d",i+1),100,-10,90);
    TofMtCut[i]= new TH1D(Form("TofMtCut%d",i+1),Form("TofMtCut%d",i+1),100,-10,90);
    TofSegMultiplicity[i]= new TH1D(Form("TofSegMultiplicity%d",i+1),Form("TofSegMultiplicity%d",i+1),10,0,10);
    TofHitPat[i]= new TH1D(Form("TofHitPat%d",i+1),Form("TofHitPat%d",i+1),NumOfSegTOF,0,NumOfSegTOF);
  }

  TH1D *TofMtOr = new TH1D("TofMtOr","TofMtOr",100,-10,90);
  TH1D *TofMtOrCut = new TH1D("TofMtOrCut","TofMtOrCut",100,-10,90);
  TH1D *TofMtOrMtxFlgCut = new TH1D("TofMtOr TdcCut & MtxFlgCut","TofMtOr TdcCut & MtxFlgCut",100,-10,90);
  TH1D *TofMtOrVarMtxFlgCut = new TH1D("TofMtOrVarMtxFlgCut","TofMtOrVarMtxFlgCut",1000,-10,90);
  TH1D *TofMultiplicityOr = new TH1D("TofMultiplicityOr","TofMultiplicityOr",10,0,10);

//-Mtx Flag - Tof -----
  TH1D *MtxFlag_Tof = new TH1D("MtxFlag_Tof","MtxFlag_Tof",2100,0,2100);
  TH1D *MtxFlag_TofCut = new TH1D("MtxFlag_TofCut","MtxFlag_TofCut",2100,-2100,0);

//-Event loop---------------------------------------------------------------------------------------
   Long64_t nentries = tree->GetEntries();
   Long64_t nbytes = 0;
   for (Long64_t s=0; s<nentries;s++) {
     nbytes += tree->GetEntry(s);
     TrigNhits->Fill(trignhits);
     for(int i=0; i<32; i++){
       TrigPat[i]->Fill(trigpat[i]);
     }
     for(int i=0; i<32; i++){
       TrigFlag[i]->Fill(trigflag[i]);
     }

     TofNhits->Fill(tofnhits);

     for(int i=0; i<NumOfSegTOF; i++){
       TofHitPat[i]->Fill(tofhitpat[i]);
       bool flag=false;
       for(int j=0; j<16; j++){
         TofMt[i]->Fill(tofmt[i][j]);
         TofMtOr->Fill(tofmt[i][j]);
         MtxFlag_Tof->Fill(abs(-trigflag[28]-tofmt[i][j]));
         if(tofmt[i][j]==-999){
           if(!flag){
             TofSegMultiplicity[i]->Fill(j);
             TofMultiplicityOr->Fill(j);
             flag=true;
           }
         }else{
           TofMtCut[i]->Fill(tofmt[i][j]);
           TofMtOrCut->Fill(tofmt[i][j]);
           MtxFlag_TofCut->Fill(-trigflag[28]-tofmt[i][j]);
           TrigFlagCut[28]->Fill(-trigflag[28]);
           if(trigflag[28]>0){
             TofMtOrMtxFlgCut->Fill(tofmt[i][j]);
           }else{
             TofMtOrVarMtxFlgCut->Fill(tofmt[i][j]);
           }
         }
       }
     }
   }

//-Canvas def---------------------------------------------------------------------------------------
  TCanvas *c1 = new TCanvas("c1","c1",1200,900);
  TCanvas *c2 = new TCanvas("c2","c2",1200,900);
  TCanvas *c3 = new TCanvas("c3","c3",1200,900);
  TCanvas *c4 = new TCanvas("c4","c4",1200,900);
  TCanvas *c5 = new TCanvas("c5","c5",1200,900);

//  c1->Divide();
  c2->Divide(6,3);
  c3->Divide(4,4);
  c4->Divide(4,3);
  c5->Divide(2,2);

   c1->Print(pdf+"["); 

//-Hist Draw----------------------------------------------------------------------------------------
  c1->cd();
  TrigNhits->Draw();
  c1->Print(pdf);

  for(int i=0; i<18; i++){
    c2->cd(i+1);
    TrigPat[i]->Draw();
  }
  c2->Print(pdf);

  for(int i=0; i<2; i++){
    for(int j=0; j<16; j++){
      c3->cd(j+1);
      TrigFlag[i*16+j]->Draw();
    }
    c3->Print(pdf);
  }

  c1->cd();
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

  for(int j=0; j<2; j++){
    for(int i=0; i<12; i++){
      c4->cd(i+1);
      TofSegMultiplicity[j*12+i]->Draw();
    }
    c4->Print(pdf);
  }

  c1->cd();
  TofMultiplicityOr->Draw();
  c1->Print(pdf);

  for(int j=0; j<6; j++){
    for(int i=0; i<4; i++){
      c5->cd(i+1);
      TofHitPat[j*4+i]->Draw();
    }
    c5->Print(pdf);
  }

  for(int j=0; j<6; j++){
    for(int i=0; i<4; i++){
      c5->cd(i+1);
      TofMtCut[j*4+i]->Draw();
    }
    c5->Print(pdf);
  }

  c1->cd();
//  TofHitPat->Draw();
//  c1->Print(pdf);

  TrigFlagCut[28]->Draw();
  c1->Print(pdf);

  TrigFlagCut[28]->SetAxisRange(-1050,-900,"X");
  TrigFlagCut[28]->Draw();
  c1->Print(pdf);

  TofMtOrCut->Draw();
  c1->Print(pdf);

  MtxFlag_Tof->Draw();
  c1->Print(pdf);
    
  MtxFlag_TofCut->Draw();
  c1->Print(pdf);

  MtxFlag_TofCut->SetAxisRange(-1100,-700,"X");
  MtxFlag_TofCut->Draw();
  c1->Print(pdf);

  TofMtOrMtxFlgCut->Draw();
  c1->Print(pdf);

  TofMtOrVarMtxFlgCut->Draw();
  c1->Print(pdf);

  c1->Print(pdf+"]"); 

}
