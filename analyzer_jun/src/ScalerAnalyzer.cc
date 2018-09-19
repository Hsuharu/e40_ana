// -*- C++ -*-

#include "ScalerAnalyzer.hh"

#include <algorithm>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <sstream>
#include <stdexcept>

#include <TCanvas.h>
#include <TLatex.h>
#include <TLine.h>
#include <TMath.h>
#include <TSystem.h>
#include <TTimeStamp.h>

#include <std_ostream.hh>
#include <Unpacker.hh>
#include <UnpackerManager.hh>

#include "ConfMan.hh"
#include "DetectorID.hh"
#include "Exception.hh"
#include "FuncName.hh"
#include "UserParamMan.hh"

namespace
{
  using namespace hddaq::unpacker;
  const UnpackerManager& gUnpacker = GUnpacker::get_instance();
  const std::vector<TString> sFlag =
    { "SeparateComma", "SpillBySpill", "SemiOnline", "ScalerSheet" };
}

//______________________________________________________________________________
ScalerAnalyzer::ScalerAnalyzer( void )
  : m_ost( std::cout ), //m_ost( hddaq::cout ),
    m_info( MaxColumn, std::vector<ScalerInfo>(MaxRow) ),
    m_flag( nFlag, false ),
    m_spill_increment(false),
    m_is_spill_end(false),
    m_run_number(-1),
    m_canvas()
{
  for( Int_t i=0; i<MaxColumn; ++i ){
    for( Int_t j=0; j<MaxRow; ++j ){
      m_info[i][j] = ScalerInfo("n/a", i, j, false );
    }
  }
}

//______________________________________________________________________________
ScalerAnalyzer::~ScalerAnalyzer( void )
{
}

//______________________________________________________________________________
void
ScalerAnalyzer::Clear( Option_t* )
{
  for( Int_t i=0; i<MaxColumn; ++i ){
    for( Int_t j=0; j<MaxRow; ++j ){
      if( !m_info[i][j].name.EqualTo("Spill") ){
	m_info[i][j].data = 0;
      }
    }
  }
}

//______________________________________________________________________________
Bool_t
ScalerAnalyzer::Decode( void )
{
  m_spill_increment = false;
  m_is_spill_end    = false;

  //////////////////// Run Number
  if( m_run_number != gUnpacker.get_root()->get_run_number() ){
    m_run_number = gUnpacker.get_root()->get_run_number();
    Clear();
  }

  //////////////////// Trigger Flag
  {
    static const Int_t device_id = gUnpacker.get_device_id("TFlag");
    static const Int_t tdc_id    = gUnpacker.get_data_id("TFlag", "tdc");
    if( gUnpacker.get_entries( device_id, 0, SpillEndFlag, 0, tdc_id ) > 0 &&
	gUnpacker.get( device_id, 0, SpillEndFlag, 0, tdc_id ) > 0 ){
      m_is_spill_end = true;
    }
  }

  if( m_flag[kScalerSheet] && !m_is_spill_end ){
    for( Int_t i=0; i<MaxColumn; ++i ){
      for( Int_t j=0; j<MaxRow; ++j ){
	m_info[i][j].prev = 0;
      }
    }
    return true;
  }

  //////////////////// Scaler Data
  {
    static const Int_t device_id  = gUnpacker.get_device_id("Scaler");

    for( Int_t i=0; i<MaxColumn; ++i ){
      for( Int_t j=0; j<MaxRow; ++j ){
	if( !m_info[i][j].flag_disp )
	  continue;
	if( m_info[i][j].name.EqualTo("Spill") )
	  continue;

	Int_t module_id = m_info[i][j].module_id;
	Int_t channel   = m_info[i][j].channel;

	if( module_id < 0 || channel < 0 )
	  continue;

	Int_t nhit = gUnpacker.get_entries( device_id, module_id, 0, channel, 0 );
	if( nhit<=0 ) continue;
	Scaler val = gUnpacker.get( device_id, module_id, 0, channel, 0 );

	if( m_info[i][j].prev > val ){
	  m_spill_increment = true;
	  m_info[i][j].prev = 0;
	}

    	if( m_flag[kSpillBySpill] && m_spill_increment )
    	  m_info[i][j].data = 0;

	m_info[i][j].curr  = val;
	m_info[i][j].data += val - m_info[i][j].prev;
	m_info[i][j].prev  = m_info[i][j].curr;
      }
    }
  }

  //////////////////// for BH1 SUM
  {
    if( Has("BH1-SUM") ){
      static std::pair<Int_t,Int_t> p = Find("BH1-SUM");
      m_info[p.first][p.second].data = 0;
      for( Int_t i=0; i<NumOfSegBH1; ++i ){
	m_info[p.first][p.second].data += Get( Form("BH1-%02d", i+1) );
      }
    }
  }

  //////////////////// for BH2 SUM
  {
    if( Has("BH2-SUM") ){
      static std::pair<Int_t,Int_t> p = Find("BH2-SUM");
      m_info[p.first][p.second].data = 0;
      for( Int_t i=0; i<NumOfSegBH2; ++i ){
	m_info[p.first][p.second].data += Get( Form("BH2-%02d", i+1) );
      }
    }
  }

  //////////////////// Spill
  {
    if( Has("Spill") ){
      static Bool_t first = true;
      static std::pair<Int_t,Int_t> p = Find("Spill");
      if( first && !m_flag[kScalerSheet] ){
	m_info[p.first][p.second].data++;
	first = false;
      }
      if( m_spill_increment ||
	  ( m_flag[kScalerSheet] && m_is_spill_end ) ){
	m_info[p.first][p.second].data++;
      }
    }
  }
  return true;
}

