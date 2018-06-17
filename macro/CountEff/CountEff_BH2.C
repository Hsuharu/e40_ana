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


void CountEff_BH2( int month, int runnum){
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
   Long64_t nentries = tree->GetEntries();
   double fitprm[3];
   double bh1utprm[NumOfSegBH1]; 
   double bh1dtprm[NumOfSegBH1]; 

   double bh2utprm[NumOfSegBH2]; 
   double bh2dtprm[NumOfSegBH2]; 

//Setting Value
   int MaxDepth = 16;
   double FPGA_hr_TDC = 0.000939002;;

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

//time range
   int Range = 5; //unit [ns]

//time
   double Time = 0.; //unit [ns]

//Counts
   int bh1usegcount[NumOfSegBH1+1] = {0,0,0,0,0,0,0,0,0,0,0,0};
   int bh1dsegcount[NumOfSegBH1+1] = {0,0,0,0,0,0,0,0,0,0,0,0};
   int bh2usegcount[NumOfSegBH2+1] = {0,0,0,0,0,0,0,0,0};
   int bh2dsegcount[NumOfSegBH2+1] = {0,0,0,0,0,0,0,0,0};
   int bh1usegevent[NumOfSegBH1+1] = {0,0,0,0,0,0,0,0,0,0,0,0};
   int bh1dsegevent[NumOfSegBH1+1] = {0,0,0,0,0,0,0,0,0,0,0,0};
   int bh2usegevent[NumOfSegBH2+1] = {0,0,0,0,0,0,0,0,0};
   int bh2dsegevent[NumOfSegBH2+1] = {0,0,0,0,0,0,0,0,0};

   TH1D *BH1UT[NumOfSegBH1]; 
   TH1D *BH1DT[NumOfSegBH1]; 
   TH1D *BH1UT0[NumOfSegBH1]; 
   TH1D *BH1DT0[NumOfSegBH1]; 
   TH1D *BH1UTns[NumOfSegBH1]; 
   TH1D *BH1DTns[NumOfSegBH1]; 
   TH1D *BH1UTnsFirst[NumOfSegBH1]; 
   TH1D *BH1DTnsFirst[NumOfSegBH1]; 
   TH1D *BH1UT0SUM = new TH1D("BH1_U_T0_SUM","BH1_UT0SUM",2000,-100000,100000); 
   TH1D *BH1DT0SUM = new TH1D("BH1_D_T0_SUM","BH1_DT0SUM",2000,-100000,100000); 
   TH1D *BH1UTnsSUM = new TH1D("BH1-U_SUM [ns]","BH1-U_SUM [ns]",160,-Range,Range); 
   TH1D *BH1DTnsSUM = new TH1D("BH1-D_SUM [ns]","BH1-D_SUM [ns]",160,-Range,Range); 
   TH1D *BH1UTnsFirstSUM = new TH1D("BH1-U First_SUM [ns]","BH1-U First_SUM [ns]",160,-Range,Range);  
   TH1D *BH1DTnsFirstSUM = new TH1D("BH1-D First_SUM [ns]","BH1-D First_SUM [ns]",160,-Range,Range);  
      for (int i=0; i<NumOfSegBH1;i++) {
        BH1UT[i] = new TH1D(Form("BH1_%dUT",i+1),Form("BH1_%dUT",i+1),2000,200000,400000);
        BH1DT[i] = new TH1D(Form("BH1_%dDT",i+1),Form("BH1_%dDT",i+1),2000,200000,400000);
        BH1UT0[i] = new TH1D(Form("BH1_%dUT0",i+1),Form("BH1_%dUT0",i+1),2000,-100000,100000);
        BH1DT0[i] = new TH1D(Form("BH1_%dDT0",i+1),Form("BH1_%dDT0",i+1),2000,-100000,100000);
        BH1UTns[i] = new TH1D(Form("BH1-%dU [ns]",i+1),Form("BH1-%dU [ns]",i+1),160,-Range,Range);
        BH1DTns[i] = new TH1D(Form("BH1-%dD [ns]",i+1),Form("BH1-%dD [ns]",i+1),160,-Range,Range);
        BH1UTnsFirst[i] = new TH1D(Form("BH1-%dU First [ns]",i+1),Form("BH1-%dU First [ns]",i+1),160,-Range,Range);
        BH1DTnsFirst[i] = new TH1D(Form("BH1-%dD First [ns]",i+1),Form("BH1-%dD First [ns]",i+1),160,-Range,Range);
      }
//   TH1D *BH1HitPat = new TH1D("BH1HitPat","BH1HitPat",12,0,12);

   TH1D *BH2UT[NumOfSegBH2]; 
   TH1D *BH2DT[NumOfSegBH2]; 
   TH1D *BH2UT0[NumOfSegBH2]; 
   TH1D *BH2DT0[NumOfSegBH2]; 
   TH1D *BH2UTns[NumOfSegBH2]; 
   TH1D *BH2DTns[NumOfSegBH2]; 
   TH1D *BH2UTnsFirst[NumOfSegBH2]; 
   TH1D *BH2DTnsFirst[NumOfSegBH2]; 
   TH1D *BH2UT0SUM = new TH1D("BH2_U_T0_SUM","BH2_UT0SUM",2000,-100000,100000); 
   TH1D *BH2DT0SUM = new TH1D("BH2_D_T0_SUM","BH2_DT0SUM",2000,-100000,100000); 
   TH1D *BH2UTnsSUM = new TH1D("BH2-U_SUM [ns]","BH2-U_SUM [ns]",160,-Range,Range); 
   TH1D *BH2DTnsSUM = new TH1D("BH2-D_SUM [ns]","BH2-D_SUM [ns]",160,-Range,Range); 
   TH1D *BH2UTnsFirstSUM = new TH1D("BH2-U First_SUM [ns]","BH2-U First_SUM [ns]",160,-Range,Range);  
   TH1D *BH2DTnsFirstSUM = new TH1D("BH2-D First_SUM [ns]","BH2-D First_SUM [ns]",160,-Range,Range);  
      for (int i=0; i<NumOfSegBH2;i++) {
        BH2UT[i] = new TH1D(Form("BH2_%dUT",i+1),Form("BH2_%dUT",i+1),2000,200000,400000);
        BH2DT[i] = new TH1D(Form("BH2_%dDT",i+1),Form("BH2_%dDT",i+1),2000,200000,400000);
        BH2UT0[i] = new TH1D(Form("BH2_%dUT0",i+1),Form("BH2_%dUT0",i+1),2000,-100000,100000);
        BH2DT0[i] = new TH1D(Form("BH2_%dDT0",i+1),Form("BH2_%dDT0",i+1),2000,-100000,100000);
        BH2UTns[i] = new TH1D(Form("BH2-%dU [ns]",i+1),Form("BH2-%dU [ns]",i+1),160,-Range,Range);
        BH2DTns[i] = new TH1D(Form("BH2-%dD [ns]",i+1),Form("BH2-%dD [ns]",i+1),160,-Range,Range);
        BH2UTnsFirst[i] = new TH1D(Form("BH2-%dU First [ns]",i+1),Form("BH2-%dU First [ns]",i+1),160,-Range,Range);
        BH2DTnsFirst[i] = new TH1D(Form("BH2-%dD First [ns]",i+1),Form("BH2-%dD First [ns]",i+1),160,-Range,Range);
      }
//   TH1D *BH2HitPat = new TH1D("BH2HitPat","BH2HitPat",9,0,9);


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
        for(int j=0; j<MaxDepth; j++){
          if(bh1ut[i][j]>0){
            BH1UT[i]->Fill(bh1ut[i][j]);
          }
          if(bh1dt[i][j]>0){
            BH1DT[i]->Fill(bh1dt[i][j]);
          }
        }
//        if(bh1nhits < range2 && bh1nhits > range1 && bh2nhits == 1){
//          BH1HitPat->Fill(bh1hitpat[i]);
//        }
      }

      for (int i=0; i<NumOfSegBH2;i++) {
        for(int j=0; j<MaxDepth; j++){
          if(bh2ut[i][j]>0){
            BH2UT[i]->Fill(bh2ut[i][j]);
          }
          if(bh2dt[i][j]>0){
            BH2DT[i]->Fill(bh2dt[i][j]);
          }
        }
//        if(bh1nhits < range2 && bh1nhits > range1 && bh2nhits == 1){
//          BH2HitPat->Fill(bh2hitpat[i]);
//        }
      }
   }

   
   TString pdf = Form("%s/pdf/CountEff/CountEff_BH2_%05d.pdf", anadir.Data(),runnum);
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

       BH2UT[i]->Fit("fit","i","", bh2utprm[i]-f_l2, bh2utprm[i]+f_l2); 
       bh2utprm[i] = fit->GetParameter(1);  
       BH2UT[i]->GetXaxis()->SetRangeUser(bh2utprm[i]-1*l2, bh2utprm[i]+2*(l2));

       BH2DT[i]->Fit("fit","i","", bh2dtprm[i]-f_l2_D, bh2dtprm[i]+f_l2_D);
       bh2dtprm[i] = fit->GetParameter(1);  
       BH2DT[i]->GetXaxis()->SetRangeUser(bh2dtprm[i]-1*(l2), bh2dtprm[i]+2*(l2));  

   }
   
