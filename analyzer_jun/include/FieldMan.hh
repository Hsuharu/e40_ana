/**
 *  file: FieldMan.hh
 *  date: 2017.04.10
 *
 */

#ifndef FIELD_MAN_HH
#define FIELD_MAN_HH

#include "ThreeVector.hh"
#include <string>
#include <vector>

class KuramaFieldMap;
class FieldElements;

typedef std::vector <FieldElements*> FEContainer;
typedef std::vector <FieldElements*>::const_iterator FEIterator;

//______________________________________________________________________________
class FieldMan
{
public:
  static FieldMan&          GetInstance( void );
  static const std::string& ClassName( void );
  ~FieldMan( void );

private:
  FieldMan( void );
  FieldMan( const FieldMan& );
  FieldMan & operator =( const FieldMan& );

private:
  bool            m_is_ready;
  std::string     m_file_name;
  KuramaFieldMap *m_kurama_map;
  FEContainer     m_element_list;

public:
  bool        Initialize( void );
  bool        Initialize( const char *file_name );
  bool        Initialize( const std::string& file_name );
  bool        IsReady( void ) const { return m_is_ready; }
  ThreeVector GetField( const ThreeVector& position ) const;
  ThreeVector GetdBdX( const ThreeVector& position ) const;
  ThreeVector GetdBdY( const ThreeVector& position ) const;
  ThreeVector GetdBdZ( const ThreeVector& position ) const;
  void        ClearElementsList( void );
  void        AddElement( FieldElements *element );
  void        SetFileName( const std::string& file_name ) { m_file_name = file_name; }
  double      StepSize( const ThreeVector& position,
			double default_step_size, double min_step_size ) const;
};

//______________________________________________________________________________
inline FieldMan&
FieldMan::GetInstance( void )
{
  static FieldMan g_instance;
  return g_instance;
}

//______________________________________________________________________________
inline const std::string&
FieldMan::ClassName( void )
{
  static std::string g_name("FieldMan");
  return g_name;
}

#endif
