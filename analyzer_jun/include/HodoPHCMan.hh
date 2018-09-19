/**
 *  file: HodoPHCMan.hh
 *  date: 2017.04.10
 *
 */

#ifndef HODO_PHC_MAN_HH
#define HODO_PHC_MAN_HH

#include <map>
#include <string>
#include <vector>

//______________________________________________________________________________
class HodoPHCParam
{
public:
  HodoPHCParam( int type, int np, std::vector<double> parlist );
  ~HodoPHCParam( void );

private:
  HodoPHCParam( const HodoPHCParam& right );
  HodoPHCParam& operator =( const HodoPHCParam& );

private:
  int                 m_type;
  int                 m_n_param;
  std::vector<double> m_param_list;

public:
  double DoPHC( double time, double de ) const;
  double DoRPHC( double time, double de ) const;

private:
  double type1Correction( double time, double de ) const;
  double type2Correction( double time, double de ) const; // For fiber
  double type1RCorrection( double time, double de ) const;
};

//______________________________________________________________________________
class HodoPHCMan
{
public:
  static HodoPHCMan&        GetInstance( void );
  static const std::string& ClassName( void );
  ~HodoPHCMan( void );

private:
  HodoPHCMan( void );
  HodoPHCMan( const HodoPHCMan& );
  HodoPHCMan& operator =( const HodoPHCMan& );

private:
  typedef std::map <int, HodoPHCParam *> PhcPContainer;
  typedef std::map <int, HodoPHCParam *>::const_iterator PhcPIterator;
  bool          m_is_ready;
  std::string   m_file_name;
  PhcPContainer m_container;

public:
  bool Initialize( void );
  bool Initialize( const std::string& file_name );
  bool IsReady( void ) const { return m_is_ready; }
  bool DoCorrection( int cid, int plid, int seg, int ud, double time,
                     double de, double& ctime ) const;
  bool DoRCorrection( int cid, int plid, int seg, int ud, double time,
                      double de, double& ctime ) const;
  void SetFileName( const std::string& file_name ) { m_file_name = file_name; }

private:
  void          ClearElements( void );
  HodoPHCParam* GetMap( int cid, int plid, int seg, int ud ) const;
};

//______________________________________________________________________________
inline HodoPHCMan&
HodoPHCMan::GetInstance( void )
{
  static HodoPHCMan g_instance;
  return g_instance;
}

//______________________________________________________________________________
inline const std::string&
HodoPHCMan::ClassName( void )
{
  static std::string g_name("HodoPHCMan");
  return g_name;
}

#endif
