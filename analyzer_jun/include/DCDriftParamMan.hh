/**
 *  file: DCDriftParamMan.hh
 *  date: 2017.04.10
 *
 */

#ifndef DC_DRIFT_PARAM_MAN_HH
#define DC_DRIFT_PARAM_MAN_HH

#include <map>
#include <string>
#include <vector>

struct DCDriftParamRecord;

//______________________________________________________________________________
struct DCDriftParamRecord
{
  int type, np;
  std::vector<double> param;
  DCDriftParamRecord( int t, int n, std::vector<double> p )
    : type(t), np(n), param(p)
  {}
};

//______________________________________________________________________________
class DCDriftParamMan
{
public:
  static DCDriftParamMan&   GetInstance( void );
  static const std::string& ClassName( void );
  ~DCDriftParamMan( void );

private:
  DCDriftParamMan( void );
  DCDriftParamMan( const DCDriftParamMan& );
  DCDriftParamMan& operator =( const DCDriftParamMan& );

private:
  typedef std::map<unsigned int, DCDriftParamRecord*> DCDriftContainer;
  typedef DCDriftContainer::const_iterator DCDriftIterator;
  bool             m_is_ready;
  std::string      m_file_name;
  DCDriftContainer m_container;

public:
  bool CalcDrift( int PlaneId, double WireId, double ctime, double & dt, double & dl ) const;
  bool Initialize( void );
  bool Initialize( const std::string& file_name );
  bool IsReady( void ) const { return m_is_ready; }
  void SetFileName( const std::string& file_name ) { m_file_name = file_name; }

private:
  void                ClearElements( void );
  static double       DriftLength1( double dt, double vel );
  static double       DriftLength2( double dt, double p1, double p2, double p3,
				    double st, double p5, double p6 );
  static double       DriftLength3( double dt, double p1, double p2, int PlaneId );
  static double       DriftLength4( double dt, double p1, double p2, double p3 );
  static double       DriftLength5( double dt, double p1, double p2, double p3,
				    double p4, double p5 );
  static double       DriftLength6( int PlaneId,
				    double dt, double p1, double p2, double p3,
				    double p4, double p5 );
  static double       DriftLength7( int PlaneId,
				    double dt, double p1, double p2, double p3,
				    double p4, double p5, double p6 );
  DCDriftParamRecord* GetParameter( int PlaneId, double WireId ) const;
};

//______________________________________________________________________________
inline DCDriftParamMan&
DCDriftParamMan::GetInstance( void )
{
  static DCDriftParamMan g_instance;
  return g_instance;
}

//______________________________________________________________________________
inline const std::string&
DCDriftParamMan::ClassName( void )
{
  static std::string g_name("DCDriftParamMan");
  return g_name;
}

#endif
