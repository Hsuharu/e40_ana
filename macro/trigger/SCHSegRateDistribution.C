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

//Work Directry
  TString anadir=Form("%s/work/e40/ana",std::getenv("HOME"));

//Global constant
  std::map<std::string, double> param_map;
  std::vector<int> runnumber{5080,5139,5118,5120,5123,5304,5303,5126,5129,5272,5275,5283};

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

///// SCH's counts Get segment by segment  //////
  void SCHSegRate_get(int runnum){
//file open
    ifstream fin;
    fin.open(Form("%s/dat/trigger/SCHBySegScaler_%05d.dat", anadir.Data(), runnum));
  
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
void SCHSegRateDistribution(){
  std::vector<double> SpillCounts;
  std::vector<double> BH2SUMCounts;
  std::vector<std::vector<double>> SCHSegCounts(NumOfSegSCH);
//file open
   ifstream fin1;
   fin1.open(Form("%s/dat/trigger/SpillByRate.txt", anadir.Data()));
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

   fin1.open(Form("%s/dat/trigger/BH2_SUMByRate.txt", anadir.Data()));

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
       param_map[name] = num;
       BH2SUMCounts.push_back(num);
     }
   }
   fin1.close();

   for(int i=0; i<runnumber.size(); i++){
     SCHSegRate_get(runnumber[i]);
     for(int j=0; j<NumOfSegSCH; j++){
       SCHSegCounts[j].push_back(param(Form("Seg%d",j+1)));
     }
   }

   for(int i=0; i<runnumber.size(); i++){
     std::cout << SCHSegCounts[0][i] << std::endl;
   }

  
}
