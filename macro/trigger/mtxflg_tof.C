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
   double HULMHTDCCalib = -0.8333;

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
  TH1D *TrigFlag28NhitsDepthCut= new TH1D("MtxFlag TdcCut & MtxFlg & Nhits=1 & MaxDepth#1 Cut","MtxFlag TdcCut & MtxFlg & Nhits=1 & MaxDepth#1 Cut",1800,-1800,0);

  TH1D *TofMt[NumOfSegTOF];
  TH1D *TofMtCut[NumOfSegTOF];
  TH1D *TofHitPat[NumOfSegTOF];
  TH1D *TofMtDepthPat[NumOfSegTOF];
  TH1D *TofMtOrMtxFlgNhitsCut[NumOfSegTOF];
  TH1D *TofMtMtxFlgNhitsDepthCut[NumOfSegTOF];
  TH1D *MtxFlag_TofNhitsCut[NumOfSegTOF];
  TH1D *TrigFlag28NhitsCut[NumOfSegTOF];
  for(int i=0;i<NumOfSegTOF;i++){
    TofMt[i]= new TH1D(Form("TofMt%d",i+1),Form("TofMt%d",i+1),100,-10,90);
    TofMtCut[i]= new TH1D(Form("TofMtCut%d",i+1),Form("TofMtCut%d",i+1),100,-10,90);
    TofHitPat[i]= new TH1D(Form("TofHitPat%d",i+1),Form("TofHitPat%d",i+1),NumOfSegTOF,0,NumOfSegTOF);
    TofMtDepthPat[i]= new TH1D(Form("TofMtDepthPat%d",i+1),Form("TofMtDepthPat%d",i+1),5,0,5);
    TofMtOrMtxFlgNhitsCut[i] = new TH1D(Form("TofMtOr TdcCut & MtxFlg & Nhits%d Cut",i+1),Form("TofMtOr TdcCut & MtxFlg & Nhits%d Cut",i+1),100,-10,90);
    TofMtMtxFlgNhitsDepthCut[i] = new TH1D(Form("TofMt%d TdcCut & MtxFlg & Nhits=1 & MaxDepth#1 Cut",i+1),Form("TofMt%d TdcCut & MtxFlg & Nhits=1 & MaxDepth#1 Cut",i+1),100,-10,90);
    MtxFlag_TofNhitsCut[i] = new TH1D(Form("MtxFlag_Tof TdcCut & MtxFlg & Nhits%d Cut",i+1),Form("MtxFlag_Tof TdcCut & MtxFlg & Nhits%d Cut",i+1),1800,-1800,0);
    TrigFlag28NhitsCut[i]= new TH1D(Form("MtxFlag TdcCut & MtxFlg & Nhits%d Cut",i+1),Form("MtxFlag_Tof TdcCut & MtxFlg & Nhits%d Cut",i+1),1800,-1800,0);
  }

  TH1D *TofMtOr = new TH1D("TofMtOr","TofMtOr",100,-10,90);
  TH1D *TofMtOrCut = new TH1D("TofMtOrCut","TofMtOrCut",100,-10,90);
  TH1D *TofMtOrDepthPat = new TH1D("TofMtOrDepthPat","TofMtOrDepthPat",10,0,10);
  TH1D *TofMtOrAllDepthPat = new TH1D("TofMtOrAllDepthPat","TofMtOrAllDepthPat",10,0,10);
  TH1D *TofMtOrMtxFlgCut = new TH1D("TofMtOr TdcCut & MtxFlgCut","TofMtOr TdcCut & MtxFlgCut",100,-10,90);
  TH1D *TofMtOrVarMtxFlgCut = new TH1D("TofMtOrVarMtxFlgCut","TofMtOrVarMtxFlgCut",1000,-10,90);
  TH1D *TofMtOrMtxFlgNhitsDepthCut = new TH1D("TofMtOr TdcCut & MtxFlg & Nhits=1 & MaxDepth#1 Cut","TofMtOr TdcCut & MtxFlg & Nhits=1 & MaxDepth#1 Cut",100,-10,90);

//-Mtx Flag - Tof -----
  TH1D *MtxFlag_Tof = new TH1D("MtxFlag_Tof","MtxFlag_Tof",2100,0,2100);
  TH1D *MtxFlag_TofCut = new TH1D("MtxFlag_TofCut","MtxFlag_TofCut",1800,-1800,0);
  TH1D *MtxFlag_TofNhitsDepthCut = new TH1D("MtxFlag-TofMtOr TdcCut & MtxFlg & Nhits=1 & Depth#1Cut","MtxFlag-TofMtOr TdcCut & MtxFlg & Nhits=1 & Depth#1Cut",2100,-2100,0);

