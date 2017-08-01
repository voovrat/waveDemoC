#ifndef FL_GRAPHICS_H
#define FL_GRAPHICS_H

#include "graphics.h"
#include <FL/fl_draw.H>


class FLGraphics : public IGraphics 
{
public:

    

    virtual void fillrect( int x, int y, int w, int h) ;
	virtual void setColor( Color c);
	virtual void setLineWidth( int lw);
	virtual void line( int x1,int y1, int x2, int y2);
	virtual void circle( int x, int y, int r);
	
};



#endif