// -*- C++ -*-

#ifndef SCALER_ANALYZER_HH
#define SCALER_ANALYZER_HH

#include <iomanip>
#include <iostream>
#include <vector>

#include <TString.h>

#include "DetectorID.hh"

class TCanvas;

typedef Long64_t Scaler;

//______________________________________________________________________________
struct ScalerInfo
{
  TString name;
  Int_t   module_id;
  Int_t   channel;
  Bool_t  flag_disp;
  Scaler  data; // integral value in a spill
  Scaler  curr; // current value
  Scaler  prev; // previous value

  ScalerInfo( void ) {}
  ScalerInfo( TString n, Int_t m, Int_t c, Bool_t f=true )
    : name(n), module_id(m), channel(c), flag_disp(f),
      data(0), curr(0), prev(0)
  {
  }

  inline void Print( void ) const
  {
    std::cout << std::setw(8)  << name
	      << std::setw(2)  << module_id
	      << std::setw(2)  << channel
	      << std::setw(2)  << flag_disp
	      << std::setw(10) << data << std::endl;
  }
};

//______________________________________________________________________________
class ScalerAnalyzer
{
public:
  static TString         ClassName( void );
  static ScalerAnalyzer& GetInstance( void );
  ~ScalerAnalyzer( void );

private:
  ScalerAnalyzer( void );
  ScalerAnalyzer( const ScalerAnalyzer& );
  ScalerAnalyzer& operator=( const ScalerAnalyzer& );

public:
  static const Int_t MaxRow = 33;
  enum eDisp {
    kLeft,
    kCenter,
    kRight,
    MaxColumn
  };
  enum eFlag {
    kSeparateComma,
    kSpillBySpill,
    kSemiOnline,
    kScalerSheet,
    nFlag
  };

private:
  enum eScaler { kScaler1, kScaler2, kScaler3, nScaler };

  typedef std::vector< std::vector<ScalerInfo> > ScalerList;

  std::ostream&       m_ost;
  ScalerList          m_info;
  std::vector<Bool_t> m_flag;
  Bool_t              m_spill_increment;
  Bool_t              m_is_spill_end;
  Int_t               m_run_number;
  TCanvas*            m_canvas;

public:
  void                   Clear( Option_t* option="" );
  Bool_t                 Decode( void );
  Double_t               Duty( void ) const;
  std::pair<Int_t,Int_t> Find( const TString& name ) const;
  Bool_t                 FlagDisp( Int_t i, Int_t j ) const { return m_info.at(i).at(j).flag_disp; }
  Double_t               Fraction( const TString& num, const TString& den ) const;
  Scaler                 Get( Int_t i, Int_t j ) const { return m_info.at(i).at(j).data; }
  Scaler                 Get( const TString& name ) const;
  Bool_t                 GetFlag( Int_t i ) const { return m_flag[i]; }
  Int_t                  GetRunNumber( void ) const { return m_run_number; }
  ScalerInfo             GetScalerInfo( Int_t i, Int_t j ) const { return m_info.at(i).at(j); }
  TString                GetScalerName( Int_t i, Int_t j ) const { return m_info.at(i).at(j).name; }
  Bool_t                 Has( const TString& key ) const;
  Bool_t                 IsSpillEnd( void ) const { return m_is_spill_end; }
  Int_t                  ModuleId( Int_t i, Int_t j ) const { return m_info.at(i).at(j).module_id; }
  void                   Print( Option_t* option="" ) const;
  void                   PrintFlags( void ) const;
  void                   PrintScalerSheet( void );
  TString                SeparateComma( Scaler number ) const;
  void                   Set( Int_t i, Int_t j, const ScalerInfo& info );
  void                   SetFlag( Int_t i, Bool_t flag=true ) { m_flag.at(i) = flag; }
  void                   SetRunNumber( Int_t n ) { m_run_number = n; }
  void                   SetSpillEnd( Bool_t flag=true ) { m_is_spill_end = flag; }
  Bool_t                 SpillIncrement( void ) const { return m_spill_increment; }

private:
  void DrawOneBox( Double_t x, Double_t y,
		   const TString& title1, const TString& val1 );
  void DrawOneLine( const TString& title1, const TString& val1,
		    const TString& title2, const TString& val2,
		    const TString& title3, const TString& val3 );
  void DrawOneLine( const TString& title1,
		    const TString& title2,
		    const TString& title3 );
};

//______________________________________________________________________________
inline TString
ScalerAnalyzer::ClassName( void )
{
  static TString g_name("ScalerAnalyzer");
  return g_name;
}

//______________________________________________________________________________
inline ScalerAnalyzer&
ScalerAnalyzer::GetInstance( void )
{
  static ScalerAnalyzer g_instance;
  return g_instance;
}

#endif
