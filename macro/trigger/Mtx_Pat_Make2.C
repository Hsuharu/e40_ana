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


void Mtx_Pat_Make2(int month,int runnum, int bin, int matrixnum =2){

  gStyle->SetOptTitle(0);
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
   TString pdf = Form("%s/pdf/trigger/Mtx_Pat_Make2_bin%d_%d_run%05d.pdf", anadir.Data(), bin, matrixnum,runnum);
   TString pdf1 = Form("%s/pdf/trigger/Mtx_Check2_bin%d_%d_run%05d.pdf", anadir.Data(), bin, matrixnum,runnum);
   TString pdfDhire = Form("%s/pdf/trigger", anadir.Data());

//Matrix Patern txt file PATH -----------------------------------------------------------------------
//  TString anadir=Form("%s/work/e40/ana",std::getenv("HOME")); 
//  TString filein1=Form("%s/analyzer_%s/param/MATRIXSFT/SFT_table.txt.2018Jun.3_1",anadir.Data(),Month[month] ); 
  TString filein1=Form("%s/analyzer_%s/param/MATRIXSFT/%s",anadir.Data(),Month[month],MPG[matrixnum] ); 

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
   pik->SetBranchStatus("evnum");
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
   pik->SetBranchStatus("SchPos");
   pik->SetBranchStatus("SchSeg");
   pik->SetBranchStatus("delta_x");
   pik->SetBranchStatus("delta_seg");
   pik->SetBranchStatus("sftx_unhits");
   pik->SetBranchStatus("sftx_uhitpat");
   pik->SetBranchStatus("nhSftX");
   pik->SetBranchStatus("SftXSeg");
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
   pik->SetBranchStatus("xtgtKurama");
   pik->SetBranchStatus("ytgtKurama");
//   pik->SetBranchStatus("utgtKurama");
//   pik->SetBranchStatus("vtgtKurama");
//   pik->SetBranchStatus("thetaKurama");
//   pik->SetBranchStatus("xtofKurama");
//   pik->SetBranchStatus("ytofKurama");
//   pik->SetBranchStatus("utofKurama");
//   pik->SetBranchStatus("vtofKurama");
   pik->SetBranchStatus("tofsegKurama");
   pik->SetBranchStatus("sftxsegKurama");
   pik->SetBranchStatus("vpx");
   pik->SetBranchStatus("vpy");
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
     pik->SetBranchAddress("evnum",&evnum);
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
     pik->SetBranchAddress("SchPos",SchPos);
     pik->SetBranchAddress("SchSeg",SchSeg);
     pik->SetBranchAddress("delta_x",delta_x);
     pik->SetBranchAddress("delta_seg",delta_seg);
     pik->SetBranchAddress("sftx_unhits",&sftx_unhits);
     pik->SetBranchAddress("sftx_uhitpat",sftx_uhitpat);
     pik->SetBranchAddress("nhSftX",&nhSftX);
     pik->SetBranchAddress("SftXSeg",SftXSeg);
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
     pik->SetBranchAddress("xtgtKurama",xtgtKurama);
     pik->SetBranchAddress("ytgtKurama",ytgtKurama);
//   pik->SetBranchAddress("utgtKurama",utgtKurama);
//   pik->SetBranchAddress("vtgtKurama",vtgtKurama);
//   pik->SetBranchAddress("thetaKurama",thetaKurama);
//   pik->SetBranchAddress("xtofKurama",xtofKurama);
//   pik->SetBranchAddress("ytofKurama",ytofKurama);
//   pik->SetBranchAddress("utofKurama",utofKurama);
//   pik->SetBranchAddress("vtofKurama",vtofKurama);
     pik->SetBranchAddress("tofsegKurama",tofsegKurama);
     pik->SetBranchAddress("sftxsegKurama",&sftxsegKurama);
     pik->SetBranchAddress("vpx",vpx);
     pik->SetBranchAddress("vpy",vpy);
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
   Hist1Max = 34 + (int)Mtx_prm.size()*17 +1;
   Hist2Max = 8 + (int)Mtx_prm.size()*4 + 3;
   chisqr = 50;
   TH1D *Hist1[Hist1Max];
   TH2D *Hist2[Hist2Max];

    Hist1[0 ]= new TH1D("delta_x","delta_x",200,-100,100);
    Hist1[1 ]= new TH1D("delta_seg","delta_seg",20,-10,10);
    Hist1[2 ]= new TH1D("pKurama","pKurama",100,0,2);
    Hist1[3 ]= new TH1D("m2","m2",100,-0.4,1.4);
    Hist1[4 ]= new TH1D("chisqrKurama","chisqrKurama",100,0,200);
    Hist1[5 ]= new TH1D("MissMass Sigma","MissMass Sigma",100,0.8,1.4);
    Hist1[6 ]= new TH1D("qKurama","qKurama",4,-2,2);
    Hist1[7 ]= new TH1D("vpseg[1]","vpseg[1]",NumOfSegSCH,0,NumOfSegSCH);
    Hist1[8 ]= new TH1D("tofsegKurama[0]","tofsegKurama[0]",NumOfSegTOF,0,NumOfSegTOF);
    Hist1[9 ]= new TH1D("sftxsegKurama","sftxsegKurama",bin,0,NumOfSegSFT_X);
    Hist1[10]= new TH1D("vtx[0]","vtx[0]",200,-100,100);
    Hist1[11]= new TH1D("vty[0]","vty[0]",200,-100,100);
    Hist1[12]= new TH1D("vtz[0]","vtz[0]",600,-300,300);
    Hist1[13]= new TH1D("delta_x Cut1","delta_x Cut1",200,-100,100);
    Hist1[14]= new TH1D("delta_seg Cut1","delta_seg Cut1",20,-10,10);
    Hist1[15]= new TH1D("pKurama Cut1","pKurama Cut1",100,0,2);
    Hist1[16]= new TH1D("m2 Cut1","m2 Cut1",100,-0.4,1.4);
    Hist1[17]= new TH1D("chisqrKurama Cut1","chisqrKurama Cut1",100,0,200);
    Hist1[18]= new TH1D("MissMass Sigma Cut1","MissMass Sigma Cut1",100,0.8,1.4);
    Hist1[19]= new TH1D("qKurama Cut1","qKurama Cut1",4,-2,2);
    Hist1[20]= new TH1D("vpseg[1] Cut1","vpseg[1] Cut1",NumOfSegSCH,0,NumOfSegSCH);
    Hist1[21]= new TH1D("tofsegKurama[0] Cut1","tofsegKurama[0] Cut1",NumOfSegTOF,0,NumOfSegTOF);
    Hist1[22]= new TH1D("sftxsegKurama Cut1","sftxsegKurama Cut1",bin,0,NumOfSegSFT_X);
    Hist1[23]= new TH1D("vtx[0] Cut1","vtx[0] Cut1",200,-100,100);
    Hist1[24]= new TH1D("vty[0] Cut1","vty[0] Cut1",200,-100,100);
    Hist1[25]= new TH1D("vtz[0] Cut1","vtz[0] Cut1",600,-300,300);

    Hist1[26]= new TH1D("pKurama Cut2","pKurama Cut2",100,0,2);
    Hist1[27]= new TH1D("m2 Cut2","m2 Cut2",100,-0.4,1.4);
    Hist1[28]= new TH1D("pKurama Cut3","pKurama Cut3",100,0,2);
    Hist1[29]= new TH1D("m2 Cut3","m2 Cut3",100,-0.4,1.4);
    Hist1[30]= new TH1D("pKurama Cut4","pKurama Cut4",100,0,2);
    Hist1[31]= new TH1D("m2 Cut4","m2 Cut4",100,-0.4,1.4);
    Hist1[32]= new TH1D("pKurama Cut5","pKurama Cut5",100,0,2);
    Hist1[33]= new TH1D("m2 Cut5","m2 Cut5",100,-0.4,1.4);
    Hist1[34+Mtx_prm.size()*17]= new TH1D("MissMass Sigma all",";Missing Mass [GeV/cc];Counts",100,0.8,1.4);

    for(int l=0; l < Mtx_prm.size(); l++){
      Hist1[34+Mtx_prm.size()*0 +l]= new TH1D(Form("sftxseg Sch[%d]-Tof[%d]",Mtx_prm.at(l).at(0)+1,Mtx_prm.at(l).at(1)+1),Form("sftx Sch;SFTX Segment SCH[%d]-TOF[%d];Counts",Mtx_prm.at(l).at(0),Mtx_prm.at(l).at(1)),bin,0,NumOfSegSFT_X);
      Hist1[34+Mtx_prm.size()*1 +l]= new TH1D(Form("sftxseg Cut2 Sch[%d]-Tof[%d]",Mtx_prm.at(l).at(0)+1,Mtx_prm.at(l).at(1)+1),Form("sftx Cut2;SFTX Segment SCH[%d]-TOF[%d];Counts",Mtx_prm.at(l).at(0),Mtx_prm.at(l).at(1)),bin,0,NumOfSegSFT_X);
      Hist1[34+Mtx_prm.size()*2 +l]= new TH1D(Form("sftxseg Cut3 Sch[%d]-Tof[%d]",Mtx_prm.at(l).at(0)+1,Mtx_prm.at(l).at(1)+1),Form("sftx Cut3;SFTX Segment SCH[%d]-TOF[%d];Counts",Mtx_prm.at(l).at(0),Mtx_prm.at(l).at(1)),bin,0,NumOfSegSFT_X);
      Hist1[34+Mtx_prm.size()*3 +l]= new TH1D(Form("sftxseg Cut4 Sch[%d]-Tof[%d]",Mtx_prm.at(l).at(0)+1,Mtx_prm.at(l).at(1)+1),Form("sftx Cut4;SFTX Segment SCH[%d]-TOF[%d];Counts",Mtx_prm.at(l).at(0),Mtx_prm.at(l).at(1)),bin,0,NumOfSegSFT_X);
      Hist1[34+Mtx_prm.size()*4 +l]= new TH1D(Form("sftxseg Cut5 Sch[%d]-Tof[%d]",Mtx_prm.at(l).at(0)+1,Mtx_prm.at(l).at(1)+1),Form("sftx Cut5;SFTX Segment SCH[%d]-TOF[%d];Counts",Mtx_prm.at(l).at(0),Mtx_prm.at(l).at(1)),bin,0,NumOfSegSFT_X);
      Hist1[34+Mtx_prm.size()*1 +l]->SetLineColor(8); 
      Hist1[34+Mtx_prm.size()*2 +l]->SetLineColor(9); 
      Hist1[34+Mtx_prm.size()*3 +l]->SetLineColor(kBlue); 
      Hist1[34+Mtx_prm.size()*4 +l]->SetLineColor(kRed); 
      Hist1[34+Mtx_prm.size()*1 +l]->SetFillColor(8); 
      Hist1[34+Mtx_prm.size()*2 +l]->SetFillColor(9); 
      Hist1[34+Mtx_prm.size()*3 +l]->SetFillColor(kBlue); 
//      Hist1[34+Mtx_prm.size()*4 +l]->SetFillColor(kRed); 
      Hist1[34+Mtx_prm.size()*5 +l]= new TH1D(Form("m2 Sch[%d]-Tof[%d]",Mtx_prm.at(l).at(0)+1,Mtx_prm.at(l).at(1)+1),Form("m2 Sch[%d]-Tof[%d]",Mtx_prm.at(l).at(0)+1,Mtx_prm.at(l).at(1)+1),100,-0.4,1.4);
      Hist1[34+Mtx_prm.size()*6 +l]= new TH1D(Form("m2 Cut2 Sch[%d]-Tof[%d]",Mtx_prm.at(l).at(0)+1,Mtx_prm.at(l).at(1)+1),Form("m2 Cut2 Sch[%d]-Tof[%d]",Mtx_prm.at(l).at(0)+1,Mtx_prm.at(l).at(1)+1),100,-0.4,1.4);
      Hist1[34+Mtx_prm.size()*7 +l]= new TH1D(Form("m2 Cut3 Sch[%d]-Tof[%d]",Mtx_prm.at(l).at(0)+1,Mtx_prm.at(l).at(1)+1),Form("m2 Cut3 Sch[%d]-Tof[%d]",Mtx_prm.at(l).at(0)+1,Mtx_prm.at(l).at(1)+1),100,-0.4,1.4);
      Hist1[34+Mtx_prm.size()*8 +l]= new TH1D(Form("m2 Cut4 Sch[%d]-Tof[%d]",Mtx_prm.at(l).at(0)+1,Mtx_prm.at(l).at(1)+1),Form("m2 Cut4 Sch[%d]-Tof[%d]",Mtx_prm.at(l).at(0)+1,Mtx_prm.at(l).at(1)+1),100,-0.4,1.4);
      Hist1[34+Mtx_prm.size()*9 +l]= new TH1D(Form("m2 Cut5 Sch[%d]-Tof[%d]",Mtx_prm.at(l).at(0)+1,Mtx_prm.at(l).at(1)+1),Form("m2 Cut5 Sch[%d]-Tof[%d]",Mtx_prm.at(l).at(0)+1,Mtx_prm.at(l).at(1)+1),100,-0.4,1.4);
      Hist1[34+Mtx_prm.size()*10+l]= new TH1D(Form("pKurama Sch[%d]-Tof[%d]",Mtx_prm.at(l).at(0)+1,Mtx_prm.at(l).at(1)+1),Form("pKurama Sch[%d]-Tof[%d]",Mtx_prm.at(l).at(0)+1,Mtx_prm.at(l).at(1)+1),100,0,2);
      Hist1[34+Mtx_prm.size()*11+l]= new TH1D(Form("pKurama Cut2 Sch[%d]-Tof[%d]",Mtx_prm.at(l).at(0)+1,Mtx_prm.at(l).at(1)+1),Form("pKurama Cut2 Sch[%d]-Tof[%d]",Mtx_prm.at(l).at(0)+1,Mtx_prm.at(l).at(1)+1),100,0,2);
      Hist1[34+Mtx_prm.size()*12+l]= new TH1D(Form("pKurama Cut3 Sch[%d]-Tof[%d]",Mtx_prm.at(l).at(0)+1,Mtx_prm.at(l).at(1)+1),Form("pKurama Cut3 Sch[%d]-Tof[%d]",Mtx_prm.at(l).at(0)+1,Mtx_prm.at(l).at(1)+1),100,0,2);
      Hist1[34+Mtx_prm.size()*13+l]= new TH1D(Form("pKurama Cut4 Sch[%d]-Tof[%d]",Mtx_prm.at(l).at(0)+1,Mtx_prm.at(l).at(1)+1),Form("pKurama Cut4 Sch[%d]-Tof[%d]",Mtx_prm.at(l).at(0)+1,Mtx_prm.at(l).at(1)+1),100,0,2);
      Hist1[34+Mtx_prm.size()*14+l]= new TH1D(Form("pKurama Cut5 Sch[%d]-Tof[%d]",Mtx_prm.at(l).at(0)+1,Mtx_prm.at(l).at(1)+1),Form("pKurama Cut5 Sch[%d]-Tof[%d]",Mtx_prm.at(l).at(0)+1,Mtx_prm.at(l).at(1)+1),100,0,2);
      Hist1[34+Mtx_prm.size()*15+l]= new TH1D(Form("MissMass Sigma Sch[%d]-Tof[%d]",Mtx_prm.at(l).at(0)+1,Mtx_prm.at(l).at(1)+1),Form("MissMass Sigma Sch[%d]-Tof[%d];[Gev/cc];Counts",Mtx_prm.at(l).at(0)+1,Mtx_prm.at(l).at(1)+1),100,0.8,1.4);
      Hist1[34+Mtx_prm.size()*16+l]= new TH1D(Form("sftxseg all Sch[%d]-Tof[%d]",Mtx_prm.at(l).at(0)+1,Mtx_prm.at(l).at(1)+1),Form("sftx all Sch[%d]-Tof[%d];SFTX Segment;Counts",Mtx_prm.at(l).at(0)+1,Mtx_prm.at(l).at(1)+1),bin,0,NumOfSegSFT_X);
    }                         
                              
    Hist2[0 ]= new TH2D("pKurama % m2",     "pKurama % m2 "    ,100,-0.4,1.4,100,0,2);
    Hist2[1 ]= new TH2D("tofsegKurama[0] % vpseg[1]","tofsegKurama[0] % vpseg[1];SCH Segment;TOF Segment" ,NumOfSegSCH,0,NumOfSegSCH,NumOfSegTOF,0,NumOfSegTOF);
    Hist2[2 ]= new TH2D("pKurama % m2 Cut1",     "pKurama % m2  Cut1"    ,100,-0.4,1.4,100,0,2);
    Hist2[3 ]= new TH2D("tofsegKurama[0] % vpseg[1] Cut1","tofsegKurama[0] % vpseg[1] Cut1;SCH Segment;TOF Segment" ,NumOfSegSCH,0,NumOfSegSCH,NumOfSegTOF,0,NumOfSegTOF);
    Hist2[4]= new TH2D("pKurama % m2 Cut2",     "pKurama % m2  Cut2"    ,100,-0.4,1.4,100,0,2);
    Hist2[5]= new TH2D("pKurama % m2 Cut3",     "pKurama % m2  Cut3"    ,100,-0.4,1.4,100,0,2);
    Hist2[6]= new TH2D("pKurama % m2 Cut4",     "pKurama % m2  Cut4"    ,100,-0.4,1.4,100,0,2);
    Hist2[7]= new TH2D("pKurama % m2 Cut5",     "pKurama % m2  Cut5"    ,100,-0.4,1.4,100,0,2);

    for(int l=0; l < Mtx_prm.size(); l++){
      Hist2[8+Mtx_prm.size()*0+l]= new TH2D(Form("pKurama %% m2 Cut2 Sch[%d]-Tof[%d]",Mtx_prm.at(l).at(0)+1,Mtx_prm.at(l).at(1)+1), Form("pKurama %% m2 Cut2 Sch[%d]-Tof[%d]",Mtx_prm.at(l).at(0)+1,Mtx_prm.at(l).at(1)+1)   ,100,-0.4,1.4,100,0,2);
      Hist2[8+Mtx_prm.size()*1+l]= new TH2D(Form("pKurama %% m2 Cut3 Sch[%d]-Tof[%d]",Mtx_prm.at(l).at(0)+1,Mtx_prm.at(l).at(1)+1), Form("pKurama %% m2 Cut3 Sch[%d]-Tof[%d]",Mtx_prm.at(l).at(0)+1,Mtx_prm.at(l).at(1)+1)   ,100,-0.4,1.4,100,0,2);
      Hist2[8+Mtx_prm.size()*2+l]= new TH2D(Form("pKurama %% m2 Cut4 Sch[%d]-Tof[%d]",Mtx_prm.at(l).at(0)+1,Mtx_prm.at(l).at(1)+1), Form("pKurama %% m2 Cut4 Sch[%d]-Tof[%d]",Mtx_prm.at(l).at(0)+1,Mtx_prm.at(l).at(1)+1)   ,100,-0.4,1.4,100,0,2);
      Hist2[8+Mtx_prm.size()*3+l]= new TH2D(Form("pKurama %% m2 Cut5 Sch[%d]-Tof[%d]",Mtx_prm.at(l).at(0)+1,Mtx_prm.at(l).at(1)+1), Form("pKurama %% m2 Cut5 Sch[%d]-Tof[%d]",Mtx_prm.at(l).at(0)+1,Mtx_prm.at(l).at(1)+1)   ,100,-0.4,1.4,100,0,2);
    }                                         

    Hist2[8+Mtx_prm.size()*4]= new TH2D("tofsegKurama[0] % vpseg[1] Sigma w/Matrix","tofsegKurama[0] % vpseg[1] Sigma w/Matrix;SCH Segment;TOF Segment" ,NumOfSegSCH,0,NumOfSegSCH,NumOfSegTOF,0,NumOfSegTOF);
    Hist2[8+Mtx_prm.size()*4+1]= new TH2D("tofsegKurama[0] % vpseg[1] Sigma","tofsegKurama[0] % vpseg[1] Sigma;SCH Segment;TOF Segment" ,NumOfSegSCH,0,NumOfSegSCH,NumOfSegTOF,0,NumOfSegTOF);
    Hist2[8+Mtx_prm.size()*4+2]= new TH2D("tofsegKurama[0] % vpseg[1] Sigma tight","tofsegKurama[0] % vpseg[1] Sigma;SCH Segment;TOF Segment" ,NumOfSegSCH,0,NumOfSegSCH,NumOfSegTOF,0,NumOfSegTOF);

//-Legend def --------------------------------------------------------------------------------------
//  TLegend *Leg1 = new TLegend(0.78,0.575,0.98,0.935);

//-Event Loop --------------------------------------------------------------------------------------
//   Long64_t nentries = pik->GetEntries();
   Long64_t nentries = 10000;

//-Event Loop First --------
   for (Long64_t s=0; s<nentries;s++) {
     pik->GetEntry(s);

     if(s%(nentries/10) ==0){
       std::cout << ( ((double)s)/nentries *100 ) << "%\t" << s << "/" << nentries << "\r"  << std::endl;
     }

     bool sch_flag = false;

     if( trigflag[28]<0 ) continue; //Cut1

     for(int l=0; l < Mtx_prm.size(); l++){
       double m = 0;
       double n = 0;
       m = (double)Mtx_prm.at(l).at(1);
       n = (double)Mtx_prm.at(l).at(0);
       if( vpseg[1]==n && tofsegKurama[0]-1.==m ){
//         for(int j=0; j<nhSftX; j++){
         for(int j=0; j<sftx_unhits; j++){
           Hist1[34+Mtx_prm.size()*16+l]->Fill(sftx_uhitpat[j]);
         }
       }
     }

     if( ntKurama!=1 ) continue; //Cut1

     for(int i=0; i<nhSch; i++){
       Hist1[0]->Fill(delta_x[i]);
       Hist1[1]->Fill(delta_seg[i]);
       if(delta_seg[i]==0) sch_flag = true;
     }

     Hist1[2 ]->Fill(pKurama[0]);
     Hist1[3 ]->Fill(m2[0]);
     Hist1[4 ]->Fill(chisqrKurama[0]);

     if(m2[0]>0.15 && m2[0]<0.35 && qKurama[0]>0 && pKurama[0]<0.9){ 
       if( vtx[0]>-20 && vtx[0]<20 && vty[0]>-20 && vty[0]<20 && vtz[0]>-200 && vtz[0]<200 ){
         Hist1[5 ]->Fill(MissMass[0]);
       }
     }

     Hist1[6 ]->Fill(qKurama[0]);
     Hist1[7 ]->Fill(vpseg[1]);
     Hist1[8 ]->Fill(tofsegKurama[0]-1.);
     Hist1[9 ]->Fill(sftxsegKurama);
     Hist1[10]->Fill(vtx[0]);
     Hist1[11]->Fill(vty[0]);
     Hist1[12]->Fill(vtz[0]);

     Hist2[0 ]->Fill(m2[0],pKurama[0]);
     Hist2[1 ]->Fill(vpseg[1],tofsegKurama[0]-1.);

     if( chisqrKurama[0]>50 ) continue; //Cut1
     if( !sch_flag ) continue; //Cut1

     Hist1[13]->Fill(vpx[1]);
     Hist1[14]->Fill(vpseg[1]);
     Hist1[15]->Fill(pKurama[0]);
     Hist1[16]->Fill(m2[0]);
     Hist1[17]->Fill(chisqrKurama[0]);

     if(m2[0]>0.15 && m2[0]<0.35 && qKurama[0]>0 && pKurama[0]<0.9){ 
       if( vtx[0]>-20 && vtx[0]<20 && vty[0]>-20 && vty[0]<20 && vtz[0]>-200 && vtz[0]<200 ){
         Hist1[18]->Fill(MissMass[0]);
       }
     }

     Hist1[19]->Fill(qKurama[0]);
     Hist1[20]->Fill(vpseg[1]);
     Hist1[21]->Fill(tofsegKurama[0]-1.);
     Hist1[22]->Fill(sftxsegKurama);
     Hist1[23]->Fill(vtx[0]);
     Hist1[24]->Fill(vty[0]);
     Hist1[25]->Fill(vtz[0]);

     Hist2[2 ]->Fill(m2[0],pKurama[0]);
     Hist2[3 ]->Fill(vpseg[1],tofsegKurama[0]-1.);

     if(m2[0]>0.15 && m2[0]<0.35 && qKurama[0]>0){
       if( vtx[0]>-20 && vtx[0]<20 && vty[0]>-20 && vty[0]<20 && vtz[0]>-200 && vtz[0]<200 ){
         Hist2[8+Mtx_prm.size()*4+1]->Fill(vpseg[1],tofsegKurama[0]-1.);
         if( MissMass[0]>1.15 && MissMass[0]<1.25 ){
           Hist2[8+Mtx_prm.size()*4+2]->Fill(vpseg[1],tofsegKurama[0]-1.);
         }
       }//Cut5
     }//Cut4

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
         Hist1[34+Mtx_prm.size()*0 +l]->Fill(sftxsegKurama);
         Hist1[34+Mtx_prm.size()*5 +l]->Fill(m2[0]); 
         Hist1[34+Mtx_prm.size()*10 +l]->Fill(pKurama[0]); 
         if(m2[0]>-0.15 && m2[0]<0.15){
           Hist1[26]->Fill(pKurama[0]);
           Hist1[27]->Fill(m2[0]);
           Hist1[34+Mtx_prm.size()*1 +l]->Fill(sftxsegKurama); 
           Hist1[34+Mtx_prm.size()*6 +l]->Fill(m2[0]); 
           Hist1[34+Mtx_prm.size()*11 +l]->Fill(pKurama[0]); 
           Hist2[4]->Fill(m2[0],pKurama[0]);
           Hist2[8+Mtx_prm.size()*0+l]->Fill(m2[0],pKurama[0]);
         }//Cut2
         if(m2[0]>0.6 && m2[0]<1.0 && qKurama[0]>0){
           Hist1[28]->Fill(pKurama[0]);
           Hist1[29]->Fill(m2[0]);
           Hist1[34+Mtx_prm.size()*2 +l]->Fill(sftxsegKurama); 
           Hist1[34+Mtx_prm.size()*7 +l]->Fill(m2[0]); 
           Hist1[34+Mtx_prm.size()*12 +l]->Fill(pKurama[0]); 
           Hist2[5]->Fill(m2[0],pKurama[0]);
           Hist2[8+Mtx_prm.size()*1+l]->Fill(m2[0],pKurama[0]);
         }//Cut3
         if(m2[0]>0.15 && m2[0]<0.35 && qKurama[0]>0){
           Hist1[30]->Fill(pKurama[0]);
           Hist1[31]->Fill(m2[0]);
           Hist1[34+Mtx_prm.size()*3 +l]->Fill(sftxsegKurama); 
           Hist1[34+Mtx_prm.size()*8 +l]->Fill(m2[0]); 
           Hist1[34+Mtx_prm.size()*13 +l]->Fill(pKurama[0]); 
           Hist2[6]->Fill(m2[0],pKurama[0]);
           Hist2[8+Mtx_prm.size()*2+l]->Fill(m2[0],pKurama[0]);
           if( vtx[0]>-20 && vtx[0]<20 && vty[0]>-20 && vty[0]<20 && vtz[0]>-200 && vtz[0]<200 ){
             if(sftxsegKurama>min&&sftxsegKurama<max){
               Hist1[34+Mtx_prm.size()*15 +l]->Fill(MissMass[0]); 
               Hist1[34+Mtx_prm.size()*17]->Fill(MissMass[0]); 
             }
             if( MissMass[0]>1.15 && MissMass[0]<1.25 ){
               Hist1[32]->Fill(pKurama[0]);
               Hist1[33]->Fill(m2[0]);
               Hist1[34+Mtx_prm.size()*4 +l]->Fill(sftxsegKurama); 
               Hist1[34+Mtx_prm.size()*9 +l]->Fill(m2[0]); 
               Hist1[34+Mtx_prm.size()*14 +l]->Fill(pKurama[0]); 
               Hist2[7]->Fill(m2[0],pKurama[0]);
               Hist2[8+Mtx_prm.size()*3+l]->Fill(m2[0],pKurama[0]);
               Hist2[8+Mtx_prm.size()*4]->Fill(vpseg[1],tofsegKurama[0]-1.);
             }       
           }//Cut5
         }//Cut4
       }
     }// for Mtx_Pat.size()
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
  TCanvas *c2 = new TCanvas("c2","c2",1200,900);
  c2->Divide(2,2);
   c1->Print(pdf+"["); 
