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

  gStyle->SetOptTitle(0);
  gStyle->SetLabelSize(0.04,"XYZ");
  gStyle->SetTitleSize(0.05,"XYZ");
  gStyle->SetTitleOffset(1.2,"X");
  gStyle->SetTitleOffset(1.3,"Y");
  gStyle->SetPadLeftMargin(0.16);
  gStyle->SetPadBottomMargin(0.16);

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
  std::vector<int> runnumber{5272,5275,5283,5298,5299,5300,5301,5302,5303,5304};

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

  TString filein1=Form("%s/dat/trigger/GateAccept.txt", anadir.Data()); 
  TString filein3=Form("%s/dat/trigger/GateAccept_matrix2_3.txt", anadir.Data()); 
  TString filein4=Form("%s/dat/trigger/GateAccept_matrix2_28.txt", anadir.Data()); 
  TString filein2=Form("%s/dat/trigger/SigmaEffi.txt", anadir.Data()); 

  std::ifstream fin1(filein1);
  std::ifstream fin2(filein2);
  std::ifstream fin3(filein3);
  std::ifstream fin4(filein4);
  std::string line;
  std::vector<double> Gate; 
  std::vector<double> Accept; 
  std::vector<double> Accept_matrix2_3; 
  std::vector<double> Accept_matrix2_28; 
  std::vector<double> SigmaEffi; 
  std::vector<double> Yield    ; 
  std::vector<double> Yield_matrix2_3    ; 
  std::vector<double> Yield_matrix2_28    ; 
  while(std::getline(fin1, line)){
    double a=-1., b=-1.;
    std::istringstream input_line( line );
    if( input_line >> a >> b ){
      Gate.push_back(a);
      Accept.push_back(b);
    }
  }
  while(std::getline(fin3, line)){
    double a=-1., b=-1.;
    std::istringstream input_line( line );
    if( input_line >> a >> b ){
      Accept_matrix2_3.push_back(b);
    }
  }

  while(std::getline(fin4, line)){
    double a=-1., b=-1.;
    std::istringstream input_line( line );
    if( input_line >> a >> b ){
      Accept_matrix2_28.push_back(b);
    }
  }

  while(std::getline(fin2, line)){
    double a=-1.;
    std::istringstream input_line( line );
    if( input_line >> a  ){
      SigmaEffi.push_back(a);
    }
  }

  double bx[] = {0.};
  double by[] = {0.};

  TCanvas *c1 = new TCanvas("c1","c1",1200,900);
  c1->Print(pdf+"["); 
  int gnum = 12;
  TGraph *g[gnum];
  TGraph *base = new TGraph(1,&bx[0],&by[0]);
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
  g[11] = new TGraph(L1Req.size(),Matrix.data(),L1Req.data());
  for(int i=0; i<gnum; i++ ){
    gStyle->SetOptStat(0);
    g[i]->SetTitle("");
    g[i]->SetMarkerStyle(8);
    g[i]->SetMarkerColor(1);
    g[i]->SetMarkerSize(2);
    g[i]->SetMinimum(0);
    g[i]->Draw("AP");
    c1->Print(pdf);
    c1->Print(Form("%s/DAQEffbyTriggerRate%d.pdf",pdfDhire.Data(), i+1));
  }
  c1->Print(pdf+"]"); 
//  g1->GetXaxis()->SetRangeUser(0,4.5);
//  g1->GetYaxis()->SetRangeUser(0,1);


  sort(Matrix.begin(),Matrix.end());
  sort(DAQEff.begin(),DAQEff.end());
  sort(L1Req.begin(),L1Req.end());

  TF1 *fit = new TF1("fit","pol1"); 
  fit->SetParameters(10,0.1);
//  g[8]->GetXaxis()->SetRangeUser(0,L1Req.back()*1.1);
//  g[8]->GetYaxis()->SetRangeUser(0,DAQEff.back()*1.1);
//  g[8]->GetXaxis()->SetTitle("");
//  g[8]->GetYaxis()->SetTitle("");
  TH1D *h8 = new TH1D("h8",";L1 [Counts/Spill];DAQ Efficiency",100,0,L1Req.back()*1.1);
  h8->SetAxisRange(0.8,DAQEff.back()*1.1,"Y");
  h8->Draw();
  g[8]->GetYaxis()->SetDecimals(2);
//  g[8]->SetMinimum(0.8);
  g[8]->Draw("P");
  c1->Print(Form("%s/L1_DAQ_pre_%d.pdf",pdfDhire.Data(), 8));
  g[8]->Fit("fit","","R",L1Req.at(0),L1Req.at(L1Req.size()-1));
  c1->Print(pdf);
  c1->Print(Form("%s/L1_DAQ_%d.pdf",pdfDhire.Data(), 8));
  double b2=fit->GetParameter(0);
  double a2=fit->GetParameter(1);

