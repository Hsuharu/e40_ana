#include "DetectorID.hh"
#include <fstream>
#include <string>
#include <vector>

const char* Month[] =
{
  "zero",
  "Jan",
  "Feb",
  "Mar",
  "Apr",
  "May",
  "Jun",
  "Jly",
  "Agt",
  "Sep",
  "Oct",
  "Nov",
  "Dec",
};


//Work Directry
  TString anadir=Form("%s/work/e40/ana",std::getenv("HOME"));
  TString pdf = Form("%s/pdf/trigger/TriggerRateSum.pdf", anadir.Data());
  TString pdfDhire = Form("%s/pdf/trigger", anadir.Data());

//Global constant
  std::map<std::string, double> param_map;

//Fanction ---------------------------------------------------------------------------
///// Param //////
  double param(std::string name){
    std::map<std::string, double>::const_iterator itr=param_map.find(name);
    if(itr==param_map.end()){
      std::cout << "No this name" << name << std::endl;
      std::exit(-1);
    }else{
      return itr->second;
    }
  }

  std::tuple<double, double>  scaler_get(int month, int runnum){
     double SpillCounts, BH2SUMCounts, L1Req, DAQEff;
  
  //file open
     ifstream fin;
     fin.open(Form("%s/data/JPARC2018%s/scaler/scaler_%05d.txt", anadir.Data(),Month[month], runnum));
  
  //file error
     if(!fin){
       std::cout << "File Open error\n" << std::endl;
       exit(1);
     }
       
  //file read 
     std::string line;
  
     while(getline(fin,line)){
       string name;
       double num=-1;
       std::istringstream input_line( line );
       if( input_line >> name >> num ){
         param_map[name] = num;
       }
     }
  
  //Output scaler count
     SpillCounts  = param("Spill")  ;
     BH2SUMCounts = param("BH2-SUM");
//     DAQEff= param("DAQ-Eff");
//     L1Req= param("L1-Req/Spill");
//     L2Acc= param("L2-Acc/Spill    ");
     
     return std::forward_as_tuple(SpillCounts, BH2SUMCounts);
  }


