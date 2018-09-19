#include<iostream>
#include<fstream>
#include<sstream>

#include"BH1Match.hh"
#include"DetectorID.hh"
#include"FuncName.hh"
#include"Exception.hh"

//_______________________________________________________________________
BH1Match::Param::Param(void)
  : m_xmin(0),
    m_xmax(0)
{

}

//_______________________________________________________________________
BH1Match::Param::~Param(void)
{

}

//_______________________________________________________________________
void
BH1Match::Param::Print(std::ostream& ost) const
{
  static const int w = 5;
  ost << std::right << std::setw(w) << m_seg << ":";
  ost << " ( " << std::right
      << std::setw(w) << m_xmin << " "
      << std::setw(w) << m_xmax << " )";
  ost << std::endl;
}

//_______________________________________________________________________
BH1Match::BH1Match(void)
  : m_param(2*NumOfSegBH1-1)
{
  m_status.reset();
}

//_______________________________________________________________________
BH1Match::~BH1Match(void)
{
  
}

//_______________________________________________________________________
bool
BH1Match::Initialize(const std::string& file_name)
{
  std::ifstream ifs(file_name);
  if(!ifs.is_open()){
    std::cerr << "#E: " << FUNC_NAME
	      << " No such parameter file(" << file_name << ")"
	      << std::endl;
    return false;
  }// file check

  std::string line;
  while(getline(ifs, line)){
    if( line.empty() )   continue;
    if( line[0] == '#' ) continue;
    std::istringstream to_word(line);
    std::istream_iterator<double> itr_begin(to_word);
    std::istream_iterator<double> itr_end;
    std::vector<double> cont(itr_begin, itr_end);
    if(cont.size() != kNParam){
      std::cerr << "#E: " << FUNC_NAME << "\n"
		<< " Number of parameters: " << cont.size() << "\n"
		<< " Required: " << kNParam << std::endl;
      throw Exception(FUNC_NAME + " invalid parameter.");
    }
    
    const double bh1seg = cont[kBH1Segment];
    const int i_bh1seg  = static_cast<int>(2*cont[kBH1Segment]);
    const double xmin   = cont[kXMin];
    const double xmax   = cont[kXMax];

    m_param.at(i_bh1seg).m_seg  = bh1seg;
    m_param.at(i_bh1seg).m_xmin = xmin;
    m_param.at(i_bh1seg).m_xmax = xmax;
  }// read line
  
  if( m_status[kVerbose] ) this->Print();
  m_status.set(kReady);

  return true;
}

//_______________________________________________________________________
bool
BH1Match::Judge(double bft_xpos, double bh1seg)
{
  if(!m_status[kReady]){
    throw Exception(FUNC_NAME + " Is not initialized.");
  }

  const int i_bh1seg = static_cast<int>(2*bh1seg);
  const double xmin  = m_param.at(i_bh1seg).m_xmin;
  const double xmax  = m_param.at(i_bh1seg).m_xmax;

  if(m_status[kVerbose]){
    hddaq::cout << "#D: " << FUNC_NAME << std::endl;
    m_param.at(i_bh1seg).Print();
    hddaq::cout << std::fixed;
    hddaq::cout << " BFT pos (" << std::setw(5)
		<< std::setprecision(2) << bft_xpos
		<< ") : ";
    if(xmin < bft_xpos && bft_xpos < xmax){
      hddaq::cout << "adopt" << std::endl;
    }else{
      hddaq::cout << "reject" << std::endl;
    }
  }

  return (xmin < bft_xpos && bft_xpos < xmax);
}

//_______________________________________________________________________
void
BH1Match::Print(std::ostream& ost) const
{
  ost << "#D: " << FUNC_NAME << "\n"
      << "     (xmin xmax)" << std::endl;
  for(const auto& param : m_param) param.Print(ost);
}
