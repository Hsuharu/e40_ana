// -*- C++ -*-

#ifndef EXCEPTION_HH
#define EXCEPTION_HH

#include <exception>
#include <stdexcept>

#include <TString.h>

//______________________________________________________________________________
class Exception : public std::exception
{
public:
  static TString ClassName( void );
  Exception( const TString& msg );
  virtual ~Exception( void ) throw();

private:
  TString m_msg;

public:
  virtual void          hoge( const TString& arg="" ) const;
  virtual const Char_t* what( void ) const throw();
};

//______________________________________________________________________________
inline TString
Exception::ClassName( void )
{
  static TString g_name("Exception");
  return g_name;
}

#endif