//   c1->cd(); 
//   BH1HitPat->Draw(); 
//   c1 ->Print(pdf); 
//
//   c1->cd(); 
//   BH2HitPat->Draw(); 
//   c1 ->Print(pdf); 
   
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

// If you have TDC Peak parameter
///////////////////////////////////////////////////////////////////////////////////////////////
////                                                                                         //
////    BH1 & BH2 TDC's peak parameter file get                                              //
////                                                                                         //
///////////////////////////////////////////////////////////////////////////////////////////////
//  std::vector<std::vector<double>> bh1tdcMean; 
//  std::vector<std::vector<double>> bh2tdcMean; 
//  TString prmdir2=Form("%s/work/e40/ana/hp_dat",std::getenv("HOME")); 
//  TString filein1=Form("%s/HodoParam_BH1_TDCcalib_00001.dat",prmdir2.Data()); 
//  TString filein2=Form("%s/HodoParam_BH2_TDCcalib_00001.dat",prmdir2.Data()); 
//  std::ifstream fin1(filein1);
//  std::ifstream fin2(filein2);
//  std::string line;
//
//
//  while(std::getline(fin1, line)){
//    double a=-1, b=-1;
//    std::istringstream input_line( line );
//    std::vector<double> inner;
//    if( input_line >> a >> b ){
//      inner.push_back(a);
//      inner.push_back(b);
//      bh1tdcMean.push_back(inner);
//    }
//  }
//
//  while(std::getline(fin2, line)){
//    double a=-1, b=-1;
//    std::istringstream input_line( line );
//    std::vector<double> inner;
//    if( input_line >> a >> b ){
//      inner.push_back(a);
//      inner.push_back(b);
//      bh2tdcMean.push_back(inner);
//    }
//  }



