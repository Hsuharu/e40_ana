#include "DetectorID.hh"

void Index_plot(){
  //////////////////////////////////////////////////////////
  //   This file has been automatically generated 
  //     (Mon Dec 31 18:42:47 2018 by ROOT version6.10/08)
  //   from TTree khodo_lc/tree of DstKuramaHodoscope_LC
  //   found on file: rootfile/run05126_DstKuramaHodoscope_LC.root
  //////////////////////////////////////////////////////////


  gStyle->SetOptTitle(0);
  gStyle->SetLabelSize(0.04,"XYZ");
  gStyle->SetTitleSize(0.05,"XYZ");
  gStyle->SetTitleOffset(1.2,"X");
  gStyle->SetTitleOffset(1.3,"Y");
  gStyle->SetPadLeftMargin(0.16);
  gStyle->SetPadBottomMargin(0.16);

  gROOT->Reset();
  TString anadir=Form("%s/work/e40/ana",std::getenv("HOME")); 
  TString pdf = Form("%s/pdf/trigger/index_plot.pdf", anadir.Data());
  TString pdfDhire = Form("%s/pdf/trigger", anadir.Data());

  //-Legend def --------------------------------------------------------------------------------------
  TLegend *Leg1 = new TLegend(0.78,0.775,0.98,0.935);
  TLegend *Leg2 = new TLegend(0.78,0.775,0.98,0.935);
  TLegend *Leg3 = new TLegend(0.68,0.675,0.98,0.935);
  TLegend *Leg4 = new TLegend(0.78,0.775,0.98,0.935);
  TLegend *Leg5 = new TLegend(0.78,0.775,0.98,0.935);
  TLegend *Leg6 = new TLegend(0.78,0.775,0.98,0.935);
  TLegend *Leg7 = new TLegend(0.78,0.775,0.98,0.935);


 TCanvas *c1 = new TCanvas("c1","c1",1200,900);
  c1->Print(pdf+"["); 
// index fanction -----------------------------------------------------------------------------------
  int n = 100;
  double x1[n], y1[n], y2[n], y3[n], y4[n], y5[n], y6[n];

  for (int i=0; i<n; i++) {
    x1[i] = (i+1) * 0.02;
//    y[i] = 10 * sin(x[i] + 0.2);
    y1[i] = sqrt(1+(0.138/x1[i])*(0.138/x1[i]));
    y2[i] = sqrt(1+(0.500/x1[i])*(0.500/x1[i]));
    y3[i] = sqrt(1+(0.940/x1[i])*(0.940/x1[i]));
    y4[i] = 1.1;
    y5[i] = 1.49;
    y6[i] = 1.05;
  }

  TGraph *g1 = new TGraph(n, x1, y1);
  TGraph *g2 = new TGraph(n, x1, y2);
  TGraph *g3 = new TGraph(n, x1, y3);
  TGraph *g4 = new TGraph(n, x1, y4);
  TGraph *g5 = new TGraph(n, x1, y5);
  TGraph *g6 = new TGraph(n, x1, y6);
  

  g1->SetLineColor(2);
  g2->SetLineColor(4);
  g3->SetLineColor(3);
  g4->SetLineStyle(9);
  g5->SetLineStyle(10);
  g6->SetLineStyle(5);

  g1->GetXaxis()->SetRangeUser(0,2);
  g2->GetXaxis()->SetRangeUser(0,2);
  g3->GetXaxis()->SetRangeUser(0,2);
  g4->GetXaxis()->SetRangeUser(0,2);
  g5->GetXaxis()->SetRangeUser(0,2);
  g6->GetXaxis()->SetRangeUser(0,2);

  g1->GetYaxis()->SetRangeUser(0.98,1.6);
  g2->GetYaxis()->SetRangeUser(0.98,1.6);
  g3->GetYaxis()->SetRangeUser(0.98,1.6);
  g4->GetYaxis()->SetRangeUser(0.98,1.6);
  g5->GetYaxis()->SetRangeUser(0.98,1.6);
  g6->GetYaxis()->SetRangeUser(0.98,1.6);

  g1->SetLineWidth(4);
  g2->SetLineWidth(4);
  g3->SetLineWidth(4);
  g4->SetLineWidth(3);
  g5->SetLineWidth(3);
  g6->SetLineWidth(3);

  g4->SetTitle("Title;momentum[GeV/c];index");

//  gStyle->SetOptTitle(0);

  g4->Draw("al");
  g1->Draw("same");
  g2->Draw("same");
  g3->Draw("same");
  g5->Draw("same");
  g6->Draw("same");

  Leg3->AddEntry(g1,"Pion"     ,"l");
  Leg3->AddEntry(g2,"Kaon"     ,"l");
  Leg3->AddEntry(g3,"Proton"   ,"l");
  Leg3->AddEntry(g4,"SAC index 1.1","l");
  Leg3->AddEntry(g5,"LC index 1.49","l");
  Leg3->AddEntry(g6,"LAC index 1.05","l");
  Leg3->Draw();

//  c1->Print(Form("%s/pdf/trigger/index_plot_run%05d.pdf",anadir.Data(),runnum));
  c1->Print(pdf);


  c1->Print(pdf+"]"); 

}
