#include "DetectorID.hh"
#include <fstream>
#include <string>
#include <vector>

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

const char* Plane[] =
{
  "V",
  "U",
  "XU",
  "XD",
  "X"
};

//Work Directry
  TString anadir=Form("%s/work/e40/ana",std::getenv("HOME"));
  TString pdfDhire = Form("%s/pdf/trigger", anadir.Data());

//Global constant
  std::map<std::string, double> param_map;
//  std::vector<int> runnumber{5080,5139,5118,5120,5123,5304,5303,5126,5129,5272,5275,5283};
  std::vector<int> runnumber{5272,5275,5283,5298,5299,5300,5301,5302,5303,5304};

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

/////// SCH's counts Get segment by segment  //////
//  void SCHSegRate_get(int runnum){
////file open
//    ifstream fin;
//    fin.open(Form("%s/dat/trigger/SCHBySegScaler_%05d.dat", anadir.Data(), runnum));
//  
////file error
//    if(!fin){
//      std::cout << "File Open error\n" << std::endl;
//      exit(1);
//    }
//       
////file read 
//    std::string line;
//  
//    while(getline(fin,line)){
//      string name;
//      double num=-1;
//      std::istringstream input_line( line );
//      if( input_line >> name >> num ){
//        param_map[name] = num;
//      }
//    }
//    fin.close();
//  }
    
///// SFT's counts Get plane by plane  //////
  void SFTPlaneRate_get(int runnum){
//file open
    ifstream fin;
    fin.open(Form("%s/dat/trigger/SFTByPlaneScaler_%05d.dat", anadir.Data(), runnum));
  
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
    fin.close();
  }
    
//Main -------------------------------------------------------------------------------
void SFTPlaneRateDistribution(){
  std::vector<double> SpillCounts;
  std::vector<double> BH2SUMCounts;
//  std::vector<std::vector<double>> SCHSegCounts(NumOfSegSCH);
  std::vector<std::vector<double>> SFTPlaneCounts(NumOfSegSCH);
//file open
   ifstream fin1;
   fin1.open(Form("%s/dat/trigger/SpillByRate2.txt", anadir.Data()));
//file error
   if(!fin1){
     std::cout << "File Open error\n" << std::endl;
     exit(1);
   }
     
//file read 
   std::string line;

   while(getline(fin1,line)){
     string name;
     double num=-1;
     std::istringstream input_line( line );
     if( input_line >> name >> num ){
//       param_map[name] = num;
       SpillCounts.push_back(num);
     }
   }
   fin1.close();

   fin1.open(Form("%s/dat/trigger/BH2_SUMByRate2.txt", anadir.Data()));

//file error
   if(!fin1){
     std::cout << "File Open error\n" << std::endl;
     exit(1);
   }
     
//file read 
   while(getline(fin1,line)){
     string name;
     double num=-1;
     std::istringstream input_line( line );
     if( input_line >> name >> num ){
//       param_map[name] = num;
       BH2SUMCounts.push_back(num);
     }
   }
   fin1.close();

   for(int i=0; i<runnumber.size(); i++){
    BH2SUMCounts.at(i) = BH2SUMCounts.at(i)/SpillCounts.at(i);
   }

//   for(int i=0; i<runnumber.size(); i++){
//     SCHSegRate_get(runnumber[i]);
//     for(int j=0; j<NumOfSegSCH; j++){
//       SCHSegCounts[j].push_back(param(Form("Seg%d",j+1))/SpillCounts[i]);
//     }
//   }

   for(int i=0; i<runnumber.size(); i++){
     SFTPlaneRate_get(runnumber.at(i));
     for(int j=0; j<5; j++){
       SFTPlaneCounts.at(j).push_back(param(Form("Plane%s",Plane[j]))/SpillCounts.at(i));
     }
   }

// TGraph---------------------------------------------------------------------
//  TGraph *graph[NumOfSegSCH];
//  for(int i=0; i<NumOfSegSCH; i++){ 
//    graph[i] = new TGraph(runnumber.size(),&BH2SUMCounts[0],&SCHSegCounts[i][0]);
//  }

  TGraph *graph1[5];
  for(int i=0; i<5; i++){ 
    graph1[i] = new TGraph(runnumber.size(),BH2SUMCounts.data(),SFTPlaneCounts.at(i).data());
  }

// TCanvas--------------------------------------------------------------------
//  TString pdf = Form("%s/pdf/trigger/SCHSegRateDistribution.pdf", anadir.Data());
  TString pdf1 = Form("%s/pdf/trigger/SFTPlaneRateDistribution2.pdf", anadir.Data());
  TCanvas *c1 = new TCanvas("c1","c1",1200,900);
//  TCanvas *c2 = new TCanvas("c2","c2",1600,900);
//  c2->Divide(4,2);
//  c1->Print(pdf+"["); 

// Frame ---------------------------------------------------------------------

//  for(int i=0 ; i<NumOfSegSCH; i++){
//    graph[i]->SetTitle(Form("SCH Segment%d Counts/spill ;BH2-SUM [ M/Spill ];SCH Segment%d [Counts/Spill]",i+1,i+1));
//    graph[i]->SetMarkerStyle(20);
//    graph[i]->SetLineStyle(2);
//    graph[i]->SetMarkerColor(2);
//    graph[i]->SetLineColor(2);
////    graph[i]->GetHistogram()->SetMinimum(0);
//    graph[i]->SetMinimum(0);
//    graph[i]->GetXaxis()->SetRangeUser(-1000000,22000000);
//    c1->cd();
//    graph[i]->Draw("ap");
//    c1->Print(pdf); 
//    if((i+1)%8 != 0){
//      c2->cd((i+1)%8);
//      graph[i]->Draw("ap");
//    }else{
//      c2->cd(8);
//      graph[i]->Draw("ap");
//      c2->Print(pdf); 
//    }
//  }
//
//  c1->Print(pdf+"]");        
  c1->Print(pdf1+"["); 
  
  for(int i=0 ; i<5; i++){
    graph1[i]->SetTitle(Form("SFT Plane%s Counts/spill ;BH2-SUM [ M/Spill ];SFT Plane%s [Counts/Spill]",Plane[i],Plane[i]));
    graph1[i]->SetMarkerStyle(8);
    graph1[i]->SetMarkerColor(2);
    graph1[i]->SetMarkerSize(2);
//    graph1[i]->GetHistogram()->SetMinimum(0);
    graph1[i]->SetMinimum(0);
    graph1[i]->GetXaxis()->SetRangeUser(-1000000,22000000);
    graph1[i]->Draw("ap");
    c1->Print(pdf1); 
    c1->Print(Form("%s/SFTByPlane%sDist.pdf",pdfDhire.Data(),Plane[i]));
  }

  c1->Print(pdf1+"]");        
  
}
