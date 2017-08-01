#ifndef AME_THREAD_H
#define AME_THREAD_H

#include <FL/Fl.H>
//#include <FL/Fl_Window.H>
//#include <FL/Fl_Box.H>
//#include <FL/fl_draw.H>

//#include <stdio.h>
//#include <pthread.h>
//#include <stdlib.h>

#include "shared_object.h"

//#include <math.h>

namespace AME {


class Thread 
{
protected:

  pthread_t mThread;

public:

  virtual ~Thread() {}

  void start() 
  {
     pthread_create(&mThread,NULL,&run_callback,this);
  }
  
protected:

  virtual void run() = 0;  

  static void *run_callback( void * context ) 
  {  Thread *_this = (Thread *)context;
     if(_this) _this->run();
     return NULL;
  }

};

} // namespace AME



#endif
