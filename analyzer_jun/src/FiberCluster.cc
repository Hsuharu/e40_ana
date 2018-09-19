/**
 *  file: FiberCluster.cc
 *  date: 2017.04.10
 *
 */

#include "FiberCluster.hh"

#include <cmath>
#include <string>
#include <limits>

#include <std_ostream.hh>

#include "DebugCounter.hh"
#include "FiberHit.hh"
#include "FLHit.hh"

static const bool reject_nan = false;

namespace
{
  const std::string& class_name("FiberCluster");
}

//______________________________________________________________________________
FiberCluster::FiberCluster( void )
  : m_cluster_size(0)
{
  for ( int i=0; i<sizeFlagsFiber; ++i ){
    m_flag[i] = false;
  }
  debug::ObjectCounter::increase(class_name);
}

//______________________________________________________________________________
FiberCluster::~FiberCluster( void )
{
  m_hit_container.clear();
  debug::ObjectCounter::decrease(class_name);
}

//______________________________________________________________________________
FLHit*
FiberCluster::GetHit( int i ) const
{
  return m_hit_container.at(i);
}

//______________________________________________________________________________
bool
FiberCluster::GoodForAnalysis( bool status )
{
  bool ret = m_flag[gfastatus];
  m_flag[gfastatus] = status;
  return ret;
}

//______________________________________________________________________________
bool
FiberCluster::Calculate( void )
{
  static const std::string funcname("["+class_name+"::"+__func__+"()]");

  if( m_flag[Initialized] ){
    hddaq::cerr << "#E " << funcname << " "
		<< "Already initialied" << std::endl;
    return false;
  }

  if( 0 == (m_cluster_size = m_hit_container.size()) ){
    hddaq::cerr << "#E " << funcname << " "
		<< "No FiberHit in local container" << std::endl;
    return false;
  }

  calc();
  if(m_cluster_size == 0){
    //    std::cout << "FiberCluster is destroied" << std::endl;
    return false;
  }

  m_flag[Initialized] = true;

#ifdef DEBUG
  Debug();
#endif

  return true;
}

//______________________________________________________________________________
void
FiberCluster::calc( void )
{
  double mean_seg       = 0.;
  double mean_pos       = 0.;
  double mean_time      = std::numeric_limits<double>::quiet_NaN();
  double max_width      = 0.;
  double real_mean_time = 0.;
  int    cluster_id     = 0;

  for( int i=0; i<m_cluster_size; ++i ){
    if(reject_nan && isnan(m_hit_container.at(i)->GetWidth())){
      --m_cluster_size;
      continue;
    }
    
    mean_seg       += m_hit_container.at(i)->SegmentId();
    mean_pos       += m_hit_container.at(i)->GetPosition();
    real_mean_time += m_hit_container.at(i)->GetCTime();
    double time = m_hit_container.at(i)->GetCTime();
    if(isnan(mean_time)){
      mean_time = time;
    }else if( std::abs(time) < std::abs(mean_time) ){
      mean_time = time;
    }
    if( max_width < m_hit_container.at(i)->GetWidth() ){
      max_width = m_hit_container.at(i)->GetWidth();
    }
    cluster_id  += m_hit_container.at(i)->PairId();
  }

  mean_seg       /= double(m_cluster_size);
  mean_pos       /= double(m_cluster_size);
  real_mean_time /= double(m_cluster_size);

  m_mean_time      = mean_time;
  m_max_width      = max_width;
  m_mean_seg       = mean_seg;
  m_mean_pos       = mean_pos;
  m_real_mean_time = real_mean_time;
  m_cluster_id     = (m_cluster_size == 1) ? 2*cluster_id : cluster_id;
}

//______________________________________________________________________________
void
FiberCluster::Debug( void )
{
  hddaq::cout << "Used hit" << std::endl;
  for(int i = 0; i<m_cluster_size; ++i){
    m_hit_container.at(i)->Dump();
  }
}
