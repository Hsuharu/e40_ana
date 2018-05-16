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


#include "DetectorID.hh"


//using namespace std;


void TDCcalib(int runnum){
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


   TH1D *BH1UT[NumOfSegBH1]; 
   TH1D *BH1DT[NumOfSegBH1]; 
      for (int i=0; i<NumOfSegBH1;i++) {
        BH1UT[i] = new TH1D(Form("BH1UT%d",i+1),Form("BH1UT%d",i+1),4000,0,4000);
        BH1DT[i] = new TH1D(Form("BH1DT%d",i+1),Form("BH1DT%d",i+1),4000,0,4000);
      }

   TH1D *BH2UT[NumOfSegBH2]; 
   TH1D *BH2DT[NumOfSegBH2]; 
      for (int i=0; i<NumOfSegBH2;i++) {
        BH2UT[i] = new TH1D(Form("BH2UT%d",i+1),Form("BH2UT%d",i+1),4000,0,4000);
        BH2DT[i] = new TH1D(Form("BH2DT%d",i+1),Form("BH2DT%d",i+1),4000,0,4000);
      }

   TH1D *TOFUT[NumOfSegTOF]; 
   TH1D *TOFDT[NumOfSegTOF]; 
      for (int i=0; i<NumOfSegTOF;i++) {
        TOFUT[i] = new TH1D(Form("TOFUT%d",i+1),Form("TOFUT%d",i+1),4000,0,4000);
        TOFDT[i] = new TH1D(Form("TOFDT%d",i+1),Form("TOFDT%d",i+1),4000,0,4000);
      }

   Long64_t nentries = tree->GetEntries();

   TF1 *fit = new TF1("fit","gaus"); 
   TF1 *polone; 

   Long64_t nbytes = 0;
   for (Long64_t i=0; i<nentries;i++) {
      nbytes += tree->GetEntry(i);
      for (int i=0; i<NumOfSegBH1;i++) {
        if(bh1ut[i]>0 && bh1ut[i]<2100){  
          BH1UT[i]->Fill(bh1ut[i]);
        }
        if(bh1dt[i]>0 && bh1dt[i]<2100){  
          BH1DT[i]->Fill(bh1dt[i]);
        }
      }

      for (int i=0; i<NumOfSegBH2;i++) {
        if(bh2ut[i]>0 && bh2ut[i]<2100){  
          BH2UT[i]->Fill(bh2ut[i]);
        }
        if(bh2dt[i]>0 && bh2dt[i]<2100){  
          BH2DT[i]->Fill(bh2dt[i]);
        }
      }

      for (int i=0; i<NumOfSegTOF;i++) {
        if(tofut[i]>0 && tofut[i]<2200){  
          TOFUT[i]->Fill(tofut[i]);
        }
        if(tofdt[i]>0 && tofdt[i]<2150){  
          TOFDT[i]->Fill(tofdt[i]);
        }
      }
   }

   TCanvas *c1 = new TCanvas("c1","c1",800,700); 
   TCanvas *c2 = new TCanvas("c2","c2",800,700); 
   TCanvas *c3 = new TCanvas("c3","c3",800,700); 
   TCanvas *c4 = new TCanvas("c4","c4",800,700); 
   TCanvas *c5 = new TCanvas("c5","c5",800,700); 
   TCanvas *c6 = new TCanvas("c6","c6",800,700); 
       c1->Divide(4,3);
       c2->Divide(4,3);
       c3->Divide(4,2);
       c4->Divide(4,2);
       c5->Divide(6,4);
       c6->Divide(6,4);

   TCanvas *c11 = new TCanvas("c11","c11",800,700); 
   TCanvas *c12 = new TCanvas("c12","c12",800,700); 
   TCanvas *c13 = new TCanvas("c13","c13",800,700); 
   TCanvas *c14 = new TCanvas("c14","c14",800,700); 
   TCanvas *c15 = new TCanvas("c15","c15",800,700); 
   TCanvas *c16 = new TCanvas("c16","c16",800,700); 
       c11->Divide(4,3);
       c12->Divide(4,3);
       c13->Divide(4,2);
       c14->Divide(4,2);
       c15->Divide(6,4);
       c16->Divide(6,4);
   
   TString pdf = Form("%s/pdf/trigger_study/TDCcalib_%05d.pdf", anadir.Data(),runnum);
   c1->Print(pdf+"["); 

   int npeaks = 7;
   int nfound = 0;
   int l = 3;
   double y[npeaks];   
   double err_y[npeaks];   
   for(int i=0; i<npeaks; i++){
     y[i]=i*10;   
     err_y[i]=0.01;   
   }  

   TSpectrum *s_bh1;
   std::vector< std::vector<double> >  p_bh1u (NumOfSegBH1, std::vector<double>(npeaks) ) ; 
   std::vector< std::vector<double> >  p_bh1d (NumOfSegBH1, std::vector<double>(npeaks) ) ; 
   std::vector< std::vector<double> >  err_bh1u (NumOfSegBH1, std::vector<double>(npeaks) ) ; 
   std::vector< std::vector<double> >  err_bh1d (NumOfSegBH1, std::vector<double>(npeaks) ) ; 

   TGraphErrors *ger_bh1u[NumOfSegBH1]; 
   double a_bh1u[npeaks];   
   double b_bh1u[npeaks];   

   TGraphErrors *ger_bh1d[NumOfSegBH1]; 
   double a_bh1d[npeaks];   
   double b_bh1d[npeaks];   

   for (int i=0; i<NumOfSegBH1;i++) {
       s_bh1 = new TSpectrum(npeaks);  
       c1->cd(i+1);
       BH1UT[i]->Draw(); 
       nfound = s_bh1->Search(BH1UT[i],2,"",0.010); 
       for(int j=0; j<nfound; j++){
         p_bh1u[i][j] = s_bh1 ->GetPositionX()[j];
         BH1UT[i]->Fit("fit","","", p_bh1u[i][j]-l, p_bh1u[i][j]+l);  
         p_bh1u[i][j] = fit->GetParameter(1);
         err_bh1u[i][j] = fit->GetParError(1);
         fit -> Draw("sames"); 
       }  
       std::sort(&p_bh1u[i][0],&p_bh1u[i][npeaks]); 
       c11->cd(i+1);
       ger_bh1u[i] = new TGraphErrors(nfound, &(p_bh1u[i][0]), y, &(err_bh1u[i][0]),err_y);  
       ger_bh1u[i]->SetMarkerStyle(8);
       ger_bh1u[i]->Draw();
       ger_bh1u[i]->Fit("pol1","","");  
       gStyle->SetOptFit(1);
       polone = ger_bh1u[i]->GetFunction("pol1");  
       a_bh1u[i] = polone->GetParameter(1);   
       b_bh1u[i] = polone->GetParameter(0);   
       ger_bh1u[i]->GetXaxis()->SetTitle(Form("TDC_U%d[ch]",i+1));   
       ger_bh1u[i]->GetYaxis()->SetTitle("time[ns] ");   
    
       c2->cd(i+1);
       BH1DT[i]->Draw(); 
       nfound = s_bh1->Search(BH1DT[i],2,"",0.010); 
       for(int j=0; j<nfound; j++){
         p_bh1d[i][j] = s_bh1 ->GetPositionX()[j];
         BH1DT[i]->Fit("fit","","", p_bh1d[i][j]-l, p_bh1d[i][j]+l);  
         p_bh1d[i][j] = fit->GetParameter(1);
         err_bh1d[i][j] = fit->GetParError(1);
         fit -> Draw("sames"); 
       }  
       std::sort(&p_bh1d[i][0],&p_bh1d[i][npeaks]); 
       c12->cd(i+1);
       ger_bh1d[i] = new TGraphErrors(nfound, &(p_bh1d[i][0]), y, &(err_bh1d[i][0]),err_y);  
       ger_bh1d[i]->SetMarkerStyle(8);
       ger_bh1d[i]->Draw();
       ger_bh1d[i]->Fit("pol1","","");  
       gStyle->SetOptFit(1);
       polone = ger_bh1d[i]->GetFunction("pol1");  
       a_bh1d[i] = polone->GetParameter(1);   
       b_bh1d[i] = polone->GetParameter(0);   
       ger_bh1d[i]->GetXaxis()->SetTitle(Form("TDC_D%d[ch]",i+1));   
       ger_bh1d[i]->GetYaxis()->SetTitle("time[ns] ");   

   }
   c1->Print(pdf); 
   c2->Print(pdf); 
   c11->Print(pdf); 
   c12->Print(pdf); 

   TSpectrum *s_bh2;
   std::vector< std::vector<double> >  p_bh2u (NumOfSegBH2, std::vector<double>(npeaks) ) ; 
   std::vector< std::vector<double> >  p_bh2d (NumOfSegBH2, std::vector<double>(npeaks) ) ; 
   std::vector< std::vector<double> >  err_bh2u (NumOfSegBH2, std::vector<double>(npeaks) ) ; 
   std::vector< std::vector<double> >  err_bh2d (NumOfSegBH2, std::vector<double>(npeaks) ) ; 

   TGraphErrors *ger_bh2u[NumOfSegBH2]; 
   double a_bh2u[npeaks];   
   double b_bh2u[npeaks];   

   TGraphErrors *ger_bh2d[NumOfSegBH2]; 
   double a_bh2d[npeaks];   
   double b_bh2d[npeaks];   

   for (int i=0; i<NumOfSegBH2;i++) {
       s_bh2 = new TSpectrum(npeaks);  
       c3->cd(i+1);
       BH2UT[i]->Draw(); 
       nfound = s_bh2->Search(BH2UT[i],2,"",0.010); 
       for(int j=0; j<nfound; j++){
         p_bh2u[i][j] = s_bh2 ->GetPositionX()[j];
         BH2UT[i]->Fit("fit","","", p_bh2u[i][j]-l, p_bh2u[i][j]+l);  
         p_bh2u[i][j] = fit->GetParameter(1);
         err_bh2u[i][j] = fit->GetParError(1);
         fit -> Draw("sames"); 
       }  
       std::sort(&p_bh2u[i][0],&p_bh2u[i][npeaks]); 
       c13->cd(i+1);
       ger_bh2u[i] = new TGraphErrors(nfound, &(p_bh2u[i][0]), y, &(err_bh2u[i][0]),err_y);  
       ger_bh2u[i]->SetMarkerStyle(8);
       ger_bh2u[i]->Draw();
       ger_bh2u[i]->Fit("pol1","","");  
       gStyle->SetOptFit(1);
       polone = ger_bh2u[i]->GetFunction("pol1");  
       a_bh2u[i] = polone->GetParameter(1);   
       b_bh2u[i] = polone->GetParameter(0);   
       ger_bh2u[i]->GetXaxis()->SetTitle(Form("TDC_U%d[ch]",i+1));   
       ger_bh2u[i]->GetYaxis()->SetTitle("time[ns] ");   
    
       c4->cd(i+1);
       BH2DT[i]->Draw(); 
       nfound = s_bh2->Search(BH2DT[i],2,"",0.010); 
       for(int j=0; j<nfound; j++){
         p_bh2d[i][j] = s_bh2 ->GetPositionX()[j];
         BH2DT[i]->Fit("fit","","", p_bh2d[i][j]-l, p_bh2d[i][j]+l);  
         p_bh2d[i][j] = fit->GetParameter(1);
         err_bh2d[i][j] = fit->GetParError(1);
         fit -> Draw("sames"); 
       }  
       std::sort(&p_bh2d[i][0],&p_bh2d[i][npeaks]); 
       c14->cd(i+1);
       ger_bh2d[i] = new TGraphErrors(nfound, &(p_bh2d[i][0]), y, &(err_bh2d[i][0]),err_y);  
       ger_bh2d[i]->SetMarkerStyle(8);
       ger_bh2d[i]->Draw();
       ger_bh2d[i]->Fit("pol1","","");  
       gStyle->SetOptFit(1);
       polone = ger_bh2d[i]->GetFunction("pol1");  
       a_bh2d[i] = polone->GetParameter(1);   
       b_bh2d[i] = polone->GetParameter(0);   
       ger_bh2d[i]->GetXaxis()->SetTitle(Form("TDC_D%d[ch]",i+1));   
       ger_bh2d[i]->GetYaxis()->SetTitle("time[ns] ");   

   }
   c3->Print(pdf); 
   c4->Print(pdf); 
   c13->Print(pdf); 
   c14->Print(pdf); 
   
   
   TSpectrum *s_tof;
   std::vector< std::vector<double> >  p_tofu (NumOfSegTOF, std::vector<double>(npeaks) ) ; 
   std::vector< std::vector<double> >  p_tofd (NumOfSegTOF, std::vector<double>(npeaks) ) ; 
   std::vector< std::vector<double> >  err_tofu (NumOfSegTOF, std::vector<double>(npeaks) ) ; 
   std::vector< std::vector<double> >  err_tofd (NumOfSegTOF, std::vector<double>(npeaks) ) ; 

   TGraphErrors *ger_tofu[NumOfSegTOF]; 
   double a_tofu[npeaks];   
   double b_tofu[npeaks];   

   TGraphErrors *ger_tofd[NumOfSegTOF]; 
   double a_tofd[npeaks];   
   double b_tofd[npeaks];   

   for (int i=0; i<NumOfSegTOF;i++) {
       s_tof = new TSpectrum(npeaks);  
       c5->cd(i+1);
       TOFUT[i]->Draw(); 
       nfound = s_tof->Search(TOFUT[i],2,"",0.010); 
       for(int j=0; j<nfound; j++){
         p_tofu[i][j] = s_tof ->GetPositionX()[j];
         TOFUT[i]->Fit("fit","","", p_tofu[i][j]-l, p_tofu[i][j]+l);  
         p_tofu[i][j] = fit->GetParameter(1);
         err_tofu[i][j] = fit->GetParError(1);
         fit -> Draw("sames"); 
       }  
       std::sort(&p_tofu[i][0],&p_tofu[i][npeaks]); 
       c15->cd(i+1);
       ger_tofu[i] = new TGraphErrors(nfound, &(p_tofu[i][0]), y, &(err_tofu[i][0]),err_y);  
       ger_tofu[i]->SetMarkerStyle(8);
       ger_tofu[i]->Draw();
       ger_tofu[i]->Fit("pol1","","");  
       gStyle->SetOptFit(1);
       polone = ger_tofu[i]->GetFunction("pol1");  
       a_tofu[i] = polone->GetParameter(1);   
       b_tofu[i] = polone->GetParameter(0);   
       ger_tofu[i]->GetXaxis()->SetTitle(Form("TDC_U%d[ch]",i+1));   
       ger_tofu[i]->GetYaxis()->SetTitle("time[ns] ");   
    
       c6->cd(i+1);
       TOFDT[i]->Draw(); 
       nfound = s_tof->Search(TOFDT[i],2,"",0.010); 
       for(int j=0; j<nfound; j++){
         p_tofd[i][j] = s_tof ->GetPositionX()[j];
         TOFDT[i]->Fit("fit","","", p_tofd[i][j]-l, p_tofd[i][j]+l);  
         p_tofd[i][j] = fit->GetParameter(1);
         err_tofd[i][j] = fit->GetParError(1);
         fit -> Draw("sames"); 
       }  
       std::sort(&p_tofd[i][0],&p_tofd[i][npeaks]); 
       c16->cd(i+1);
       ger_tofd[i] = new TGraphErrors(nfound, &(p_tofd[i][0]), y, &(err_tofd[i][0]),err_y);  
       ger_tofd[i]->SetMarkerStyle(8);
       ger_tofd[i]->Draw();
       ger_tofd[i]->Fit("pol1","","");  
       gStyle->SetOptFit(1);
       polone = ger_tofd[i]->GetFunction("pol1");  
       a_tofd[i] = polone->GetParameter(1);   
       b_tofd[i] = polone->GetParameter(0);   
       ger_tofd[i]->GetXaxis()->SetTitle(Form("TDC_D%d[ch]",i+1));   
       ger_tofd[i]->GetYaxis()->SetTitle("time[ns] ");   

   }
   c5->Print(pdf); 
   c6->Print(pdf); 
   c15->Print(pdf); 
   c16->Print(pdf); 
   
   c1->Print(pdf+"]"); 

  TString fout1 = (Form( "%s/hp_dat/HodoParam_BH1_TDCcalib_%05d.dat", anadir.Data() ,runnum));  
  std::ofstream fout_1(fout1.Data()); 
  for(int i=0; i<NumOfSegBH1; i++){
      fout_1 << a_bh1u[i] << "\t" << a_bh1d[i]   << endl;
  }     

  TString fout2 = (Form( "%s/hp_dat/HodoParam_BH2_TDCcalib_%05d.dat", anadir.Data() ,runnum));  
  std::ofstream fout_2(fout2.Data()); 
  for(int i=0; i<NumOfSegBH2; i++){
    fout_2 << a_bh2u[i] << "\t" << a_bh2d[i]   << endl;
  }     

  TString fout3 = (Form( "%s/hp_dat/HodoParam_TOF_TDCcalib_%05d.dat", anadir.Data() ,runnum));  
  std::ofstream fout_3(fout3.Data()); 
  for(int i=0; i<NumOfSegTOF; i++){
    fout_3 << a_tofu[i] << "\t" << a_tofd[i]   << endl;
  }     
}


//int main(int argc, char** argv){
//  TROOT root("GUI","GUI");   
//  TApplication theApp("App",&argc,argv);
//  TDCcalib();
//  theApp.Run();
//  return 0;
//}  
