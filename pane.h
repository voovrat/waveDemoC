#ifndef PANE_H
#define PANE_H

#include "graphics.h"
#include "vector_field.h"
#include <list>

class Pane  // extends JPanel implements ActionListener
{

private:    
    
    int R;
    
    static constexpr double SCALEX = 1;  // 0.1
    static constexpr double SCALEY = 0.4;  // 2
    static constexpr double SCALEZ = 1;  // 2

    static constexpr double SCALEFX = 1;
    static constexpr double SCALEFY = 0.3;
    static constexpr double SCALEFZ = 1;

    static constexpr double DX  = 20*SCALEX;
    static constexpr double DYz=14.142 * 2 * SCALEY;
    static constexpr double DYx = 11.1 * 2 * SCALEY;
    static constexpr double DZ  = 20*SCALEZ;

    static constexpr double ORIGX = 0;
    static constexpr double ORIGY = 580;

    static constexpr int W = 700;
    static constexpr int H = 600;

    int Nx, Ny, Nz;
    Color cGridColor;


public:

    static int w() { return W; }
    static int h() { return H; }

    struct ColorField {
        Color c;
        const VectorField *v;
        int lw;
        ColorField(const VectorField *_v,Color _c,int _lw) {v=_v; c=_c; lw=_lw; }
    };

    std::list<ColorField> flist;

    
    Pane(int nx = 0,int ny = 0,int nz = 0,Color _basicColor = Color::WHITE ,int radius = 5);
    
    void init(int nx,int ny,int nz,Color _basicColor = Color::WHITE ,int radius = 5);
    
    //
    //                 *
    //               /
    //ORIGY  *------*----
    //     ix*DX+iy*DY
    private:

     static P2 index2point(double ix,double iy, double iz) {
        return P2( ix * DX + ORIGX  + iy*DYx,  ORIGY - iz*DZ - iy*DYz  );
    }

    double layerScale(int iy) 
    {
        return (double)(Ny-iy)/Ny;//(double)(Ny-iy)/Ny;
    }


    Color layerColor(Color basicColor, int iy)
    {

        double sc = layerScale(iy);
        int R = (int)(basicColor.r()*sc);
        int G = (int)(basicColor.g()*sc);
        int B = (int)(basicColor.b()*sc);
        int A = (int)(255*sc);

        return Color(R,G,B,A);
    }


    void drawFields( IGraphics * g );  
  

    void drawGrid( IGraphics * g); 
  

public:

    void draw( IGraphics * g);
   
    void addField(const VectorField *v,Color c,int lw = 1) {
        flist.push_back(ColorField(v,c,lw));
    }

    void clearFields() { flist.clear(); }


    void drawVectorField(const ColorField  & cf, IGraphics *g);

};

#endif 
