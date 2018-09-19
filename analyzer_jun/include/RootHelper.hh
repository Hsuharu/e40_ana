/**
 *  file: RootHelper.hh
 *  date: 2017.04.10
 *
 */

#ifndef ROOT_HELPER_HH
#define ROOT_HELPER_HH

#include <stdexcept>

#include <TApplication.h>
#include <TCanvas.h>
#include <TCut.h>
#include <TDatabasePDG.h>
#include <TError.h>
#include <TF1.h>
#include <TFile.h>
#include <TGraph.h>
#include <TGraphErrors.h>
#include <TH1.h>
#include <TH2.h>
#include <TList.h>
#include <TLatex.h>
#include <TMatrix.h>
#include <TMinuit.h>
#include <TObject.h>
#include <TPDGCode.h>
#include <TParticlePDG.h>
#include <TPad.h>
#include <TProfile.h>
#include <TRint.h>
#include <TRandom.h>
// #include <TRandom1.h>
// #include <TRandom2.h>
#include <TRandom3.h>
#include <TROOT.h>
#include <TString.h>
#include <TStyle.h>
#include <TTree.h>
#include <TVector3.h>

#include <std_ostream.hh>

#define ThrowError 1 // if h[i] already exist, throw error
#define OverWrite  0 // if h[i] already exist, delete and renew.

namespace root
{
  const  int    MaxHits  = 500;
  const  int    MaxDepth = 16;
  const  int    MaxHist  = 100000000;
  extern TH1   *h[MaxHist];
  extern TTree *tree;

  //___________________________________________________________________
  inline void
  HB1( int i, const char *title,
       int nbinx, double xlow, double xhigh )
  {
    if( i<0 || MaxHist<=i )
      throw std::out_of_range( Form("HB1() invalid HistId : %d/%d", i, MaxHist) );
    if( h[i] ){
#if ThrowError
      throw std::invalid_argument( Form("h%d (%s) is already exist", i, title) );
#endif
#if OverWrite
      delete h[i];
      h[i] = 0;
#endif
    }
    h[i] = new TH1F( Form("h%d", i), title, nbinx, xlow, xhigh );
  }

  //___________________________________________________________________
  inline void
  HB1( int i, const TString& title,
       int nbinx, double xlow, double xhigh )
  {
    HB1( i, title.Data(), nbinx, xlow, xhigh );
  }

  //___________________________________________________________________
  inline void
  HB2( int i, const char *title,
       int nbinx, double xlow, double xhigh,
       int nbiny, double ylow, double yhigh )
  {
    if( i<0 || MaxHist<=i )
      throw std::out_of_range( Form("HB2() invalid HistId : %d/%d", i, MaxHist) );
    if( h[i] ){
#if ThrowError
      throw std::invalid_argument( Form("h%d (%s) is already exist", i, title) );
#endif
#if OverWrite
      delete h[i];
      h[i] = 0;
#endif
    }
    h[i] = new TH2F( Form("h%d", i), title,
		     nbinx, xlow, xhigh,
		     nbiny, ylow, yhigh );
  }

  //___________________________________________________________________
  inline void
  HB2( int i, const TString& title,
       int nbinx, double xlow, double xhigh,
       int nbiny, double ylow, double yhigh )
  {
    HB2( i, title.Data(), nbinx, xlow, xhigh, nbiny, ylow, yhigh );
  }

  //_____________________________________________________________________
  inline void
  HBProf( int i, const char *title,
	  int nbinx, double xlow, double xhigh,
	  double ylow, double yhigh )
  {
    if( i<0 || MaxHist<=i )
      throw std::out_of_range( Form("HBProf() invalid HistId : %d/%d", i, MaxHist) );
    if( h[i] ){
#if ThrowError
      throw std::invalid_argument( Form("h%d (%s) is already exist", i, title) );
#endif
#if OverWrite
      delete h[i];
      h[i] = 0;
#endif
    }
    h[i] = new TProfile( Form("h%d", i), title,
			 nbinx, xlow, xhigh, ylow, yhigh );
  }

  //___________________________________________________________________
  inline void
  HF1( int i, double x )
  {
    if( i<0 || MaxHist<=i )
      throw std::out_of_range( Form("HF1() invalid HistId : %d/%d", i, MaxHist) );
    if( h[i] ) h[i]->Fill( x );
  }

  //___________________________________________________________________
  inline void
  HF2( int i, double x, double y )
  {
    if( i<0 || MaxHist<=i )
      throw std::out_of_range( Form("HF2() invalid HistId : %d/%d", i, MaxHist) );
    if( h[i] ) h[i]->Fill( x, y );
  }

  //___________________________________________________________________
  inline void
  HFProf( int i, double x, double y )
  {
    if( i<0 || MaxHist<=i )
      throw std::out_of_range( Form("HFProf() invalid HistId : %d/%d", i, MaxHist) );
    if( h[i] ) h[i]->Fill( x, y );
  }

  //_____________________________________________________________________
  inline void
  HBTree( const char *name, const char *title )
  {
    if( tree ){
#if ThrowError
      throw std::invalid_argument( Form("%s (%s) is already exist", name, title) );
#endif
#if OverWrite
      delete tree;
      tree = 0;
#endif
    }
    tree = new TTree( name, title );
  }

  //_____________________________________________________________________
  inline void
  HPrint( const std::string& arg="" )
  {
    hddaq::cout << "#D [root::HPrint()] " << arg << std::endl;
    TList* list = gDirectory->GetList();
#if 1
    int count = 0;
    TIter itr( list );
    while( itr.Next() && ++count ){
      const TString& name( (*itr)->GetName() );
      hddaq::cout << " " << std::setw(8) << std::left << name;
      if( count%10==0 ) hddaq::cout << std::endl;
    }
    hddaq::cout << std::endl;
#endif
    hddaq::cout << " NObject : " << list->GetEntries() << std::endl;
  }

}

#endif
