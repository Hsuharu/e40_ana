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


void DCTDCParamMaker( int month, int runnum){
  gStyle->SetOptStat(1111110); 
  gStyle->SetOptFit(1); 

//Recchar *monthhar *monthset ROOT and connect tree file
   gROOT->Reset();
   TString anadir=Form("%s/work/e40/ana",std::getenv("HOME")); 
   TFile *f = new TFile(Form("%s/analyzer_%s/rootfile/run%05d_BcOutTracking.root", anadir.Data(),Month[month], runnum),"READ");
   if (!f) {
      f = new TFile(Form("%s/rootfile/run%05d_BcOutTracking.root", anadir.Data() , runnum));
   }

//Make Hist
  TH1F *BcOut[PlMaxBcIn]; 

/////////////////////////////////////////////////////////////////////
//   BH1 U/D                                                       //
/////////////////////////////////////////////////////////////////////
  for(int i=0; i<NumOfSegBH1; i++){
    if(i<9){  
     BH1_U[i] = (TH1F*)file->Get(Form("h%d0%d0%d",BH1,i+1,ADC_U)) ; 
     BH1_D[i] = (TH1F*)file->Get(Form("h%d0%d0%d",BH1,i+1,ADC_D)) ; 
    }else{   
     BH1_U[i] = (TH1F*)file->Get(Form("h%d%d0%d",BH1,i+1,ADC_U))  ;
     BH1_D[i] = (TH1F*)file->Get(Form("h%d%d0%d",BH1,i+1,ADC_D))  ;
    }  
  }  
