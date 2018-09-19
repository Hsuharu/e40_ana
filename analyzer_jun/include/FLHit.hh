/**
 *  file: FLHit.hh
 *  date: 2017.04.10
 *
 */

#ifndef FL_HIT_HH
#define FL_HIT_HH

#include "FiberHit.hh"
#include <vector>

//______________________________________________________________________________
class FLHit
{
public:
  // One side readout method (BFT, SFT, SCH)
  FLHit( FiberHit* ptr, int index );
  // Both side readout method (FBH)
  FLHit( FiberHit* ptr1, FiberHit* ptr2,
	 int index1, int index2);
  ~FLHit( void );

private:
  FiberHit *m_hit_u;
  FiberHit *m_hit_d;
  int       m_nth_hit_u;
  int       m_nth_hit_d;
  double    m_leading;
  double    m_trailing;
  double    m_time;
  double    m_ctime;
  double    m_width;
  bool      m_flag_fljoin;

public:
  double GetLeading( void )  const { return m_leading;  }
  double GetTrailing( void ) const { return m_trailing; }
  double GetTime( void )     const { return m_time;     }
  double GetCTime( void )    const { return m_ctime;    }
  double GetWidth( void )    const { return m_width;    }
  double GetPosition( void ) const { return m_hit_u->GetPosition(); }
  int    PairId( void )      const { return m_hit_u->PairId();      }
  double SegmentId( void )   const { return m_hit_u->SegmentId();   }
  void   SetJoined( void )         { m_flag_fljoin = true;          }
  bool   Joined( void )      const { return m_flag_fljoin;          }
  void   Dump( void )              { Debug();                       }

  friend class FiberHit;

private:
  FLHit( void );
  FLHit(const FLHit& object);
  FLHit& operator =(const FLHit& object);

  void Initialize( void );

  void Debug( void )
  {
    std::cout << "plid " << m_hit_u->PairId() << " ";
    std::cout << "Pos "  << GetPosition()   << " ";
    std::cout << "Time " << GetCTime()      << std::endl;
  }

};

#endif
