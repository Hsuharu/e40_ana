#include "DetectorID.hh"
#include <fstream>
#include <string>
#include <vector>

double BH1 = 1;
double BH2 = 2;

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

void merge_CountEff( int month,int runnum){
  TString prmdir1=Form("%s/work/e40/ana/analyzer_%s/param/HDPRM",std::getenv("HOME"),Month[month]); 
  //  TString filein1=Form("%s/HodoParam_%05d",prmdir1.Data(),runnum); 
  TString filein1=Form("%s/HodoParam_2018Jun_0",prmdir1.Data() ); 


  TString prmdir2=Form("%s/work/e40/ana/hp_dat",std::getenv("HOME")); 
  //  TString filein2=Form("%s/HodoParamMaker1_BH1_ADC_%05d.dat",prmdir2.Data(),runnum); 
  TString filein3=Form("%s/Debug_BH1_TDC_%05d.dat",prmdir2.Data(),runnum); 
  //  TString filein4=Form("%s/HodoParamMaker1_BH2_ADC_%05d.dat",prmdir2.Data(),runnum); 
  TString filein5=Form("%s/Debug_BH2_TDC_%05d.dat",prmdir2.Data(),runnum); 

  TString prmdir3=Form("%s/work/e40/ana/prm/HDPRM",std::getenv("HOME")); 
  TString fileout1=Form("%s/HodoParam_%05d",prmdir3.Data(),runnum); 
  TString fileout2=Form("%s/HodoParam_%05d",prmdir1.Data(),runnum); 

  std::ifstream fin1(filein1);
  //  std::ifstream fin2(filein2);
  std::ifstream fin3(filein3);
  //  std::ifstream fin4(filein4);
  std::ifstream fin5(filein5);

  std::ofstream fout1(fileout1);
  std::ofstream fout2(fileout2);

  std::vector<std::vector<double>> parameter; 
  //  std::vector<std::vector<double>> BH1ADC; 
  std::vector<std::vector<double>> BH1TDC; 
  //  std::vector<std::vector<double>> BH2ADC; 
  std::vector<std::vector<double>> BH2TDC; 
  std::vector<std::vector<double>> BH2CO; 

  std::string line;
  std::vector<string> comment;

  //  if(fin1.fail() || fin2.fail() || fin3.fail() || fin4.fail() || fin5.fail()){
  //    std::cerr << "no file" << std::endl;
  //    exit(0); 
  //  }  
  if(fin3.fail()){
    std::cerr << "file3" << std::endl;
    exit(0); 
  }  

  if(fin5.fail()){
    std::cerr << "file5" << std::endl;
    exit(0); 
  }  

  if(fin1.fail() ){
    std::cerr << "file1" << std::endl;
    exit(0); 
  }  
  //
  //  while(std::getline(fin2, line)){
  //    double a=-1, b=-1, c=-1, d=-1;
  //    std::istringstream input_line( line );
  //    std::vector<double> inner;
  //    if( input_line >> a >> b >> c >> d ){
  //      inner.push_back(a);
  //      inner.push_back(b);
  //      inner.push_back(c);
  //      inner.push_back(d);
  //      BH1ADC.push_back(inner);
  //    }
  //  }
  //
  while(std::getline(fin3, line)){
    double a=-1, b=-1;
    std::istringstream input_line( line );
    std::vector<double> inner;
    if( input_line >> a >> b ){
      inner.push_back(a);
      inner.push_back(b);
      BH1TDC.push_back(inner);
    }
  }
  //
  //  while(std::getline(fin4, line)){
  //    double a=-1, b=-1, c=-1, d=-1, e=-1;
  //    std::istringstream input_line( line );
  //    std::vector<double> inner;
  //    if( input_line >> a >> b >> c >> d ){
  //      inner.push_back(a);
  //      inner.push_back(b);
  //      inner.push_back(c);
  //      inner.push_back(d);
  //      BH2ADC.push_back(inner);
  //    }
  //  }
  //
  while(std::getline(fin5, line)){
    double a=-1, b=-1;
    std::istringstream input_line( line );
    std::vector<double> inner;
    if( input_line >> a >> b ){
      inner.push_back(a);
      inner.push_back(b);
      BH2TDC.push_back(inner);
    }
  }

  while(std::getline(fin1, line)){
    if( line[0]=='#' || line.empty() ){
      comment.push_back(line);
      fout1 << line << std::endl;
      fout2 << line << std::endl;
    }else{
      double cid=-1, plid=-1, seg=-1, at=-1, ud=-1;
      double p0=-9999., p1=-9999.;
      std::istringstream input_line( line );
      std::vector<double> inner;
      if( input_line >> cid >> plid >> seg >> at >> ud >> p0 >> p1 ){
        inner.push_back(cid);
        inner.push_back(plid);
        inner.push_back(seg);
        inner.push_back(cid);
        inner.push_back(at);
        inner.push_back(ud);
        if( cid == 1 ){
          if( at == 0 ){
            //            if( ud == 0){
            //              p0 = BH1ADC[seg][0];
            //              p1 = BH1ADC[seg][1];
            //              inner.push_back(p0);
            //              inner.push_back(p1);
            //            }else if(ud == 1){
            //              p0 = BH1ADC[seg][2];
            //              p1 = BH1ADC[seg][3];
            inner.push_back(p0);
            inner.push_back(p1);
            //            }
          }else if(at == 1){
            if( ud == 0){
              p0 = BH1TDC[seg][0];
              inner.push_back(p0);
              inner.push_back(p1);
            }else if(ud == 1){
              p0 = BH1TDC[seg][1];
              inner.push_back(p0);
              inner.push_back(p1);
            }
          }
        }
        if( cid == 2 ){
          if( at == 0 ){
            //            if( ud == 0){
            //              p0 = BH2ADC[seg][0];
            //              p1 = BH2ADC[seg][1];
            //              inner.push_back(p0);
            //              inner.push_back(p1);
            //            }else if(ud == 1){
            //              p0 = BH2ADC[seg][2];
            //              p1 = BH2ADC[seg][3];
            inner.push_back(p0);
            inner.push_back(p0);
            //            }
          }else if(at == 1){
            if( ud == 0){
              p0 = BH2TDC[seg][0];
              inner.push_back(p0);
              inner.push_back(p1);
            }else if(ud == 1){
              p0 = BH2TDC[seg][1];
              inner.push_back(p0);
              inner.push_back(p1);
            }else if(ud == 2){
              p0 = 0.;
              inner.push_back(p0);
              inner.push_back(p1);
            }
          }
        }
        if(cid != 1 &&  cid != 2 ){
          inner.push_back(p0);
          inner.push_back(p1);
        }
        parameter.push_back(inner);
        fout1 << cid << "\t " << plid << "\t " << seg << "\t " << at << "\t " << ud << "\t " << p0 << "  \t  " << p1 << std::endl; ;
        fout2 << cid << "\t " << plid << "\t " << seg << "\t " << at << "\t " << ud << "\t " << p0 << "  \t  " << p1 << std::endl; ;
      }
    }
  }
}

