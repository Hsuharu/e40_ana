/**
 *  file: DCDriftParamMan.cc
 *  date: 2017.04.10
 *
 */

#include "DCDriftParamMan.hh"

#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <iterator>
#include <sstream>
#include <string>
#include <vector>

#include <std_ostream.hh>

#include "DeleteUtility.hh"

namespace
{
  const std::string& class_name("DCDriftParamMan");
}

//______________________________________________________________________________
DCDriftParamMan::DCDriftParamMan( void )
  : m_is_ready(false),
    m_file_name("")
{
}

//______________________________________________________________________________
DCDriftParamMan::~DCDriftParamMan( void )
{
  ClearElements();
}

//______________________________________________________________________________
void
DCDriftParamMan::ClearElements( void )
{
  del::ClearMap( m_container );
}

//______________________________________________________________________________
inline unsigned int
MakeKey( int plane, double wire )
{
  return (plane<<10) | int(wire);
}

//______________________________________________________________________________
inline void
DecodeKey( unsigned int key, int& plane, int& wire )
{
  wire  = key & 0x3ff;
  plane = key >> 10;
}

//______________________________________________________________________________
bool
DCDriftParamMan::Initialize( void )
{
  static const std::string func_name("["+class_name+"::"+__func__+"()]");

  if( m_is_ready ){
    hddaq::cerr << "#W " << func_name
		<< " already initialied" << std::endl;
    return false;
  }

  std::ifstream f( m_file_name.c_str() );
  if( !f.is_open() ){
    hddaq::cerr << "#E " << func_name
		<< " file open fail : " << m_file_name << std::endl;
    return false;
  }

  ClearElements();

  std::string line;
  while( std::getline( f, line ) ){
    if( line.empty() || line[0]=='#' ) continue;
    std::istringstream iss( line );
    // wid is not used at present
    // reserved for future updates
    int pid, wid, type, np;
    double param;
    std::vector<double> q;
    if( iss >> pid >> wid >> type >> np ){
      while( iss >> param )
	q.push_back( param );
    }
    if( q.size() < 2 ){
      hddaq::cerr << func_name << " format is wrong : " << line << std::endl;
      continue;
    }
    unsigned int key = MakeKey( pid, 0 );
    DCDriftParamRecord *record = new DCDriftParamRecord( type, np, q );
    if( m_container[key] ){
      hddaq::cerr << "#W " << func_name << " "
		  << "duplicated key is deleted : " << key << std::endl;
      delete m_container[key];
    }
    m_container[key] = record;
  }

  m_is_ready = true;
  return m_is_ready;
}

//______________________________________________________________________________
bool
DCDriftParamMan::Initialize( const std::string& file_name )
{
  m_file_name = file_name;
  return Initialize();
}

//______________________________________________________________________________
DCDriftParamRecord*
DCDriftParamMan::GetParameter( int PlaneId, double WireId ) const
{
  WireId = 0;
  unsigned int key = MakeKey( PlaneId, WireId );
  DCDriftParamRecord *record = 0;
  DCDriftIterator itr = m_container.find(key);
  if( itr!=m_container.end() ) record = itr->second;
  return record;
}

//______________________________________________________________________________
double
DCDriftParamMan::DriftLength1( double dt, double vel )
{
  return dt*vel;
}

//______________________________________________________________________________
double
DCDriftParamMan::DriftLength2( double dt, double p1, double p2, double p3,
			       double st, double p5, double p6 )
{
  double dtmax=10.+p2+1./p6;
  double dl;
  double alph=-0.5*p5*st+0.5*st*p3*p5*(p1-st)
    +0.5*p3*p5*(p1-st)*(p1-st);
  if( dt<-10. || dt>dtmax+10. )
    dl = -500.;
  else if( dt<st )
    dl = 0.5*(p5+p3*p5*(p1-st))/st*dt*dt;
  else if( dt<p1 )
    dl = alph+p5*dt-0.5*p3*p5*(p1-dt)*(p1-dt);
  else if( dt<p2 )
    dl = alph+p5*dt;
  else
    dl = alph+p5*dt-0.5*p6*p5*(dt-p2)*(dt-p2);
  return dl;
}

//______________________________________________________________________________
//DL = a0 + a1*Dt + a2*Dt^2
double
DCDriftParamMan::DriftLength3( double dt, double p1, double p2 ,int PlaneId )
{
  if (PlaneId>=1 && PlaneId <=4) {
    if (dt > 130.)
      return 999.9;
  } else if (PlaneId == 5) {
    if (dt > 500.)
      ;
  } else if (PlaneId>=6 && PlaneId <=11) {
    if (dt > 80.)
      return 999.9;
  } else if (PlaneId>=101 && PlaneId <=124) {
    if (dt > 80.)
      return 999.9;
  }

  return dt*p1+dt*dt*p2;
}

