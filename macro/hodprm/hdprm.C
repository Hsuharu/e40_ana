void hdprm(int runnum, int n){
  gStyle->SetOptStat(1111110); 
  gStyle->SetOptFit(1); 
//  TFile *file = new TFile("/home/had/suharu/work/e40/ana/rootfile/Hod04300.root","READ");
//  TFile *file = new TFile("/home/had/suharu/work/e40/ana/rootfile/run04307_Hod.root","READ");
  TString anadir=Form("%s/work/e40/ana",std::getenv("HOME")); 
  TFile *file = new TFile(Form("%s/rootfile/run%05d_hodo.root", anadir.Data() , runnum),"READ");

  double l = 30;
  double l_t = 100;

  int BH1 = 1;
  int NumOfSegBH1 = 11; 
  int BH1_U_Max[NumOfSegBH1]; 
  int BH1_D_Max[NumOfSegBH1]; 
  double BH1_U_X[NumOfSegBH1]; 
  double BH1_D_X[NumOfSegBH1]; 
  double BH1_U_Mean[NumOfSegBH1]; 
  double BH1_D_Mean[NumOfSegBH1]; 
  double BH1_U_Sigma[NumOfSegBH1]; 
  double BH1_D_Sigma[NumOfSegBH1]; 

  int BH2 = 2;
  int NumOfSegBH2 = 8; 
  int BH2_U_Max[NumOfSegBH2]; 
  int BH2_D_Max[NumOfSegBH2]; 
  double BH2_U_X[NumOfSegBH2]; 
  double BH2_D_X[NumOfSegBH2]; 
  double BH2_U_Mean[NumOfSegBH2]; 
  double BH2_D_Mean[NumOfSegBH2]; 
  double BH2_U_Sigma[NumOfSegBH2]; 
  double BH2_D_Sigma[NumOfSegBH2]; 
  double BH2_U_Ave = 0.;
  double BH2_D_Ave = 0.;


  int TOF = 4;
  int NumOfSegTOF = 24; 
  int TOF_U_Max[NumOfSegTOF]; 
  int TOF_D_Max[NumOfSegTOF]; 
  double TOF_U_X[NumOfSegTOF]; 
  double TOF_D_X[NumOfSegTOF]; 
  double TOF_U_Mean[NumOfSegTOF]; 
  double TOF_D_Mean[NumOfSegTOF]; 
  double TOF_U_Sigma[NumOfSegTOF]; 
  double TOF_D_Sigma[NumOfSegTOF]; 


  int ADC_U = 3; 
  int ADC_D = 4;

  int TDC_U = 3; 
  int TDC_D = 4;

  TH1F *BH1_U[NumOfSegBH1]; 
  TH1F *BH1_D[NumOfSegBH1]; 
  TH1F *BH2_U[NumOfSegBH2]; 
  TH1F *BH2_D[NumOfSegBH2]; 
  TH1F *TOF_U[NumOfSegTOF]; 
  TH1F *TOF_D[NumOfSegTOF]; 

  TF1 *fit_U = new TF1("fit_U","gaus"); 
  TF1 *fit_D = new TF1("fit_D","gaus"); 

/////////////////////////////////////////////////////////////////////
//   BH1 U/D                                                       //
/////////////////////////////////////////////////////////////////////
  for(int i=0; i<NumOfSegBH1; i++){
    if(i<9){  
     BH1_U[i] = (TH1F*)file->Get(Form("h%d0%d0%d",BH1,i+1,ADC_U)) ; 
     BH1_D[i] = (TH1F*)file->Get(Form("h%d0%d0%d",BH1,i+1,ADC_D)) ; 
    }else{   
     BH1_U[i] = (TH1F*)file->Get(Form("h%d%d0%d",BH1,i+1,ADC_U))  ;
     BH1_D[i] = (TH1F*)file->Get(Form("h%d%d0%d",BH1,i+1,ADC_D))  ;
    }  
  }  
  
  TCanvas *c1 = new TCanvas("c1","BH1_U",800,800); 
  c1->Divide(4,3); 
  TCanvas *c2 = new TCanvas("c2","BH1_D",800,800); 
  c2->Divide(4,3); 

  for(int i=0; i<NumOfSegBH1; i++){
    c1->cd(i+1); 
    BH1_U_Max[i] = BH1_U[i]->GetMaximumBin();  
    BH1_U_X[i] = BH1_U[i]->GetXaxis()->GetBinCenter(BH1_U_Max[i]);  
    BH1_U[i]->Fit("fit_U","","", BH1_U_X[i]-l, BH1_U_X[i]+l);  
    BH1_U_Mean[i] = fit_U->GetParameter(1); 
    BH1_U_Sigma[i] = fit_U->GetParameter(2); 
    BH1_U[i]->Draw(); 
    BH1_U[i]->GetXaxis()->SetRangeUser(BH1_U_Mean[i]-20,BH1_U_Mean[i]+40);   
  
    c2->cd(i+1); 
    BH1_D_Max[i] = BH1_D[i]->GetMaximumBin();  
    BH1_D_X[i] = BH1_D[i]->GetXaxis()->GetBinCenter(BH1_D_Max[i]);  
    BH1_D[i]->Fit("fit_D","","", BH1_D_X[i]-l, BH1_D_X[i]+l);  
    BH1_D_Mean[i] = fit_D->GetParameter(1); 
    BH1_D_Sigma[i] = fit_D->GetParameter(2); 
    BH1_D[i]->Draw(); 
    BH1_D[i]->GetXaxis()->SetRangeUser(BH1_D_Mean[i]-20,BH1_D_Mean[i]+40);   
  }  

/////////////////////////////////////////////////////////////////////
//   BH2 U/D                                                       //
/////////////////////////////////////////////////////////////////////
  for(int i=0; i<NumOfSegBH2; i++){
    if(i<9){  
     BH2_U[i] =  (TH1F*)file->Get(Form("h%d0%d0%d",BH2,i+1,ADC_U)) ;
     BH2_D[i] =  (TH1F*)file->Get(Form("h%d0%d0%d",BH2,i+1,ADC_D)) ;
    }else{                                                        
     BH2_U[i] =  (TH1F*)file->Get(Form("h%d%d0%d",BH2,i+1,ADC_U))  ;
     BH2_D[i] =  (TH1F*)file->Get(Form("h%d%d0%d",BH2,i+1,ADC_D))  ;
    }  
  }  
  
  TCanvas *c3 = new TCanvas("c3","BH2_U",800,800); 
  c3->Divide(4,2); 
  TCanvas *c4 = new TCanvas("c4","BH2_D",800,800); 
  c4->Divide(4,2); 

  for(int i=0; i<NumOfSegBH2; i++){
    c3->cd(i+1); 
    BH2_U_Max[i] = BH2_U[i]->GetMaximumBin();  
    BH2_U_X[i] = BH2_U[i]->GetXaxis()->GetBinCenter(BH2_U_Max[i]);  
    BH2_U[i]->Fit("fit_U","","", BH2_U_X[i]-l, BH2_U_X[i]+l);  
    BH2_U_Mean[i] = fit_U->GetParameter(1); 
    BH2_U_Sigma[i] = fit_U->GetParameter(2); 
    BH2_U[i]->Draw(); 
    BH2_U[i]->GetXaxis()->SetRangeUser(BH2_U_Mean[i]-20,BH2_U_Mean[i]+40);   
    BH2_U_Ave += BH2_U_Mean[i]/NumOfSegBH2;

    c4->cd(i+1); 
    BH2_D_Max[i] = BH2_D[i]->GetMaximumBin();  
    BH2_D_X[i] = BH2_D[i]->GetXaxis()->GetBinCenter(BH2_D_Max[i]);  
    BH2_D[i]->Fit("fit_D","","", BH2_D_X[i]-l, BH2_D_X[i]+l);  
    BH2_D_Mean[i] = fit_D->GetParameter(1); 
    BH2_D_Sigma[i] = fit_D->GetParameter(2); 
    BH2_D[i]->Draw(); 
    BH2_D[i]->GetXaxis()->SetRangeUser(BH2_D_Mean[i]-20,BH2_D_Mean[i]+40);   
    BH2_D_Ave += BH2_D_Mean[i]/NumOfSegBH2;
    if(n!=1) continue; 
    BH2_D[i]->GetXaxis()->SetRangeUser(BH2_D_Mean[i]-10,BH2_D_Mean[i]+20);   
  }  
  
///////////////////////////////////////////////////////////////////////
////   TOF U/D                                                       //
///////////////////////////////////////////////////////////////////////
//  for(int i=0; i<NumOfSegTOF; i++){
//    if(i<9){  
//     TOF_U[i] =  (TH1F*)file->Get(Form("h%d0%d0%d",TOF,i+1,TDC_U)) ;
//     TOF_D[i] =  (TH1F*)file->Get(Form("h%d0%d0%d",TOF,i+1,TDC_D)) ;
//    }else{                                                        
//     TOF_U[i] =  (TH1F*)file->Get(Form("h%d%d0%d",TOF,i+1,TDC_U))  ;
//     TOF_D[i] =  (TH1F*)file->Get(Form("h%d%d0%d",TOF,i+1,TDC_D))  ;
//    }  
//  }  
//
//  TCanvas *c5 = new TCanvas("c5","TOF_U",800,800); 
//  c5->Divide(6,4); 
//  TCanvas *c6 = new TCanvas("c6","TOF_D",800,800); 
//  c6->Divide(6,4); 
//
//  for(int i=0; i<NumOfSegTOF; i++){
//    c5->cd(i+1); 
//    TOF_U_Max[i] = TOF_U[i]->GetMaximumBin();  
//    TOF_U_X[i] = TOF_U[i]->GetXaxis()->GetBinCenter(TOF_U_Max[i]);  
//    TOF_U[i]->Fit("fit_U","","", TOF_U_X[i]-l_t, TOF_U_X[i]+l_t);  
//    TOF_U_Mean[i] = fit_U->GetParameter(1); 
//    TOF_U_Sigma[i] = fit_U->GetParameter(2); 
//    TOF_U[i]->Draw(); 
//    c6->cd(i+1); 
//    TOF_D_Max[i] = TOF_D[i]->GetMaximumBin();  
//    TOF_D_X[i] = TOF_D[i]->GetXaxis()->GetBinCenter(TOF_D_Max[i]);  
//    TOF_D[i]->Fit("fit_D","","", TOF_D_X[i]-l_t, TOF_D_X[i]+l_t);  
//    TOF_D_Mean[i] = fit_D->GetParameter(1); 
//    TOF_D_Sigma[i] = fit_D->GetParameter(2); 
//    TOF_D[i]->Draw(); 
//  }  
  
  TString fout1 = (Form( "%s/hp_dat/HDPRAM_BH1_U_ADC_%05d.dat", anadir.Data() ,runnum));  
  TString fout2 = (Form( "%s/hp_dat/HDPRAM_BH1_D_ADC_%05d.dat", anadir.Data() ,runnum));  
  std::ofstream fout_1(fout1.Data()); 
  std::ofstream fout_2(fout2.Data()); 
  for(int i=0; i<NumOfSegBH1; i++){
     fout_1 << BH1_U_Mean[i] << endl; 
     fout_2 << BH1_D_Mean[i] << endl; 
  }     

  TString fout3 = (Form( "%s/hp_dat/HDPRAM_BH2_U_ADC_%05d.dat", anadir.Data() ,runnum));  
  TString fout4 = (Form( "%s/hp_dat/HDPRAM_BH2_D_ADC_%05d.dat", anadir.Data() ,runnum));  
  std::ofstream fout_3(fout3.Data()); 
  std::ofstream fout_4(fout4.Data()); 
  for(int i=0; i<NumOfSegBH2; i++){
     fout_3 << BH2_U_Mean[i] << endl; 
     fout_4 << BH2_D_Mean[i] << endl; 
  }     

//  TString fout5 = ("./dat/HDPRAM_TOF_U_TDC.dat");  
//  TString fout6 = ("./dat/HDPRAM_TOF_D_TDC.dat");  
//  ofstream fout_5(fout5.Data()); 
//  ofstream fout_6(fout6.Data()); 
//  for(int i=0; i<NumOfSegTOF; i++){
//     fout_5 << TOF_U_Mean[i] << endl; 
//     fout_6 << TOF_D_Mean[i] << endl; 
//  }     

//  TString fout7 = ("./dat/HDPRAM_BH2_Ave_TDC.dat");  
//  ofstream fout_7(fout7.Data()); 
//     fout_7 << BH2_U_Ave << endl; 
//     fout_7 << BH2_D_Ave << endl; 

}

