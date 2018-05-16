#include "DetectorID.hh"

void mt_check(int runnum){
////////////////////////////////////////////////////////////
//   This file has been automatically generated           //
//     (Sun Feb 25 23:10:42 2018 by ROOT version6.10/08)  //
//   from TTree tree/tree of Counter                      //
//   found on file: ../rootfile/run04571_hodo.root        //
////////////////////////////////////////////////////////////

  gStyle->SetOptStat(1111110); 
  gStyle->SetOptFit(1); 

//Reset ROOT and connect tree file
   gROOT->Reset();
//   TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("../rootfile/run04571_hodo.root");
   TString anadir=Form("%s/work/e40/ana",std::getenv("HOME")); 
   TFile *f = new TFile(Form("%s/rootfile/run%05d_hodo.root", anadir.Data() , runnum),"READ");
   if (!f) {
      f = new TFile(Form("%s/rootfile/run%05d_hodo.root", anadir.Data() , runnum));
   }
    TTree *tree;
    f->GetObject("tree",tree);

//Declaration of leaves types
   int           evnum;
   int           trignhits;
   int           trigpat[18];
   int           trigflag[32];
   int           bh1nhits;
   int           bh1hitpat[11];
   double        bh1ua[11];
   double        bh1ut[11];
   double        bh1da[11];
   double        bh1dt[11];
   int           bh2nhits;
   int           bh2hitpat[8];
   double        bh2ua[8];
   double        bh2ut[8];
   double        bh2da[8];
   double        bh2dt[8];
   int           sacnhits;
   int           sachitpat[4];
   double        saca[4];
   double        sact[4];
   int           tofnhits;
   int           tofhitpat[24];
   double        tofua[24];
   double        tofut[24];
   double        tofda[24];
   double        tofdt[24];
   int           lcnhits;
   int           lchitpat[28];
   double        lcua[28];
   double        lcut[28];
   double        lcda[28];
   double        lcdt[28];
   double        bh1utime[11];
   double        bh1dtime[11];
   double        bh1mt[11];
   double        bh1de[11];
   double        bh2utime[8];
   double        bh2dtime[8];
   double        bh2mt[8];
   double        bh2de[8];
   double        sacmt[4];
   double        sacde[4];
   double        tofmt[24];
   double        tofde[24];
   double        lcmt[28];
   double        lcde[28];
   double        t0[8];
   double        ct0[8];
   double        btof[11][8];
   double        cbtof[11][8];

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
   tree->SetBranchAddress("lcnhits",&lcnhits);
   tree->SetBranchAddress("lchitpat",lchitpat);
   tree->SetBranchAddress("lcua",lcua);
   tree->SetBranchAddress("lcut",lcut);
   tree->SetBranchAddress("lcda",lcda);
   tree->SetBranchAddress("lcdt",lcdt);
   tree->SetBranchAddress("bh1utime",bh1utime);
   tree->SetBranchAddress("bh1dtime",bh1dtime);
   tree->SetBranchAddress("bh1mt",bh1mt);
   tree->SetBranchAddress("bh1de",bh1de);
   tree->SetBranchAddress("bh2utime",bh2utime);
   tree->SetBranchAddress("bh2dtime",bh2dtime);
   tree->SetBranchAddress("bh2mt",bh2mt);
   tree->SetBranchAddress("bh2de",bh2de);
   tree->SetBranchAddress("sacmt",sacmt);
   tree->SetBranchAddress("sacde",sacde);
   tree->SetBranchAddress("tofmt",tofmt);
   tree->SetBranchAddress("tofde",tofde);
   tree->SetBranchAddress("lcmt",lcmt);
   tree->SetBranchAddress("lcde",lcde);
   tree->SetBranchAddress("t0",t0);
   tree->SetBranchAddress("ct0",ct0);
   tree->SetBranchAddress("btof",btof);
   tree->SetBranchAddress("cbtof",cbtof);

//     This is the loop skeleton
//       To read only selected branches, Insert statements like:
// tree->SetBranchStatus("*",0);  // disable all branches
// TTreePlayer->SetBranchStatus("branchname",1);  // activate branchname


   TH1D *BH1MT[NumOfSegBH1]; 
      for (int i=0; i<NumOfSegBH1;i++) {
        BH1MT[i] = new TH1D(Form("BH1MT%d",i+1),Form("BH1MT%d",i+1),2800,-50,50);
      }

   Long64_t nentries = tree->GetEntries();
   double bh1mtm[NumOfSegBH1]; 

   int l = 2 ;
   int l_v = 1 ;


   TF1 *fit = new TF1("fit","gaus"); 

   Long64_t nbytes = 0;
   for (Long64_t i=0; i<nentries;i++) {
      nbytes += tree->GetEntry(i);
      for (int i=0; i<NumOfSegBH1;i++) {
        if(bh1mt[i] > -100){ 
            BH1MT[i]->Fill(bh1mt[i]);
        }
      }
   }

   TCanvas *c1 = new TCanvas("c1","c1",800,700); 
       c1->Divide(4,3);

   TString pdf1 = Form("%s/pdf/trigger_study/mt_%05d.pdf", anadir.Data(),runnum);
   c1->Print(pdf1+"["); 

   for (int i=0; i<NumOfSegBH1;i++) {
       bh1mtm[i] = BH1MT[i]->GetMaximumBin();   

       bh1mtm[i] = BH1MT[i]->GetXaxis()->GetBinCenter(bh1mtm[i]);  

       c1->cd(i+1); 
       BH1MT[i]->Draw(); 
       BH1MT[i]->Fit("fit","","", bh1mtm[i]-l, bh1mtm[i]+l);  
       bh1mtm[i] = fit->GetParameter(1);  
       BH1MT[i]->GetXaxis()->SetRangeUser(bh1mtm[i]-l_v,bh1mtm[i]+2*l_v);   
   }
   
   c1->Print(pdf1); 

  c1->Print(pdf1+"]"); 

  TString fout1 = (Form( "%s/hp_dat/HodoParam_BH1_MT_%05d.dat", anadir.Data() ,runnum));  
  std::ofstream fout_1(fout1.Data()); 
  for(int i=0; i<NumOfSegBH1; i++){
     fout_1 << bh1mtm[i]   << endl;
  }     

}
