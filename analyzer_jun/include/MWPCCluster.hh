/**
 *  file: MWPCCluster.hh
 *  date: 2017.04.10
 *
 */

#ifndef MWPC_CLUSTER_HH
#define MWPC_CLUSTER_HH

#include <string>
#include <vector>

class DCHit;

//______________________________________________________________________________
class MWPCCluster
{
public:
  MWPCCluster( void );
  ~MWPCCluster( void );

private:
  MWPCCluster( const MWPCCluster& );
  MWPCCluster& operator =( const MWPCCluster& );

public:
  struct Statistics
  {
    double m_wire;
    double m_wpos;
    double m_leading;
    double m_trailing;
    double m_length;
    double m_totalLength;
    int    m_clusterSize;

    Statistics( void );
    ~Statistics( void );

    void Print(const std::string& arg="") const;
  };

private:
  std::vector<DCHit*> m_hits;
  Statistics          m_mean;
  Statistics          m_first;
  bool                m_status;

public:
  void   Add(DCHit* h);
  void   Calculate( void );
  int    GetClusterSize( void ) const;
  const Statistics&          GetFirst( void ) const;
  const std::vector<DCHit*>& GetHits( void ) const;
  const Statistics&          GetMean( void ) const;
  double GetMeanTime( void ) const;
  double GetMeanWire( void ) const;
  double GetMeanWirePos( void ) const;
  int    GetNumOfHits( void ) const;
  bool   IsGoodForAnalysis( void ) const;
  void   Print( const std::string& arg="" ) const;
  void   SetStatus( bool status );

};

#endif