//______________________________________________________________________________
Double_t
ScalerAnalyzer::Duty( void ) const
{
  Double_t daq_eff  = Fraction("L1-Acc","L1-Req");
  Double_t live_eff = Fraction("Live-Time","Real-Time");
  Double_t duty = daq_eff/(1.-daq_eff)*(1./live_eff-1.);
  if( duty > 1. || TMath::IsNaN(duty) )
    return 1.;
  else
    return duty;
}

//______________________________________________________________________________
void
ScalerAnalyzer::DrawOneBox( Double_t x, Double_t y,
			    const TString& title1, const TString& val1 )
{
  TLatex tex;
  tex.SetNDC();
  tex.SetTextSize(0.04);
  tex.SetTextAlign(12);
  tex.DrawLatex( x, y, title1 );
  tex.SetTextAlign(32);
  tex.DrawLatex( x+0.28, y, val1 );
}

//______________________________________________________________________________
void
ScalerAnalyzer::DrawOneLine( const TString& title1, const TString& val1,
			     const TString& title2, const TString& val2,
			     const TString& title3, const TString& val3 )
{
  static Int_t i = 0;
  const Double_t ystep = 0.05;
  const Double_t y0 = 0.95;
  Double_t y = y0 - (i+1)*ystep;
  Double_t x[] = { 0.05, 0.35, 0.67 };
  DrawOneBox( x[0], y, title1, val1 );
  DrawOneBox( x[1], y, title2, val2 );
  DrawOneBox( x[2], y, title3, val3 );
  TLine line;
  line.SetNDC();
  line.SetLineColor(kGray);
  line.DrawLine( 0.05, y-0.5*ystep, 0.95, y-0.5*ystep );
  line.SetLineColor(kBlack);
  line.DrawLine( 0.34, y-0.5*ystep, 0.34, y+0.5*ystep );
  line.DrawLine( 0.66, y-0.5*ystep, 0.66, y+0.5*ystep );
  if( i==1 || i==5 || i==15 )
    line.DrawLine( 0.05, y-0.5*ystep, 0.95, y-0.5*ystep );

  ++i;
}

//______________________________________________________________________________
void
ScalerAnalyzer::DrawOneLine( const TString& title1,
			     const TString& title2,
			     const TString& title3 )
{
  DrawOneLine( title1, SeparateComma( Get(title1) ),
	       title2, SeparateComma( Get(title2) ),
	       title3, SeparateComma( Get(title3) ) );
}

