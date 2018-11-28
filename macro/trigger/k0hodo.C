{
//////////////////////////////////////////////////////////
//   This file has been automatically generated 
//     (Wed Nov 28 22:04:37 2018 by ROOT version6.10/08)
//   from TTree k0hodo/tree of DstKuramaEasirocHodoscope
//   found on file: rootfile/run05126_DstKuramaEasirocHodoscope.root
//////////////////////////////////////////////////////////


//Reset ROOT and connect tree file
   gROOT->Reset();
   TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("rootfile/run05126_DstKuramaEasirocHodoscope.root");
   if (!f) {
      f = new TFile("rootfile/run05126_DstKuramaEasirocHodoscope.root");
   }
    f->GetObject("k0hodo",tree);

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
   Double_t        csSac[41];
   Double_t        SacSeg[41];
   Double_t        tSac[41];
   Double_t        deSac[41];
   Int_t           nhTof;
   Double_t        csTof[17];
   Double_t        TofSeg[17];
   Double_t        tTof[17];
   Double_t        dtTof[17];
   Double_t        deTof[17];
   Int_t           tofnhits;
   Int_t           tofhitpat[24];
   Double_t        tofmt[24][16];
   Int_t           nhBft;
   Int_t           csBft[15];
   Double_t        tBft[15];
   Double_t        wBft[15];
   Double_t        BftPos[15];
   Int_t           sch_nhits;
   Int_t           sch_hitpat[26];
   Double_t        sch_tdc[64][16];
   Double_t        sch_trailing[64][16];
   Double_t        sch_tot[64][16];
   Int_t           sch_depth[64];
   Int_t           nhSch;
   Int_t           csSch[25];
   Double_t        tSch[25];
   Double_t        wSch[25];
   Double_t        SchPos[25];
   Int_t           sftx_nhits;
   Int_t           sftx_unhits;
   Int_t           sftx_dnhits;
   Int_t           sftx_uhitpat[94];
   Int_t           sftx_dhitpat[49];
   Double_t        sftx_utdc[256][16];
   Double_t        sftx_dtdc[256][16];
   Double_t        sftx_utrailing[256][16];
   Double_t        sftx_dtrailing[256][16];
   Double_t        sftx_utot[256][16];
   Double_t        sftx_dtot[256][16];
   Int_t           sftx_udepth[256];
   Int_t           sftx_ddepth[256];
   Int_t           sftx_ncl;
   Int_t           sftx_clsize[29];
   Double_t        sftx_ctime[29];
   Double_t        sftx_ctot[29];
   Double_t        sftx_clpos[29];
   Int_t           m2Combi;
   Double_t        beta[36];
   Double_t        stof[36];
   Double_t        m2[36];

   // Set branch addresses.
   k0hodo->SetBranchAddress("trigflag",trigflag);
   k0hodo->SetBranchAddress("trigpat",trigpat);
   k0hodo->SetBranchAddress("status",&status);
   k0hodo->SetBranchAddress("ntKurama",&ntKurama);
   k0hodo->SetBranchAddress("path",path);
   k0hodo->SetBranchAddress("pKurama",pKurama);
   k0hodo->SetBranchAddress("qKurama",qKurama);
   k0hodo->SetBranchAddress("chisqrKurama",chisqrKurama);
   k0hodo->SetBranchAddress("xtgtKurama",xtgtKurama);
   k0hodo->SetBranchAddress("ytgtKurama",ytgtKurama);
   k0hodo->SetBranchAddress("utgtKurama",utgtKurama);
   k0hodo->SetBranchAddress("vtgtKurama",vtgtKurama);
   k0hodo->SetBranchAddress("thetaKurama",thetaKurama);
   k0hodo->SetBranchAddress("vpx",vpx);
   k0hodo->SetBranchAddress("vpy",vpy);
   k0hodo->SetBranchAddress("tTofCalc",tTofCalc);
   k0hodo->SetBranchAddress("nhBh1",&nhBh1);
   k0hodo->SetBranchAddress("csBh1",csBh1);
   k0hodo->SetBranchAddress("Bh1Seg",Bh1Seg);
   k0hodo->SetBranchAddress("tBh1",tBh1);
   k0hodo->SetBranchAddress("dtBh1",dtBh1);
   k0hodo->SetBranchAddress("deBh1",deBh1);
   k0hodo->SetBranchAddress("btof",btof);
   k0hodo->SetBranchAddress("nhBh2",&nhBh2);
   k0hodo->SetBranchAddress("csBh2",csBh2);
   k0hodo->SetBranchAddress("Bh2Seg",Bh2Seg);
   k0hodo->SetBranchAddress("tBh2",tBh2);
   k0hodo->SetBranchAddress("dtBh2",dtBh2);
   k0hodo->SetBranchAddress("t0Bh2",t0Bh2);
   k0hodo->SetBranchAddress("deBh2",deBh2);
   k0hodo->SetBranchAddress("nhSac",&nhSac);
   k0hodo->SetBranchAddress("csSac",csSac);
   k0hodo->SetBranchAddress("SacSeg",SacSeg);
   k0hodo->SetBranchAddress("tSac",tSac);
   k0hodo->SetBranchAddress("deSac",deSac);
   k0hodo->SetBranchAddress("nhTof",&nhTof);
   k0hodo->SetBranchAddress("csTof",csTof);
   k0hodo->SetBranchAddress("TofSeg",TofSeg);
   k0hodo->SetBranchAddress("tTof",tTof);
   k0hodo->SetBranchAddress("dtTof",dtTof);
   k0hodo->SetBranchAddress("deTof",deTof);
   k0hodo->SetBranchAddress("tofnhits",&tofnhits);
   k0hodo->SetBranchAddress("tofhitpat",tofhitpat);
   k0hodo->SetBranchAddress("tofmt",tofmt);
   k0hodo->SetBranchAddress("nhBft",&nhBft);
   k0hodo->SetBranchAddress("csBft",csBft);
   k0hodo->SetBranchAddress("tBft",tBft);
   k0hodo->SetBranchAddress("wBft",wBft);
   k0hodo->SetBranchAddress("BftPos",BftPos);
   k0hodo->SetBranchAddress("sch_nhits",&sch_nhits);
   k0hodo->SetBranchAddress("sch_hitpat",sch_hitpat);
   k0hodo->SetBranchAddress("sch_tdc",sch_tdc);
   k0hodo->SetBranchAddress("sch_trailing",sch_trailing);
   k0hodo->SetBranchAddress("sch_tot",sch_tot);
   k0hodo->SetBranchAddress("sch_depth",sch_depth);
   k0hodo->SetBranchAddress("nhSch",&nhSch);
   k0hodo->SetBranchAddress("csSch",csSch);
   k0hodo->SetBranchAddress("tSch",tSch);
   k0hodo->SetBranchAddress("wSch",wSch);
   k0hodo->SetBranchAddress("SchPos",SchPos);
   k0hodo->SetBranchAddress("sftx_nhits",&sftx_nhits);
   k0hodo->SetBranchAddress("sftx_unhits",&sftx_unhits);
   k0hodo->SetBranchAddress("sftx_dnhits",&sftx_dnhits);
   k0hodo->SetBranchAddress("sftx_uhitpat",sftx_uhitpat);
   k0hodo->SetBranchAddress("sftx_dhitpat",sftx_dhitpat);
   k0hodo->SetBranchAddress("sftx_utdc",sftx_utdc);
   k0hodo->SetBranchAddress("sftx_dtdc",sftx_dtdc);
   k0hodo->SetBranchAddress("sftx_utrailing",sftx_utrailing);
   k0hodo->SetBranchAddress("sftx_dtrailing",sftx_dtrailing);
   k0hodo->SetBranchAddress("sftx_utot",sftx_utot);
   k0hodo->SetBranchAddress("sftx_dtot",sftx_dtot);
   k0hodo->SetBranchAddress("sftx_udepth",sftx_udepth);
   k0hodo->SetBranchAddress("sftx_ddepth",sftx_ddepth);
   k0hodo->SetBranchAddress("sftx_ncl",&sftx_ncl);
   k0hodo->SetBranchAddress("sftx_clsize",sftx_clsize);
   k0hodo->SetBranchAddress("sftx_ctime",sftx_ctime);
   k0hodo->SetBranchAddress("sftx_ctot",sftx_ctot);
   k0hodo->SetBranchAddress("sftx_clpos",sftx_clpos);
   k0hodo->SetBranchAddress("m2Combi",&m2Combi);
   k0hodo->SetBranchAddress("beta",beta);
   k0hodo->SetBranchAddress("stof",stof);
   k0hodo->SetBranchAddress("m2",m2);

//     This is the loop skeleton
//       To read only selected branches, Insert statements like:
// k0hodo->SetBranchStatus("*",0);  // disable all branches
// TTreePlayer->SetBranchStatus("branchname",1);  // activate branchname

   Long64_t nentries = k0hodo->GetEntries();

   Long64_t nbytes = 0;
//   for (Long64_t i=0; i<nentries;i++) {
//      nbytes += k0hodo->GetEntry(i);
//   }
}
