//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Fri Dec 21 01:57:55 2018 by ROOT version 6.10/08
// from TTree tree/tree of Counter
// found on file: analyzer_jun/rootfile/run05115_Hodoscope.root
//////////////////////////////////////////////////////////

#ifndef tree_h
#define tree_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.

class tree {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

// Fixed size dimensions of array or collections stored in the TTree if any.

   // Declaration of leaf types
   Int_t           evnum;
   Int_t           spill;
   Int_t           trignhits;
   Int_t           trigpat[17];   //[trignhits]
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

   // List of branches
   TBranch        *b_evnum;   //!
   TBranch        *b_spill;   //!
   TBranch        *b_trignhits;   //!
   TBranch        *b_trigpat;   //!
   TBranch        *b_trigflag;   //!
   TBranch        *b_bh1nhits;   //!
   TBranch        *b_bh1hitpat;   //!
   TBranch        *b_bh1ua;   //!
   TBranch        *b_bh1ut;   //!
   TBranch        *b_bh1da;   //!
   TBranch        *b_bh1dt;   //!
   TBranch        *b_bh2nhits;   //!
   TBranch        *b_bh2hitpat;   //!
   TBranch        *b_bh2ua;   //!
   TBranch        *b_bh2ut;   //!
   TBranch        *b_bh2da;   //!
   TBranch        *b_bh2dt;   //!
   TBranch        *b_fpga_bh2mtnhits;   //!
   TBranch        *b_fpga_bh2mthitpat;   //!
   TBranch        *b_fpga_bh2mt;   //!
   TBranch        *b_sacnhits;   //!
   TBranch        *b_sachitpat;   //!
   TBranch        *b_saca;   //!
   TBranch        *b_sact;   //!
   TBranch        *b_tofnhits;   //!
   TBranch        *b_tofhitpat;   //!
   TBranch        *b_tofua;   //!
   TBranch        *b_tofut;   //!
   TBranch        *b_tofda;   //!
   TBranch        *b_tofdt;   //!
   TBranch        *b_tofhtnhits;   //!
   TBranch        *b_tofhthitpat;   //!
   TBranch        *b_tofhtt;   //!
   TBranch        *b_lcnhits;   //!
   TBranch        *b_lchitpat;   //!
   TBranch        *b_lct;   //!
   TBranch        *b_bh1mt;   //!
   TBranch        *b_bh1de;   //!
   TBranch        *b_bh2mt;   //!
   TBranch        *b_bh2de;   //!
   TBranch        *b_sacmt;   //!
   TBranch        *b_sacde;   //!
   TBranch        *b_tofmt;   //!
   TBranch        *b_tofde;   //!
   TBranch        *b_tofhtmt;   //!
   TBranch        *b_lcmt;   //!
   TBranch        *b_t0;   //!
   TBranch        *b_ct0;   //!
   TBranch        *b_btof;   //!
   TBranch        *b_cbtof;   //!
   TBranch        *b_Time0Seg;   //!
   TBranch        *b_deTime0;   //!
   TBranch        *b_Time0;   //!
   TBranch        *b_CTime0;   //!
   TBranch        *b_Btof0Seg;   //!
   TBranch        *b_deBtof0;   //!
   TBranch        *b_Btof0;   //!
   TBranch        *b_CBtof0;   //!

   tree(TTree *tree=0);
   virtual ~tree();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef tree_cxx
tree::tree(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("analyzer_jun/rootfile/run05115_Hodoscope.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("analyzer_jun/rootfile/run05115_Hodoscope.root");
      }
      f->GetObject("tree",tree);

   }
   Init(tree);
}

