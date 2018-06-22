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

void CountEff_graph( int month,int det,int runnum1,int runnum2,int runnum3,int runnum4){
  TString prmdir1=Form("%s/work/e40/ana/pdf/CountEff",std::getenv("HOME")); 
  TString prmdir2=Form("%s/work/e40/ana/hp_dat",std::getenv("HOME")); 

  TString filein1=Form("%s/CountEff_BH%d_%05d.dat",prmdir2.Data(),det,runnum1); 
  TString filein2=Form("%s/CountEff_BH%d_%05d.dat",prmdir2.Data(),det,runnum2); 
  TString filein3=Form("%s/CountEff_BH%d_%05d.dat",prmdir2.Data(),det,runnum3); 
  TString filein4=Form("%s/CountEff_BH%d_%05d.dat",prmdir2.Data(),det,runnum4); 

  std::ifstream fin1(filein1);
  std::ifstream fin2(filein2);
  std::ifstream fin3(filein3);
  std::ifstream fin4(filein4);

  std::vector< std::vector<double> > BH2_Eff_5M; 
  std::vector< std::vector<double> > BH2_Eff_10M; 
  std::vector< std::vector<double> > BH2_Eff_15M; 
  std::vector< std::vector<double> > BH2_Eff_20M; 

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
      BH2_Eff_5M.push_back(inner);
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
      BH2_Eff_10M.push_back(inner);
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
      BH2_Eff_15M.push_back(inner);
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
      BH2_Eff_20M.push_back(inner);
    }
  }
  
  int number = 4;//Number of M/spill data
  double M_par_Spill[] = {5,10,15,20};
  double efficiency[2][4];
  for(int i=0; i<number; i++){
    for(int j=0; j<2; j++){
       efficiency[j][0] = BH2_Eff_5M[ NumOfSegBH2][j*3+2];
       efficiency[j][1] = BH2_Eff_10M[NumOfSegBH2][j*3+2];
       efficiency[j][2] = BH2_Eff_15M[NumOfSegBH2][j*3+2];
       efficiency[j][3] = BH2_Eff_20M[NumOfSegBH2][j*3+2];
    }
  }
  
// TGraph---------------------------------------------------------------------
  TGraph *graph[2];
  graph[0] = new TGraph(number,&(M_par_Spill[0]),&(efficiency[0][0]));
  graph[1] = new TGraph(number,&(M_par_Spill[0]),&(efficiency[1][0]));

// TCanvas--------------------------------------------------------------------
  TCanvas *c1 = new TCanvas("c1","c1",800,700);
//        c1->DrawFrame(0,0.8,22,1,"Efficiency");

// Frame ---------------------------------------------------------------------
  TH1 *frame1=gPad->DrawFrame(0,0.95,22,1.01,Form("BH%d Efficiency",det));      
  gPad->SetGrid();
  frame1->GetXaxis()->SetTitle("[ M/Spill ]");
  frame1->GetYaxis()->SetTitleOffset(1.2);
  frame1->GetYaxis()->SetTitle("Efficiency");

// Legend --------------------------------------------------------------------
  TLegend *legend = new TLegend(0.8,0.8,0.9,0.9);

  frame1->Draw();
  for(int i=0 ; i<2; i++){
    graph[i]->SetMarkerStyle(21);
    graph[i]->SetLineStyle(2);
    graph[i]->SetMarkerColor(i+4);
    graph[i]->SetLineColor(i+4);
    legend->AddEntry(graph[i],Form("BH%d_%s",det,ud[i]),"p");
    legend->Draw();
    graph[i]->Draw("p");
  }


  c1->Print(Form("%s/CountEff_BH%d_Eff.pdf",prmdir1.Data(),det));
  
}