//- Correlation -------
  TH2D *MtxFlag_vs_TofMtOrNhitsDepthCut = new TH2D("MtxFlag vs TofMtOr TdcCut & MtxFlg & Nhits=1 & Depth#1Cut","MtxFlag vs TofMtOr TdcCut & MtxFlg & Nhits=1 & Depth#1Cut",100,-10,90,1800,-1800,0);
  TH2D *MtxFlag_vs_MtxFlagTofMtOrNhitsDepthCut = new TH2D("MtxFlag vs MtxFlag-TofMtOr TdcCut & MtxFlg & Nhits=1 & Depth#1Cut","MtxFlag vs MtxFlag-TofMtOr TdcCut & MtxFlg & Nhits=1 & Depth#1Cut",100,-10,90,1800,-1800,0);
  TH2D *TofMtOr_vs_MtxFlagTofMtOrNhitsDepthCut = new TH2D("TofMtOr vs MtxFlag-TofMtOr TdcCut & MtxFlg & Nhits=1 & Depth#1Cut","TofMtOr vs MtxFlag-TofMtOr TdcCut & MtxFlg & Nhits=1 & Depth#1Cut",100,-10,90,1800,-1800,0);

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
             if(j!=0){
               if(tofnhits!=1) continue;
               TofMtDepthPat[i]->Fill(j);
               TofMtOrDepthPat->Fill(j);
               if(j==1){
                 if(trigflag[28]>0){
                   TofMtMtxFlgNhitsDepthCut[i]->Fill(tofmt[i][0]);
                   TofMtOrMtxFlgNhitsDepthCut->Fill(tofmt[i][0]);
                   TrigFlag28NhitsDepthCut->Fill(HULMHTDCCalib*trigflag[28]);
                   MtxFlag_TofNhitsDepthCut->Fill(HULMHTDCCalib*trigflag[28]-tofmt[i][0]);
                   MtxFlag_vs_TofMtOrNhitsDepthCut->Fill(tofmt[i][0],HULMHTDCCalib*trigflag[28]);
                 }
               }
             }
             flag=true;
           }
         }else{
           TofMtCut[i]->Fill(tofmt[i][j]);
           TofMtOrCut->Fill(tofmt[i][j]);
           MtxFlag_TofCut->Fill(-trigflag[28]-tofmt[i][j]);
           TrigFlagCut[28]->Fill(-trigflag[28]);
           if(trigflag[28]>0){
             TofMtOrMtxFlgCut->Fill(tofmt[i][j]);
               if(tofnhits!=1) continue;
               TofMtOrAllDepthPat->Fill(j+1);
           }else{
             TofMtOrVarMtxFlgCut->Fill(tofmt[i][j]);
           }
         }
       }
       if(trigflag[28]>0&&tofnhits==i+1){
         for(int j=0; j<NumOfSegTOF; j++){
           for(int k=0; k<16; k++){
             if(tofmt[j][k]!=-999){
               TofMtOrMtxFlgNhitsCut[i]->Fill(tofmt[j][k]);
               MtxFlag_TofNhitsCut[i]->Fill(HULMHTDCCalib*trigflag[28]-tofmt[j][k]);
               TrigFlag28NhitsCut[i]->Fill(HULMHTDCCalib*trigflag[28]);
             }
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
      TofMtDepthPat[j*12+i]->Draw();
    }
    c4->Print(pdf);
  }

  c1->cd();
  TofMtOrDepthPat->Draw();
  c1->Print(pdf);

  TofMtOrAllDepthPat->Draw();
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

  TrigFlagCut[28]->SetAxisRange(-1010,-910,"X");
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

  for(int j=0; j<6; j++){
    for(int i=0; i<4; i++){
      c6->cd(1);
      TrigFlag28NhitsCut[j*4+i]->SetAxisRange(-1010,-910,"X");
      TrigFlag28NhitsCut[j*4+i]->Draw();
      c6->cd(2);
      TofMtOrMtxFlgNhitsCut[j*4+i]->Draw();
      c6->cd(3);
      MtxFlag_TofNhitsCut[j*4+i]->SetAxisRange(-1010,-910,"X");
      MtxFlag_TofNhitsCut[j*4+i]->Draw();
      c6->Print(pdf);
    }
  }

  c6->cd(1);
  TrigFlag28NhitsDepthCut->SetAxisRange(-1010,-910,"X");
  TrigFlag28NhitsDepthCut->Draw();
  c6->cd(2);
  TofMtOrMtxFlgNhitsDepthCut->Draw();
  c6->cd(3);
  MtxFlag_TofNhitsDepthCut->SetAxisRange(-1010,-910,"X");
  MtxFlag_TofNhitsDepthCut->Draw();
  c6->cd(4);
  MtxFlag_vs_TofMtOrNhitsDepthCut->Draw();
  c6->Print(pdf);

  c1->Print(pdf+"]"); 

}
