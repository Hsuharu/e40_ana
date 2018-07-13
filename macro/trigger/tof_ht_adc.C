#include "DetectorID.hh"
#include <iostream>
#include "TString.h"


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


void tof_ht_adc( int month, int runnum){
////////////////////////////////////////////////////////////
//   This file has been automatically generated           //
//     (Sun Feb 25 23:10:42 2018 by ROOT version6.10/08)  //
//   from TTree tree/tree of Counter                      //
//   found on file: ../rootfile/run04571_hodo.root        //
////////////////////////////////////////////////////////////

  gStyle->SetOptStat(1111110); 
  gStyle->SetOptFit(1); 

//Recchar *monthhar *monthset ROOT and connect tree file
   gROOT->Reset();
//   TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("../rootfile/run04571_hodo.root");
   TString anadir=Form("%s/work/e40/ana",std::getenv("HOME")); 
//j   TFile *f = new TFile(Form("%s/analyzer_%s/rootfile/run%05d_hodo.root", anadir.Data(),Month[month], runnum),"READ");
   TFile *f = new TFile(Form("%s/analyzer_%s/rootfile/run%05d_Hodoscope.root", anadir.Data(),Month[month], runnum),"READ");
   if (!f) {
      f = new TFile(Form("%s/rootfile/run%05d_Hodoscope.root", anadir.Data() , runnum));
   }
    TTree *tree;
    f->GetObject("tree",tree);

//Declaration of leaves types
   Int_t           evnum;
   Int_t           trignhits;
   Int_t           trigpat[11];
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

   // Set branch addresses.
   tree->SetBranchAddress("evnum",&evnum);
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

//     This is the loop skeleton
//       To read only selected branches, Insert statements like:
// tree->SetBranchStatus("*",0);  // disable all branches
// TTreePlayer->SetBranchStatus("branchname",1);  // activate branchname

   int seg1 = 4; //1 origine
   int seg2 = 4; //1 origine
   int range1 = 0; //  
   int range2 = 3; //  range1 < nhit < range2 
   int xbin = 60;

   int MaxDepth = 16;

   int NumOfAllHist = 100;

//   TH1D *hist[NumOfAllHist]; 
//   for(int i = 0; i<NumOfAllHist; i++){
//     hist[i] = new TH1D(Form("hist%d",i+1),Form("hist%d",i+1), , ,,  );
//   }

   TH1D *TOFUT[NumOfSegTOF]; 
   TH1D *TOFDT[NumOfSegTOF]; 
   TH1D *TOFUADC[NumOfSegTOF]; 
   TH1D *TOFDADC[NumOfSegTOF]; 
   TH1D *TOFUMIP[NumOfSegTOF]; 
   TH1D *TOFDMIP[NumOfSegTOF]; 
   TH1D *TOFUMIPSC[NumOfSegTOF]; 
   TH1D *TOFDMIPSC[NumOfSegTOF]; 
   TH1D *TOFUPEDE[NumOfSegTOF]; 
   TH1D *TOFDPEDE[NumOfSegTOF]; 
      for (int i=0; i<NumOfSegTOF;i++) {
        TOFUT[i] = new TH1D(Form("TOFUT_%d",i+1),Form("TOFUT_%d",i+1),2000,200000,400000);
        TOFDT[i] = new TH1D(Form("TOFDT_%d",i+1),Form("TOFDT_%d",i+1),2000,200000,400000);
        TOFUADC[i] = new TH1D(Form("TOFUADC_%d",i+1),Form("TOFUADC_%d",i+1),1000,0,4000);
        TOFDADC[i] = new TH1D(Form("TOFDADC_%d",i+1),Form("TOFDADC_%d",i+1),1000,0,4000);
        TOFUMIP[i] = new TH1D(Form("TOFUMIP_%d",i+1),Form("TOFUMIP_%d",i+1),1000,0,4000);
        TOFDMIP[i] = new TH1D(Form("TOFDMIP_%d",i+1),Form("TOFDMIP_%d",i+1),1000,0,4000);
        TOFUMIPSC[i] = new TH1D(Form("TOFUMIPSC_%d",i+1),Form("TOFUMIPSC_%d",i+1),1000,0,4);
        TOFDMIPSC[i] = new TH1D(Form("TOFDMIPSC_%d",i+1),Form("TOFDMIPSC_%d",i+1),1000,0,4);
        TOFUPEDE[i] = new TH1D(Form("TOFUPEDE_%d",i+1),Form("TOFUPEDE_%d",i+1),4000,0,4000);
        TOFDPEDE[i] = new TH1D(Form("TOFDPEDE_%d",i+1),Form("TOFDPEDE_%d",i+1),4000,0,4000);
      }
   TH1D *TOFHitPat = new TH1D("TOFHitPat","TOFHitPat",NumOfSegTOF+1,0,NumOfSegTOF+1);

   TH1D *HtTOFT[NumOfSegHtTOF]; 
   TH1D *HtTOFA[NumOfSegHtTOF]; 
   TH1D *HtTOFT0[NumOfSegHtTOF]; 
   TH1D *HtTOFT0ns[NumOfSegHtTOF]; 
   TH1D *HtTOFMIP[NumOfSegHtTOF]; 
      for (int i=0; i<NumOfSegHtTOF;i++) {
        HtTOFT[i] = new TH1D(Form("HtTOF_%dT",i+1),Form("HtTOF_%dT",i+1),4000,0,4000);
        HtTOFA[i] = new TH1D(Form("TOF-HTADC-Pede %s [ch]",STOF_HT[i]),Form("TOF-HTADC-Pede %s [ch];[ch];[counts]",STOF_HT[i]),4000,0,4000);
        HtTOFT0[i] = new TH1D(Form("HtTOFT0_%dT",i+1),Form("HtTOFT0_%dT",i+1),4000,-2000,2000);
        HtTOFT0ns[i] = new TH1D(Form("TOF-HT %s Time [ns]",STOF_HT[i]),Form("TOF-HT %s Time [ns]",STOF_HT[i]),4000,-1666,1666);
        HtTOFMIP[i] = new TH1D(Form("TOF-HT %s [mip]",STOF_HT[i]),Form("TOF-HT %s [mip];[mip];[counts]",STOF_HT[i]),4000,0,4);
      }
   TH1D *HtTOFHitPat = new TH1D("HtTOFHitPat","HtTOFHitPat;[Segment];[counts]",NumOfSegHtTOF+1,0,NumOfSegHtTOF+1);

   Long64_t nentries = tree->GetEntries();
   double fitprm[3];
   double sactprm[NumOfSegSAC]; 
   double httoftprm[NumOfSegHtTOF]; 
   double httofadc[NumOfSegHtTOF]; 
   double httofmip[NumOfSegHtTOF]; 
   double tofutprm[NumOfSegTOF]; 
   double tofdtprm[NumOfSegTOF]; 
   double tofumipprm[NumOfSegTOF]; 
   double tofdmipprm[NumOfSegTOF]; 
   double tofubgprm[NumOfSegTOF]; 
   double tofdbgprm[NumOfSegTOF]; 
   double sigma_tofubgprm[NumOfSegTOF]; 
   double sigma_tofdbgprm[NumOfSegTOF]; 


   double mhtdcns = 0.8333;

//Fit range
   double f_l  = 2000;

//Draw range
   double l = 5000;

//gate range
   double gr1 = 5000; 

//Draw range
   int T0_range_min = -100;
   int T0_range_max =  100;

//Draw range ns
   int T0ns_range_min = -83;
   int T0ns_range_max =  83;

   double l_mip = 100; 
   double l_mip0 = 50;
   double l_bg = 4; 
   double l_bg1 = 3; 
   double l_bg2 = 2; 
//Draw range
   double r_bg = 10; 

   TF1 *fit = new TF1("fit","gaus"); 

/////////////////////////////////////////////////////////////////////////////////////////////
//                                                                                         //
//    TOF TDC Mean get code                                                                //
//                                                                                         //
/////////////////////////////////////////////////////////////////////////////////////////////
   Long64_t nbytes = 0;
   for (Long64_t s=0; s<nentries;s++) {
      nbytes += tree->GetEntry(s);
      for (int i=0; i<NumOfSegTOF;i++) {
        if(tofut[i]>0 && tofdt[i]>0){
          for(int j=0; j<MaxDepth; j++){
            TOFUT[i]->Fill(tofut[i][j]);
            TOFDT[i]->Fill(tofdt[i][j]);
          }
        }
        TOFHitPat->Fill(tofhitpat[i]);
      }
   }

   
   TString pdf = Form("%s/pdf/trigger/tofht_adc_%05d.pdf", anadir.Data(),runnum);
   TCanvas *c1 = new TCanvas("c1","c1",800,700); 
   c1->Print(pdf+"["); 

// TOF UandD TDC MEAN 
   for (int i=0; i<NumOfSegTOF;i++) {
       tofutprm[i] = TOFUT[i]->GetMaximumBin();   
       tofdtprm[i] = TOFDT[i]->GetMaximumBin();   

       tofutprm[i] = TOFUT[i]->GetXaxis()->GetBinCenter(tofutprm[i]);  
       tofdtprm[i] = TOFDT[i]->GetXaxis()->GetBinCenter(tofdtprm[i]);  

       TOFUT[i]->Fit("fit","i","", tofutprm[i]-f_l, tofutprm[i]+f_l); 
       tofutprm[i] = fit->GetParameter(1);  
       TOFUT[i]->GetXaxis()->SetRangeUser(tofutprm[i]-1*(l), tofutprm[i]+2*(l)); 

       TOFDT[i]->Fit("fit","i","", tofdtprm[i]-f_l, tofdtprm[i]+f_l); 
       tofdtprm[i] = fit->GetParameter(1);  
       TOFDT[i]->GetXaxis()->SetRangeUser(tofdtprm[i]-1*(l), tofdtprm[i]+2*(l));  

   }

   c1->cd(); 
   TOFHitPat->Draw(); 
   c1 ->Print(pdf); 

   c1->cd(); 
   c1->SetGridx();
   c1->SetGridy();

   for(int i=0; i<NumOfSegTOF; i++){
     TOFUT[i]->Draw(); 
     c1 ->Print(pdf); 
   }
   for(int i=0; i<NumOfSegTOF; i++){
     TOFDT[i]->Draw(); 
     c1 ->Print(pdf); 
   }

/////////////////////////////////////////////////////////////////////////////////////////////
//                                                                                         //
//    TOF ADC Pede get                                                                     //
//                                                                                         //
/////////////////////////////////////////////////////////////////////////////////////////////
   nbytes = 0;
   for (Long64_t s=0; s<nentries;s++) {
     nbytes += tree->GetEntry(s);
     int u_mipflg = 0;
     int d_mipflg = 0;
     for (int i=0; i<NumOfSegTOF;i++) {
       for (int j=0; j<MaxDepth;j++) {
         if(tofut[i][j] > (tofutprm[i] - gr1) && tofut[i][j] < (tofutprm[i] + gr1) ) u_mipflg = 1;
         if(tofdt[i][j] > (tofdtprm[i] - gr1) && tofdt[i][j] < (tofdtprm[i] + gr1) ) d_mipflg = 1;
       }
       if(u_mipflg == 0 && d_mipflg == 0 ){
         TOFUPEDE[i]->Fill(tofua[i]);
         TOFDPEDE[i]->Fill(tofda[i]);
       }
       u_mipflg = 0;
       d_mipflg = 0;
     }
   }

   TF1 *fit3 = new TF1("fit3","landau"); 

   for (int i=0; i<NumOfSegTOF;i++) {
       tofubgprm[i] = TOFUPEDE[i]->GetMaximumBin();   
       tofdbgprm[i] = TOFDPEDE[i]->GetMaximumBin();   

       tofubgprm[i] = TOFUPEDE[i]->GetXaxis()->GetBinCenter(tofubgprm[i]);  
       tofdbgprm[i] = TOFDPEDE[i]->GetXaxis()->GetBinCenter(tofdbgprm[i]);  

       TOFUPEDE[i]->Fit("fit","","", tofubgprm[i]-l_bg1, tofubgprm[i]+l_bg1);  
       tofubgprm[i] = fit->GetParameter(1);  
       sigma_tofubgprm[i] = fit->GetParameter(2);  
       TOFUPEDE[i]->GetXaxis()->SetRangeUser(tofubgprm[i]-1*(r_bg), tofubgprm[i]+2*(r_bg)); 

       TOFDPEDE[i]->Fit("fit","","", tofdbgprm[i]-l_bg1, tofdbgprm[i]+l_bg1); 
       tofdbgprm[i] = fit->GetParameter(1);  
       sigma_tofdbgprm[i] = fit->GetParameter(2);  
       TOFDPEDE[i]->GetXaxis()->SetRangeUser(tofdbgprm[i]-(r_bg), tofdbgprm[i]+2*(r_bg)); 

   }


   for(int i=0; i<NumOfSegTOF; i++){
     TOFUPEDE[i]->Draw(); 
     c1 ->Print(pdf); 
   }
   for(int i=0; i<NumOfSegTOF; i++){
     TOFDPEDE[i]->Draw(); 
     c1 ->Print(pdf); 
   }
   


/////////////////////////////////////////////////////////////////////////////////////////////
//                                                                                         //
//    TOF ADC MIP get                                                                      //
//                                                                                         //
/////////////////////////////////////////////////////////////////////////////////////////////
   nbytes = 0;
   for (Long64_t s=0; s<nentries;s++) {
     nbytes += tree->GetEntry(s);
     int u_mipflg = 0;
     int d_mipflg = 0;
     for (int i=0; i<NumOfSegTOF;i++) {
       for (int j=0; j<MaxDepth;j++) {
         if(tofut[i][j] > (tofutprm[i] - gr1) && tofut[i][j] < (tofutprm[i] + gr1) ) u_mipflg = 1;
         if(tofdt[i][j] > (tofdtprm[i] - gr1) && tofdt[i][j] < (tofdtprm[i] + gr1) ) d_mipflg = 1;
       }
       if(u_mipflg && d_mipflg){
         if(tofua[i] > tofubgprm[i] + 200*sigma_tofubgprm[i]) TOFUMIP[i]->Fill(tofua[i]);
         if(tofda[i] > tofdbgprm[i] + 200*sigma_tofdbgprm[i]) TOFDMIP[i]->Fill(tofda[i]);
       }
       u_mipflg = 0;
       d_mipflg = 0;
     }
   }


   for (int i=0; i<NumOfSegTOF;i++) {
       tofumipprm[i] = TOFUMIP[i]->GetMaximumBin();   
       tofdmipprm[i] = TOFDMIP[i]->GetMaximumBin();   

       tofumipprm[i] = TOFUMIP[i]->GetXaxis()->GetBinCenter(tofumipprm[i]);  
       tofdmipprm[i] = TOFDMIP[i]->GetXaxis()->GetBinCenter(tofdmipprm[i]);  

       TOFUMIP[i]->Fit("fit","","", tofumipprm[i]-l_mip, tofumipprm[i]+l_mip); 
       tofumipprm[i] = fit->GetParameter(1);  
       TOFUMIP[i]->GetXaxis()->SetRangeUser(tofumipprm[i]-4*(l_mip), tofumipprm[i]+6*(l_mip)); 

       TOFDMIP[i]->Fit("fit","","", tofdmipprm[i]-l_mip, tofdmipprm[i]+l_mip);  
       tofdmipprm[i] = fit->GetParameter(1);  
       TOFDMIP[i]->GetXaxis()->SetRangeUser(tofdmipprm[i]-4*(l_mip), tofdmipprm[i]+6*(l_mip)); 

   }

   for(int i=0; i<NumOfSegTOF; i++){
     TOFUMIP[i]->Draw(); 
     c1 ->Print(pdf); 
   }
   for(int i=0; i<NumOfSegTOF; i++){
     TOFDMIP[i]->Draw(); 
     c1 ->Print(pdf); 
   }

/////////////////////////////////////////////////////////////////////////////////////////////
//                                                                                         //
//    TOF ADC MIP                                                                          //
//                                                                                         //
/////////////////////////////////////////////////////////////////////////////////////////////
   nbytes = 0;
   for (Long64_t s=0; s<nentries;s++) {
     nbytes += tree->GetEntry(s);
     int u_mipflg = 0;
     int d_mipflg = 0;
     for (int i=0; i<NumOfSegTOF;i++) {
       for (int j=0; j<MaxDepth;j++) {
         if(tofut[i][j] > (tofutprm[i] - gr1) && tofut[i][j] < (tofutprm[i] + gr1) ) u_mipflg = 1;
         if(tofdt[i][j] > (tofdtprm[i] - gr1) && tofdt[i][j] < (tofdtprm[i] + gr1) ) d_mipflg = 1;
       }
       if(u_mipflg && d_mipflg){
         TOFUMIPSC[i]->Fill((tofua[i]-tofubgprm[i])/(tofumipprm[i]-tofubgprm[i]));
         TOFDMIPSC[i]->Fill((tofda[i]-tofdbgprm[i])/(tofdmipprm[i]-tofdbgprm[i]));
       }
       u_mipflg = 0;
       d_mipflg = 0;
     }
   }


   for(int i=0; i<NumOfSegTOF; i++){
     TOFUMIPSC[i]->Draw(); 
     c1 ->Print(pdf); 
   }
   for(int i=0; i<NumOfSegTOF; i++){
     TOFDMIPSC[i]->Draw(); 
     c1 ->Print(pdf); 
   }

/////////////////////////////////////////////////////////////////////////////////////////////
//                                                                                         //
//    TOF-HT ADC                                                                           //
//                                                                                         //
/////////////////////////////////////////////////////////////////////////////////////////////
   nbytes = 0;
   for (Long64_t s=0; s<nentries;s++) {
      nbytes += tree->GetEntry(s);
      if(trigflag[kBeamTofPs]>0){
//  MIP calib
        httofmip[TOF1_20] = ((tofua[0]-tofubgprm[0])/(tofumipprm[0]-tofubgprm[0])
                            +(tofda[0]-tofdbgprm[0])/(tofdmipprm[0]-tofdbgprm[0]))*0.5
                            +((tofua[19]-tofubgprm[19])/(tofumipprm[19]-tofubgprm[19])
                            + (tofda[19]-tofdbgprm[19])/(tofdmipprm[19]-tofdbgprm[19]))*0.5;
        httofmip[TOF5_22] = ((tofua[4]-tofubgprm[4])/(tofumipprm[4]-tofubgprm[4])
                            +(tofda[4]-tofdbgprm[4])/(tofdmipprm[4]-tofdbgprm[4]))*0.5
                            +((tofua[21]-tofubgprm[21])/(tofumipprm[21]-tofubgprm[21])
                            + (tofda[21]-tofdbgprm[21])/(tofdmipprm[21]-tofdbgprm[21]))*0.5;
        httofmip[TOF18  ] = ((tofua[17]-tofubgprm[17])/(tofumipprm[17]-tofubgprm[17])
                            +(tofda[17]-tofdbgprm[17])/(tofdmipprm[17]-tofdbgprm[17]))*0.5;
        httofmip[TOF4_10] = ((tofua[3]-tofubgprm[3])/(tofumipprm[3]-tofubgprm[3])
                            +(tofda[3]-tofdbgprm[3])/(tofdmipprm[3]-tofdbgprm[3]))*0.5
                            +((tofua[9]-tofubgprm[9])/(tofumipprm[9]-tofubgprm[9])
                            + (tofda[9]-tofdbgprm[9])/(tofdmipprm[9]-tofdbgprm[9]))*0.5;
        httofmip[TOF2_11] = ((tofua[1]-tofubgprm[1])/(tofumipprm[1]-tofubgprm[1])
                            +(tofda[1]-tofdbgprm[1])/(tofdmipprm[1]-tofdbgprm[1]))*0.5
                            +((tofua[10]-tofubgprm[10])/(tofumipprm[10]-tofubgprm[10])
                            + (tofda[10]-tofdbgprm[10])/(tofdmipprm[10]-tofdbgprm[10]))*0.5;
        httofmip[TOF8_24] = ((tofua[7]-tofubgprm[7])/(tofumipprm[7]-tofubgprm[7])
                            +(tofda[7]-tofdbgprm[7])/(tofdmipprm[7]-tofdbgprm[7]))*0.5
                            +((tofua[23]-tofubgprm[23])/(tofumipprm[23]-tofubgprm[23])
                            + (tofda[23]-tofdbgprm[23])/(tofdmipprm[23]-tofdbgprm[23]))*0.5;
        httofmip[TOF6_9 ] = ((tofua[5]-tofubgprm[5])/(tofumipprm[5]-tofubgprm[5])
                            +(tofda[5]-tofdbgprm[5])/(tofdmipprm[5]-tofdbgprm[5]))*0.5
                            +((tofua[8]-tofubgprm[8])/(tofumipprm[8]-tofubgprm[8])
                            + (tofda[8]-tofdbgprm[8])/(tofdmipprm[8]-tofdbgprm[8]))*0.5;
        httofmip[TOF7_23] = ((tofua[6]-tofubgprm[6])/(tofumipprm[6]-tofubgprm[6])
                            +(tofda[6]-tofdbgprm[6])/(tofdmipprm[6]-tofdbgprm[6]))*0.5
                            +((tofua[22]-tofubgprm[22])/(tofumipprm[22]-tofubgprm[22])
                            + (tofda[22]-tofdbgprm[22])/(tofdmipprm[22]-tofdbgprm[22]))*0.5;
        httofmip[TOF12  ] = ((tofua[11]-tofubgprm[11])/(tofumipprm[11]-tofubgprm[11])
                            +(tofda[11]-tofdbgprm[11])/(tofdmipprm[11]-tofdbgprm[11]))*0.5;
        httofmip[TOF19  ] = ((tofua[18]-tofubgprm[18])/(tofumipprm[18]-tofubgprm[18])
                            +(tofda[18]-tofdbgprm[18])/(tofdmipprm[18]-tofdbgprm[18]))*0.5;
        httofmip[TOF13  ] = ((tofua[12]-tofubgprm[12])/(tofumipprm[12]-tofubgprm[12])
                            +(tofda[12]-tofdbgprm[12])/(tofdmipprm[12]-tofdbgprm[12]))*0.5;
        httofmip[TOF14  ] = ((tofua[13]-tofubgprm[13])/(tofumipprm[13]-tofubgprm[13])
                            +(tofda[13]-tofdbgprm[13])/(tofdmipprm[13]-tofdbgprm[13]))*0.5;
        httofmip[TOF15  ] = ((tofua[14]-tofubgprm[14])/(tofumipprm[14]-tofubgprm[14])
                            +(tofda[14]-tofdbgprm[14])/(tofdmipprm[14]-tofdbgprm[14]))*0.5;
        httofmip[TOF16  ] = ((tofua[15]-tofubgprm[15])/(tofumipprm[15]-tofubgprm[15])
                            +(tofda[15]-tofdbgprm[15])/(tofdmipprm[15]-tofdbgprm[15]))*0.5;
        httofmip[TOF3_21] = ((tofua[2]-tofubgprm[2])/(tofumipprm[2]-tofubgprm[2])
                            +(tofda[2]-tofdbgprm[2])/(tofdmipprm[2]-tofdbgprm[2]))*0.5
                            +((tofua[20]-tofubgprm[20])/(tofumipprm[20]-tofubgprm[20])
                            + (tofda[20]-tofdbgprm[20])/(tofdmipprm[20]-tofdbgprm[20]))*0.5;
        httofmip[TOF17  ] = ((tofua[16]-tofubgprm[16])/(tofumipprm[16]-tofubgprm[16])
                            +(tofda[16]-tofdbgprm[16])/(tofdmipprm[16]-tofdbgprm[16]))*0.5;

// ADC                              
        httofadc[TOF1_20] = ((tofua[0]-tofubgprm[0]) + (tofda[0]-tofdbgprm[0]))*0.5
                          + ((tofua[19]-tofubgprm[19]) + (tofda[19]-tofdbgprm[19]))*0.5;
        httofadc[TOF5_22] = ((tofua[4]-tofubgprm[4]) + (tofda[4]-tofdbgprm[4]))*0.5
                          + ((tofua[21]-tofubgprm[21]) + (tofda[21]-tofdbgprm[21]))*0.5;
        httofadc[TOF18  ] = ((tofua[17]-tofubgprm[17]) + (tofda[17]-tofdbgprm[17]))*0.5;
        httofadc[TOF4_10] = ((tofua[3]-tofubgprm[3]) + (tofda[3]-tofdbgprm[3]))*0.5
                          + ((tofua[9]-tofubgprm[9]) + (tofda[9]-tofdbgprm[9]))*0.5;
        httofadc[TOF2_11] = ((tofua[1]-tofubgprm[1]) + (tofda[1]-tofdbgprm[1]))*0.5
                          + ((tofua[10]-tofubgprm[10]) + (tofda[10]-tofdbgprm[10]))*0.5;
        httofadc[TOF8_24] = ((tofua[7]-tofubgprm[7]) + (tofda[7]-tofdbgprm[7]))*0.5
                          + ((tofua[23]-tofubgprm[23]) + (tofda[23]-tofdbgprm[23]))*0.5;
        httofadc[TOF6_9 ] = ((tofua[5]-tofubgprm[5]) + (tofda[5]-tofdbgprm[5]))*0.5
                          + ((tofua[8]-tofubgprm[8]) + (tofda[8]-tofdbgprm[8]))*0.5;
        httofadc[TOF7_23] = ((tofua[6]-tofubgprm[6]) + (tofda[6]-tofdbgprm[6]))*0.5
                          + ((tofua[22]-tofubgprm[22]) + (tofda[22]-tofdbgprm[22]))*0.5;
        httofadc[TOF12  ] = ((tofua[11]-tofubgprm[11]) + (tofda[11]-tofdbgprm[11]))*0.5;
        httofadc[TOF19  ] = ((tofua[18]-tofubgprm[18]) + (tofda[18]-tofdbgprm[18]))*0.5;
        httofadc[TOF13  ] = ((tofua[12]-tofubgprm[12]) + (tofda[12]-tofdbgprm[12]))*0.5;
        httofadc[TOF14  ] = ((tofua[13]-tofubgprm[13]) + (tofda[13]-tofdbgprm[13]))*0.5;
        httofadc[TOF15  ] = ((tofua[14]-tofubgprm[14]) + (tofda[14]-tofdbgprm[14]))*0.5;
        httofadc[TOF16  ] = ((tofua[15]-tofubgprm[15]) + (tofda[15]-tofdbgprm[15]))*0.5;
        httofadc[TOF3_21] = ((tofua[2]-tofubgprm[2]) + (tofda[2]-tofdbgprm[2]))*0.5
                          + ((tofua[20]-tofubgprm[20]) + (tofda[20]-tofdbgprm[20]))*0.5;
        httofadc[TOF17  ] = ((tofua[16]-tofubgprm[16]) + (tofda[16]-tofdbgprm[16]))*0.5;

        for(int i=0; i<NumOfSegHtTOF; i++){
          if(tofhtt[i][0]>0){
            HtTOFA[i]->Fill(httofadc[i]);
            HtTOFMIP[i]->Fill(httofmip[i]);
            HtTOFHitPat->Fill(tofhthitpat[i]);
          }
        }
      }
    }

   c1->cd(); 
   HtTOFHitPat->Draw(); 
   c1 ->Print(pdf); 

   for(int i=0; i<NumOfSegHtTOF; i++){
     HtTOFA[i]->Draw(); 
     c1 ->Print(pdf); 
   }

   
   for(int i=0; i<NumOfSegHtTOF; i++){
     HtTOFMIP[i]->Draw(); 
     c1 ->Print(pdf); 
   }

                             
  c1->Print(pdf+"]");        
   
/////////////////////////////////////////////////////////////////////////////////////////////
//                                                                                         //
//     TOF dat file maker                                                                  //
//                                                                                         //
/////////////////////////////////////////////////////////////////////////////////////////////
  TString fout2 = (Form( "%s/hp_dat/HodoParamMaker_TOF_ADC_%05d.dat", anadir.Data() ,runnum));  
   
  std::ofstream fout_2(fout2.Data()); 
  for(int i=0; i<NumOfSegTOF; i++){
     fout_2 << tofubgprm[i]  <<  "\t" << tofumipprm[i]  <<  "\t" << tofdbgprm[i]  <<  "\t" << tofdmipprm[i] << endl;
  }     

}                            
                             
