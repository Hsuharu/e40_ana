void mean(){

  NumOfSegBH1
  NumOfSegBH2
  NumOfSegTOF

  TFile *Tf = new TFile("/home/had/suharu/work/e40/ana/rootfile/Hod4307.root");  
  TTree *tree = (TTree*)Tf->Get("tree");  

  int BH1UT[NumOfSegBH1]; 
  int BH2UT[NumOfSegBH2]; 
  int TOFUT[NumOfSegTOF]; 
  int BH1DT[NumOfSegBH1]; 
  int BH2DT[NumOfSegBH2]; 
  int TOFDT[NumOfSegTOF]; 

  tree->SetBranchAdress("bh1ut",BH1UT);  
  tree->SetBranchAdress("bh2ut",BH2UT);  
  tree->SetBranchAdress("bh2ut",TOFUT);  
  tree->SetBranchAdress("bh1dt",BH1DT);  
  tree->SetBranchAdress("bh2dt",BH2DT);  
  tree->SetBranchAdress("bh2dt",TOFDT);  

  int BH1MT[NumOfSegBH1]; 
  int BH2MT[NumOfSegBH2]; 
  int TOFMT[NumOfSegTOF]; 

  tree->SetBranchAdress("bh1mt",BH1MT);  
  tree->SetBranchAdress("bh2mt",BH2MT);  
  tree->SetBranchAdress("bh2mt",TOFMT);  
}  
