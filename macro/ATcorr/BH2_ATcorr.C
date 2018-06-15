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


void BH2_ATcorr( int month, int runnum){
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
//   TFile *f = new TFile(Form("%s/analyzer_%s/rootfile/run%05d_Hodoscope.root", anadir.Data(),Month[month], runnum),"READ");
   if (!f) {
      f = new TFile(Form("%s/rootfile/run%05d_Hodoscope.root", anadir.Data() , runnum));
   }

  double l = 30;
  double l_t = 100;

  int BH1 = 1;
  int NumOfSegBH1 = 11; 

  int BH2 = 2;
  int NumOfSegBH2 = 8; 

  int TOF = 4;
  int NumOfSegTOF = 24; 

  int ADC_U = 3; 
  int ADC_D = 4;

  int tdc_u = 3; 
  int tdc_d = 4;

  int t_u = 27; 
  int t_d = 28;

  TH2F *BH2_U[NumOfSegBH2]; 
  TH2F *BH2_D[NumOfSegBH2]; 

  TF1 *fit = new TF1("fit","gaus"); 
   
/////////////////////////////////////////////////////////////////////
//   BH1 U/D                                                       //
/////////////////////////////////////////////////////////////////////
  for(int i=0; i<NumOfSegBH2; i++){
     BH2_U[i] = (TH2F*)f->Get(Form("h%d0%d%d",BH2,i+1,t_u)) ; 
     BH2_D[i] = (TH2F*)f->Get(Form("h%d0%d%d",BH2,i+1,t_d)) ; 
  }  

   
   TString pdf = Form("%s/pdf/ATcorr/BH2corr_%05d.pdf", anadir.Data(),runnum);
   TCanvas *c1 = new TCanvas("c1","c1",800,700); 
   c1->Print(pdf+"["); 

  for(int i=0; i<NumOfSegBH2; i++){
    BH2_U[i]->Draw("colz") ; 
    c1->Print(pdf);        
    BH2_D[i]->Draw("colz") ; 
    c1->Print(pdf);        
  }  

                             
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
//
//  TString fout3 = (Form( "%s/hp_dat/HodoParamMaker1_BH2_TDC_%05d.dat", anadir.Data() ,runnum));  
//  TString fout4 = (Form( "%s/hp_dat/HodoParamMaker1_BH2_ADC_%05d.dat", anadir.Data() ,runnum));  
//   
//  std::ofstream fout_3(fout3.Data()); 
//  std::ofstream fout_4(fout4.Data()); 
//  for(int i=0; i<NumOfSegBH2; i++){
//     fout_3 << bh2utprm[i]  <<  "\t"  << bh2dtprm[i] << endl;
//     fout_4 << bh2ubgprm[i]  <<  "\t" << bh2umipprm[i]  <<  "\t" << bh2dbgprm[i]  <<  "\t" << bh2dmipprm[i] << endl;
//  }     

                             
}                            
                             
