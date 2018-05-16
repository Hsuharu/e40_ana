#include "DetectorID.hh"
#include <fstream>
#include <string>
#include <vector>

double BH1 = 1;
double BH2 = 2;

void merge2(int runnum){
  TString prmdir1=Form("%s/work/e40/ana/analyzer/param/HDPRM",std::getenv("HOME")); 
  TString filein1=Form("%s/HodoParam_%05d",prmdir1.Data(),runnum); 
  
  TString prmdir2=Form("%s/work/e40/ana/hp_dat",std::getenv("HOME")); 
  TString filein2=Form("%s/HodoParam_BH1_TDC_%05d.dat",prmdir2.Data(),runnum); 
  TString filein3=Form("%s/HodoParam_CableOffset_%05d.dat",prmdir2.Data(),runnum); 
  
  TString prmdir3=Form("%s/work/e40/ana/prm/HDPRM",std::getenv("HOME")); 
  TString fileout1=Form("%s/HodoParam_%05d",prmdir3.Data(),runnum); 
  
  std::ifstream fin1(filein1);
  std::ifstream fin2(filein2);
  std::ifstream fin3(filein3);

  std::ofstream fout1(fileout1);

  std::vector<std::vector<double>> parameter; 
  std::vector<std::vector<double>> BH1TDC; 
  std::vector<std::vector<double>> BH2CO; 

  std::string line;
  std::vector<string> comment;

  if(fin1.fail() || fin2.fail() || fin3.fail()){
    std::cerr << "no file" << std::endl;
    exit(0); 
  }  

  while(std::getline(fin2, line)){
    double a=-1, b=-1;
    std::istringstream input_line( line );
    std::vector<double> inner;
    if( input_line >> a >> b ){
      inner.push_back(a);
      inner.push_back(b);
      BH1TDC.push_back(inner);
    }
  }

  while(std::getline(fin3, line)){
    double a=-1;
    std::istringstream input_line( line );
    std::vector<double> inner;
    if( input_line >> a ){
      inner.push_back(a);
      BH2CO.push_back(inner);
    }
  }

  while(std::getline(fin1, line)){
    if( line[0]=='#' || line.empty() ){
      comment.push_back(line);
      fout1 << line << endl;
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
          if( at == 1 ){
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
        }else if( cid == 2 ){
          if( at == 1 ){
            if( ud == 2){
              p0 = BH2CO[seg][0];
              inner.push_back(p0);
              inner.push_back(p1);
            }
          }
        }else{
          inner.push_back(p0);
          inner.push_back(p1);
        }
      }
      parameter.push_back(inner);
      fout1 << cid << " " << plid << " " << seg << " " << at << " " << ud << " " << p0 << " " << p1 << endl; ;
      }
  }
}

