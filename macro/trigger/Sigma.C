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

bool eq3(int a,int b,int c){
  if( a!= b ) return false;
  if( b!= c ) return false;
  if( c!= a ) return false;

  return true;
}


void Sigma(int month=6,int runnum=0, int file=2){

  gStyle->SetOptStat(0);
  gStyle->SetOptTitle(0);
  gStyle->SetLabelSize(0.04,"XYZ");
  gStyle->SetTitleSize(0.05,"XYZ");
  gStyle->SetTitleOffset(1.2,"X");
  gStyle->SetTitleOffset(1.3,"Y");
  gStyle->SetPadLeftMargin(0.16);
  gStyle->SetPadBottomMargin(0.16);
//   gStyle->SetOptTitle(0);

  //Reset ROOT and connect tree file
  gROOT->Reset();
  gROOT->Reset();
  TString anadir=Form("%s/work/e40/ana",std::getenv("HOME")); 
  TString pdf = Form("%s/pdf/trigger/Sigma_run%05d.pdf", anadir.Data(),runnum);
  TString pdf1 = Form("%s/pdf/trigger/Sigma_run%05d.pdf", anadir.Data(),runnum);
  TString pdfDhire = Form("%s/pdf/trigger", anadir.Data());

  //Matrix Patern txt file PATH -----------------------------------------------------------------------
  //  TString anadir=Form("%s/work/e40/ana",std::getenv("HOME")); 
  TString filein1=Form("%s/analyzer_%s/param/MATRIXSFT/SFT_table.txt.2018Jun.3_1",anadir.Data(),Month[month] ); 

  std::ifstream fin1(filein1);

  // Param Vector Dif ----------------------------------------------------------------------
  std::vector<std::vector<int>> Mtx_prm; //size() = 301
  std::vector<std::vector<int>> New_Mtx_prm; //size() = 301
  std::string line;
  int preSCH=0;
  std::vector<std::vector<int>> sch_tof; 
  std::vector<int> SCH_Seg; 
  std::vector<int> TOF_Min; 
  std::vector<int> TOF_Max; 
  std::vector<bool> Mtx_Flag; 
  std::vector<int> SFTX_Min; 
  std::vector<int> SFTX_Max; 


  // Error Out ----------------------------------------------------------------------------------------
  if(fin1.fail() ){
    std::cerr << "file1" << std::endl;
    exit(0); 
  }  

  while(std::getline(fin1, line)){
    int sch=-1, tof=-1, sft_min=-1, sft_max=-1;
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
      if((int)sft_min%32==0){
        SFTX_Min.push_back(sft_min-10);
      }else{
        SFTX_Min.push_back(sft_min-11);
      }
      SFTX_Max.push_back(sft_max-1);
    }
    Mtx_Flag.push_back(true);
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
  TFile *f;
  if(file==2){
    f = new TFile(Form("%s/analyzer_%s/rootfile2/run%05d_DstPiKAna.root", anadir.Data(),Month[month],runnum),"READ");
  }else{
    f = new TFile(Form("%s/analyzer_%s/rootfile/run%05d_DstPiKAna.root", anadir.Data(),Month[month],runnum),"READ");
  }
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
  Int_t           csBh2[5];
  Double_t        Bh2Seg[5];
  Double_t        tBh2[5];
  Double_t        t0Bh2[5];
  Double_t        dtBh2[5];
  Double_t        deBh2[5];
  Int_t           nhTof;
  Int_t           csTof[25];
  Double_t        TofSeg[25];
  Double_t        tTof[25];
  Double_t        dtTof[25];
  Double_t        deTof[25];
  Int_t           nhBft;
  Int_t           csBft[41];
  Double_t        tBft[41];
  Double_t        wBft[41];
  Double_t        BftPos[41];
  Int_t           nhSch;
  Int_t           csSch[27];
  Double_t        tSch[27];
  Double_t        wSch[27];
  Double_t        SchPos[27];
  Double_t        SchSeg[27];
  Double_t        delta_x[27];
  Double_t        delta_seg[27];
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
  Int_t           nhSdcOut[5];
  Double_t        chisqrSdcOut[5];
  Double_t        x0SdcOut[5];
  Double_t        y0SdcOut[5];
  Double_t        u0SdcOut[5];
  Double_t        v0SdcOut[5];
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
  Hist1Max = 4;
  Hist2Max = 1;
  chisqr = 50;
  TH1D *Hist1[Hist1Max];
  TH2D *Hist2[Hist2Max];

  Hist1[0 ]= new TH1D("MissMass[0] w/Sigma",";Missing Mass [GeV/c^{2}];Counts",100,0.8,1.5);
  Hist1[1 ]= new TH1D("pKurama[0] w/Sigma",";Momentum [GeV/c];Counts",100,0.2,1.4);
  Hist1[2 ]= new TH1D("m2[0]",";m2 [(GeV/c^{2})^{2}];Counts",100,-0.4,1.4);
  Hist1[3 ]= new TH1D("MissMass[0] all",";Missing Mass [GeV/c^{2}];Counts]",100,0.8,1.5);
  Hist1[4 ]= new TH1D("pKurama[0] w/Sigma Scale",";Momentum [GeV/c];Counts",100,0,2);

//  Hist2[0 ]= new TH2D("pKurama % m2",     "pKurama % m2 "    ,100,-0.4,1.4,100,0,2);

  //-Legend def --------------------------------------------------------------------------------------
  //  TLegend *Leg1 = new TLegend(0.78,0.575,0.98,0.935);

  //-Event Loop --------------------------------------------------------------------------------------
  Long64_t nentries = pik->GetEntries();
//     Long64_t nentries = 100000;

  //-Event Loop First --------
  for (Long64_t s=0; s<nentries;s++) {
    pik->GetEntry(s);
    if(s%(nentries/10) ==0){
      std::cout << ( ((double)s)/nentries *100 ) << "%\t" << s << "/" << nentries << "\r"  << std::endl;
    }

    if( trigflag[28]<0 ) continue; //Cut1
    if( ntKurama!=1 ) continue; //Cut1
    if( chisqrKurama[0]>50 ) continue; //Cut1
          Hist1[2]->Fill(m2[0]);

    if(m2[0]>0.15 && m2[0]<0.35 && qKurama[0]>0){// && pKurama[0]<0.9){ 
      if( vtx[0]>-20 && vtx[0]<20 && vty[0]>-20 && vty[0]<20 && vtz[0]>-200 && vtz[0]<200 ){
        Hist1[3]->Fill(MissMass[0]);
        if(MissMass[0]<1.25&&MissMass[0]>1.15){
          Hist1[0]->Fill(MissMass[0]);
          Hist1[1]->Fill(pKurama[0]);
          Hist1[4]->Fill(pKurama[0]);
        }
      }
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

  //- Analysis ---------------------------------------------------------------------------------------

  //-Canvas def---------------------------------------------------------------------------------------

  TCanvas *c1 = new TCanvas("c1","c1",1200,900);
  TCanvas *c2 = new TCanvas("c2","c2",1200,900);
  c2->Divide(2,2);
  c1->Print(pdf+"["); 
   gStyle->SetOptStat(0);
   gStyle->SetOptTitle(0);
   gStyle->SetPadLeftMargin(0.15);
   gStyle->SetPadBottomMargin(0.15);
   
  //-Hist Draw----------------------------------------------------------------------------------------
  c1->cd();
  for(int i=0; i<Hist1Max; i++){
    //   if(i==15 || i==16 || i==38) gPad->SetLogy(1);
    Hist1[i]->Draw();
    if(i==2){
      double y1 = 0.;
      double y3 = 0.;
      y3 = Hist1[2]->GetBinContent(Hist1[2]->GetMaximumBin());
      TLine *Min = new TLine(0.15,y1,0.15,y3);
      TLine *Max = new TLine(0.35,y1,0.35,y3);
      Min->SetLineColor(2);
      Max->SetLineColor(2);
      Min->SetLineWidth(1);
      Max->SetLineWidth(1);
      Min->Draw("same");
      Max->Draw("same");
    }
    if(i==3){
      double y1 = 0.;
      double y3 = 0.;
      y3 = Hist1[3]->GetBinContent(Hist1[3]->GetMaximumBin());
      TLine *Min = new TLine(1.15,y1,1.15,y3);
      TLine *Max = new TLine(1.25,y1,1.25,y3);
      Min->SetLineColor(2);
      Max->SetLineColor(2);
      Min->SetLineWidth(1);
      Max->SetLineWidth(1);
      Min->Draw("same");
      Max->Draw("same");
    }
    c1->Print(pdf);
    c1->Print(Form("%s/Sigma_run%05d_Hist1_%04d.pdf",pdfDhire.Data(),runnum,i));
    //   if(i==15 || i==16 || i==38) gPad->SetLogy(0);
  }

  double max=0.;
  double sum=0.;
  max = Hist1[4]->GetBinContent(Hist1[4]->GetMaximumBin());
  sum = Hist1[4]->Integral();
  Hist1[4]->Scale(1./max);
  Hist1[4]->Draw("hist");
  c1->Print(pdf);
  c1->Print(Form("%s/Sigma_run%05d_Hist1_ScaleMon.pdf",pdfDhire.Data(),runnum));

  TString filein2=Form("%s/dat/trigger/MonDist_matrix%d.txt", anadir.Data(), 2); 
  std::ifstream fin2(filein2);
  std::vector<double> cx; 
  std::vector<double> cratio; 
  std::vector<double> cxerr; 
  std::vector<double> cratioerr; 

  while(std::getline(fin2, line)){
    double a=-1., b=-1.,c=-1.,d=-1.;
    std::istringstream input_line( line );
    if( input_line >> a >> b >> c >> d){
      cx.push_back(a);
      cratio.push_back(b);
      cxerr.push_back(c);
      cratioerr.push_back(d);
    }
  }

  TGraphErrors *graph = new TGraphErrors(cx.size(),cx.data(),cratio.data(),cxerr.data(),cratioerr.data());
  graph->SetMarkerStyle(20);
  graph->SetMarkerColor(1);
  graph->SetMarkerSize(2);
  graph->Draw("AP");
  c1->Print(pdf);
  c1->Print(Form("%s/Sigma_run%05d_Hist1_ScaleMon_graphpdf",pdfDhire.Data(),runnum));

  Hist1[4]->Draw("hist");
  graph->Draw("P");
  c1->Print(pdf);
  c1->Print(Form("%s/Sigma_run%05d_Hist1_ScaleMon_same.pdf",pdfDhire.Data(),runnum));
  Hist1[4]->Scale(max/sum*4);
  Hist1[4]->Draw("hist");
  c1->Print(pdf);
  c1->Print(Form("%s/Sigma_run%05d_Hist1_IntegMon.pdf",pdfDhire.Data(),runnum));

  Hist1[4]->SetAxisRange(0,1,"Y");
  Hist1[4]->Draw("hist");
  graph->Draw("P");
  c1->Print(pdf);
  c1->Print(Form("%s/Sigma_run%05d_Hist1_IntegMon_same.pdf",pdfDhire.Data(),runnum));
  //     for(int i=0; i<Hist2Max; i++){
  //       Hist2[i]->Draw("colz");
  //       c1->Print(pdf);
  //  //     c1->Print(Form("%s/Mtx_Pat_Make_run%05d_Hist2_colz_%04d.pdf",pdfDhire.Data(),runnum,i));
  //     }
  
    Hist1[4]->Draw("hist");
    graph->Draw("P");
    c1->Print(pdf);
    c1->Print(Form("%s/Sigma_run%05d_Hist1_IntegMon_same.pdf",pdfDhire.Data(),runnum));

//// MissMass Distribution

  double maxM=0.;
  double sumM=0.;
  maxM = Hist1[0]->GetBinContent(Hist1[0]->GetMaximumBin());
  sumM = Hist1[0]->Integral();
  Hist1[0]->Scale(1./maxM);
  Hist1[0]->Draw("hist");
  c1->Print(pdf);
  c1->Print(Form("%s/Sigma_run%05d_Hist1_ScaleMissMass.pdf",pdfDhire.Data(),runnum));

  TString filein3=Form("%s/dat/trigger/MissMassDist_matrix%d_chisqr3.txt", anadir.Data(), 2); 
  std::ifstream fin3(filein3);
  std::vector<double> cMx; 
  std::vector<double> cMratio; 
  std::vector<double> cMxerr; 
  std::vector<double> cMratioerr; 

  while(std::getline(fin2, line)){
    double a=-1., b=-1.,c=-1.,d=-1.;
    std::istringstream input_line( line );
    if( input_line >> a >> b >> c >> d){
      cMx.push_back(a);
      cMratio.push_back(b);
      cMxerr.push_back(c);
      cMratioerr.push_back(d);
    }
  }

  TGraphErrors *graphM = new TGraphErrors(cMx.size(),cMx.data(),cMratio.data(),cMxerr.data(),cMratioerr.data());
  graphM->SetMarkerStyle(20);
  graphM->SetMarkerColor(1);
  graphM->SetMarkerSize(2);
  graphM->Draw("AP");
  c1->Print(pdf);
  c1->Print(Form("%s/Sigma_run%05d_Hist1_ScaleMissMass_graphMpdf",pdfDhire.Data(),runnum));

  Hist1[0]->Draw("hist");
  graphM->Draw("P");
  c1->Print(pdf);
  c1->Print(Form("%s/Sigma_run%05d_Hist1_ScaleMissMass_same.pdf",pdfDhire.Data(),runnum));
  Hist1[0]->Scale(maxM/sumM*4);
  Hist1[0]->Draw("hist");
  c1->Print(pdf);
  c1->Print(Form("%s/Sigma_run%05d_Hist1_IntegMissMass.pdf",pdfDhire.Data(),runnum));

  Hist1[0]->SetAxisRange(0,1,"Y");
  Hist1[0]->Draw("hist");
  graphM->Draw("P");
  c1->Print(pdf);
  c1->Print(Form("%s/Sigma_run%05d_Hist1_IntegMissMass_same.pdf",pdfDhire.Data(),runnum));
  //     for(int i=0; i<Hist2Max; i++){
  //       Hist2[i]->Draw("colz");
  //       c1->Print(pdf);
  //  //     c1->Print(Form("%s/Mtx_Pat_Make_run%05d_Hist2_colz_%04d.pdf",pdfDhire.Data(),runnum,i));
  //     }
  
    Hist1[0]->Draw("hist");
    graphM->Draw("P");
    c1->Print(pdf);
    c1->Print(Form("%s/Sigma_run%05d_Hist1_IntegMissMass_same.pdf",pdfDhire.Data(),runnum));

  c1->Print(pdf1+"]"); 


}
