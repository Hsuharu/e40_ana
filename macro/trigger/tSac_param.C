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


void tSac_param(int month,int runnum){
//////////////////////////////////////////////////////////
//   This file has been automatically generated 
//     (Fri Dec 21 17:08:12 2018 by ROOT version6.10/08)
//   from TTree tree/tree of Counter
//   found on file: analyzer_jun/rootfile/run05078_Hodoscope.root
//////////////////////////////////////////////////////////

  gStyle->SetOptStat(1111110); 
  gStyle->SetOptFit(1); 

//Reset ROOT and connect tree file
   gROOT->Reset();
   gROOT->Reset();
   TString anadir=Form("%s/work/e40/ana",std::getenv("HOME")); 
   TString pdf = Form("%s/pdf/trigger/tSac_param_run%05d.pdf", anadir.Data(),runnum);
   TString pdfDhire = Form("%s/pdf/trigger", anadir.Data());
//   TFile *f = new TFile(Form("%s/analyzer_%s/rootfile/trigf19_tofht.root", anadir.Data(),Month[month]),"READ");
   TFile *f = new TFile(Form("%s/analyzer_%s/rootfile/run%05d_Hodoscope.root", anadir.Data(),Month[month],runnum),"READ");
   TTree *tree;
    f->GetObject("tree",tree);

//Declaration of leaves types
   Int_t           evnum;
   Int_t           spill;
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
   Double_t        Btof0Seg;
   Double_t        deBtof0;
   Double_t        Btof0;
   Double_t        CBtof0;

// Select Branch ------------------------------------------------------------------------------------
   tree->SetBranchStatus("*", 0);
   tree->SetBranchStatus("evnum");
   tree->SetBranchStatus("spill");
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
//   tree->SetBranchStatus("fpga_bh2mtnhits");
//   tree->SetBranchStatus("fpga_bh2mthitpat");
//   tree->SetBranchStatus("fpga_bh2mt");
   tree->SetBranchStatus("sacnhits");
   tree->SetBranchStatus("sachitpat");
   tree->SetBranchStatus("saca");
   tree->SetBranchStatus("sact");
//   tree->SetBranchStatus("tofnhits");
//   tree->SetBranchStatus("tofhitpat");
//   tree->SetBranchStatus("tofua");
//   tree->SetBranchStatus("tofut");
//   tree->SetBranchStatus("tofda");
//   tree->SetBranchStatus("tofdt");
//   tree->SetBranchStatus("tofhtnhits");
//   tree->SetBranchStatus("tofhthitpat");
//   tree->SetBranchStatus("tofhtt");
//   tree->SetBranchStatus("lcnhits");
//   tree->SetBranchStatus("lchitpat");
//   tree->SetBranchStatus("lct");
//   tree->SetBranchStatus("bh1mt");
//   tree->SetBranchStatus("bh1de");
//   tree->SetBranchStatus("bh2mt");
//   tree->SetBranchStatus("bh2de");
   tree->SetBranchStatus("sacmt");
   tree->SetBranchStatus("sacde");
//   tree->SetBranchStatus("tofmt");
//   tree->SetBranchStatus("tofde");
//   tree->SetBranchStatus("tofhtmt");
//   tree->SetBranchStatus("lcmt");
//   tree->SetBranchStatus("t0");
//   tree->SetBranchStatus("ct0");
//   tree->SetBranchStatus("btof");
//   tree->SetBranchStatus("cbtof");
//   tree->SetBranchStatus("Time0Seg");
//   tree->SetBranchStatus("deTime0");
//   tree->SetBranchStatus("Time0");
//   tree->SetBranchStatus("CTime0");
//   tree->SetBranchStatus("Btof0Seg");
//   tree->SetBranchStatus("deBtof0");
//   tree->SetBranchStatus("Btof0");
//   tree->SetBranchStatus("CBtof0");


//Set branch addresses.
     tree->SetBranchAddress("evnum",&evnum);
     tree->SetBranchAddress("spill",&spill);
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
//   tree->SetBranchAddress("fpga_bh2mtnhits",&fpga_bh2mtnhits);
//   tree->SetBranchAddress("fpga_bh2mthitpat",fpga_bh2mthitpat);
//   tree->SetBranchAddress("fpga_bh2mt",fpga_bh2mt);
     tree->SetBranchAddress("sacnhits",&sacnhits);
     tree->SetBranchAddress("sachitpat",sachitpat);
     tree->SetBranchAddress("saca",saca);
     tree->SetBranchAddress("sact",sact);
//   tree->SetBranchAddress("tofnhits",&tofnhits);
//   tree->SetBranchAddress("tofhitpat",tofhitpat);
//   tree->SetBranchAddress("tofua",tofua);
//   tree->SetBranchAddress("tofut",tofut);
//   tree->SetBranchAddress("tofda",tofda);
//   tree->SetBranchAddress("tofdt",tofdt);
//   tree->SetBranchAddress("tofhtnhits",&tofhtnhits);
//   tree->SetBranchAddress("tofhthitpat",tofhthitpat);
//   tree->SetBranchAddress("tofhtt",tofhtt);
//   tree->SetBranchAddress("lcnhits",&lcnhits);
//   tree->SetBranchAddress("lchitpat",lchitpat);
//   tree->SetBranchAddress("lct",lct);
//   tree->SetBranchAddress("bh1mt",bh1mt);
//   tree->SetBranchAddress("bh1de",bh1de);
//   tree->SetBranchAddress("bh2mt",bh2mt);
//   tree->SetBranchAddress("bh2de",bh2de);
     tree->SetBranchAddress("sacmt",sacmt);
     tree->SetBranchAddress("sacde",sacde);
//   tree->SetBranchAddress("tofmt",tofmt);
//   tree->SetBranchAddress("tofde",tofde);
//   tree->SetBranchAddress("tofhtmt",tofhtmt);
//   tree->SetBranchAddress("lcmt",lcmt);
//   tree->SetBranchAddress("t0",t0);
//   tree->SetBranchAddress("ct0",ct0);
//   tree->SetBranchAddress("btof",btof);
//   tree->SetBranchAddress("cbtof",cbtof);
//   tree->SetBranchAddress("Time0Seg",&Time0Seg);
//   tree->SetBranchAddress("deTime0",&deTime0);
//   tree->SetBranchAddress("Time0",&Time0);
//   tree->SetBranchAddress("CTime0",&CTime0);
//   tree->SetBranchAddress("Btof0Seg",&Btof0Seg);
//   tree->SetBranchAddress("deBtof0",&deBtof0);
//   tree->SetBranchAddress("Btof0",&Btof0);
//   tree->SetBranchAddress("CBtof0",&CBtof0);

//     This is the loop skeleton
//       To read only selected branches, Insert statements like:
// tree->SetBranchStatus("*",0);  // disable all branches
// TTreePlayer->SetBranchStatus("branchname",1);  // activate branchname
//-para def-----------------------------------------------------------------------------------------
   int Hist1Max = 0;
   int Hist2Max = 0;


//-hist def-----------------------------------------------------------------------------------------
   Hist1Max = 12;
//   Hist2Max = 7;
   TH1D *Hist1[Hist1Max];
//   TH2D *Hist2[Hist2Max];

   for(int i=0; i<NumOfSegSAC; i++){
     Hist1[i ]= new TH1D(Form("sact ROOM%d",i+1),Form("sact ROOM%d",i+1),1000,0,2000);
     Hist1[i+4 ]= new TH1D(Form("sact ROOM%d zoom",i+1),Form("sact ROOM%d zoom",i+1),1000,0,2000);
     Hist1[i+4*2]= new TH1D(Form("sacmt ROOM%d",i+1),Form("sacmt ROOM%d",i+1),2000,-2000,2000);
   }


//    Hist2[0]= new TH2D("pKurama % ThetaKurama","pKurama % ThetaKurama",1000,0,40,1000,0,2);

//-Legend def --------------------------------------------------------------------------------------

//-Event Loop --------------------------------------------------------------------------------------

   Long64_t nentries = tree->GetEntries();

   Long64_t nbytes = 0;
   for (Long64_t s=0; s<nentries;s++) {
      nbytes += tree->GetEntry(s);
      for(int i=0; i<sacnhits; i++){
        for(int nd=0; nd<16; nd++){
          if(sact[sachitpat[i]-1][nd]==-9999) continue;
            Hist1[sachitpat[i]-1]->Fill(sact[sachitpat[i]-1][nd]);
            Hist1[sachitpat[i]-1+NumOfSegSAC]->Fill(sact[sachitpat[i]-1][nd]);
          if(sacmt[sachitpat[i]-1][nd]==-9999) continue;
            Hist1[sachitpat[i]-1+NumOfSegSAC*2]->Fill(sacmt[sachitpat[i]-1][nd]);
        }
      }
   }
// Peak & Gate Make -----
   TF1 *FitFunc1 = new TF1("FitFunc1","gaus");
   FitFunc1->SetParameters(1000,400,5);
   double MaximumBintSac=0.;
   double tSacPeak[NumOfSegSAC];
   for(int i=0; i<NumOfSegSAC; i++){
     MaximumBintSac=Hist1[i+NumOfSegSAC]->GetXaxis()->GetBinCenter(Hist1[i+NumOfSegSAC]->GetMaximumBin());
     Hist1[i+NumOfSegSAC]->Fit("FitFunc1","","",MaximumBintSac-4,MaximumBintSac+4);
     Hist1[i+NumOfSegSAC]->SetAxisRange(MaximumBintSac-50,MaximumBintSac+80,"X");
     tSacPeak[i]=FitFunc1->GetParameter(1);

     MaximumBintSac=Hist1[i+NumOfSegSAC*2]->GetXaxis()->GetBinCenter(Hist1[i+NumOfSegSAC*2]->GetMaximumBin());
     Hist1[i+NumOfSegSAC*2]->SetAxisRange(MaximumBintSac-50,MaximumBintSac+80,"X");
   }



//-Canvas def---------------------------------------------------------------------------------------

  TCanvas *c1 = new TCanvas("c1","c1",1200,900);
   c1->Print(pdf+"["); 
//-Hist Draw----------------------------------------------------------------------------------------
   c1->cd();
   for(int i=0; i<Hist1Max; i++){
//   if(i==15 || i==16) gPad->SetLogy(1);
   Hist1[i]->Draw();
   c1->Print(pdf);
   c1->Print(Form("%s/tSac_param_run%05d_Hist1_%03d.pdf",pdfDhire.Data(),runnum,i));
//   if(i==15 || i==16) gPad->SetLogy(0);
   }
//   for(int i=0; i<Hist2Max; i++){
//   Hist2[i]->Draw("colz");
//   c1->Print(pdf);
//   c1->Print(Form("%s/tSac_param_run%05d_Hist2_%03d.pdf",pdfDhire.Data(),runnum,i));
//   }
   c1->Print(pdf+"]"); 

   for(int i=0; i<NumOfSegSAC; i++){
     std::cout << tSacPeak[i ]<< std::endl;
   }
}
