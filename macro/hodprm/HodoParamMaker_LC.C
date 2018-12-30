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
//
void HodoParamMaker_LC(int month, int runnum){
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
  //   TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("rootfile/run05126_DstKuramaEasirocHodoscope.root");
  TString anadir=Form("%s/work/e40/ana",std::getenv("HOME")); 
  TString pdf = Form("%s/pdf/hdprm/HodoParamMaker_LC_run%05d.pdf", anadir.Data(),runnum);
  TString pdfDhire = Form("%s/pdf/hdprm", anadir.Data());
  TFile *f = new TFile(Form("%s/analyzer_%s/rootfile/run%05d_Hodoscope.root", anadir.Data(),Month[month], runnum),"READ");
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
   double        lct[28][16];
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

  // Set branch atatus.
   tree->SetBranchStatus("*",0);  // disable all branches
   tree->SetBranchStatus("evnum");
   tree->SetBranchStatus("trignhits");
   tree->SetBranchStatus("trigpat");
   tree->SetBranchStatus("trigflag");
//   tree->SetBranchStatus("bh1nhits");
//   tree->SetBranchStatus("bh1hitpat");
//   tree->SetBranchStatus("bh1ua");
//   tree->SetBranchStatus("bh1ut");
//   tree->SetBranchStatus("bh1da");
//   tree->SetBranchStatus("bh1dt");
//   tree->SetBranchStatus("bh2nhits");
//   tree->SetBranchStatus("bh2hitpat");
//   tree->SetBranchStatus("bh2ua");
//   tree->SetBranchStatus("bh2ut");
//   tree->SetBranchStatus("bh2da");
//   tree->SetBranchStatus("bh2dt");
//   tree->SetBranchStatus("sacnhits");
//   tree->SetBranchStatus("sachitpat");
//   tree->SetBranchStatus("saca");
//   tree->SetBranchStatus("sact");
//   tree->SetBranchStatus("tofnhits");
//   tree->SetBranchStatus("tofhitpat");
//   tree->SetBranchStatus("tofua");
//   tree->SetBranchStatus("tofut");
//   tree->SetBranchStatus("tofda");
//   tree->SetBranchStatus("tofdt");
   tree->SetBranchStatus("lcnhits");
   tree->SetBranchStatus("lchitpat");
   tree->SetBranchStatus("lct");
//   tree->SetBranchStatus("bh1utime");
//   tree->SetBranchStatus("bh1dtime");
//   tree->SetBranchStatus("bh1mt");
//   tree->SetBranchStatus("bh1de");
//   tree->SetBranchStatus("bh2utime");
//   tree->SetBranchStatus("bh2dtime");
//   tree->SetBranchStatus("bh2mt");
//   tree->SetBranchStatus("bh2de");
//   tree->SetBranchStatus("sacmt");
//   tree->SetBranchStatus("sacde");
//   tree->SetBranchStatus("tofmt");
//   tree->SetBranchStatus("tofde");
//   tree->SetBranchStatus("lcmt");
//   tree->SetBranchStatus("t0");
//   tree->SetBranchStatus("ct0");
//   tree->SetBranchStatus("btof");
//   tree->SetBranchStatus("cbtof");

   // Set branch addresses.
     tree->SetBranchAddress("evnum",&evnum);
     tree->SetBranchAddress("trignhits",&trignhits);
     tree->SetBranchAddress("trigpat",trigpat);
     tree->SetBranchAddress("trigflag",trigflag);
//   tree->SetBranchAddress("bh1nhits",&bh1nhits);
//   tree->SetBranchAddress("bh1hitpat",bh1hitpat);
//   tree->SetBranchAddress("bh1ua",bh1ua);
//   tree->SetBranchAddress("bh1ut",bh1ut);
//   tree->SetBranchAddress("bh1da",bh1da);
//   tree->SetBranchAddress("bh1dt",bh1dt);
//   tree->SetBranchAddress("bh2nhits",&bh2nhits);
//   tree->SetBranchAddress("bh2hitpat",bh2hitpat);
//   tree->SetBranchAddress("bh2ua",bh2ua);
//   tree->SetBranchAddress("bh2ut",bh2ut);
//   tree->SetBranchAddress("bh2da",bh2da);
//   tree->SetBranchAddress("bh2dt",bh2dt);
//   tree->SetBranchAddress("sacnhits",&sacnhits);
//   tree->SetBranchAddress("sachitpat",sachitpat);
//   tree->SetBranchAddress("saca",saca);
//   tree->SetBranchAddress("sact",sact);
//   tree->SetBranchAddress("tofnhits",&tofnhits);
//   tree->SetBranchAddress("tofhitpat",tofhitpat);
//   tree->SetBranchAddress("tofua",tofua);
//   tree->SetBranchAddress("tofut",tofut);
//   tree->SetBranchAddress("tofda",tofda);
//   tree->SetBranchAddress("tofdt",tofdt);
     tree->SetBranchAddress("lcnhits",&lcnhits);
     tree->SetBranchAddress("lchitpat",lchitpat);
     tree->SetBranchAddress("lct",lct);
//     tree->SetBranchAddress("bh1utime",bh1utime);
//   tree->SetBranchAddress("bh1dtime",bh1dtime);
//   tree->SetBranchAddress("bh1mt",bh1mt);
//   tree->SetBranchAddress("bh1de",bh1de);
//   tree->SetBranchAddress("bh2utime",bh2utime);
//   tree->SetBranchAddress("bh2dtime",bh2dtime);
//   tree->SetBranchAddress("bh2mt",bh2mt);
//   tree->SetBranchAddress("bh2de",bh2de);
//   tree->SetBranchAddress("sacmt",sacmt);
//   tree->SetBranchAddress("sacde",sacde);
//   tree->SetBranchAddress("tofmt",tofmt);
//   tree->SetBranchAddress("tofde",tofde);
//     tree->SetBranchAddress("lcmt",lcmt);
//     tree->SetBranchAddress("t0",t0);
//   tree->SetBranchAddress("ct0",ct0);
//   tree->SetBranchAddress("btof",btof);
//   tree->SetBranchAddress("cbtof",cbtof);
 
//     This is the loop skeleton
//       To read only selected branches, Insert statements like:
// tree->SetBranchStatus("*",0);  // disable all branches
// TTreePlayer->SetBranchStatus("branchname",1);  // activate branchname

  //-para def-----------------------------------------------------------------------------------------
  double HULMHTDCCalib = -0.8333;
  double MaxBinValue=0.;

  int Hist1Max = 0;
  int Hist2Max = 0;

   double lcmttdcpeak[NumOfSegLC]; 
   int l = 5;

  //-hist def-----------------------------------------------------------------------------------------
  Hist1Max = 30;
  Hist2Max = 1;
  TH1D *Hist1[Hist1Max];
  TH2D *Hist2[Hist2Max];
  
  for(int i=0;i<NumOfSegLC;i++){
    Hist1[i]= new TH1D(Form("LC Mt Tdc %d",i+1),Form("LC Mt Tdc %d",i+1),2000,0,2000);
  }
  Hist1[28]= new TH1D("LC Mt Nhits","LC Mt Nhits",28,1,29);
  Hist1[29]= new TH1D("LC Mt Hitpattern","LC Mt Hitpattern",28,1,29);



   TF1 *fit = new TF1("fit","gaus"); 

//-Event Loop --------------------------------------------------------------------------------------
   Long64_t nentries = tree->GetEntries();

   Long64_t nbytes = 0;
   for (Long64_t s=0; s<nentries;s++) {
     nbytes += tree->GetEntry(s);

     Hist1[28]->Fill(lcnhits);

     for(int i=0; i<NumOfSegLC; i++){
       Hist1[29]->Fill(lchitpat[i]);
       for(int j=0; j<16; j++){
         if(lct[i][j]==-999) continue;
         Hist1[i]->Fill(lct[i][j]);
       }
     }
   }

   
//-Hist Draw----------------------------------------------------------------------------------------

   TCanvas *c1 = new TCanvas("c1","c1",800,700); 
  c1->Print(pdf+"["); 
  c1->cd();
  for(int i=0; i<Hist1Max; i++){
    //   if(i==15 || i==16 || i==38) gPad->SetLogy(1);
    Hist1[i]->Draw();
    c1->Print(pdf);
    c1->Print(Form("%s/HodoParamMaker_LC_run%05d_Hist1_%03d.pdf",pdfDhire.Data(),runnum,i));
    //   if(i==15 || i==16 || i==38) gPad->SetLogy(0);
  }
//  for(int i=0; i<Hist2Max; i++){
//  Hist2[i]->Draw("colz");
//  c1->Print(pdf);
//  c1->Print(Form("%s/HodoParam_LC_run%05d_Hist2_%03d.pdf",pdfDhire.Data(),runnum,i));
//  }

   for (int i=0; i<NumOfSegLC;i++) {
       lcmttdcpeak[i] = Hist1[i]->GetMaximumBin();   
       lcmttdcpeak[i] = Hist1[i]->GetXaxis()->GetBinCenter(lcmttdcpeak[i]);  
       Hist1[i]->SetAxisRange(lcmttdcpeak[i]-50,lcmttdcpeak[i]+80,"X");

       Hist1[i]->Draw(); 
       Hist1[i]->Fit("fit","","", lcmttdcpeak[i]-l, lcmttdcpeak[i]+l);  
       c1->Print(pdf);
       lcmttdcpeak[i] = fit->GetParameter(1);  
   }
   
  c1->Print(pdf+"]"); 

  TString fout1 = (Form( "%s/hp_dat/HodoParam_LC_TDC_%05d.dat", anadir.Data() ,runnum));  
  std::ofstream fout_1(fout1.Data()); 
  for(int i=0; i<NumOfSegLC; i++){
     fout_1 << lcmttdcpeak[i] << endl;
  }     

}
