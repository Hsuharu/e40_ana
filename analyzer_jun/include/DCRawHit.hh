/**
 *  file: DCRawHit.hh
 *  date: 2017.04.10
 *
 */

#ifndef DC_RAW_HIT_HH
#define DC_RAW_HIT_HH

#include <cstddef>
#include <string>
#include <vector>

typedef std::vector<int> IntVec;

//______________________________________________________________________________
class DCRawHit
{
public:
  DCRawHit( int plane_id, int wire_id );
  ~DCRawHit( void );

private:
  int    m_plane_id;
  int    m_wire_id;
  IntVec m_tdc;
  IntVec m_trailing;
  bool   m_oftdc; // module tdc over flow

public:
  int  PlaneId( void ) const { return m_plane_id; }
  int  WireId( void )  const { return m_wire_id;  }
  void SetTdc( int tdc )        { m_tdc.push_back(tdc); }
  void SetTrailing( int tdc )   { m_trailing.push_back(tdc); }
  void SetTdcOverflow( int fl ) { m_oftdc = static_cast<bool>( fl ); }
  int  GetTdc( int nh )        const { return m_tdc[nh]; }
  int  GetTdcSize( void )      const { return m_tdc.size(); }
  int  GetTrailing( int nh )   const { return m_trailing[nh]; }
  int  GetTrailingSize( void ) const { return m_trailing.size(); }
  bool IsTdcOverflow( void )      const { return m_oftdc; }
  void Print( const std::string& arg="" ) const;
};

#endif
