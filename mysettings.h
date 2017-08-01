#ifndef MYSETTINGS_H
#define MYSETTINGS_H

class MySettings 
{
public:
  int tic;
  bool paused; 
  bool aborted;  // set by view to signal calculator to stop
  bool finished; // set by calculator to indicate that the run is over 

  MySettings() 
   : tic(0)
   , paused(false)
   , aborted(false)
   , finished(false)
    {}
};

#endif

