int NumOfSegSAC = 4;

void saccheck(){
  TFile *file = new TFile("/home/had/suharu/work/e40/ana/rootfile/run04376Hodoscope.root","READ");

  TTree *tree = (TTree*)file->Get("tree");  
  double ADC[4]; 
  double TDC[4]; 
  tree->SetBranchAddress("saca",ADC); 
  tree->SetBranchAddress("sact",TDC); 

  TH1F *SAC_A[12]; 
  TH1F *SAC_T[4]; 
  for(int i=0; i<NumOfSegSAC; i++){
    SAC_A[i] = new TH1F(Form("SAC_A%d",i+1),Form("SAC_A%d",i+1),800,0,800) ; 
    SAC_A[i+4] = new TH1F(Form("SAC_A%dwTDC",i+1),Form("SAC_A%dwTDC",i+1),800,0,800) ; 
    SAC_A[i+8] = new TH1F(Form("SAC_A%dwoTDC",i+1),Form("SAC_A%dwoTDC",i+1),800,0,800) ; 
    SAC_T[i] = new TH1F(Form("SAC_T%d",i+1),Form("SAC_T%d",i+1),800,0,800) ; 
  }  
  int n = tree->GetEntries(); 
  for(int i=0; i<n; i++){
    tree->GetEntry(i);
    for(int j=0; j<NumOfSegSAC; j++){
      SAC_A[j]->Fill(ADC[j]);  
      SAC_T[j]->Fill(TDC[j]);  
      if( TDC[j]>0 ){
        SAC_A[j+4]->Fill(ADC[j]);     
      }else{  
        SAC_A[j+8]->Fill(ADC[j]);     
      }  
    }  
  }  

  TCanvas *c1 = new TCanvas("c1","c1",800,700); 
  TCanvas *c2 = new TCanvas("c2","c2",800,700); 
  TCanvas *c3 = new TCanvas("c3","c3",800,700); 
  c1->Divide(2,2); 
  c2->Divide(2,2); 
  c3->Divide(2,2); 
//  c1->SetLogy();  
//  c2->SetLogy();  
//  c3->SetLogy();  
  for(int i=0; i<NumOfSegSAC; i++){
    c1->cd(i+1)->SetLogy(); 
    SAC_A[i]->Draw();  
    SAC_A[i+4]->SetLineColor(2);  
    SAC_A[i+4]->Draw("same");  
    c2->cd(i+1)->SetLogy(); 
    SAC_T[i]->Draw();  
    c3->cd(i+1)->SetLogy(); 
    SAC_A[i+8]->Draw();  
  }  

}

