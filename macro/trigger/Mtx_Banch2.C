#include <iostream>
#include <string>
#include <vector>

#include <fstream>
#include <TApplication.h>
#include <TROOT.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TString.h>
#include <TTree.h>
#include <TFile.h>
#include <TSystem.h>
#include <TH1.h>
#include <TH2.h>

//using namespace std;

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
  "dec"
};

const char* TriggerFlag[]=
{
  "Bh21K     ",
  "Bh22K     ",
  "Bh23K     ",
  "Bh24K     ",
  "Bh25K     ",
  "Bh26K     ",
  "Bh27K     ",
  "Bh28K     ",
  "Bh2K      ",
  "ElseOr    ",
  "Beam      ",
  "BeamTof   ",
  "BeamPi    ",
  "BeamP     ",
  "Coin1     ",
  "Coin2     ",
  "E03       ",
  "Bh2KPs    ",
  "BeamPs    ",
  "BeamTofPs ",
  "BeamPiPs  ",
  "BeamPPs   ",
  "Coin1Ps   ",
  "Coin2Ps   ",
  "E03Ps     ",
  "Clock     ",
  "Reserve2  ",
  "SpillEnd  ",
  "Matrix    ",
  "MstAccept ",
  "MstClear  ",
  "TofTiming "
};

bool eq3(int a,int b,int c){
  if( a!= b ) return false;
  if( b!= c ) return false;
  if( c!= a ) return false;

  return true;
}

