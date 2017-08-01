#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Box.H>
#include <FL/fl_draw.H>



#include "mymodel.h"
#include "mysettings.h"
#include "mycalculator.h"
#include "mywindow.h"
#include "myview.h"
#include "shared_object.h"


const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;

int main( int argc, const char **argv)
{

Fl::args(argc,(char **)argv);

   AME::SharedObject< MyModel > m;
   AME::SharedObject< MySettings > s;

   MyView v(&m,&s);
   MyWindow w(WINDOW_WIDTH,WINDOW_HEIGHT,"the window",&v,0.1);
   v.setWindow(&w);

   MyCalculator c(&m,&s);

   c.start();

Fl::run();

// here we appear when the window is closed --> inform calculator 
  v.stop();


return 0;
}


int minimal_main(int argc, const char **argv)
{
Fl::args(argc,(char **)argv);

Fl_Window *w = new Fl_Window(640,480);
//     Fl_Box *box = new Fl_Box(20,40,260,100,"Hello, World!");
//     box->box(FL_UP_BOX);
//     box->labelsize(36);
//     box->labelfont(FL_BOLD+FL_ITALIC);
//     box->labeltype(FL_SHADOW_LABEL);
w->end();

const char *window_args[] = { "Window Title" };
w->show(1,(char**)window_args);

Fl::run();



}