//  g[11]->GetXaxis()->SetRangeUser(0,Matrix.back()*1.1);
//  g[11]->GetYaxis()->SetRangeUser(0,L1Req.back()*1.1);
//  g[11]->GetXaxis()->SetTitle("Matrix [Counts/Spill]");
//  g[11]->GetYaxis()->SetTitle("L1 [Counts/Spill]");
  TH1D *h11 = new TH1D("h8",";Matrix [Counts/Spill];L1 [Counts/Spill]",100,0,Matrix.back()*1.1);
  h11->SetAxisRange(0,L1Req.back()*1.1,"Y");
  h11->Draw();
  g[11]->GetYaxis()->SetDecimals(2);
  g[11]->Draw("P");
  c1->Print(Form("%s/Mtx_L1_pre_%d.pdf",pdfDhire.Data(), 11));
  g[11]->Fit("fit","","R",Matrix.at(0),Matrix.at(Matrix.size()-1));
  c1->Print(pdf);
  c1->Print(Form("%s/Mtx_L1_%d.pdf",pdfDhire.Data(), 11));
  double b1=fit->GetParameter(0);
  double a1=fit->GetParameter(1);

  for(int i=0; i<Gate.size(); i++){
    Yield.push_back(SigmaEffi.at(i)*((Matrix.back()*Accept.at(i)*a1+b1)*a2+b2)*0.99/DAQEff.front());
    Yield_matrix2_3.push_back(SigmaEffi.at(i)*((Matrix.back()*Accept_matrix2_3.at(i)*a1+b1)*a2+b2)*0.99/DAQEff.front());
    Yield_matrix2_28.push_back(SigmaEffi.at(i)*((Matrix.back()*Accept_matrix2_28.at(i)*a1+b1)*a2+b2)*0.99/DAQEff.front());
  }
  TGraph *graph = new TGraph(Gate.size(),Gate.data(),Yield.data());
  graph->SetTitle("");
  graph->SetMarkerStyle(8);
  graph->SetMarkerColor(1);
  graph->SetMarkerSize(2);
  graph->GetXaxis()->SetTitle("Gate [ns]");
  graph->GetYaxis()->SetTitle("Sigma N");
  graph->Draw("AP");
  c1->Print(Form("%s/Gate_Yield.pdf",pdfDhire.Data()));

  graph->SetMinimum(0.95);
  graph->Draw("AP");
  c1->Print(Form("%s/Gate_Yield_min0.9.pdf",pdfDhire.Data()));

  TGraph *graph1 = new TGraph(Gate.size(),Gate.data(),Yield_matrix2_3.data());
  graph1->SetTitle("");
  graph1->SetMarkerStyle(8);
  graph1->SetMarkerColor(1);
  graph1->SetMarkerSize(2);
  graph1->GetXaxis()->SetTitle("Gate [ns]");
  graph1->GetYaxis()->SetTitle("Sigma Efficiency");
  graph1->Draw("AP");
  c1->Print(Form("%s/Gate_Yield_matrix2_3.pdf",pdfDhire.Data()));

  graph1->SetMinimum(0.95);
  graph1->Draw("AP");
  c1->Print(Form("%s/Gate_Yield_matrix2_3_min0.9.pdf",pdfDhire.Data()));


  TGraph *graph2 = new TGraph(Gate.size(),Gate.data(),Yield_matrix2_28.data());
  graph2->SetTitle("");
  graph2->SetMarkerStyle(8);
  graph2->SetMarkerColor(1);
  graph2->SetMarkerSize(2);
  graph2->GetXaxis()->SetTitle("Gate [ns]");
  graph2->GetYaxis()->SetTitle("Sigma Efficiency");
  graph2->Draw("AP");
  c1->Print(Form("%s/Gate_Yield_matrix2_28.pdf",pdfDhire.Data()));

  graph2->SetMinimum(0.95);
  graph2->Draw("AP");
  c1->Print(Form("%s/Gate_Yield_matrix2_28_min0.9.pdf",pdfDhire.Data()));


  std::ofstream fout1;
  fout1.open(Form("%s/dat/trigger/SpillByRate2.txt", anadir.Data()));
  for(int i=0; i<SpillCounts.size(); i++){
    fout1 << Form("run%05d",runnumber[i]) << "\t" << SpillCounts[i] << std::endl;
  }

  std::ofstream fout2;
  fout2.open(Form("%s/dat/trigger/BH2_SUMByRate2.txt", anadir.Data()));
  for(int i=0; i<BH2SUMCounts.size(); i++){
    fout2 << Form("run%05d",runnumber[i]) << "\t" << BH2SUMCounts[i] << std::endl;
  }
  
  std::ofstream fout3;
  fout3.open(Form("%s/dat/trigger/Yield.txt", anadir.Data()));
  for(int i=0; i<Yield.size(); i++){
    fout3 << Yield.at(i) << std::endl;
  }
  
  std::ofstream fout4;
  fout4.open(Form("%s/dat/trigger/Yield_matrix2_3.txt", anadir.Data()));
  for(int i=0; i<Yield_matrix2_3.size(); i++){
    fout4 << Yield_matrix2_3.at(i) << std::endl;
  }
  
  std::ofstream fout5;
  fout5.open(Form("%s/dat/trigger/Yield_matrix2_28.txt", anadir.Data()));
  for(int i=0; i<Yield_matrix2_28.size(); i++){
    fout5 << Yield_matrix2_28.at(i) << std::endl;
  }

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
