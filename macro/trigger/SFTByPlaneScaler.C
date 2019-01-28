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

 const char* Plane[] =
 {
   "V",
   "U",
   "XU",
   "XD",
   "X"
 };

 double sftscr[5]={0.,0.,0.,0.,0.}; 
// std::vector<int> runnumber{5080,5139,5118,5120,5123,5304,5303,5126,5129,5272,5275,5283};
//  std::vector<int> runnumber{5272,5275,5283,5298,5299,5300,5301,5302,5303,5304};
  int runnumber[] = {5272,5275,5283,5298,5299,5300,5301,5302,5303,5304};
// int runnumber[] = {5080,5139,5118,5120,5123,5304,5303,5126,5129,5272,5275,5283};
// int runnumber[] = {5080,5139,5118,5120,5123,5304,5303,5126,5129,5275,5283};
// int runnumber1[] = {5080,5139,5118,5120,5123,5304};
// int runnumber2[] = {5303,5126,5129,5272,5275,5283};

void SFTByPlane_get( int month, int runnum){
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
   TString anadir=Form("%s/work/e40/ana",std::getenv("HOME")); 
   TFile *f = new TFile(Form("%s/analyzer_%s/rootfile/run%05d_Easiroc.root", anadir.Data(),Month[month], runnum),"READ");
   if (!f) {
      f = new TFile(Form("%s/rootfile/run%05d_Easiroc.root", anadir.Data() , runnum));
   }
    TTree *ea0c;
    f->GetObject("ea0c",ea0c);

//Declaration of leaves types
   Int_t           evnum;
   Int_t           trignhits;
   Int_t           trigpat[32];
   Int_t           trigflag[32];
   Int_t           bft_nhits;
   Int_t           bft_unhits;
   Int_t           bft_dnhits;
   Int_t           bft_uhitpat[17];
   Int_t           bft_dhitpat[36];
   Double_t        bft_utdc[160][16];
   Double_t        bft_dtdc[160][16];
   Double_t        bft_utrailing[160][16];
   Double_t        bft_dtrailing[160][16];
   Double_t        bft_utot[160][16];
   Double_t        bft_dtot[160][16];
   Int_t           bft_udepth[160];
   Int_t           bft_ddepth[160];
   Int_t           bft_ncl;
   Int_t           bft_clsize[92];
   Double_t        bft_ctime[92];
   Double_t        bft_ctot[92];
   Double_t        bft_clpos[92];
   Int_t           sch_nhits;
   Int_t           sch_hitpat[36];
   Double_t        sch_tdc[64][16];
   Double_t        sch_trailing[64][16];
   Double_t        sch_tot[64][16];
   Int_t           sch_depth[64];
   Int_t           sch_ncl;
   Int_t           sch_clsize[64];
   Double_t        sch_ctime[64];
   Double_t        sch_ctot[64];
   Double_t        sch_clpos[64];
   Int_t           sftv_nhits;
   Int_t           sftv_hitpat[109];
   Double_t        sftv_tdc[320][16];
   Double_t        sftv_trailing[320][16];
   Double_t        sftv_tot[320][16];
   Int_t           sftv_depth[320];
   Int_t           sftv_ncl;
   Int_t           sftv_clsize[190];
   Double_t        sftv_ctime[190];
   Double_t        sftv_ctot[190];
   Double_t        sftv_clpos[190];
   Int_t           sftu_nhits;
   Int_t           sftu_hitpat[116];
   Double_t        sftu_tdc[320][16];
   Double_t        sftu_trailing[320][16];
   Double_t        sftu_tot[320][16];
   Int_t           sftu_depth[320];
   Int_t           sftu_ncl;
   Int_t           sftu_clsize[153];
   Double_t        sftu_ctime[153];
   Double_t        sftu_ctot[153];
   Double_t        sftu_clpos[153];
   Int_t           sftx_nhits;
   Int_t           sftx_unhits;
   Int_t           sftx_dnhits;
   Int_t           sftx_uhitpat[95];
   Int_t           sftx_dhitpat[91];
   Double_t        sftx_utdc[256][16];
   Double_t        sftx_dtdc[256][16];
   Double_t        sftx_utrailing[256][16];
   Double_t        sftx_dtrailing[256][16];
   Double_t        sftx_utot[256][16];
   Double_t        sftx_dtot[256][16];
   Int_t           sftx_udepth[256];
   Int_t           sftx_ddepth[256];
   Int_t           sftx_ncl;
   Int_t           sftx_clsize[55];
   Double_t        sftx_ctime[55];
   Double_t        sftx_ctot[55];
   Double_t        sftx_clpos[55];

   // Set branch addresses.
   ea0c->SetBranchStatus("*",0);
   ea0c->SetBranchStatus("sftv_tdc");
   ea0c->SetBranchStatus("sftu_tdc");
//   ea0c->SetBranchAddress("evnum",&evnum);
//   ea0c->SetBranchAddress("trignhits",&trignhits);
//   ea0c->SetBranchAddress("trigpat",trigpat);
//   ea0c->SetBranchAddress("trigflag",trigflag);
//   ea0c->SetBranchAddress("bft_nhits",&bft_nhits);
//   ea0c->SetBranchAddress("bft_unhits",&bft_unhits);
//   ea0c->SetBranchAddress("bft_dnhits",&bft_dnhits);
//   ea0c->SetBranchAddress("bft_uhitpat",bft_uhitpat);
//   ea0c->SetBranchAddress("bft_dhitpat",bft_dhitpat);
//   ea0c->SetBranchAddress("bft_utdc",bft_utdc);
//   ea0c->SetBranchAddress("bft_dtdc",bft_dtdc);
//   ea0c->SetBranchAddress("bft_utrailing",bft_utrailing);
//   ea0c->SetBranchAddress("bft_dtrailing",bft_dtrailing);
//   ea0c->SetBranchAddress("bft_utot",bft_utot);
//   ea0c->SetBranchAddress("bft_dtot",bft_dtot);
//   ea0c->SetBranchAddress("bft_udepth",bft_udepth);
//   ea0c->SetBranchAddress("bft_ddepth",bft_ddepth);
//   ea0c->SetBranchAddress("bft_ncl",&bft_ncl);
//   ea0c->SetBranchAddress("bft_clsize",bft_clsize);
//   ea0c->SetBranchAddress("bft_ctime",bft_ctime);
//   ea0c->SetBranchAddress("bft_ctot",bft_ctot);
//   ea0c->SetBranchAddress("bft_clpos",bft_clpos);
//   ea0c->SetBranchAddress("sch_nhits",&sch_nhits);
//   ea0c->SetBranchAddress("sch_hitpat",sch_hitpat);
//   ea0c->SetBranchAddress("sch_tdc",sch_tdc);
//   ea0c->SetBranchAddress("sch_trailing",sch_trailing);
//   ea0c->SetBranchAddress("sch_tot",sch_tot);
//   ea0c->SetBranchAddress("sch_depth",sch_depth);
//   ea0c->SetBranchAddress("sch_ncl",&sch_ncl);
//   ea0c->SetBranchAddress("sch_clsize",sch_clsize);
//   ea0c->SetBranchAddress("sch_ctime",sch_ctime);
//   ea0c->SetBranchAddress("sch_ctot",sch_ctot);
//   ea0c->SetBranchAddress("sch_clpos",sch_clpos);
//   ea0c->SetBranchAddress("sftv_nhits",&sftv_nhits);
//   ea0c->SetBranchAddress("sftv_hitpat",sftv_hitpat);
   ea0c->SetBranchAddress("sftv_tdc",sftv_tdc);
//   ea0c->SetBranchAddress("sftv_trailing",sftv_trailing);
//   ea0c->SetBranchAddress("sftv_tot",sftv_tot);
//   ea0c->SetBranchAddress("sftv_depth",sftv_depth);
//   ea0c->SetBranchAddress("sftv_ncl",&sftv_ncl);
//   ea0c->SetBranchAddress("sftv_clsize",sftv_clsize);
//   ea0c->SetBranchAddress("sftv_ctime",sftv_ctime);
//   ea0c->SetBranchAddress("sftv_ctot",sftv_ctot);
//   ea0c->SetBranchAddress("sftv_clpos",sftv_clpos);
//   ea0c->SetBranchAddress("sftu_nhits",&sftu_nhits);
//   ea0c->SetBranchAddress("sftu_hitpat",sftu_hitpat);
   ea0c->SetBranchAddress("sftu_tdc",sftu_tdc);
//   ea0c->SetBranchAddress("sftu_trailing",sftu_trailing);
//   ea0c->SetBranchAddress("sftu_tot",sftu_tot);
//   ea0c->SetBranchAddress("sftu_depth",sftu_depth);
//   ea0c->SetBranchAddress("sftu_ncl",&sftu_ncl);
//   ea0c->SetBranchAddress("sftu_clsize",sftu_clsize);
//   ea0c->SetBranchAddress("sftu_ctime",sftu_ctime);
//   ea0c->SetBranchAddress("sftu_ctot",sftu_ctot);
//   ea0c->SetBranchAddress("sftu_clpos",sftu_clpos);
//   ea0c->SetBranchAddress("sftx_nhits",&sftx_nhits);
//   ea0c->SetBranchAddress("sftx_unhits",&sftx_unhits);
//   ea0c->SetBranchAddress("sftx_dnhits",&sftx_dnhits);
//   ea0c->SetBranchAddress("sftx_uhitpat",sftx_uhitpat);
//   ea0c->SetBranchAddress("sftx_dhitpat",sftx_dhitpat);
//   ea0c->SetBranchAddress("sftx_utdc",sftx_utdc);
//   ea0c->SetBranchAddress("sftx_dtdc",sftx_dtdc);
//   ea0c->SetBranchAddress("sftx_utrailing",sftx_utrailing);
//   ea0c->SetBranchAddress("sftx_dtrailing",sftx_dtrailing);
//   ea0c->SetBranchAddress("sftx_utot",sftx_utot);
//   ea0c->SetBranchAddress("sftx_dtot",sftx_dtot);
//   ea0c->SetBranchAddress("sftx_udepth",sftx_udepth);
//   ea0c->SetBranchAddress("sftx_ddepth",sftx_ddepth);
//   ea0c->SetBranchAddress("sftx_ncl",&sftx_ncl);
//   ea0c->SetBranchAddress("sftx_clsize",sftx_clsize);
//   ea0c->SetBranchAddress("sftx_ctime",sftx_ctime);
//   ea0c->SetBranchAddress("sftx_ctot",sftx_ctot);
//   ea0c->SetBranchAddress("sftx_clpos",sftx_clpos);


//     This is the loop skeleton
//       To read only selected branches, Insert statements like:
// tree->SetBranchStatus("*",0);  // disable all branches
// TTreePlayer->SetBranchStatus("branchname",1);  // activate branchname

   int MaxDepth = 16;

   TH1F *SFTVHitPat  = new TH1F("SFTVHitPat ","SFTVHitPat ",NumOfSegSFT_UV+1,0,NumOfSegSFT_UV+1);
   TH1F *SFTUHitPat  = new TH1F("SFTUHitPat ","SFTUHitPat ",NumOfSegSFT_UV+1,0,NumOfSegSFT_UV+1);
   TH1F *SFTXUHitPat = new TH1F("SFTXUHitPat","SFTXUHitPat",NumOfSegSFT_X+1,0,NumOfSegSFT_X+1);
   TH1F *SFTXDHitPat = new TH1F("SFTXDHitPat","SFTXDHitPat",NumOfSegSFT_X+1,0,NumOfSegSFT_X+1);

   TH1F *SFTVTDC  = new TH1F("SFTVTDC" ,"SFTVTDC" ,1000,0,1000);
   TH1F *SFTUTDC  = new TH1F("SFTUTDC" ,"SFTUTDC" ,1000,0,1000);
   TH1F *SFTXUTDC = new TH1F("SFTXUTDC","SFTXUTDC",1000,0,1000);
   TH1F *SFTXDTDC = new TH1F("SFTXDTDC","SFTXDTDC",1000,0,1000);

   Long64_t nentries = ea0c->GetEntries();
   double fitprm[3];

//Fit range
   double f_l  = 5; 

//Draw range
   double l = 50; 

//Integral range
   int range1 = 700; 
   int range2 = 1000; 
   int range3 = 1; 
   int range4 = 400; 
   int v_seg_range1 = 0; 
   int v_seg_range2 = 0; 

   int u_seg_range1 = 0; 
   int u_seg_range2 = 0; 

//Draw range
   int T0_range_min = -3000;
   int T0_range_max = 3000;

   TF1 *fit = new TF1("fit","gaus"); 
   

/////////////////////////////////////////////////////////////////////////////////////////////
//                                                                                         //
//    SFTX UD Plane rate  get code                                                         //
//                                                                                         //
/////////////////////////////////////////////////////////////////////////////////////////////

  SFTVHitPat  = (TH1F*)f->Get("h30004");
  SFTUHitPat  = (TH1F*)f->Get("h40004");
  SFTXUHitPat = (TH1F*)f->Get("h50004");
  SFTXDHitPat = (TH1F*)f->Get("h50005");
  
  SFTVTDC  = (TH1F*)f->Get("h30006");
  SFTUTDC  = (TH1F*)f->Get("h40006");
  SFTXUTDC = (TH1F*)f->Get("h50006");
  SFTXDTDC = (TH1F*)f->Get("h50007");
  
  TString pdf1 = Form("%s/pdf/trigger/SFTByPlaneScaler_%05d.pdf", anadir.Data(),runnum);
  TCanvas *c1 = new TCanvas("c1","c1",800,700); 
  c1->Print(pdf1+"["); 

  sftscr[2] = SFTXUTDC->Integral(range3,range4) + SFTXUTDC->Integral(range1,range2);
  sftscr[3] = SFTXDTDC->Integral(range3,range4) + SFTXDTDC->Integral(range1,range2);
  sftscr[4] += SFTXUTDC->Integral(range3,range2);
  sftscr[4] += SFTXDTDC->Integral(range3,range2);

  double max;
  double sigma;
  max = SFTVHitPat->GetMaximumBin();
  SFTVHitPat->Fit("fit","i","",max-20,max+20);
  max = fit->GetParameter(1);
  sigma = fit->GetParameter(2);
  
  v_seg_range1 = max - 1*sigma;
  v_seg_range2 = max + 1*sigma;

  max = SFTUHitPat->GetMaximumBin();
  SFTUHitPat->Fit("fit","i","",max-20,max+20);
  max = fit->GetParameter(1);
  sigma = fit->GetParameter(2);
  
  u_seg_range1 = max - 1*sigma;
  u_seg_range2 = max + 1*sigma;
  
  c1->cd(); 
  SFTVHitPat ->Draw(); 
  c1 ->Print(pdf1); 
  SFTUHitPat ->Draw(); 
  c1 ->Print(pdf1); 
  SFTXUHitPat->Draw(); 
  c1 ->Print(pdf1); 
  SFTXDHitPat->Draw(); 
  c1 ->Print(pdf1); 

  c1->cd(); 
  c1->SetGridx();
  c1->SetGridy();


/////////////////////////////////////////////////////////////////////////////////////////////
//                                                                                         //
//    SFT Beam  Mean get code                                                              //
//                                                                                         //
/////////////////////////////////////////////////////////////////////////////////////////////
   Long64_t nbytes = 0;
//   for (Long64_t s=0; s<nentries;s++) {
//      nbytes += ea0c->GetEntry(s);
////      if(s%10000 == 0) std::cout << s << std::endl;
//      for (int i=0; i<NumOfSegSFT_UV;i++) {
//        if(i>v_seg_range1 && i<v_seg_range2) continue;
//          if(sftv_tdc[i]>0){
//            for(int j=0; j<MaxDepth; j++){
//              SFTVTDC->Fill(sftv_tdc[i][j]);
//            }
//          }
//      }
//      for (int i=0; i<NumOfSegSFT_UV;i++) {
//        if(i>u_seg_range1 && i<u_seg_range2) continue;
//          if(sftu_tdc[i]>0){
//            for(int j=0; j<MaxDepth; j++){
//              SFTUTDC->Fill(sftu_tdc[i][j]);
//            }
//          }
//      }
//   }

  sftscr[0] = SFTVTDC->Integral(range3,range4)  + SFTVTDC->Integral(range1,range2);
  sftscr[1] = SFTUTDC->Integral(range3,range4)  + SFTUTDC->Integral(range1,range2);

  SFTVTDC ->Draw();
  c1 ->Print(pdf1); 
  SFTUTDC ->Draw();
  c1 ->Print(pdf1); 
  SFTXUTDC->Draw();
  c1 ->Print(pdf1); 
  SFTXDTDC->Draw();
  c1 ->Print(pdf1); 

  c1->Print(pdf1+"]");        

  
/////////////////////////////////////////////////////////////////////////////////////////////
//                                                                                         //
//    SFT Counts dat file maker                                                             //
//                                                                                         //
/////////////////////////////////////////////////////////////////////////////////////////////
  TString fout1 = (Form( "%s/dat/trigger/SFTByPlaneScaler_%05d.dat", anadir.Data() ,runnum));  
   
  std::ofstream fout_2(fout1.Data()); 
  for(int i=0; i<5; i++){
     fout_2 << Form("Plane%s",Plane[i]) <<  "\t"  << sftscr[i] << endl;
  }     

                             
}                            

void SFTByPlaneScaler( int month){
  for(int i=0; i<10; i++){
//    SFTByPlane_get(6, runnumber.at(i));
    SFTByPlane_get(6, runnumber[i]);
  }
//  for(int i=0; i<11; i++){
//    SFTByPlane_get(6, runnumber[i]);
//  }

//    SFTByPlane_get(6, 5272);

//  for(int i=0; i<6; i++){
//    SFTByPlane_get(6, runnumber1[i]);
//  }
//
//  for(int i=0; i<6; i++){
//    SFTByPlane_get(6, runnumber2[i]);
//  }

}
                             
