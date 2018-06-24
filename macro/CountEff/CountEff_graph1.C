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

const char* ud[] =
{
  "U",
  "D",
};

void CountEff_graph1( int month,int det,int gatenum,int runnum1,int runnum2,int runnum3,int runnum4){
  TString prmdir1=Form("%s/work/e40/ana/pdf/CountEff",std::getenv("HOME")); 
  TString prmdir2=Form("%s/work/e40/ana/hp_dat",std::getenv("HOME")); 

  TString filein1=Form("%s/CountEff_BH%d_Gate_%05d.dat",prmdir2.Data(),det,runnum1); 
  TString filein2=Form("%s/CountEff_BH%d_Gate_%05d.dat",prmdir2.Data(),det,runnum2); 
  TString filein3=Form("%s/CountEff_BH%d_Gate_%05d.dat",prmdir2.Data(),det,runnum3); 
  TString filein4=Form("%s/CountEff_BH%d_Gate_%05d.dat",prmdir2.Data(),det,runnum4); 

  std::ifstream fin1(filein1);
  std::ifstream fin2(filein2);
  std::ifstream fin3(filein3);
  std::ifstream fin4(filein4);

  std::vector< std::vector<double> > Det_Eff_5M; 
  std::vector< std::vector<double> > Det_Eff_10M; 
  std::vector< std::vector<double> > Det_Eff_15M; 
  std::vector< std::vector<double> > Det_Eff_20M; 

  std::string line;
  
  if(fin1.fail() || fin2.fail() || fin3.fail() || fin4.fail()){
    std::cerr << "no file" << std::endl;
    exit(0); 
  }  

  while(std::getline(fin1, line)){
    double ucount=-1,uevent=-1,dcount=-1,devent=-1;
    double ueff=-1, deff=-1;
    std::istringstream input_line( line );
    std::vector<double> inner;
    if( input_line >> ucount >> uevent >> ueff >> dcount >> devent >> deff){
      inner.push_back(ucount);
      inner.push_back(uevent);
      inner.push_back(ueff  );
      inner.push_back(dcount);
      inner.push_back(devent);
      inner.push_back(deff  );
      Det_Eff_5M.push_back(inner);
    }
  }

  while(std::getline(fin2, line)){
    double ucount=-1,uevent=-1,dcount=-1,devent=-1;
    double ueff=-1, deff=-1;
    std::istringstream input_line( line );
    std::vector<double> inner;
    if( input_line >> ucount >> uevent >> ueff >> dcount >> devent >> deff){
      inner.push_back(ucount);
      inner.push_back(uevent);
      inner.push_back(ueff  );
      inner.push_back(dcount);
      inner.push_back(devent);
      inner.push_back(deff  );
      Det_Eff_10M.push_back(inner);
    }
  }

  while(std::getline(fin3, line)){
    double ucount=-1,uevent=-1,dcount=-1,devent=-1;
    double ueff=-1, deff=-1;
    std::istringstream input_line( line );
    std::vector<double> inner;
    if( input_line >> ucount >> uevent >> ueff >> dcount >> devent >> deff){
      inner.push_back(ucount);
      inner.push_back(uevent);
      inner.push_back(ueff  );
      inner.push_back(dcount);
      inner.push_back(devent);
      inner.push_back(deff  );
      Det_Eff_15M.push_back(inner);
    }
  }

  while(std::getline(fin4, line)){
    double ucount=-1,uevent=-1,dcount=-1,devent=-1;
    double ueff=-1, deff=-1;
    std::istringstream input_line( line );
    std::vector<double> inner;
    if( input_line >> ucount >> uevent >> ueff >> dcount >> devent >> deff){
      inner.push_back(ucount);
      inner.push_back(uevent);
      inner.push_back(ueff  );
      inner.push_back(dcount);
      inner.push_back(devent);
      inner.push_back(deff  );
      Det_Eff_20M.push_back(inner);
    }
  }
  
  int number = 4;//Number of M/spill data
//  int gatenum = 10;
  double M_par_Spill[] = {5,10,15,20};
  double efficiency[20][4];
  int style[] = {3,2,27,4,5,20,21,22,23,25};
  for(int i=0; i<gatenum; i++){
    for(int j=0; j<2; j++){
       efficiency[10*j+i][0] = Det_Eff_5M[ i][j*3+2];
       efficiency[10*j+i][1] = Det_Eff_10M[i][j*3+2];
       efficiency[10*j+i][2] = Det_Eff_15M[i][j*3+2];
       efficiency[10*j+i][3] = Det_Eff_20M[i][j*3+2];
    }
  }
  
// TGraph---------------------------------------------------------------------
  TGraph *graph[20];
  for(int i=0; i<gatenum; i++){
    graph[i] = new TGraph(number,&(M_par_Spill[0]),&(efficiency[i][0]));
    graph[10+i] = new TGraph(number,&(M_par_Spill[0]),&(efficiency[10+i][0]));
  }
  
// TCanvas--------------------------------------------------------------------
  TCanvas *c1 = new TCanvas("c1","c1",800,700);
  TString pdf = Form("%s/CountEff_BH%d_Gate_Eff.pdf",prmdir1.Data(),det);
  c1->Print(pdf+"["); 

// Frame ---------------------------------------------------------------------
  TH1 *frame1=gPad->DrawFrame(0,0.7,24,1.06,Form("BH%d_%s Efficiency",det,ud[0]));      
  TH1 *frame2=gPad->DrawFrame(0,0.7,24,1.06,Form("BH%d_%s Efficiency",det,ud[1]));      
  gPad->SetGrid();
  frame1->GetXaxis()->SetTitle("[ M/Spill ]");
  frame1->GetYaxis()->SetTitleOffset(1.2);
  frame1->GetYaxis()->SetTitle("Efficiency");
  frame2->GetXaxis()->SetTitle("[ M/Spill ]");
  frame2->GetYaxis()->SetTitleOffset(1.2);
  frame2->GetYaxis()->SetTitle("Efficiency");

// Legend --------------------------------------------------------------------
  TLegend *legend  = new TLegend(0.8,0.6,0.9,0.9);
  TLegend *legend2 = new TLegend(0.8,0.6,0.9,0.9);

  frame1->Draw();
  for(int i=0 ; i<gatenum; i++){
    graph[i]->SetMarkerStyle(i+20);
    graph[i]->SetLineStyle(i);
    graph[i]->SetMarkerColor(i+1);
    graph[i]->SetLineColor(i+1);
      if(i==9){
              graph[i]->SetMarkerColor(12);
              graph[i]->SetLineColor(12);
      }
    legend->AddEntry(graph[i],Form("Gate:%dns", i+1),"p");
    legend->Draw();
    graph[i]->Draw("p");
  }


  c1 ->Print(pdf); 
  


  frame2->Draw();
  for(int i=0 ; i<gatenum; i++){
//    graph[10+i]->SetMarkerStyle(21);
//    graph[10+i]->SetLineStyle(2);
    graph[10+i]->SetMarkerStyle(i+20);
    graph[10+i]->SetLineStyle(i+1);
    graph[10+i]->SetMarkerColor(i+1);
    graph[10+i]->SetLineColor(i+1);
      if(i==9){
              graph[10+i]->SetMarkerColor(12);
              graph[10+i]->SetLineColor(12);
      }
    legend2->AddEntry(graph[10+i],Form("Gate:%dns",i+1),"p");
    legend2->Draw();
    graph[10+i]->Draw("p");
  }


  c1 ->Print(pdf); 
  c1->Print(pdf+"]");        
  
}
