#ifndef GRAPHICS_H
#define GRAPHICS_H

struct Color 
{

    unsigned c;

    Color() {c=0;}

    Color( unsigned _c ) { c = _c; }
    Color(unsigned r, unsigned g, unsigned b, unsigned a = 0) 
    {
        c = (r<<24) | (g<<16) | (b<<8);
    }

    unsigned r() const { return c>>24;}
    unsigned g() const { return (c & 0xFF0000) >>16;}
    unsigned b() const { return (c & 0xFF00) >> 8;}

    static const Color BLACK ;//(0,0,0);
    static const Color WHITE;//(255,255,255);
    static const Color RED  ;//(255,0,0);
    static const Color GREEN;//(0,255,0);
    static const Color BLUE ;//(0,0,255);


};

struct P2 {
  
    P2(double _x,double _y) 
    {   x=(int)_x; 
        y=(int)_y;
    }

    int x,y;
};



class IGraphics 
{
	public:

		virtual void setColor( Color c) = 0;
		virtual void setLineWidth( int lw) = 0;

		virtual void line( int x1,int y1, int x2, int y2) = 0;
		virtual void circle( int x, int y, int r) = 0;

        virtual void fillrect( int x, int y, int w, int h) = 0;

		void line( P2 A, P2 B) { line(A.x, A.y, B.x, B.y); }
		void line( P2 A, P2 B, Color c) { setColor(c); line(A,B); }

		void circle( P2 C, int r) { circle(C.x, C.y, r); }
		void circle( P2 C, int r, Color c) { setColor(c); circle(C,r); }
};


#endif