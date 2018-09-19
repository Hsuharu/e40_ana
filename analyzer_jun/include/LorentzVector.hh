/**
 *  file: LorentzVector.hh
 *  date: 2017.04.10
 *
 */

#ifndef LORENTZ_VECTOR_HH
#define LORENTZ_VECTOR_HH

#include <ostream>

#include <TLorentzVector.h>
typedef TLorentzVector LorentzVector;

//______________________________________________________________________________
inline
std::ostream&
operator <<( std::ostream& ost,
	     const LorentzVector& v )
{
  ost << "(" << v.Px() << ", " << v.Py()
      << ", " << v.Pz() << ", " << v.E() << " )";
  return ost;
}

#endif