void Mtx_Banch2(int month, int runnum, int filesel=1){

  gStyle->SetOptTitle(0);
  gStyle->SetLabelSize(0.04,"XYZ");
  gStyle->SetTitleSize(0.05,"XYZ");
  gStyle->SetTitleOffset(1.2,"X");
  gStyle->SetTitleOffset(1.3,"Y");
  gStyle->SetPadLeftMargin(0.16);
  gStyle->SetPadBottomMargin(0.16);
  
  //Matrix Patern txt file PATH -----------------------------------------------------------------------
  TString anadir=Form("%s/work/e40/ana",std::getenv("HOME")); 
  TString filein1=Form("%s/analyzer_%s/param/MATRIXSFT/SFT_table.txt.2018Jun.3_1",anadir.Data(),Month[month] ); 

  std::ifstream fin1(filein1);

  // Param Vector Dif ----------------------------------------------------------------------
  std::vector<std::vector<int>> Mtx_prm; 
  std::string line;
  int preSCH = 0;
  std::vector<std::vector<int>> sch_tof; 
  std::vector<int> SCH_Seg; 
  std::vector<int> TOF_Min; 
  std::vector<int> TOF_Max; 


  // Error Out ----------------------------------------------------------------------------------------
  if(fin1.fail() ){
    std::cerr << "file1" << std::endl;
    exit(0); 
  }  

  if( !eq3(SCH_Seg.size(),TOF_Min.size(),TOF_Max.size()) ){
    std::cerr << "Size Not Same" << std::endl;
  }

  while(std::getline(fin1, line)){
    double sch=-1, tof=-1, sft_min=-1, sft_max=-1;
    std::istringstream input_line( line );
    std::vector<int> inner;
    if( input_line >> sch >> tof >> sft_min >> sft_max ){
      inner.push_back(sch);
      inner.push_back(tof);
      if((int)sft_min%32==0){
        inner.push_back(sft_min-10);
      }else{
        inner.push_back(sft_min-11);
      }
      inner.push_back(sft_max-1);
      Mtx_prm.push_back(inner);
    }
  }

  //  for(int i=0; i<Mtx_prm.size(); i++){
  //    if(i==0){
  //      SCH_Seg.push_back( Mtx_prm.at(i).at(0) );
  //      TOF_Min.push_back( Mtx_prm.at(i).at(1) );
  //    }else{
  //      if(i==Mtx_prm.size()-1){
  //        TOF_Max.push_back( Mtx_prm.at(i).at(1) );
  //      }else if(Mtx_prm.at(i).at(0)!=Mtx_prm.at(i-1).at(0)){
  //        SCH_Seg.push_back( Mtx_prm.at(i).at(0) );
  //        TOF_Max.push_back( Mtx_prm.at(i-1).at(1) );
  //        TOF_Min.push_back( Mtx_prm.at(i).at(1) );
  //      }
  //    }
  //  }

  gStyle->SetOptStat(1111110); 
  gStyle->SetOptFit(1); 


  //Reset ROOT and connect tree file
  gROOT->Reset();
  //   TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("rootfile/run05126_DstKuramaEasirocHodoscope.root");
  //  TString anadir=Form("%s/work/e40/ana",std::getenv("HOME")); 
  TString pdf = Form("%s/pdf/trigger/Mtx_Banch2_run%05d_%d.pdf", anadir.Data(),runnum,filesel);
  TString pdfDhire = Form("%s/pdf/trigger", anadir.Data());
  TFile *f;
  if(filesel==1){
    //    TFile *f = new TFile(Form("%s/analyzer_%s/rootfile/run%05d_Matrix.root", anadir.Data(),Month[month], runnum),"READ");
    f = new TFile(Form("%s/analyzer_%s/rootfile/run%05d_DstPiKAna2.root", anadir.Data(),Month[month], runnum),"READ");
  }else{
    f = new TFile(Form("%s/analyzer_%s/rootfile%d/run%05d_DstPiKAna2.root", anadir.Data(),Month[month],filesel, runnum),"READ");
  }
  TTree *pik;
  f->GetObject("pik",pik);

  //Declaration of leaves types
  Int_t           evnum;
  Int_t           trigflag[32];
  Double_t        tofmt[24][16];
  Double_t        sch_time[64][16];
  Int_t           sch_depth[64];
  Double_t        sftx_utime[256][16];
  Double_t        sftx_dtime[256][16];
  Int_t           sftx_udepth[256];
  Int_t           sftx_ddepth[256];
  Double_t        vtx[12];
  Double_t        vty[12];
  Double_t        vtz[12];
  Double_t        MissMass[12];
  Int_t           ntKurama;
  Double_t        chisqrKurama[4];
  Double_t        pKurama[4];
  Double_t        qKurama[4];
  Double_t        m2[4];

  // Set branch atatus.
  pik->SetBranchStatus("*",0);  // disable all branches
  pik->SetBranchStatus("evnum");
  pik->SetBranchStatus("trigflag");
  pik->SetBranchStatus("tofmt");
  pik->SetBranchStatus("sch_time");
  pik->SetBranchStatus("sch_depth");
  pik->SetBranchStatus("sftx_utime");
  pik->SetBranchStatus("sftx_dtime");
  pik->SetBranchStatus("sftx_udepth");
  pik->SetBranchStatus("sftx_ddepth");
  pik->SetBranchStatus("ntKurama");
  pik->SetBranchStatus("chisqrKurama");
  pik->SetBranchStatus("pKurama");
  pik->SetBranchStatus("qKurama");
  pik->SetBranchStatus("m2");
  pik->SetBranchStatus("vtx");
  pik->SetBranchStatus("vty");
  pik->SetBranchStatus("vtz");
  pik->SetBranchStatus("MissMass");


  // Set branch addresses.
  pik->SetBranchAddress("evnum",&evnum);
  pik->SetBranchAddress("trigflag",trigflag);
  pik->SetBranchAddress("tofmt",tofmt);
  pik->SetBranchAddress("sch_time",sch_time);
  pik->SetBranchAddress("sch_depth",sch_depth);
  pik->SetBranchAddress("sftx_utime",sftx_utime);
  pik->SetBranchAddress("sftx_dtime",sftx_dtime);
  pik->SetBranchAddress("sftx_udepth",sftx_udepth);
  pik->SetBranchAddress("sftx_ddepth",sftx_ddepth);
  pik->SetBranchAddress("ntKurama",&ntKurama);
  pik->SetBranchAddress("chisqrKurama",chisqrKurama);
  pik->SetBranchAddress("pKurama",pKurama);
  pik->SetBranchAddress("qKurama",qKurama);
  pik->SetBranchAddress("m2",m2);
  pik->SetBranchAddress("vtx",vtx);
  pik->SetBranchAddress("vty",vty);
  pik->SetBranchAddress("vtz",vtz);
  pik->SetBranchAddress("MissMass",MissMass);


  //-para def-----------------------------------------------------------------------------------------
  double HULMHTDCCalib = -0.8333;
  double MaxBinValue=0.;

//  int nGate = 9;
//  int Gate[] = {1,5,10,15,20,30,40,60,120};
//  double Gate_d[] = {1.,5.,10.,15.,20.,30.,40.,60.,120.};

  int nGate = 15;
//  int Gate[] = {1,5,10,15,20,30,40,60,120};
  int  Gate[] = {1,5,10,15,20,30,40,50,60,70,80,90,100,110,120};
  double Gate_d[] = {1.,5.,10.,15.,20.,30.,40.,50.,60.,70.,80.,90.,100.,110.,120.};

  double TofMid = 10.;
  double SchMid = 0.;
  double SftMid = 0.;

  int Hist1Max = 0;
  int Hist2Max = 0;

  Long64_t SigmaCount = 0;
  int Count1[nGate+1];
  int Count1_Sigma[nGate+1];
  double MtxEfficiency[nGate];
  double MtxEfficiency_Sigma[nGate];
  double x[nGate];
  for(int n=0; n<nGate; n++){
    Count1[n] = 0;
    Count1_Sigma[n] = 0;
    MtxEfficiency[n] = 0.;
    MtxEfficiency_Sigma[n] = 0.;
    x[n] = (double)nGate - (double)n -1.;
  }
  Count1[nGate] = 0;
  Count1_Sigma[nGate] = 0;


  //-hist def-----------------------------------------------------------------------------------------
  Hist1Max = 9+nGate*4+2;
  TH1D *Hist1[Hist1Max];


  //-Tof ----------------
  Hist1[0] = new TH1D("TofMtOr Hitpat","TofMtOr Hitpat",25,0,24);
  Hist1[1] = new TH1D("TofMtOr DepthPat","TofMtOrDepthPat",20,0,20);
  Hist1[2] = new TH1D("TofMtOr","TofMtOr",200,-100,100);
  Hist1[3]= new TH1D("Sch Depthpat","Sch Depthpat",65,0,65);
  Hist1[4]= new TH1D("Sch Time"   ,"Sch Time"   ,200,-100,100);
  Hist1[5] = new TH1D("SftX U Time","SftX U Time",200,-100,100);
  Hist1[6] = new TH1D("SftX D Time","SftX D Time",200,-100,100);
  Hist1[7] = new TH1D("SftXTime","SftXTime",200,-100,100);
  Hist1[8] = new TH1D("MissMass Sigma","MissMass Sigma",100,0.8,1.4);

  //-Sch ----------------
  for(int i=0; i<nGate; i++){
    Hist1[9+nGate*0+i] = new TH1D(Form("TofMtOr %dnsGate",Gate[i]),Form("TofMtOr %dnsGate",Gate[i]),200,-100,100);
    Hist1[9+nGate*1+i] = new TH1D(Form("Sch Time %dnsGate",Gate[i]),Form("Sch Time %dnsGate",Gate[i]),200,-100,100);
    Hist1[9+nGate*2+i] = new TH1D(Form("SftX Time %dnsGate",Gate[i]),Form("SftX Time %dnsGate",Gate[i]),200,-100,100);
    Hist1[9+nGate*3+i] = new TH1D(Form("MissMass Sigma %dnsGate",Gate[i]),Form("MissMass Sigma %dnsGate",Gate[i]),100,0.8,1.4);
    }
  //-SftX ----------------

  Hist1[9+nGate*4+0] = new TH1D("MissMass Sigma vtx & K","MissMass Sigma vtx & K",100,0.8,1.4);
  Hist1[9+nGate*4+1] = new TH1D("MissMass Sigma vtx & K & MissMass","MissMass Sigma vtx & K & MissMass",100,0.8,1.4);

  //-Event Loop --------------------------------------------------------------------------------------
//  Long64_t nentries = pik->GetEntries();
    Long64_t nentries =10000;

  for (Long64_t s=0; s<nentries;s++){
    pik->GetEntry(s);
    if(s%(nentries/10) ==0){
      std::cout << ( ((double)s)/nentries *100 ) << "%\t" << s << "/" << nentries << "\r"  << std::endl;
    }

    bool TofFlag = false;
    // TofMtOr ----------------------------
    for(int i=0; i<NumOfSegTOF; i++){
      for(int j=0; j<16; j++){
        if(tofmt[i][j]==-999)   continue;
        Hist1[0]->Fill(i);
        Hist1[1]->Fill(j);
        Hist1[2]->Fill(tofmt[i][j]);
      }
    }

    // Sch --------------------------------
    for(int i=0; i<NumOfSegSCH; i++){
      Hist1[3]->Fill(sch_depth[i]);
      for(int k=0; k<16; k++){
        if(sch_time[i][k]==-999) continue;
        Hist1[4]->Fill(sch_time[i][k]);
      }
    }

    // Sft X ------------------------------
    for(int i=0; i<NumOfSegSFT_X; i++){
      for(int j=0; j<16; j++){
        if(sftx_utime[i][j]!=-999){
          Hist1[5]->Fill(sftx_utime[i][j]);
          Hist1[7]->Fill(sftx_utime[i][j]);
        }
        if(sftx_dtime[i][j]!=-999){
          Hist1[6]->Fill(sftx_dtime[i][j]);
          Hist1[7]->Fill(sftx_dtime[i][j]);
        }
      }
    }

    bool Flag[nGate+1];
    bool Flag1[nGate+1];
    bool Flag2[nGate+1];
    bool Flag3[nGate+1];
    bool Flag_Sigma[nGate+1];
    bool Flag1_Sigma[nGate+1];
    bool Flag2_Sigma[nGate+1];
    bool Flag3_Sigma[nGate+1];
    for(int n=0; n<nGate+1; n++){
      Flag[n] = false;
      Flag1[n] = false;
      Flag2[n] = false;
      Flag3[n] = false;
      Flag_Sigma[n] = false;
      Flag1_Sigma[n] = false;
      Flag2_Sigma[n] = false;
      Flag3_Sigma[n] = false;
    }

    // Mtx Pattern ----------------------------
    if(ntKurama==1&&chisqrKurama[0]<50){ 
      if(m2[0]>0.15 && m2[0]<0.35 && qKurama[0]>0 && pKurama[0]<0.9){ 
        Hist1[8]->Fill(MissMass[0]);
        if( vtx[0]>-20 && vtx[0]<20 && vty[0]>-20 && vty[0]<20 && vtz[0]>-200 && vtz[0]<200 ){
          Hist1[9+nGate*4+0]->Fill(MissMass[0]);
          if(MissMass[0]>1.15&&MissMass[0]<1.25){
            Hist1[9+nGate*4+1]->Fill(MissMass[0]);
            SigmaCount+=1;
            for(int l=0; l < Mtx_prm.size(); l++){
              int i = 0;
              int j = 0;
              int min = 0;
              int max = 0;
              i = Mtx_prm.at(l).at(1);
              j = Mtx_prm.at(l).at(0);
              min = Mtx_prm.at(l).at(2);
              max = Mtx_prm.at(l).at(3) + 1;
              for(int m=0; m<16 ;m++){
                if( tofmt[i][m] != -999.0 ){ 
                  Flag1[nGate]=true;
                  if(trigflag[28]>0) Flag1_Sigma[nGate]=true;
                }
              }
              for(int m=0; m<sch_depth[j] ;m++){
                if( sch_time[j][m]!= -999. ){
                  Flag2[nGate]=true;
                  if(trigflag[28]>0) Flag2_Sigma[nGate]=true;
                }
              }
              for(int k = min; k < max; k++){
                for(int m=0; m<sftx_udepth[k] ;m++){
                  if( sftx_utime[k][m] != -999. ){
                    Flag3[nGate]=true;
                    if(trigflag[28]>0) Flag3_Sigma[nGate]=true;
                  }
                }
                for(int m=0; m<sftx_ddepth[k] ;m++){
                  if( sftx_dtime[k][m] != -999. ){
                    Flag3[nGate]=true;
                    if(trigflag[28]>0) Flag3_Sigma[nGate]=true;
                  }
                }
              }
              for(int n=0; n<nGate; n++){
                for(int m=0; m<16 ;m++){
                  if( tofmt[i][m]      > (double)TofMid - Gate[n] && tofmt[i][m]     < (double)TofMid + Gate[n] ){ 
                    Hist1[9+nGate*0+n]->Fill(tofmt[i][m]);
                    Flag1[n]=true;
                    if(trigflag[28]>0) Flag1_Sigma[n]=true;
                  }
                }
                for(int m=0; m<sch_depth[j] ;m++){
                  if( sch_time[j][m]   > (double)SchMid - Gate[n] && sch_time[j][m]  < (double)SchMid + Gate[n] ){
                    Hist1[9+nGate*1+n]->Fill(sch_time[j][m]);
                    Flag2[n]=true;
                    if(trigflag[28]>0) Flag2_Sigma[n]=true;
                  }
                }
                for(int k = min; k < max; k++){
                  for(int m=0; m<sftx_udepth[k] ;m++){
                    if( sftx_utime[k][m] > (double)SftMid - Gate[n] && sftx_utime[k][m]< (double)SftMid + Gate[n] ){
                      Hist1[9+nGate*2+n]->Fill(sftx_utime[k][m]);
                      Flag3[n]=true;
                      if(trigflag[28]>0) Flag3_Sigma[n]=true;
                    }
                  }
                  for(int m=0; m<sftx_ddepth[k] ;m++){
                    if( sftx_dtime[k][m] > (double)SftMid - Gate[n] && sftx_dtime[k][m]< (double)SftMid + Gate[n] ){ 
                      Hist1[9+nGate*2+n]->Fill(sftx_dtime[k][m]);
                      Flag3[n]=true;
                      if(trigflag[28]>0) Flag3_Sigma[n]=true;
                    }
                  }
                }
              }
              for(int n=0; n<nGate+1; n++){
                if(Flag1[n]&&Flag2[n]&&Flag3[n]){
                  Flag[n]=true;
                }
                if(Flag1_Sigma[n]&&Flag2_Sigma[n]&&Flag3_Sigma[n]){
                  Flag_Sigma[n]=true;
                }
              }
              for(int n=0; n<nGate+1; n++){
                Flag1[n] = false;
                Flag2[n] = false;
                Flag3[n] = false;
                Flag1_Sigma[n] = false;
                Flag2_Sigma[n] = false;
                Flag3_Sigma[n] = false;
              }
            }
          }
        }
      }
    }

    for(int n=0; n<nGate+1; n++){
      if(Flag[n]){
        Count1[n]+=1;
      }
      if(Flag_Sigma[n]){
        Count1_Sigma[n]+=1;
      }
    }
  }

  //-Canvas def---------------------------------------------------------------------------------------
  TCanvas *c1 = new TCanvas("c1","c1",1200,900);
  //-Hist Draw----------------------------------------------------------------------------------------

  c1->Print(pdf+"["); 
  c1->cd();
  for(int i=0; i<Hist1Max; i++){
    Hist1[i]->Draw();
    c1->Print(pdf);
    c1->Print(Form("%s/Mtx_Banch2_run%05d_Hist1_%03d_%d.pdf",pdfDhire.Data(),runnum,i, filesel));
  }

  for(int n=0; n<nGate; n++){
    MtxEfficiency[n]= (double)Count1[n]/Count1[nGate];
    std::cout << "Total Event# is " << Count1[nGate] << "\t" << Form("Count%d# is ",n+1) << Count1[n] << "\t" << "Efficiency is " << MtxEfficiency[n] << std::endl;
  }
  for(int n=0; n<nGate; n++){
    MtxEfficiency_Sigma[n]= (double)Count1_Sigma[n]/ Count1_Sigma[nGate];
    std::cout << "Total Event# is " << SigmaCount << "\t" << Form("Count%d_Sigma# is ",nGate) << Count1_Sigma[nGate]  << "\t" << Form("Count%d_Sigma# is ",n+1) << Count1_Sigma[n] << "\t" << "Efficiency is " << MtxEfficiency_Sigma[n] << std::endl;
  }

  c1->SetGrid();
  c1->SetGridx();
  c1->SetGridy();

  TGraph *g1 = new TGraph(nGate, x, MtxEfficiency);
  TGraph *g2 = new TGraph(nGate, x, MtxEfficiency_Sigma);
  TGraph *g3 = new TGraph(nGate, Gate_d, MtxEfficiency_Sigma);
  g1->SetMarkerStyle(8);
  g1->SetMarkerColor(2);
  g1->SetMarkerSize(2);
  g1->GetXaxis()->SetRangeUser(0,nGate - 0.5);
  g1->GetYaxis()->SetRangeUser(0,1);
  g1->Draw("AP");

  c1->Print(pdf);
  c1->Print(Form("%s/Mtx_Banch2_run%05d_Graph_%d.pdf",pdfDhire.Data(),runnum, filesel));

  g2->SetMarkerStyle(8);
  g2->SetMarkerColor(2);
  g2->SetMarkerSize(2);
  g2->GetXaxis()->SetRangeUser(0,nGate - 0.5);
  g2->GetYaxis()->SetRangeUser(0,1);
  g2->Draw("AP");

  c1->Print(pdf);
  c1->Print(Form("%s/Mtx_Banch2_run%05d_Graph_Sigma_%d.pdf",pdfDhire.Data(),runnum, filesel));

  g3->SetMarkerStyle(8);
  g3->SetMarkerColor(1);
  g3->SetMarkerSize(2);
  g3->GetXaxis()->SetRangeUser(0,Gate[nGate-1]+10);
  g3->GetYaxis()->SetRangeUser(0,1);
  g3->GetXaxis()->SetTitle("Gate [ns]");
  g3->GetYaxis()->SetTitle("Efficiency");
  g3->GetYaxis()->SetDecimals(2);
  g3->Draw("AP");

  c1->Print(pdf);
  c1->Print(Form("%s/Mtx_Banch2_run%05d_Graph_Sigma_Gate_%d.pdf",pdfDhire.Data(),runnum, filesel));

  g3->GetYaxis()->SetRangeUser(0.9,1);
  g3->Draw("AP");
  c1->Print(pdf);
  c1->Print(Form("%s/Mtx_Banch2_run%05d_Graph_Sigma_Gate_zoom_%d.pdf",pdfDhire.Data(),runnum, filesel));

  std::ofstream fout1;
  fout1.open(Form("%s/dat/trigger/SigmaEffi.txt", anadir.Data()));
  for(int i=0; i<nGate; i++){
    fout1 << MtxEfficiency_Sigma[i] << std::endl;
  }

  c1->Print(pdf+"]"); 

}

