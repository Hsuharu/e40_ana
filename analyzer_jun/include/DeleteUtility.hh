/**
 *  file: DeleteUtility.hh
 *  date: 2017.04.10
 *
 */

#ifndef DELETE_UTILITY_HH
#define DELETE_UTILITY_HH

#include <algorithm>
#include <iterator>
#include <signal.h>
#include <vector>

//______________________________________________________________________________
namespace del
{
  //______________________________________________________________________________
  struct DeleteFuntion
  {
    template <typename T>
    void operator ()( T*& p ) const
    {
      delete p;
      p = 0;
    }
  };

  //______________________________________________________________________________
  template <typename T>
  inline void DeleteObject( T*& p )
  {
    delete p;
    p = 0;
  }

  //______________________________________________________________________________
  template <typename Container>
  inline void ClearContainer( Container& c, bool ownership=true )
  {
    if( ownership )
      std::for_each( c.begin(), c.end(), DeleteFuntion() );
    c.clear();
  }

  //______________________________________________________________________________
  template <typename Container>
  inline void DeleteObject( Container& c, bool ownership=true )
  {
    ClearContainer(c,ownership);
  }

  //______________________________________________________________________________
  template <typename Container>
  inline void ClearContainerAll( Container& c, bool ownership=true )
  {
    typename Container::iterator itr, itr_end=c.end();
    for( itr=c.begin(); itr!=itr_end; ++itr )
      ClearContainer( *itr, ownership );
  }

  //______________________________________________________________________________
  template <typename Map>
  inline void ClearMap( Map& m, bool ownership=true )
  {
    typename Map::const_iterator itr, end=m.end();
    if( ownership ){
      for( itr=m.begin(); itr!=end; ++itr ){
	delete itr->second;
      }
    }
    m.clear();
  }
}


#endif