//______________________________________________________________________________
std::pair<Int_t,Int_t>
ScalerAnalyzer::Find( const TString& name ) const
{
  for( Int_t i=0; i<MaxColumn; ++i ){
    for( Int_t j=0; j<MaxRow; ++j ){
      if( m_info[i][j].name.EqualTo( name ) ){
	return std::pair<Int_t,Int_t>( i, j );
      }
    }
  }

  m_ost << "#W " << FUNC_NAME << " "
	<< "no such name : " << name << std::endl;

  return std::pair<Int_t,Int_t>( -1, -1 );
}

//______________________________________________________________________________
Double_t
ScalerAnalyzer::Fraction( const TString& num, const TString& den ) const
{
  return (Double_t)Get( num ) / Get( den );
}

//______________________________________________________________________________
Scaler
ScalerAnalyzer::Get( const TString& name ) const
{
  for( Int_t i=0; i<MaxColumn; ++i ){
    for( Int_t j=0; j<MaxRow; ++j ){
      if( m_info[i][j].name.EqualTo( name ) ){
	return m_info[i][j].data;
      }
    }
  }

  m_ost << "#W " << FUNC_NAME << " "
	<< "no such ScalerInfo : " << name << std::endl;

  return 0;
}

//______________________________________________________________________________
Bool_t
ScalerAnalyzer::Has( const TString& name ) const
{
  for( Int_t i=0; i<MaxColumn; ++i ){
    for( Int_t j=0; j<MaxRow; ++j ){
      if( m_info[i][j].name.EqualTo( name ) ){
	return true;
      }
    }
  }

  return false;
}

//______________________________________________________________________________
void
ScalerAnalyzer::Print( Option_t* ) const
{
  m_ost << "\033[2J" << std::endl;

  TString end_mark = m_is_spill_end ? "Spill End" : "";

  Int_t event_number = gUnpacker.get_event_number();
  std::cout << std::left  << std::setw(16) << "RUN"
	    << std::right << std::setw(16) << SeparateComma( m_run_number ) << " : "
	    << std::left  << std::setw(16) << "Event Number"
	    << std::right << std::setw(16) << SeparateComma( event_number ) << " : "
	    << std::left  << std::setw(16) << ""
	    << std::right << std::setw(16) << end_mark
	    << std::endl << std::endl;

  for( Int_t i=0; i<MaxRow; ++i ){
    m_ost << std::left  << std::setw(16) << m_info[kLeft][i].name
	  << std::right << std::setw(16) << SeparateComma( m_info[kLeft][i].data )
	  << " : "
	  << std::left  << std::setw(16) << m_info[kCenter][i].name
	  << std::right << std::setw(16) << SeparateComma( m_info[kCenter][i].data )
	  << " : "
	  << std::left  << std::setw(16) << m_info[kRight][i].name
	  << std::right << std::setw(16) << SeparateComma( m_info[kRight][i].data )
	  <<std::endl;
  }
  m_ost << std::endl  << std::setprecision(6) << std::fixed
	<< std::left  << std::setw(16) << "Beam/TM"
	<< std::right << std::setw(16) << Fraction("Beam", "TM") << " : "
	<< std::left  << std::setw(16) << "Live/Real"
	<< std::right << std::setw(16) << Fraction("Live-Time","Real-Time") << " : "
	<< std::left  << std::setw(16) << "DAQ-Eff"
	<< std::right << std::setw(16) << Fraction("L1-Acc","L1-Req") << std::endl
	<< std::left  << std::setw(16) << "(BH2,K)/Beam"
	<< std::right << std::setw(16) << Fraction("(BH2,K)", "Beam") << " : "
	<< std::left  << std::setw(16) << "L2-Eff"
	<< std::right << std::setw(16) << Fraction("L2-Acc","L1-Acc") << " : "
	<< std::left  << std::setw(16) << "Duty-Factor"
	<< std::right << std::setw(16) << Duty() << std::endl
	<< std::endl;
}

//______________________________________________________________________________
TString
ScalerAnalyzer::SeparateComma( Scaler number ) const
{
  if( m_flag[kSeparateComma] ){
    std::vector<Scaler> sep_num;

    while( number/1000 ){
      sep_num.push_back( number%1000 );
      number /= 1000;
    }

    std::stringstream ss;  ss << number;
    std::vector<Scaler>::reverse_iterator
      itr, itr_end = sep_num.rend();
    for( itr=sep_num.rbegin(); itr!=itr_end; ++itr ){
      ss << "," << std::setfill('0') << std::setw(3) << *itr;
    }

    return TString( ss.str() );
  }
  else {
    return TString::LLtoa( number, 10 );
  }
}

