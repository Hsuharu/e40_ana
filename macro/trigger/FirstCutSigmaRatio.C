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

  std::vector<double> FirstCutRatio   ;
  std::vector<double> FirstCutRatio1   ;
  std::vector<double> FirstCutRatio2   ;
  std::vector<double> FirstCutRatio3   ;
  std::vector<double> AllCutSigmaNum  ;
  std::vector<double> FirstCutSigmaNum  ;
  std::vector<double> FirstCutSigmaNum1  ;
  std::vector<double> FirstCutSigmaNum2  ;
  std::vector<double> FirstCutSigmaNum3  ;
  std::vector<double> FirstCutSigmaAccept  ;
  std::vector<double> FirstCutSigmaAccept1  ;
  std::vector<double> FirstCutSigmaAccept2  ;
  std::vector<double> FirstCutSigmaAccept3  ;
  std::vector<double> Accepterr  ;
  std::vector<double> Accept1err  ;
  std::vector<double> Accept2err  ;
  std::vector<double> Accept3err  ;
  std::vector<double> xerr  ;



  TString filein=Form("%s/dat/trigger/SigmaNumberByMatrix.txt", anadir.Data()); 
  TString filein1=Form("%s/dat/trigger/SigmaNumberByMatrix123.txt", anadir.Data()); 
  TString filein2=Form("%s/dat/trigger/SigmaNumberByMatrix1.txt", anadir.Data()); 
  TString filein3=Form("%s/dat/trigger/SigmaNumberByMatrix2.txt", anadir.Data()); 
  TString filein4=Form("%s/dat/trigger/SigmaNumberByMatrix_r1.txt", anadir.Data()); 

  std::ifstream fin(filein);
  std::ifstream fin1(filein1);
  std::ifstream fin2(filein2);
  std::ifstream fin3(filein3);
  std::ifstream fin4(filein4);
  std::string line;

  while(std::getline(fin1, line)){
    double a=-1., b=-1.;
    std::istringstream input_line( line );
    if( input_line >> a >> b ){
      //      FirstCutRatio1.push_back(a);
      AllCutSigmaNum.push_back(b);
    }
  }

  while(std::getline(fin, line)){
    double a=-1., b=-1.;
    std::istringstream input_line( line );
    if( input_line >> a >> b ){
      FirstCutRatio.push_back(a);
      FirstCutSigmaNum.push_back(b);
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

  while(std::getline(fin4, line)){
    double a=-1., b=-1.;
    std::istringstream input_line( line );
    if( input_line >> a >> b ){
      FirstCutRatio3.push_back(a);
      FirstCutSigmaNum3.push_back(b);
    }
  }

  for(int i=0; i<FirstCutRatio.size() ;i++){
    double r=0.;
    r = FirstCutSigmaNum.at(i)/AllCutSigmaNum.at(2);
    FirstCutSigmaAccept.push_back(r);
    Accepterr.push_back(sqrt(AllCutSigmaNum.at(2)*r*(1-r))/AllCutSigmaNum.at(2));
    xerr.push_back(0);
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

  for(int i=0; i<FirstCutRatio3.size() ;i++){
    double r=0.;
    r = FirstCutSigmaNum3.at(i)/AllCutSigmaNum.at(2);
    FirstCutSigmaAccept3.push_back(r);
    Accept3err.push_back(sqrt(AllCutSigmaNum.at(2)*r*(1-r))/AllCutSigmaNum.at(2));
    xerr.push_back(0);
  }


  TCanvas *c1 = new TCanvas("c1","c1",1200,900);
  c1->Print(pdf+"["); 
  int gnum = 4;
  TGraph *g[gnum];
  TGraphErrors *ge[gnum];
  g[0] = new TGraph(FirstCutRatio1.size(),FirstCutRatio1.data(),FirstCutSigmaNum1.data());
  g[1] = new TGraph(FirstCutRatio2.size(),FirstCutRatio2.data(),FirstCutSigmaNum2.data());
  g[2] = new TGraph(FirstCutRatio.size(),FirstCutRatio.data(),FirstCutSigmaNum.data());
  g[3] = new TGraph(FirstCutRatio3.size(),FirstCutRatio3.data(),FirstCutSigmaNum3.data());
  ge[0] = new TGraphErrors(FirstCutRatio1.size(),FirstCutRatio1.data(),FirstCutSigmaAccept1.data(),xerr.data(),Accept1err.data());
  ge[1] = new TGraphErrors(FirstCutRatio2.size(),FirstCutRatio2.data(),FirstCutSigmaAccept2.data(),xerr.data(),Accept2err.data());
  ge[2] = new TGraphErrors(FirstCutRatio.size(),FirstCutRatio.data(),FirstCutSigmaAccept.data(),xerr.data(),Accepterr.data());
  ge[3] = new TGraphErrors(FirstCutRatio3.size(),FirstCutRatio3.data(),FirstCutSigmaAccept3.data(),xerr.data(),Accept3err.data());

  for(int i=0; i<gnum; i++ ){
    gStyle->SetOptStat(0);
    g[i]->SetTitle("");
    g[i]->SetMarkerStyle(8);
    g[i]->SetMarkerColor(1);
    g[i]->SetMarkerSize(2);
    g[i]->Draw("AP");
    g[i]->GetXaxis()->SetTitle("Ratio");
    g[i]->GetYaxis()->SetTitle("Counts");
    c1->Print(pdf);
    c1->Print(Form("%s/SigmabyNumber%d.pdf",pdfDhire.Data(), i+1));
  }
      TLine *line99 = new TLine(0,0.99,110,0.99);
      TLine *line99_2 = new TLine(0,0.99,60,0.99);
      line99->SetLineColor(2);
      line99->SetLineWidth(1);
      line99_2->SetLineColor(2);
      line99_2->SetLineWidth(1);
  for(int i=0; i<gnum; i++ ){
    gStyle->SetOptStat(0);
    ge[i]->SetTitle("");
    ge[i]->SetMarkerStyle(8);
    ge[i]->SetMarkerColor(1);
    ge[i]->SetMarkerSize(2);
    ge[i]->SetMaximum(1);
    ge[i]->SetMinimum(0.9);
    ge[i]->GetXaxis()->SetTitle("Ratio");
    ge[i]->GetYaxis()->SetTitle("Efficiency");
    ge[i]->Draw("AP");
    if(i!=3){
      line99->Draw("same");
      c1->Print(pdf);
      c1->Print(Form("%s/SigmabyRatio%d.pdf",pdfDhire.Data(), i+1));
      ge[i]->SetMinimum(0.95);
      line99->Draw();
      ge[i]->Draw("AP");
      line99->Draw("same");
      c1->Print(pdf);
      c1->Print(Form("%s/SigmabyRatio%dzoom.pdf",pdfDhire.Data(), i+1));
    }else{
      line99_2->Draw("same");
      c1->Print(pdf);
      c1->Print(Form("%s/SigmabyRatio%d.pdf",pdfDhire.Data(), i+1));
      ge[i]->SetMinimum(0.95);
      line99_2->Draw();
      ge[i]->Draw("AP");
      line99_2->Draw("same");
      c1->Print(pdf);
      c1->Print(Form("%s/SigmabyRatio%dzoom.pdf",pdfDhire.Data(), i+1));
    }
  }
  c1->Print(pdf+"]"); 

}
