#ifndef BH1_MATHC_HH
#define BH1_MATHC_HH

#include<string>
#include<vector>
#include<bitset>

#include<std_ostream.hh>

class BH1Match
{
public:
  virtual           ~BH1Match(void);
  static
  const std::string& ClassName();
  static
  BH1Match&          GetInstance(void);
  bool               Initialize(const std::string& file_name);
  bool               Judge(double bft_xpos, double bh1seg);
  void               Print(std::ostream& ost=hddaq::cout) const;
  void               SetVerbose();

  struct Param{
    double m_seg;
    double m_xmin;
    double m_xmax;

    Param(void);
    ~Param(void);
    void Print(std::ostream& ost=hddaq::cout) const;
  };

  enum EParam{
    kBH1Segment,
    kXMin,
    kXMax,
    kNParam
  };

private:
  BH1Match(void);
  BH1Match(const BH1Match& );
  BH1Match& operator =(const BH1Match& );

  enum EStatus{
    kReady,
    kVerbose,
    kNStatus
  };
  
  std::bitset<kNStatus> m_status;
  std::vector<Param>    m_param;
    
};

//_____________________________________________________________________________
inline
BH1Match&
BH1Match::GetInstance(void)
{
  static BH1Match g_instance;
  return g_instance;
}

//_____________________________________________________________________________
inline
const std::string&
BH1Match::ClassName(void)
{
  static std::string g_name("BH1Match");
  return g_name;
}

//_____________________________________________________________________________
inline
void
BH1Match::SetVerbose(void)
{
  m_status.set(kVerbose);
}

#endif
