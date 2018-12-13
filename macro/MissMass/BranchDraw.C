// Date::20181106 
// Author::S.Hoshino
// 
 

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


void BranchDraw( int month, int runnumber){
//////////////////////////////////////////////////////////
//   This file has been automatically generated 
//     (Tue Nov  6 16:04:20 2018 by ROOT version6.12/06)
//   from TTree pik/tree of PiKAna
//   found on file: ../../analyzer_jun/rootfile/run05126_DstPiKAna3.root
//////////////////////////////////////////////////////////


//Reset ROOT and connect tree file
   gROOT->Reset();
//   TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("../../analyzer_jun/rootfile/run05126_DstPiKAna3.root");
//
   TString anadir=Form("%s/work/e40/ana",std::getenv("HOME")); 
   TString pdf = Form("%s/pdf/MissMass/BranchDraw_run%05d.pdf", anadir.Data(),runnumber);
   TFile *f = new TFile(Form("%s/analyzer_%s/rootfile/run%05d_DstPiKAna4.root", anadir.Data(),Month[month], runnumber),"READ");

    TTree *pik;
    f->GetObject("pik",pik);

//Declaration of leaves types
   Int_t           runnum;
   Int_t           evnum;
   Int_t           spill;
   Int_t           trigpat[32];
   Int_t           trigflag[32];
   Int_t           nhBh1;
   Int_t           csBh1[5];
   Double_t        Bh1Seg[5];
   Double_t        tBh1[5];
   Double_t        dtBh1[5];
   Double_t        deBh1[5];
   Double_t        btof[5];
   Int_t           nhBh2;
   Int_t           csBh2[4];
   Double_t        Bh2Seg[4];
   Double_t        tBh2[4];
   Double_t        t0Bh2[4];
   Double_t        dtBh2[4];
   Double_t        deBh2[4];
   Int_t           nhTof;
   Int_t           csTof[17];
   Double_t        TofSeg[17];
   Double_t        tTof[17];
   Double_t        dtTof[17];
   Double_t        deTof[17];
   Int_t           nhBft;
   Int_t           csBft[15];
   Double_t        tBft[15];
   Double_t        wBft[15];
   Double_t        BftPos[15];
   Int_t           nhSch;
   Int_t           csSch[25];
   Double_t        tSch[25];
   Double_t        wSch[25];
   Double_t        SchPos[25];
   Int_t           nlBcOut;
   Int_t           ntBcOut;
   Int_t           nhBcOut[3];
   Double_t        chisqrBcOut[3];
   Double_t        x0BcOut[3];
   Double_t        y0BcOut[3];
   Double_t        u0BcOut[3];
   Double_t        v0BcOut[3];
   Double_t        xtgtBcOut[3];
   Double_t        ytgtBcOut[3];
   Double_t        xbh2BcOut[3];
   Double_t        ybh2BcOut[3];
   Int_t           ntK18;
   Int_t           nhK18[3];
   Double_t        chisqrK18[3];
   Double_t        pK18[3];
   Double_t        xtgtK18[3];
   Double_t        ytgtK18[3];
   Double_t        utgtK18[3];
   Double_t        vtgtK18[3];
   Double_t        thetaK18[3];
   Int_t           nlSdcIn;
   Int_t           ntSdcIn;
   Int_t           nhSdcIn[7];
   Double_t        chisqrSdcIn[7];
   Double_t        x0SdcIn[7];
   Double_t        y0SdcIn[7];
   Double_t        u0SdcIn[7];
   Double_t        v0SdcIn[7];
   Int_t           nlSdcOut;
   Int_t           ntSdcOut;
   Int_t           nhSdcOut[4];
   Double_t        chisqrSdcOut[4];
   Double_t        x0SdcOut[4];
   Double_t        y0SdcOut[4];
   Double_t        u0SdcOut[4];
   Double_t        v0SdcOut[4];
   Int_t           ntKurama;
   Int_t           nhKurama[4];
   Double_t        chisqrKurama[4];
   Double_t        stof[4];
   Double_t        path[4];
   Double_t        pKurama[4];
   Double_t        qKurama[4];
   Double_t        m2[4];
   Double_t        xtgtKurama[4];
   Double_t        ytgtKurama[4];
   Double_t        utgtKurama[4];
   Double_t        vtgtKurama[4];
   Double_t        thetaKurama[4];
   Double_t        xtofKurama[4];
   Double_t        ytofKurama[4];
   Double_t        utofKurama[4];
   Double_t        vtofKurama[4];
   Double_t        tofsegKurama[4];
   Int_t           nPi;
   Int_t           nK;
   Int_t           nPiK;
   Double_t        vtx[8];
   Double_t        vty[8];
   Double_t        vtz[8];
   Double_t        closeDist[8];
   Double_t        theta[8];
   Double_t        MissMass[8];
   Double_t        MissMassCorr[8];
   Double_t        MissMassCorrDE[8];
   Double_t        thetaCM[8];
   Double_t        costCM[8];
   Double_t        xpi[8];
   Double_t        ypi[8];
   Double_t        upi[8];
   Double_t        vpi[8];
   Double_t        xk[8];
   Double_t        yk[8];
   Double_t        uk[8];
   Double_t        vk[8];
   Double_t        pOrg[8];
   Double_t        pCalc[8];
   Double_t        pCorr[8];
   Double_t        pCorrDE[8];

   // Set branch addresses.
   pik->SetBranchAddress("runnum",&runnum);
   pik->SetBranchAddress("evnum",&evnum);
   pik->SetBranchAddress("spill",&spill);
   pik->SetBranchAddress("trigpat",trigpat);
   pik->SetBranchAddress("trigflag",trigflag);
   pik->SetBranchAddress("nhBh1",&nhBh1);
   pik->SetBranchAddress("csBh1",csBh1);
   pik->SetBranchAddress("Bh1Seg",Bh1Seg);
   pik->SetBranchAddress("tBh1",tBh1);
   pik->SetBranchAddress("dtBh1",dtBh1);
   pik->SetBranchAddress("deBh1",deBh1);
   pik->SetBranchAddress("btof",btof);
   pik->SetBranchAddress("nhBh2",&nhBh2);
   pik->SetBranchAddress("csBh2",csBh2);
   pik->SetBranchAddress("Bh2Seg",Bh2Seg);
   pik->SetBranchAddress("tBh2",tBh2);
   pik->SetBranchAddress("t0Bh2",t0Bh2);
   pik->SetBranchAddress("dtBh2",dtBh2);
   pik->SetBranchAddress("deBh2",deBh2);
   pik->SetBranchAddress("nhTof",&nhTof);
   pik->SetBranchAddress("csTof",csTof);
   pik->SetBranchAddress("TofSeg",TofSeg);
   pik->SetBranchAddress("tTof",tTof);
   pik->SetBranchAddress("dtTof",dtTof);
   pik->SetBranchAddress("deTof",deTof);
   pik->SetBranchAddress("nhBft",&nhBft);
   pik->SetBranchAddress("csBft",csBft);
   pik->SetBranchAddress("tBft",tBft);
   pik->SetBranchAddress("wBft",wBft);
   pik->SetBranchAddress("BftPos",BftPos);
   pik->SetBranchAddress("nhSch",&nhSch);
   pik->SetBranchAddress("csSch",csSch);
   pik->SetBranchAddress("tSch",tSch);
   pik->SetBranchAddress("wSch",wSch);
   pik->SetBranchAddress("SchPos",SchPos);
   pik->SetBranchAddress("nlBcOut",&nlBcOut);
   pik->SetBranchAddress("ntBcOut",&ntBcOut);
   pik->SetBranchAddress("nhBcOut",nhBcOut);
   pik->SetBranchAddress("chisqrBcOut",chisqrBcOut);
   pik->SetBranchAddress("x0BcOut",x0BcOut);
   pik->SetBranchAddress("y0BcOut",y0BcOut);
   pik->SetBranchAddress("u0BcOut",u0BcOut);
   pik->SetBranchAddress("v0BcOut",v0BcOut);
   pik->SetBranchAddress("xtgtBcOut",xtgtBcOut);
   pik->SetBranchAddress("ytgtBcOut",ytgtBcOut);
   pik->SetBranchAddress("xbh2BcOut",xbh2BcOut);
   pik->SetBranchAddress("ybh2BcOut",ybh2BcOut);
   pik->SetBranchAddress("ntK18",&ntK18);
   pik->SetBranchAddress("nhK18",nhK18);
   pik->SetBranchAddress("chisqrK18",chisqrK18);
   pik->SetBranchAddress("pK18",pK18);
   pik->SetBranchAddress("xtgtK18",xtgtK18);
   pik->SetBranchAddress("ytgtK18",ytgtK18);
   pik->SetBranchAddress("utgtK18",utgtK18);
   pik->SetBranchAddress("vtgtK18",vtgtK18);
   pik->SetBranchAddress("thetaK18",thetaK18);
   pik->SetBranchAddress("nlSdcIn",&nlSdcIn);
   pik->SetBranchAddress("ntSdcIn",&ntSdcIn);
   pik->SetBranchAddress("nhSdcIn",nhSdcIn);
   pik->SetBranchAddress("chisqrSdcIn",chisqrSdcIn);
   pik->SetBranchAddress("x0SdcIn",x0SdcIn);
   pik->SetBranchAddress("y0SdcIn",y0SdcIn);
   pik->SetBranchAddress("u0SdcIn",u0SdcIn);
   pik->SetBranchAddress("v0SdcIn",v0SdcIn);
   pik->SetBranchAddress("nlSdcOut",&nlSdcOut);
   pik->SetBranchAddress("ntSdcOut",&ntSdcOut);
   pik->SetBranchAddress("nhSdcOut",nhSdcOut);
   pik->SetBranchAddress("chisqrSdcOut",chisqrSdcOut);
   pik->SetBranchAddress("x0SdcOut",x0SdcOut);
   pik->SetBranchAddress("y0SdcOut",y0SdcOut);
   pik->SetBranchAddress("u0SdcOut",u0SdcOut);
   pik->SetBranchAddress("v0SdcOut",v0SdcOut);
   pik->SetBranchAddress("ntKurama",&ntKurama);
   pik->SetBranchAddress("nhKurama",nhKurama);
   pik->SetBranchAddress("chisqrKurama",chisqrKurama);
   pik->SetBranchAddress("stof",stof);
   pik->SetBranchAddress("path",path);
   pik->SetBranchAddress("pKurama",pKurama);
   pik->SetBranchAddress("qKurama",qKurama);
   pik->SetBranchAddress("m2",m2);
   pik->SetBranchAddress("xtgtKurama",xtgtKurama);
   pik->SetBranchAddress("ytgtKurama",ytgtKurama);
   pik->SetBranchAddress("utgtKurama",utgtKurama);
   pik->SetBranchAddress("vtgtKurama",vtgtKurama);
   pik->SetBranchAddress("thetaKurama",thetaKurama);
   pik->SetBranchAddress("xtofKurama",xtofKurama);
   pik->SetBranchAddress("ytofKurama",ytofKurama);
   pik->SetBranchAddress("utofKurama",utofKurama);
   pik->SetBranchAddress("vtofKurama",vtofKurama);
   pik->SetBranchAddress("tofsegKurama",tofsegKurama);
   pik->SetBranchAddress("nPi",&nPi);
   pik->SetBranchAddress("nK",&nK);
   pik->SetBranchAddress("nPiK",&nPiK);
   pik->SetBranchAddress("vtx",vtx);
   pik->SetBranchAddress("vty",vty);
   pik->SetBranchAddress("vtz",vtz);
   pik->SetBranchAddress("closeDist",closeDist);
   pik->SetBranchAddress("theta",theta);
   pik->SetBranchAddress("MissMass",MissMass);
   pik->SetBranchAddress("MissMassCorr",MissMassCorr);
   pik->SetBranchAddress("MissMassCorrDE",MissMassCorrDE);
   pik->SetBranchAddress("thetaCM",thetaCM);
   pik->SetBranchAddress("costCM",costCM);
   pik->SetBranchAddress("xpi",xpi);
   pik->SetBranchAddress("ypi",ypi);
   pik->SetBranchAddress("upi",upi);
   pik->SetBranchAddress("vpi",vpi);
   pik->SetBranchAddress("xk",xk);
   pik->SetBranchAddress("yk",yk);
   pik->SetBranchAddress("uk",uk);
   pik->SetBranchAddress("vk",vk);
   pik->SetBranchAddress("pOrg",pOrg);
   pik->SetBranchAddress("pCalc",pCalc);
   pik->SetBranchAddress("pCorr",pCorr);
   pik->SetBranchAddress("pCorrDE",pCorrDE);

//     This is the loop skeleton
//       To read only selected branches, Insert statements like:
// pik->SetBranchStatus("*",0);  // disable all branches
// Hist Identification
  TH1D *Hist[100];
  Hist[0] = new TH1D(Form("Hist%d",0),Form("Hist%d",0),300000,0,300000);
      for(int i=0;i<5;i++){
        Hist[i+1]= new TH1D(Form("Hist%d",i+1),Form("Hist%d",i+1),24,0,12);
        Hist[i+27]= new TH1D(Form("Hist%d",i+27),Form("Hist%d",i+27),50,-2.5,2.5);
      }
      for(int i=0;i<4;i++){
        Hist[i+6]= new TH1D(Form("Hist%d",i+6),Form("Hist%d",i+6),16,0,8);
      }
      for(int i=0;i<17;i++){
        Hist[i+10]= new TH1D(Form("Hist%d",i+10),Form("Hist%d",i+6),48,0,24);
      }

      TH1D *MM[5];
      for(int i=0;i<5;i++){
        MM[i]= new TH1D(Form("Missing Mass Cut%d",i+1),Form("Missing Mass Cut%d",i+1),50,0,1.6);
      }
// Para Identification
   int pre_evnum=0;


   Long64_t nentries = pik->GetEntries();

   Long64_t nbytes = 0;
   for (Long64_t i=0; i<nentries;i++) {
      nbytes += pik->GetEntry(i);
//      if(evnum!=0){
//        if(pre_evnum!=evnum-1){
//          cout << pre_evnum <<endl;
//        }
//      }
      Hist[0]->Fill(evnum);
      pre_evnum = evnum;

      for(int i=0;i<nhBh1;i++){
        Hist[i+1]->Fill(Bh1Seg[i]);
        Hist[i+27]->Fill(btof[i]);
      }
      for(int i=0;i<nhBh2;i++){
        Hist[i+6]->Fill(Bh2Seg[i]);
      }
      for(int i=0;i<nhTof;i++){
        Hist[i+10]->Fill(TofSeg[i]);
      }
      MM[0]->Fill(MissMass[0]);
      if(m2[0]<0.4&&m2[0]>0.1){
        MM[1]->Fill(MissMass[0]);
        if(chisqrKurama[0]<50){
          MM[2]->Fill(MissMass[0]);
        }
      }
      
   }

   TCanvas *c1= new TCanvas("c1","c1",900,800);
   TCanvas *c2= new TCanvas("c2","c2",900,800);
   TCanvas *c3= new TCanvas("c3","c3",900,800);
   TCanvas *c4= new TCanvas("c4","c4",1100,800);
   TCanvas *c5= new TCanvas("c5","c5",900,800);
   c2->Divide(3,2);
   c3->Divide(2,2);
   c4->Divide(5,4);
   c5->Divide(3,2);

   c1->Print(pdf+"["); 

   c1->cd();
   Hist[0]->Draw();
   c1->Print(pdf);

   for(int i=0;i<5;i++){
     c2->cd(i+1);
     Hist[i+1]->Draw();
     c5->cd(i+1);
     Hist[i+27]->Draw();
   }
   c2->Print(pdf);

   for(int i=0;i<4;i++){
     c3->cd(i+1);
     Hist[i+6]->Draw();
   }
   c3->Print(pdf);
   for(int i=0;i<17;i++){
     c4->cd(i+1);
     Hist[i+10]->Draw();
   }
   c4->Print(pdf);

   c1->cd();
   MM[0]->Draw();
   c1->Print(pdf);
   MM[1]->Draw();
   c1->Print(pdf);
   MM[2]->Draw();
   c1->Print(pdf);

   c1->Print(pdf+"]"); 
}


