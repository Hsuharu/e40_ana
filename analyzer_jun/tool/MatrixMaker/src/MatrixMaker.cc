/**
 *  file: MatrixMaker.cc
 *  date: 2017.04.10
 *
 */

#include "MatrixMaker.hh"

#include <cstdlib>
#include <libgen.h>
#include <iomanip>
#include <iostream>
#include <cmath>
#include <vector>
#include <fstream>
#include <sstream>
#include <iterator>
#include <map>

namespace
{
  enum e_argv
    {
      k_process,
      k_param_file,
      k_argc
    };
  const std::string& input("orbit/K18MatrixDesignFFpFocus.D2U");
  const std::string& output("orbit/temp.in");
}

//______________________________________________________________________________
int
main( int argc,char** argv )
{
  const std::string& process = basename( argv[k_process] );
  if( argc!=k_argc ){
    std::cout << "#D Usage: " << process
	      << " [param_file]" << std::endl;
    return EXIT_FAILURE ;
  }

  const std::string& param_file = argv[k_param_file];
  std::ifstream ifs( argv[k_param_file] );

  if( ifs.fail() || !ifs.is_open() ){
    std::cerr << "#E [::main()] file open fail : " << param_file << std::endl;
    return EXIT_FAILURE ;
  }

  std::cout << "#D [::main()] file open : " << param_file << std::endl;

  std::map< std::string, double > mag_status;

  std::string line;
  while( ifs.good() && std::getline(ifs,line) ){
    if( line.empty() || line[0]=='#' ) continue;
    std::istringstream iss(line);
    std::istream_iterator<std::string> iss_begin(iss);
    std::istream_iterator<std::string> iss_end;
    std::vector<std::string> param( iss_begin, iss_end );
    if( param.size()<2 ) continue;
    const std::string& key = param[0];
    double value = std::strtod( param[1].c_str(), NULL );
    std::cout.precision(5);
    std::cout.setf( std::ios::fixed );
    std::cout << " key = "  << std::setw(12) << std::left << key
	      << " value = " << std::setw(10) << std::right << value
	      << std::endl;
    mag_status[param[0]] = value;
  }

  ifs.close();

  double mag_field_d4 = std::abs( mag_status["D4_Field"] );
  double current_Q10  = std::abs( mag_status["Q10"] );
  double current_Q11  = std::abs( mag_status["Q11"] );
  double current_Q12  = std::abs( mag_status["Q12"] );
  double current_Q13  = std::abs( mag_status["Q13"] );
  double mag_field_q[4];
  mag_field_q[0] = funcQ10( current_Q10 );
  mag_field_q[1] = funcQ11( current_Q11 );
  mag_field_q[2] = funcQ12( current_Q12 );
  mag_field_q[3] = funcQ13( current_Q13 );
  std::cout << "#D [::main()] calculate magnetic field" << std::endl;
  std::cout << " Q10 = " << std::setw(10) << std::right << current_Q10 << " [A] : "
	    << std::setw(8) << mag_field_q[0] << " [T]" << std::endl;
  std::cout << " Q11 = " << std::setw(10) << std::right << current_Q11 << " [A] : "
	    << std::setw(8) << mag_field_q[1] << " [T]" << std::endl;
  std::cout << " Q12 = " << std::setw(10) << std::right << current_Q12 << " [A] : "
	    << std::setw(8) << mag_field_q[2] << " [T]" << std::endl;
  std::cout << " Q13 = " << std::setw(10) << std::right << current_Q13 << " [A] : "
	    << std::setw(8) << mag_field_q[3] << " [T]" << std::endl;

  MakeOrbitFile( mag_field_q, mag_field_d4 );
  return 0;
}

//______________________________________________________________________________
void
MakeOrbitFile( double *mag, double mag_field_d4 )
{
  std::ifstream infile( input.c_str() );
  std::ofstream outfile( output.c_str() );
  double B    = mag_field_d4;
  double Brho = 4*B;
  double fg[4];
  double apparture = 0.1;
  for( int i=0; i<4; ++i )
    fg[i] = mag[i]/Brho/apparture;
#if 0
  std::cout<<"mag "<<mag[0]<<std::endl;
  std::cout<<"mag "<<mag[1]<<std::endl;
  std::cout<<"mag "<<mag[2]<<std::endl;
  std::cout<<"mag "<<mag[3]<<std::endl;
  std::cout<<B<<std::endl;
  std::cout<<Brho<<std::endl;
  std::cout<<"fg : "<<fg[0]<<std::endl;
  std::cout<<"fg : "<<fg[1]<<std::endl;
  std::cout<<"fg : "<<fg[2]<<std::endl;
  std::cout<<"fg : "<<fg[3]<<std::endl;
#endif
  std::stringstream ss[4];
  ss[0] << fg[0];
  ss[1] << fg[1]*(-1);
  ss[2] << fg[2];
  ss[3] << fg[3]*(-1);
  std::vector<std::vector<std::string> > inparam(32);
  int s=0;

  // std::cout << "#D [::MakeOrbitFile()] open file : " << input << std::endl;
  std::string line;
  while( infile.good() && std::getline(infile,line) ){
    if( line.empty() || line[0]=='#') continue;
    std::istringstream iss(line);
    std::istream_iterator<std::string> iss_begin(iss);
    std::istream_iterator<std::string> iss_end;
    std::vector<std::string> param(iss_begin,iss_end);
    for( std::size_t i=0; i<param.size(); ++i )
      inparam[s].push_back(param[i]);
    ++s;
  }
  infile.close();
  // std::cout << "#D [::MakeOrbitFile()] open file : " << output << std::endl;
  for( std::size_t j=0, m=inparam.size(); j<m; ++j ){
    for( std::size_t i=0, n=inparam[j].size(); i<n; ++i ){
      if(inparam[j][i]=="Q10") inparam[j+1][i]=ss[0].str();
      if(inparam[j][i]=="Q11") inparam[j+1][i]=ss[1].str();
      if(inparam[j][i]=="Q12") inparam[j+1][i]=ss[2].str();
      if(inparam[j][i]=="Q13") inparam[j+1][i]=ss[3].str();
      outfile<<inparam[j][i]<<" ";
      // std::cout << inparam[j][i] << " ";
    }
    outfile << std::endl;
    // std::cout << std::endl;
  }
  outfile.close();
}
