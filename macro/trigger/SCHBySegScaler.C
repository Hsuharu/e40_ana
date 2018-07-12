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


void SCHBySegScaler( int month, int runnum){
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
   TString anadir=Form("%s/work/e40/ana",std::getenv("HOME")); 
   TFile *f = new TFile(Form("%s/analyzer_%s/rootfile/run%05d_Easiroc.root", anadir.Data(),Month[month], runnum),"READ");
   if (!f) {
      f = new TFile(Form("%s/rootfile/run%05d_Easiroc.root", anadir.Data() , runnum));
   }
    TTree *ea0c;
    f->GetObject("ea0c",ea0c);

//Declaration of leaves types
   Int_t           evnum;
   Int_t           trignhits;
   Int_t           trigpat[32];
   Int_t           trigflag[32];
   Int_t           bft_ncl;
   Int_t           bft_clsize[92];
   Double_t        bft_ctime[92];
   Double_t        bft_ctot[92];
   Double_t        bft_clpos[92];
   Int_t           sch_ncl;
   Int_t           sch_clsize[64];
   Double_t        sch_ctime[64];
   Double_t        sch_ctot[64];
   Double_t        sch_clpos[64];
   Int_t           sftv_ncl;
   Int_t           sftv_clsize[190];
   Double_t        sftv_ctime[190];
   Double_t        sftv_ctot[190];
   Double_t        sftv_clpos[190];
   Int_t           sftu_ncl;
   Int_t           sftu_clsize[153];
   Double_t        sftu_ctime[153];
   Double_t        sftu_ctot[153];
   Double_t        sftu_clpos[153];
   Int_t           sftx_ncl;
   Int_t           sftx_clsize[55];
   Double_t        sftx_ctime[55];
   Double_t        sftx_ctot[55];
   Double_t        sftx_clpos[55];

   // Set branch addresses.
   ea0c->SetBranchAddress("evnum",&evnum);
   ea0c->SetBranchAddress("trignhits",&trignhits);
   ea0c->SetBranchAddress("trigpat",trigpat);
   ea0c->SetBranchAddress("trigflag",trigflag);
   ea0c->SetBranchAddress("bft_ncl",&bft_ncl);
   ea0c->SetBranchAddress("bft_clsize",bft_clsize);
   ea0c->SetBranchAddress("bft_ctime",bft_ctime);
   ea0c->SetBranchAddress("bft_ctot",bft_ctot);
   ea0c->SetBranchAddress("bft_clpos",bft_clpos);
   ea0c->SetBranchAddress("sch_ncl",&sch_ncl);
   ea0c->SetBranchAddress("sch_clsize",sch_clsize);
   ea0c->SetBranchAddress("sch_ctime",sch_ctime);
   ea0c->SetBranchAddress("sch_ctot",sch_ctot);
   ea0c->SetBranchAddress("sch_clpos",sch_clpos);
   ea0c->SetBranchAddress("sftv_ncl",&sftv_ncl);
   ea0c->SetBranchAddress("sftv_clsize",sftv_clsize);
   ea0c->SetBranchAddress("sftv_ctime",sftv_ctime);
   ea0c->SetBranchAddress("sftv_ctot",sftv_ctot);
   ea0c->SetBranchAddress("sftv_clpos",sftv_clpos);
   ea0c->SetBranchAddress("sftu_ncl",&sftu_ncl);
   ea0c->SetBranchAddress("sftu_clsize",sftu_clsize);
   ea0c->SetBranchAddress("sftu_ctime",sftu_ctime);
   ea0c->SetBranchAddress("sftu_ctot",sftu_ctot);
   ea0c->SetBranchAddress("sftu_clpos",sftu_clpos);
   ea0c->SetBranchAddress("sftx_ncl",&sftx_ncl);
   ea0c->SetBranchAddress("sftx_clsize",sftx_clsize);
   ea0c->SetBranchAddress("sftx_ctime",sftx_ctime);
   ea0c->SetBranchAddress("sftx_ctot",sftx_ctot);
   ea0c->SetBranchAddress("sftx_clpos",sftx_clpos);

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

   TH1D *SCHCT[NumOfSegSCH]; 
      for (int i=0; i<NumOfSegSCH;i++) {
        SCHCT[i] = new TH1D(Form("SCH_%dCT",i+1),Form("SCH_%dCT",i+1),2000,-5000,5000);
      }
   TH1D *SCHHitPat = new TH1D("SCHHitPat","SCHHitPat",NumOfSegSCH+1,0,NumOfSegSCH+1);


   Long64_t nentries = ea0c->GetEntries();
   double fitprm[3];
   double schctprm[NumOfSegSCH]; 
   double schscr[NumOfSegSCH]; 

//Fit range
   double f_l  = 200; 

//Draw range
   double l = 1000; 

//Draw range
   int T0_range_min = -3000;
   int T0_range_max = 3000;

   TF1 *fit = new TF1("fit","gaus"); 
   

/////////////////////////////////////////////////////////////////////////////////////////////
//                                                                                         //
//    SCH CTime Mean get code                                                              //
//                                                                                         //
/////////////////////////////////////////////////////////////////////////////////////////////
   Long64_t nbytes = 0;
   for (Long64_t s=0; s<nentries;s++) {
      nbytes += ea0c->GetEntry(s);
      for (int i=0; i<NumOfSegSCH;i++) {
            SCHCT[i]->Fill(sch_ctime[i]);
      }
   }

   
   TString pdf = Form("%s/pdf/trigger/SCHBySegScaler_%05d.pdf", anadir.Data(),runnum);
   TCanvas *c1 = new TCanvas("c1","c1",800,700); 
   c1->Print(pdf+"["); 

// SCH TDC MEAN 
   for (int i=0; i<NumOfSegSCH;i++) {
       schctprm[i] = SCHCT[i]->GetMaximumBin();   

       schctprm[i] = SCHCT[i]->GetXaxis()->GetBinCenter(schctprm[i]);  

       SCHCT[i]->Fit("fit","i","", schctprm[i]-f_l, schctprm[i]+f_l); 
       schctprm[i] = fit->GetParameter(1);  
       SCHCT[i]->GetXaxis()->SetRangeUser(schctprm[i]-1*(l), schctprm[i]+2*(l)); 

   }

   c1->cd(); 
   SCHHitPat->Draw(); 
   c1 ->Print(pdf); 

   c1->cd(); 
   c1->SetGridx();
   c1->SetGridy();

   for(int i=0; i<NumOfSegSCH; i++){
     SCHCT[i]->Draw(); 
     c1 ->Print(pdf); 
   }


///////////////////////////////////////////////////////////////////////////////////////////////
////                                                                                         //
////    BH1 & BH2 TDC's peak change to 0 code                                                //
////                                                                                         //
///////////////////////////////////////////////////////////////////////////////////////////////
//   nbytes = 0;
//   for (Long64_t s=0; s<nentries;s++) {
//      nbytes += ea0c->GetEntry(s);
//      for (int i=0; i<NumOfSegBH1;i++) {
//        if(bh1ut[i]>0 && bh1dt[i]>0 && bh1nhits < range2 && bh1nhits > range1 && bh2nhits == 1){
//          for(int j=0; j<MaxDepth; j++){
//            BH1UT0[i]->Fill(bh1ut[i][j]-bh1utprm[i]);
//            BH1DT0[i]->Fill(bh1dt[i][j]-bh1dtprm[i]);
//          }
//        }
//      }
//   }
//
//
//   for(int i=0; i<NumOfSegBH1; i++){
//     BH1UT0[i]->GetXaxis()->SetRangeUser(T0_range_min,T0_range_max);  
//     BH1UT0[i]->Draw(); 
//     c1 ->Print(pdf); 
//   }
//   for(int i=0; i<NumOfSegBH1; i++){
//     BH1DT0[i]->GetXaxis()->SetRangeUser(T0_range_min,T0_range_max);  
//     BH1DT0[i]->Draw(); 
//     c1 ->Print(pdf); 
//   }
//                             
  c1->Print(pdf+"]");        
   
///////////////////////////////////////////////////////////////////////////////////////////////
////                                                                                         //
////    BH1 & BH2 dat file maker                                                             //
////                                                                                         //
///////////////////////////////////////////////////////////////////////////////////////////////
//  TString fout1 = (Form( "%s/hp_dat/HodoParamMaker1_BH1_TDC_%05d.dat", anadir.Data() ,runnum));  
//  TString fout2 = (Form( "%s/hp_dat/HodoParamMaker1_BH1_ADC_%05d.dat", anadir.Data() ,runnum));  
//   
//  std::ofstream fout_1(fout1.Data()); 
//  std::ofstream fout_2(fout2.Data()); 
//  for(int i=0; i<NumOfSegBH1; i++){
//     fout_1 << bh1utprm[i]  <<  "\t"  << bh1dtprm[i] << endl;
//     fout_2 << bh1ubgprm[i]  <<  "\t" << bh1umipprm[i]  <<  "\t" << bh1dbgprm[i]  <<  "\t" << bh1dmipprm[i] << endl;
//  }     
                             
}                            
                             
