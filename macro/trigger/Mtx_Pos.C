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

void Mtx_Pos(int month,int runnum){

  gStyle->SetOptStat(1111110); 
  gStyle->SetOptFit(1); 

//Reset ROOT and connect tree file
   gROOT->Reset();
   gROOT->Reset();
   TString anadir=Form("%s/work/e40/ana",std::getenv("HOME")); 
   TString pdf = Form("%s/pdf/trigger/Mtx_Pos_run%05d.pdf", anadir.Data(),runnum);
   TString pdfDhire = Form("%s/pdf/trigger", anadir.Data());
//   TFile *f = new TFile(Form("%s/analyzer_%s/rootfile/trigf19_tofht.root", anadir.Data(),Month[month]),"READ");
   TFile *f = new TFile(Form("%s/analyzer_%s/rootfile/run%05d_DstKuramaEasirocHodoscope_BH2TOF.root", anadir.Data(),Month[month],runnum),"READ");
   TTree *k0hodo;
    f->GetObject("k0hodo",k0hodo);

// Declaration of leaves types-----------------------------------------------------------------------
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
   Double_t        tofsegKurama[4];
   Double_t        vpx[5];
   Double_t        vpy[5];
   Int_t           vpseg[5];
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
   Double_t        delta_x[25];
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


// Select Branch ------------------------------------------------------------------------------------
   k0hodo->SetBranchStatus("*", 0);
   k0hodo->SetBranchStatus("trigflag");
   k0hodo->SetBranchStatus("trigpat");
   k0hodo->SetBranchStatus("status");
   k0hodo->SetBranchStatus("ntKurama");
   k0hodo->SetBranchStatus("path");
   k0hodo->SetBranchStatus("pKurama");
   k0hodo->SetBranchStatus("qKurama");
   k0hodo->SetBranchStatus("chisqrKurama");
   k0hodo->SetBranchStatus("xtgtKurama");
   k0hodo->SetBranchStatus("ytgtKurama");
   k0hodo->SetBranchStatus("utgtKurama");
   k0hodo->SetBranchStatus("vtgtKurama");
   k0hodo->SetBranchStatus("thetaKurama");
   k0hodo->SetBranchStatus("tofsegKurama");
   k0hodo->SetBranchStatus("vpx");
   k0hodo->SetBranchStatus("vpy");
   k0hodo->SetBranchStatus("vpseg");
//   k0hodo->SetBranchStatus("tTofCalc");
//   k0hodo->SetBranchStatus("nhBh1");
//   k0hodo->SetBranchStatus("csBh1");
//   k0hodo->SetBranchStatus("Bh1Seg");
//   k0hodo->SetBranchStatus("tBh1");
//   k0hodo->SetBranchStatus("dtBh1");
//   k0hodo->SetBranchStatus("deBh1");
//   k0hodo->SetBranchStatus("btof");
//   k0hodo->SetBranchStatus("nhBh2");
//   k0hodo->SetBranchStatus("csBh2");
//   k0hodo->SetBranchStatus("Bh2Seg");
//   k0hodo->SetBranchStatus("tBh2");
//   k0hodo->SetBranchStatus("dtBh2");
//   k0hodo->SetBranchStatus("t0Bh2");
//   k0hodo->SetBranchStatus("deBh2");
//   k0hodo->SetBranchStatus("nhSac");
//   k0hodo->SetBranchStatus("csSac");
//   k0hodo->SetBranchStatus("SacSeg");
//   k0hodo->SetBranchStatus("tSac");
//   k0hodo->SetBranchStatus("deSac");
   k0hodo->SetBranchStatus("nhTof");
   k0hodo->SetBranchStatus("csTof");
   k0hodo->SetBranchStatus("TofSeg");
   k0hodo->SetBranchStatus("tTof");
   k0hodo->SetBranchStatus("dtTof");
   k0hodo->SetBranchStatus("deTof");
//   k0hodo->SetBranchStatus("tofnhits");
//   k0hodo->SetBranchStatus("tofhitpat");
//   k0hodo->SetBranchStatus("tofmt");
//   k0hodo->SetBranchStatus("nhBft");
//   k0hodo->SetBranchStatus("csBft");
//   k0hodo->SetBranchStatus("tBft");
//   k0hodo->SetBranchStatus("wBft");
//   k0hodo->SetBranchStatus("BftPos");
//   k0hodo->SetBranchStatus("sch_nhits");
//   k0hodo->SetBranchStatus("sch_hitpat");
//   k0hodo->SetBranchStatus("sch_tdc");
//   k0hodo->SetBranchStatus("sch_trailing");
//   k0hodo->SetBranchStatus("sch_tot");
//   k0hodo->SetBranchStatus("sch_depth");
   k0hodo->SetBranchStatus("nhSch");
   k0hodo->SetBranchStatus("csSch");
   k0hodo->SetBranchStatus("tSch");
   k0hodo->SetBranchStatus("wSch");
   k0hodo->SetBranchStatus("SchPos");
   k0hodo->SetBranchStatus("delta_x");
//   k0hodo->SetBranchStatus("sftx_nhits");
//   k0hodo->SetBranchStatus("sftx_unhits");
//   k0hodo->SetBranchStatus("sftx_dnhits"
//   k0hodo->SetBranchStatus("sftx_uhitpat");
//   k0hodo->SetBranchStatus("sftx_dhitpat");
//   k0hodo->SetBranchStatus("sftx_utdc");
//   k0hodo->SetBranchStatus("sftx_dtdc");
//   k0hodo->SetBranchStatus("sftx_utrailing");
//   k0hodo->SetBranchStatus("sftx_dtrailing");
//   k0hodo->SetBranchStatus("sftx_utot");
//   k0hodo->SetBranchStatus("sftx_dtot");
//   k0hodo->SetBranchStatus("sftx_udepth");
//   k0hodo->SetBranchStatus("sftx_ddepth");
   k0hodo->SetBranchStatus("sftx_ncl");
   k0hodo->SetBranchStatus("sftx_clsize");
   k0hodo->SetBranchStatus("sftx_ctime");
   k0hodo->SetBranchStatus("sftx_ctot");
   k0hodo->SetBranchStatus("sftx_clpos");
   k0hodo->SetBranchStatus("m2Combi");
   k0hodo->SetBranchStatus("beta");
   k0hodo->SetBranchStatus("stof");
   k0hodo->SetBranchStatus("m2");


// Set branch addresses -----------------------------------------------------------------------------
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
   k0hodo->SetBranchAddress("tofsegKurama",tofsegKurama);
   k0hodo->SetBranchAddress("vpx",vpx);
   k0hodo->SetBranchAddress("vpy",vpy);
   k0hodo->SetBranchAddress("vpseg",vpseg);
//   k0hodo->SetBranchAddress("tTofCalc",tTofCalc);
//   k0hodo->SetBranchAddress("nhBh1",&nhBh1);
//   k0hodo->SetBranchAddress("csBh1",csBh1);
//   k0hodo->SetBranchAddress("Bh1Seg",Bh1Seg);
//   k0hodo->SetBranchAddress("tBh1",tBh1);
//   k0hodo->SetBranchAddress("dtBh1",dtBh1);
//   k0hodo->SetBranchAddress("deBh1",deBh1);
//   k0hodo->SetBranchAddress("btof",btof);
//   k0hodo->SetBranchAddress("nhBh2",&nhBh2);
//   k0hodo->SetBranchAddress("csBh2",csBh2);
//   k0hodo->SetBranchAddress("Bh2Seg",Bh2Seg);
//   k0hodo->SetBranchAddress("tBh2",tBh2);
//   k0hodo->SetBranchAddress("dtBh2",dtBh2);
//   k0hodo->SetBranchAddress("t0Bh2",t0Bh2);
//   k0hodo->SetBranchAddress("deBh2",deBh2);
//   k0hodo->SetBranchAddress("nhSac",&nhSac);
//   k0hodo->SetBranchAddress("csSac",csSac);
//   k0hodo->SetBranchAddress("SacSeg",SacSeg);
//   k0hodo->SetBranchAddress("tSac",tSac);
//   k0hodo->SetBranchAddress("deSac",deSac);
   k0hodo->SetBranchAddress("nhTof",&nhTof);
   k0hodo->SetBranchAddress("csTof",csTof);
   k0hodo->SetBranchAddress("TofSeg",TofSeg);
   k0hodo->SetBranchAddress("tTof",tTof);
   k0hodo->SetBranchAddress("dtTof",dtTof);
   k0hodo->SetBranchAddress("deTof",deTof);
//   k0hodo->SetBranchAddress("tofnhits",&tofnhits);
//   k0hodo->SetBranchAddress("tofhitpat",tofhitpat);
//   k0hodo->SetBranchAddress("tofmt",tofmt);
//   k0hodo->SetBranchAddress("nhBft",&nhBft);
//   k0hodo->SetBranchAddress("csBft",csBft);
//   k0hodo->SetBranchAddress("tBft",tBft);
//   k0hodo->SetBranchAddress("wBft",wBft);
//   k0hodo->SetBranchAddress("BftPos",BftPos);
//   k0hodo->SetBranchAddress("sch_nhits",&sch_nhits);
//   k0hodo->SetBranchAddress("sch_hitpat",sch_hitpat);
//   k0hodo->SetBranchAddress("sch_tdc",sch_tdc);
//   k0hodo->SetBranchAddress("sch_trailing",sch_trailing);
//   k0hodo->SetBranchAddress("sch_tot",sch_tot);
//   k0hodo->SetBranchAddress("sch_depth",sch_depth);
   k0hodo->SetBranchAddress("nhSch",&nhSch);
   k0hodo->SetBranchAddress("csSch",csSch);
   k0hodo->SetBranchAddress("tSch",tSch);
   k0hodo->SetBranchAddress("wSch",wSch);
   k0hodo->SetBranchAddress("SchPos",SchPos);
   k0hodo->SetBranchAddress("delta_x",delta_x);
//   k0hodo->SetBranchAddress("sftx_nhits",&sftx_nhits);
//   k0hodo->SetBranchAddress("sftx_unhits",&sftx_unhits);
//   k0hodo->SetBranchAddress("sftx_dnhits",&sftx_dnhits);
//   k0hodo->SetBranchAddress("sftx_uhitpat",sftx_uhitpat);
//   k0hodo->SetBranchAddress("sftx_dhitpat",sftx_dhitpat);
//   k0hodo->SetBranchAddress("sftx_utdc",sftx_utdc);
//   k0hodo->SetBranchAddress("sftx_dtdc",sftx_dtdc);
//   k0hodo->SetBranchAddress("sftx_utrailing",sftx_utrailing);
//   k0hodo->SetBranchAddress("sftx_dtrailing",sftx_dtrailing);
//   k0hodo->SetBranchAddress("sftx_utot",sftx_utot);
//   k0hodo->SetBranchAddress("sftx_dtot",sftx_dtot);
//   k0hodo->SetBranchAddress("sftx_udepth",sftx_udepth);
//   k0hodo->SetBranchAddress("sftx_ddepth",sftx_ddepth);
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
// kurama->SetBranchStatus("*",0);  // disable all branches
// TTreePlayer->SetBranchStatus("branchname",1);  // activate branchname

//
//-para def-----------------------------------------------------------------------------------------
   double HULMHTDCCalib = -0.8333;

   int Hist1Max = 0;
   int Hist2Max = 0;

   int chisqr = 0;

//-hist def-----------------------------------------------------------------------------------------
   Hist1Max = 34;
   Hist2Max =  16;
   chisqr = 10;
   TH1D *Hist1[Hist1Max];
   TH2D *Hist2[Hist2Max];

    Hist1[0 ]= new TH1D("pKurama","pKurama",100,0,2);
    Hist1[1 ]= new TH1D("m2","m2",100,-0.4,1.4);
    Hist1[2 ]= new TH1D("chisqrKurama","chisqrKurama",100,0,200);
    Hist1[3 ]= new TH1D("qKurama","qKurama",6,-3,3);
    Hist1[4 ]= new TH1D("vpx[1]","vpx[1]",200,-400,400);
    Hist1[5 ]= new TH1D("vpy[1]","vpy[1]",200,-400,400);
    Hist1[6 ]= new TH1D("vpseg[1]","vpseg[1]",64,1,65);
    Hist1[7 ]= new TH1D("pKurama Cut1","pKurama Cut1",100,0,2);
    Hist1[8 ]= new TH1D("m2 Cut1","m2 Cut1",100,-0.4,1.4);
    Hist1[9 ]= new TH1D("chisqrKurama Cut1","chisqrKurama Cut1",100,0,200);
    Hist1[10]= new TH1D("qKurama Cut1","qKurama Cut1",6,-3,3);
    Hist1[11]= new TH1D("vpx[1] Cut1","vpx[1] Cut1",200,-400,400);
    Hist1[12]= new TH1D("vpy[1] Cut1","vpy[1] Cut1",200,-400,400);
    Hist1[13]= new TH1D("vpseg[1] Cut1","vpseg[1] Cut1",64,1,65);
    Hist1[14]= new TH1D("pKurama Cut2","pKurama Cut2",100,0,2);
    Hist1[15]= new TH1D("m2 Cut2","m2 Cut2",100,-0.4,1.4);
    Hist1[16]= new TH1D("chisqrKurama Cut2","chisqrKurama Cut2",100,0,200);
    Hist1[17]= new TH1D("qKurama Cut2","qKurama Cut2",6,-3,3);
    Hist1[18]= new TH1D("vpx[1] Cut2","vpx[1] Cut2",200,-400,400);
    Hist1[19]= new TH1D("vpy[1] Cut2","vpy[1] Cut2",200,-400,400);
    Hist1[20]= new TH1D("vpseg[1] Cut2","vpseg[1] Cut2",64,1,65);
    Hist1[21]= new TH1D("TofSeg[0]","TofSeg[0]",24,1,25);
    Hist1[22]= new TH1D("TofSeg[0] Cut1","TofSeg[0] Cut1",24,1,25);
    Hist1[23]= new TH1D("TofSeg[0] Cut2","TofSeg[0] Cut2",24,1,25);
    Hist1[24]= new TH1D("delta_x","delta_x",200,-100,100);
    Hist1[25]= new TH1D("Sch Position by HitSegment","Sch Position by HitSegment",50,-400,400);
    Hist1[26]= new TH1D("tofsegKurama[0]","tofsegKurama[0]",24,1,25);
    Hist1[27]= new TH1D("tofsegKurama[0] Cut1","tofsegKurama[0] Cut1",24,1,25);
    Hist1[28]= new TH1D("tofsegKurama[0] Cut2","tofsegKurama[0] Cut2",24,1,25);
    Hist1[29]= new TH1D("vpseg[1] Cut3","vpseg[1] Cut3",64,1,65);
    Hist1[30]= new TH1D("TofSeg[0] Cut3","TofSeg[0] Cut3",24,1,25);
    Hist1[31]= new TH1D("tofsegKurama[0] Cut3","tofsegKurama[0] Cut3",24,1,25);
    Hist1[32]= new TH1D("vpx[1] Cut3","vpx[1] Cut3",200,-400,400);
    Hist1[33]= new TH1D("Sch Position by HitSegment Cut3","Sch Position by HitSegment Cut3",50,-400,400);


            

    Hist2[0 ]= new TH2D("pKurama % m2",     "pKurama % m2 "    ,100,-0.4,1.4,100,0,2);
    Hist2[1 ]= new TH2D("vpy[1] % vpx[1]     ","vpy[1] % vpx[1]     ",100,-400,400,100,-400,400);
    Hist2[2 ]= new TH2D("pKurama % m2 Cut1",     "pKurama % m2 Cut1 "    ,100,-0.4,1.4,100,0,2);
    Hist2[3 ]= new TH2D("vpy[1] % vpx[1] Cut1     ","vpy[1] % vpx[1] Cut1     ",100,-400,400,100,-400,400);
    Hist2[4 ]= new TH2D("pKurama % m2 Cut2",     "pKurama % m2 Cut2 "    ,100,-0.4,1.4,100,0,2);
    Hist2[5 ]= new TH2D("vpy[1] % vpx[1] Cut2     ","vpy[1] % vpx[1] Cut2     ",100,-400,400,100,-400,400);
    Hist2[6 ]= new TH2D("TofSeg[0] % vpseg[1]","TofSeg[0] % vpseg[1]",64,1,65,24,1,25);
    Hist2[7 ]= new TH2D("TofSeg[0] % vpseg[1] Cut1","TofSeg[0] % vpseg[1] Cut1",64,1,65,24,1,25);
    Hist2[8 ]= new TH2D("TofSeg[0] % vpseg[1] Cut2","TofSeg[0] % vpseg[1] Cut2",64,1,65,24,1,25);
    Hist2[9 ]= new TH2D("Sch Position by HitSegment % vpx[1]","Sch Position by HitSegment % vpx[1]",50,-400,400,100,-400,400);
    Hist2[10]= new TH2D("tofsegKurama[0] % vpseg[1]","tofsegKurama[0] % vpseg[1]",64,1,65,24,1,25);
    Hist2[11]= new TH2D("tofsegKurama[0] % vpseg[1] Cut1","tofsegKurama[0] % vpseg[1] Cut1",64,1,65,24,1,25);
    Hist2[12]= new TH2D("tofsegKurama[0] % vpseg[1] Cut2","tofsegKurama[0] % vpseg[1] Cut2",64,1,65,24,1,25);
    Hist2[13]= new TH2D("TofSeg[0] % vpseg[1] Cut3","TofSeg[0] % vpseg[1] Cut3",64,1,65,24,1,25);
    Hist2[14]= new TH2D("tofsegKurama[0] % vpseg[1] Cut3","tofsegKurama[0] % vpseg[1] Cut3",64,1,65,24,1,25);
    Hist2[15]= new TH2D("Sch Position by HitSegment % vpx[1] Cut3","Sch Position by HitSegment % vpx[1] Cut3",50,-400,400,100,-400,400);

//-Legend def --------------------------------------------------------------------------------------

//-Event Loop --------------------------------------------------------------------------------------
   Long64_t nentries = k0hodo->GetEntries();
//   Long64_t nentries = 10000;

//-Event Loop First --------
   Long64_t nbytes = 0;
   for (Long64_t s=0; s<nentries;s++) {
     nbytes += k0hodo->GetEntry(s);
     //     for(int i=0; i<ntKurama; i++){
     if( ntKurama!=1) continue;
     bool sch_flag = false;

     for(int i=0; i<nhSch; i++){
       Hist1[24]->Fill(delta_x[i]);
       Hist1[25]->Fill(SchPos[i]);
       Hist2[9 ]->Fill(SchPos[i],vpx[1]);
       if(delta_x[i]<-10 || delta_x[i]>10) continue;
       sch_flag = true;
       Hist1[32]->Fill(vpx[1]);
       Hist1[33]->Fill(SchPos[i]);
       Hist2[15]->Fill(SchPos[i],vpx[1]);
     }

     int i=0;
     Hist1[0 ]->Fill(pKurama[i]);
     Hist1[1 ]->Fill(m2[i]);
     Hist1[2 ]->Fill(chisqrKurama[i]);
     Hist1[3 ]->Fill(qKurama[i]);
     Hist1[4 ]->Fill(vpx[1]);
     Hist1[5 ]->Fill(vpy[1]);
     Hist1[6 ]->Fill(vpseg[1]);
     Hist1[21]->Fill(TofSeg[i]);
     Hist1[26]->Fill(tofsegKurama[i]);

     Hist2[0 ]->Fill(m2[i],pKurama[i]);
     Hist2[1 ]->Fill(vpx[1],vpy[1]);
     Hist2[6 ]->Fill(vpseg[1],TofSeg[i]);
     Hist2[10]->Fill(vpseg[1],tofsegKurama[i]);
     if(sch_flag){
       Hist1[29]->Fill(vpseg[1]);
       Hist1[30]->Fill(TofSeg[i]);
       Hist1[31]->Fill(tofsegKurama[i]);
       Hist2[13]->Fill(vpseg[1],TofSeg[i]);
       Hist2[14]->Fill(vpseg[1],tofsegKurama[i]);
     }

     if(chisqrKurama[i]<chisqr&&qKurama[i]>0){
       Hist1[7 ]->Fill(pKurama[i]);
       Hist1[8 ]->Fill(m2[i]);
       Hist1[9 ]->Fill(chisqrKurama[i]);
       Hist1[10]->Fill(qKurama[i]);
       Hist1[11]->Fill(vpx[1]);
       Hist1[12]->Fill(vpy[1]);
       Hist1[13]->Fill(vpseg[1]);
       Hist1[22]->Fill(TofSeg[i]);
       Hist1[27]->Fill(tofsegKurama[i]);

       Hist2[2 ]->Fill(m2[i],pKurama[i]);
       Hist2[3 ]->Fill(vpx[1],vpy[1]);
       Hist2[7 ]->Fill(vpseg[1],TofSeg[i]);
       Hist2[11]->Fill(vpseg[1],tofsegKurama[i]);

       if(m2[i]<0.15)continue;
       if(m2[i]>0.35)continue;  //Cut2
       Hist1[14]->Fill(pKurama[i]);
       Hist1[15]->Fill(m2[i]);
       Hist1[16]->Fill(chisqrKurama[i]);
       Hist1[17]->Fill(qKurama[i]);
       Hist1[18]->Fill(vpx[1]);
       Hist1[19]->Fill(vpy[1]);
       Hist1[20]->Fill(vpseg[1]);
       Hist1[23]->Fill(TofSeg[i]);
       Hist1[28]->Fill(tofsegKurama[i]);

       Hist2[4 ]->Fill(m2[i],pKurama[i]);
       Hist2[5 ]->Fill(vpx[1],vpy[1]);
       Hist2[8 ]->Fill(vpseg[1],TofSeg[i]);
       Hist2[12]->Fill(vpseg[1],tofsegKurama[i]);

     } // Cut1
   } 

// Peak & Gate Make -----
//   TF1 *FitFunc1 = new TF1("FitFunc1","gaus");
//   FitFunc1->SetParameters(1000,-400,5);
//   double MaximumBintSac=0.;
//   double tSacGateMin   =0.;
//   double tSacGateMax   =0.;
//   MaximumBintSac=Hist1[13]->GetXaxis()->GetBinCenter(Hist1[13]->GetMaximumBin());
//   Hist1[13]->Fit("FitFunc1","","",MaximumBintSac-4,MaximumBintSac+4);
//   Hist1[13]->SetAxisRange(MaximumBintSac-50,MaximumBintSac+80,"X");
//   tSacGateMin=FitFunc1->GetParameter(1) - 20 ;//FitFunc1->GetParameter(2);
//   tSacGateMax=FitFunc1->GetParameter(1) + 20 ;//FitFunc1->GetParameter(2);
//   std::cout << "SAC Time Gate Min \t" << tSacGateMin << std::endl;
//   std::cout << "SAC Time Gate Max \t" << tSacGateMax << std::endl;


//-Canvas def---------------------------------------------------------------------------------------

  TCanvas *c1 = new TCanvas("c1","c1",1200,900);
   c1->Print(pdf+"["); 
//-Hist Draw----------------------------------------------------------------------------------------
   c1->cd();
   for(int i=0; i<Hist1Max; i++){
//   if(i==15 || i==16 || i==38) gPad->SetLogy(1);
   Hist1[i]->Draw();
   c1->Print(pdf);
   c1->Print(Form("%s/Mtx_Pos_run%05d_Hist1_%03d.pdf",pdfDhire.Data(),runnum,i));
//   if(i==15 || i==16 || i==38) gPad->SetLogy(0);
   }
   for(int i=0; i<Hist2Max; i++){
   Hist2[i]->Draw("colz");
   c1->Print(pdf);
   c1->Print(Form("%s/Mtx_Pos_run%05d_Hist2_%03d.pdf",pdfDhire.Data(),runnum,i));
   }

   c1->Print(pdf+"]"); 


}
