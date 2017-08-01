#ifndef MYVIEW_H
#define MYVIEW_H

#include "view.h"
#include "mymodel.h"
#include "mysettings.h"
#include "pane.h"
#include "fl_graphics.h"
#include "window.h"

class MyView : public AME::View<MyModel, MySettings >
{
protected:

  Pane p;
  FLGraphics mGraph;
  AME::Window<MySettings> *pWnd;
public:

   MyView( AME::SharedObject<MyModel> * model
         , AME::SharedObject<MySettings> * settings 
              );

   virtual ~MyView(); 

   virtual void timer();
   virtual void draw();

   virtual void keydown( int key );


   virtual void setWindow( AME::Window<MySettings> * wnd)
   {
   	pWnd = wnd;
   }


   virtual void stop()  // will be called form the main ( window ) process
                        // set bAborted and waits for bFinished in settings
   {
      mSettings.aborted = true;
      saveSettings();

      while( !mSettings.finished )  // wait for calculator to finish
      {
      	readSettings();
      }

   }


  // events 
   void OnPause( Fl_Widget * sender = NULL);
   void OnExit ( Fl_Widget * sender = NULL);


};

#endif
