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


void HodoParamMaker3_jun( int month, int runnum){
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

   TH1D *SACT[NumOfSegSAC]; 
   TH1D *SACT0[NumOfSegSAC]; 
   TH1D *SACT0ns[NumOfSegSAC]; 
      for (int i=0; i<NumOfSegSAC;i++) {
        SACT[i] = new TH1D(Form("SAC_%dT",i+1),Form("SAC_%dT",i+1),4000,0,4000);
        SACT0[i] = new TH1D(Form("SACT0_%dT",i+1),Form("SACT0_%dT",i+1),4000,-2000,2000);
        SACT0ns[i] = new TH1D(Form("SACT0ns_%dT",i+1),Form("SACT0ns_%dT",i+1),4000,-1800,1800);
      }
   TH1D *SACHitPat = new TH1D("SACHitPat","SACHitPat",NumOfSegSAC+1,0,NumOfSegSAC+1);

   TH1D *HtTOFT[NumOfSegHtTOF]; 
   TH1D *HtTOFT0[NumOfSegHtTOF]; 
   TH1D *HtTOFT0ns[NumOfSegHtTOF]; 
      for (int i=0; i<NumOfSegHtTOF;i++) {
        HtTOFT[i] = new TH1D(Form("HtTOF_%dT",i+1),Form("HtTOF_%dT",i+1),4000,0,4000);
        HtTOFT0[i] = new TH1D(Form("HtTOFT0_%dT",i+1),Form("HtTOFT0_%dT",i+1),4000,-2000,2000);
        HtTOFT0ns[i] = new TH1D(Form("HtTOFT0ns_%dT",i+1),Form("HtTOFT0ns_%dT",i+1),4000,-1800,1800);
      }
   TH1D *HtTOFHitPat = new TH1D("HtTOFHitPat","HtTOFHitPat",NumOfSegHtTOF+1,0,NumOfSegHtTOF+1);

   Long64_t nentries = tree->GetEntries();
   double fitprm[3];
   double sactprm[NumOfSegSAC]; 
   double httoftprm[NumOfSegHtTOF]; 

   double mhtdcns = 0.8333;

//Fit range
   double f_l  = 10;
   double f_l2 = 10;
   double f_l2_D = 20;

//Draw range
   double l = 50;

//gate range
   double gr1 = 1000; 
   double gr2 = 1500; 
   double gr3 = 500; 

//Draw range
   int T0_range_min = -100;
   int T0_range_max =  100;

//Draw range ns
   int T0ns_range_min = -83;
   int T0ns_range_max =  83;

   double l_mip = 17; 
   double l_mip0 = 50;
   double l_bg = 4; 
   double l_bg1 = 3; 
   double l_bg2 = 2; 
//Draw range
   double r_bg = 10; 

   TF1 *fit = new TF1("fit","gaus"); 

/////////////////////////////////////////////////////////////////////////////////////////////
//                                                                                         //
//    SAC TDC Mean get code                                                                //
//                                                                                         //
/////////////////////////////////////////////////////////////////////////////////////////////
   Long64_t nbytes = 0;
   for (Long64_t s=0; s<nentries;s++) {
      nbytes += tree->GetEntry(s);
      for (int i=0; i<NumOfSegSAC;i++) {
        if(sact[i]>0 && trigflag[kBeamPiPs]>0){
          for(int j=0; j<MaxDepth; j++){
            SACT[i]->Fill(sact[i][j]);
          }
          SACHitPat->Fill(sachitpat[i]);
        }
      }

      for (int i=0; i<NumOfSegHtTOF;i++) {
        if(tofhtt[i]>0 && trigflag[kBeamTofPs]>0){
          for(int j=0; j<MaxDepth; j++){
            HtTOFT[i]->Fill(tofhtt[i][j]);
          }
          HtTOFHitPat->Fill(tofhthitpat[i]);
        }
      }
   }

   
   TString pdf = Form("%s/pdf/hdprm/Hodomaker3_%05d.pdf", anadir.Data(),runnum);
   TCanvas *c1 = new TCanvas("c1","c1",800,700); 
   c1->Print(pdf+"["); 

// SAC TDC MEAN 
   for (int i=0; i<NumOfSegSAC;i++) {
       sactprm[i] = SACT[i]->GetMaximumBin();   

       sactprm[i] = SACT[i]->GetXaxis()->GetBinCenter(sactprm[i]);  

       SACT[i]->Fit("fit","i","", sactprm[i]-f_l, sactprm[i]+f_l); 
       sactprm[i] = fit->GetParameter(1);  
       SACT[i]->GetXaxis()->SetRangeUser(sactprm[i]-1*(l), sactprm[i]+2*(l)); 
   }

// HtTOF TDC MEAN 
   for (int i=0; i<NumOfSegHtTOF;i++) {
       httoftprm[i] = HtTOFT[i]->GetMaximumBin();   

       httoftprm[i] = HtTOFT[i]->GetXaxis()->GetBinCenter(httoftprm[i]);  

       HtTOFT[i]->Fit("fit","i","", httoftprm[i]-f_l, httoftprm[i]+f_l); 
       httoftprm[i] = fit->GetParameter(1);  
       HtTOFT[i]->GetXaxis()->SetRangeUser(httoftprm[i]-1*(l), httoftprm[i]+2*(l)); 
   }

   
   c1->cd(); 
   SACHitPat->Draw(); 
   c1 ->Print(pdf); 

   HtTOFHitPat->Draw(); 
   c1 ->Print(pdf); 

   c1->SetGridx();
   c1->SetGridy();

   for(int i=0; i<NumOfSegSAC; i++){
     SACT[i]->Draw(); 
     c1 ->Print(pdf); 
   }

   for(int i=0; i<NumOfSegHtTOF; i++){
     HtTOFT[i]->Draw(); 
     c1 ->Print(pdf); 
   }


/////////////////////////////////////////////////////////////////////////////////////////////
//                                                                                         //
//    SAC TDC's peak change to 0 & ch2ns code                                                //
//                                                                                         //
/////////////////////////////////////////////////////////////////////////////////////////////
   nbytes = 0;
   for (Long64_t s=0; s<nentries;s++) {
      nbytes += tree->GetEntry(s);
      for (int i=0; i<NumOfSegSAC;i++) {
        if(sact[i]>0 && trigflag[kBh2KPs]>0){
          for(int j=0; j<MaxDepth; j++){
            SACT0[i]->Fill(sact[i][j]-sactprm[i]);
            double sactns = (sact[i][j]-sactprm[i])*-mhtdcns;
            SACT0ns[i]->Fill(sactns);
          }
        }
      }
      for (int i=0; i<NumOfSegHtTOF;i++) {
        if(tofhtt[i]>0 && trigflag[kBh2KPs]>0){
          for(int j=0; j<MaxDepth; j++){
            HtTOFT0[i]->Fill(tofhtt[i][j]-httoftprm[i]);
            double httoftns = (tofhtt[i][j]-httoftprm[i])*-mhtdcns;
            HtTOFT0ns[i]->Fill(httoftns);
          }
        }
      }
   }


   for(int i=0; i<NumOfSegSAC; i++){
     SACT0[i]->GetXaxis()->SetRangeUser(T0_range_min,T0_range_max);  
     SACT0[i]->Draw(); 
     c1 ->Print(pdf); 
   }
   for(int i=0; i<NumOfSegSAC; i++){
     SACT0ns[i]->GetXaxis()->SetRangeUser(T0ns_range_min,T0ns_range_max);  
     SACT0ns[i]->Draw(); 
     c1 ->Print(pdf); 
   }
   
   for(int i=0; i<NumOfSegHtTOF; i++){
     HtTOFT0[i]->GetXaxis()->SetRangeUser(T0_range_min,T0_range_max);  
     HtTOFT0[i]->Draw(); 
     c1 ->Print(pdf); 
   }
   for(int i=0; i<NumOfSegHtTOF; i++){
     HtTOFT0ns[i]->GetXaxis()->SetRangeUser(T0ns_range_min,T0ns_range_max);  
     HtTOFT0ns[i]->Draw(); 
     c1 ->Print(pdf); 
   }
   
///////////////////////////////////////////////////////////////////////////////////////////////
////                                                                                         //
////    BH1 & BH2 ADC BG get                                                                 //
////                                                                                         //
///////////////////////////////////////////////////////////////////////////////////////////////
//   nbytes = 0;
//   for (Long64_t s=0; s<nentries;s++) {
//     nbytes += tree->GetEntry(s);
//     int u_mipflg = 0;
//     int d_mipflg = 0;
//     for (int i=0; i<NumOfSegBH1;i++) {
//       for (int j=0; j<MaxDepth;j++) {
//         if(bh1ut[i][j] > (bh1utprm[i] - gr1) && bh1ut[i][j] < (bh1utprm[i] + gr1) ) u_mipflg = 1;
//         if(bh1dt[i][j] > (bh1dtprm[i] - gr1) && bh1dt[i][j] < (bh1dtprm[i] + gr1) ) d_mipflg = 1;
//       }
//       if(u_mipflg == 0 && d_mipflg == 0 ){
//         BH1UBG[i]->Fill(bh1ua[i]);
//         BH1DBG[i]->Fill(bh1da[i]);
//       }
//       u_mipflg = 0;
//       d_mipflg = 0;
//     }
//
//     for (int i=0; i<NumOfSegBH2;i++) {
//       for (int j=0; j<MaxDepth;j++) {
//         if(bh2ut[i][j] > (bh2utprm[i] - gr2) && bh2ut[i][j] < (bh2utprm[i] + gr2) ) u_mipflg = 1;
//         if(bh2dt[i][j] > (bh2dtprm[i] - gr3) && bh2dt[i][j] < (bh2dtprm[i] + gr3) ) d_mipflg = 1;
//       }
//       if(u_mipflg == 0 && d_mipflg == 0 ){
//         BH2UBG[i]->Fill(bh2ua[i]);
//         BH2DBG[i]->Fill(bh2da[i]);
//       }
//       u_mipflg = 0;
//       d_mipflg = 0;
//     }
//   }
//
//   TF1 *fit3 = new TF1("fit3","landau"); 
//
//   for (int i=0; i<NumOfSegBH1;i++) {
//       bh1ubgprm[i] = BH1UBG[i]->GetMaximumBin();   
//       bh1dbgprm[i] = BH1DBG[i]->GetMaximumBin();   
//
//       bh1ubgprm[i] = BH1UBG[i]->GetXaxis()->GetBinCenter(bh1ubgprm[i]);  
//       bh1dbgprm[i] = BH1DBG[i]->GetXaxis()->GetBinCenter(bh1dbgprm[i]);  
//
//       BH1UBG[i]->Fit("fit","","", bh1ubgprm[i]-l_bg1, bh1ubgprm[i]+l_bg1);  
//       bh1ubgprm[i] = fit->GetParameter(1);  
//       sigma_bh1ubgprm[i] = fit->GetParameter(2);  
//       BH1UBG[i]->GetXaxis()->SetRangeUser(bh1ubgprm[i]-1*(r_bg), bh1ubgprm[i]+2*(r_bg)); 
//
//       BH1DBG[i]->Fit("fit","","", bh1dbgprm[i]-l_bg1, bh1dbgprm[i]+l_bg1); 
//       bh1dbgprm[i] = fit->GetParameter(1);  
//       sigma_bh1dbgprm[i] = fit->GetParameter(2);  
//       BH1DBG[i]->GetXaxis()->SetRangeUser(bh1dbgprm[i]-(r_bg), bh1dbgprm[i]+2*(r_bg)); 
//
//   }
//
//   for (int i=0; i<NumOfSegBH2;i++) {
//       bh2ubgprm[i] = BH2UBG[i]->GetMaximumBin();   
//       bh2dbgprm[i] = BH2DBG[i]->GetMaximumBin();   
//
//       bh2ubgprm[i] = BH2UBG[i]->GetXaxis()->GetBinCenter(bh2ubgprm[i]);  
//       bh2dbgprm[i] = BH2DBG[i]->GetXaxis()->GetBinCenter(bh2dbgprm[i]);  
//
//       BH2UBG[i]->Fit("fit","","", bh2ubgprm[i]-l_bg2, bh2ubgprm[i]+l_bg2);
//       bh2ubgprm[i] = fit->GetParameter(1);  
//       sigma_bh2ubgprm[i] = fit->GetParameter(2);  
//       BH2UBG[i]->GetXaxis()->SetRangeUser(bh2ubgprm[i]-2*(r_bg), bh2ubgprm[i]+4*(r_bg)); 
//
//       BH2DBG[i]->Fit("fit","","", bh2dbgprm[i]-l_bg2, bh2dbgprm[i]+l_bg2); 
//       bh2dbgprm[i] = fit->GetParameter(1);  
//       sigma_bh2dbgprm[i] = fit->GetParameter(2);  
//       BH2DBG[i]->GetXaxis()->SetRangeUser(bh2dbgprm[i]-2*(r_bg), bh2dbgprm[i]+4*(r_bg)); 
//
//   }
//
//   for(int i=0; i<NumOfSegBH1; i++){
//     BH1UBG[i]->Draw(); 
//     c1 ->Print(pdf); 
//   }
//   for(int i=0; i<NumOfSegBH1; i++){
//     BH1DBG[i]->Draw(); 
//     c1 ->Print(pdf); 
//   }
//   for(int i=0; i<NumOfSegBH2; i++){
//     BH2UBG[i]->Draw(); 
//     c1 ->Print(pdf); 
//   }
//   for(int i=0; i<NumOfSegBH2; i++){
//     BH2DBG[i]->Draw(); 
//     c1 ->Print(pdf); 
//   }
//
//   
//
///////////////////////////////////////////////////////////////////////////////////////////////
////                                                                                         //
////    BH1 & BH2 ADC BG get                                                                 //
////                                                                                         //
///////////////////////////////////////////////////////////////////////////////////////////////
//   nbytes = 0;
//   for (Long64_t s=0; s<nentries;s++) {
//     nbytes += tree->GetEntry(s);
//     int u_mipflg = 0;
//     int d_mipflg = 0;
//     for (int i=0; i<NumOfSegBH1;i++) {
//       for (int j=0; j<MaxDepth;j++) {
//         if(bh1ut[i][j] > (bh1utprm[i] - gr1) && bh1ut[i][j] < (bh1utprm[i] + gr1) ) u_mipflg = 1;
//         if(bh1dt[i][j] > (bh1dtprm[i] - gr1) && bh1dt[i][j] < (bh1dtprm[i] + gr1) ) d_mipflg = 1;
//       }
//       if(u_mipflg && d_mipflg){
//         if(bh1nhits < range2 && bh1nhits > range1 && bh2nhits == 1){
//           if(bh1ua[i] > bh1ubgprm[i] + 2*sigma_bh1ubgprm[i]) BH1UMIP[i]->Fill(bh1ua[i]);
//           if(bh1da[i] > bh1dbgprm[i] + 2*sigma_bh1dbgprm[i]) BH1DMIP[i]->Fill(bh1da[i]);
//         }
//       }
//       u_mipflg = 0;
//       d_mipflg = 0;
//     }
//
//     for (int i=0; i<NumOfSegBH2;i++) {
//       for (int j=0; j<MaxDepth;j++) {
//         if(bh2ut[i][j] > (bh2utprm[i] - gr2) && bh2ut[i][j] < (bh2utprm[i] + gr2) ) u_mipflg = 1;
//         if(bh2dt[i][j] > (bh2dtprm[i] - gr3) && bh2dt[i][j] < (bh2dtprm[i] + gr3) ) d_mipflg = 1;
//       }
//       if(u_mipflg && d_mipflg){
//         if(bh1nhits < range2 && bh1nhits > range1 && bh2nhits == 1){
//           if(bh2ua[i] > bh2ubgprm[i] + 7*sigma_bh2ubgprm[i]) BH2UMIP[i]->Fill(bh2ua[i]);
//           if(bh2da[i] > bh2dbgprm[i] + 7*sigma_bh2dbgprm[i]) BH2DMIP[i]->Fill(bh2da[i]);
//         }
//       }
//       u_mipflg = 0;
//       d_mipflg = 0;
//     }
//   }
//
//
//   for (int i=0; i<NumOfSegBH1;i++) {
//       bh1umipprm[i] = BH1UMIP[i]->GetMaximumBin();   
//       bh1dmipprm[i] = BH1DMIP[i]->GetMaximumBin();   
//
//       bh1umipprm[i] = BH1UMIP[i]->GetXaxis()->GetBinCenter(bh1umipprm[i]);  
//       bh1dmipprm[i] = BH1DMIP[i]->GetXaxis()->GetBinCenter(bh1dmipprm[i]);  
//
//       BH1UMIP[i]->Fit("fit","","", bh1umipprm[i]-l_mip, bh1umipprm[i]+l_mip); 
//       bh1umipprm[i] = fit->GetParameter(1);  
//       BH1UMIP[i]->GetXaxis()->SetRangeUser(bh1umipprm[i]-4*(l_mip), bh1umipprm[i]+6*(l_mip)); 
//
//       BH1DMIP[i]->Fit("fit","","", bh1dmipprm[i]-l_mip, bh1dmipprm[i]+l_mip);  
//       bh1dmipprm[i] = fit->GetParameter(1);  
//       BH1DMIP[i]->GetXaxis()->SetRangeUser(bh1dmipprm[i]-4*(l_mip), bh1dmipprm[i]+6*(l_mip)); 
//
//   }
//
//   for (int i=0; i<NumOfSegBH2;i++) {
//     if(i == 0 ){
//       bh2umipprm[i] = BH2UMIP[i]->GetMaximumBin();   
//       bh2dmipprm[i] = BH2DMIP[i]->GetMaximumBin();   
//
//       bh2umipprm[i] = BH2UMIP[i]->GetXaxis()->GetBinCenter(bh2umipprm[i]);  
//       bh2dmipprm[i] = BH2DMIP[i]->GetXaxis()->GetBinCenter(bh2dmipprm[i]);  
//
//       BH2UMIP[i]->Fit("fit","","", bh2umipprm[i]-l_mip0, bh2umipprm[i]+l_mip0);
//       bh2umipprm[i] = fit->GetParameter(1);  
//       BH2UMIP[i]->GetXaxis()->SetRangeUser(bh2umipprm[i]-4*(l_mip0), bh2umipprm[i]+6*(l_mip0)); 
//
//       BH2DMIP[i]->Fit("fit","","", bh2dmipprm[i]-l_mip0, bh2dmipprm[i]+l_mip0);
//       bh2dmipprm[i] = fit->GetParameter(1);  
//       BH2DMIP[i]->GetXaxis()->SetRangeUser(bh2dmipprm[i]-4*(l_mip0), bh2dmipprm[i]+6*(l_mip0)); 
//     }else{
//       bh2umipprm[i] = BH2UMIP[i]->GetMaximumBin();   
//       bh2dmipprm[i] = BH2DMIP[i]->GetMaximumBin();   
//
//       bh2umipprm[i] = BH2UMIP[i]->GetXaxis()->GetBinCenter(bh2umipprm[i]);  
//       bh2dmipprm[i] = BH2DMIP[i]->GetXaxis()->GetBinCenter(bh2dmipprm[i]);  
//
//       BH2UMIP[i]->Fit("fit","","", bh2umipprm[i]-l_mip, bh2umipprm[i]+l_mip);
//       bh2umipprm[i] = fit->GetParameter(1);  
//       BH2UMIP[i]->GetXaxis()->SetRangeUser(bh2umipprm[i]-4*(l_mip), bh2umipprm[i]+6*(l_mip)); 
//
//       BH2DMIP[i]->Fit("fit","","", bh2dmipprm[i]-l_mip, bh2dmipprm[i]+l_mip);
//       bh2dmipprm[i] = fit->GetParameter(1);  
//       BH2DMIP[i]->GetXaxis()->SetRangeUser(bh2dmipprm[i]-4*(l_mip), bh2dmipprm[i]+6*(l_mip)); 
//     }
//   }
//
//   for(int i=0; i<NumOfSegBH1; i++){
//     BH1UMIP[i]->Draw(); 
//     c1 ->Print(pdf); 
//   }
//   for(int i=0; i<NumOfSegBH1; i++){
//     BH1DMIP[i]->Draw(); 
//     c1 ->Print(pdf); 
//   }
//   for(int i=0; i<NumOfSegBH2; i++){
//     BH2UMIP[i]->Draw(); 
//     c1 ->Print(pdf); 
//   }
//   for(int i=0; i<NumOfSegBH2; i++){
//     BH2DMIP[i]->Draw(); 
//     c1 ->Print(pdf); 
//   }
//   
///////////////////////////////////////////////////////////////////////////////////////////////
////                                                                                         //
////    BH1 & BH2 ADC 1mip -> 1                                                              //
////                                                                                         //
///////////////////////////////////////////////////////////////////////////////////////////////
//   nbytes = 0;
//   for (Long64_t s=0; s<nentries;s++) {
//      nbytes += tree->GetEntry(s);
//     if(bh1nhits < range2 && bh1nhits > range1 && bh2nhits == 1){
//       int u_mipflg = 0;
//       int d_mipflg = 0;
//       for (int i=0; i<NumOfSegBH1;i++) {
//         for (int j=0; j<MaxDepth;j++) {
//           if(bh1ut[i][j] > (bh1utprm[i] - gr1) && bh1ut[i][j] < (bh1utprm[i] + gr1) ) u_mipflg = 1;
//           if(bh1dt[i][j] > (bh1dtprm[i] - gr1) && bh1dt[i][j] < (bh1dtprm[i] + gr1) ) d_mipflg = 1;
//         }
//         if(u_mipflg ==1 && d_mipflg ==1){
//           BH1UdE[i]->Fill((bh1ua[i]-bh1ubgprm[i])/(bh1umipprm[i]-bh1ubgprm[i]));
//           BH1DdE[i]->Fill((bh1da[i]-bh1dbgprm[i])/(bh1dmipprm[i]-bh1dbgprm[i]));
//         }
//         u_mipflg = 0;
//         d_mipflg = 0;
//       }
//
//       for (int i=0; i<NumOfSegBH2;i++) {
//         for (int j=0; j<MaxDepth;j++) {
//           if(bh2ut[i][j] > (bh2utprm[i] - gr2) && bh2ut[i][j] < (bh2utprm[i] + gr2) ) u_mipflg = 1;
//           if(bh2dt[i][j] > (bh2dtprm[i] - gr3) && bh2dt[i][j] < (bh2dtprm[i] + gr3) ) d_mipflg = 1;
//         }
//         if(u_mipflg ==1  && d_mipflg ==1){
//           BH2UdE[i]->Fill((bh2ua[i]-bh2ubgprm[i])/(bh2umipprm[i]-bh2ubgprm[i]));
//           BH2DdE[i]->Fill((bh2da[i]-bh2dbgprm[i])/(bh2dmipprm[i]-bh2dbgprm[i]));
//         }
//         u_mipflg = 0;
//         d_mipflg = 0;
//       }
//     }
//   }
//
//   for(int i=0; i<NumOfSegBH1; i++){
//     BH1UdE[i]->Draw(); 
//     c1 ->Print(pdf); 
//   }
//   for(int i=0; i<NumOfSegBH1; i++){
//     BH1DdE[i]->Draw(); 
//     c1 ->Print(pdf); 
//   }
//   for(int i=0; i<NumOfSegBH2; i++){
//     BH2UdE[i]->Draw(); 
//     c1 ->Print(pdf); 
//   }
//   for(int i=0; i<NumOfSegBH2; i++){
//     BH2DdE[i]->Draw(); 
//     c1 ->Print(pdf); 
//   }
                             
  c1->Print(pdf+"]");        
   
/////////////////////////////////////////////////////////////////////////////////////////////
//                                                                                         //
//    BH1 & BH2 dat file maker                                                             //
//                                                                                         //
/////////////////////////////////////////////////////////////////////////////////////////////
  TString fout1 = (Form( "%s/hp_dat/HodoParamMaker3_SAC_TDC_%05d.dat", anadir.Data() ,runnum));  
   
  std::ofstream fout_1(fout1.Data()); 
  for(int i=0; i<NumOfSegSAC; i++){
     fout_1 << sactprm[i]  << endl;
  }     

  TString fout2 = (Form( "%s/hp_dat/HodoParamMaker3_HtTOF_TDC_%05d.dat", anadir.Data() ,runnum));  
   
  std::ofstream fout_2(fout2.Data()); 
  for(int i=0; i<NumOfSegHtTOF; i++){
     fout_2 << sactprm[i]  << endl;
  }     
}                            
                             
