/**
 *  file: K18TransMatrix.hh
 *  date: 2017.04.10
 *
 */

#ifndef K18_TRANS_MATRIX_HH
#define K18_TRANS_MATRIX_HH

#include <string>

//______________________________________________________________________________
class K18TransMatrix
{
public:
  static K18TransMatrix&    GetInstance( void );
  static const std::string& ClassName( void );
  ~K18TransMatrix( void );

private:
  K18TransMatrix( void );
  K18TransMatrix( const K18TransMatrix& );
  K18TransMatrix& operator=( const K18TransMatrix& );

private:
  bool        m_is_ready;
  std::string m_file_name;

  enum NameX{ X, A, T, XX, XA, XT, AA, AT, TT, YY,
	      YB, BB, XXX, XXA, XXT, XAA, XAT, XTT, XYY, XYB,
	      XBB, AAA, AAT, ATT, AYY, AYB, ABB, TTT, TYY, TYB,
	      TBB,
	      size_NameX};
  enum NameY{ Y, B, YX, YA, YT, BX, BA, BT,
	      size_NameY};
  double m_X[size_NameX], m_Y[size_NameY];
  double m_U[size_NameX], m_V[size_NameY];

public:
  bool Initialize( void );
  bool Initialize( const std::string& file_name );
  bool IsReady( void ) const { return m_is_ready; }
  void SetFileName( const std::string& file_name ) { m_file_name = file_name; }
  bool Transport( double xin, double yin, double uin, double vin, double delta,
		  double & xout, double & yout, double & uout, double & vout ) const;
  bool CalcDeltaD2U( double xin, double yin, double uin, double vin,
		     double xout, double& yout, double& uout, double& vout,
		     double & delta1, double & delta2 ) const;

};

//______________________________________________________________________________
inline K18TransMatrix&
K18TransMatrix::GetInstance( void )
{
  static K18TransMatrix g_instance;
  return g_instance;
}

//______________________________________________________________________________
inline const std::string&
K18TransMatrix::ClassName( void )
{
  static std::string g_name("K18TransMatrix");
  return g_name;
}

#endif
