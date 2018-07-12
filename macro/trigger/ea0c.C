{
//////////////////////////////////////////////////////////
//   This file has been automatically generated 
//     (Fri Jul 13 02:16:14 2018 by ROOT version6.10/08)
//   from TTree ea0c/tree of Easiroc
//   found on file: run05080_Easiroc.root
//////////////////////////////////////////////////////////


//Reset ROOT and connect tree file
   gROOT->Reset();
   TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("run05080_Easiroc.root");
   if (!f) {
      f = new TFile("run05080_Easiroc.root");
   }
    f->GetObject("ea0c",tree);

//Declaration of leaves types
   Int_t           evnum;
   Int_t           trignhits;
   Int_t           trigpat[32];
   Int_t           trigflag[32];
   Int_t           bft_ncl;
   Int_t           bft_clsize[92];
   Double_t        bft_ctime[92];
   Double_t        bft_ctot[92];
   Double_t        bft_clpos[92];
   Int_t           sch_ncl;
   Int_t           sch_clsize[64];
   Double_t        sch_ctime[64];
   Double_t        sch_ctot[64];
   Double_t        sch_clpos[64];
   Int_t           sftv_ncl;
   Int_t           sftv_clsize[190];
   Double_t        sftv_ctime[190];
   Double_t        sftv_ctot[190];
   Double_t        sftv_clpos[190];
   Int_t           sftu_ncl;
   Int_t           sftu_clsize[153];
   Double_t        sftu_ctime[153];
   Double_t        sftu_ctot[153];
   Double_t        sftu_clpos[153];
   Int_t           sftx_ncl;
   Int_t           sftx_clsize[55];
   Double_t        sftx_ctime[55];
   Double_t        sftx_ctot[55];
   Double_t        sftx_clpos[55];
   Int_t           fbt1_u1ncl;
   Int_t           fbt1_d1ncl;
   Int_t           fbt1_u2ncl;
   Int_t           fbt1_d2ncl;
   Int_t           fbt1_u1clsize[28];
   Int_t           fbt1_d1clsize[16];
   Int_t           fbt1_u2clsize[38];
   Int_t           fbt1_d2clsize[15];
   Double_t        fbt1_u1ctime[28];
   Double_t        fbt1_d1ctime[16];
   Double_t        fbt1_u2ctime[38];
   Double_t        fbt1_d2ctime[15];
   Double_t        fbt1_u1ctot[28];
   Double_t        fbt1_d1ctot[16];
   Double_t        fbt1_u2ctot[38];
   Double_t        fbt1_d2ctot[15];
   Double_t        fbt1_u1clpos[28];
   Double_t        fbt1_d1clpos[16];
   Double_t        fbt1_u2clpos[38];
   Double_t        fbt1_d2clpos[15];
   Int_t           fbt2_u1ncl;
   Int_t           fbt2_d1ncl;
   Int_t           fbt2_u2ncl;
   Int_t           fbt2_d2ncl;
   Int_t           fbt2_u1clsize[64];
   Int_t           fbt2_d1clsize[16];
   Int_t           fbt2_u2clsize[64];
   Int_t           fbt2_d2clsize[30];
   Double_t        fbt2_u1ctime[64];
   Double_t        fbt2_d1ctime[16];
   Double_t        fbt2_u2ctime[64];
   Double_t        fbt2_d2ctime[30];
   Double_t        fbt2_u1ctot[64];
   Double_t        fbt2_d1ctot[16];
   Double_t        fbt2_u2ctot[64];
   Double_t        fbt2_d2ctot[30];
   Double_t        fbt2_u1clpos[64];
   Double_t        fbt2_d1clpos[16];
   Double_t        fbt2_u2clpos[64];
   Double_t        fbt2_d2clpos[30];

   // Set branch addresses.
   ea0c->SetBranchAddress("evnum",&evnum);
   ea0c->SetBranchAddress("trignhits",&trignhits);
   ea0c->SetBranchAddress("trigpat",trigpat);
   ea0c->SetBranchAddress("trigflag",trigflag);
   ea0c->SetBranchAddress("bft_ncl",&bft_ncl);
   ea0c->SetBranchAddress("bft_clsize",bft_clsize);
   ea0c->SetBranchAddress("bft_ctime",bft_ctime);
   ea0c->SetBranchAddress("bft_ctot",bft_ctot);
   ea0c->SetBranchAddress("bft_clpos",bft_clpos);
   ea0c->SetBranchAddress("sch_ncl",&sch_ncl);
   ea0c->SetBranchAddress("sch_clsize",sch_clsize);
   ea0c->SetBranchAddress("sch_ctime",sch_ctime);
   ea0c->SetBranchAddress("sch_ctot",sch_ctot);
   ea0c->SetBranchAddress("sch_clpos",sch_clpos);
   ea0c->SetBranchAddress("sftv_ncl",&sftv_ncl);
   ea0c->SetBranchAddress("sftv_clsize",sftv_clsize);
   ea0c->SetBranchAddress("sftv_ctime",sftv_ctime);
   ea0c->SetBranchAddress("sftv_ctot",sftv_ctot);
   ea0c->SetBranchAddress("sftv_clpos",sftv_clpos);
   ea0c->SetBranchAddress("sftu_ncl",&sftu_ncl);
   ea0c->SetBranchAddress("sftu_clsize",sftu_clsize);
   ea0c->SetBranchAddress("sftu_ctime",sftu_ctime);
   ea0c->SetBranchAddress("sftu_ctot",sftu_ctot);
   ea0c->SetBranchAddress("sftu_clpos",sftu_clpos);
   ea0c->SetBranchAddress("sftx_ncl",&sftx_ncl);
   ea0c->SetBranchAddress("sftx_clsize",sftx_clsize);
   ea0c->SetBranchAddress("sftx_ctime",sftx_ctime);
   ea0c->SetBranchAddress("sftx_ctot",sftx_ctot);
   ea0c->SetBranchAddress("sftx_clpos",sftx_clpos);
   ea0c->SetBranchAddress("fbt1_u1ncl",&fbt1_u1ncl);
   ea0c->SetBranchAddress("fbt1_d1ncl",&fbt1_d1ncl);
   ea0c->SetBranchAddress("fbt1_u2ncl",&fbt1_u2ncl);
   ea0c->SetBranchAddress("fbt1_d2ncl",&fbt1_d2ncl);
   ea0c->SetBranchAddress("fbt1_u1clsize",fbt1_u1clsize);
   ea0c->SetBranchAddress("fbt1_d1clsize",fbt1_d1clsize);
   ea0c->SetBranchAddress("fbt1_u2clsize",fbt1_u2clsize);
   ea0c->SetBranchAddress("fbt1_d2clsize",fbt1_d2clsize);
   ea0c->SetBranchAddress("fbt1_u1ctime",fbt1_u1ctime);
   ea0c->SetBranchAddress("fbt1_d1ctime",fbt1_d1ctime);
   ea0c->SetBranchAddress("fbt1_u2ctime",fbt1_u2ctime);
   ea0c->SetBranchAddress("fbt1_d2ctime",fbt1_d2ctime);
   ea0c->SetBranchAddress("fbt1_u1ctot",fbt1_u1ctot);
   ea0c->SetBranchAddress("fbt1_d1ctot",fbt1_d1ctot);
   ea0c->SetBranchAddress("fbt1_u2ctot",fbt1_u2ctot);
   ea0c->SetBranchAddress("fbt1_d2ctot",fbt1_d2ctot);
   ea0c->SetBranchAddress("fbt1_u1clpos",fbt1_u1clpos);
   ea0c->SetBranchAddress("fbt1_d1clpos",fbt1_d1clpos);
   ea0c->SetBranchAddress("fbt1_u2clpos",fbt1_u2clpos);
   ea0c->SetBranchAddress("fbt1_d2clpos",fbt1_d2clpos);
   ea0c->SetBranchAddress("fbt2_u1ncl",&fbt2_u1ncl);
   ea0c->SetBranchAddress("fbt2_d1ncl",&fbt2_d1ncl);
   ea0c->SetBranchAddress("fbt2_u2ncl",&fbt2_u2ncl);
   ea0c->SetBranchAddress("fbt2_d2ncl",&fbt2_d2ncl);
   ea0c->SetBranchAddress("fbt2_u1clsize",fbt2_u1clsize);
   ea0c->SetBranchAddress("fbt2_d1clsize",fbt2_d1clsize);
   ea0c->SetBranchAddress("fbt2_u2clsize",fbt2_u2clsize);
   ea0c->SetBranchAddress("fbt2_d2clsize",fbt2_d2clsize);
   ea0c->SetBranchAddress("fbt2_u1ctime",fbt2_u1ctime);
   ea0c->SetBranchAddress("fbt2_d1ctime",fbt2_d1ctime);
   ea0c->SetBranchAddress("fbt2_u2ctime",fbt2_u2ctime);
   ea0c->SetBranchAddress("fbt2_d2ctime",fbt2_d2ctime);
   ea0c->SetBranchAddress("fbt2_u1ctot",fbt2_u1ctot);
   ea0c->SetBranchAddress("fbt2_d1ctot",fbt2_d1ctot);
   ea0c->SetBranchAddress("fbt2_u2ctot",fbt2_u2ctot);
   ea0c->SetBranchAddress("fbt2_d2ctot",fbt2_d2ctot);
   ea0c->SetBranchAddress("fbt2_u1clpos",fbt2_u1clpos);
   ea0c->SetBranchAddress("fbt2_d1clpos",fbt2_d1clpos);
   ea0c->SetBranchAddress("fbt2_u2clpos",fbt2_u2clpos);
   ea0c->SetBranchAddress("fbt2_d2clpos",fbt2_d2clpos);

//     This is the loop skeleton
//       To read only selected branches, Insert statements like:
// ea0c->SetBranchStatus("*",0);  // disable all branches
// TTreePlayer->SetBranchStatus("branchname",1);  // activate branchname

   Long64_t nentries = ea0c->GetEntries();

   Long64_t nbytes = 0;
//   for (Long64_t i=0; i<nentries;i++) {
//      nbytes += ea0c->GetEntry(i);
//   }
}
