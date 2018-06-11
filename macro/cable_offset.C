void cable_offset(int runnum, 1){
  gStyle->SetOptStat(1111110); 
  gStyle->SetOptFit(1); 
  gErrorIgnoreLevel=kWarning;
// TFile *f = TFile::Open("../rootfile/Hod04462.root");
// TFile *f = TFile::Open("../rootfile/Hod04464.root");
// TFile *f = TFile::Open("/home/had/suharu/work/e40/ana/rootfile/run04462_hodo.root");
 TString anadir=Form("%s/work/e40/ana",std::getenv("HOME")); 
 TFile *f = new TFile(Form("%s/analyzer_%3s/rootfile/run%05d_hodo.root", anadir.Data() ,month, runnum),"READ");
 TTree *t = (TTree*)f->Get("tree"); 
 
 TCanvas *c1 = new TCanvas;
 c1->Divide(4,2); 


 TString fpdf = Form("%s/pdf/trigger_study/cable_offset_%05d.pdf", anadir.Data(),runnum);
 c1->Print(fpdf+"["); 

 for(int i=0;i<8;i++){
    TF1 tf("tf","gaus"); 
    c1->cd(i+1);
    TH1F *h = new TH1F(Form("h%d",i+1),Form("h%d",i+1),80,-4,4 ); 
//    t->Project(Form("h%d",i+1),Form("bh1mt[5]+bh2mt[%d]",i),Form("bh1mt[5]>0&&bh2nhits==1",i));
    t->Project(Form("h%d",i+1),Form("bh1mt[5]-bh2mt[%d]",i),"bh1mt[5]>0");
    h->Fit("tf","Q"); 
    double mean = tf.GetParameter(1); 
    double err_mean = tf.GetParError(1); 
    double sigma = tf.GetParameter(2); 
    double err_sigma = tf.GetParError(2); 
    h->GetXaxis()->SetRangeUser(mean-1,mean+2);   
    std::cout << "Mean = "<< mean << " \t " << "Mean Error = "<< err_mean << " \t " << "Sigma = "<< sigma << " \t " << "Sigma Error = "<< err_sigma <<  std::endl;
 }
 c1->Print(fpdf);  
 c1->Print(fpdf+"]"); 

}  