//______________________________________________________________________________
double
DCDriftParamMan::DriftLength4( double dt, double p1, double p2 ,double p3 )
{
  if (dt < p2)
    return dt*p1;
  else
    return p3*(dt-p2) + p1*p2;
}

//______________________________________________________________________________
double
DCDriftParamMan::DriftLength5( double dt, double p1, double p2,
			       double p3, double p4, double p5 )
{
  if (dt < p2)
    return dt*p1;
  else if (dt >= p2 && dt < p4)
    return p3*(dt-p2) + p1*p2;
  else
    return p5*(dt-p4) + p3*(p4-p2) + p1*p2;
}

//______________________________________________________________________________
////////////////Now using
// DL = a0 + a1*Dt + a2*Dt^2 + a3*Dt^3 + a4*Dt^4 + a5*Dt^5
double
DCDriftParamMan::DriftLength6( int PlaneId, double dt,
			       double p1, double p2 ,double p3, double p4, double p5 )
{
  static const std::string func_name("["+class_name+"::"+__func__+"()]");

  double dl = dt*p1+dt*dt*p2+p3*pow(dt, 3.0)+p4*pow(dt, 4.0)+p5*pow(dt, 5.0);

  switch( PlaneId ){
    // BC3&4
  case 113: case 114: case 115: case 116: case 117: case 118:
  case 119: case 120: case 121: case 122: case 123: case 124:
    //if( dt<-10. || dt>50. ) // Tight drift time selection
    if (dt<-10 || dt>80) // Loose drift time selection
      return 999.9;
    if( PlaneId==123 || PlaneId==124 ){
      if( dt>35 ) dt=35.;
      dl = dt*p1+dt*dt*p2+p3*pow(dt, 3.0)+p4*pow(dt, 4.0)+p5*pow(dt, 5.0);
    }else if( dt>32. ){
      dt = 32.;
    }
    if( dl>1.5 )
      return 1.5;
    if( dl<0. )
      return 0.;
    else
      return dl;
    break;
    // SDC1
  case 1: case 2: case 3: case 4: case 5: case 6:
    if( dt<-10 || 150<dt ) // Loose drift time selection
      return 999.9;
    // if( dt>120. ){
    //   dt = 120.;
    //   dl = dt*p1+dt*dt*p2+p3*pow(dt, 3.0)+p4*pow(dt, 4.0)+p5*pow(dt, 5.0);
    // }
    if( dl>3.0 || dt>120. )
      return 3.0;
    if( dl<0. )
      return 0.;
    else
      return dl;
    break;
  case 7: case 8: case 9:
    return 0.;
    // SDC2
  case 31: case 32: case 33: case 34:
    if( dt<-20. || dt>150. )
      return 999.9;
    if( dl>4.5 || dt>120. )
      return 4.5;
    if( dl<0. )
      return 0.;
    else
      return dl;
    break;
    //For SDC3
  case 35: case 36: case 37: case 38:
    if( dt<-20. || dt>300. )
      return 999.9;
    if( dl>10. || dt>250. )
      return 10.0;
    if( dl<0. )
      return 0.;
    else
      return dl;
    break;
  default:
    hddaq::cerr << "#E " << func_name << " "
		<< "invalid plane id : " << PlaneId << std::endl;
    std::exit( EXIT_FAILURE );
  }
}

//______________________________________________________________________________
bool
DCDriftParamMan::CalcDrift( int PlaneId, double WireId, double ctime,
			    double & dt, double & dl ) const
{
  static const std::string func_name("["+class_name+"::"+__func__+"()]");
  DCDriftParamRecord *record = GetParameter(PlaneId,WireId);
  if( !record ){
    hddaq::cerr << "#E " << func_name << " No record. "
		<< " PlaneId=" << std::setw(3) << PlaneId
		<< " WireId="  << std::setw(3) << WireId << std::endl;
    return false;
  }

  int type = record->type;
  // int np   = record->np;
  std::vector<double> p = record->param;

  dt = p[0]-ctime;

  switch( type ){
  case 1:
    dl=DriftLength1( dt, p[1] );
    return true;
  case 2:
    dl=DriftLength2( dt, p[1], p[2], p[3], p[4],
		     p[5], p[6] );
    return true;
  case 3:
    dl=DriftLength3( dt, p[1], p[2], PlaneId );
    return true;
  case 4:
    dl=DriftLength4( dt, p[1], p[2], p[3] );
    return true;
  case 5:
    dl=DriftLength5( dt, p[1], p[2], p[3], p[4], p[5] );
    return true;
  case 6:
    dl=DriftLength6( PlaneId, dt, p[1], p[2], p[3], p[4], p[5] );
    return true;
  default:
    hddaq::cerr << "#E " << func_name << " invalid type : " << type << std::endl;
    return false;
  }
}
