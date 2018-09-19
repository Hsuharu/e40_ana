/**
 *  file: TrackMaker.hh
 *  date: 2017.04.10
 *
 */

#ifndef TRACK_MAKER_HH
#define TRACK_MAKER_HH

#include <string>
#include <vector>
#include <deque>

class DCPairHitCluster;
class DCLocalTrack;

#define KeepOrderAsMakeIndex

//______________________________________________________________________________
class TrackMaker
{
public:
  typedef std::vector<DCPairHitCluster*> ClusterList;
  typedef std::vector<int>               IndexList;
#ifdef KeepOrderAsMakeIndex
  typedef std::vector<ClusterList>::const_reverse_iterator  PlaneIterator;
#else
  typedef std::vector<ClusterList>::const_iterator          PlaneIterator;
#endif

public:
  TrackMaker( const std::vector<ClusterList>& candCont,
	      int minNumOfHits,
	      double maxCombi,
	      double maxChiSquare);
  virtual ~TrackMaker( void );

private:
  TrackMaker( const TrackMaker& );
  TrackMaker& operator =( const TrackMaker& );

protected:
  const std::vector<ClusterList>& m_candidates;
  const std::size_t               m_npp;
  std::deque<DCPairHitCluster*>   m_trackCandidate;
  std::vector<DCLocalTrack*>      m_trackList;
  int    m_nCombi;
  double m_maxChiSquare;
  double m_maxCombi;
  int    m_minNumOfHits;

public:
  virtual void  MakeTracks( std::vector<DCLocalTrack*>& trackList );

  inline double GetMaxChiSquare( void ) const;
  inline double GetMaxCombi( void ) const;
  inline int    GetMinNumOfHits( void ) const;
  inline int    GetNumOfCombi( void ) const;
  inline int    GetNumOfValidCombi( void ) const;
  inline void   SetMaxChiSquare( double maxChiSquare );
  inline void   SetMaxCombi( double maxCombi );
  inline void   SetMinNumOfHits( int minNumOfHits );

protected:
  virtual bool IsGood( const DCLocalTrack* track ) const;

private:
  std::vector<IndexList> MakeIndex( int ndim, const int *index1 );
  std::vector<IndexList> MakeIndex( int ndim, const std::vector<int>& index1 );
  DCLocalTrack*          MakeOneTrack( const std::vector<ClusterList>& CandCont,
				       const IndexList& combination );

};

//______________________________________________________________________________
inline double
TrackMaker::GetMaxChiSquare( void ) const
{
  return m_maxChiSquare;
}

//______________________________________________________________________________
inline double
TrackMaker::GetMaxCombi( void ) const
{
  return m_maxCombi;
}

//______________________________________________________________________________
inline int
TrackMaker::GetMinNumOfHits( void ) const
{
  return m_minNumOfHits;
}

//______________________________________________________________________________
inline int
TrackMaker::GetNumOfCombi( void ) const
{
  return m_nCombi;
}

//______________________________________________________________________________
inline void
TrackMaker::SetMaxChiSquare( double maxChiSquare )
{
  m_maxChiSquare = maxChiSquare;
}

//______________________________________________________________________________
inline void
TrackMaker::SetMaxCombi( double maxCombi )
{
  m_maxCombi = maxCombi;
}

//______________________________________________________________________________
inline void
TrackMaker::SetMinNumOfHits( int minNumOfHits )
{
  m_minNumOfHits = minNumOfHits;
}

#endif
