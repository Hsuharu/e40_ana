#include "DetectorID.hh"

 const char* MPG[] =
 {
  "SFT_Newtable.txt.2019Jan.1_1",
  "SFT_Newtable.txt.2019Jan.1_2",
  "SFT_table.txt.2018Jun.3_1",
  "SFT_Newtable.txt.2019Jan.2_2",
  "SFT_CutFirst_ratio100_Newtable.txt.2019Jan.1_2",
  "SFT_CutFirst_ratio50_Newtable.txt.2019Jan.1_2",
  "SFT_CutFirst_ratio20_Newtable.txt.2019Jan.1_2",
  "SFT_CutFirst_ratio15_Newtable.txt.2019Jan.1_2",
  "SFT_CutFirst_ratio10_Newtable.txt.2019Jan.1_2",
  "SFT_CutFirst_ratio8_Newtable.txt.2019Jan.1_2",
  "SFT_CutFirst_ratio6_Newtable.txt.2019Jan.1_2",
  "SFT_CutFirst_ratio5_Newtable.txt.2019Jan.1_2",
  "SFT_CutFirst_ratio4_Newtable.txt.2019Jan.1_2",
  "SFT_CutFirst_ratio2_Newtable.txt.2019Jan.1_2",
  "SFT_CutFirst_ratio1_Newtable.txt.2019Jan.1_2",
  "SFT_CutSecond_Newtable.txt.2019Jan.1_2"
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



double SigmaCountbyMtx(int month=6,int runnum=0, int bin=256, int matrixnum =1){

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
   TString anadir=Form("%s/work/e40/ana",std::getenv("HOME")); 
   TString pdf = Form("%s/pdf/trigger/Mtx_Pat_Sigma_bin%d_ratio%d_run%05d.pdf", anadir.Data(), bin, matrixnum,runnum);
   TString pdf1 = Form("%s/pdf/trigger/Mtx_Sigma_bin%d_ratio%d_run%05d.pdf", anadir.Data(), bin, matrixnum,runnum);
   TString pdfDhire = Form("%s/pdf/trigger", anadir.Data());

//Matrix Patern txt file PATH -----------------------------------------------------------------------
//  TString anadir=Form("%s/work/e40/ana",std::getenv("HOME")); 
//  TString filein1=Form("%s/analyzer_%s/param/MATRIXSFT/SFT_table.txt.2018Jun.3_1",anadir.Data(),Month[month] ); 
//  TString filein1=Form("%s/analyzer_%s/param/MATRIXSFT/%s",anadir.Data(),Month[month],MPG[matrixnum] ); 

//  TString filein1=Form("%s/analyzer_%s/param/MATRIXSFT/SFT_CutFirst_ratio%d_Newtable.txt.2019Jan.1_2",anadir.Data(),Month[month],matrixnum ); 
  TString filein1=Form("%s/analyzer_%s/param/MATRIXSFT/SFT_CutFirst_r1%d_Newtable.txt.2019Jan.1_2",anadir.Data(),Month[month],matrixnum ); 
//  TString filein1=Form("%s/analyzer_%s/param/MATRIXSFT/SFT_CutSecond_%d_Newtable.txt.2019Jan.1_2",anadir.Data(),Month[month],matrixnum ); 

  std::ifstream fin1(filein1);

  // Param Vector Dif ----------------------------------------------------------------------
  std::vector<std::vector<int>> Mtx_prm; //size() = 301
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
      inner.push_back(sft_min-11);
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
   TFile *f = new TFile(Form("%s/analyzer_%s/rootfile2/run%05d_DstPiKAna.root", anadir.Data(),Month[month],runnum),"READ");
   TTree *pik;
    f->GetObject("pik",pik);

// Declaration of leaves types-----------------------------------------------------------------------
//   Int_t           runnum;
   Int_t           evnum;
   Int_t           spill;
   Int_t           trigpat[32];
   Int_t           trigflag[32];
   Int_t           nhBh1;
   Int_t           csBh1[7];
   Double_t        Bh1Seg[7];
   Double_t        tBh1[7];
   Double_t        dtBh1[7];
   Double_t        deBh1[7];
   Double_t        btof[7];
   Int_t           nhBh2;
   Int_t           csBh2[6];
   Double_t        Bh2Seg[6];
   Double_t        tBh2[6];
   Double_t        t0Bh2[6];
   Double_t        dtBh2[6];
   Double_t        deBh2[6];
   Int_t           nhTof;
   Int_t           csTof[25];
   Double_t        TofSeg[25];
   Double_t        tTof[25];
   Double_t        dtTof[25];
   Double_t        deTof[25];
   Int_t           nhBft;
   Int_t           csBft[43];
   Double_t        tBft[43];
   Double_t        wBft[43];
   Double_t        BftPos[43];
   Int_t           nhSch;
   Int_t           csSch[25];
   Double_t        tSch[25];
   Double_t        wSch[25];
   Double_t        SchPos[25];
   Double_t        SchSeg[25];
   Double_t        delta_x[25];
   Double_t        delta_seg[25];
   Int_t           sftx_unhits;
   Int_t           sftx_uhitpat[179];
   Int_t           nhSftX;
   Double_t        SftXSeg[71];
   Int_t           nlBcOut;
   Int_t           ntBcOut;
   Int_t           nhBcOut[4];
   Double_t        chisqrBcOut[4];
   Double_t        x0BcOut[4];
   Double_t        y0BcOut[4];
   Double_t        u0BcOut[4];
   Double_t        v0BcOut[4];
   Double_t        xtgtBcOut[4];
   Double_t        ytgtBcOut[4];
   Double_t        xbh2BcOut[4];
   Double_t        ybh2BcOut[4];
   Int_t           ntK18;
   Int_t           nhK18[4];
   Double_t        chisqrK18[4];
   Double_t        pK18[4];
   Double_t        xtgtK18[4];
   Double_t        ytgtK18[4];
   Double_t        utgtK18[4];
   Double_t        vtgtK18[4];
   Double_t        thetaK18[4];
   Int_t           nlSdcIn;
   Int_t           ntSdcIn;
   Int_t           nhSdcIn[9];
   Double_t        chisqrSdcIn[9];
   Double_t        x0SdcIn[9];
   Double_t        y0SdcIn[9];
   Double_t        u0SdcIn[9];
   Double_t        v0SdcIn[9];
   Int_t           nlSdcOut;
   Int_t           ntSdcOut;
   Int_t           nhSdcOut[6];
   Double_t        chisqrSdcOut[6];
   Double_t        x0SdcOut[6];
   Double_t        y0SdcOut[6];
   Double_t        u0SdcOut[6];
   Double_t        v0SdcOut[6];
   Int_t           ntKurama;
   Int_t           nhKurama[4];
   Double_t        chisqrKurama[4];
   Double_t        stof[4];
   Double_t        path[4];
   Double_t        pKurama[4];
   Double_t        qKurama[4];
   Double_t        m2[4];
   Double_t        xtgtKurama[4];
   Double_t        ytgtKurama[4];
   Double_t        utgtKurama[4];
   Double_t        vtgtKurama[4];
   Double_t        thetaKurama[4];
   Double_t        xtofKurama[4];
   Double_t        ytofKurama[4];
   Double_t        utofKurama[4];
   Double_t        vtofKurama[4];
   Double_t        tofsegKurama[4];
   Double_t        sftxsegKurama;
   Double_t        vpx[5];
   Double_t        vpy[5];
   Double_t        vpseg[5];
   Int_t           nPi;
   Int_t           nK;
   Int_t           nPiK;
   Double_t        vtx[12];
   Double_t        vty[12];
   Double_t        vtz[12];
   Double_t        closeDist[12];
   Double_t        theta[12];
   Double_t        MissMass[12];
   Double_t        MissMassCorr[12];
   Double_t        MissMassCorrDE[12];
   Double_t        thetaCM[12];
   Double_t        costCM[12];
   Double_t        xpi[12];
   Double_t        ypi[12];
   Double_t        upi[12];
   Double_t        vpi[12];
   Double_t        xk[12];
   Double_t        yk[12];
   Double_t        uk[12];
   Double_t        vk[12];
   Double_t        pOrg[12];
   Double_t        pCalc[12];
   Double_t        pCorr[12];
   Double_t        pCorrDE[12];

// Select Branch ------------------------------------------------------------------------------------
   pik->SetBranchStatus("*", 0);
//   pik->SetBranchStatus("runnum");
//   pik->SetBranchStatus("evnum");
   pik->SetBranchStatus("spill");
//   pik->SetBranchStatus("trigpat");
   pik->SetBranchStatus("trigflag");
//   pik->SetBranchStatus("nhBh1");
//   pik->SetBranchStatus("csBh1");
//   pik->SetBranchStatus("Bh1Seg");
//   pik->SetBranchStatus("tBh1");
//   pik->SetBranchStatus("dtBh1");
//   pik->SetBranchStatus("deBh1";
//   pik->SetBranchStatus("btof");
//   pik->SetBranchStatus("nhBh2");
//   pik->SetBranchStatus("csBh2");
//   pik->SetBranchStatus("Bh2Seg");
//   pik->SetBranchStatus("tBh2");
//   pik->SetBranchStatus("t0Bh2");
//   pik->SetBranchStatus("dtBh2");
//   pik->SetBranchStatus("deBh2");
//   pik->SetBranchStatus("nhTof");
//   pik->SetBranchStatus("csTof");
//   pik->SetBranchStatus("TofSeg");
//   pik->SetBranchStatus("tTof");
//   pik->SetBranchStatus("dtTof");
//   pik->SetBranchStatus("deTof");
//   pik->SetBranchStatus("nhBft");
//   pik->SetBranchStatus("csBft");
//   pik->SetBranchStatus("tBft");
//   pik->SetBranchStatus("wBft");
//   pik->SetBranchStatus("BftPos");
   pik->SetBranchStatus("nhSch");
//   pik->SetBranchStatus("csSch");
//   pik->SetBranchStatus("tSch");
//   pik->SetBranchStatus("wSch");
//   pik->SetBranchStatus("SchPos");
//   pik->SetBranchStatus("SchSeg");
//   pik->SetBranchStatus("delta_x");
   pik->SetBranchStatus("delta_seg");
//   pik->SetBranchStatus("sftx_unhits");
//   pik->SetBranchStatus("sftx_uhitpat");
//   pik->SetBranchStatus("nhSftX");
//   pik->SetBranchStatus("SftXSeg");
//   pik->SetBranchStatus("nlBcOut");
//   pik->SetBranchStatus("ntBcOut");
//   pik->SetBranchStatus("nhBcOut");
//   pik->SetBranchStatus("chisqrBcOut");
//   pik->SetBranchStatus("x0BcOut");
//   pik->SetBranchStatus("y0BcOut");
//   pik->SetBranchStatus("u0BcOut");
//   pik->SetBranchStatus("v0BcOut");
//   pik->SetBranchStatus("xtgtBcOut");
//   pik->SetBranchStatus("ytgtBcOut");
//   pik->SetBranchStatus("xbh2BcOut");
//   pik->SetBranchStatus("ybh2BcOut");
//   pik->SetBranchStatus("ntK18");
//   pik->SetBranchStatus("nhK18");
//   pik->SetBranchStatus("chisqrK18");
//   pik->SetBranchStatus("pK18");
//   pik->SetBranchStatus("xtgtK18");
//   pik->SetBranchStatus("ytgtK18");
//   pik->SetBranchStatus("utgtK18");
//   pik->SetBranchStatus("vtgtK18");
//   pik->SetBranchStatus("thetaK18");
//   pik->SetBranchStatus("nlSdcIn");
//   pik->SetBranchStatus("ntSdcIn");
//   pik->SetBranchStatus("nhSdcIn");
//   pik->SetBranchStatus("chisqrSdcIn");
//   pik->SetBranchStatus("x0SdcIn");
//   pik->SetBranchStatus("y0SdcIn");
//   pik->SetBranchStatus("u0SdcIn");
//   pik->SetBranchStatus("v0SdcIn");
//   pik->SetBranchStatus("nlSdcOut");
//   pik->SetBranchStatus("ntSdcOut");
//   pik->SetBranchStatus("nhSdcOut");
//   pik->SetBranchStatus("chisqrSdcOut");
//   pik->SetBranchStatus("x0SdcOut");
//   pik->SetBranchStatus("y0SdcOut");
//   pik->SetBranchStatus("u0SdcOut");
//   pik->SetBranchStatus("v0SdcOut");
   pik->SetBranchStatus("ntKurama");
//   pik->SetBranchStatus("nhKurama");
   pik->SetBranchStatus("chisqrKurama");
//   pik->SetBranchStatus("stof");
//   pik->SetBranchStatus("path");
   pik->SetBranchStatus("pKurama");
   pik->SetBranchStatus("qKurama");
   pik->SetBranchStatus("m2");
//   pik->SetBranchStatus("xtgtKurama");
//   pik->SetBranchStatus("ytgtKurama");
//   pik->SetBranchStatus("utgtKurama");
//   pik->SetBranchStatus("vtgtKurama");
//   pik->SetBranchStatus("thetaKurama");
//   pik->SetBranchStatus("xtofKurama");
//   pik->SetBranchStatus("ytofKurama");
//   pik->SetBranchStatus("utofKurama");
//   pik->SetBranchStatus("vtofKurama");
   pik->SetBranchStatus("tofsegKurama");
   pik->SetBranchStatus("sftxsegKurama");
//   pik->SetBranchStatus("vpx");
//   pik->SetBranchStatus("vpy");
   pik->SetBranchStatus("vpseg");
//   pik->SetBranchStatus("nPi");
//   pik->SetBranchStatus("nK");
//   pik->SetBranchStatus("nPiK");
   pik->SetBranchStatus("vtx");
   pik->SetBranchStatus("vty");
   pik->SetBranchStatus("vtz");
//   pik->SetBranchStatus("closeDist");
//   pik->SetBranchStatus("theta");
   pik->SetBranchStatus("MissMass");
//   pik->SetBranchStatus("MissMassCorr");
//   pik->SetBranchStatus("MissMassCorrDE");
//   pik->SetBranchStatus("thetaCM");
//   pik->SetBranchStatus("costCM");
//   pik->SetBranchStatus("xpi");
//   pik->SetBranchStatus("ypi");
//   pik->SetBranchStatus("upi");
//   pik->SetBranchStatus("vpi");
//   pik->SetBranchStatus("xk");
//   pik->SetBranchStatus("yk");
//   pik->SetBranchStatus("uk");
//   pik->SetBranchStatus("vk");
//   pik->SetBranchStatus("pOrg");
//   pik->SetBranchStatus("pCalc");
//   pik->SetBranchStatus("pCorr");
//   pik->SetBranchStatus("pCorrDE");

// Set branch addresses -----------------------------------------------------------------------------
//     pik->SetBranchAddress("runnum",&runnum);
//     pik->SetBranchAddress("evnum",&evnum);
     pik->SetBranchAddress("spill",&spill);
//   pik->SetBranchAddress("trigpat",trigpat);
     pik->SetBranchAddress("trigflag",trigflag);
//   pik->SetBranchAddress("nhBh1",&nhBh1);
//   pik->SetBranchAddress("csBh1",csBh1);
//   pik->SetBranchAddress("Bh1Seg",Bh1Seg);
//   pik->SetBranchAddress("tBh1",tBh1);
//   pik->SetBranchAddress("dtBh1",dtBh1);
//   pik->SetBranchAddress("deBh1",deBh1);
//   pik->SetBranchAddress("btof",btof);
//   pik->SetBranchAddress("nhBh2",&nhBh2);
//   pik->SetBranchAddress("csBh2",csBh2);
//   pik->SetBranchAddress("Bh2Seg",Bh2Seg);
//   pik->SetBranchAddress("tBh2",tBh2);
//   pik->SetBranchAddress("t0Bh2",t0Bh2);
//   pik->SetBranchAddress("dtBh2",dtBh2);
//   pik->SetBranchAddress("deBh2",deBh2);
//   pik->SetBranchAddress("nhTof",&nhTof);
//   pik->SetBranchAddress("csTof",csTof);
//   pik->SetBranchAddress("TofSeg",TofSeg);
//   pik->SetBranchAddress("tTof",tTof);
//   pik->SetBranchAddress("dtTof",dtTof);
//   pik->SetBranchAddress("deTof",deTof);
//   pik->SetBranchAddress("nhBft",&nhBft);
//   pik->SetBranchAddress("csBft",csBft);
//   pik->SetBranchAddress("tBft",tBft);
//   pik->SetBranchAddress("wBft",wBft);
//   pik->SetBranchAddress("BftPos",BftPos);
   pik->SetBranchAddress("nhSch",&nhSch);
//   pik->SetBranchAddress("csSch",csSch);
//   pik->SetBranchAddress("tSch",tSch);
//   pik->SetBranchAddress("wSch",wSch);
//     pik->SetBranchAddress("SchPos",SchPos);
//     pik->SetBranchAddress("SchSeg",SchSeg);
//     pik->SetBranchAddress("delta_x",delta_x);
     pik->SetBranchAddress("delta_seg",delta_seg);
//     pik->SetBranchAddress("sftx_unhits",&sftx_unhits);
//     pik->SetBranchAddress("sftx_uhitpat",sftx_uhitpat);
//     pik->SetBranchAddress("nhSftX",&nhSftX);
//     pik->SetBranchAddress("SftXSeg",SftXSeg);
//   pik->SetBranchAddress("nlBcOut",&nlBcOut);
//   pik->SetBranchAddress("ntBcOut",&ntBcOut);
//   pik->SetBranchAddress("nhBcOut",nhBcOut);
//   pik->SetBranchAddress("chisqrBcOut",chisqrBcOut);
//   pik->SetBranchAddress("x0BcOut",x0BcOut);
//   pik->SetBranchAddress("y0BcOut",y0BcOut);
//   pik->SetBranchAddress("u0BcOut",u0BcOut);
//   pik->SetBranchAddress("v0BcOut",v0BcOut);
//   pik->SetBranchAddress("xtgtBcOut",xtgtBcOut);
//   pik->SetBranchAddress("ytgtBcOut",ytgtBcOut);
//   pik->SetBranchAddress("xbh2BcOut",xbh2BcOut);
//   pik->SetBranchAddress("ybh2BcOut",ybh2BcOut);
//   pik->SetBranchAddress("ntK18",&ntK18);
//   pik->SetBranchAddress("nhK18",nhK18);
//   pik->SetBranchAddress("chisqrK18",chisqrK18);
//   pik->SetBranchAddress("pK18",pK18);
//   pik->SetBranchAddress("xtgtK18",xtgtK18);
//   pik->SetBranchAddress("ytgtK18",ytgtK18);
//   pik->SetBranchAddress("utgtK18",utgtK18);
//   pik->SetBranchAddress("vtgtK18",vtgtK18);
//   pik->SetBranchAddress("thetaK18",thetaK18);
//   pik->SetBranchAddress("nlSdcIn",&nlSdcIn);
//   pik->SetBranchAddress("ntSdcIn",&ntSdcIn);
//   pik->SetBranchAddress("nhSdcIn",nhSdcIn);
//   pik->SetBranchAddress("chisqrSdcIn",chisqrSdcIn);
//   pik->SetBranchAddress("x0SdcIn",x0SdcIn);
//   pik->SetBranchAddress("y0SdcIn",y0SdcIn);
//   pik->SetBranchAddress("u0SdcIn",u0SdcIn);
//   pik->SetBranchAddress("v0SdcIn",v0SdcIn);
//   pik->SetBranchAddress("nlSdcOut",&nlSdcOut);
//   pik->SetBranchAddress("ntSdcOut",&ntSdcOut);
//   pik->SetBranchAddress("nhSdcOut",nhSdcOut);
//   pik->SetBranchAddress("chisqrSdcOut",chisqrSdcOut);
//   pik->SetBranchAddress("x0SdcOut",x0SdcOut);
//   pik->SetBranchAddress("y0SdcOut",y0SdcOut);
//   pik->SetBranchAddress("u0SdcOut",u0SdcOut);
//   pik->SetBranchAddress("v0SdcOut",v0SdcOut);
     pik->SetBranchAddress("ntKurama",&ntKurama);
//   pik->SetBranchAddress("nhKurama",nhKurama);
     pik->SetBranchAddress("chisqrKurama",chisqrKurama);
//   pik->SetBranchAddress("stof",stof);
//   pik->SetBranchAddress("path",path);
     pik->SetBranchAddress("pKurama",pKurama);
     pik->SetBranchAddress("qKurama",qKurama);
     pik->SetBranchAddress("m2",m2);
//     pik->SetBranchAddress("xtgtKurama",xtgtKurama);
//     pik->SetBranchAddress("ytgtKurama",ytgtKurama);
//   pik->SetBranchAddress("utgtKurama",utgtKurama);
//   pik->SetBranchAddress("vtgtKurama",vtgtKurama);
//   pik->SetBranchAddress("thetaKurama",thetaKurama);
//   pik->SetBranchAddress("xtofKurama",xtofKurama);
//   pik->SetBranchAddress("ytofKurama",ytofKurama);
//   pik->SetBranchAddress("utofKurama",utofKurama);
//   pik->SetBranchAddress("vtofKurama",vtofKurama);
     pik->SetBranchAddress("tofsegKurama",tofsegKurama);
     pik->SetBranchAddress("sftxsegKurama",&sftxsegKurama);
//     pik->SetBranchAddress("vpx",vpx);
//     pik->SetBranchAddress("vpy",vpy);
     pik->SetBranchAddress("vpseg",vpseg);
//   pik->SetBranchAddress("nPi",&nPi);
//   pik->SetBranchAddress("nK",&nK);
//   pik->SetBranchAddress("nPiK",&nPiK);
     pik->SetBranchAddress("vtx",vtx);
     pik->SetBranchAddress("vty",vty);
     pik->SetBranchAddress("vtz",vtz);
//   pik->SetBranchAddress("closeDist",closeDist);
//   pik->SetBranchAddress("theta",theta);
     pik->SetBranchAddress("MissMass",MissMass);
//   pik->SetBranchAddress("MissMassCorr",MissMassCorr);
//   pik->SetBranchAddress("MissMassCorrDE",MissMassCorrDE);
//   pik->SetBranchAddress("thetaCM",thetaCM);
//   pik->SetBranchAddress("costCM",costCM);
//   pik->SetBranchAddress("xpi",xpi);
//   pik->SetBranchAddress("ypi",ypi);
//   pik->SetBranchAddress("upi",upi);
//   pik->SetBranchAddress("vpi",vpi);
//   pik->SetBranchAddress("xk",xk);
//   pik->SetBranchAddress("yk",yk);
//   pik->SetBranchAddress("uk",uk);
//   pik->SetBranchAddress("vk",vk);
//   pik->SetBranchAddress("pOrg",pOrg);
//   pik->SetBranchAddress("pCalc",pCalc);
//   pik->SetBranchAddress("pCorr",pCorr);
//   pik->SetBranchAddress("pCorrDE",pCorrDE);



//-para def-----------------------------------------------------------------------------------------
   double HULMHTDCCalib = -0.8333;

   int Hist1Max = 0;
   int Hist2Max = 0;

   int chisqr = 0;

//-hist def-----------------------------------------------------------------------------------------
//   Hist1Max = 5151;
//   Hist2Max = 1214;
   Hist1Max =1; 
   Hist2Max =0; 
   chisqr = 50;
   TH1D *Hist1[Hist1Max];
   TH2D *Hist2[Hist2Max];

    Hist1[0]= new TH1D("MissMass Sigma Cut1","MissMass Sigma Cut1",100,0.8,1.4);

//    Hist2[1]= new TH1D("MissMass Sigma Cut1","MissMass Sigma Cut1",100,0.8,1.4);

//-Legend def --------------------------------------------------------------------------------------
//  TLegend *Leg1 = new TLegend(0.78,0.575,0.98,0.935);

//-Event Loop --------------------------------------------------------------------------------------
   Long64_t nentries = pik->GetEntries();
//   Long64_t nentries = 10000;

//-Event Loop First --------
   for (Long64_t s=0; s<nentries;s++) {
     pik->GetEntry(s);

//     if(s%(nentries/10) ==0){
//       std::cout << ( ((double)s)/nentries *100 ) << "%\t" << s << "/" << nentries << "\r"  << std::endl;
//     }

     bool sch_flag = false;

     if( trigflag[28]<0 ) continue; //Cut1

     if( ntKurama!=1 ) continue; //Cut1

     for(int i=0; i<nhSch; i++){
       if(delta_seg[i]==0) sch_flag = true;
     }

     if( chisqrKurama[0]>50 ) continue; //Cut1
     if( !sch_flag ) continue; //Cut1

     for(int l=0; l < Mtx_prm.size(); l++){
       double m = 0;
       double n = 0;
       double min = 0;
       double max = 0;
       m = (double)Mtx_prm.at(l).at(1);
       n = (double)Mtx_prm.at(l).at(0);
       min = (double)Mtx_prm.at(l).at(2);
       max = (double)Mtx_prm.at(l).at(3) + 1;
       if( vpseg[1]==n && tofsegKurama[0]-1.==m ){
         if(m2[0]>0.15 && m2[0]<0.35 && qKurama[0]>0){
           if( vtx[0]>-20 && vtx[0]<20 && vty[0]>-20 && vty[0]<20 && vtz[0]>-200 && vtz[0]<200 ){
             if(sftxsegKurama>min&&sftxsegKurama<max){
               if( MissMass[0]>1.15 && MissMass[0]<1.25 ){
                 Hist1[0]->Fill(MissMass[0]);
               }
             }
           }//Cut5
         }//Cut4
       }
     }// for Mtx_Pat.size()
   } 

//-Canvas def---------------------------------------------------------------------------------------

//  TCanvas *c1 = new TCanvas("c1","c1",1200,900);
//  TCanvas *c2 = new TCanvas("c2","c2",1200,900);
//  c2->Divide(2,2);
//   c1->Print(pdf+"["); 
//-Hist Draw----------------------------------------------------------------------------------------
//   c1->cd();
   for(int i=0; i<Hist1Max; i++){
//     Hist1[i]->Draw();
//     c1->Print(pdf);
     //   c1->Print(Form("%s/Mtx_Pat_Make2_run%05d_Hist1_%04d.pdf",pdfDhire.Data(),runnum,i));
   }
        
   double  SigmaTotal=0.;
   SigmaTotal = Hist1[0]->Integral();

//  std::cout << "Sigma Total \t" << SigmaTotal << std::endl;

//   c1->Print(pdf+"]"); 
   return SigmaTotal;

}

void Mtx_Pat_Sigma(){
  TString anadir1=Form("%s/work/e40/ana",std::getenv("HOME")); 
  TString pdfDhire1 = Form("%s/pdf/trigger", anadir1.Data());

//  int mtxnum = 1;
//  int mtxgroup[]={15};

//  int mtxnum = 3;
  int mtxnum = 9;
//  int mtxgroup[]={2,4,6,9,10,11,12};
//  int mtxgroup[]={1,2,5,10,20,50,100};
//  int mtxgroup[]={1,2,4,6,8,10,20};
//  int mtxnum = 3;
//  int mtxnum = 1;
//  int mtxgroup[]={0,1,2};
//  int mtxgroup[]={1};
//  int mtxnum = 10;
  int mtxgroup[]={1,5,10,20,25,30,36,40,50};
//  int mtxgroup[]={900,990,999};
  double SigmaNum[mtxnum];

  for(int i=0;i<mtxnum; i++){
    SigmaNum[i] = SigmaCountbyMtx(6,0,2,mtxgroup[i]);
//    std::cout << "Sigma Total \t" << SigmaNum[i] << std::endl;
  }

  std::ofstream fout1;
  fout1.open(Form("%s/dat/trigger/SigmaNumberByMatrix_r1.txt", anadir1.Data()));
//  fout1.open(Form("%s/dat/trigger/SigmaNumberByMatrix_SFTChange.txt", anadir1.Data()));
//  fout1.open(Form("%s/dat/trigger/SigmaNumberByMatrix1.txt", anadir1.Data()));
//  fout1.open(Form("%s/dat/trigger/SigmaNumberByMatrix2.txt", anadir1.Data()));
//  fout1.open(Form("%s/dat/trigger/SigmaNumberByMatrix%d.txt", anadir1.Data(),mtxgroup[0]));
//  fout1.open(Form("%s/dat/trigger/SigmaNumberByMatrix_matirxSFT.txt", anadir1.Data()));
  for(int i=0; i<mtxnum; i++){
    fout1 << Form("%d",mtxgroup[i]) << "\t" << SigmaNum[i] << std::endl;
  }

}
