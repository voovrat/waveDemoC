#ifndef MYWINDOW_H
#define MYWINDOW_H

#include "window.h"
#include "mysettings.h"
#include "view.h"
#include <string>

typedef void (AME::IView<MySettings>::*ViewCallbackFn)( Fl_Widget *);

struct ViewCallback 
{
  AME::IView<MySettings>  * view;
  ViewCallbackFn fn;

  ViewCallback( AME::IView<MySettings>  * _view
              , ViewCallbackFn _fn
              )
  {
      view = _view;
      fn = _fn;
  }  
};


class Fl_Button;

class MyWindow : public AME::Window<MySettings>
{
private:
  std::string sTitle;
  const char *pArgs[1];  

  static void run_view_method( Fl_Widget *sender, void *viewcallback );

  ViewCallback cbOnPause;
  ViewCallback cbOnExit;

  Fl_Button *bnPause;
  Fl_Button *bnExit;  

public:

  MyWindow( int w
          , int h
          , const char *window_title
          , AME::IView<MySettings> *view 
          , double dt = 0.1
          );

  virtual ~MyWindow();

  virtual int handle(int event);


protected:

  void constructWindow(); 
  void destructWindow();

};

#endif
