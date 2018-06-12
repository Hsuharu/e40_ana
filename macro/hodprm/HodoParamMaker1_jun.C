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


void HodoParamMaker1_jun( int month, int runnum){
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
   TFile *f = new TFile(Form("%s/analyzer_%s/rootfile/run%05d_hodo.root", anadir.Data(),Month[month], runnum),"READ");
   if (!f) {
      f = new TFile(Form("%s/rootfile/run%05d_hodo.root", anadir.Data() , runnum));
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
   int xbin = 100;

   int MaxDepth = 16;

   int NumOfAllHist = 100;

//   TH1D *hist[NumOfAllHist]; 
//   for(int i = 0; i<NumOfAllHist; i++){
//     hist[i] = new TH1D(Form("hist%d",i+1),Form("hist%d",i+1), , ,,  );
//   }

   TH1D *BH1UT[NumOfSegBH1]; 
   TH1D *BH1DT[NumOfSegBH1]; 
   TH1D *BH1UT0[NumOfSegBH1]; 
   TH1D *BH1DT0[NumOfSegBH1]; 
   TH1D *BH1UTns[NumOfSegBH1]; 
   TH1D *BH1DTns[NumOfSegBH1]; 
   TH1D *BH1MT[NumOfSegBH1]; 
   TH1D *BH1UMIP[NumOfSegBH1]; 
   TH1D *BH1DMIP[NumOfSegBH1]; 
   TH1D *BH1UBG[NumOfSegBH1]; 
   TH1D *BH1DBG[NumOfSegBH1]; 
   TH1D *BH1UdE[NumOfSegBH1]; 
   TH1D *BH1DdE[NumOfSegBH1]; 
      for (int i=0; i<NumOfSegBH1;i++) {
        BH1UT[i] = new TH1D(Form("BH1_%dUT",i+1),Form("BH1_%dUT",i+1),2000,200000,400000);
        BH1DT[i] = new TH1D(Form("BH1_%dDT",i+1),Form("BH1_%dDT",i+1),2000,200000,400000);
        BH1UT0[i] = new TH1D(Form("BH1_%dUT0",i+1),Form("BH1_%dUT0",i+1),2000,-100000,100000);
        BH1DT0[i] = new TH1D(Form("BH1_%dDT0",i+1),Form("BH1_%dDT0",i+1),2000,-100000,100000);
        BH1UTns[i] = new TH1D(Form("BH1UTns%d",i+1),Form("BH1UTns%d",i+1),162,-3,3);
        BH1DTns[i] = new TH1D(Form("BH1DTns%d",i+1),Form("BH1DTns%d",i+1),162,-3,3);
        BH1MT[i] = new TH1D(Form("BH1MT%d",i+1),Form("BH1MT%d",i+1),162,-3,3);
        BH1UMIP[i] = new TH1D(Form("BH1UMIP%d",i+1),Form("BH1UMIP%d",i+1),1200,0,1200);
        BH1DMIP[i] = new TH1D(Form("BH1DMIP%d",i+1),Form("BH1DMIP%d",i+1),1200,0,1200);
        BH1UBG[i] = new TH1D(Form("BH1UBG%d",i+1),Form("BH1UBG%d",i+1),600,0,600);
        BH1DBG[i] = new TH1D(Form("BH1DBG%d",i+1),Form("BH1DBG%d",i+1),600,0,600);
        BH1UdE[i] = new TH1D(Form("BH1UdE%d",i+1),Form("BH1UdE%d",i+1),xbin,0,3);
        BH1DdE[i] = new TH1D(Form("BH1DdE%d",i+1),Form("BH1DdE%d",i+1),xbin,0,3);
      }
   TH1D *BH1HitPat = new TH1D("BH1HitPat","BH1HitPat",12,0,12);

   TH1D *BH2UT[NumOfSegBH2]; 
   TH1D *BH2DT[NumOfSegBH2]; 
   TH1D *BH2UT0[NumOfSegBH2]; 
   TH1D *BH2DT0[NumOfSegBH2]; 
   TH1D *BH2UTns[NumOfSegBH2]; 
   TH1D *BH2DTns[NumOfSegBH2]; 
   TH1D *BH2MT[NumOfSegBH2]; 
   TH1D *BH2UMIP[NumOfSegBH2]; 
   TH1D *BH2DMIP[NumOfSegBH2]; 
   TH1D *BH2UBG[NumOfSegBH2]; 
   TH1D *BH2DBG[NumOfSegBH2]; 
   TH1D *BH2UdE[NumOfSegBH2]; 
   TH1D *BH2DdE[NumOfSegBH2]; 
      for (int i=0; i<NumOfSegBH2;i++) {
        BH2UT[i] = new TH1D(Form("BH2_%dUT",i+1),Form("BH2_%dUT",i+1),2000,200000,400000);
        BH2DT[i] = new TH1D(Form("BH2_%dDT",i+1),Form("BH2_%dDT",i+1),5000,200000,400000);
        BH2UT0[i] = new TH1D(Form("BH2_%dUT0",i+1),Form("BH2_%dUT0",i+1),2000,-100000,100000);
        BH2DT0[i] = new TH1D(Form("BH2_%dDT0",i+1),Form("BH2_%dDT0",i+1),1000,-10000,10000);
        BH2UTns[i] = new TH1D(Form("BH2UTns%d",i+1),Form("BH2UTns%d",i+1),162,-3,3);
        BH2DTns[i] = new TH1D(Form("BH2DTns%d",i+1),Form("BH2DTns%d",i+1),162,-3,3);
        BH2MT[i] = new TH1D(Form("BH2MT%d",i+1),Form("BH2MT%d",i+1),162,-3,3);
        BH2UMIP[i] = new TH1D(Form("BH2UMIP%d",i+1),Form("BH2UMIP%d",i+1),1200,0,1200);
        BH2DMIP[i] = new TH1D(Form("BH2DMIP%d",i+1),Form("BH2DMIP%d",i+1),1200,0,1200);
        BH2UBG[i] = new TH1D(Form("BH2UBG%d",i+1),Form("BH2UBG%d",i+1),600,0,600);
        BH2DBG[i] = new TH1D(Form("BH2DBG%d",i+1),Form("BH2DBG%d",i+1),600,0,600);
        BH2UdE[i] = new TH1D(Form("BH2UdE%d",i+1),Form("BH2UdE%d",i+1),xbin,0,3);
        BH2DdE[i] = new TH1D(Form("BH2DdE%d",i+1),Form("BH2DdE%d",i+1),xbin,0,3);
      }
   TH1D *BH2HitPat = new TH1D("BH2HitPat","BH2HitPat",9,0,9);

   Long64_t nentries = tree->GetEntries();
   double fitprm[3];
   double bh1utprm[NumOfSegBH1]; 
   double bh1dtprm[NumOfSegBH1]; 
   double bh1umipprm[NumOfSegBH1]; 
   double bh1dmipprm[NumOfSegBH1]; 
   double bh1ubgprm[NumOfSegBH1]; 
   double bh1dbgprm[NumOfSegBH1]; 

   double bh2utprm[NumOfSegBH2]; 
   double bh2dtprm[NumOfSegBH2]; 
   double bh2umipprm[NumOfSegBH2]; 
   double bh2dmipprm[NumOfSegBH2]; 
   double bh2ubgprm[NumOfSegBH2]; 
   double bh2dbgprm[NumOfSegBH2]; 

//Fit range
   double f_l  = 300; //4462 & 4464
   double f_l2 = 300; //4462 & 4464
   double f_l2_D = 200; //4462 & 4464

//Draw range
   double l = 2000; //4462 & 4464
   double l2 = 1500; //4462 & 4464

//gate range
   double gr1 = 1000; //4462 & 4464
   double gr2 = 1500; //4462 & 4464
   double gr3 = 500; //4462 & 4464

//Draw range
   int T0_range_min = -3000;
   int T0_range_max = 3000;

   double btof1[NumOfSegBH1]; 
   double btof2[NumOfSegBH2]; 

   double l_mip = 40; 
   double l_bg = 4; 
   double l_bg1 = 4; 
   double l_bg2 = 2; 
//Draw range
   double r_bg = 10; 

   TF1 *fit = new TF1("fit","gaus"); 
   

/////////////////////////////////////////////////////////////////////////////////////////////
//                                                                                         //
//    BH1 & BH2 TDC Mean get code                                                          //
//                                                                                         //
/////////////////////////////////////////////////////////////////////////////////////////////
   Long64_t nbytes = 0;
   for (Long64_t s=0; s<nentries;s++) {
      nbytes += tree->GetEntry(s);
      for (int i=0; i<NumOfSegBH1;i++) {
        if(bh1ut[i]>0 && bh1dt[i]>0  && bh1nhits < range2 && bh1nhits > range1 && bh2nhits == 1){
          for(int j=0; j<MaxDepth; j++){
            BH1UT[i]->Fill(bh1ut[i][j]);
            BH1DT[i]->Fill(bh1dt[i][j]);
          }
        }
        if(bh1nhits < range2 && bh1nhits > range1 && bh2nhits == 1){
          BH1HitPat->Fill(bh1hitpat[i]);
        }
      }

      for (int i=0; i<NumOfSegBH2;i++) {
        if(bh1nhits < range2 && bh1nhits > range1 && bh2ut[i]>0 && bh2dt[i]>0 && bh2nhits == 1){
          for(int j=0; j<MaxDepth; j++){
            BH2UT[i]->Fill(bh2ut[i][j]);
            BH2DT[i]->Fill(bh2dt[i][j]);
          }
        }
        if(bh1nhits < range2 && bh1nhits > range1 && bh2nhits == 1){
          BH2HitPat->Fill(bh2hitpat[i]);
        }
      }
   }

   
   TString pdf = Form("%s/pdf/hdprm/Hodomaker1_%05d.pdf", anadir.Data(),runnum);
   TCanvas *c1 = new TCanvas("c1","c1",800,700); 
   c1->Print(pdf+"["); 

// BH1 UandD TDC MEAN 
   for (int i=0; i<NumOfSegBH1;i++) {
       bh1utprm[i] = BH1UT[i]->GetMaximumBin();   
       bh1dtprm[i] = BH1DT[i]->GetMaximumBin();   

       bh1utprm[i] = BH1UT[i]->GetXaxis()->GetBinCenter(bh1utprm[i]);  
       bh1dtprm[i] = BH1DT[i]->GetXaxis()->GetBinCenter(bh1dtprm[i]);  

       BH1UT[i]->Fit("fit","i","", bh1utprm[i]-f_l, bh1utprm[i]+f_l); 
       bh1utprm[i] = fit->GetParameter(1);  
       BH1UT[i]->GetXaxis()->SetRangeUser(bh1utprm[i]-1*(l), bh1utprm[i]+2*(l)); 

       BH1DT[i]->Fit("fit","i","", bh1dtprm[i]-f_l, bh1dtprm[i]+f_l); 
       bh1dtprm[i] = fit->GetParameter(1);  
       BH1DT[i]->GetXaxis()->SetRangeUser(bh1dtprm[i]-1*(l), bh1dtprm[i]+2*(l));  

   }

// BH2 UandD TDC MEAN 
   for (int i=0; i<NumOfSegBH2;i++) {
       bh2utprm[i] = BH2UT[i]->GetMaximumBin();   
       bh2dtprm[i] = BH2DT[i]->GetMaximumBin();   

       bh2utprm[i] = BH2UT[i]->GetXaxis()->GetBinCenter(bh2utprm[i]);  
       bh2dtprm[i] = BH2DT[i]->GetXaxis()->GetBinCenter(bh2dtprm[i]);  

       BH2UT[i]->Fit("fit","i","", bh2utprm[i]-f_l2, bh2utprm[i]+f_l2);  //4462 & 4464
       bh2utprm[i] = fit->GetParameter(1);  
       BH2UT[i]->GetXaxis()->SetRangeUser(bh2utprm[i]-1*l2, bh2utprm[i]+2*(l2));  //4462 & 4464 

       BH2DT[i]->Fit("fit","i","", bh2dtprm[i]-f_l2_D, bh2dtprm[i]+f_l2_D); //4462 & 4464 
       bh2dtprm[i] = fit->GetParameter(1);  
       BH2DT[i]->GetXaxis()->SetRangeUser(bh2dtprm[i]-1*(l2), bh2dtprm[i]+2*(l2));  

   }
   
   c1->cd(); 
   BH1HitPat->Draw(); 
   c1 ->Print(pdf); 

   c1->cd(); 
   BH2HitPat->Draw(); 
   c1 ->Print(pdf); 
   
   c1->cd(); 
   c1->SetGridx();
   c1->SetGridy();

   for(int i=0; i<NumOfSegBH1; i++){
     BH1UT[i]->Draw(); 
     c1 ->Print(pdf); 
   }
   for(int i=0; i<NumOfSegBH1; i++){
     BH1DT[i]->Draw(); 
     c1 ->Print(pdf); 
   }
   for(int i=0; i<NumOfSegBH2; i++){
     BH2UT[i]->Draw(); 
     c1 ->Print(pdf); 
   }
   for(int i=0; i<NumOfSegBH2; i++){
     BH2DT[i]->Draw(); 
     c1 ->Print(pdf); 
   }
   
   


/////////////////////////////////////////////////////////////////////////////////////////////
//                                                                                         //
//    BH1 & BH2 TDC's peak change to 0 code                                                //
//                                                                                         //
/////////////////////////////////////////////////////////////////////////////////////////////
   nbytes = 0;
   for (Long64_t s=0; s<nentries;s++) {
      nbytes += tree->GetEntry(s);
      for (int i=0; i<NumOfSegBH1;i++) {
        if(bh1ut[i]>0 && bh1dt[i]>0 && bh1nhits < range2 && bh1nhits > range1 && bh2nhits == 1){
          for(int j=0; j<MaxDepth; j++){
            BH1UT0[i]->Fill(bh1ut[i][j]-bh1utprm[i]);
            BH1DT0[i]->Fill(bh1dt[i][j]-bh1dtprm[i]);
          }
        }
      }

      for (int i=0; i<NumOfSegBH2;i++) {
        if(bh1nhits < range2 && bh1nhits > range1 && bh2ut[i]>0 && bh2dt[i]>0 && bh2nhits ==1 ){
          for(int j=0; j<MaxDepth; j++){
            BH2UT0[i]->Fill(bh2ut[i][j]-bh2utprm[i]);
            BH2DT0[i]->Fill(bh2dt[i][j]-bh2dtprm[i]);
          }
        }
      }
   }


   for(int i=0; i<NumOfSegBH1; i++){
     BH1UT0[i]->GetXaxis()->SetRangeUser(T0_range_min,T0_range_max);  
     BH1UT0[i]->Draw(); 
     c1 ->Print(pdf); 
   }
   for(int i=0; i<NumOfSegBH1; i++){
     BH1DT0[i]->GetXaxis()->SetRangeUser(T0_range_min,T0_range_max);  
     BH1DT0[i]->Draw(); 
     c1 ->Print(pdf); 
   }
   for(int i=0; i<NumOfSegBH2; i++){
     BH2UT0[i]->GetXaxis()->SetRangeUser(T0_range_min,T0_range_max);  
     BH2UT0[i]->Draw(); 
     c1 ->Print(pdf); 
   }
   for(int i=0; i<NumOfSegBH2; i++){
     BH2DT0[i]->GetXaxis()->SetRangeUser(T0_range_min,T0_range_max);  
     BH2DT0[i]->Draw(); 
     c1 ->Print(pdf); 
   }

/////////////////////////////////////////////////////////////////////////////////////////////
//                                                                                         //
//    BH1 & BH2 ADC BG get                                                                 //
//                                                                                         //
/////////////////////////////////////////////////////////////////////////////////////////////
   nbytes = 0;
   for (Long64_t s=0; s<nentries;s++) {
     nbytes += tree->GetEntry(s);
     int u_mipflg = 0;
     int d_mipflg = 0;
     for (int i=0; i<NumOfSegBH1;i++) {
       for (int j=0; j<MaxDepth;j++) {
         if(bh1ut[i][j] > (bh1utprm[i] - gr1) && bh1ut[i][j] < (bh1utprm[i] + gr1) ) u_mipflg = 1;
         if(bh1dt[i][j] > (bh1dtprm[i] - gr1) && bh1dt[i][j] < (bh1dtprm[i] + gr1) ) d_mipflg = 1;
       }
       if(u_mipflg && d_mipflg){
         if(bh1nhits < range2 && bh1nhits > range1 && bh2nhits == 1){
           BH1UMIP[i]->Fill(bh1ua[i]);
           BH1DMIP[i]->Fill(bh1da[i]);
         }
       }else if(u_mipflg == 0 && d_mipflg == 0 ){
         BH1UBG[i]->Fill(bh1ua[i]);
         BH1DBG[i]->Fill(bh1da[i]);
       }
       u_mipflg = 0;
       d_mipflg = 0;
     }

     for (int i=0; i<NumOfSegBH2;i++) {
       for (int j=0; j<MaxDepth;j++) {
         if(bh2ut[i][j] > (bh2utprm[i] - gr2) && bh2ut[i][j] < (bh2utprm[i] + gr2) ) u_mipflg = 1;
         if(bh2dt[i][j] > (bh2dtprm[i] - gr3) && bh2dt[i][j] < (bh2dtprm[i] + gr3) ) d_mipflg = 1;
       }
       if(u_mipflg && d_mipflg){
         if(bh1nhits < range2 && bh1nhits > range1 && bh2nhits == 1){
           BH2UMIP[i]->Fill(bh2ua[i]);
           BH2DMIP[i]->Fill(bh2da[i]);
         }
       }else if(u_mipflg == 0 && d_mipflg == 0 ){
         BH2UBG[i]->Fill(bh2ua[i]);
         BH2DBG[i]->Fill(bh2da[i]);
       }
       u_mipflg = 0;
       d_mipflg = 0;
     }
   }

   TF1 *fit3 = new TF1("fit3","landau"); 

   for (int i=0; i<NumOfSegBH1;i++) {
       bh1umipprm[i] = BH1UMIP[i]->GetMaximumBin();   
       bh1dmipprm[i] = BH1DMIP[i]->GetMaximumBin();   

       bh1umipprm[i] = BH1UMIP[i]->GetXaxis()->GetBinCenter(bh1umipprm[i]);  
       bh1dmipprm[i] = BH1DMIP[i]->GetXaxis()->GetBinCenter(bh1dmipprm[i]);  

       BH1UMIP[i]->Fit("fit","","", bh1umipprm[i]-l_mip, bh1umipprm[i]+l_mip); 
       bh1umipprm[i] = fit->GetParameter(1);  
       BH1UMIP[i]->GetXaxis()->SetRangeUser(bh1umipprm[i]-2*(l_mip), bh1umipprm[i]+4*(l_mip)); 

       BH1DMIP[i]->Fit("fit","","", bh1dmipprm[i]-l_mip, bh1dmipprm[i]+l_mip);  
       bh1dmipprm[i] = fit->GetParameter(1);  
       BH1DMIP[i]->GetXaxis()->SetRangeUser(bh1dmipprm[i]-2*(l_mip), bh1dmipprm[i]+4*(l_mip)); 

   }

   for (int i=0; i<NumOfSegBH2;i++) {
       bh2umipprm[i] = BH2UMIP[i]->GetMaximumBin();   
       bh2dmipprm[i] = BH2DMIP[i]->GetMaximumBin();   

       bh2umipprm[i] = BH2UMIP[i]->GetXaxis()->GetBinCenter(bh2umipprm[i]);  
       bh2dmipprm[i] = BH2DMIP[i]->GetXaxis()->GetBinCenter(bh2dmipprm[i]);  

       BH2UMIP[i]->Fit("fit","","", bh2umipprm[i]-l_mip, bh2umipprm[i]+l_mip);
       bh2umipprm[i] = fit->GetParameter(1);  
       BH2UMIP[i]->GetXaxis()->SetRangeUser(bh2umipprm[i]-2*(l_mip), bh2umipprm[i]+4*(l_mip)); 

       BH2DMIP[i]->Fit("fit","","", bh2dmipprm[i]-l_mip, bh2dmipprm[i]+l_mip);
       bh2dmipprm[i] = fit->GetParameter(1);  
       BH2DMIP[i]->GetXaxis()->SetRangeUser(bh2dmipprm[i]-2*(l_mip), bh2dmipprm[i]+4*(l_mip)); 

   }


   for (int i=0; i<NumOfSegBH1;i++) {
       bh1ubgprm[i] = BH1UBG[i]->GetMaximumBin();   
       bh1dbgprm[i] = BH1DBG[i]->GetMaximumBin();   

       bh1ubgprm[i] = BH1UBG[i]->GetXaxis()->GetBinCenter(bh1ubgprm[i]);  
       bh1dbgprm[i] = BH1DBG[i]->GetXaxis()->GetBinCenter(bh1dbgprm[i]);  

       BH1UBG[i]->Fit("fit","","", bh1ubgprm[i]-l_bg, bh1ubgprm[i]+l_bg);  
       bh1ubgprm[i] = fit->GetParameter(1);  
       BH1UBG[i]->GetXaxis()->SetRangeUser(bh1ubgprm[i]-1*(r_bg), bh1ubgprm[i]+2*(r_bg)); 

       BH1DBG[i]->Fit("fit","","", bh1dbgprm[i]-l_bg1, bh1dbgprm[i]+l_bg1); 
       bh1dbgprm[i] = fit->GetParameter(1);  
       BH1DBG[i]->GetXaxis()->SetRangeUser(bh1dbgprm[i]-(r_bg), bh1dbgprm[i]+2*(r_bg)); 

   }

   for (int i=0; i<NumOfSegBH2;i++) {
       bh2ubgprm[i] = BH2UBG[i]->GetMaximumBin();   
       bh2dbgprm[i] = BH2DBG[i]->GetMaximumBin();   

       bh2ubgprm[i] = BH2UBG[i]->GetXaxis()->GetBinCenter(bh2ubgprm[i]);  
       bh2dbgprm[i] = BH2DBG[i]->GetXaxis()->GetBinCenter(bh2dbgprm[i]);  

       BH2UBG[i]->Fit("fit","","", bh2ubgprm[i]-l_bg2, bh2ubgprm[i]+l_bg2);
       bh2ubgprm[i] = fit->GetParameter(1);  
       BH2UBG[i]->GetXaxis()->SetRangeUser(bh2ubgprm[i]-2*(r_bg), bh2ubgprm[i]+4*(r_bg)); 

       BH2DBG[i]->Fit("fit","","", bh2dbgprm[i]-l_bg2, bh2dbgprm[i]+l_bg2); 
       bh2dbgprm[i] = fit->GetParameter(1);  
       BH2DBG[i]->GetXaxis()->SetRangeUser(bh2dbgprm[i]-2*(r_bg), bh2dbgprm[i]+4*(r_bg)); 

   }

   for(int i=0; i<NumOfSegBH1; i++){
     BH1UMIP[i]->Draw(); 
     c1 ->Print(pdf); 
   }
   for(int i=0; i<NumOfSegBH1; i++){
     BH1DMIP[i]->Draw(); 
     c1 ->Print(pdf); 
   }
   for(int i=0; i<NumOfSegBH2; i++){
     BH2UMIP[i]->Draw(); 
     c1 ->Print(pdf); 
   }
   for(int i=0; i<NumOfSegBH2; i++){
     BH2DMIP[i]->Draw(); 
     c1 ->Print(pdf); 
   }

   for(int i=0; i<NumOfSegBH1; i++){
     BH1UBG[i]->Draw(); 
     c1 ->Print(pdf); 
   }
   for(int i=0; i<NumOfSegBH1; i++){
     BH1DBG[i]->Draw(); 
     c1 ->Print(pdf); 
   }
   for(int i=0; i<NumOfSegBH2; i++){
     BH2UBG[i]->Draw(); 
     c1 ->Print(pdf); 
   }
   for(int i=0; i<NumOfSegBH2; i++){
     BH2DBG[i]->Draw(); 
     c1 ->Print(pdf); 
   }

   
/////////////////////////////////////////////////////////////////////////////////////////////
//                                                                                         //
//    BH1 & BH2 ADC 1mip -> 1                                                              //
//                                                                                         //
/////////////////////////////////////////////////////////////////////////////////////////////
   nbytes = 0;
   for (Long64_t s=0; s<nentries;s++) {
      nbytes += tree->GetEntry(s);
     if(bh1nhits < range2 && bh1nhits > range1 && bh2nhits == 1){
       int u_mipflg = 0;
       int d_mipflg = 0;
       for (int i=0; i<NumOfSegBH1;i++) {
         for (int j=0; j<MaxDepth;j++) {
           if(bh1ut[i][j] > (bh1utprm[i] - gr1) && bh1ut[i][j] < (bh1utprm[i] + gr1) ) u_mipflg = 1;
           if(bh1dt[i][j] > (bh1dtprm[i] - gr1) && bh1dt[i][j] < (bh1dtprm[i] + gr1) ) d_mipflg = 1;
         }
         if(u_mipflg ==1 && d_mipflg ==1){
           BH1UdE[i]->Fill((bh1ua[i]-bh1ubgprm[i])/(bh1umipprm[i]-bh1ubgprm[i]));
           BH1DdE[i]->Fill((bh1da[i]-bh1dbgprm[i])/(bh1dmipprm[i]-bh1dbgprm[i]));
         }
         u_mipflg = 0;
         d_mipflg = 0;
       }

       for (int i=0; i<NumOfSegBH2;i++) {
         for (int j=0; j<MaxDepth;j++) {
           if(bh2ut[i][j] > (bh2utprm[i] - gr2) && bh2ut[i][j] < (bh2utprm[i] + gr2) ) u_mipflg = 1;
           if(bh2dt[i][j] > (bh2dtprm[i] - gr3) && bh2dt[i][j] < (bh2dtprm[i] + gr3) ) d_mipflg = 1;
         }
         if(u_mipflg ==1  && d_mipflg ==1){
           BH2UdE[i]->Fill((bh2ua[i]-bh2ubgprm[i])/(bh2umipprm[i]-bh2ubgprm[i]));
           BH2DdE[i]->Fill((bh2da[i]-bh2dbgprm[i])/(bh2dmipprm[i]-bh2dbgprm[i]));
         }
         u_mipflg = 0;
         d_mipflg = 0;
       }
     }
   }

   for(int i=0; i<NumOfSegBH1; i++){
     BH1UdE[i]->Draw(); 
     c1 ->Print(pdf); 
   }
   for(int i=0; i<NumOfSegBH1; i++){
     BH1DdE[i]->Draw(); 
     c1 ->Print(pdf); 
   }
   for(int i=0; i<NumOfSegBH2; i++){
     BH2UdE[i]->Draw(); 
     c1 ->Print(pdf); 
   }
   for(int i=0; i<NumOfSegBH2; i++){
     BH2DdE[i]->Draw(); 
     c1 ->Print(pdf); 
   }
                             
  c1->Print(pdf+"]");        
   
/////////////////////////////////////////////////////////////////////////////////////////////
//                                                                                         //
//    BH1 & BH2 dat file maker                                                             //
//                                                                                         //
/////////////////////////////////////////////////////////////////////////////////////////////
  TString fout1 = (Form( "%s/hp_dat/HodoParamMaker1_BH1_TDC_%05d.dat", anadir.Data() ,runnum));  
  TString fout2 = (Form( "%s/hp_dat/HodoParamMaker1_BH1_ADC_%05d.dat", anadir.Data() ,runnum));  
   
  std::ofstream fout_1(fout1.Data()); 
  std::ofstream fout_2(fout2.Data()); 
  for(int i=0; i<NumOfSegBH1; i++){
     fout_1 << bh1utprm[i]  <<  "\t"  << bh1dtprm[i] << endl;
     fout_2 << bh1ubgprm[i]  <<  "\t" << bh1umipprm[i]  <<  "\t" << bh1dbgprm[i]  <<  "\t" << bh1dmipprm[i] << endl;
  }     

  TString fout3 = (Form( "%s/hp_dat/HodoParamMaker1_BH2_TDC_%05d.dat", anadir.Data() ,runnum));  
  TString fout4 = (Form( "%s/hp_dat/HodoParamMaker1_BH2_ADC_%05d.dat", anadir.Data() ,runnum));  
   
  std::ofstream fout_3(fout3.Data()); 
  std::ofstream fout_4(fout4.Data()); 
  for(int i=0; i<NumOfSegBH2; i++){
     fout_1 << bh2utprm[i]  <<  "\t"  << bh2dtprm[i] << endl;
     fout_2 << bh2ubgprm[i]  <<  "\t" << bh2umipprm[i]  <<  "\t" << bh2dbgprm[i]  <<  "\t" << bh2dmipprm[i] << endl;
  }     

                             
}                            
                             
