/**
 *  file: MstParamMan.hh
 *  date: 2017.04.10
 *
 */

#ifndef MST_PARAM_MAN_HH
#define MST_PARAM_MAN_HH

#include <vector>
#include <map>

#include<TROOT.h>

//______________________________________________________________________________
class MsTParamMan
{
public:
  static MsTParamMan&       GetInstance( void );
  static const std::string& ClassName( void );
  ~MsTParamMan( void );

private:
  MsTParamMan( void );
  MsTParamMan( const MsTParamMan& );
  MsTParamMan& operator =( const MsTParamMan& );

private:
  bool                               m_is_ready;
  std::size_t                        m_nA;
  std::size_t                        m_nB;
  std::vector< std::vector<double> > m_low_threshold;
  std::vector< std::vector<double> > m_high_threshold;

public:
  double GetLowThreshold( std::size_t detA, std::size_t detB ) const;
  double GetHighThreshold( std::size_t detA, std::size_t detB ) const;
  bool   Initialize( const std::string& filename );
  bool   IsAccept( std::size_t detA, std::size_t detB, int tdc ) const;
  bool   IsReady( void ) const { return m_is_ready; }
  void   Print( const std::string& arg="" ) const;
  void   Print( std::size_t detA, std::size_t detB, int tdc ) const;
};

//______________________________________________________________________________
inline MsTParamMan&
MsTParamMan::GetInstance( void )
{
  static MsTParamMan g_instance;
  return g_instance;
}

//______________________________________________________________________________
inline const std::string&
MsTParamMan::ClassName( void )
{
  static std::string g_name("MsTParamMan");
  return g_name;
}

#endif
