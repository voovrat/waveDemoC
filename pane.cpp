#include "pane.h"
    
Pane::Pane( int nx,int ny,int nz,Color _basicColor,int radius )
{
    init(nx,ny,nz,_basicColor,radius);
}

void Pane::init(int nx,int ny,int nz,Color _basicColor,int radius)
{
    R = radius;
    cGridColor = _basicColor;
    Nx = nx; Ny =ny; Nz = nz;
}


void Pane::drawFields( IGraphics * g) 
{
    for( auto vf : flist )
        drawVectorField(vf,g);
 }

void Pane::drawGrid( IGraphics * g) 
{

    for(int iy=Ny-1;iy>=0;iy--) 
    {
        g->setColor( layerColor(cGridColor, iy) );
        int r = (int) (R * layerScale(iy));
        for(int ix=0; ix<Nx;ix++) 
        {
            for(int iz=0;iz<Nz;iz++) 
            {
                P2 p2= index2point(ix,iy,iz);
                g->circle(p2, r);
            }//iz

        }//ix
    }//iy
}


void Pane::draw( IGraphics * g)
{
    g->setColor(Color::BLACK);
    g->fillrect(0,0,800,600);


  //  drawGrid(g);
    drawFields(g);
}


void Pane::drawVectorField(const ColorField  & cf, IGraphics *g) {

    g->setLineWidth(cf.lw);

  
//        Graphics2D g2 = (Graphics2D) g;
//        g2.setStroke(new java.awt.BasicStroke(cf.lw));
//    g2.draw(new java.awt.geom.Line2D.Float(30, 20, 80, 90));

    for(int iy=Ny-1;iy>=0;iy--) {

       // g->setColor( Color(cf.c.r(),cf.c.g(),cf.c.b(), (int) (255*layerScale(iy)) ) );
        g->setColor( layerColor( cf.c, iy));
//
//  int r = (int) (R * layerScale(iy));
        for(int ix=0; ix<Nx;ix++) {
            for(int iz=0;iz<Nz;iz++) {
                P3 d= cf.v->get(ix,iy,iz);
                P2 A = index2point(ix,iy,iz);
                P2 B = index2point(ix + d.x() * SCALEFX,iy+d.y() * SCALEFY,iz+d.z() * SCALEFZ);
                g->line(A,B);
            //    P2 p2= index2point(ix,iy,iz);
            //    g.fillOval(p2.x,p2.y,r,r);
            }

        }

    }

}

