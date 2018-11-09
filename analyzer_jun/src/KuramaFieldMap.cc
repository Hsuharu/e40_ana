/**
 *  file: KuramaFieldMap.cc
 *  date: 2017.04.10
 *
 */

#include "KuramaFieldMap.hh"

#include <cmath>
#include <cstdlib>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>

#include <std_ostream.hh>

#include "ConfMan.hh"

namespace
{
  const std::string& class_name("KuramaFieldMap");
//  const ConfMan& gConf = ConfMan::GetInstance();
  const double& valueNMR  = ConfMan::Get<double>("FLDNMR");
  const double& valueCalc = ConfMan::Get<double>("FLDCALC");
}

//______________________________________________________________________________
KuramaFieldMap::KuramaFieldMap( const std::string& file_name )
  : m_is_ready(false),
    m_file_name(file_name),
    Nx(0), Ny(0), Nz(0)
{
}

//______________________________________________________________________________
KuramaFieldMap::~KuramaFieldMap( void )
{
  ClearField();
}

//______________________________________________________________________________
bool
KuramaFieldMap::Initialize( void )
{
  static const std::string func_name("["+class_name+"::"+__func__+"()]");

  std::ifstream ifs( m_file_name.c_str() );
  if( !ifs.is_open() ){
    hddaq::cerr << "#E " << func_name << " file open fail : "
		<< m_file_name << std::endl;
    return false;
  }

  if( m_is_ready ){
    hddaq::cerr << "#W " << func_name
		<< " already initialied" << std::endl;
    return false;
  }

  ClearField();

  if( !( ifs >> Nx >> Ny >> Nz >> X0 >> Y0 >> Z0 >> dX >> dY >> dZ ) ){
    hddaq::cerr << "#E " << func_name << " invalid format" << std::endl;
    return false;
  }

  if( Nx<0 || Ny<0 || Nz<0 ){
    hddaq::cerr << "#E " << func_name << " Nx, Ny, Nz must be positive" << std::endl;
    return false;
  }

  B.resize( Nx );
  for( int ix=0; ix<Nx; ++ix ){
    B[ix].resize( Ny );
    for( int iy=0; iy<Ny; ++iy ){
      B[ix][iy].resize( Nz );
    }
  }

  if( valueCalc==0. || !std::isfinite(valueCalc) ||
      valueNMR==0.  || !std::isfinite(valueNMR)  ){
    // hddaq::cerr << " KuramaField is zero : "
    // 	       << " Calc = " << valueCalc
    // 	       << " NMR = " << valueNMR << std::endl;
    return true;
  }
  const double factor    = valueNMR/valueCalc;

  double x, y, z, bx, by, bz;

  hddaq::cout << " reading fieldmap " << std::flush;

  int line = 0;
  while( ifs.good() ){
    if( line++%1000000==0 )
      hddaq::cout << "." << std::flush;
    ifs >> x >> y >> z >> bx >> by >> bz;
    int ix = int((x-X0+0.1*dX)/dX);
    int iy = int((y-Y0+0.1*dY)/dY);
    int iz = int((z-Z0+0.1*dZ)/dZ);
    if( ix>=0 && ix<Nx && iy>=0 && iy<Ny && iz>=0 && iz<Nz ){
      B[ix][iy][iz].x = bx*factor;
      B[ix][iy][iz].y = by*factor;
      B[ix][iy][iz].z = bz*factor;
    }
  }

  hddaq::cout << " done" << std::endl;
  m_is_ready = true;
  return true;
}

//______________________________________________________________________________
bool
KuramaFieldMap::GetFieldValue( const double pointCM[3],
			       double *BfieldTesla ) const
{
  static const std::string func_name("["+class_name+"::"+__func__+"()]");

  double xt = pointCM[0];
  double yt = pointCM[1];
  double zt = pointCM[2];

  int ix1, ix2, iy1, iy2, iz1, iz2;
  ix1 = int( (xt-X0)/dX );
  iy1 = int( (yt-Y0)/dY );
  iz1 = int( (zt-Z0)/dZ );

  double wx1, wx2, wy1, wy2, wz1, wz2;
  if( ix1<0 ) { ix1=ix2=0; wx1=1.; wx2=0.; }
  else if( ix1>=Nx-1 ) { ix1=ix2=Nx-1; wx1=1.; wx2=0.; }
  else { ix2=ix1+1; wx1=(X0+dX*ix2-xt)/dX; wx2=1.-wx1; }

  if( iy1<0 ) { iy1=iy2=0; wy1=1.; wy2=0.; }
  else if( iy1>=Ny-1 ) { iy1=iy2=Ny-1; wy1=1.; wy2=0.; }
  else { iy2=iy1+1; wy1=(Y0+dY*iy2-yt)/dY; wy2=1.-wy1; }

  if( iz1<0 ) { iz1=iz2=0; wz1=1.; wz2=0.; }
  else if( iz1>=Nz-1 ) { iz1=iz2=Nz-1; wz1=1.; wz2=0.; }
  else { iz2=iz1+1; wz1=(Z0+dZ*iz2-zt)/dZ; wz2=1.-wz1; }

  double bx1 = wx1*wy1*B[ix1][iy1][iz1].x + wx1*wy2*B[ix1][iy2][iz1].x
    + wx2*wy1*B[ix2][iy1][iz1].x + wx2*wy2*B[ix2][iy2][iz1].x;
  double bx2 = wx1*wy1*B[ix1][iy1][iz2].x + wx1*wy2*B[ix1][iy2][iz2].x
    + wx2*wy1*B[ix2][iy1][iz2].x + wx2*wy2*B[ix2][iy2][iz2].x;
  double bx  = wz1*bx1 + wz2*bx2;

  double by1 = wx1*wy1*B[ix1][iy1][iz1].y + wx1*wy2*B[ix1][iy2][iz1].y
    + wx2*wy1*B[ix2][iy1][iz1].y + wx2*wy2*B[ix2][iy2][iz1].y;
  double by2 = wx1*wy1*B[ix1][iy1][iz2].y + wx1*wy2*B[ix1][iy2][iz2].y
    + wx2*wy1*B[ix2][iy1][iz2].y + wx2*wy2*B[ix2][iy2][iz2].y;
  double by  = wz1*by1 + wz2*by2;

  double bz1 = wx1*wy1*B[ix1][iy1][iz1].z + wx1*wy2*B[ix1][iy2][iz1].z
    + wx2*wy1*B[ix2][iy1][iz1].z + wx2*wy2*B[ix2][iy2][iz1].z;
  double bz2 = wx1*wy1*B[ix1][iy1][iz2].z + wx1*wy2*B[ix1][iy2][iz2].z
    + wx2*wy1*B[ix2][iy1][iz2].z + wx2*wy2*B[ix2][iy2][iz2].z;
  double bz  = wz1*bz1 + wz2*bz2;

  //Default
  BfieldTesla[0] = bx;
  BfieldTesla[1] = by;
  BfieldTesla[2] = bz;

  return true;
}

//______________________________________________________________________________
void
KuramaFieldMap::ClearField( void )
{
  for( int ix=0; ix<Nx; ++ix ){
    for( int iy=0; iy<Ny; ++iy ){
      B[ix][iy].clear();
    }
    B[ix].clear();
  }
  B.clear();
}
