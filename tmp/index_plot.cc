void index_plot(){
  gROOT->Reset();

  TCanvas *c1 = new TCanvas("c1", "c1", 800, 700);
  c1->SetGrid();
  c1->SetGridx();
  c1->SetGridy();

  TLegend *Leg1 = new TLegend(0.78,0.775,0.98,0.935);

  int n = 100;
  double x[n], y1[n], y2[n], y3[n], y4[n], y5[n], y6[n];

  for (int i=0; i<n; i++) {
    x[i] = (i+1) * 0.02;
//    y[i] = 10 * sin(x[i] + 0.2);
    y1[i] = sqrt(1+(0.138/x[i])*(0.138/x[i]));
    y2[i] = sqrt(1+(0.500/x[i])*(0.500/x[i]));
    y3[i] = sqrt(1+(0.940/x[i])*(0.940/x[i]));
    y4[i] = 1.1;
    y5[i] = 1.49;
    y6[i] = 1.05;
  }

  TGraph *g1 = new TGraph(n, x, y1);
  TGraph *g2 = new TGraph(n, x, y2);
  TGraph *g3 = new TGraph(n, x, y3);
  TGraph *g4 = new TGraph(n, x, y4);
  TGraph *g5 = new TGraph(n, x, y5);
  TGraph *g6 = new TGraph(n, x, y6);
  

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

  gStyle->SetOptTitle(0);

  g4->Draw();
  g1->Draw("same");
  g2->Draw("same");
  g3->Draw("same");
  g5->Draw("same");
  g6->Draw("same");

  Leg1->AddEntry(g1,"Pion"     ,"l");
  Leg1->AddEntry(g2,"Kaon"     ,"l");
  Leg1->AddEntry(g3,"Proton"   ,"l");
  Leg1->AddEntry(g4,"SAC index 1.1","l");
  Leg1->AddEntry(g5,"LC index 1.49","l");
  Leg1->AddEntry(g6,"LAC index 1.05","l");
  Leg1->Draw();

  c1->Print("./index_plot.pdf");

}
