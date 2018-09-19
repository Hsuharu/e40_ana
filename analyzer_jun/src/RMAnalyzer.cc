/**
 *  file: RMAnalyzer.cc
 *  date: 2017.04.10
 *
 */

#include "RMAnalyzer.hh"

#include <algorithm>
#include <iomanip>
#include <iostream>
#include <string>

#include <std_ostream.hh>

#include "ConfMan.hh"
#include "DetectorID.hh"
#include "DCRawHit.hh"
#include "HodoRawHit.hh"
#include "Unpacker.hh"
#include "UnpackerManager.hh"
#include "UserParamMan.hh"

namespace
{
  using namespace hddaq::unpacker;
  const std::string& class_name("RMAnalyzer");
  const UnpackerManager& gUnpacker = GUnpacker::get_instance();
}


//______________________________________________________________________________
RMAnalyzer::RMAnalyzer( void )
  : m_event_number( 0 ),
    m_local_event_number( 0 ),
    m_spill_number( 0 )
{
  m_data.resize( NumOfPlaneVmeRm + NumOfHulRm);
  for( std::size_t i=0; i<NumOfPlaneVmeRm + NumOfHulRm; ++i ){
    m_data[i].resize( nType );
    for( std::size_t j=0; j<nType; ++j ){
      m_data[i][j].resize( nData );
    }
  }
}

//______________________________________________________________________________
RMAnalyzer::~RMAnalyzer( void )
{
}

//______________________________________________________________________________
void
RMAnalyzer::Clear( void )
{
  for( std::size_t i=0; i<NumOfPlaneVmeRm + NumOfHulRm; ++i ){
    for( std::size_t j=0; j<nType; ++j ){
      for( std::size_t k=0; k<nData; ++k ){
  	m_data[i][j][k] = 0;
      }
    }
  }
}

//______________________________________________________________________________
bool
RMAnalyzer::Decode( void )
{
  static const std::string func_name("["+class_name+"::"+__func__+"()]");

  Clear();

  Unpacker *gUnpackerRoot = gUnpacker.get_root();
  if( gUnpackerRoot ) m_run_number = gUnpackerRoot->get_run_number();

  // VmeRm
  for( int plane=0; plane<NumOfPlaneVmeRm; ++plane ){
    for( int ch=0; ch<nType; ++ch ){
      for( int data=0; data<nData; ++data ){
	int nhit = gUnpacker.get_entries( DetIdVmeRm, plane, 0, ch, data );
	if( nhit<=0 ) continue;
	unsigned int val = gUnpacker.get( DetIdVmeRm, plane, 0, ch, data );
	if( ch==kLock && val!=0 ) val = 1;
	m_data[plane][ch][data] = val;
      }// for(data)
    }// for(ch)
  }// for(plane)

  // HulRm
  for( int plane=0; plane<NumOfHulRm; ++plane ){
    for( int data=0; data<nData-2; ++data ){
      static const int device_id = gUnpacker.get_device_id("HUL-RM");
      int nhit = gUnpacker.get_entries( device_id, plane, 0, 0, data );
      if( nhit<=0 ) continue;
      unsigned int val = gUnpacker.get( device_id, plane, 0, 0, data );
      m_data[plane][0][data] = val;
    }// for(data)
  }// for(plane)

  m_local_event_number = m_data[0][kTag][kEvent]; // refer to vme01

  // avoid multiple decode
  static int pre_event = 0;
  if( m_local_event_number==pre_event ) return false;
  pre_event = m_local_event_number;

  m_event_number++;
  m_spill_number = m_data[0][kTag][kSpill];
  //  if( m_local_event_number==1 ) m_spill_number++;

  return true;
}

//______________________________________________________________________________
void
RMAnalyzer::Print( const std::string& arg ) const
{
  static const std::string func_name("["+class_name+"::"+__func__+"()]");

  hddaq::cout << func_name << " " << arg << std::endl
	      << " Run# "    << std::setw(5) << m_run_number
	      << " Event# "  << std::setw(8) << m_event_number
	      << " LEvent# " << std::setw(5) << m_local_event_number
	      << " Spill# "  << std::setw(5) << m_spill_number
	      << std::endl << std::endl
	      << "_RM_ _____Event _____Spill ____Serial ______Time"
	      << "   _Lock" << std::endl;

  std::size_t w[nType] = { 10, 3 };
  for( std::size_t i=0; i<NumOfPlaneVmeRm; ++i ){
    hddaq::cout << "[" << std::setw(2) << std::right << i << "] ";
    for( std::size_t j=0; j<nType; ++j ){
      for( std::size_t k=0; k<nData; ++k ){
	if( ( j==kLock && k==kSerial ) || ( j==kLock && k==kTime ) )
	  continue;
	hddaq::cout << std::setw(w[j]) << m_data[i][j][k] << " ";
      }
    }
    hddaq::cout << std::endl;
  }
}
