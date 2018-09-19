/**
 *  file: RMAnalyzer.hh
 *  date: 2017.04.10
 *
 */

#ifndef RM_ANALYZER_HH
#define RM_ANALYZER_HH

#include "DetectorID.hh"
#include <vector>

//______________________________________________________________________________
class RMAnalyzer
{
public:
  static RMAnalyzer& GetInstance( void );
  ~RMAnalyzer( void );

private:
  RMAnalyzer( void );
  RMAnalyzer( const RMAnalyzer& );
  RMAnalyzer& operator=( const RMAnalyzer& );

private:
  enum eType { kTag, kLock, nType };
  enum eData { kEvent, kSpill, kSerial, kTime, nData };
  int  m_run_number;
  int  m_event_number;
  int  m_local_event_number; // reset in each spill
  int  m_spill_number;
  std::vector< std::vector< std::vector<unsigned int> > > m_data;
  // m_data[i][j][k] : three dimensional vector
  //    i : plane of VME-RM in digit_data.xml
  //    j : eType / Tag or Lock Bit
  //    k : eData / Event, Spill, Serial or Time

public:
  void Clear( void );
  bool Decode( void );
  int  RunNumber( void )        const { return m_run_number;         }
  int  EventNumber( void )      const { return m_event_number;       }
  int  LocalEventNumber( void ) const { return m_local_event_number; }
  int  SpillNumber( void )      const { return m_spill_number;       }
  // each tag
  int  EventNumber( int i ) const;
  int  SpillNumber( int i ) const;
  int  Serial( int i ) const;
  int  Time( int i ) const;
  // each lock bit
  bool LockBitEventNumber( int i ) const;
  bool LockBitSpillNumber( int i ) const;


  void Print( const std::string& arg="" ) const;
};

//______________________________________________________________________________
inline RMAnalyzer&
RMAnalyzer::GetInstance( void )
{
  static RMAnalyzer g_instance;
  return g_instance;
}

//______________________________________________________________________________
inline int
RMAnalyzer::EventNumber( int i ) const
{
  if( i<0 || i>=(int)m_data.size() ) return -1;
  return m_data[i][kTag][kEvent];
}

//______________________________________________________________________________
inline int
RMAnalyzer::SpillNumber( int i ) const
{
  if( i<0 || i>=(int)m_data.size() ) return -1;
  return m_data[i][kTag][kSpill];
}

//______________________________________________________________________________
inline int
RMAnalyzer::Serial( int i ) const
{
  if( i<0 || i>=(int)m_data.size() ) return -1;
  return m_data[i][kTag][kSerial];
}

//______________________________________________________________________________
inline int
RMAnalyzer::Time( int i ) const
{
  if( i<0 || i>=(int)m_data.size() ) return -1;
  return m_data[i][kTag][kTime];
}

//______________________________________________________________________________
inline bool
RMAnalyzer::LockBitEventNumber( int i ) const
{
  if( i<0 || i>=(int)m_data.size() ) return false;
  return ( m_data[i][kLock][kEvent]==1 );
}

//______________________________________________________________________________
inline bool
RMAnalyzer::LockBitSpillNumber( int i ) const
{
  if( i<0 || i>=(int)m_data.size() ) return false;
  return ( m_data[i][kLock][kSpill]==1 );
}

#endif
