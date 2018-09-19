/**
 *  file: TrackMaker.cc
 *  date: 2017.04.10
 *
 */

#include "TrackMaker.hh"

#include <cstdlib>
#include <iomanip>
#include <iostream>

#include <std_ostream.hh>

#include "DCLocalTrack.hh"
#include "DCLTrackHit.hh"
#include "DCPairHitCluster.hh"

namespace
{
  const std::string& class_name("TrackMaker");
}

//______________________________________________________________________________
TrackMaker::TrackMaker( const std::vector<ClusterList>& candCont,
			int minNumOfHits,
			double maxCombi,
			double maxChiSquare )
  : m_candidates(candCont),
    m_npp(candCont.size()),
    m_trackCandidate(),
    m_trackList(),
    m_nCombi(0),
    m_maxChiSquare(maxChiSquare),
    m_maxCombi(maxCombi),
    m_minNumOfHits(minNumOfHits)
{
}

//______________________________________________________________________________
TrackMaker::~TrackMaker( void )
{
}

//______________________________________________________________________________
void
TrackMaker::MakeTracks( std::vector<DCLocalTrack*>& trackList )
{
  static const std::string funcname("["+class_name+"::"+__func__+"]");

  std::vector<int> nCombi(m_npp);
  for( int i=0; i<m_npp; ++i ){
    nCombi[i] = m_candidates[i].size();
  }

  std::vector< std::vector<int> >
    CombiIndex = MakeIndex( m_npp, nCombi );
  const std::size_t nnCombi = CombiIndex.size();

  for( std::size_t i=0; i<nnCombi; ++i ){
    DCLocalTrack *track = MakeOneTrack( m_candidates, CombiIndex[i] );
    if( !track ) continue;
    if( track->GetNHit()>=m_minNumOfHits
	&& track->DoFit()
	&& track->GetChiSquare()<m_maxChiSquare ){
      trackList.push_back(track);
    }
    else
      delete track;
  }

  return;
}

//______________________________________________________________________________
bool
TrackMaker::IsGood( const DCLocalTrack* track ) const
{
  return
    (static_cast<int>(track->GetNHit())>=m_minNumOfHits)
    &&
    (const_cast<DCLocalTrack*>(track)->DoFit())
    &&
    (track->GetChiSquare()<m_maxChiSquare);
}

//______________________________________________________________________________
std::vector<TrackMaker::IndexList>
TrackMaker::MakeIndex( int ndim, const int *index1 )
{
  static const std::string func_name("["+class_name+"::"+__func__+"()]");

  if( ndim==1 ){
    std::vector<IndexList> index2;
    for( int i=-1; i<index1[0]; ++i ){
      IndexList elem(1,i);
      index2.push_back(elem);
    }
    return index2;
  }

  std::vector< std::vector<int> >
    index2 = MakeIndex( ndim-1, index1+1 );

  std::vector< std::vector<int> > index;
  int n2=index2.size();
  for( int j=0; j<n2; ++j ){
    for( int i=-1; i<index1[0]; ++i ){
      IndexList elem;
      int n3=index2[j].size();
      elem.reserve(n3+1);
      elem.push_back(i);
      for( int k=0; k<n3; ++k )
	elem.push_back(index2[j][k]);
      index.push_back(elem);
      int size1=index.size();
      if( size1>m_maxCombi ){
#if 0
	hddaq::cout << func_name << " too much combinations..." << std::endl;
#endif
	return std::vector<IndexList>();
      }
    }
  }

  return index;
}

//______________________________________________________________________________
std::vector<TrackMaker::IndexList>
TrackMaker::MakeIndex( int ndim, const IndexList& index1 )
{
  return MakeIndex( ndim, &(index1[0]) );
}

//______________________________________________________________________________
DCLocalTrack*
TrackMaker::MakeOneTrack( const std::vector<ClusterList>& CandCont,
			  const IndexList& combination )
{
  static const std::string func_name("["+class_name+"::"+__func__+"()]");

  DCLocalTrack *tp = new DCLocalTrack;

  for( std::size_t i=0; i<m_npp; ++i ){
    int m = combination[i];
    if( m<0 ) continue;
    DCPairHitCluster *cluster = CandCont[i][m];
    if( !cluster ) continue;
    int mm = cluster->NumberOfHits();
    for( int j=0; j<mm; ++j ){
      DCLTrackHit *hitp = cluster->GetHit(j);
      if( !hitp ) continue;
      tp->AddHit( hitp );
    }
#if 0
    hddaq::cout << func_name << ":" << std::setw(3)
		<< i << std::setw(3) << m  << " "
		<< CandCont[i][m] << " " << mm << std::endl;
#endif
  }
  return tp;
}
