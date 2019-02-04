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


void Mtx_Mon_Check(int month,int runnum, int matrix = 2){

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
  TString pdf = Form("%s/pdf/trigger/Mtx_Mon_Check%d_run%05d.pdf", anadir.Data(),matrix,runnum);
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
  TFile *f = new TFile(Form("%s/analyzer_%s/rootfile/run%05d_DstPiKAna.root", anadir.Data(),Month[month],runnum),"READ");
  TTree *pik;
  f->GetObject("pik",pik);

  // Declaration of leaves types-----------------------------------------------------------------------
  //   Int_t           runnum;
  Int_t           evnum;
  Int_t           spill;
  Int_t           trigpat[32];
  Int_t           trigflag[32];
  Int_t           nhBh1;
  Int_t           csBh1[4];
  Double_t        Bh1Seg[4];
  Double_t        tBh1[4];
  Double_t        dtBh1[4];
  Double_t        deBh1[4];
  Double_t        btof[4];
  Int_t           nhBh2;
  Int_t           csBh2[4];
  Double_t        Bh2Seg[4];
  Double_t        tBh2[4];
  Double_t        t0Bh2[4];
  Double_t        dtBh2[4];
  Double_t        deBh2[4];
  Int_t           nhTof;
  Int_t           csTof[13];
  Double_t        TofSeg[13];
  Double_t        tTof[13];
  Double_t        dtTof[13];
  Double_t        deTof[13];
  Int_t           nhBft;
  Int_t           csBft[13];
  Double_t        tBft[13];
  Double_t        wBft[13];
  Double_t        BftPos[13];
  Int_t           nhSch;
  Int_t           csSch[21];
  Double_t        tSch[21];
  Double_t        wSch[21];
  Double_t        SchPos[21];
  Double_t        SchSeg[21];
  Double_t        delta_x[21];
  Double_t        delta_seg[21];
  Int_t           sftx_unhits;
  Int_t           sftx_uhitpat[0];
  Int_t           nhSftX;
  Double_t        SftXSeg[45];
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
  Int_t           nhK18[3];
  Double_t        chisqrK18[3];
  Double_t        pK18[3];
  Double_t        xtgtK18[3];
  Double_t        ytgtK18[3];
  Double_t        utgtK18[3];
  Double_t        vtgtK18[3];
  Double_t        thetaK18[3];
  Int_t           nlSdcIn;
  Int_t           ntSdcIn;
  Int_t           nhSdcIn[8];
  Double_t        chisqrSdcIn[8];
  Double_t        x0SdcIn[8];
  Double_t        y0SdcIn[8];
  Double_t        u0SdcIn[8];
  Double_t        v0SdcIn[8];
  Int_t           nlSdcOut;
  Int_t           ntSdcOut;
  Int_t           nhSdcOut[3];
  Double_t        chisqrSdcOut[3];
  Double_t        x0SdcOut[3];
  Double_t        y0SdcOut[3];
  Double_t        u0SdcOut[3];
  Double_t        v0SdcOut[3];
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
  Double_t        vtx[8];
  Double_t        vty[8];
  Double_t        vtz[8];
  Double_t        closeDist[8];
  Double_t        theta[8];
  Double_t        MissMass[8];
  Double_t        MissMassCorr[8];
  Double_t        MissMassCorrDE[8];
  Double_t        thetaCM[8];
  Double_t        costCM[8];
  Double_t        xpi[8];
  Double_t        ypi[8];
  Double_t        upi[8];
  Double_t        vpi[8];
  Double_t        xk[8];
  Double_t        yk[8];
  Double_t        uk[8];
  Double_t        vk[8];
  Double_t        pOrg[8];
  Double_t        pCalc[8];
  Double_t        pCorr[8];
  Double_t        pCorrDE[8];


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
  Hist1Max = 6;
  //   Hist2Max =  405;
  //  Hist2Max =  2;
  chisqr = 50;
  TH1D *Hist1[Hist1Max];
  TH2D *Hist2[Hist2Max];

  Hist1[0]= new TH1D("pKurama Cut3",";Momentum[GeV/c];Counts",100,0,2);
  Hist1[1]= new TH1D("pKurama Cut5",";Momentum[GeV/c];Counts",100,0,2);
  Hist1[2]= new TH1D("pKurama Cut3 w/oCut5",";Momentum[GeV/c];Counts",100,0,2);
  Hist1[3]= new TH1D("MissMass Cut3",";MissMass[GeV/c^{2}];Counts",100,-10,10);
  Hist1[4]= new TH1D("MissMass Cut5",";MissMass[GeV/c^{2}];Counts",100,-10,10);
  Hist1[5]= new TH1D("MissMass Cut3 w/oCut5",";MissMass[GeV/c^{2}];Counts",100,-10,10);

  //  Hist2[0 ]= new TH2D("Sch Position by HitSegment % vpx[1]","Sch Position by HitSegment % vpx[1]",200,-400,400,100,-400,400);
  //  Hist2[1 ]= new TH2D("Sch Position by HitSegment % vpx[1] Cut1","Sch Position by HitSegment % vpx[1] Cut1",200,-400,400,100,-400,400);


  //-Legend def --------------------------------------------------------------------------------------
  TLegend *Leg1 = new TLegend(0.78,0.575,0.98,0.935);
  TLegend *Leg2 = new TLegend(0.78,0.575,0.98,0.935);
  TLegend *Leg3 = new TLegend(0.78,0.575,0.98,0.935);

  //-Event Loop --------------------------------------------------------------------------------------
  Long64_t nentries = pik->GetEntries();
//  Long64_t nentries = 10000;

  //-Event Loop First --------
  Long64_t nbytes = 0;
  for (Long64_t s=0; s<nentries;s++) {
    nbytes += pik->GetEntry(s);

    bool mtx_flg = false;

    if(s%(nentries/10) ==0){
      std::cout << ( ((double)s)/nentries *100 ) << "%\t" << s << "/" << nentries << "\r"  << std::endl;
    }

    if( ntKurama!=1) continue;
    bool sch_flag = false;

    for(int i=0; i<nhSch; i++){
      if(delta_x[i]<-10 || delta_x[i]>10) continue;
      sch_flag = true;
    }

    if(sch_flag){ //Cut1
      if(chisqrKurama[0]<chisqr){ // Cut2
        if(qKurama[0]>0){ // Cut3
          Hist1[0]->Fill(pKurama[0]);
          Hist1[3]->Fill(MissMass[0]);
          for(int l=0; l < Mtx_prm.size(); l++){
            double m = 0;
            double n = 0;
            double min = 0;
            double max = 0;
            m = (double)Mtx_prm.at(l).at(1);
            n = (double)Mtx_prm.at(l).at(0);
            min = (double)Mtx_prm.at(l).at(2);
            max = (double)Mtx_prm.at(l).at(3) + 1;
            if(vpseg[1]==n&&tofsegKurama[0]-1==m){
              if(sftxsegKurama>min&&sftxsegKurama<max){
                Hist1[1]->Fill(pKurama[0]);
                Hist1[4]->Fill(MissMass[0]);
                mtx_flg = true;
              }
            }
          } // Cut3
          if(!mtx_flg){
            Hist1[2]->Fill(pKurama[0]);
            Hist1[5]->Fill(MissMass[0]);
          }
        } // Cut2
      } //Cut1
    } 
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
    //     c1->Print(Form("%s/Mtx_Mon_Chack%d_run%05d_Hist1_%04d.pdf",pdfDhire.Data(),matrix,runnum,i));
    //     if(i==15 || i==16 || i==38) gPad->SetLogy(0);
  }
  //   for(int i=0; i<Hist2Max; i++){
  //     Hist2[i]->Draw("colz");
  //     c1->Print(pdf);
  //     c1->Print(Form("%s/Mtx_Pos_Mon%d_run%05d_Hist2_colz_%04d.pdf",pdfDhire.Data(),matrix,runnum,i));
  //   }
  //   for(int j=0; j<Hist2Max; j++){
  //     Hist2[j]->Draw("box");
  //
  //     for(int i=0; i<SCH_Seg.size(); i++){
  //       double x1;
  //       double x2;
  //
  //       double TOF_Min_y1;
  //       double TOF_Min_y2;
  //
  //       double TOF_Max_y1;
  //       double TOF_Max_y2;
  //
  //       x1 =  (double)SCH_Seg.at(i);
  //       x2 =  (double)(SCH_Seg.at(i)+1);
  //
  //       TOF_Min_y1 =(double)TOF_Min.at(i);
  //       TOF_Min_y2 =(double)TOF_Min.at(i);
  //
  //       TOF_Max_y1 =  (double)TOF_Max.at(i)+1;
  //       TOF_Max_y2 =  (double)TOF_Max.at(i)+1;
  //
  //       TLine *MtxGateMin = new TLine(x1,TOF_Min_y1,x2,TOF_Min_y2);
  //       TLine *MtxGateMax = new TLine(x1,TOF_Max_y1,x2,TOF_Max_y2);
  //
  //       MtxGateMin->SetLineColor(2);
  //       MtxGateMax->SetLineColor(2);
  //       MtxGateMin->SetLineWidth(1);
  //       MtxGateMax->SetLineWidth(1);
  //       MtxGateMin->Draw("same");
  //       MtxGateMax->Draw("same");
  //       if(i==0){
  //         TLine *MtxGateMin_Y = new TLine(x1,TOF_Min_y1,x1,TOF_Max_y1);
  //         MtxGateMin_Y->SetLineColor(2);
  //         MtxGateMin_Y->SetLineWidth(1);
  //         MtxGateMin_Y->Draw("same");
  //       }else if(i==SCH_Seg.size()-1){
  //         TLine *MtxGateMin_Y = new TLine(x2,TOF_Min_y1,x2,TOF_Max_y1);
  //         MtxGateMin_Y->SetLineColor(2);
  //         MtxGateMin_Y->SetLineWidth(1);
  //         MtxGateMin_Y->Draw("same");
  //       }else{
  //         if(TOF_Min.at(i)-TOF_Min.at(i-1)!=0){
  //           TLine *MtxGate_Y1 = new TLine(x1,(double)TOF_Min.at(i-1),x1,TOF_Min_y1);
  //           MtxGate_Y1->SetLineColor(2);
  //           MtxGate_Y1->SetLineWidth(1);
  //           MtxGate_Y1->Draw("same");
  //         }
  //         if(TOF_Max.at(i)-TOF_Max.at(i-1)!=0){
  //           TLine *MtxGate_Y2 = new TLine(x1,(double)TOF_Max.at(i-1)+1,x1,TOF_Max_y1);
  //           MtxGate_Y2->SetLineColor(2);
  //           MtxGate_Y2->SetLineWidth(1);
  //           MtxGate_Y2->Draw("same");
  //         }
  //       }
  //     }
  //     c1->Print(pdf);
  //     c1->Print(Form("%s/Mtx_Pos_Mon%d_run%05d_Hist2_box_%04d.pdf",pdfDhire.Data(),matrix,runnum,j));
  //   }



  int nBin = 100;
  double x[100],m[100];
  double ratio[100],m_ratio[100];
  double xerr[100],merr[0];
  double ratioerr[100],m_ratioerr[100];
  for(int i = 0; i<nBin; i++){
    x[i] = 2./(double)nBin/2. + (double)i*2./nBin;
    m[i] = 20./(double)nBin/20. + (double)i*20./nBin;
    double  a1=0.,a2=0.;
    double  b1=0.,b2=0.;
    a1=  Hist1[1]->GetBinContent(i+1);
    b1=  Hist1[0]->GetBinContent(i+1);
    a2=  Hist1[4]->GetBinContent(i+1);
    b2=  Hist1[3]->GetBinContent(i+1);
    //   x[i]=Hist1[47]->GetXaxis()->GetBinCenter(i+i);
    ratio[i] = a1/b1 ;
    m_ratio[i] = a2/b2 ;
    xerr[i] = 2./(double)nBin/2.;
    merr[i] = 20./(double)nBin/20.;
    ratioerr[i] = sqrt(b1*ratio[i]*(1-ratio[i]))/b1;
    m_ratioerr[i] = sqrt(b2*m_ratio[i]*(1-m_ratio[i]))/b2;
  }

  TGraphErrors *graph1 = new TGraphErrors(nBin,x,ratio,xerr,ratioerr);
  TGraphErrors *graph2 = new TGraphErrors(nBin,m,m_ratio,merr,m_ratioerr);
  graph1->SetMarkerStyle(20);
  graph1->SetMarkerColor(1);
  graph1->SetMarkerSize(2);
  graph2->SetMarkerStyle(20);
  graph2->SetMarkerColor(1);
  graph2->SetMarkerSize(2);
  TH1D *test = new TH1D("test",";Momentum   [GeV/c];Ratio",100,0,2);
  test->SetAxisRange(0,1,"Y");
  test->Draw();
  graph1->Draw("P");
  c1->Print(pdf);
  test->Draw();
  graph2->Draw("P");
  c1->Print(pdf);
  //  c1->Print(Form("%s/Mtx_Pos_Mon_matrix%d_run%05d_Hist1_graph.pdf",pdfDhire.Data(),matrix,runnum));

  Hist1[0]->Draw();
  Hist1[1]->SetLineColor(kRed); 
  Hist1[1]->Draw("same");
  c1->Print(pdf);

  Hist1[3]->Draw();
  Hist1[4]->SetLineColor(kRed); 
  Hist1[4]->Draw("same");
  c1->Print(pdf);
  //  c1->Print(Form("%s/Mtx_Mon_Check%d_run%05d_Hist1_0_1_same.pdf",pdfDhire.Data(),matrix,runnum));




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