tree::~tree()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t tree::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t tree::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (fChain->GetTreeNumber() != fCurrent) {
      fCurrent = fChain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void tree::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("evnum", &evnum, &b_evnum);
   fChain->SetBranchAddress("spill", &spill, &b_spill);
   fChain->SetBranchAddress("trignhits", &trignhits, &b_trignhits);
   fChain->SetBranchAddress("trigpat", trigpat, &b_trigpat);
   fChain->SetBranchAddress("trigflag", trigflag, &b_trigflag);
   fChain->SetBranchAddress("bh1nhits", &bh1nhits, &b_bh1nhits);
   fChain->SetBranchAddress("bh1hitpat", bh1hitpat, &b_bh1hitpat);
   fChain->SetBranchAddress("bh1ua", bh1ua, &b_bh1ua);
   fChain->SetBranchAddress("bh1ut", bh1ut, &b_bh1ut);
   fChain->SetBranchAddress("bh1da", bh1da, &b_bh1da);
   fChain->SetBranchAddress("bh1dt", bh1dt, &b_bh1dt);
   fChain->SetBranchAddress("bh2nhits", &bh2nhits, &b_bh2nhits);
   fChain->SetBranchAddress("bh2hitpat", bh2hitpat, &b_bh2hitpat);
   fChain->SetBranchAddress("bh2ua", bh2ua, &b_bh2ua);
   fChain->SetBranchAddress("bh2ut", bh2ut, &b_bh2ut);
   fChain->SetBranchAddress("bh2da", bh2da, &b_bh2da);
   fChain->SetBranchAddress("bh2dt", bh2dt, &b_bh2dt);
   fChain->SetBranchAddress("fpga_bh2mtnhits", &fpga_bh2mtnhits, &b_fpga_bh2mtnhits);
   fChain->SetBranchAddress("fpga_bh2mthitpat", fpga_bh2mthitpat, &b_fpga_bh2mthitpat);
   fChain->SetBranchAddress("fpga_bh2mt", fpga_bh2mt, &b_fpga_bh2mt);
   fChain->SetBranchAddress("sacnhits", &sacnhits, &b_sacnhits);
   fChain->SetBranchAddress("sachitpat", sachitpat, &b_sachitpat);
   fChain->SetBranchAddress("saca", saca, &b_saca);
   fChain->SetBranchAddress("sact", sact, &b_sact);
   fChain->SetBranchAddress("tofnhits", &tofnhits, &b_tofnhits);
   fChain->SetBranchAddress("tofhitpat", tofhitpat, &b_tofhitpat);
   fChain->SetBranchAddress("tofua", tofua, &b_tofua);
   fChain->SetBranchAddress("tofut", tofut, &b_tofut);
   fChain->SetBranchAddress("tofda", tofda, &b_tofda);
   fChain->SetBranchAddress("tofdt", tofdt, &b_tofdt);
   fChain->SetBranchAddress("tofhtnhits", &tofhtnhits, &b_tofhtnhits);
   fChain->SetBranchAddress("tofhthitpat", tofhthitpat, &b_tofhthitpat);
   fChain->SetBranchAddress("tofhtt", tofhtt, &b_tofhtt);
   fChain->SetBranchAddress("lcnhits", &lcnhits, &b_lcnhits);
   fChain->SetBranchAddress("lchitpat", lchitpat, &b_lchitpat);
   fChain->SetBranchAddress("lct", lct, &b_lct);
   fChain->SetBranchAddress("bh1mt", bh1mt, &b_bh1mt);
   fChain->SetBranchAddress("bh1de", bh1de, &b_bh1de);
   fChain->SetBranchAddress("bh2mt", bh2mt, &b_bh2mt);
   fChain->SetBranchAddress("bh2de", bh2de, &b_bh2de);
   fChain->SetBranchAddress("sacmt", sacmt, &b_sacmt);
   fChain->SetBranchAddress("sacde", sacde, &b_sacde);
   fChain->SetBranchAddress("tofmt", tofmt, &b_tofmt);
   fChain->SetBranchAddress("tofde", tofde, &b_tofde);
   fChain->SetBranchAddress("tofhtmt", tofhtmt, &b_tofhtmt);
   fChain->SetBranchAddress("lcmt", lcmt, &b_lcmt);
   fChain->SetBranchAddress("t0", t0, &b_t0);
   fChain->SetBranchAddress("ct0", ct0, &b_ct0);
   fChain->SetBranchAddress("btof", btof, &b_btof);
   fChain->SetBranchAddress("cbtof", cbtof, &b_cbtof);
   fChain->SetBranchAddress("Time0Seg", &Time0Seg, &b_Time0Seg);
   fChain->SetBranchAddress("deTime0", &deTime0, &b_deTime0);
   fChain->SetBranchAddress("Time0", &Time0, &b_Time0);
   fChain->SetBranchAddress("CTime0", &CTime0, &b_CTime0);
   fChain->SetBranchAddress("Btof0Seg", &Btof0Seg, &b_Btof0Seg);
   fChain->SetBranchAddress("deBtof0", &deBtof0, &b_deBtof0);
   fChain->SetBranchAddress("Btof0", &Btof0, &b_Btof0);
   fChain->SetBranchAddress("CBtof0", &CBtof0, &b_CBtof0);
   Notify();
}

Bool_t tree::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void tree::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t tree::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef tree_cxx
