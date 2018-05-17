#include "DetectorID.hh"

void HodoParamMaker_1tof(int runnum){
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

   int seg1 = 4; //1 origine
   int seg2 = 4; //1 origine
   int range1 = 0; //  
   int range2 = 4; //  range1 < nhit < range2 

   TH1D *BH1UT[NumOfSegBH1]; 
   TH1D *BH1DT[NumOfSegBH1]; 
   TH1D *BH1UT0[NumOfSegBH1]; 
   TH1D *BH1DT0[NumOfSegBH1]; 
   TH1D *BH1UTns[NumOfSegBH1]; 
   TH1D *BH1DTns[NumOfSegBH1]; 
   TH1D *BH1MT[NumOfSegBH1]; 
      for (int i=0; i<NumOfSegBH1;i++) {
        BH1UT[i] = new TH1D(Form("BH1UT%d",i+1),Form("BH1UT%d",i+1),600,600,1200);
        BH1DT[i] = new TH1D(Form("BH1DT%d",i+1),Form("BH1DT%d",i+1),600,600,1200);
        BH1UT0[i] = new TH1D(Form("BH1UT0%d",i+1),Form("BH1UT0%d",i+1),600,-300,300);
        BH1DT0[i] = new TH1D(Form("BH1DT0%d",i+1),Form("BH1DT0%d",i+1),600,-300,300);
        BH1UTns[i] = new TH1D(Form("BH1UTns%d",i+1),Form("BH1UTns%d",i+1),162,-3,3);
        BH1DTns[i] = new TH1D(Form("BH1DTns%d",i+1),Form("BH1DTns%d",i+1),162,-3,3);
        BH1MT[i] = new TH1D(Form("BH1MT%d",i+1),Form("BH1MT%d",i+1),162,-3,3);
      }

   TH1D *BH2UT[NumOfSegBH2]; 
   TH1D *BH2DT[NumOfSegBH2]; 
   TH1D *BH2UT0[NumOfSegBH2]; 
   TH1D *BH2DT0[NumOfSegBH2]; 
   TH1D *BH2UTns[NumOfSegBH2]; 
   TH1D *BH2DTns[NumOfSegBH2]; 
   TH1D *BH2MT[NumOfSegBH2]; 
      for (int i=0; i<NumOfSegBH2;i++) {
        BH2UT[i] = new TH1D(Form("BH2UT%d",i+1),Form("BH2UT%d",i+1),400,200,600);
        BH2DT[i] = new TH1D(Form("BH2DT%d",i+1),Form("BH2DT%d",i+1),400,200,600);
        BH2UT0[i] = new TH1D(Form("BH2UT0%d",i+1),Form("BH2UT0%d",i+1),400,-200,200);
        BH2DT0[i] = new TH1D(Form("BH2DT0%d",i+1),Form("BH2DT0%d",i+1),400,-200,200);
        BH2UTns[i] = new TH1D(Form("BH2UTns%d",i+1),Form("BH2UTns%d",i+1),52,-1,1);
        BH2DTns[i] = new TH1D(Form("BH2DTns%d",i+1),Form("BH2DTns%d",i+1),52,-1,1);
        BH2MT[i] = new TH1D(Form("BH2MT%d",i+1),Form("BH2MT%d",i+1),52,-1,1);
      }

   TH1D *BTOF = new TH1D(Form("BTOF%d_%d",seg1,seg2),Form("BTOF%d_%d",seg1,seg2),166,-2,4); 

   Long64_t nentries = tree->GetEntries();
   double fitprm[3];
   double bh1utprm[NumOfSegBH1]; 
   double bh1dtprm[NumOfSegBH1]; 

   double bh2utprm[NumOfSegBH2]; 
   double bh2dtprm[NumOfSegBH2]; 
//   double l = 10; //4465
//   double l2 = 3;//4465
//   double l3 = 12;//4465
   double l = 15; //4462 & 4464
   double l2 = 7; //4462 & 4464

   double btof1[NumOfSegBH1]; 
   double btof2[NumOfSegBH2]; 


   TF1 *fit = new TF1("fit","gaus"); 
   

/////////////////////////////////////////////////////////////////////////////////////////////
//                                                                                         //
//    BH1 & BH2 TDC Mean get code                                                          //
//                                                                                         //
/////////////////////////////////////////////////////////////////////////////////////////////
   Long64_t nbytes = 0;
   for (Long64_t i=0; i<nentries;i++) {
      nbytes += tree->GetEntry(i);
      for (int i=0; i<NumOfSegBH1;i++) {
        if(bh1ut[i]>0 && bh1dt[i]>0  && bh1nhits < range2 && bh1nhits > range1 && bh2ut[seg2-1]>0 && bh2dt[seg2-1]>0 && bh2nhits < range2 && bh2nhits > range1){
          BH1UT[i]->Fill(bh1ut[i]);
          BH1DT[i]->Fill(bh1dt[i]);
        }
      }

      for (int i=0; i<NumOfSegBH2;i++) {
        if(bh1ut[seg1-1]>0 && bh1dt[seg1-1]>0 && bh1nhits < range2 && bh1nhits > range1 && bh2ut[i]>0 && bh2dt[i]>0 && bh2nhits < range2 && bh2nhits > range1){
          BH2UT[i]->Fill(bh2ut[i]);
          BH2DT[i]->Fill(bh2dt[i]);
        }
      }
   }

   
   TString pdf = Form("%s/pdf/trigger_study/seg_mean_%05d.pdf", anadir.Data(),runnum);
   TCanvas *c1 = new TCanvas("c1","c1",800,700); 
   TCanvas *c2 = new TCanvas("c2","c2",800,700); 
   TCanvas *c3 = new TCanvas("c3","c3",800,700); 
   TCanvas *c4 = new TCanvas("c4","c4",800,700); 
   c1->Print(pdf+"["); 

// BH1 UandD seg4 TDC MEAN 
   for (int i=0; i<NumOfSegBH1;i++) {
       bh1utprm[i] = BH1UT[i]->GetMaximumBin();   
       bh1dtprm[i] = BH1DT[i]->GetMaximumBin();   

       bh1utprm[i] = BH1UT[i]->GetXaxis()->GetBinCenter(bh1utprm[i]);  
       bh1dtprm[i] = BH1DT[i]->GetXaxis()->GetBinCenter(bh1dtprm[i]);  

       BH1UT[i]->Fit("fit","","", bh1utprm[i]-l, bh1utprm[i]+l-2);  //4462 & 4464 
//       BH1UT[i]->Fit("fit","","", bh1utprm[i]-l, bh1utprm[i]+l+2); //4465 
       bh1utprm[i] = fit->GetParameter(1);  
       BH1UT[i]->GetXaxis()->SetRangeUser(bh1utprm[i]-2*(l), bh1utprm[i]+4*(l)); 

       BH1DT[i]->Fit("fit","","", bh1dtprm[i]-l-2, bh1dtprm[i]+l-2); //4462 & 4464 
//       BH1DT[i]->Fit("fit","","", bh1dtprm[i]-l, bh1dtprm[i]+ 2*l); //4465  
       bh1dtprm[i] = fit->GetParameter(1);  
       BH1DT[i]->GetXaxis()->SetRangeUser(bh1dtprm[i]-2*(l), bh1dtprm[i]+4*(l));  

   }

// BH2 UandD seg4 TDC MEAN 
   for (int i=0; i<NumOfSegBH2;i++) {
       bh2utprm[i] = BH2UT[i]->GetMaximumBin();   
       bh2dtprm[i] = BH2DT[i]->GetMaximumBin();   

       bh2utprm[i] = BH2UT[i]->GetXaxis()->GetBinCenter(bh2utprm[i]);  
       bh2dtprm[i] = BH2DT[i]->GetXaxis()->GetBinCenter(bh2dtprm[i]);  

       BH2UT[i]->Fit("fit","","", bh2utprm[i]-l2, bh2utprm[i]+l2-1);  //4462 & 4464
//       BH2UT[i]->Fit("fit","","", bh2utprm[i]-l3+1, bh2utprm[i]+l3);  //4465 
       bh2utprm[i] = fit->GetParameter(1);  
       BH2UT[i]->GetXaxis()->SetRangeUser(bh2utprm[i]-2*l2, bh2utprm[i]+4*(l2));  //4462 & 4464 
//       BH2UT[i]->GetXaxis()->SetRangeUser(bh2utprm[i]-2*l3, bh2utprm[i]+4*(l3));  //4465  

       BH2DT[i]->Fit("fit","","", bh2dtprm[i]-l2+1, bh2dtprm[i]+l2-1); //4462 & 4464 
//       BH2DT[i]->Fit("fit","","", bh2dtprm[i]-l2+1, bh2dtprm[i]+l2);  //4465 
       bh2dtprm[i] = fit->GetParameter(1);  
       BH2DT[i]->GetXaxis()->SetRangeUser(bh2dtprm[i]-1*(l2+1), bh2dtprm[i]+4*(l2-1));  

   }
   
   c1->cd(); 
   c1->SetLogy();
   c1->SetGridx();
   c1->SetGridy();
   BH1UT[seg1-1]->Draw(); 
   c1 ->Print(pdf); 

   c2->cd(); 
   c2->SetLogy();
   c2->SetGridx();
   c2->SetGridy();
   BH1DT[seg1-1]->Draw(); 
   c2 ->Print(pdf); 
   
   c3->cd(); 
   c3->SetLogy();
   c3->SetGridx();
   c3->SetGridy();
   BH2UT[seg2-1]->Draw(); 
   c3 ->Print(pdf); 

   c4->cd(); 
   c4->SetLogy();
   c4->SetGridx();
   c4->SetGridy();
   BH2DT[seg2-1]->Draw(); 
   c4 ->Print(pdf); 
   


/////////////////////////////////////////////////////////////////////////////////////////////
//                                                                                         //
//    BH1 & BH2 TDC's peak chande to 0 code                                                          //
//                                                                                         //
/////////////////////////////////////////////////////////////////////////////////////////////
   nbytes = 0;
   for (Long64_t i=0; i<nentries;i++) {
      nbytes += tree->GetEntry(i);
      for (int i=0; i<NumOfSegBH1;i++) {
        if(bh1ut[i]>0 && bh1dt[i]>0 && bh1nhits < range2 && bh1nhits > range1 && bh2ut[seg2-1]>0 && bh2dt[seg2-1]>0 && bh2nhits < range2 && bh2nhits > range1){
          BH1UT0[i]->Fill(bh1ut[i]-bh1utprm[i]);
          BH1DT0[i]->Fill(bh1dt[i]-bh1dtprm[i]);
        }
      }

      for (int i=0; i<NumOfSegBH2;i++) {
        if(bh1ut[seg1-1]>0 && bh1dt[seg1-1]>0 && bh1nhits < range2 && bh1nhits > range1 && bh2ut[i]>0 && bh2dt[i]>0 && bh2nhits < range2 && bh2nhits > range1){
          BH2UT0[i]->Fill(bh2ut[i]-bh2utprm[i]);
          BH2DT0[i]->Fill(bh2dt[i]-bh2dtprm[i]);
        }
      }
   }

   BH1UT0[seg1-1]->GetXaxis()->SetRangeUser(-50,50);  
   BH1DT0[seg1-1]->GetXaxis()->SetRangeUser(-50,50);  
   BH2UT0[seg2-1]->GetXaxis()->SetRangeUser(-50,50);  
   BH2DT0[seg2-1]->GetXaxis()->SetRangeUser(-50,50);  

   c1->cd(); 
   c1->SetLogy();
   c1->SetGridx();
   c1->SetGridy();
   BH1UT0[seg1-1]->Draw(); 
   c1 ->Print(pdf); 

   c2->cd(); 
   c2->SetLogy();
   c2->SetGridx();
   c2->SetGridy();
   BH1DT0[seg1-1]->Draw(); 
   c2 ->Print(pdf); 
   
   c3->cd(); 
   c3->SetLogy();
   c3->SetGridx();
   c3->SetGridy();
   BH2UT0[seg2-1]->Draw(); 
   c3 ->Print(pdf); 

   c4->cd(); 
   c4->SetLogy();
   c4->SetGridx();
   c4->SetGridy();
   BH2DT0[seg2-1]->Draw(); 
   c4 ->Print(pdf); 
   


/////////////////////////////////////////////////////////////////////////////////////////////
//                                                                                         //
//    BH1 & BH2 ch chande to ns code                                                       //
//                                                                                         //
/////////////////////////////////////////////////////////////////////////////////////////////
  std::vector<std::vector<double>> BH1TDC; 
  std::vector<std::vector<double>> BH2TDC; 
  TString prmdir2=Form("%s/work/e40/ana/hp_dat",std::getenv("HOME")); 
  TString filein1=Form("%s/HodoParam_BH1_TDCcalib_00001.dat",prmdir2.Data()); 
  TString filein2=Form("%s/HodoParam_BH2_TDCcalib_00001.dat",prmdir2.Data()); 
  std::ifstream fin1(filein1);
  std::ifstream fin2(filein2);
  std::string line;


  while(std::getline(fin1, line)){
    double a=-1, b=-1;
    std::istringstream input_line( line );
    std::vector<double> inner;
    if( input_line >> a >> b ){
      inner.push_back(a);
      inner.push_back(b);
      BH1TDC.push_back(inner);
    }
  }

  while(std::getline(fin2, line)){
    double a=-1, b=-1;
    std::istringstream input_line( line );
    std::vector<double> inner;
    if( input_line >> a >> b ){
      inner.push_back(a);
      inner.push_back(b);
      BH2TDC.push_back(inner);
    }
  }

   nbytes = 0;
   for (Long64_t i=0; i<nentries;i++) {
      nbytes += tree->GetEntry(i);
      for (int i=0; i<NumOfSegBH1;i++) {
        if(bh1ut[i]>0 && bh1dt[i]>0 && bh1nhits < range2 && bh1nhits > range1 && bh2ut[seg2-1]>0 && bh2dt[seg2-1]>0 && bh2nhits < range2 && bh2nhits > range1){
          BH1UTns[i]->Fill((bh1ut[i]-bh1utprm[i])*BH1TDC[i][0]);
          BH1DTns[i]->Fill((bh1dt[i]-bh1dtprm[i])*BH1TDC[i][1]);
          BH1MT[i]->Fill(((bh1dt[i]-bh1dtprm[i])*BH1TDC[i][0]+(bh1dt[i]-bh1dtprm[i])*BH1TDC[i][1])*0.5);
        }
      }

      for (int i=0; i<NumOfSegBH2;i++) {
        if(bh1ut[seg1-1]>0 && bh1dt[seg1-1]>0 && bh1nhits < range2 && bh1nhits > range1 && bh2ut[i]>0 && bh2dt[i]>0 && bh2nhits < range2 && bh2nhits > range1){
          BH2UTns[i]->Fill((bh2ut[i]-bh2utprm[i])*BH2TDC[i][0]);
          BH2DTns[i]->Fill((bh2dt[i]-bh2dtprm[i])*BH2TDC[i][1]);
          BH2MT[i]->Fill(((bh2dt[i]-bh2dtprm[i])*BH2TDC[i][0]+(bh2dt[i]-bh2dtprm[i])*BH2TDC[i][1])*0.5);
        }
      }
      
      if(bh1ut[seg1-1]>0 && bh1dt[seg1-1]>0 && bh2ut[seg2-1]>0 && bh2dt[seg2-1]>0 && bh1nhits < range2 && bh1nhits > range1  && bh2nhits < range2 && bh2nhits > range1){
        BTOF->Fill(((bh1dt[seg1-1]-bh1dtprm[seg1-1])*BH1TDC[seg1-1][0]+(bh1dt[seg1-1]-bh1dtprm[seg1-1])*BH1TDC[seg1-1][1])*0.5-((bh2dt[seg2-1]-bh2dtprm[seg2-1])*BH2TDC[seg2-1][0]+(bh2dt[seg2-1]-bh2dtprm[seg2-1])*BH2TDC[seg2-1][1])*0.5);   
      }

   }

   TF1 *fit2 = new TF1("fit2","gaus"); 
   BTOF->Fit("fit2","","", -0.5, 0.5);

   c1->cd(); 
   c1->SetLogy();
   c1->SetGridx();
   c1->SetGridy();
   BH1UTns[seg1-1]->Draw(); 
   c1 ->Print(pdf); 

   c2->cd(); 
   c2->SetLogy();
   c2->SetGridx();
   c2->SetGridy();
   BH1DTns[seg1-1]->Draw(); 
   c2 ->Print(pdf); 
   
   c3->cd(); 
   c3->SetLogy();
   c3->SetGridx();
   c3->SetGridy();
   BH2UTns[seg2-1]->Draw(); 
   c3 ->Print(pdf); 

   c4->cd(); 
   c4->SetLogy();
   c4->SetGridx();
   c4->SetGridy();
   BH2DTns[seg2-1]->Draw(); 
   c4 ->Print(pdf); 
   
   c1->cd(); 
   c1->SetLogy();
   c1->SetGridx();
   c1->SetGridy();
   BH1MT[seg1-1]->Draw(); 
   c1 ->Print(pdf); 

   c2->cd(); 
   c2->SetLogy();
   c2->SetGridx();
   c2->SetGridy();
   BH2MT[seg2-1]->Draw(); 
   c2 ->Print(pdf); 
   
   c3->cd(); 
   c3->SetLogy();
   c3->SetGridx();
   c3->SetGridy();
   BTOF->Draw(); 
   c3 ->Print(pdf); 


   c1->Print(pdf+"]"); 

}
