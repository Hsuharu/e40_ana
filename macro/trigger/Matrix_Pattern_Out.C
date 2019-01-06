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

bool eq3(int a,int b,int c){
  if( a!= b ) return false;
  if( b!= c ) return false;
  if( c!= a ) return false;

  return true;
}



void Matrix_Pattern_Out( int month){

  //Matrix Patern txt file PATH -----------------------------------------------------------------------
  TString anadir=Form("%s/work/e40/ana",std::getenv("HOME")); 
  TString filein1=Form("%s/analyzer_%s/param/MATRIXSFT/SFT_table.txt.2018Jun.3_1",anadir.Data(),Month[month] ); 

  std::ifstream fin1(filein1);

  // Param Vector Dif ----------------------------------------------------------------------
  std::vector<std::vector<int>> Mtx_prm; 
  std::string line;
  int preSCH=0;
  std::vector<std::vector<int>> sch_tof; 
  std::vector<int> SCH_Seg; 
  std::vector<int> TOF_Min; 
  std::vector<int> TOF_Max; 

  // Error Out ----------------------------------------------------------------------------------------
  if(fin1.fail() ){
    std::cerr << "file1" << std::endl;
    exit(0); 
  }  


  while(std::getline(fin1, line)){
    double sch=-1, tof=-1, sft_min=-1, sft_max=-1;
    std::istringstream input_line( line );
    std::vector<int> inner;
    if( input_line >> sch >> tof >> sft_min >> sft_max ){
      inner.push_back(sch);
      inner.push_back(tof);
      inner.push_back(sft_min-11);
      inner.push_back(sft_max-1);
      Mtx_prm.push_back(inner);
    }
  }


  for(int i=0; i<Mtx_prm.size(); i++){
    std::cout << "SCH=" << Mtx_prm.at(i).at(0)  << "\t" << "TOF="  <<  Mtx_prm.at(i).at(1)  << "\t"  << "SFT_Min=" << Mtx_prm.at(i).at(2)  << "\t"  << "SFT_Max=" << Mtx_prm.at(i).at(3)  << std::endl;
    if(i==0){
      preSCH = Mtx_prm.at(i).at(0);
      SCH_Seg.push_back( Mtx_prm.at(i).at(0) );
      TOF_Min.push_back( Mtx_prm.at(i).at(1) );
    }else{
      if(i==Mtx_prm.size()-1){
        TOF_Max.push_back( Mtx_prm.at(i-1).at(1) );
      }else if(Mtx_prm.at(i).at(0)-preSCH!=0){
        SCH_Seg.push_back( Mtx_prm.at(i).at(0) );
        TOF_Max.push_back( Mtx_prm.at(i-1).at(1) );
        TOF_Min.push_back( Mtx_prm.at(i).at(1) );
      }
      preSCH = Mtx_prm.at(i).at(0);
    }
  }


  std::cout << "SCH_Seg size is" << SCH_Seg.size() << "\n"  
    << "TOF_Min size is" << TOF_Min.size() << "\n"
    << "TOF_Max size is" << TOF_Max.size() << std::endl;

  if( !eq3(SCH_Seg.size(),TOF_Min.size(),TOF_Max.size()) ){
    std::cerr << "Size Not Same" << std::endl;
  }

  TCanvas *c1= new TCanvas("c1","c1",800,700);
  TH2D *Hist = new TH2D("Hist","Hist",NumOfSegSCH,0,NumOfSegSCH,NumOfSegTOF,0,NumOfSegTOF);
  Hist->Draw();

  for(int i=0; i<SCH_Seg.size(); i++){
    double x1;
    double x2;

    double TOF_Min_y1;
    double TOF_Min_y2;
                   
    double TOF_Max_y1;
    double TOF_Max_y2;

    x1 =  (double)SCH_Seg.at(i);
    x2 =  (double)(SCH_Seg.at(i)+1);

    TOF_Min_y1 = 1. + (double)TOF_Min.at(i)-1;
    TOF_Min_y2 = 1. + (double)TOF_Min.at(i)-1;

    TOF_Max_y1 = 1. + (double)TOF_Max.at(i);
    TOF_Max_y2 = 1. + (double)TOF_Max.at(i);

    TLine *MtxGateMin = new TLine(x1,TOF_Min_y1,x2,TOF_Min_y2);
    TLine *MtxGateMax = new TLine(x1,TOF_Max_y1,x2,TOF_Max_y2);

    MtxGateMin->SetLineColor(2);
    MtxGateMax->SetLineColor(2);
    MtxGateMin->SetLineWidth(1);
    MtxGateMax->SetLineWidth(1);
    MtxGateMin->Draw("same");
    MtxGateMax->Draw("same");
  }
}

