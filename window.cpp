#include "window.h"

#include <FL/fl_draw.H>  // offscreen 

void AME::WindowBase::draw()
{


#define Window ::Window  

Fl_Offscreen offscreen = fl_create_offscreen(w(),h());
fl_begin_offscreen(offscreen); 

   Fl_Window::draw();
 draw_content();

 fl_end_offscreen();
 fl_copy_offscreen(0,0,w(),h(),offscreen,0,0);
 fl_delete_offscreen(offscreen);

 #undef Winow
}
