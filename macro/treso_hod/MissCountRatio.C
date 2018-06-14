#include "DetectorID.hh"
#include <fstream>
#include <string>
#include <vector>

double BH1 = 1;
double BH2 = 2;

 const char* MONTH[] =
 {
   "Zero",
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

 const char* month[] =
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

void MissCountRatio( int month,int runnum){
  TString prmdir1=Form("%s/work/e40/ana/data/JPARC2018%s/scaler",std::getenv("HOME"),MONTH[month]); 
  TString filein1=Form("%s/scaler_%s.txt",prmdir1.Data(),runnum ); 

  TString prmdir2=Form("%s/work/e40/ana/dat/scr_dat/",std::getenv("HOME")); 
  TString fileout1=Form("%s/BH2_seg_scaler_%05d",prmdir2.Data(),runnum); 
  TString fileout2=Form("%s/TOF_24_scaler_%05d",prmdir2.Data(),runnum); 
  
  
  
  std::ifstream fin1(filein1);

  std::ofstream fout1(fileout1);
  std::ofstream fout2(fileout2);

  std::vector<std::vector<double>> parameter; 
  std::vector<double> BH2_seg; 
  std::vector<double> TOF_24; 

  std::string line;
  std::vector<string> comment;


  if(fin1.fail() ){
    std::cerr << "file1" << std::endl;
    exit(0); 
  }  

  struct scaler_line {
    std::string  name;
    double  value;
  };

  double ave3 = 0;
  double ave5 = 0;
  
  while(std::getline(fin3, line)){
    double a=-1, b=-1;
    std::istringstream input_line( line );
    std::vector<double> inner;
    if( input_line >> a >> b ){
      inner.push_back(a);
      inner.push_back(b);
      BH1TDC.push_back(inner);
      ave3 += a + b;
    }
  }
  ave3 = ave3/(2*NumOfSegBH1);

    
  while(std::getline(fin5, line)){
    double a=-1, b=-1;
    std::istringstream input_line( line );
    std::vector<double> inner;
    if( input_line >> a >> b ){
      inner.push_back(a);
      inner.push_back(b);
      BH2TDC.push_back(inner);
      ave5 += a + b;
    }
  }
  ave5 = ave5/(2*NumOfSegBH2);

  double range1 = 10000;
  double range2 = 10000;
  std::vector<user_line> user;

  while(std::getline(fin1, line)){
    if( line[0]=='#' || line.empty() ){
//      comment.push_back(line);
      fout1 << line << endl;
      fout2 << line << endl;
    }else{
      std::string  det = "miss";
      double min=-1, max=-1;
      std::istringstream input_line( line );
//      std::vector<double> inner;
      std::vector<user_line> inner;
        if( input_line >> det >> min >> max ){
          if( det == "BH1_TDC" ){
//            user[0] = det;
//            user[1] = ave3 - range1;
//            user[2] = ave3 + range1;
            min = ave3 - range1;
            max = ave3 + range1;
//            inner.push_back(user);
          }else if( det == "BH2_TDC" ){
//            user[0] = det;
//            user[1] = ave5 - range1;
//            user[2] = ave5 + range2;
            min = ave5 - range1;
            max = ave5 + range2;
//            inner.push_back(user);
          }else{
//            inner.push_back(user);
          }
        }
//      parameter.push_back(inner);
      fout1 << det << "\t " << min << "\t " << max << endl; ;
      fout2 << det << "\t " << min << "\t " << max << endl; ;
    }
  }
}

