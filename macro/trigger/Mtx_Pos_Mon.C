#include "DetectorID.hh"

 const char* MPG[] =
 {
   "SFT_Newtable.txt.2019Jan.1_1",
   "SFT_Newtable.txt.2019Jan.1_2",
   "SFT_table.txt.2018Jun.3_1"
 };

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

bool eq3(int a,int b,int c){
  if( a!= b ) return false;
  if( b!= c ) return false;
  if( c!= a ) return false;

  return true;
}


void Mtx_Pos_Mon(int month,int runnum, int matrix = 2){

  gStyle->SetOptTitle(0);
  gStyle->SetOptStat(0);
  gStyle->SetLabelSize(0.04,"XYZ");
  gStyle->SetTitleSize(0.05,"XYZ");
  gStyle->SetTitleOffset(1.2,"X");
  gStyle->SetTitleOffset(1.3,"Y");
  gStyle->SetPadLeftMargin(0.16);
  gStyle->SetPadBottomMargin(0.16);


//Reset ROOT and connect tree file
   gROOT->Reset();
   gROOT->Reset();
   TString anadir=Form("%s/work/e40/ana",std::getenv("HOME")); 
   TString pdf = Form("%s/pdf/trigger/Mtx_Pos_Mon%d_run%05d.pdf", anadir.Data(),matrix,runnum);
   TString pdfDhire = Form("%s/pdf/trigger", anadir.Data());
//   TFile *f = new TFile(Form("%s/analyzer_%s/rootfile/trigf19_tofht.root", anadir.Data(),Month[month]),"READ");
//   TFile *f = new TFile(Form("%s/analyzer_%s/rootfile/run%05d_DstKuramaEasirocHodoscope_BH2TOF.root", anadir.Data(),Month[month],runnum),"READ");

//Matrix Patern txt file PATH -----------------------------------------------------------------------
//  TString anadir=Form("%s/work/e40/ana",std::getenv("HOME")); 
//  TString filein1=Form("%s/analyzer_%s/param/MATRIXSFT/SFT_table.txt.2018Jun.3_1",anadir.Data(),Month[month] ); 
  TString filein1=Form("%s/analyzer_%s/param/MATRIXSFT/%s",anadir.Data(),Month[month],MPG[matrix] ); 

  std::ifstream fin1(filein1);

  // Param Vector Dif ----------------------------------------------------------------------
  std::vector<std::vector<int>> Mtx_prm; 
  std::string line;
  int preSCH=0;
  std::vector<std::vector<int>> sch_tof; 
  std::vector<int> SCH_Seg; 
  std::vector<int> TOF_Min; 
  std::vector<int> TOF_Max; 


  // Error Out ----------------------------------------------------------------------------------------
  if(fin1.fail() ){
    std::cerr << "file1" << std::endl;
    exit(0); 
  }  

  while(std::getline(fin1, line)){
    double sch=-1, tof=-1, sft_min=-1, sft_max=-1;
    std::istringstream input_line( line );
    std::vector<int> inner;
    if( input_line >> sch >> tof >> sft_min >> sft_max ){
      inner.push_back(sch);
      inner.push_back(tof);
      if((int)sft_min%32==0){
        inner.push_back(sft_min-10);
      }else{
        inner.push_back(sft_min-11);
      }
      inner.push_back(sft_max-1);
      Mtx_prm.push_back(inner);
    }
  }

  for(int i=0; i<Mtx_prm.size(); i++){
    //        std::cout << "SCH=" << Mtx_prm.at(i).at(0)  << "\t" << "TOF="  <<  Mtx_prm.at(i).at(1)  << "\t"  << "SFT_Min=" << Mtx_prm.at(i).at(2)  << "\t"  << "SFT_Max=" << Mtx_prm.at(i).at(3)  << std::endl;
    if(i==0){
      SCH_Seg.push_back( Mtx_prm.at(i).at(0) );
      TOF_Min.push_back( Mtx_prm.at(i).at(1) );
    }else{
      if(i==Mtx_prm.size()-1){
        TOF_Max.push_back( Mtx_prm.at(i).at(1) );
      }else if(Mtx_prm.at(i).at(0)!=Mtx_prm.at(i-1).at(0)){
        SCH_Seg.push_back( Mtx_prm.at(i).at(0) );
        TOF_Max.push_back( Mtx_prm.at(i-1).at(1) );
        TOF_Min.push_back( Mtx_prm.at(i).at(1) );
      }
    }
  }

  //  std::cout << "SCH_Seg size is" << SCH_Seg.size() << "\n"  
  //    << "TOF_Min size is" << TOF_Min.size() << "\n"
  //    << "TOF_Max size is" << TOF_Max.size() << std::endl;

  if( !eq3(SCH_Seg.size(),TOF_Min.size(),TOF_Max.size()) ){
    std::cerr << "Size Not Same" << std::endl;
  }

 // RootFile Open
   TFile *f = new TFile(Form("%s/analyzer_%s/rootfile/run%05d_DstKuramaEasirocHodoscope.root", anadir.Data(),Month[month],runnum),"READ");
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
   Double_t           vpseg[5];
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
   Double_t        sftxsegKurama;;


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
   k0hodo->SetBranchStatus("sftxsegKurama");
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
   k0hodo->SetBranchAddress("sftxsegKurama",&sftxsegKurama);
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

//std::cout << Mtx_prm.size() <<std::endl;

//
//-para def-----------------------------------------------------------------------------------------
   double HULMHTDCCalib = -0.8333;

   int Hist1Max = 0;
   int Hist2Max = 0;

   int chisqr = 0;

//-hist def-----------------------------------------------------------------------------------------
//   Hist1Max = 1252;
   Hist1Max = 48 + Mtx_prm.size()*4;
//   Hist2Max =  405;
   Hist2Max =  104 + Mtx_prm.size();
   chisqr = 50;
   TH1D *Hist1[Hist1Max];
   TH2D *Hist2[Hist2Max];

    Hist1[0 ]= new TH1D("vpx[1]","vpx[1]",200,-400,400);
    Hist1[1 ]= new TH1D("Sch Position by HitSegment","Sch Position by HitSegment",200,-400,400);
    Hist1[2 ]= new TH1D("delta_x","delta_x",200,-100,100);
    Hist1[3 ]= new TH1D("vpx[1] Cut1","vpx[1] Cut1",200,-400,400);
    Hist1[4 ]= new TH1D("Sch Position by HitSegment Cut1","Sch Position by HitSegment Cut1",200,-400,400);
    Hist1[5 ]= new TH1D("pKurama","pKurama",100,0,2);
    Hist1[6 ]= new TH1D("m2","m2",100,-0.4,1.4);
    Hist1[7 ]= new TH1D("chisqrKurama","chisqrKurama",100,0,200);
    Hist1[8 ]= new TH1D("qKurama","qKurama",6,-3,3);
    Hist1[9 ]= new TH1D("vpx[1] 2","vpx[1] 2",200,-400,400);
    Hist1[10]= new TH1D("vpy[1]","vpy[1]",200,-400,400);
    Hist1[11]= new TH1D("vpseg[1]","vpseg[1]",NumOfSegSCH,0,NumOfSegSCH);
    Hist1[12]= new TH1D("TofSeg[0]","TofSeg[0]",NumOfSegTOF,0,NumOfSegTOF);
    Hist1[13]= new TH1D("tofsegKurama[0]","tofsegKurama[0]",NumOfSegTOF,0,NumOfSegTOF);
    Hist1[14]= new TH1D("pKurama Cut1","pKurama Cut1",100,0,2);
    Hist1[15]= new TH1D("m2 Cut1","m2 Cut1",100,-0.4,1.4);
    Hist1[16]= new TH1D("chisqrKurama Cut1","chisqrKurama Cut1",100,0,200);
    Hist1[17]= new TH1D("qKurama Cut1","qKurama Cut1",6,-3,3);
    Hist1[18]= new TH1D("vpx[1] Cut1 2","vpx[1] Cut1 2",200,-400,400);
    Hist1[19]= new TH1D("vpseg[1] Cut1","vpseg[1] Cut1",NumOfSegSCH,0,NumOfSegSCH);
    Hist1[20]= new TH1D("TofSeg[0] Cut1","TofSeg[0] Cut1",NumOfSegTOF,0,NumOfSegTOF);
    Hist1[21]= new TH1D("tofsegKurama[0] Cut1","tofsegKurama[0] Cut1",NumOfSegTOF,0,NumOfSegTOF);
    Hist1[22]= new TH1D("pKurama Cut2","pKurama Cut2",100,0,2);
    Hist1[23]= new TH1D("m2 Cut2","m2 Cut2",100,-0.4,1.4);
    Hist1[24]= new TH1D("chisqrKurama Cut2","chisqrKurama Cut2",100,0,200);
    Hist1[25]= new TH1D("qKurama Cut2","qKurama Cut2",6,-3,3);
    Hist1[26]= new TH1D("vpx[1] Cut2","vpx[1] Cut2",200,-400,400);
    Hist1[27]= new TH1D("vpseg[1] Cut2","vpseg[1] Cut2",NumOfSegSCH,0,NumOfSegSCH);
    Hist1[28]= new TH1D("TofSeg[0] Cut2","TofSeg[0] Cut2",NumOfSegTOF,0,NumOfSegTOF);
    Hist1[29]= new TH1D("tofsegKurama[0] Cut2","tofsegKurama[0] Cut2",NumOfSegTOF,0,NumOfSegTOF);
    Hist1[30]= new TH1D("pKurama Cut3","pKurama Cut3;Momentum[GeV/c];Counts",100,0,2);
    Hist1[31]= new TH1D("m2 Cut3","m2 Cut3",100,-0.4,1.4);
    Hist1[32]= new TH1D("chisqrKurama Cut3","chisqrKurama Cut3",100,0,200);
    Hist1[33]= new TH1D("qKurama Cut3","qKurama Cut3",6,-3,3);
    Hist1[34]= new TH1D("vpx[1] Cut3","vpx[1] Cut3",200,-400,400);
    Hist1[35]= new TH1D("vpseg[1] Cut3","vpseg[1] Cut3",NumOfSegSCH,0,NumOfSegSCH);
    Hist1[36]= new TH1D("TofSeg[0] Cut3","TofSeg[0] Cut3",NumOfSegTOF,0,NumOfSegTOF);
    Hist1[37]= new TH1D("tofsegKurama[0] Cut3","tofsegKurama[0] Cut3",NumOfSegTOF,0,NumOfSegTOF);
    Hist1[38]= new TH1D("pKurama Cut4","pKurama Cut4",100,0,2);
    Hist1[39]= new TH1D("m2 Cut4","m2 Cut4",100,-0.4,1.4);
    Hist1[40]= new TH1D("chisqrKurama Cut4","chisqrKurama Cut4",100,0,200);
    Hist1[41]= new TH1D("qKurama Cut4","qKurama Cut4",6,-3,3);
    Hist1[42]= new TH1D("vpx[1] Cut4","vpx[1] Cut4",200,-400,400);
    Hist1[43]= new TH1D("vpseg[1] Cut4","vpseg[1] Cut4",NumOfSegSCH,0,NumOfSegSCH);
    Hist1[44]= new TH1D("TofSeg[0] Cut4","TofSeg[0] Cut4",NumOfSegTOF,0,NumOfSegTOF);
    Hist1[45]= new TH1D("tofsegKurama[0] Cut4","tofsegKurama[0] Cut4",NumOfSegTOF,0,NumOfSegTOF);
    Hist1[46]= new TH1D("m2 Cut5","m2 Cut5",100,-0.4,1.4);
    Hist1[47]= new TH1D("pKurama Cut5","pKurama Cut5;Momentum[GeV/c];Counts",100,0,2);
    for(int l=0; l < Mtx_prm.size(); l++){
      Hist1[48+Mtx_prm.size()*0+l]= new TH1D(Form("sftxsegKurama[0] Cut3 SchSeg%d - TofSeg%d",Mtx_prm.at(l).at(0)+1,Mtx_prm.at(l).at(1)+1),Form("sftxsegKurama[0] Cut3 SchSeg%d - TofSeg%d",Mtx_prm.at(l).at(0)+1,Mtx_prm.at(l).at(1)+1),NumOfSegSFT_X,0,NumOfSegSFT_X);
      Hist1[48+Mtx_prm.size()*1+l]= new TH1D(Form("sftxsegKurama[0] Cut5 SchSeg%d - TofSeg%d",Mtx_prm.at(l).at(0)+1,Mtx_prm.at(l).at(1)+1),Form("sftxsegKurama[0] Cut5 SchSeg%d - TofSeg%d",Mtx_prm.at(l).at(0)+1,Mtx_prm.at(l).at(1)+1),NumOfSegSFT_X,0,NumOfSegSFT_X);
      Hist1[48+Mtx_prm.size()*2+l]= new TH1D(Form("pKurama Cut5 SchSeg%d - TofSeg%d",Mtx_prm.at(l).at(0)+1,Mtx_prm.at(l).at(1)+1),Form("pKurama Cut5 SchSeg%d - TofSeg%d",Mtx_prm.at(l).at(0)+1,Mtx_prm.at(l).at(1)+1),100,0,2);
      Hist1[48+Mtx_prm.size()*3+l]= new TH1D(Form("m2      Cut5 SchSeg%d - TofSeg%d",Mtx_prm.at(l).at(0)+1,Mtx_prm.at(l).at(1)+1),Form("m2      Cut5 SchSeg%d - TofSeg%d",Mtx_prm.at(l).at(0)+1,Mtx_prm.at(l).at(1)+1),100,-0.4,1.4);
    }

    Hist2[0 ]= new TH2D("Sch Position by HitSegment % vpx[1]","Sch Position by HitSegment % vpx[1]",200,-400,400,100,-400,400);
    Hist2[1 ]= new TH2D("Sch Position by HitSegment % vpx[1] Cut1","Sch Position by HitSegment % vpx[1] Cut1",200,-400,400,100,-400,400);
    Hist2[2 ]= new TH2D("pKurama % m2",     "pKurama % m2 "    ,100,-0.4,1.4,100,0,2);
    Hist2[3 ]= new TH2D("vpy[1] % vpx[1]     ","vpy[1] % vpx[1]     ",100,-400,400,100,-400,400);
    Hist2[4 ]= new TH2D("TofSeg[0] % vpseg[1]","TofSeg[0] % vpseg[1]",NumOfSegSCH,0,NumOfSegSCH,NumOfSegTOF,0,NumOfSegTOF);
    Hist2[5 ]= new TH2D("tofsegKurama[0] % vpseg[1]","tofsegKurama[0] % vpseg[1]" ,NumOfSegSCH,0,NumOfSegSCH,NumOfSegTOF,0,NumOfSegTOF);
    Hist2[6 ]= new TH2D("pKurama % m2 Cut1",     "pKurama % m2  Cut1"    ,100,-0.4,1.4,100,0,2);
    Hist2[7 ]= new TH2D("vpy[1] % vpx[1]      Cut1","vpy[1] % vpx[1]      Cut1",100,-400,400,100,-400,400);
    Hist2[8 ]= new TH2D("TofSeg[0] % vpseg[1] Cut1","TofSeg[0] % vpseg[1] Cut1",NumOfSegSCH,0,NumOfSegSCH,NumOfSegTOF,0,NumOfSegTOF);
    Hist2[9 ]= new TH2D("tofsegKurama[0] % vpseg[1] Cut1","tofsegKurama[0] % vpseg[1] Cut1",NumOfSegSCH,0,NumOfSegSCH,NumOfSegTOF,0,NumOfSegTOF);
    Hist2[10]= new TH2D("pKurama % m2 Cut2",     "pKurama % m2  Cut2"    ,100,-0.4,1.4,100,0,2);
    Hist2[11]= new TH2D("vpy[1] % vpx[1]      Cut2","vpy[1] % vpx[1]      Cut2",100,-400,400,100,-400,400);
    Hist2[12]= new TH2D("TofSeg[0] % vpseg[1] Cut2","TofSeg[0] % vpseg[1] Cut2",NumOfSegSCH,0,NumOfSegSCH,NumOfSegTOF,0,NumOfSegTOF);
    Hist2[13]= new TH2D("tofsegKurama[0] % vpseg[1] Cut2","tofsegKurama[0] % vpseg[1] Cut2",NumOfSegSCH,0,NumOfSegSCH,NumOfSegTOF,0,NumOfSegTOF);
    Hist2[14]= new TH2D("pKurama % m2 Cut3",     "pKurama % m2  Cut3"    ,100,-0.4,1.4,100,0,2);
    Hist2[15]= new TH2D("vpy[1] % vpx[1]      Cut3","vpy[1] % vpx[1]      Cut3",100,-400,400,100,-400,400);
    Hist2[16]= new TH2D("TofSeg[0] % vpseg[1] Cut3","TofSeg[0] % vpseg[1] Cut3",NumOfSegSCH,0,NumOfSegSCH,NumOfSegTOF,0,NumOfSegTOF);
    Hist2[17]= new TH2D("tofsegKurama[0] % vpseg[1] Cut3","tofsegKurama[0] % vpseg[1] Cut3",NumOfSegSCH,0,NumOfSegSCH,NumOfSegTOF,0,NumOfSegTOF);
    Hist2[18]= new TH2D("pKurama % m2 Cut4",     "pKurama % m2  Cut4"    ,100,-0.4,1.4,100,0,2);
    Hist2[19]= new TH2D("vpy[1] % vpx[1]      Cut4","vpy[1] % vpx[1]      Cut4",100,-400,400,100,-400,400);
    Hist2[20]= new TH2D("TofSeg[0] % vpseg[1] Cut4","TofSeg[0] % vpseg[1] Cut4",NumOfSegSCH,0,NumOfSegSCH,NumOfSegTOF,0,NumOfSegTOF);
    Hist2[21]= new TH2D("tofsegKurama[0] % vpseg[1] Cut4","tofsegKurama[0] % vpseg[1] Cut4",NumOfSegSCH,0,NumOfSegSCH,NumOfSegTOF,0,NumOfSegTOF);
    for(int p=0; p<10; p++ ){
      int i=0;
        Hist2[22+p*4]= new TH2D(Form("pKurama vs m2 Cut3 %lg<pKurama[%d]<%lg",p*0.2,i,(p+1)*0.2),Form("pKurama  vs  m2 Cut3 %lg<pKurama[%d]<%lg",p*0.2,i,(p+1)*0.2),100,-0.4,1.4,100,0,2);             
        Hist2[23+p*4]= new TH2D(Form("vpy[1]  vs  vpx[1]      Cut3 %lg<pKurama[%d]<%lg",p*0.2,i,(p+1)*0.2),Form("vpy[1]  vs  vpx[1]      Cut3 %lg<pKurama[%d]<%lg",p*0.2,i,(p+1)*0.2),100,-400,400,100,-400,400);  
        Hist2[24+p*4]= new TH2D(Form("TofSeg[0]  vs  vpseg[1] Cut3 %lg<pKurama[%d]<%lg",p*0.2,i,(p+1)*0.2),Form("TofSeg[0]  vs  vpseg[1] Cut3 %lg<pKurama[%d]<%lg",p*0.2,i,(p+1)*0.2),NumOfSegSCH,0,NumOfSegSCH,NumOfSegTOF,0,NumOfSegTOF);            
        Hist2[25+p*4]= new TH2D(Form("tofsegKurama[0]  vs  vpseg[1] Cut3 %lg<pKurama[%d]<%lg",p*0.2,i,(p+1)*0.2),Form("tofsegKurama[0]  vs  vpseg[1] Cut3 %lg<pKurama[%d]<%lg",p*0.2,i,(p+1)*0.2),NumOfSegSCH,0,NumOfSegSCH,NumOfSegTOF,0,NumOfSegTOF);
        Hist2[62+p*4]= new TH2D(Form("pKurama  vs  m2 Cut4 %lg<pKurama[%d]<%lg",p*0.2,i,(p+1)*0.2),Form("pKurama  vs  m2 Cut4 %lg<pKurama[%d]<%lg",p*0.2,i,(p+1)*0.2),100,-0.4,1.4,100,0,2);             
        Hist2[63+p*4]= new TH2D(Form("vpy[1]  vs  vpx[1]      Cut4 %lg<pKurama[%d]<%lg",p*0.2,i,(p+1)*0.2),Form("vpy[1]  vs  vpx[1]      Cut4 %lg<pKurama[%d]<%lg",p*0.2,i,(p+1)*0.2),100,-400,400,100,-400,400);  
        Hist2[64+p*4]= new TH2D(Form("TofSeg[0]  vs  vpseg[1] Cut4 %lg<pKurama[%d]<%lg",p*0.2,i,(p+1)*0.2),Form("TofSeg[0]  vs  vpseg[1] Cut4 %lg<pKurama[%d]<%lg",p*0.2,i,(p+1)*0.2),NumOfSegSCH,0,NumOfSegSCH,NumOfSegTOF,0,NumOfSegTOF);            
        Hist2[65+p*4]= new TH2D(Form("tofsegKurama[0]  vs  vpseg[1] Cut4 %lg<pKurama[%d]<%lg",p*0.2,i,(p+1)*0.2),Form("tofsegKurama[0]  vs  vpseg[1] Cut4 %lg<pKurama[%d]<%lg",p*0.2,i,(p+1)*0.2),NumOfSegSCH,0,NumOfSegSCH,NumOfSegTOF,0,NumOfSegTOF);
//        Hist2[22+p*4]= new TH2D(Form("pKurama vs m2 Cut3 %lg<pKurama[%d]<%lg",(double)p*0.2,i,((double)p+1.)*0.2),Form("pKurama  vs  m2 Cut3 %lg<pKurama[%d]<%lg",(double)p*0.2,i,((double)p+1.)*0.2),100,-0.4,1.4,100,0,2);             
//        Hist2[23+p*4]= new TH2D(Form("vpy[1]  vs  vpx[1]      Cut3 %lg<pKurama[%d]<%lg",(double)p*0.2,i,((double)p.+1)*0.2),Form("vpy[1]  vs  vpx[1]      Cut3 %lg<pKurama[%d]<%lg",(double)p*0.2,i,((double)p+1.)*0.2),100,-400,400,100,-400,400);  
//        Hist2[24+p*4]= new TH2D(Form("TofSeg[0]  vs  vpseg[1] Cut3 %lg<pKurama[%d]<%lg",(double)p*0.2,i,((double)p+1.)*0.2),Form("TofSeg[0]  vs  vpseg[1] Cut3 %lg<pKurama[%d]<%lg",(double)p*0.2,i,((double)p+1.)*0.2),64,1,65,24,1,25);            
//        Hist2[25+p*4]= new TH2D(Form("tofsegKurama[0]  vs  vpseg[1] Cut3 %lg<pKurama[%d]<%lg",(double)p*0.2,i,((double)p+1.)*0.2),Form("tofsegKurama[0]  vs  vpseg[1] Cut3 %lg<pKurama[%d]<%lg",(double)p*0.2,i,((double)p+1.)*0.2),64,1,65,24,1,25);
    }

//   Hist2Max =  102;
    Hist2[102]= new TH2D("tofsegKurama[0] % vpseg[1] Cut5","tofsegKurama[0] % vpseg[1] Cut5",NumOfSegSCH,0,NumOfSegSCH,NumOfSegTOF,0,NumOfSegTOF);
    Hist2[103]= new TH2D("pKurama % m2 Cut5",     "pKurama % m2  Cut5"    ,100,-0.4,1.4,100,0,2);
    for(int l=0; l < Mtx_prm.size(); l++){
      Hist2[104+Mtx_prm.size()*0+l]= new TH2D(Form("pKurama %% m2 Cut5 SchSeg%d - TofSeg%d",Mtx_prm.at(l).at(0)+1,Mtx_prm.at(l).at(1)+1), Form("pKurama %% m2 Cut5 SchSeg%d - TofSeg%d",Mtx_prm.at(l).at(0)+1,Mtx_prm.at(l).at(1)+1)   ,100,-0.4,1.4,100,0,2);
    }                                         


//-Legend def --------------------------------------------------------------------------------------
  TLegend *Leg1 = new TLegend(0.78,0.575,0.98,0.935);
  TLegend *Leg2 = new TLegend(0.78,0.575,0.98,0.935);
  TLegend *Leg3 = new TLegend(0.78,0.575,0.98,0.935);

//-Event Loop --------------------------------------------------------------------------------------
//   Long64_t nentries = k0hodo->GetEntries();
   Long64_t nentries = 10000;

//-Event Loop First --------
   Long64_t nbytes = 0;
   for (Long64_t s=0; s<nentries;s++) {
     nbytes += k0hodo->GetEntry(s);
     //     for(int i=0; i<ntKurama; i++){
     
    if(s%(nentries/10) ==0){
      std::cout << ( ((double)s)/nentries *100 ) << "%\t" << s << "/" << nentries << "\r"  << std::endl;
    }

     if( ntKurama!=1) continue;
     bool sch_flag = false;

     for(int i=0; i<nhSch; i++){
       Hist1[0]->Fill(vpx[1]);
       Hist1[1]->Fill(SchPos[i]);
       Hist1[2]->Fill(delta_x[i]);
       Hist2[0 ]->Fill(SchPos[i],vpx[1]);
       if(delta_x[i]<-10 || delta_x[i]>10) continue;
//       if(delta_x[i]<10 || delta_x[i]>25) continue;
       sch_flag = true;
       Hist1[3]->Fill(vpx[1]);
       Hist1[4]->Fill(SchPos[i]);
       Hist2[1]->Fill(SchPos[i],vpx[1]);
     }

     int i=0;
     Hist1[5 ]->Fill(pKurama[i]);
     Hist1[6 ]->Fill(m2[i]);
     Hist1[7 ]->Fill(chisqrKurama[i]);
     Hist1[8 ]->Fill(qKurama[i]);
     Hist1[9 ]->Fill(vpx[1]);
     Hist1[10]->Fill(vpy[1]);
     Hist1[11]->Fill(vpseg[1]);
     Hist1[12]->Fill(TofSeg[i]);
     Hist1[13]->Fill(tofsegKurama[i]-1);

     Hist2[2 ]->Fill(m2[i],pKurama[i]);
     Hist2[3 ]->Fill(vpx[1],vpy[1]);
     Hist2[4 ]->Fill(vpseg[1],TofSeg[i]);
     Hist2[5 ]->Fill(vpseg[1],tofsegKurama[i]-1);

     if(sch_flag){ //Cut1
       Hist1[14]->Fill(pKurama[i]);
       Hist1[15]->Fill(m2[i]);
       Hist1[16]->Fill(chisqrKurama[i]);
       Hist1[17]->Fill(qKurama[i]);
       Hist1[18]->Fill(vpx[1]);
       Hist1[19]->Fill(vpseg[1]);
       Hist1[20]->Fill(TofSeg[i]);
       Hist1[21]->Fill(tofsegKurama[i]-1);

       Hist2[6 ]->Fill(m2[i],pKurama[i]);
       Hist2[7 ]->Fill(vpx[1],vpy[1]);
       Hist2[8 ]->Fill(vpseg[1],TofSeg[i]);
       Hist2[9 ]->Fill(vpseg[1],tofsegKurama[i]-1);
       if(chisqrKurama[i]<chisqr){ // Cut2
         Hist1[22]->Fill(pKurama[i]);
         Hist1[23]->Fill(m2[i]);
         Hist1[24]->Fill(chisqrKurama[i]);
         Hist1[25]->Fill(qKurama[i]);
         Hist1[26]->Fill(vpx[1]);
         Hist1[27]->Fill(vpseg[1]);
         Hist1[28]->Fill(TofSeg[i]);
         Hist1[29]->Fill(tofsegKurama[i]-1);

         Hist2[10]->Fill(m2[i],pKurama[i]);
         Hist2[11]->Fill(vpx[1],vpy[1]);
         Hist2[12]->Fill(vpseg[1],TofSeg[i]);
         Hist2[13]->Fill(vpseg[1],tofsegKurama[i]-1);
         if(qKurama[i]>0){ // Cut3
           Hist1[30]->Fill(pKurama[i]);
           Hist1[31]->Fill(m2[i]);
           Hist1[32]->Fill(chisqrKurama[i]);
           Hist1[33]->Fill(qKurama[i]);
           Hist1[34]->Fill(vpx[1]);
           Hist1[35]->Fill(vpseg[1]);
           Hist1[36]->Fill(TofSeg[i]);
           Hist1[37]->Fill(tofsegKurama[i]-1);

           Hist2[14]->Fill(m2[i],pKurama[i]);
           Hist2[15]->Fill(vpx[1],vpy[1]);
           Hist2[16]->Fill(vpseg[1],TofSeg[i]);
           Hist2[17]->Fill(vpseg[1],tofsegKurama[i]-1);
           for(int p=0; p<10; p++ ){
             if(p*0.2<pKurama[i]&&(p+1)*0.2>pKurama[i]){
               Hist2[22+p*4]->Fill(m2[i],pKurama[i]);
               Hist2[23+p*4]->Fill(vpx[1],vpy[1]);
               Hist2[24+p*4]->Fill(vpseg[1],TofSeg[i]);
               Hist2[25+p*4]->Fill(vpseg[1],tofsegKurama[i]-1);
             }
           }
           for(int l=0; l < Mtx_prm.size(); l++){
             double m = 0;
             double n = 0;
             double min = 0;
             double max = 0;
             m = (double)Mtx_prm.at(l).at(1);
             n = (double)Mtx_prm.at(l).at(0);
             min = (double)Mtx_prm.at(l).at(2);
             max = (double)Mtx_prm.at(l).at(3) + 1;
             if(vpseg[1]==n&&tofsegKurama[i]-1==m){
                 Hist1[48+Mtx_prm.size()*0+l]->Fill(sftxsegKurama);
               if(sftxsegKurama>min&&sftxsegKurama<max){
                 Hist1[48+Mtx_prm.size()*1+l]->Fill(sftxsegKurama);
                 Hist1[46]->Fill(m2[i]);
                 Hist1[47]->Fill(pKurama[i]);
                 Hist1[48+Mtx_prm.size()*2+l]->Fill(pKurama[i]);
                 Hist1[48+Mtx_prm.size()*3+l]->Fill(m2[i]);
                 Hist2[102]->Fill(vpseg[1],tofsegKurama[i]-1);
                 Hist2[103]->Fill(m2[i],pKurama[i]);
                 Hist2[104+Mtx_prm.size()*0+l]->Fill(m2[i],pKurama[i]);
               }
             }
           }
         } // Cut3
         if(qKurama[i]<0){ // Cut4
           Hist1[38]->Fill(pKurama[i]);
           Hist1[39]->Fill(m2[i]);
           Hist1[40]->Fill(chisqrKurama[i]);
           Hist1[41]->Fill(qKurama[i]);
           Hist1[42]->Fill(vpx[1]);
           Hist1[43]->Fill(vpseg[1]);
           Hist1[44]->Fill(TofSeg[i]);
           Hist1[45]->Fill(tofsegKurama[i]-1);

           Hist2[18]->Fill(m2[i],pKurama[i]);
           Hist2[19]->Fill(vpx[1],vpy[1]);
           Hist2[20]->Fill(vpseg[1],TofSeg[i]);
           Hist2[21]->Fill(vpseg[1],tofsegKurama[i]-1);
           for(int p=0; p<10; p++ ){
             if(p*0.2<pKurama[i]&&(p+1)*0.2>pKurama[i]){
               Hist2[62+p*4]->Fill(m2[i],pKurama[i]);
               Hist2[63+p*4]->Fill(vpx[1],vpy[1]);
               Hist2[64+p*4]->Fill(vpseg[1],TofSeg[i]);
               Hist2[65+p*4]->Fill(vpseg[1],tofsegKurama[i]-1);
             }
           }
         } // Cut4
       } // Cut2
     } //Cut1
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
   c1->Print(Form("%s/Mtx_Pos_Mon%d_run%05d_Hist1_%04d.pdf",pdfDhire.Data(),matrix,runnum,i));
//   if(i==15 || i==16 || i==38) gPad->SetLogy(0);
   }
   for(int i=0; i<Hist2Max; i++){
     Hist2[i]->Draw("colz");
     c1->Print(pdf);
     c1->Print(Form("%s/Mtx_Pos_Mon%d_run%05d_Hist2_colz_%04d.pdf",pdfDhire.Data(),matrix,runnum,i));
   }
   for(int j=0; j<Hist2Max; j++){
     Hist2[j]->Draw("box");

     for(int i=0; i<SCH_Seg.size(); i++){
       double x1;
       double x2;

       double TOF_Min_y1;
       double TOF_Min_y2;

       double TOF_Max_y1;
       double TOF_Max_y2;

       x1 =  (double)SCH_Seg.at(i);
       x2 =  (double)(SCH_Seg.at(i)+1);

       TOF_Min_y1 =(double)TOF_Min.at(i);
       TOF_Min_y2 =(double)TOF_Min.at(i);

       TOF_Max_y1 =  (double)TOF_Max.at(i)+1;
       TOF_Max_y2 =  (double)TOF_Max.at(i)+1;

       TLine *MtxGateMin = new TLine(x1,TOF_Min_y1,x2,TOF_Min_y2);
       TLine *MtxGateMax = new TLine(x1,TOF_Max_y1,x2,TOF_Max_y2);

       MtxGateMin->SetLineColor(2);
       MtxGateMax->SetLineColor(2);
       MtxGateMin->SetLineWidth(1);
       MtxGateMax->SetLineWidth(1);
       MtxGateMin->Draw("same");
       MtxGateMax->Draw("same");
       if(i==0){
         TLine *MtxGateMin_Y = new TLine(x1,TOF_Min_y1,x1,TOF_Max_y1);
         MtxGateMin_Y->SetLineColor(2);
         MtxGateMin_Y->SetLineWidth(1);
         MtxGateMin_Y->Draw("same");
       }else if(i==SCH_Seg.size()-1){
         TLine *MtxGateMin_Y = new TLine(x2,TOF_Min_y1,x2,TOF_Max_y1);
         MtxGateMin_Y->SetLineColor(2);
         MtxGateMin_Y->SetLineWidth(1);
         MtxGateMin_Y->Draw("same");
       }else{
         if(TOF_Min.at(i)-TOF_Min.at(i-1)!=0){
           TLine *MtxGate_Y1 = new TLine(x1,(double)TOF_Min.at(i-1),x1,TOF_Min_y1);
           MtxGate_Y1->SetLineColor(2);
           MtxGate_Y1->SetLineWidth(1);
           MtxGate_Y1->Draw("same");
         }
         if(TOF_Max.at(i)-TOF_Max.at(i-1)!=0){
           TLine *MtxGate_Y2 = new TLine(x1,(double)TOF_Max.at(i-1)+1,x1,TOF_Max_y1);
           MtxGate_Y2->SetLineColor(2);
           MtxGate_Y2->SetLineWidth(1);
           MtxGate_Y2->Draw("same");
         }
       }
     }
     c1->Print(pdf);
     c1->Print(Form("%s/Mtx_Pos_Mon%d_run%05d_Hist2_box_%04d.pdf",pdfDhire.Data(),matrix,runnum,j));
   }
   
   Hist1[30]->Draw();
   Hist1[47]->SetLineColor(kRed); 
   Hist1[47]->Draw("same");
   c1->Print(pdf);
   c1->Print(Form("%s/Mtx_Pos_Mon%d_run%05d_Hist1_30_47_same.pdf",pdfDhire.Data(),matrix,runnum));


   TH1D *test = new TH1D("test","Momentum Ratio Cut5/Cut3 w/MtxCut;GeV/c;Ratio",100,0,2);
   test->SetAxisRange(0,1,"Y");
   test->Draw();

   int nBin = 100;
   double x[nBin];
   double ratio[nBin];
   double xerr[nBin];
   double ratioerr[nBin];
   for(int i = 0; i<nBin; i++){
     x[i] = 2./(double)nBin/2. + (double)i*2./nBin;
     double a=0.;
     double b=0.;
     a=  Hist1[47]->GetBinContent(i+1);
     b=  Hist1[30]->GetBinContent(i+1);
//   x[i]=Hist1[47]->GetXaxis()->GetBinCenter(i+i);
     ratio[i] = a/b ;
     xerr[i] = 2./(double)nBin/2.;
     ratioerr[i] = sqrt(b*ratio[i]*(1-ratio[i]))/b;
   }

   TGraphErrors *graph1 = new TGraphErrors(nBin,x,ratio,xerr,ratioerr);
   graph1->SetMarkerStyle(20);
   graph1->SetMarkerColor(2);
//   graph1->GetXaxis()->SetRangeUser(0,2);
//   graph1->GetYaxis()->SetRangeUser(0,1);
//   gPad->GetRangeAxis(0,2,0,1);
   graph1->SetMaximum(1);
   graph1->SetMinimum(0);
   graph1->GetXaxis()->SetLimits(0,2);
   graph1->GetYaxis()->SetDecimals(2);
   graph1->Draw("p");
   c1->Print(pdf);
   c1->Print(Form("%s/Mtx_Pos_Mon%d_run%05d_Hist1_graph.pdf",pdfDhire.Data(),matrix,runnum));

   TH1D *h = (TH1D*)Hist1[47]->Clone("Hist1[47]");
   h->Divide(Hist1[30]);
   h->SetXTitle("GeV/c");
   h->SetYTitle("ratio");
//   h->Sumw2();
   h->Draw("");
   c1->Print(pdf);
   c1->Print(Form("%s/Mtx_Pos_Mon%d_run%05d_Hist1_ratio.pdf",pdfDhire.Data(),matrix,runnum));





//   for(int p=0; p<10; p++ ){
//     if(p==0){
//       Hist2[25+p*4]->SetMarkerColor(p+1);
//       Leg1->AddEntry(Hist2[25+p*4],Form("Cut3 %lg<pKurama[0]<%lg",p*0.2,(p+1)*0.2),"p");
//       Hist2[25+p*4]->Draw();
//     }else{
//       Hist2[25+p*4]->SetMarkerColor(p+1);
//       Leg1->AddEntry(Hist2[25+p*4],Form("Cut3 %lg<pKurama[0]<%lg",p*0.2,(p+1)*0.2),"p");
//       Hist2[25+p*4]->Draw("same");
//     }
//   }
//   Leg1->Draw();
//   c1->Print(pdf);
//   c1->Print(Form("%s/Mtx_Pos_Mon_run%05d_Hist2_same_Cut3.pdf",pdfDhire.Data(),runnum));
//
//   for(int p=0; p<10; p++ ){
//     if(p==0){
//       Hist2[65+p*4]->SetMarkerColor(p+1);
//       Leg1->AddEntry(Hist2[65+p*4],Form("Cut4 %lg<pKurama[0]<%lg",p*0.2,(p+1)*0.2),"p");
//       Leg2->AddEntry(Hist2[65+p*4],Form("Cut4 %lg<pKurama[0]<%lg",p*0.2,(p+1)*0.2),"p");
//       Hist2[65+p*4]->Draw();
//     }else{
//       Hist2[65+p*4]->SetMarkerColor(p+1);
//       Leg1->AddEntry(Hist2[65+p*4],Form("Cut4 %lg<pKurama[0]<%lg",p*0.2,(p+1)*0.2),"p");
//       Leg2->AddEntry(Hist2[65+p*4],Form("Cut4 %lg<pKurama[0]<%lg",p*0.2,(p+1)*0.2),"p");
//       Hist2[65+p*4]->Draw("same");
//     }
//   }
//   Leg2->Draw();
//   c1->Print(pdf);
//   c1->Print(Form("%s/Mtx_Pos_Mon_run%05d_Hist2_same_Cut4.pdf",pdfDhire.Data(),runnum));
//
//   for(int p=0; p<10; p++ ){
//     if(p==0){
//       Hist2[25+p*4]->Draw();
//       Hist2[65+p*4]->Draw("same");
//     }else{
//       Hist2[25+p*4]->Draw("same");
//       Hist2[65+p*4]->Draw("same");
//     }
//   }
//   Leg1->Draw();
//   c1->Print(pdf);
//   c1->Print(Form("%s/Mtx_Pos_Mon_run%05d_Hist2_same_Cut34.pdf",pdfDhire.Data(),runnum));
//
//   for(int p=0; p<10; p++ ){
//     if(p==2){
//       Hist2[25+p*4]->Draw();
//       Hist2[65+p*4]->Draw("same");
//       Leg3->AddEntry(Hist2[25+p*4],Form("Cut3 %lg<pKurama[0]<%lg",p*0.2,(p+1)*0.2),"p");
//       Leg3->AddEntry(Hist2[65+p*4],Form("Cut4 %lg<pKurama[0]<%lg",p*0.2,(p+1)*0.2),"p");
//     }
//     if(p==4){
//       Hist2[25+p*4]->Draw("same");
//       Hist2[65+p*4]->Draw("same");
//       Leg3->AddEntry(Hist2[25+p*4],Form("Cut3 %lg<pKurama[0]<%lg",p*0.2,(p+1)*0.2),"p");
//       Leg3->AddEntry(Hist2[65+p*4],Form("Cut4 %lg<pKurama[0]<%lg",p*0.2,(p+1)*0.2),"p");
//     }
//     if(p==6){
//       Hist2[25+p*4]->Draw("same");
//       Hist2[65+p*4]->Draw("same");
//       Leg3->AddEntry(Hist2[25+p*4],Form("Cut3 %lg<pKurama[0]<%lg",p*0.2,(p+1)*0.2),"p");
//       Leg3->AddEntry(Hist2[65+p*4],Form("Cut4 %lg<pKurama[0]<%lg",p*0.2,(p+1)*0.2),"p");
//     }
//   }
//   Leg3->Draw();
//   c1->Print(pdf);
//   c1->Print(Form("%s/Mtx_Pos_Mon_run%05d_Hist2_same_Cut34_Part.pdf",pdfDhire.Data(),runnum));


   c1->Print(pdf+"]"); 


}
