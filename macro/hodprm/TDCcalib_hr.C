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
#include <TSpectrum.h>
#include <TMath.h>
#include <TH1.h>
#include <TF1.h>
#include <TH2.h>


//#include "DetectorID.hh"

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

//using namespace std;

void TDCcalib_hr(int month,int runnum){
//  int runnum = 1;
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

   int NumOfSegBH1 = 1;
   int NumOfSegBH2 = 1;

   TH1D *BH1UT[NumOfSegBH1]; 
   TH1D *BH1DT[NumOfSegBH1]; 
      for (int i=0; i<NumOfSegBH1;i++) {
        BH1UT[i] = new TH1D(Form("BH1_%dUT",i+1),Form("BH1_%dUT",i+1),20000,0,400000);
        BH1DT[i] = new TH1D(Form("BH1_%dDT",i+1),Form("BH1_%dDT",i+1),20000,0,400000);
      }

   TH1D *BH2UT[NumOfSegBH2]; 
   TH1D *BH2DT[NumOfSegBH2]; 
      for (int i=0; i<NumOfSegBH2;i++) {
        BH2UT[i] = new TH1D(Form("BH2_%dUT",i+1),Form("BH2_%dUT",i+1),20000,0,400000);
        BH2DT[i] = new TH1D(Form("BH2_%dDT",i+1),Form("BH2_%dDT",i+1),20000,0,400000);
      }

   Long64_t nentries = tree->GetEntries();

   TF1 *fit = new TF1("fit","gaus"); 
   TF1 *polone; 
   int mhit = 16;

   Long64_t nbytes = 0;
   for (Long64_t s=0; s<nentries;s++) {
      nbytes += tree->GetEntry(s);
      for (int i=0; i<NumOfSegBH1;i++) {
        for (int j=0; j<mhit;j++) {
          BH1UT[i]->Fill(bh1ut[i][j]);
        }
      }

      for (int i=0; i<NumOfSegBH2;i++) {
        for (int j=0; j<mhit;j++) {
          BH2UT[i]->Fill(bh2ut[i][j]);
        }
      }
   }

   TCanvas *c1 = new TCanvas("c1","c1",800,700); 
   TCanvas *c3 = new TCanvas("c3","c3",800,700); 

   TCanvas *c11 = new TCanvas("c11","c11",800,700); 
   TCanvas *c13 = new TCanvas("c13","c13",800,700); 
   
   TString pdf = Form("%s/pdf/trigger_study/TDCcalib_hr_%05d.pdf", anadir.Data(),runnum);
   c1->Print(pdf+"["); 

   int npeaks=300;
   int nfound = 0;
   int l = 300;
//   std::vector<double> y;   
//   std::vector<double> err_y;   

   TSpectrum *s_bh1;
//   std::vector< std::vector<double> >  p_bh1u  ; 
//   std::vector< std::vector<double> >  err_bh1u  ; 

   TGraphErrors *ger_bh1u[NumOfSegBH1]; 
   double a_bh1u[NumOfSegBH1];   
   double b_bh1u[NumOfSegBH1];   

   for (int i=0; i<NumOfSegBH1;i++) {
       s_bh1 = new TSpectrum(npeaks);  
       c1->cd();
       BH1UT[i]->Draw(); 
       nfound = s_bh1->Search(BH1UT[i],2,"",0.010); 
       std::vector< std::vector<double> >  p_bh1u (NumOfSegBH1, std::vector<double> (nfound))  ; 
       std::vector< std::vector<double> >  err_bh1u (NumOfSegBH1, std::vector<double> (nfound)) ; 
       std::vector<double> y (nfound);   
       std::vector<double> err_y (nfound);   
       for(int j=0; j<nfound; j++){
         p_bh1u[i][j] = s_bh1 ->GetPositionX()[j];
         BH1UT[i]->Fit("fit","","", p_bh1u[i][j]-l, p_bh1u[i][j]+l);  
         p_bh1u[i][j] = fit->GetParameter(1);
         err_bh1u[i][j] = fit->GetParError(1);
         y[j]=j*10;   
         err_y[j]=0.01;   
         fit -> Draw("sames"); 
       }  
       std::sort(&p_bh1u[i][0],&p_bh1u[i][nfound]); 
       c11->cd();
       ger_bh1u[i] = new TGraphErrors(nfound, &(p_bh1u[i][0]), &(y[0]), &(err_bh1u[i][0]),&(err_y[0]));  
       ger_bh1u[i]->SetMarkerStyle(8);
       ger_bh1u[i]->Draw();
       ger_bh1u[i]->Fit("pol1","","");  
       gStyle->SetOptFit(1);
       polone = ger_bh1u[i]->GetFunction("pol1");  
       a_bh1u[i] = polone->GetParameter(1);   
       b_bh1u[i] = polone->GetParameter(0);   
       ger_bh1u[i]->GetXaxis()->SetTitle(Form("TDC_U%d[ch]",i+1));   
       ger_bh1u[i]->GetYaxis()->SetTitle("time[ns] ");   
   }
   c1->Print(pdf); 
   c11->Print(pdf); 

   TSpectrum *s_bh2;
   std::vector< std::vector<double> >  p_bh2u   ; 
   std::vector< std::vector<double> >  err_bh2u  ; 

   TGraphErrors *ger_bh2u[NumOfSegBH2]; 
   double a_bh2u[NumOfSegBH2];   
   double b_bh2u[NumOfSegBH2];   

   for (int i=0; i<NumOfSegBH2;i++) {
       s_bh2 = new TSpectrum(npeaks);  
       c3->cd();
       BH2UT[i]->Draw(); 
       nfound = s_bh2->Search(BH2UT[i],2,"",0.010); 
       std::vector< std::vector<double> >  p_bh2u (NumOfSegBH1, std::vector<double> (nfound))  ; 
       std::vector< std::vector<double> >  err_bh2u (NumOfSegBH1, std::vector<double> (nfound)) ; 
       std::vector<double> y (nfound);   
       std::vector<double> err_y (nfound);   
       for(int j=0; j<nfound; j++){
         p_bh2u[i][j] = s_bh2 ->GetPositionX()[j];
         BH2UT[i]->Fit("fit","","", p_bh2u[i][j]-l, p_bh2u[i][j]+l);  
         p_bh2u[i][j] = fit->GetParameter(1);
         err_bh2u[i][j] = fit->GetParError(1);
         fit -> Draw("sames"); 
       }  
       std::sort(&p_bh2u[i][0],&p_bh2u[i][nfound]); 
       for(int i=0; i<nfound; i++){
         y[i]=i*10;   
         err_y[i]=0.01;   
       }  
       c13->cd();
       ger_bh2u[i] = new TGraphErrors(nfound, &(p_bh2u[i][0]), &(y[0]), &(err_bh2u[i][0]),&(err_y[0]));  
       ger_bh2u[i]->SetMarkerStyle(8);
       ger_bh2u[i]->Draw();
       ger_bh2u[i]->Fit("pol1","","");  
       gStyle->SetOptFit(1);
       polone = ger_bh2u[i]->GetFunction("pol1");  
       a_bh2u[i] = polone->GetParameter(1);   
       b_bh2u[i] = polone->GetParameter(0);   
       ger_bh2u[i]->GetXaxis()->SetTitle(Form("TDC_U%d[ch]",i+1));   
       ger_bh2u[i]->GetYaxis()->SetTitle("time[ns] ");   
   }
   c3->Print(pdf); 
   c13->Print(pdf); 
   
   c1->Print(pdf+"]"); 

  TString fout1 = (Form( "%s/hp_dat/HodoParam_BH1_TDCcalib_hr_%05d.dat", anadir.Data() ,runnum));  
  std::ofstream fout_1(fout1.Data()); 
  for(int i=0; i<NumOfSegBH1; i++){
      fout_1 << a_bh1u[i] << endl;
  }     

  TString fout2 = (Form( "%s/hp_dat/HodoParam_BH2_TDCcalib_hr_%05d.dat", anadir.Data() ,runnum));  
  std::ofstream fout_2(fout2.Data()); 
  for(int i=0; i<NumOfSegBH2; i++){
    fout_2 << a_bh2u[i] << endl;
  }     
}


//int main(int argc, char** argv){
//  TROOT root("GUI","GUI");   
//  TApplication theApp("App",&argc,argv);
//  TDCcalib();
//  theApp.Run();
//  return 0;
//}  
