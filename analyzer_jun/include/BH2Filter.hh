// -*- C++ -*-

#ifndef BH2_FILTER_HH
#define BH2_FILTER_HH

#include <string>
#include <vector>
#include <set>

#include "DCAnalyzer.hh"

class DCHit;
class HodoAnalyzer;

//______________________________________________________________________________
class BH2Filter
{
public:
  static BH2Filter&         GetInstance( void );
  static const std::string& ClassName( void );
  ~BH2Filter( void );

private:
  BH2Filter( void );
  BH2Filter( const BH2Filter& );
  BH2Filter& operator =( const BH2Filter& );

public:
  typedef std::vector< std::vector<DCHitContainer> > FilterList;
  typedef FilterList::iterator                       FIterator;
  // FilterList : [segment id] [plane id] [hit id]

  struct Param
  {
    // [plane]
    std::vector<Double_t> m_xmin;
    std::vector<Double_t> m_xmax;

    Param( void );
    ~Param( void );
    void Print( const TString& arg="" ) const;
  };

  enum EParam
    {
      kBH2Segment,
      kLayerID,
      kXMin,
      kXMax,
      kNParam
    };


private:
  Bool_t              m_is_ready;
  Bool_t              m_verbose;
  std::vector<Param>  m_param;
  const DCAnalyzer*   m_dc;
  const HodoAnalyzer* m_hodo;

public:
  void                         Apply( const HodoAnalyzer& hodo, const DCAnalyzer& dc, FilterList& cands );
  void                         Apply( Int_t T0Seg, const DCAnalyzer& dc, FilterList& cands );
  const std::vector<Double_t>& GetXmax( Int_t seg ) const;
  const std::vector<Double_t>& GetXmin( Int_t seg ) const;
  Bool_t                       Initialize( const TString& file_name );
  void                         SetVerbose( Bool_t verbose=true ) { m_verbose = verbose; }
  virtual void                 Print( Option_t* option="" ) const;

private:
  void                         BuildCandidates( std::set<Int_t>& seg, FilterList& cands );
};

//______________________________________________________________________________
inline BH2Filter&
BH2Filter::GetInstance( void )
{
  static BH2Filter g_instance;
  return g_instance;
}

//______________________________________________________________________________
inline const std::string&
BH2Filter::ClassName( void )
{
  static std::string g_name("BH2Filter");
  return g_name;
}

#endif