/////////////////////////////////////////////////////////////////////////////////////////////
//                                                                                         //
//    BH1 & BH2 TDC's peak change to 0 code                                                //
//                                                                                         //
/////////////////////////////////////////////////////////////////////////////////////////////
   nbytes = 0;
   for (Long64_t s=0; s<nentries;s++) {
     nbytes += tree->GetEntry(s);
     for (int i=0, Firstflg1=1, Firstflg2=1, FirstEventflg1 = 1, FirstEventflg2 = 1, bh1usegcounts=1, bh1dsegcounts=1; i<NumOfSegBH1;i++) {
       for(int j=0; j<MaxDepth; j++){
         if(bh1ut[i][j]>0){
           //Up
           BH1UT0[i]->Fill(bh1ut[i][j]-bh1utprm[i]);
           BH1UT0SUM->Fill(bh1ut[i][j]-bh1utprm[i]);
           Time = (bh1ut[i][j]-bh1utprm[i])*FPGA_hr_TDC;
           BH1UTns[i]->Fill(Time);
           BH1UTnsSUM->Fill(Time);
           if(Time > -5. && Time < 5.){
             if(Firstflg1 == 1){
               BH1UTnsFirst[i]->Fill(Time);
               BH1UTnsFirstSUM->Fill(Time);
               Firstflg1 = 0;
               bh1usegcount[i] += bh1usegcounts;
               bh1usegcount[NumOfSegBH1] += bh1usegcounts;
             }
           }
           if(FirstEventflg1 == 1){
             bh1usegevent[i] += 1;
             bh1usegevent[NumOfSegBH1] += 1;
             FirstEventflg1 = 0;
           }
         }
         if(bh1dt[i][j]>0){
           //Down
           BH1DT0[i]->Fill(bh1dt[i][j]-bh1dtprm[i]);
           BH1DT0SUM->Fill(bh1dt[i][j]-bh1dtprm[i]);
           Time = (bh1dt[i][j]-bh1dtprm[i])*FPGA_hr_TDC;
           BH1DTns[i]->Fill(Time);
           BH1DTnsSUM->Fill(Time);
           if(Time > -5. && Time < 5.){
             if(Firstflg2 == 1){
               BH1DTnsFirst[i]->Fill(Time);
               BH1DTnsFirstSUM->Fill(Time);
               Firstflg2 = 0;
               bh1dsegcount[i] += bh1dsegcounts;
               bh1dsegcount[NumOfSegBH1] += bh1dsegcounts;
             }
           }
           if(FirstEventflg2 == 1){
             bh1dsegevent[i] += 1;
             bh1dsegevent[NumOfSegBH1] += 1;
             FirstEventflg2 = 0;
           }
         }
       }
     }

     for (int i=0, Firstflg1=1, Firstflg2=1, FirstEventflg1 = 1, FirstEventflg2 = 1, bh2usegcounts=1, bh2dsegcounts=1; i<NumOfSegBH2;i++) {
       for(int j=0; j<MaxDepth; j++){
         if(bh2ut[i][j]>0){
           BH2UT0[i]->Fill(bh2ut[i][j]-bh2utprm[i]);
           BH2UT0SUM->Fill(bh2ut[i][j]-bh2utprm[i]);
           Time = (bh2ut[i][j]-bh2utprm[i])*FPGA_hr_TDC;
           BH2UTns[i]->Fill(Time);
           BH2UTnsSUM->Fill(Time);
           if(Time > -5. && Time < 5.){
             if(Firstflg1 == 1){
               BH2UTnsFirst[i]->Fill(Time);
               BH2UTnsFirstSUM->Fill(Time);
               Firstflg1 = 0;
               bh2usegcount[i] += bh2usegcounts;
               bh2usegcount[NumOfSegBH2] += bh2usegcounts;
             }
           }
           if(FirstEventflg1 == 1){
             bh2usegevent[i] += 1;
             bh2usegevent[NumOfSegBH2] += 1;
             FirstEventflg1 = 0;
           }
         }
         if(bh2dt[i][j]>0){
           BH2DT0[i]->Fill(bh2dt[i][j]-bh2dtprm[i]);
           BH2DT0SUM->Fill(bh2dt[i][j]-bh2dtprm[i]);
           Time = (bh2dt[i][j]-bh2dtprm[i])*FPGA_hr_TDC;
           BH2DTns[i]->Fill(Time);
           BH2DTnsSUM->Fill(Time);
           if(Time > -5. && Time < 5.){
             if(Firstflg2 == 1){
               BH2DTnsFirst[i]->Fill(Time);
               BH2DTnsFirstSUM->Fill(Time);
               Firstflg2 = 0;
               bh2dsegcount[i] += bh2dsegcounts;
               bh2dsegcount[NumOfSegBH2] += bh2dsegcounts;
             }
           }
           if(FirstEventflg2 == 1){
             bh2dsegevent[i] += 1;
             bh2dsegevent[NumOfSegBH2] += 1;
             FirstEventflg2 = 0;
           }
         }
       }
     }
   }
   
   TCanvas *c2 = new TCanvas("c2","c2",800,700); 
   c2->Divide(2,2);
   for(int i=0; i<NumOfSegBH1; i++){
     BH1UT0[i]->GetXaxis()->SetRangeUser(T0_range_min,T0_range_max);  
     c2->cd(1);
     BH1UT0[i]->Draw(); 
     c2->cd(2);
     BH1UTns[i]->Draw(); 
     c2->cd(3);
     BH1UTnsFirst[i]->Draw(); 
     c2 ->Print(pdf); 
   }
   for(int i=0; i<NumOfSegBH1; i++){
     BH1DT0[i]->GetXaxis()->SetRangeUser(T0_range_min,T0_range_max);  
     c2->cd(1);
     BH1DT0[i]->Draw(); 
     c2->cd(2);
     BH1DTns[i]->Draw(); 
     c2->cd(3);
     BH1DTnsFirst[i]->Draw(); 
     c2 ->Print(pdf); 
   }
   for(int i=0; i<NumOfSegBH2; i++){
     BH2UT0[i]->GetXaxis()->SetRangeUser(T0_range_min,T0_range_max);  
     c2->cd(1);
     BH2UT0[i]->Draw(); 
     c2->cd(2);
     BH2UTns[i]->Draw(); 
     c2->cd(3);
     BH2UTnsFirst[i]->Draw(); 
     c2 ->Print(pdf); 
   }
   for(int i=0; i<NumOfSegBH2; i++){
     BH2DT0[i]->GetXaxis()->SetRangeUser(T0_range_min,T0_range_max);  
     c2->cd(1);
     BH2DT0[i]->Draw(); 
     c2->cd(2);
     BH2DTns[i]->Draw(); 
     c2->cd(3);
     BH2DTnsFirst[i]->Draw(); 
     c2 ->Print(pdf); 
   }
   
   BH2DT0SUM->GetXaxis()->SetRangeUser(T0_range_min,T0_range_max);  
   c2->cd(1);
   BH2DT0SUM->Draw(); 
   c2->cd(2);
   BH2DTnsSUM->Draw(); 
   c2->cd(3);
   BH2DTnsFirstSUM->Draw(); 
   c2 ->Print(pdf); 
                             
  c1->Print(pdf+"]");        
  
   for(int i=0; i<NumOfSegBH1+1; i++){
     std::cout << " BH1 " <<  i+1 << "U " <<  " \t "  << bh1usegcount[i] <<  " \t "  << bh1usegevent[i] <<  " \t "  << (double)bh1usegcount[i]/bh1usegevent[i] <<  " \t "  << std::endl;
     std::cout << " BH1 " <<  i+1 << "D " <<  " \t "  << bh1dsegcount[i] <<  " \t "  << bh1dsegevent[i] <<  " \t "  << (double)bh1dsegcount[i]/bh1dsegevent[i] <<  " \t "  << std::endl;
   }                                                                                                                                
                                                                                                                                    
   for(int i=0; i<NumOfSegBH2+1; i++){                                                                                              
     std::cout << " BH2 " <<  i+1 << "U " <<  " \t "  << bh2usegcount[i] <<  " \t "  << bh2usegevent[i] <<  " \t "  << (double)bh2usegcount[i]/bh2usegevent[i] <<  " \t "  << std::endl;
     std::cout << " BH2 " <<  i+1 << "D " <<  " \t "  << bh2dsegcount[i] <<  " \t "  << bh2dsegevent[i] <<  " \t "  << (double)bh2dsegcount[i]/bh2dsegevent[i] <<  " \t "  << std::endl;
   }

   
