/**
 *  file: VEvent.hh
 *  date: 2017.04.10
 *
 */

#ifndef VEVENT_HH
#define VEVENT_HH

//_____________________________________________________________________
class VEvent
{
public:
                VEvent( void );
  virtual      ~VEvent( void )           = 0;
  virtual bool  ProcessingBegin( void )  = 0;
  virtual bool  ProcessingEnd( void )    = 0;
  virtual bool  ProcessingNormal( void ) = 0;

};

#endif
