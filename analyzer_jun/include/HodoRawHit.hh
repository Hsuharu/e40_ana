/**
 *  file: HodoRawHit.hh
 *  date: 2017.04.10
 *
 */

#ifndef HODO_RAW_HIT_HH
#define HODO_RAW_HIT_HH

#include <cstddef>
#include <vector>
#include <iostream>

//______________________________________________________________________________
class HodoRawHit
{
public:
  HodoRawHit( int detector_id, int plane_id, int segment_id );
  ~HodoRawHit( void );

private:
  int              m_detector_id;
  int              m_plane_id;
  int              m_segment_id;
  std::vector<int> m_adc1;
  std::vector<int> m_adc2;
  // leading
  std::vector<int> m_tdc1;
  std::vector<int> m_tdc2;
  //trailing
  std::vector<int> m_tdc_t1;
  std::vector<int> m_tdc_t2;
  bool             m_oftdc; // module TDC overflow
  int              m_nhtdc;

public:
  void SetAdc1( int adc );
  void SetAdc2( int adc );
  // leading
  void SetTdc1( int tdc );
  void SetTdc2( int tdc );
  // trailing
  void SetTdcT1( int tdc );
  void SetTdcT2( int tdc );
  
  void SetAdcUp( int adc )    { SetAdc1(adc); }
  void SetAdcLeft( int adc )  { SetAdc1(adc); }
  void SetAdcDown( int adc )  { SetAdc2(adc); }
  void SetAdcRight( int adc ) { SetAdc2(adc); }
  
  // leading
  void SetTdcUp( int tdc )    { SetTdc1(tdc); }
  void SetTdcLeft( int tdc )  { SetTdc1(tdc); }
  void SetTdcDown( int tdc )  { SetTdc2(tdc); }
  void SetTdcRight( int tdc ) { SetTdc2(tdc); }
  // trailing
  void SetTdcTUp( int tdc )    { SetTdcT1(tdc); }
  void SetTdcTLeft( int tdc )  { SetTdcT1(tdc); }
  void SetTdcTDown( int tdc )  { SetTdcT2(tdc); }
  void SetTdcTRight( int tdc ) { SetTdcT2(tdc); }

  int  DetectorId( void )      const { return m_detector_id; }
  int  PlaneId( void )         const { return m_plane_id;    }
  int  SegmentId( void )       const { return m_segment_id;  }
  // for Multi-hit method
  void SetTdcOverflow( int fl ) { m_oftdc = static_cast<bool>( fl ); }
  int  GetNumOfTdcHits( void )   const { return m_nhtdc;       }
  int  GetAdc1( int i=0 )        const { return m_adc1.at(i);  }
  int  GetAdc2( int i=0 )        const { return m_adc2.at(i);  }
  // leading
  int  GetTdc1( int i=0 )        const { return m_tdc1.at(i);  }
  int  GetTdc2( int i=0 )        const { return m_tdc2.at(i);  }
  // trailing
  int  GetTdcT1( int i=0 )       const { return m_tdc_t1.at(i);  }
  int  GetTdcT2( int i=0 )       const { return m_tdc_t2.at(i);  }

  int  GetAdcUp( int i=0 )       const { return GetAdc1(i);    }
  int  GetAdcLeft( int i=0 )     const { return GetAdc1(i);    }
  int  GetAdcDown( int i=0 )     const { return GetAdc2(i);    }
  int  GetAdcRight( int i=0 )    const { return GetAdc2(i);    }

  // leading
  int  GetTdcUp( int i=0 )       const { return GetTdc1(i);    }
  int  GetTdcLeft( int i=0 )     const { return GetTdc1(i);    }
  int  GetTdcDown( int i=0 )     const { return GetTdc2(i);    }
  int  GetTdcRight( int i=0 )    const { return GetTdc2(i);    }
  // trailing
  int  GetTdcTUp( int i=0 )      const { return GetTdcT1(i);    }
  int  GetTdcTLeft( int i=0 )    const { return GetTdcT1(i);    }
  int  GetTdcTDown( int i=0 )    const { return GetTdcT2(i);    }
  int  GetTdcTRight( int i=0 )   const { return GetTdcT2(i);    }

  int  SizeAdc1( void ) const;
  int  SizeAdc2( void ) const;
  int  SizeTdc1( void ) const;
  int  SizeTdc2( void ) const;
  int  SizeTdcT1( void ) const;
  int  SizeTdcT2( void ) const;

  int  GetSizeAdcUp( void )    const { return SizeAdc1(); }
  int  GetSizeAdcLeft( void )  const { return SizeAdc1(); }
  int  GetSizeAdcDown( void )  const { return SizeAdc2(); }
  int  GetSizeAdcRight( void ) const { return SizeAdc2(); }

  // leading
  int  GetSizeTdcUp( void )    const { return SizeTdc1(); }
  int  GetSizeTdcLeft( void )  const { return SizeTdc1(); }
  int  GetSizeTdcDown( void )  const { return SizeTdc2(); }
  int  GetSizeTdcRight( void ) const { return SizeTdc2(); }

  // trailing
  int  GetSizeTdcTUp( void )    const { return SizeTdcT1(); }
  int  GetSizeTdcTLeft( void )  const { return SizeTdcT1(); }
  int  GetSizeTdcTDown( void )  const { return SizeTdcT2(); }
  int  GetSizeTdcTRight( void ) const { return SizeTdcT2(); }

  bool IsTdcOverflow( void )   const { return m_oftdc; }
  void Clear( void );
  void Print( const std::string& arg="" );
};

#endif