/////////////////////////////////////////////////////////////////////////////////////////////
//                                                                                         //
//    BH1 & BH2 dat file maker                                                             //
//                                                                                         //
/////////////////////////////////////////////////////////////////////////////////////////////
  TString fout1 = (Form( "%s/hp_dat/Debug_BH1_TDC_%05d.dat", anadir.Data() ,runnum));  
  TString fout2 = (Form( "%s/hp_dat/CountEff_BH1_%05d.dat", anadir.Data() ,runnum));  
   
  std::ofstream fout_1(fout1.Data()); 
  std::ofstream fout_2(fout2.Data()); 
  for(int i=0; i<NumOfSegBH1; i++){
     fout_1 << bh1utprm[i]  <<  "\t"  << bh1dtprm[i] << endl;
  }     
  for(int i=0; i<NumOfSegBH1+1; i++){
     fout_2 << bh1usegcount[i] <<  "\t" 
            << bh1usegevent[i] <<  "\t"
            << (double)bh1usegcount[i]/bh1usegevent[i] <<  "\t" 
            << bh1dsegcount[i] <<  "\t" 
            << bh1dsegevent[i] <<  "\t"
            << (double)bh1dsegcount[i]/bh1dsegevent[i]  <<endl;
  }     

  TString fout3 = (Form( "%s/hp_dat/Debug_BH2_TDC_%05d.dat", anadir.Data() ,runnum));  
  TString fout4 = (Form( "%s/hp_dat/CountEff_BH3_%05d.dat", anadir.Data() ,runnum));  
   
  std::ofstream fout_3(fout3.Data()); 
  std::ofstream fout_4(fout4.Data()); 
  for(int i=0; i<NumOfSegBH2; i++){
     fout_3 << bh2utprm[i]  <<  "\t"  << bh2dtprm[i] << endl;
  }     
  for(int i=0; i<NumOfSegBH2+1; i++){
     fout_2 << bh2usegcount[i] <<  "\t" 
            << bh2usegevent[i] <<  "\t"
            << (double)bh2usegcount[i]/bh2usegevent[i] <<  "\t" 
            << bh2dsegcount[i] <<  "\t" 
            << bh2dsegevent[i] <<  "\t"
            << (double)bh2dsegcount[i]/bh2dsegevent[i]  <<endl;
  }     

                             
}                            
                             
