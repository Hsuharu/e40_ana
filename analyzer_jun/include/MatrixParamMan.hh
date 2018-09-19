/**
 *  file: MatrixParamMan.hh
 *  date: 2017.04.10
 *
 */

#ifndef MATRIX_PARAM_MAN_HH
#define MATRIX_PARAM_MAN_HH

#include <vector>
#include <map>

//______________________________________________________________________________
class MatrixParamMan
{
public:
  static MatrixParamMan&    GetInstance( void );
  static const std::string& ClassName( void );
  ~MatrixParamMan( void );

private:
  MatrixParamMan( void );
  MatrixParamMan( const MatrixParamMan& );
  MatrixParamMan& operator =( const MatrixParamMan& );

private:
  typedef std::vector< std::vector<double> > Matrix2D;
  typedef std::vector< std::vector< std::vector<double> > > Matrix3D;
  bool        m_is_ready;
  std::string m_file_name_2d;
  std::string m_file_name_3d;
  Matrix2D    m_enable_2d;
  Matrix3D    m_enable_3d;

public:
  bool Initialize( void );
  bool Initialize( const std::string& filename_2d,
		   const std::string& filename_3d );
  bool IsAccept( std::size_t detA, std::size_t detB ) const;
  bool IsAccept( std::size_t detA, std::size_t detB, std::size_t detC ) const;
  bool IsReady( void ) const { return m_is_ready; }
  void Print2D( const std::string& arg="" ) const;
  void Print3D( const std::string& arg="" ) const;
  void SetMatrix2D( const std::string& file_name );
  void SetMatrix3D( const std::string& file_name );

};

//______________________________________________________________________________
inline MatrixParamMan&
MatrixParamMan::GetInstance( void )
{
  static MatrixParamMan g_instance;
  return g_instance;
}

//______________________________________________________________________________
inline const std::string&
MatrixParamMan::ClassName( void )
{
  static std::string g_name("MatixParamMan");
  return g_name;
}

#endif
