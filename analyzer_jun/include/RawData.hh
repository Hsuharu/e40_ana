/**
 *  file: RawData.hh
 *  date: 2017.04.10
 *
 */

#ifndef RAW_DATA_HH
#define RAW_DATA_HH

#include "DetectorID.hh"
#include <vector>

class HodoRawHit;
class DCRawHit;

typedef std::vector<HodoRawHit*> HodoRHitContainer;
typedef std::vector<DCRawHit*>   DCRHitContainer;

//______________________________________________________________________________
class RawData
{
public:
  RawData( void );
  ~RawData( void );

private:
  RawData( const RawData& );
  RawData& operator=( const RawData& );

private:
  bool              m_is_decoded;
  HodoRHitContainer m_BH1RawHC;
  HodoRHitContainer m_BH2RawHC;
  HodoRHitContainer m_SACRawHC;
  HodoRHitContainer m_TOFRawHC;
  HodoRHitContainer m_HtTOFRawHC;
  HodoRHitContainer m_LCRawHC;
  std::vector<HodoRHitContainer> m_BFTRawHC;
  std::vector<HodoRHitContainer> m_SFTRawHC;
  HodoRHitContainer m_SCHRawHC;
  std::vector<HodoRHitContainer> m_FBT1RawHC;
  std::vector<HodoRHitContainer> m_FBT2RawHC;

  std::vector<DCRHitContainer> m_BcInRawHC;
  std::vector<DCRHitContainer> m_BcOutRawHC;
  std::vector<DCRHitContainer> m_SdcInRawHC;
  std::vector<DCRHitContainer> m_SdcOutRawHC;

  HodoRHitContainer m_ScalerRawHC;
  HodoRHitContainer m_TrigRawHC;
  HodoRHitContainer m_VmeCalibRawHC;

  HodoRHitContainer m_FpgaBH2MtRawHC;

public:
  void                     ClearAll( void );
  bool                     DecodeHits( void );
  bool                     DecodeCalibHits( void );

  const HodoRHitContainer& GetBH1RawHC( void ) const;
  const HodoRHitContainer& GetBH2RawHC( void ) const;
  const HodoRHitContainer& GetSACRawHC( void ) const;
  const HodoRHitContainer& GetTOFRawHC( void ) const;
  const HodoRHitContainer& GetHtTOFRawHC( void ) const;
  const HodoRHitContainer& GetLCRawHC( void ) const;

  const HodoRHitContainer& GetBFTRawHC( int plane ) const;
  const HodoRHitContainer& GetSFTRawHC( int plane ) const;
  const HodoRHitContainer& GetSCHRawHC( void ) const;
  const HodoRHitContainer& GetFBT1RawHC( int layer, int UorD ) const;
  const HodoRHitContainer& GetFBT2RawHC( int layer, int UorD ) const;

  const DCRHitContainer&   GetBcInRawHC( int layer ) const;
  const DCRHitContainer&   GetBcOutRawHC( int layer ) const;
  const DCRHitContainer&   GetSdcInRawHC( int layer ) const;
  const DCRHitContainer&   GetSdcOutRawHC( int layer ) const;

  const HodoRHitContainer& GetScalerRawHC( void ) const;
  const HodoRHitContainer& GetTrigRawHC( void ) const;
  const HodoRHitContainer& GetVmeCalibRawHC( void ) const;

  const HodoRHitContainer& GetFpgaBH2MtRawHC( void ) const;
};

//______________________________________________________________________________
inline const HodoRHitContainer&
RawData::GetBH1RawHC( void ) const
{
  return m_BH1RawHC;
}

//______________________________________________________________________________
inline const HodoRHitContainer&
RawData::GetBH2RawHC( void ) const
{
  return m_BH2RawHC;
}

//______________________________________________________________________________
inline const HodoRHitContainer&
RawData::GetSACRawHC( void ) const
{
  return m_SACRawHC;
}

//______________________________________________________________________________
inline const HodoRHitContainer&
RawData::GetTOFRawHC( void ) const
{
  return m_TOFRawHC;
}

//______________________________________________________________________________
inline const HodoRHitContainer&
RawData::GetHtTOFRawHC( void ) const
{
  return m_HtTOFRawHC;
}

//______________________________________________________________________________
inline const HodoRHitContainer&
RawData::GetLCRawHC( void ) const
{
  return m_LCRawHC;
}

//______________________________________________________________________________
inline const HodoRHitContainer&
RawData::GetBFTRawHC( int plane ) const
{
  if( plane<0 || plane>NumOfPlaneBFT-1 ) plane=0;
  return m_BFTRawHC[plane];
}

//______________________________________________________________________________
inline const HodoRHitContainer&
RawData::GetSFTRawHC( int plane ) const
{
  if( plane<0 || plane>NumOfPlaneSFT-1 ) plane=0;
  return m_SFTRawHC[plane];
}

//______________________________________________________________________________
inline const HodoRHitContainer&
RawData::GetSCHRawHC( void ) const
{
  return m_SCHRawHC;
}

//______________________________________________________________________________
inline const HodoRHitContainer&
RawData::GetFBT1RawHC( int layer, int UorD ) const
{
  if( layer<0 || layer>NumOfLayersFBT1-1 ) layer = 0;
  if( !(0 <= UorD && UorD <= 1)) layer = 0;
  return m_FBT1RawHC[2*layer + UorD];
}

//______________________________________________________________________________
inline const HodoRHitContainer&
RawData::GetFBT2RawHC( int layer, int UorD ) const
{
  if( layer<0 || layer>NumOfLayersFBT2-1 ) layer = 0;
  if( !(0 <= UorD && UorD <= 1)) layer = 0;
  return m_FBT2RawHC[2*layer + UorD];
}

//______________________________________________________________________________
inline const DCRHitContainer&
RawData::GetBcInRawHC( int layer ) const
{
  if( layer<0 || layer>NumOfLayersBcIn ) layer = 0;
  return m_BcInRawHC[layer];
}

//______________________________________________________________________________
inline const DCRHitContainer&
RawData::GetBcOutRawHC( int layer ) const
{
  if( layer<0 || layer>NumOfLayersBcOut ) layer = 0;
  return m_BcOutRawHC[layer];
}

//______________________________________________________________________________
inline const DCRHitContainer&
RawData::GetSdcInRawHC( int layer ) const
{
  if( layer<0 || layer>NumOfLayersSdcIn ) layer = 0;
  return m_SdcInRawHC[layer];
}

//______________________________________________________________________________
inline const DCRHitContainer&
RawData::GetSdcOutRawHC( int layer ) const
{
  if( layer<0 || layer>NumOfLayersSdcOut ) layer = 0;
  return m_SdcOutRawHC[layer];
}

//______________________________________________________________________________
inline const HodoRHitContainer&
RawData::GetScalerRawHC( void ) const
{
  return m_ScalerRawHC;
}

//______________________________________________________________________________
inline const HodoRHitContainer&
RawData::GetTrigRawHC( void ) const
{
  return m_TrigRawHC;
}

//______________________________________________________________________________
inline const HodoRHitContainer&
RawData::GetVmeCalibRawHC( void ) const
{
  return m_VmeCalibRawHC;
}

//______________________________________________________________________________
inline const HodoRHitContainer&
RawData::GetFpgaBH2MtRawHC( void ) const
{
  return m_FpgaBH2MtRawHC;
}

#endif
