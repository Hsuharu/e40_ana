int NumOfSegBH2  = 8;
int NumOfSegTOF  = 24;
int NumOfBin = 2000;

void tofde(){
  TFile *file = new TFile("/home/had/suharu/work/e40/ana/rootfile/run04376Hodoscope.root","READ");

  TTree *tree = (TTree*)file->Get("tree");  
  double BH2_U_ADC[NumOfSegBH2]; 
  double BH2_D_ADC[NumOfSegBH2]; 
  double BH2_U_TDC[NumOfSegBH2]; 
  double BH2_D_TDC[NumOfSegBH2]; 
  double BH2_MeanTime[NumOfSegBH2]; 
  tree->SetBranchAddress("bh2ua",BH2_U_ADC); 
  tree->SetBranchAddress("bh2da",BH2_D_ADC); 
  tree->SetBranchAddress("bh2ut",BH2_U_TDC); 
  tree->SetBranchAddress("bh2dt",BH2_D_TDC); 

  double TOF_U_ADC[NumOfSegTOF]; 
  double TOF_D_ADC[NumOfSegTOF]; 
  double TOF_U_TDC[NumOfSegTOF]; 
  double TOF_D_TDC[NumOfSegTOF]; 
  double TOF_ADC[NumOfSegTOF]; 
  double TOF_MeanTime[NumOfSegBH2]; 
  tree->SetBranchAddress("tofua",TOF_U_ADC); 
  tree->SetBranchAddress("tofda",TOF_D_ADC); 
  tree->SetBranchAddress("tofut",TOF_U_TDC); 
  tree->SetBranchAddress("tofdt",TOF_D_TDC); 

  TH1F *BH2_UA[NumOfSegBH2]; 
  TH1F *BH2_UT[NumOfSegBH2]; 
  TH1F *BH2_DA[NumOfSegBH2]; 
  TH1F *BH2_DT[NumOfSegBH2]; 
  TH1F *BH2_MT[NumOfSegBH2]; 

  TH1F *TOF_UA[NumOfSegTOF]; 
  TH1F *TOF_UT[NumOfSegTOF]; 
  TH1F *TOF_DA[NumOfSegTOF]; 
  TH1F *TOF_DT[NumOfSegTOF]; 
  TH1F *TOF_MT[NumOfSegTOF]; 
  TH2D *TOFdE[NumOfSegTOF]; 

  TH1F *TOF = new TH1F(Form("TOF%d",1),Form("TOF%d",1),1000,-5000,4999) ; ; 

  for(int i=0; i<NumOfSegBH2; i++){
    BH2_UA[i] = new TH1F(Form("BH2_UA%d",i+1),Form("BH2_UA%d",i+1),NumOfBin,0,NumOfBin) ; 
    BH2_UT[i] = new TH1F(Form("BH2_UT%d",i+1),Form("BH2_UT%d",i+1),NumOfBin,0,NumOfBin) ; 
    BH2_DA[i] = new TH1F(Form("BH2_DA%d",i+1),Form("BH2_DA%d",i+1),NumOfBin,0,NumOfBin) ; 
    BH2_DT[i] = new TH1F(Form("BH2_DT%d",i+1),Form("BH2_DT%d",i+1),NumOfBin,0,NumOfBin) ; 
    BH2_MT[i] = new TH1F(Form("BH2_MT%d",i+1),Form("BH2_MT%d",i+1),NumOfBin,0,NumOfBin) ; 
  }  

  for(int i=0; i<NumOfSegTOF; i++){
    TOF_UA[i] = new TH1F(Form("TOF_UA%d",i+1),Form("TOF_UA%d",i+1),NumOfBin,0,NumOfBin) ; 
    TOF_UT[i] = new TH1F(Form("TOF_UT%d",i+1),Form("TOF_UT%d",i+1),NumOfBin,0,NumOfBin) ; 
    TOF_DA[i] = new TH1F(Form("TOF_DA%d",i+1),Form("TOF_DA%d",i+1),NumOfBin,0,NumOfBin) ; 
    TOF_DT[i] = new TH1F(Form("TOF_DT%d",i+1),Form("TOF_DT%d",i+1),NumOfBin,0,NumOfBin) ; 
    TOF_MT[i] = new TH1F(Form("TOF_MT%d",i+1),Form("TOF_MT%d",i+1),NumOfBin,0,NumOfBin) ; 
    TOFdE[i]  = new TH2D(Form("TOFdE%d",i),Form("TOFdE%d",i),2000,0,2000, 2000, 0, 2000) ; ; 
  }  

  int n = tree->GetEntries(); 
  for(int i=0; i<n; i++){
    tree->GetEntry(i);
    for(int j=0; j<NumOfSegBH2; j++){
      BH2_UA[j]->Fill(BH2_U_ADC[j]);  
      BH2_UT[j]->Fill(BH2_U_TDC[j]);  
      BH2_DA[j]->Fill(BH2_D_ADC[j]);  
      BH2_DT[j]->Fill(BH2_D_TDC[j]);  
      BH2_MeanTime[j] =  (BH2_U_TDC[j] + BH2_D_TDC[j])/2. ;  
      BH2_MT[j]->Fill(BH2_MeanTime[j]);  
    }  

    for(int j=0; j<NumOfSegTOF; j++){
      TOF_UA[j]->Fill(TOF_U_ADC[j]);  
      TOF_UT[j]->Fill(TOF_U_TDC[j]);  
      TOF_DA[j]->Fill(TOF_D_ADC[j]);  
      TOF_DT[j]->Fill(TOF_D_TDC[j]);  
      TOF_MeanTime[j] =  (TOF_U_TDC[j] + TOF_D_TDC[j])/2. ;  
      TOF_ADC[j] =  (TOF_U_ADC[j] + TOF_D_ADC[j])/2. ;  
      TOF_MT[j]->Fill(TOF_MeanTime[j]);  
      TOFdE[j]->Fill(TOF_MeanTime[j], TOF_ADC[j]);  
    }  
  }  

  TCanvas *c1 = new TCanvas("c1","c1",800,700); 
    TOF_MT[9]->Draw(); 
  TCanvas *c2 = new TCanvas("c2","c2",800,700); 
    TOFdE[9]->Draw(); 
}

