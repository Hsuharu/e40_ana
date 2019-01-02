void m2_p_plot(){
  gROOT->Reset();

  TCanvas *c1 = new TCanvas("c1", "c1", 800, 700);
  c1->SetGrid();
  c1->SetGridx();
  c1->SetGridy();

  TLegend *Leg1 = new TLegend(0.78,0.775,0.98,0.935);
  TLegend *Leg2 = new TLegend(0.78,0.775,0.98,0.935);

  int n = 100;
  double x[n], y1[n], y2[n], y3[n], y4[n], y5[n], y6[n];
  double SAC_index = 1.1;
  double LC_index = 1.49;
  double LAC_index = 1.05;

  for (int i=0; i<n; i++) {
    x[i] = (i+1) * 0.014;
    y1[i] = x[i]/sqrt(-1+SAC_index*SAC_index);
    y2[i] = x[i]/sqrt(-1+LC_index*LC_index  );
    y3[i] = x[i]/sqrt(-1+LAC_index*LAC_index);
    y4[i] = x[i]/sqrt(-1+SAC_index*SAC_index);
    y5[i] = x[i]/sqrt(-1+LC_index*LC_index  );
    y6[i] = x[i]/sqrt(-1+LAC_index*LAC_index);
  }

  TGraph *g1 = new TGraph(n, x, y1);
  TGraph *g2 = new TGraph(n, x, y2);
  TGraph *g3 = new TGraph(n, x, y3);
  TGraph *g4 = new TGraph(n, x, y4);
  TGraph *g5 = new TGraph(n, x, y5);
  TGraph *g6 = new TGraph(n, x, y6);
  

  g1->SetLineStyle(9);
  g2->SetLineStyle(10);
  g3->SetLineStyle(5);
//  g4->SetLineStyle(9);

  g1->GetXaxis()->SetRangeUser(0,1.4);
  g2->GetXaxis()->SetRangeUser(0,1.4);
  g3->GetXaxis()->SetRangeUser(0,1.4);
  g4->GetXaxis()->SetRangeUser(0,1.4);
  g5->GetXaxis()->SetRangeUser(0,1.4);
  g6->GetXaxis()->SetRangeUser(0,1.4);

  g1->GetYaxis()->SetRangeUser(0,1.6);
  g2->GetYaxis()->SetRangeUser(0,1.6);
  g3->GetYaxis()->SetRangeUser(0,1.6);
  g4->GetYaxis()->SetRangeUser(0,1.6);
  g5->GetYaxis()->SetRangeUser(0,1.6);
  g6->GetYaxis()->SetRangeUser(0,1.6);

  g1->SetLineWidth(4);
  g2->SetLineWidth(4);
  g3->SetLineWidth(4);
  g4->SetLineWidth(4);
  g5->SetLineWidth(4);
  g6->SetLineWidth(4);

  g1->SetTitle("Title;m2;momentum[GeV/c]");
  g4->SetTitle("Title;m[GeV/cc];momentum[GeV/c]");

  gStyle->SetOptTitle(0);
  g1->SetFillStyle(0);
  g2->SetFillStyle(0);
  g3->SetFillStyle(0);

  g1->Draw();
  g2->Draw("same");
  g3->Draw("same");

  Leg1->AddEntry(g1,"SAC index 1.1","l");
  Leg1->AddEntry(g2,"LC index 1.49","l");
  Leg1->AddEntry(g3,"LAC index 1.05","l");
  Leg1->Draw();

  c1->Print("./m2_p_plot.pdf");

  g4->Draw();
  g5->Draw("same");
  g6->Draw("same");

  Leg2->AddEntry(g4,"SAC index 1.1","l");
  Leg2->AddEntry(g5,"LC index 1.49","l");
  Leg2->AddEntry(g6,"LAC index 1.05","l");
  Leg2->Draw();


  c1->Print("./m_p_plot.pdf");

}
