#ifndef AME_WINDOW_H
#define AME_WINDOW_H

#include <FL/Fl.H>

#include <FL/Fl_Window.H>
#include "view.h"

namespace AME {

class WindowBase : public Fl_Window 
{
public:

  WindowBase( int w, int h) : Fl_Window(w,h) {}
  virtual ~WindowBase() {}

  virtual void draw_content() = 0 ;
  virtual void draw();  // creates memory buffer to avoid blinking
};


template<class Settings>
class Window  : public WindowBase
{
protected:
  IView<Settings> *pView;
  double dTic;
  
public:

  Window( int w, int h, IView<Settings> *parent, double dt )
      : WindowBase(w,h)
      , pView(parent)
  {
    dTic = dt;
    Fl::repeat_timeout(dTic,&timer_callback,this);
 
  }

  virtual ~Window() {}

protected:

  static void timer_callback( void * wnd)  
  {
    Window<Settings> *_this = (Window<Settings> *)(wnd);
    _this->pView->timer();
    _this->redraw();    
    Fl::repeat_timeout(_this->dTic,&timer_callback,_this);
  }

 virtual void draw_content() 
 {
    pView->draw();
 }

}; // window

} // AME

#endif

