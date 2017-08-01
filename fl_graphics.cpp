#include "fl_graphics.h"

#include <FL/fl_draw.H>


void FLGraphics::setColor( Color c) 
{
	fl_color( (Fl_Color) c.c );
}

void FLGraphics::setLineWidth( int lw) 
{
	fl_line_style(0, lw );	
}

void FLGraphics::line( int x1,int y1, int x2, int y2) 
{
	fl_line( x1, y1, x2, y2);
}

void FLGraphics::circle( int x, int y, int r) 
{
	fl_circle(x, y, r);
}


void FLGraphics::fillrect( int x, int y, int w, int h) 
{
	fl_rectf(x,y,w,h);

}