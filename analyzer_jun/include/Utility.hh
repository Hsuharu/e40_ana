/**   -*- C++ -*-
 *
 *  file: Utility.hh
 *  date: 2017.06.17
 *
 */

#ifndef UTILITY_HH
#define UTILITY_HH

#include <TTimeStamp.h>

#include "UnpackerManager.hh"

//______________________________________________________________________________
namespace utility
{
  UInt_t     EBDataSize( void );
  TTimeStamp TimeStamp( void );
}

#endif
