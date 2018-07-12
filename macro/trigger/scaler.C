#include "DetectorID.hh"
#include <iostream>
#include "TString.h"

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

void scaler( int month, int runnum){
   TString anadir=Form("%s/work/e40/ana",std::getenv("HOME")); 

//file open
   ifstream fin;
   fin.open(Form("%s/data/JPARC2018%s/scaler/scaler_%05d.txt", anadir.Data(),Month[month], runnum));

   ofstream fout1;
   fout1.open(Form("%s/dat/trigger/spill_%05d.txt", anadir.Data(), runnum));
   ofstream fout2;
   fout2.open(Form("%s/dat/trigger/BH2_SUM_%05d.txt", anadir.Data(), runnum));
  
//file error
   if(!fin){
     std::cout << "File Open error\n" << std::endl;
     exit(1);
   }
     
//file read 
   std::string line;
   std::vector<double> spillnum; 
   std::vector<double> bh2sumnum; 

   while(getline(fin,line)){
     string name;
     int num=-1;
     std::istringstream input_line( line );
     std::vector<double> inner;
     if( input_line >> name >> num ){
       inner.push_back(namu);
       inner.push_back(num);
       std::cout << name << "\t" << num << std::endl;
       spill.push_back(inner);
     }
   }

}

