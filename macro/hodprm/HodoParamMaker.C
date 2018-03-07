#include "DetectorID.hh"

void HodoParamMaker(int runnum){
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


   TH1D *BH1UA[NumOfSegBH1]; 
   TH1D *BH1UT[NumOfSegBH1]; 
   TH1D *BH1DA[NumOfSegBH1]; 
   TH1D *BH1DT[NumOfSegBH1]; 
   TH1D *BH1UAMIP[NumOfSegBH1]; 
   TH1D *BH1DAMIP[NumOfSegBH1]; 
   TH1D *BTOF1[NumOfSegBH1]; 
      for (int i=0; i<NumOfSegBH1;i++) {
        BH1UA[i] = new TH1D(Form("BH1UA%d",i+1),Form("BH1UA%d",i+1),4000,0,4000);
        BH1UT[i] = new TH1D(Form("BH1UT%d",i+1),Form("BH1UT%d",i+1),4000,0,4000);
        BH1DA[i] = new TH1D(Form("BH1DA%d",i+1),Form("BH1DA%d",i+1),4000,0,4000);
        BH1DT[i] = new TH1D(Form("BH1DT%d",i+1),Form("BH1DT%d",i+1),4000,0,4000);
        BH1UAMIP[i] = new TH1D(Form("BH1UAMIP%d",i+1),Form("BH1UAMIP%d",i+1),4000,0,4000);
        BH1DAMIP[i] = new TH1D(Form("BH1DAMIP%d",i+1),Form("BH1DAMIP%d",i+1),4000,0,4000);
        BTOF1[i] = new TH1D(Form("BTOF1_%d",i+1),Form("BTOF1_%d",i+1),100,-5,5);
      }

   TH1D *BH2UA[NumOfSegBH2]; 
   TH1D *BH2UT[NumOfSegBH2]; 
   TH1D *BH2DA[NumOfSegBH2]; 
   TH1D *BH2DT[NumOfSegBH2]; 
   TH1D *BH2UAMIP[NumOfSegBH2]; 
   TH1D *BH2DAMIP[NumOfSegBH2]; 
   TH1D *BTOF2[NumOfSegBH2]; 
      for (int i=0; i<NumOfSegBH2;i++) {
        BH2UA[i] = new TH1D(Form("BH2UA%d",i+1),Form("BH2UA%d",i+1),4000,0,4000);
        BH2UT[i] = new TH1D(Form("BH2UT%d",i+1),Form("BH2UT%d",i+1),4000,0,4000);
        BH2DA[i] = new TH1D(Form("BH2DA%d",i+1),Form("BH2DA%d",i+1),4000,0,4000);
        BH2DT[i] = new TH1D(Form("BH2DT%d",i+1),Form("BH2DT%d",i+1),4000,0,4000);
        BH2UAMIP[i] = new TH1D(Form("BH2UAMIP%d",i+1),Form("BH2UAMIP%d",i+1),4000,0,4000);
        BH2DAMIP[i] = new TH1D(Form("BH2DAMIP%d",i+1),Form("BH2DAMIP%d",i+1),4000,0,4000);
        BTOF2[i] = new TH1D(Form("BTOF2_%d",i+1),Form("BTOF2_%d",i+1),100,-5,5);
      }

   Long64_t nentries = tree->GetEntries();
   double bh1uaprm[NumOfSegBH1]; 
   double bh1daprm[NumOfSegBH1]; 
   double bh1uamip[NumOfSegBH1]; 
   double bh1damip[NumOfSegBH1]; 
   double bh1utprm[NumOfSegBH1]; 
   double bh1dtprm[NumOfSegBH1]; 

   double bh2uaprm[NumOfSegBH2]; 
   double bh2daprm[NumOfSegBH2]; 
   double bh2uamip[NumOfSegBH2]; 
   double bh2damip[NumOfSegBH2]; 
   double bh2utprm[NumOfSegBH2]; 
   double bh2dtprm[NumOfSegBH2]; 
   double l = 10;
   double l_mip = 100;

   double btof1[NumOfSegBH1]; 
   double btof2[NumOfSegBH2]; 

   double l_mt = 0.5;


   TF1 *fit = new TF1("fit","gaus"); 

   Long64_t nbytes = 0;
   for (Long64_t i=0; i<nentries;i++) {
      nbytes += tree->GetEntry(i);
      for (int i=0; i<NumOfSegBH1;i++) {
        BH1UT[i]->Fill(bh1ut[i]);
        BH1DT[i]->Fill(bh1dt[i]);
        if(bh1ut[i] < 0){ 
            BH1UA[i]->Fill(bh1ua[i]);
        }
        if(bh1ut[i] > 0 && bh1nhits == 1){ 
            BH1UAMIP[i]->Fill(bh1ua[i]);
        }
        if(bh1dt[i] < 0){ 
            BH1DA[i]->Fill(bh1da[i]);
        }
        if(bh1dt[i] > 0 && bh1nhits == 1){ 
            BH1DAMIP[i]->Fill(bh1da[i]);
        }
        if(bh1mt[i]>0 && bh2mt[4]>0){  
            BTOF1[i]->Fill(bh1mt[i]-bh2mt[4]);
        }
      }

      for (int i=0; i<NumOfSegBH2;i++) {
        BH2UT[i]->Fill(bh2ut[i]);
        BH2DT[i]->Fill(bh2dt[i]);
        if(bh2ut[i] < 0){ 
            BH2UA[i]->Fill(bh2ua[i]);
        }
        if(bh2ut[i] > 0 && bh2nhits == 1){ 
            BH2UAMIP[i]->Fill(bh2ua[i]);
        } 
        if(bh2dt[i] < 0){ 
            BH2DA[i]->Fill(bh2da[i]);
        }
        if(bh2dt[i] > 0 && bh2nhits == 1){ 
            BH2DAMIP[i]->Fill(bh2da[i]);
        }
        if(bh1mt[5]>0 && bh2mt[i]>0){  
           BTOF2[i]->Fill(bh1mt[5]-bh2mt[i]);
        }
      }
   }

   TCanvas *c1 = new TCanvas("c1","c1",800,700); 
   TCanvas *c2 = new TCanvas("c2","c2",800,700); 
   TCanvas *c3 = new TCanvas("c3","c3",800,700); 
   TCanvas *c4 = new TCanvas("c4","c4",800,700); 
   TCanvas *c5 = new TCanvas("c5","c5",800,700); 
   TCanvas *c6 = new TCanvas("c6","c6",800,700); 
   TCanvas *c7  = new TCanvas("c7","c7",800,700); 
   TCanvas *c8  = new TCanvas("c8","c8",800,700); 
   TCanvas *c9  = new TCanvas("c9","c9",800,700); 
   TCanvas *c10 = new TCanvas("c10","c10",800,700); 
   TCanvas *c11 = new TCanvas("c11","c11",800,700); 
   TCanvas *c12 = new TCanvas("c12","c12",800,700); 
   TCanvas *c13 = new TCanvas("c13","c13",800,700); 
   TCanvas *c14 = new TCanvas("c14","c14",800,700); 
       c1->Divide(4,3);
       c2->Divide(4,3);
       c3->Divide(4,3);
       c4->Divide(4,3);
       c5->Divide(4,3);
       c6->Divide(4,3);
       c7 ->Divide(4,2);
       c8 ->Divide(4,2);
       c9 ->Divide(4,2);
       c10->Divide(4,2);
       c11->Divide(4,2);
       c12->Divide(4,2);
       c13->Divide(4,3);
       c14->Divide(4,2);
   
   TString p0pdf = Form("%s/pdf/trigger_study/p0_%05d.pdf", anadir.Data(),runnum);
   TString pedepdf = Form("%s/pdf/trigger_study/pede_%05d.pdf", anadir.Data(),runnum);
   TString mippdf = Form("%s/pdf/trigger_study/mip_%05d.pdf", anadir.Data(),runnum);
   TString btof12pdf = Form("%s/pdf/trigger_study/btof12_%05d.pdf", anadir.Data(),runnum);
   c1->Print(p0pdf+"["); 
   c2->Print(pedepdf+"["); 
   c3->Print(mippdf+"["); 
   c4->Print(btof12pdf+"["); 

   for (int i=0; i<NumOfSegBH1;i++) {
       bh1utprm[i] = BH1UT[i]->GetMaximumBin();   
       bh1dtprm[i] = BH1DT[i]->GetMaximumBin();   
       bh1uaprm[i] = BH1UA[i]->GetMaximumBin();   
       bh1daprm[i] = BH1DA[i]->GetMaximumBin();   
       bh1uamip[i] = BH1UAMIP[i]->GetMaximumBin();   
       bh1damip[i] = BH1DAMIP[i]->GetMaximumBin();   

       btof1[i] = BTOF1[i]->GetMaximumBin();   

       bh1utprm[i] = BH1UT[i]->GetXaxis()->GetBinCenter(bh1utprm[i]);  
       bh1dtprm[i] = BH1DT[i]->GetXaxis()->GetBinCenter(bh1dtprm[i]);  
       bh1uaprm[i] = BH1UA[i]->GetXaxis()->GetBinCenter(bh1uaprm[i]);  
       bh1daprm[i] = BH1DA[i]->GetXaxis()->GetBinCenter(bh1daprm[i]);  
       bh1uamip[i] = BH1UAMIP[i]->GetXaxis()->GetBinCenter(bh1uamip[i]);  
       bh1damip[i] = BH1DAMIP[i]->GetXaxis()->GetBinCenter(bh1damip[i]);  
       
       btof1[i] = BTOF1[i]->GetXaxis()->GetBinCenter(btof1[i]);  

       c1->cd(i+1); 
       BH1UT[i]->Draw(); 
       BH1UT[i]->Fit("fit","","", bh1utprm[i]-l, bh1utprm[i]+l);  
       bh1utprm[i] = fit->GetParameter(1);  
       BH1UT[i]->GetXaxis()->SetRangeUser(bh1utprm[i]-20,bh1utprm[i]+40);   
       c2->cd(i+1); 
       BH1DT[i]->Draw(); 
       BH1DT[i]->Fit("fit","","", bh1dtprm[i]-l, bh1dtprm[i]+l);  
       bh1dtprm[i] = fit->GetParameter(1);  
       BH1DT[i]->GetXaxis()->SetRangeUser(bh1dtprm[i]-20,bh1dtprm[i]+40);   
       c3->cd(i+1); 
       BH1UA[i]->Draw(); 
       BH1UA[i]->Fit("fit","","", bh1uaprm[i]-l, bh1uaprm[i]+l);  
       bh1uaprm[i] = fit->GetParameter(1);  
       BH1UA[i]->GetXaxis()->SetRangeUser(bh1uaprm[i]-10,bh1uaprm[i]+20);   
       c4->cd(i+1); 
       BH1DA[i]->Draw(); 
       BH1DA[i]->Fit("fit","","", bh1daprm[i]-l, bh1daprm[i]+l);  
       bh1daprm[i] = fit->GetParameter(1);  
       BH1DA[i]->GetXaxis()->SetRangeUser(bh1daprm[i]-10,bh1daprm[i]+20);   
       c5->cd(i+1); 
       BH1UAMIP[i]->Draw(); 
       BH1UAMIP[i]->Fit("fit","","", bh1uamip[i]-l_mip, bh1uamip[i]+l_mip);  
       bh1uamip[i] = fit->GetParameter(1);  
       BH1UAMIP[i]->GetXaxis()->SetRangeUser(bh1uamip[i]-100,bh1uamip[i]+200);   
       c6->cd(i+1); 
       BH1DAMIP[i]->Draw(); 
       BH1DAMIP[i]->Fit("fit","","", bh1damip[i]-l_mip, bh1damip[i]+l_mip);  
       bh1damip[i] = fit->GetParameter(1);  
       BH1DAMIP[i]->GetXaxis()->SetRangeUser(bh1damip[i]-100,bh1damip[i]+200);   
       c13->cd(i+1); 
       BTOF1[i]->Draw(); 
       BTOF1[i]->Fit("fit","","", btof1[i]-l_mt, btof1[i]+l_mt);  
       btof1[i] = fit->GetParameter(1);  
       BTOF1[i]->GetXaxis()->SetRangeUser(btof1[i]-2,btof1[i]+4);   
   }
   
   c1->Print(p0pdf); 
   c2->Print(p0pdf); 
   c3->Print(pedepdf); 
   c4->Print(pedepdf); 
   c5->Print(mippdf); 
   c6->Print(mippdf); 
   c13->Print(btof12pdf); 

   

   for (int i=0; i<NumOfSegBH2;i++) {
       bh2utprm[i] = BH2UT[i]->GetMaximumBin();   
       bh2dtprm[i] = BH2DT[i]->GetMaximumBin();   
       bh2uaprm[i] = BH2UA[i]->GetMaximumBin();   
       bh2daprm[i] = BH2DA[i]->GetMaximumBin();   
       bh2uamip[i] = BH2UAMIP[i]->GetMaximumBin();   
       bh2damip[i] = BH2DAMIP[i]->GetMaximumBin();   

       btof2[i] = BTOF2[i]->GetMaximumBin();   

       bh2utprm[i] = BH2UT[i]->GetXaxis()->GetBinCenter(bh2utprm[i]);  
       bh2dtprm[i] = BH2DT[i]->GetXaxis()->GetBinCenter(bh2dtprm[i]);  
       bh2uaprm[i] = BH2UA[i]->GetXaxis()->GetBinCenter(bh2uaprm[i]);  
       bh2daprm[i] = BH2DA[i]->GetXaxis()->GetBinCenter(bh2daprm[i]);  
       bh2uamip[i] = BH2UAMIP[i]->GetXaxis()->GetBinCenter(bh2uamip[i]);  
       bh2damip[i] = BH2DAMIP[i]->GetXaxis()->GetBinCenter(bh2damip[i]);  

       btof2[i] = BTOF2[i]->GetXaxis()->GetBinCenter(btof2[i]);  

       c7->cd(i+1); 
       BH2UT[i]->Draw(); 
       BH2UT[i]->Fit("fit","","", bh2utprm[i]-l, bh2utprm[i]+l);  
       bh2utprm[i] = fit->GetParameter(1);  
       BH2UT[i]->GetXaxis()->SetRangeUser(bh2utprm[i]-20,bh2utprm[i]+40);   
       c8->cd(i+1); 
       BH2DT[i]->Draw(); 
       BH2DT[i]->Fit("fit","","", bh2dtprm[i]-l, bh2dtprm[i]+l);  
       bh2dtprm[i] = fit->GetParameter(1);  
       BH2DT[i]->GetXaxis()->SetRangeUser(bh2dtprm[i]-20,bh2dtprm[i]+40);   
       c9->cd(i+1); 
       BH2UA[i]->Draw(); 
       BH2UA[i]->Fit("fit","","", bh2uaprm[i]-l, bh2uaprm[i]+l);  
       bh2uaprm[i] = fit->GetParameter(1);  
       BH2UA[i]->GetXaxis()->SetRangeUser(bh2uaprm[i]-10,bh2uaprm[i]+20);   
       c10->cd(i+1); 
       BH2DA[i]->Draw(); 
       BH2DA[i]->Fit("fit","","", bh2daprm[i]-l, bh2daprm[i]+l);  
       bh2daprm[i] = fit->GetParameter(1);  
       BH2DA[i]->GetXaxis()->SetRangeUser(bh2daprm[i]-10,bh2daprm[i]+20);   
       c11->cd(i+1); 
       BH2UAMIP[i]->Draw(); 
       BH2UAMIP[i]->Fit("fit","","", bh2uamip[i]-l_mip, bh2uamip[i]+l_mip);  
       bh2uamip[i] = fit->GetParameter(1);  
       BH2UAMIP[i]->GetXaxis()->SetRangeUser(bh2uamip[i]-100,bh2uamip[i]+200);   
       c12->cd(i+1); 
       BH2DAMIP[i]->Draw(); 
       BH2DAMIP[i]->Fit("fit","","", bh2damip[i]-l_mip, bh2damip[i]+l_mip);  
       bh2damip[i] = fit->GetParameter(1);  
       BH2DAMIP[i]->GetXaxis()->SetRangeUser(bh2damip[i]-100,bh2damip[i]+200);   
       c14->cd(i+1); 
       BTOF2[i]->Draw(); 
       BTOF2[i]->Fit("fit","","", btof2[i]-l_mt, btof2[i]+l_mt);  
       btof2[i] = fit->GetParameter(1);  
       BTOF2[i]->GetXaxis()->SetRangeUser(btof2[i]-2,btof2[i]+4);   
   }

  c7 ->Print(p0pdf); 
  c8 ->Print(p0pdf); 
  c9 ->Print(pedepdf); 
  c10->Print(pedepdf); 
  c11->Print(mippdf); 
  c12->Print(mippdf); 
  c14->Print(btof12pdf); 

  c1->Print(p0pdf+"]"); 
  c2->Print(pedepdf+"]"); 
  c3->Print(mippdf+"]"); 
  c4->Print(btof12pdf+"]"); 

  TString fout1 = (Form( "%s/hp_dat/HodoParam_BH1_TDC_%05d.dat", anadir.Data() ,runnum));  
  TString fout2 = (Form( "%s/hp_dat/HodoParam_BH1_ADC_%05d.dat", anadir.Data() ,runnum));  
//  TString fout3 = (Form( "%s/hp_dat/HodoParam_BH1_mip_%05d.dat", anadir.Data() ,runnum));  
  TString fout7 = (Form( "%s/hp_dat/HodoParam_BTOF1_%05d.dat", anadir.Data() ,runnum));  
  std::ofstream fout_1(fout1.Data()); 
  std::ofstream fout_2(fout2.Data()); 
//  std::ofstream fout_3(fout3.Data()); 
  std::ofstream fout_7(fout7.Data()); 
  for(int i=0; i<NumOfSegBH1; i++){
     fout_1 << bh1utprm[i]  <<  "\t"  << bh1dtprm[i] << "\t"  << bh1utprm[i] - btof1[i]   <<"\t"  << bh1dtprm[i] - btof1[i]  << endl;
     fout_2 << bh1uaprm[i]  <<  "\t" << bh1uamip[i]  <<  "\t" << bh1daprm[i]  <<  "\t" << bh1damip[i] << endl;
     fout_7 << btof1[i]  << endl;
  }     

  TString fout4 = (Form( "%s/hp_dat/HodoParam_BH2_TDC_%05d.dat", anadir.Data() ,runnum));  
  TString fout5 = (Form( "%s/hp_dat/HodoParam_BH2_ADC_%05d.dat", anadir.Data() ,runnum));  
//  TString fout6 = (Form( "%s/hp_dat/HodoParam_BH2_mip_%05d.dat", anadir.Data() ,runnum));  
  TString fout8 = (Form( "%s/hp_dat/HodoParam_BTOF2_%05d.dat", anadir.Data() ,runnum));  
  std::ofstream fout_4(fout4.Data()); 
  std::ofstream fout_5(fout5.Data()); 
//  std::ofstream fout_6(fout6.Data()); 
  std::ofstream fout_8(fout8.Data()); 
  for(int i=0; i<NumOfSegBH2; i++){
//     fout_4 << bh2utprm[i]  <<  "\t"  << bh2dtprm[i] << endl;
//     fout_5 << bh2uaprm[i]  <<  "\t"  << bh2daprm[i] << endl;
//     fout_6 << bh2uamip[i]  <<  "\t"  << bh2damip[i] << endl;
     fout_4 << bh2utprm[i]  <<  "\t"  << bh2dtprm[i] <<  endl;
     fout_5 << bh2uaprm[i]  <<  "\t" << bh2uamip[i]  <<  "\t" << bh2daprm[i]  <<  "\t" << bh2damip[i] << endl;
     fout_8 << btof2[i]  << endl;
  }     
}
