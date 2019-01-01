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
void LC_Cut(int month, int runnum){
  //////////////////////////////////////////////////////////
  //   This file has been automatically generated 
  //     (Mon Dec 31 18:42:47 2018 by ROOT version6.10/08)
  //   from TTree khodo_lc/tree of DstKuramaHodoscope_LC
  //   found on file: rootfile/run05126_DstKuramaHodoscope_LC.root
  //////////////////////////////////////////////////////////

  gStyle->SetOptStat(1111110); 
  gStyle->SetOptFit(1); 


  //Reset ROOT and connect tree file
  gROOT->Reset();
  //   TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("rootfile/run05126_DstKuramaEasirocHodoscope.root");
  TString anadir=Form("%s/work/e40/ana",std::getenv("HOME")); 
  TString pdf = Form("%s/pdf/trigger/LC_Cut_run%05d.pdf", anadir.Data(),runnum);
  TString pdfDhire = Form("%s/pdf/trigger", anadir.Data());
  TFile *f = new TFile(Form("%s/analyzer_%s/rootfile/run%05d_DstKuramaHodoscope_LC.root", anadir.Data(),Month[month], runnum),"READ");
  TTree *khodo_lc;
  f->GetObject("khodo_lc",khodo_lc);

  //Declaration of leaves types
  Int_t           trigflag[32];
  Int_t           trigpat[32];
  Int_t           status;
  Int_t           ntKurama;
  Double_t        path[4];
  Double_t        pKurama[4];
  Double_t        qKurama[4];
  Double_t        chisqrKurama[4];
  Double_t        xtgtKurama[4];
  Double_t        ytgtKurama[4];
  Double_t        utgtKurama[4];
  Double_t        vtgtKurama[4];
  Double_t        thetaKurama[4];
  Double_t        vpx[5];
  Double_t        vpy[5];
  Double_t        tTofCalc[3];
  Int_t           nhBh1;
  Double_t        csBh1[5];
  Double_t        Bh1Seg[5];
  Double_t        tBh1[5];
  Double_t        dtBh1[5];
  Double_t        deBh1[5];
  Double_t        btof[5];
  Int_t           nhBh2;
  Double_t        csBh2[4];
  Double_t        Bh2Seg[4];
  Double_t        tBh2[4];
  Double_t        dtBh2[4];
  Double_t        t0Bh2[4];
  Double_t        deBh2[4];
  Int_t           nhSac;
  Double_t        csSac[29];
  Double_t        SacSeg[29];
  Double_t        tSac[29];
  Double_t        deSac[29];
  Int_t           nhTof;
  Double_t        csTof[17];
  Double_t        TofSeg[17];
  Double_t        tTof[17];
  Double_t        dtTof[17];
  Int_t           lcnhits;
  Int_t           lchitpat[28];
  Double_t        lct[28][16];
  Double_t        lcmt[28][16];
  Int_t           nhLc;
  Int_t           csLc[71];
  Double_t        LcSeg[71];
  Double_t        tLc[71];
  Int_t           m2Combi;
  Double_t        beta[36];
  Double_t        stof[36];
  Double_t        m2[36];

  // Set branch Status.
  khodo_lc->SetBranchStatus("trigflag");
  khodo_lc->SetBranchStatus("trigpat");
  khodo_lc->SetBranchStatus("status");
  khodo_lc->SetBranchStatus("ntKurama");
  khodo_lc->SetBranchStatus("path");
  khodo_lc->SetBranchStatus("pKurama");
  khodo_lc->SetBranchStatus("qKurama");
  khodo_lc->SetBranchStatus("chisqrKurama");
  //   khodo_lc->SetBranchStatus("xtgtKurama");
  //   khodo_lc->SetBranchStatus("ytgtKurama");
  //   khodo_lc->SetBranchStatus("utgtKurama");
  //   khodo_lc->SetBranchStatus("vtgtKurama");
  //   khodo_lc->SetBranchStatus("thetaKurama");
  //   khodo_lc->SetBranchStatus("vpx");
  //   khodo_lc->SetBranchStatus("vpy");
  //   khodo_lc->SetBranchStatus("tTofCalc");
  //   khodo_lc->SetBranchStatus("nhBh1");
  //   khodo_lc->SetBranchStatus("csBh1");
  //   khodo_lc->SetBranchStatus("Bh1Seg");
  //   khodo_lc->SetBranchStatus("tBh1");
  //   khodo_lc->SetBranchStatus("dtBh1");
  //   khodo_lc->SetBranchStatus("deBh1");
  //   khodo_lc->SetBranchStatus("btof");
  //   khodo_lc->SetBranchStatus("nhBh2");
  //   khodo_lc->SetBranchStatus("csBh2");
  //   khodo_lc->SetBranchStatus("Bh2Seg");
  //   khodo_lc->SetBranchStatus("tBh2");
  //   khodo_lc->SetBranchStatus("dtBh2");
  //   khodo_lc->SetBranchStatus("t0Bh2");
  //   khodo_lc->SetBranchStatus("deBh2");
  //   khodo_lc->SetBranchStatus("nhSac");
  //   khodo_lc->SetBranchStatus("csSac");
  //   khodo_lc->SetBranchStatus("SacSeg");
  //   khodo_lc->SetBranchStatus("tSac");
  //   khodo_lc->SetBranchStatus("deSac");
  //   khodo_lc->SetBranchStatus("nhTof");
  //   khodo_lc->SetBranchStatus("csTof");
  //   khodo_lc->SetBranchStatus("TofSeg");
  //   khodo_lc->SetBranchStatus("tTof");
  //   khodo_lc->SetBranchStatus("dtTof");
  khodo_lc->SetBranchStatus("lcnhits");
  khodo_lc->SetBranchStatus("lchitpat");
  khodo_lc->SetBranchStatus("lct");
  khodo_lc->SetBranchStatus("lcmt");
  khodo_lc->SetBranchStatus("nhLc");
  khodo_lc->SetBranchStatus("csLc");
  khodo_lc->SetBranchStatus("LcSeg");
  khodo_lc->SetBranchStatus("tLc");
  khodo_lc->SetBranchStatus("m2Combi");
  khodo_lc->SetBranchStatus("beta");
  khodo_lc->SetBranchStatus("stof");
  khodo_lc->SetBranchStatus("m2");

  // Set branch addresses.
  khodo_lc->SetBranchAddress("trigflag",trigflag);
  khodo_lc->SetBranchAddress("trigpat",trigpat);
  khodo_lc->SetBranchAddress("status",&status);
  khodo_lc->SetBranchAddress("ntKurama",&ntKurama);
  khodo_lc->SetBranchAddress("path",path);
  khodo_lc->SetBranchAddress("pKurama",pKurama);
  khodo_lc->SetBranchAddress("qKurama",qKurama);
  //   khodo_lc->SetBranchAddress("chisqrKurama",chisqrKurama);
  //   khodo_lc->SetBranchAddress("xtgtKurama",xtgtKurama);
  //   khodo_lc->SetBranchAddress("ytgtKurama",ytgtKurama);
  //   khodo_lc->SetBranchAddress("utgtKurama",utgtKurama);
  //   khodo_lc->SetBranchAddress("vtgtKurama",vtgtKurama);
  //   khodo_lc->SetBranchAddress("thetaKurama",thetaKurama);
  //   khodo_lc->SetBranchAddress("vpx",vpx);
  //   khodo_lc->SetBranchAddress("vpy",vpy);
  //   khodo_lc->SetBranchAddress("tTofCalc",tTofCalc);
  //   khodo_lc->SetBranchAddress("nhBh1",&nhBh1);
  //   khodo_lc->SetBranchAddress("csBh1",csBh1);
  //   khodo_lc->SetBranchAddress("Bh1Seg",Bh1Seg);
  //   khodo_lc->SetBranchAddress("tBh1",tBh1);
  //   khodo_lc->SetBranchAddress("dtBh1",dtBh1);
  //   khodo_lc->SetBranchAddress("deBh1",deBh1);
  //   khodo_lc->SetBranchAddress("btof",btof);
  //   khodo_lc->SetBranchAddress("nhBh2",&nhBh2);
  //   khodo_lc->SetBranchAddress("csBh2",csBh2);
  //   khodo_lc->SetBranchAddress("Bh2Seg",Bh2Seg);
  //   khodo_lc->SetBranchAddress("tBh2",tBh2);
  //   khodo_lc->SetBranchAddress("dtBh2",dtBh2);
  //   khodo_lc->SetBranchAddress("t0Bh2",t0Bh2);
  //   khodo_lc->SetBranchAddress("deBh2",deBh2);
  //   khodo_lc->SetBranchAddress("nhSac",&nhSac);
  //   khodo_lc->SetBranchAddress("csSac",csSac);
  //   khodo_lc->SetBranchAddress("SacSeg",SacSeg);
  //   khodo_lc->SetBranchAddress("tSac",tSac);
  //   khodo_lc->SetBranchAddress("deSac",deSac);
  //   khodo_lc->SetBranchAddress("nhTof",&nhTof);
  //   khodo_lc->SetBranchAddress("csTof",csTof);
  //   khodo_lc->SetBranchAddress("TofSeg",TofSeg);
  //   khodo_lc->SetBranchAddress("tTof",tTof);
  khodo_lc->SetBranchAddress("dtTof",dtTof);
  khodo_lc->SetBranchAddress("lcnhits",&lcnhits);
  khodo_lc->SetBranchAddress("lchitpat",lchitpat);
  khodo_lc->SetBranchAddress("lct",lct);
  khodo_lc->SetBranchAddress("lcmt",lcmt);
  khodo_lc->SetBranchAddress("nhLc",&nhLc);
  khodo_lc->SetBranchAddress("csLc",csLc);
  khodo_lc->SetBranchAddress("LcSeg",LcSeg);
  khodo_lc->SetBranchAddress("tLc",tLc);
  khodo_lc->SetBranchAddress("m2Combi",&m2Combi);
  khodo_lc->SetBranchAddress("beta",beta);
  khodo_lc->SetBranchAddress("stof",stof);
  khodo_lc->SetBranchAddress("m2",m2);

  //     This is the loop skeleton
  //       To read only selected branches, Insert statements like:
  // khodo_lc->SetBranchStatus("*",0);  // disable all branches
  // TTreePlayer->SetBranchStatus("branchname",1);  // activate branchname

  //-para def-----------------------------------------------------------------------------------------
  double HULMHTDCCalib = -0.8333;
  double MaxBinValue=0.;

  int Hist1Max = 0;
  int Hist2Max = 0;

  double lcmttdcpeak[NumOfSegLC]; 

  int Gate1 = 10;
  int Gate2 = 15;
  int Gate3 = 20;
  double NegGate1 = -10.;
  double NegGate2 = -15.;
  double NegGate3 = -20.;


  int l = 3;
  //-hist def-----------------------------------------------------------------------------------------
  Hist1Max = 74;
  Hist2Max = 4;
  TH1D *Hist1[Hist1Max];
  TH2D *Hist2[Hist2Max];

  for(int i=0;i<NumOfSegLC;i++){
    Hist1[i]= new TH1D(Form("LC Mt Tdc %d",i+1),Form("LC Mt Tdc %d",i+1),2000,0,2000);
    Hist1[30+i]= new TH1D(Form("LC Mt Time %d",i+1),Form("LC Mt Tdime %d",i+1),1000,-500,500);
  }
  Hist1[28]= new TH1D("LC Mt Nhits","LC Mt Nhits",28,1,29);
  Hist1[29]= new TH1D("LC Mt Hitpattern","LC Mt Hitpattern",28,1,29);
  Hist1[58]= new TH1D("m2","m2",100,-0.4,1.4);
  Hist1[59]= new TH1D("m2 Cut1 Gate1","m2 Cut1 Gate1",100,-0.4,1.4);
  Hist1[60]= new TH1D("pKurama","pKurama",100,0,1.6);
  Hist1[61]= new TH1D("pKurama Cut1 Gate1","pKurama Cut1 Gate1",100,0,1.6);
  Hist1[62]= new TH1D("m2 Cut2","m2 Cut2",100,-0.4,1.4);
  Hist1[63]= new TH1D("pKurama Cut2","pKurama Cut2",100,0,1.6);
  Hist1[64]= new TH1D("m2 Cut3 Gate1","m2 Cut3 Gate1",100,-0.4,1.4);
  Hist1[65]= new TH1D("pKurama Cut3 Gate1","pKurama Cut3 Gate1",100,0,1.6);
  Hist1[66]= new TH1D("m2 Cut1 Gate2","m2 Cut1 Gate2",100,-0.4,1.4);
  Hist1[67]= new TH1D("m2 Cut1 Gate3","m2 Cut1 Gate3",100,-0.4,1.4);
  Hist1[68]= new TH1D("pKurama Cut1 Gate2","pKurama Cut1 Gate2",100,0,1.6);
  Hist1[69]= new TH1D("pKurama Cut1 Gate3","pKurama Cut1 Gate3",100,0,1.6);
  Hist1[70]= new TH1D("m2 Cut3 Gate2","m2 Cut3 Gate2",100,-0.4,1.4);
  Hist1[71]= new TH1D("pKurama Cut3 Gate2","pKurama Cut3 Gate2",100,0,1.6);
  Hist1[72]= new TH1D("m2 Cut3 Gate3","m2 Cut3 Gate3",100,-0.4,1.4);
  Hist1[73]= new TH1D("pKurama Cut3 Gate3","pKurama Cut3 Gate3",100,0,1.6);

  Hist2[0]= new TH2D("m2 vs pKurama Cut2 Gate1","m2 vs pKurama Cut2 Gate1",100,-0.4,1.4,100,0,1.6);
  Hist2[1]= new TH2D("m2 vs pKurama Cut3 Gate1","m2 vs pKurama Cut3 Gate1",100,-0.4,1.4,100,0,1.6);
  Hist2[2]= new TH2D("m2 vs pKurama Cut3 Gate2","m2 vs pKurama Cut3 Gate2",100,-0.4,1.4,100,0,1.6);
  Hist2[3]= new TH2D("m2 vs pKurama Cut3 Gate3","m2 vs pKurama Cut3 Gate3",100,-0.4,1.4,100,0,1.6);


  //   TF1 *fit = new TF1("fit","gaus"); 

  //-Legend def --------------------------------------------------------------------------------------
  TLegend *Leg1 = new TLegend(0.78,0.775,0.98,0.935);
  TLegend *Leg2 = new TLegend(0.78,0.775,0.98,0.935);

  //-Event Loop --------------------------------------------------------------------------------------
  Long64_t nentries = khodo_lc->GetEntries();

  Long64_t nbytes = 0;
  for (Long64_t s=0; s<nentries;s++) {
    nbytes += khodo_lc->GetEntry(s);

    Hist1[28]->Fill(lcnhits);

    bool LCGate1Flag = false;
    bool LCGate2Flag = false;
    bool LCGate3Flag = false;

    for(int i=0; i<NumOfSegLC; i++){
      Hist1[29]->Fill(lchitpat[i]);
      for(int j=0; j<16; j++){
        if(lct[i][j]!=-9999.){
          Hist1[i]->Fill(lct[i][j]);
        }
      }
      for(int j=0; j<16; j++){
        if(lcmt[i][j]!=-999.){
          Hist1[i+30]->Fill(lcmt[i][j]);
          if(lcmt[i][j]>-Gate1 && lcmt[i][j]<Gate1){ LCGate1Flag = true;}
          if(lcmt[i][j]>-Gate2 && lcmt[i][j]<Gate2){ LCGate2Flag = true;}
          if(lcmt[i][j]>-Gate3 && lcmt[i][j]<Gate3){ LCGate3Flag = true;}
        }
      }
    }

    for(int i=0; i<m2Combi; i++){
      Hist1[58]->Fill(m2[i]);
      if(LCGate1Flag==true){ Hist1[59]->Fill(m2[i]);}
      if(LCGate2Flag==true){ Hist1[66]->Fill(m2[i]);}
      if(LCGate3Flag==true){ Hist1[67]->Fill(m2[i]);}
    }
    for(int i=0; i<ntKurama; i++){
      Hist1[60]->Fill(pKurama[i]);
      if(LCGate1Flag==true){ Hist1[61]->Fill(pKurama[i]);}
      if(LCGate2Flag==true){ Hist1[68]->Fill(pKurama[i]);}
      if(LCGate3Flag==true){ Hist1[69]->Fill(pKurama[i]);}
    }
    if(ntKurama==1){
      Hist1[62]->Fill(m2[0]);
      Hist1[63]->Fill(pKurama[0]);
      Hist2[0]->Fill(m2[0],pKurama[0]);
      if(LCGate1Flag==true){
        Hist1[64]->Fill(m2[0]);
        Hist1[65]->Fill(pKurama[0]);
        Hist2[1]->Fill(m2[0],pKurama[0]);
      }
      if(LCGate2Flag==true){
        Hist1[70]->Fill(m2[0]);
        Hist1[71]->Fill(pKurama[0]);
        Hist2[2]->Fill(m2[0],pKurama[0]);
      }
      if(LCGate3Flag==true){
        Hist1[72]->Fill(m2[0]);
        Hist1[73]->Fill(pKurama[0]);
        Hist2[3]->Fill(m2[0],pKurama[0]);
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
//    c1->Print(Form("%s/LC_Cut_run%05d_Hist1_%03d.pdf",pdfDhire.Data(),runnum,i));
    c1->Print(Form("%s/pdf/trigger/LC_Cut_run%05d_Hist1_%03d.pdf",anadir.Data(),runnum,i));
    //   if(i==15 || i==16 || i==38) gPad->SetLogy(0);
  }
  for(int i=0; i<Hist2Max; i++){
    Hist2[i]->Draw("colz");
    c1->Print(pdf);
//    c1->Print(Form("%s/LC_Cut_run%05d_Hist2_%03d.pdf",pdfDhire.Data(),runnum,i));
    c1->Print(Form("%s/pdf/trigger/LC_Cut_run%05d_Hist2_%03d.pdf",anadir.Data(),runnum,i));
  }

//  for (int i=0; i<NumOfSegLC;i++) {
//    TF1 *fit = new TF1("fit","gaus"); 
//    lcmttdcpeak[i] = Hist1[i]->GetMaximumBin();   
//    lcmttdcpeak[i] = Hist1[i]->GetXaxis()->GetBinCenter(lcmttdcpeak[i]);  
//    Hist1[i]->SetAxisRange(lcmttdcpeak[i]-50,lcmttdcpeak[i]+80,"X");
//
//    Hist1[i]->Draw(); 
//    Hist1[i]->Fit("fit","","", lcmttdcpeak[i]-l, lcmttdcpeak[i]+l);  
//    c1->Print(pdf);
//    lcmttdcpeak[i] = fit->GetParameter(1);  
//  }

  Hist1[62]->SetStats(0);
  Hist1[64]->SetStats(0);
  Hist1[70]->SetStats(0);
  Hist1[72]->SetStats(0);

  Hist1[64]->SetLineColor(2);
  Hist1[70]->SetLineColor(3);
  Hist1[72]->SetLineColor(4);

  Hist1[62]->Draw();
  Hist1[64]->Draw("same");
  Hist1[70]->Draw("same");
  Hist1[72]->Draw("same");

  Leg1->AddEntry(Hist1[62],"ntKurama==1","l");
  Leg1->AddEntry(Hist1[64],Form("Cut Gate1 %dns",Gate1),"l");
  Leg1->AddEntry(Hist1[70],Form("Cut Gate2 %dns",Gate2),"l");
  Leg1->AddEntry(Hist1[72],Form("Cut Gate3 %dns",Gate3),"l");
  Leg1->Draw();
  c1->Print(pdf);

  Hist1[58]->SetStats(0);
  Hist1[59]->SetStats(0);
  Hist1[66]->SetStats(0);
  Hist1[67]->SetStats(0);

  Hist1[59]->SetLineColor(2);
  Hist1[66]->SetLineColor(3);
  Hist1[67]->SetLineColor(4);

  Hist1[58]->Draw();
  Hist1[59]->Draw("same");
  Hist1[66]->Draw("same");
  Hist1[67]->Draw("same");

  Leg2->AddEntry(Hist1[58],"No Cut   ","l");
  Leg2->AddEntry(Hist1[59],Form("Cut Gate1 %dns",Gate1),"l");
  Leg2->AddEntry(Hist1[66],Form("Cut Gate2 %dns",Gate2),"l");
  Leg2->AddEntry(Hist1[67],Form("Cut Gate3 %dns",Gate3),"l");
  Leg2->Draw();
  c1->Print(pdf);


  c1->Print(pdf+"]"); 

}
