void corr_U(int runnum){
  gStyle->SetOptStat(1111110); 
  gStyle->SetOptFit(1); 
  gErrorIgnoreLevel=kWarning;
// TFile *f = TFile::Open("../rootfile/Hod04462.root");
// TFile *f = TFile::Open("../rootfile/Hod04464.root");
// TFile *f = TFile::Open("/home/had/suharu/work/e40/ana/rootfile/run04462_hodo.root");
 TString anadir=Form("%s/work/e40/ana",std::getenv("HOME")); 
 TFile *f = new TFile(Form("%s/rootfile/run%05d_hodo.root", anadir.Data() , runnum),"READ");
 TTree *t = (TTree*)f->Get("tree"); 
 
 TCanvas *c1 = new TCanvas;
 c1->Divide(4,2); 
 TCanvas *c2[8];


 TString fpdf = Form("%s/pdf/trigger_study/cbtof_%05d.pdf", anadir.Data(),runnum);
 c1->Print(fpdf+"["); 

 for(int i=0;i<8;i++){
    TF1 tf("tf","gaus"); 
    c1->cd(i+1);
    TH1F *h = new TH1F(Form("h%d",i+1),Form("h%d",i+1),1000,0,1000 ); 
    t->Project(Form("h%d",i+1),Form("(bh2ut[%d]+bh2dt[%d])/2",i,i),Form("bh2ut[%d]>0&&bh2nhits==1",i));
    h->Fit("tf","Q"); 
    double mean = tf.GetParameter(1); 
    h->GetXaxis()->SetRangeUser(mean-20,mean+40);   

    c2[i] = new TCanvas(Form( "c2_%d",i),Form( "c2_%d",i),1500,1000) ;
    c2[i]->Divide(4,3); 
    for(int j=0;j<11;j++){
       TF1 tfb("tfb","gaus"); 
       c2[i]->cd(1+j);
       TH1F *h = new TH1F(Form("btof_%d_%d",j+1,i+1),Form("btof_%d_%d",j+1,i+1),2000,-1000,1000 ); 
       t->Project(Form("btof_%d_%d",j+1,i+1),Form("(bh1ut[%d]+bh1dt[%d])/2-(bh2ut[%d]+bh2dt[%d])/2",j,j,i,i),Form("bh1ut[%d]>0&&bh2ut[%d]>0&&bh1nhits==1&&bh2nhits==1",j,i));
       h->Fit("tfb","Q"); 
       double mean_b = tfb.GetParameter(1); 
       h->GetXaxis()->SetRangeUser(mean_b-20,mean_b+40);   
    }
    c2[i]->Print(fpdf);  
 }
 c1->Print(fpdf+"]"); 

}  
