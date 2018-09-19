/**
 *  file: DstHelper.hh
 *  date: 2017.04.10
 *
 */

#ifndef DST_HELPER_HH
#define DST_HELPER_HH

#include <algorithm>
#include <iomanip>
#include <iostream>
#include <vector>

#include <TFile.h>
#include <TTree.h>

// if event number mismatch is found, exit process.
#define CheckEventNumberMismatch 0

//______________________________________________________________________________
namespace dst
{
  // implemented in each dst
  extern std::vector<TString> ArgName;
  extern std::vector<TString> TreeName;
  extern std::vector<TFile*>  TFileCont;
  extern std::vector<TTree*>  TTreeCont;
  bool InitializeEvent( void );
  bool DstOpen( std::vector<std::string> arg );
  bool DstRead( void );
  bool DstRead( int ievent );
  bool DstClose( void );

  //______________________________________________________________________________
  inline bool
  CheckArg( const std::vector<std::string>& arg )
  {
    const std::size_t n = arg.size();
    bool status = ( n == ArgName.size() && n == TreeName.size() );

    if( !status ){
      std::cout << "#D Usage : " << hddaq::basename(arg[0]);
      for( std::size_t i=1; i<n; ++i ){
	std::cout << " " << ArgName[i];
      }
      std::cout << std::endl;
      std::cout << " ArgName.size() = " << ArgName.size() << " "
		<< " TreeName.size() = " << TreeName.size() << std::endl;
      return false;
    }

    for( std::size_t i=0; i<n; ++i ){
      std::cout << " key = " << std::setw(18) << std::left << ArgName[i]
		<< " arg[" << i << "] = " << arg[i] << std::endl;
    }

    TFileCont.resize(n); TTreeCont.resize(n);
    return ( ArgName.size()==TreeName.size() );
  }

  //______________________________________________________________________________
  inline bool
  OpenFile( TFile*& file, const TString& name )
  {
    file = new TFile( name );
    if( !file || !file->IsOpen() ){
      std::cerr << "#E failed to open TFile : " << name << std::endl;
      return false;
    }
    return true;
  }

  //______________________________________________________________________________
  inline bool
  OpenTree( TFile* file, TTree*& tree, const TString& name )
  {
    if( !file || !file->IsOpen() ) return false;
    tree = (TTree*)file->Get( name );
    if( !tree ){
      std::cerr << "#E failed to open TTree : " << name << std::endl;
      return false;
    }
    return true;
  }

  //______________________________________________________________________________
  inline bool
  CheckEntries( const std::vector<TTree*>& TTreeCont )
  {
    const std::size_t n = TTreeCont.size();
    bool status = true;
    std::vector<int> entries( n, -1 );
    for( std::size_t i=0; i<n; ++i ){
      if( !TTreeCont[i] ) continue;
      entries[i] = TTreeCont[i]->GetEntries();
      if( i>0 && entries[i]!=entries[i-1] && entries[i-1]!=-1 ){
	status = false;
      }
    }
    if( !status ){
#if CheckEventNumberMismatch
      std::cerr << "#E Entries Mismatch" << std::endl;
#else
      std::cerr << "#W Entries Mismatch" << std::endl;
#endif
      for( std::size_t i=0; i<n; ++i ){
	if( !TTreeCont[i] ) continue;
	std::cerr << "   " << std::setw(8) << TTreeCont[i]->GetName()
		  << " " << entries[i] << std::endl;
      }
    }
#if CheckEventNumberMismatch
    return status;
#else
    return true;
#endif
  }

  //______________________________________________________________________________
  inline int
  GetEntries( const std::vector<TTree*>& TTreeCont )
  {
    std::vector<std::size_t> nevent;
    for( std::size_t i=0, n=TTreeCont.size(); i<n; ++i ){
      if( TTreeCont[i] ){
#if CheckEventNumberMismatch
	return TTreeCont[i]->GetEntries();
#else
	nevent.push_back( TTreeCont[i]->GetEntries() );
#endif
      }
    }
#if CheckEventNumberMismatch
    return 0;
#else
    return *std::min_element( nevent.begin(), nevent.end() );
#endif
  }

  //______________________________________________________________________________
  inline bool
  GetEntry( Int_t ievent )
  {
    for( std::size_t i=0, n=TTreeCont.size(); i<n; ++i ){
      if( TTreeCont[i] ) TTreeCont[i]->GetEntry( ievent );
    }
    return true;
  }
}

#endif
