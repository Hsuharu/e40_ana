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
   }else{
     std::cout << "succusess\n" << std::endl;
   }
     
//file read 
   std::string line;

   while(fin&&getline(fin,line)){
     std::cout << line << std::endl;
   }

}

