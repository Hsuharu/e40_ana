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
TString pdf = Form("%s/pdf/trigger/SigmabyRatio.pdf", anadir.Data());
TString pdfDhire = Form("%s/pdf/trigger", anadir.Data());

void FirstCutSigmaRatio(){

  gStyle->SetOptTitle(0);
  gStyle->SetLabelSize(0.04,"XYZ");
  gStyle->SetTitleSize(0.05,"XYZ");
  gStyle->SetTitleOffset(1.2,"X");
  gStyle->SetTitleOffset(1.3,"Y");
  gStyle->SetPadLeftMargin(0.16);
  gStyle->SetPadBottomMargin(0.16);

  std::vector<double> FirstCutRatio1   ;
  std::vector<double> FirstCutRatio2   ;
  std::vector<double> AllCutSigmaNum  ;
  std::vector<double> FirstCutSigmaNum1  ;
  std::vector<double> FirstCutSigmaNum2  ;
  std::vector<double> FirstCutSigmaAccept1  ;
  std::vector<double> FirstCutSigmaAccept2  ;
  std::vector<double> Accept1err  ;
  std::vector<double> Accept2err  ;
  std::vector<double> xerr  ;

  TString filein1=Form("%s/dat/trigger/SigmaNumberByMatrix123.txt", anadir.Data()); 
  TString filein2=Form("%s/dat/trigger/SigmaNumberByMatrix1.txt", anadir.Data()); 
  TString filein3=Form("%s/dat/trigger/SigmaNumberByMatrix2.txt", anadir.Data()); 

  std::ifstream fin1(filein1);
  std::ifstream fin2(filein2);
  std::ifstream fin3(filein3);
  std::string line;

  while(std::getline(fin1, line)){
    double a=-1., b=-1.;
    std::istringstream input_line( line );
    if( input_line >> a >> b ){
      //      FirstCutRatio1.push_back(a);
      AllCutSigmaNum.push_back(b);
    }
  }

  while(std::getline(fin2, line)){
    double a=-1., b=-1.;
    std::istringstream input_line( line );
    if( input_line >> a >> b ){
      FirstCutRatio1.push_back(a);
      FirstCutSigmaNum1.push_back(b);
    }
  }

  while(std::getline(fin3, line)){
    double a=-1., b=-1.;
    std::istringstream input_line( line );
    if( input_line >> a >> b ){
      FirstCutRatio2.push_back(a);
      FirstCutSigmaNum2.push_back(b);
    }
  }

  for(int i=0; i<FirstCutRatio1.size() ;i++){
    double a=0.,b=0.;
    a = FirstCutSigmaNum1.at(i)/AllCutSigmaNum.at(2);
    FirstCutSigmaAccept1.push_back(a);
    b = FirstCutSigmaNum2.at(i)/AllCutSigmaNum.at(2);
    FirstCutSigmaAccept2.push_back(b);
    Accept1err.push_back(sqrt(AllCutSigmaNum.at(2)*a*(1-a))/AllCutSigmaNum.at(2));
    Accept2err.push_back(sqrt(AllCutSigmaNum.at(2)*b*(1-b))/AllCutSigmaNum.at(2));
    xerr.push_back(0);
  }


  TCanvas *c1 = new TCanvas("c1","c1",1200,900);
  c1->Print(pdf+"["); 
  int gnum = 2;
  TGraph *g[gnum];
  TGraphErrors *ge[gnum];
  g[0] = new TGraph(FirstCutRatio1.size(),FirstCutRatio1.data(),FirstCutSigmaNum1.data());
  g[1] = new TGraph(FirstCutRatio2.size(),FirstCutRatio2.data(),FirstCutSigmaNum2.data());
  ge[0] = new TGraphErrors(FirstCutRatio1.size(),FirstCutRatio1.data(),FirstCutSigmaAccept1.data(),xerr.data(),Accept1err.data());
  ge[1] = new TGraphErrors(FirstCutRatio2.size(),FirstCutRatio2.data(),FirstCutSigmaAccept2.data(),xerr.data(),Accept2err.data());

  for(int i=0; i<gnum; i++ ){
    gStyle->SetOptStat(0);
    g[i]->SetTitle("");
    g[i]->SetMarkerStyle(8);
    g[i]->SetMarkerColor(1);
    g[i]->SetMarkerSize(2);
    g[i]->Draw("AP");
    c1->Print(pdf);
    c1->Print(Form("%s/SigmabyNumber%d.pdf",pdfDhire.Data(), i+1));
  }
  for(int i=0; i<gnum; i++ ){
    gStyle->SetOptStat(0);
    ge[i]->SetTitle("");
    ge[i]->SetMarkerStyle(8);
    ge[i]->SetMarkerColor(1);
    ge[i]->SetMarkerSize(2);
    ge[i]->SetMaximum(1);
    ge[i]->SetMinimum(0.9);
    ge[i]->Draw("AP");
    c1->Print(pdf);
    c1->Print(Form("%s/SigmabyRatio%d.pdf",pdfDhire.Data(), i+1));
  }
  c1->Print(pdf+"]"); 

}