//Main -------------------------------------------------------------------------------
void triggerrate(){
  std::vector<double> SpillCounts;
  std::vector<double> BH2SUMCounts;
  std::vector<double> DAQEff;
  std::vector<double> L1Req;
//  std::vector<double> L2Acc;
  std::vector<double> BH2SUMMparSpillCounts;
  std::vector<double> SCHCounts;
  std::vector<double> Matrix;
  std::vector<double> BH2_K  ;
  std::vector<double> K_Scat  ;
  std::vector<double> TOF  ;
  std::vector<double> SAC  ;
  std::vector<double> SCH  ;
  std::vector<double> TOF_HT  ;

//  std::vector<int> runnumber{5080,5139,5118,5120,5123,5304,5303,5126,5129,5272,5275,5283};
  std::vector<int> runnumber{5298,5299,5300,5301,5302,5303,5304};

  for(int i=0; i<runnumber.size(); i++){
    double SCounts = 0.;
    double BCounts = 0.;
    double BMpSCounts = 0.;
    double preL1Req = 0.;
//    double preL2Acc = 0.;
    double preDAQEff = 0.;
    double preMatrix = 0.;
    double preBH2_K  ;
    double preK_Scat  ;
    double preTOF  ;
    double preSAC  ;
    double preSCH  ;
    double preTOF_HT  ;

    std::tie(SCounts
            ,BCounts
             ) = scaler_get(6,runnumber.at(i));
    BMpSCounts = BCounts/SCounts;///1000000 ;
    preDAQEff= param("DAQ-Eff");
    preL1Req= param("L1-Req/Spill");
    preMatrix = param("Matrix");
    preMatrix = preMatrix/SCounts;
    preBH2_K = param("(BH2,K)");
    preK_Scat= param("K-Scat");
    preTOF   = param("TOF");
    preSAC   = param("SAC");
    preSCH   = param("SCH");
    preTOF_HT= param("TOF-HT");
    preBH2_K = preBH2_K/SCounts;
    preK_Scat= preK_Scat/SCounts;
    preTOF   = preTOF/SCounts;
    preSAC   = preSAC/SCounts;
    preSCH   = preSCH/SCounts;
    preTOF_HT= preTOF_HT/SCounts;

//    std::cout << "Run# \t" <<runnumber.at(i) 
//              << "\t || Spill \t" << SCounts
//              << "\t || BH2-SUM \t" << BCounts 
//              << "\t || BH2-SUM[M/Spill] \t" << param("BH2-SUM")/param("Spill")/1000000
//              << "\t || L1-Req [k/Spill]\t" << preL1Req/1000
//              << "\t || DAQ-Eff\t" << preDAQEff
//              << "\t || Matrix\t" << preMatrix
//              
//              << std::endl;
    SpillCounts.push_back(SCounts);
    BH2SUMCounts.push_back(BCounts);
    BH2SUMMparSpillCounts.push_back(BMpSCounts);
//    SCHCounts.push_back(param("SCH"));
    L1Req.push_back(preL1Req);
    DAQEff.push_back(preDAQEff);
    Matrix.push_back(preMatrix);
    BH2_K.push_back(preBH2_K);
    K_Scat.push_back(preK_Scat);
    TOF.push_back(preTOF);
    SAC.push_back(preSAC);
    SCH.push_back(preSCH);
    TOF_HT.push_back(preTOF_HT);
  }

  TCanvas *c1 = new TCanvas("c1","c1",1200,900);
  c1->Print(pdf+"["); 
  TGraph *g[11];
  g[0] = new TGraph(BH2SUMMparSpillCounts.size(),BH2SUMMparSpillCounts.data(),DAQEff.data());
  g[1] = new TGraph(BH2SUMMparSpillCounts.size(),BH2SUMMparSpillCounts.data(),Matrix.data());
  g[2] = new TGraph(BH2SUMMparSpillCounts.size(),BH2SUMMparSpillCounts.data(),BH2_K.data());
  g[3] = new TGraph(BH2SUMMparSpillCounts.size(),BH2SUMMparSpillCounts.data(),K_Scat.data());
  g[4] = new TGraph(BH2SUMMparSpillCounts.size(),BH2SUMMparSpillCounts.data(),TOF.data());
  g[5] = new TGraph(BH2SUMMparSpillCounts.size(),BH2SUMMparSpillCounts.data(),SAC.data());
  g[6] = new TGraph(BH2SUMMparSpillCounts.size(),BH2SUMMparSpillCounts.data(),SCH.data());
  g[7] = new TGraph(BH2SUMMparSpillCounts.size(),BH2SUMMparSpillCounts.data(),TOF_HT.data());
  g[8] = new TGraph(L1Req.size(),L1Req.data(),DAQEff.data());
  g[9] = new TGraph(Matrix.size(),Matrix.data(),DAQEff.data());
  g[10] = new TGraph(BH2SUMMparSpillCounts.size(),BH2SUMMparSpillCounts.data(),L1Req.data());
  for(int i=0; i<11; i++ ){
    gStyle->SetOptStat(0);
    g[i]->SetMarkerStyle(8);
    g[i]->SetMarkerColor(2);
    g[i]->SetMarkerSize(2);
    g[i]->Draw("AP");
    c1->Print(pdf);
    c1->Print(Form("%s/DAQEffbyTriggerRate%d.pdf",pdfDhire.Data(), i+1));
  }
  c1->Print(pdf+"]"); 
//  g1->GetXaxis()->SetRangeUser(0,4.5);
//  g1->GetYaxis()->SetRangeUser(0,1);


//  std::ofstream fout1;
//  fout1.open(Form("%s/dat/trigger/SpillByRate.txt", anadir.Data()));
//  for(int i=0; i<SpillCounts.size(); i++){
//    fout1 << Form("run%05d",runnumber[i]) << "\t" << SpillCounts[i] << std::endl;
//  }
//
//  std::ofstream fout2;
//  fout2.open(Form("%s/dat/trigger/BH2_SUMByRate.txt", anadir.Data()));
//  for(int i=0; i<BH2SUMCounts.size(); i++){
//    fout2 << Form("run%05d",runnumber[i]) << "\t" << BH2SUMCounts[i] << std::endl;
//  }
//  
//  std::ofstream fout3;
//  fout3.open(Form("%s/dat/trigger/BH2_SUM_MparSpillByRate.txt", anadir.Data()));
//  for(int i=0; i<BH2SUMMparSpillCounts.size(); i++){
//    fout3 << Form("run%05d",runnumber[i]) << "\t" << BH2SUMMparSpillCounts[i] << std::endl;
//  }
//  
//  std::ofstream fout4;
//  fout4.open(Form("%s/dat/trigger/SCHByRate.txt", anadir.Data()));
//  for(int i=0; i<SCHCounts.size(); i++){
//    fout4 << Form("run%05d",runnumber[i]) << "\t" << SCHCounts[i] << std::endl;
//  }
  
}