//-Hist Draw----------------------------------------------------------------------------------------
   c1->cd();
   for(int i=0; i<Hist1Max; i++){
     //   if(i==15 || i==16 || i==38) gPad->SetLogy(1);
     Hist1[i]->Draw();
     c1->Print(pdf);
     //   c1->Print(Form("%s/Mtx_Pat_Make2_run%05d_Hist1_%04d.pdf",pdfDhire.Data(),runnum,i));
     //   if(i==15 || i==16 || i==38) gPad->SetLogy(0);
     if(i==34+Mtx_prm.size()*17){
       double y1 = 0.;
       double y3 = 0.;
       y3 = Hist1[34+Mtx_prm.size()*17]->GetBinContent(Hist1[34+Mtx_prm.size()*17]->GetMaximumBin());
       TLine *MMSigmaMin = new TLine(1.15,y1,1.15,y3);
       TLine *MMSigmaMax = new TLine(1.25,y1,1.25,y3);
       MMSigmaMin->SetLineColor(2);
       MMSigmaMax->SetLineColor(2);
       MMSigmaMin->SetLineWidth(1);
       MMSigmaMax->SetLineWidth(1);
       MMSigmaMin->Draw("same");
       MMSigmaMax->Draw("same");
       c1->Print(Form("%s/Mtx_Pat_Make2_matrix%d_run%05d_Hist1_%04d.pdf",pdfDhire.Data(),matrixnum,runnum,i));
     }
   }
   for(int i=0; i<Hist2Max; i++){
     Hist2[i]->Draw("colz");
     c1->Print(pdf);
//     c1->Print(Form("%s/Mtx_Pat_Make2_run%05d_Hist2_colz_%04d.pdf",pdfDhire.Data(),runnum,i));
   }
   for(int j=0; j<Hist2Max; j++){
     if(j==1 || j==3 || j ==8+Mtx_prm.size()*4 || j ==8+Mtx_prm.size()*4+1){
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
       c1->Print(Form("%s/Mtx_Pat_Make2_bin%d_run%05d_Hist2_box_%04d.pdf",pdfDhire.Data(),bin,runnum,j));
     }
   }

   c1->Print(pdf+"]"); 

   c1->Print(pdf1+"["); 

   for(int j=0; j<Hist2Max; j++){
     if(j==1 || j==3 || j ==8+Mtx_prm.size()*4 || j ==8+Mtx_prm.size()*4+1 || j ==8+Mtx_prm.size()*4+2){
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
       c1->Print(pdf1);
       c1->Print(Form("%s/Mtx_Pat_Make2_bin%d_run%05d_Hist2_box2_%04d.pdf",pdfDhire.Data(),bin,runnum,j));
     }
   }

   for(int l=0; l < Mtx_prm.size(); l++){

     c2->cd(1);
     gPad->SetLogy(1);
     Hist1[34+Mtx_prm.size()*16 +l]->Draw();
//     Hist1[34+Mtx_prm.size()*0 +l]->Draw("same");
     Hist1[34+Mtx_prm.size()*1 +l]->Draw("same");
     Hist1[34+Mtx_prm.size()*2 +l]->Draw("same");
     Hist1[34+Mtx_prm.size()*3 +l]->Draw("same");
     Hist1[34+Mtx_prm.size()*4 +l]->Draw("same");
     double min = 0.;
     double max = 0.;
     double y1 = 0.;
     double y2 = 0.;
     min = (double)Mtx_prm.at(l).at(2);
     max = (double)Mtx_prm.at(l).at(3) + 1;
     y2 = Hist1[34+Mtx_prm.size()*16 +l]->GetBinContent(Hist1[34+Mtx_prm.size()*16 +l]->GetMaximumBin());
     TLine *MtxSftXGateMin = new TLine(min,y1,min,y2);
     TLine *MtxSftXGateMax = new TLine(max,y1,max,y2);
     MtxSftXGateMin->SetLineColor(2);
     MtxSftXGateMax->SetLineColor(2);
     MtxSftXGateMin->SetLineWidth(1);
     MtxSftXGateMax->SetLineWidth(1);
     MtxSftXGateMin->Draw("same");
     MtxSftXGateMax->Draw("same");

     c2->cd(2);
     Hist1[34+Mtx_prm.size()*15 +l]->Draw();

     c2->cd(3);
     Hist1[34+Mtx_prm.size()*5 +l]->Draw();

     c2->cd(4);
     Hist1[34+Mtx_prm.size()*10 +l]->Draw();

     c2->Print(pdf1);
     if(Mtx_prm.at(l).at(0)%10==0){
       c1->cd();
       gPad->SetLogy(1);
       gStyle->SetOptStat(0);
       Hist1[34+Mtx_prm.size()*16 +l]->Draw();
       gStyle->SetOptStat(0);
       Hist1[34+Mtx_prm.size()*4 +l]->Draw("same");
       gStyle->SetOptStat(0);
       MtxSftXGateMin->Draw("same");
       gStyle->SetOptStat(0);
       MtxSftXGateMax->Draw("same");
       c1->Print(Form("%s/Mtx_Pat_Make2_bin%d_run%05d_Hist1_SFTX_matrix%d_%d_%d.pdf",pdfDhire.Data(),bin,runnum,matrixnum,Mtx_prm.at(l).at(0),Mtx_prm.at(l).at(1)));
     }
   }


   c1->Print(pdf1+"]"); 


}