//______________________________________________________________________________
void
ScalerAnalyzer::PrintFlags( void ) const
{
  m_ost << "#D " << FUNC_NAME << std::endl << std::left;
  for( Int_t i=0; i<nFlag; ++i ){
    m_ost << " key = " << std::setw(20) << sFlag[i]
	  << " val = " << m_flag[i] << std::endl;
  }
}

//______________________________________________________________________________
void
ScalerAnalyzer::PrintScalerSheet( void )
{
  if( !m_canvas )
    m_canvas = new TCanvas( "c1", "c1", 1200, 800 );

  TTimeStamp stamp;
  stamp.Add( -stamp.GetZoneOffset() );

  DrawOneLine( stamp.AsString("s"), "", "", "", "Name", "" );

  DrawOneLine( Form("#color[%d]{Run#}", kRed+1), SeparateComma( m_run_number ),
	       "Ref Run#", "",
	       "Event#", SeparateComma( gUnpacker.get_event_number() ) );

  DrawOneLine( "Spill", SeparateComma( Get("Spill") ),
	       "Beam", SeparateComma( Get("Beam") ),
	       "D4", "[T]" );
  DrawOneLine( "Clock", SeparateComma( Get("10M-Clock") ),
	       "#pi-Beam", SeparateComma( Get("pi-Beam") ),
	       "KURAMA", "[T]" );
  DrawOneLine( "IM", SeparateComma( Get("IM") ),
	       "p-Beam", SeparateComma( Get("p-Beam") ),
	       "Delay", "[s]" );
  DrawOneLine( "TM", SeparateComma( Get("TM") ),
	       "(BH2,TOF)", SeparateComma( Get("(BH2,TOF)") ),
	       "Width", "[s]" );

  DrawOneLine( "BH1",    "BH1-SUM",  "L1-Req"  );
  DrawOneLine( "BH2",    "BH2-SUM",  "L1-Acc"  );
  DrawOneLine( "SAC",    "(BH2,pi)",  "Matrix"  );
  DrawOneLine( "SCH",    "(BH2,p)",   "Mst-Acc" );
  DrawOneLine( "TOF",    "K-Scat",   "Mst-Clr" );
  DrawOneLine( "TOF-HT", "(BH2,K)",  "Clear"   );
  DrawOneLine( "TOF-24", "CFT-Phi1", "L2-Req"  );
  DrawOneLine( "LC",     "CFT-Phi2", "L2-Acc"  );
  DrawOneLine( "BGO",    "CFT-Phi3", "pi-Scat" );
  DrawOneLine( "PiID",   "CFT-Phi4", "p-Scat"  );

  DrawOneLine( "Beam/TM",   Form("%.6lf", Fraction("Beam","TM")),
	       "Live/Real", Form("%.6lf", Fraction("Live-Time","Real-Time")),
	       "DAQ Eff",   Form("%.6lf", Fraction("L1-Acc","L1-Req")) );
  DrawOneLine( "(BH2,K)/Beam", Form("%.6lf", Fraction("(BH2,K)","Beam")),
	       "L2 Eff",       Form("%.6lf", Fraction("L2-Acc","L1-Acc")),
	       "Duty Factor",  Form("%.6lf", Duty()) );

  const TString& scaler_sheet_pdf("/tmp/scaler_sheet.pdf");
  m_canvas->Print( scaler_sheet_pdf );

  const TString& print_command("lpr "+scaler_sheet_pdf);
  gSystem->Exec( print_command );
}

//______________________________________________________________________________
void
ScalerAnalyzer::Set( Int_t i, Int_t j, const ScalerInfo& info )
{
  if( i >= MaxColumn || j >= MaxRow ){
    m_ost << "#E " << FUNC_NAME << std::endl
	  << " * Exceed Column/Row : " << info.name << std::endl;
    throw Exception( FUNC_NAME+" "+info.name );
  } else {
    m_info[i][j] = info;
  }
}
