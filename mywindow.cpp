#include "mywindow.h"
#include "myview.h"

#include <iostream>
#include <stdio.h>

#include <FL/Fl_Button.H>

  MyWindow::MyWindow(
            int w
          , int h
          , const char *window_title
          , AME::IView<MySettings> *view 
          , double dt // = 0.1
          )
   : AME::Window<MySettings>( w, h, view, dt)
   , cbOnPause( view, (ViewCallbackFn)&MyView::OnPause )
   , cbOnExit( view,  (ViewCallbackFn)&MyView::OnExit )
   , bnPause(NULL)
   , bnExit(NULL)
  {
    constructWindow();
    this->end();
    sTitle = window_title;
    pArgs[0] = sTitle.c_str();
    show(1,(char **)pArgs);
  }

MyWindow::~MyWindow()
{
  destructWindow();
}

void MyWindow::destructWindow()
{
  #define DEL(x) if(x) delete x; x = NULL;

  DEL(bnPause)
  DEL(bnExit)

}

void MyWindow::run_view_method( Fl_Widget *sender, void *_callback )
{
  ViewCallback *cb = (ViewCallback *)_callback;
  (cb->view->*cb->fn)(sender);
}


void MyWindow::constructWindow() 
{

    bnPause = new Fl_Button(10,10,80,80,"Pause");
    bnPause->box(FL_UP_BOX);
    bnPause->labelsize(14);
    bnPause->callback( &MyWindow::run_view_method, &cbOnPause );


    bnExit = new Fl_Button(10,110,80,80,"Exit");
    bnExit->box(FL_UP_BOX);
    bnExit->labelsize(14);
    bnExit->callback( &MyWindow::run_view_method, &cbOnExit );
     
   // button->labelfont(FL_BOLD+FL_ITALIC);
   // button->labeltype(FL_SHADOW_LABEL);
}


int MyWindow::handle(int event)
{
  	switch( event )
  	{
  		// need for keyboard
  		case FL_FOCUS:
  			return 1;
  		case FL_UNFOCUS:
  			return 1;
  		case FL_KEYDOWN:
  			printf("KEY %d (%04X)\n",Fl::event_key(),Fl::event_key());
  			//std::cout << "KEY " << Fl::event_key() << "\n";
  			pView->keydown(Fl::event_key());
  			return 1;


  	};


    return Fl_Window::handle(event);

}