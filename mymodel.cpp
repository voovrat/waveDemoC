#include "mymodel.h"

#include <math.h>

#include "P3.h"


void MyModel::init() 
{
  initialCondition();
  boundaryConditions();
}

void MyModel::boundaryConditions()
{
 return;

   P3 p0(0,0,0);

   for ( size_t iy = 0; iy < Ny; iy++ ) 
   for ( size_t iz = 0; iz < Nz; iz++ ) 
   for ( size_t dx = 0; dx < 2;  dx++ ) // width of buffer zone is 2
   {
      m.E(dx, iy,iz) = p0;
      m.B(dx, iy,iz) = p0;
 
      m.E(Nx-dx-1,iy,iz) = p0;
      m.B(Nx-dx-1,iy,iz) = p0;
   }

}

void MyModel::init1()
{
  for (size_t iy = 0; iy < Ny; iy++) 
   for (size_t iz = 0; iz < Nz; iz++) 
   for (size_t ix = 0; ix < 20; ix++) 
   {                
      double u = ix/20*3.14;
      double s = 1; //sin(50*ix*dt);

//      m.E(ix, iy, iz ) = P3(0,  0, s *s*s*s*s*s*s*s);
    m.E(ix, iy, iz ) = P3(0,  s*sin(u), s*cos(u) );
  
    m.B(ix, iy, iz ) = P3::Zero; 
       //P3(0,  -s*cos(u), -sin(u) ); //new P3(0, Math.cos((t - 20 * ix) * dt),0);
      // E.f[ix][iy][iz] = P3.add(E.f[ix][iy][iz], new P3( 0,0,Math.exp(-(ix-32)*(ix-32)/1024)*ix/32 ) );
   }
}

void MyModel::init2()
{
   int dx = Nx/4;
   int dy = Ny/4;
   int dz = Nz/4;

  for (size_t iy = Ny/2 - dy; iy < Ny/2 + dy; iy++) 
   for (size_t iz = Nz/2 - dz; iz < Nz/2 + dz; iz++) 
   for (size_t ix = Nx/2 - dx ; ix < Nx/2 + dx; ix++) 
   {                
      double u = ix/20*3.14;
      double s = 1; //sin(50*ix*dt);

//      m.E(ix, iy, iz ) = P3(0,  0, s *s*s*s*s*s*s*s);
    m.E(ix, iy, iz ) = P3(0,  s*sin(u), s*cos(u) );
  
    m.B(ix, iy, iz ) = P3::Zero; 
       //P3(0,  -s*cos(u), -sin(u) ); //new P3(0, Math.cos((t - 20 * ix) * dt),0);
      // E.f[ix][iy][iz] = P3.add(E.f[ix][iy][iz], new P3( 0,0,Math.exp(-(ix-32)*(ix-32)/1024)*ix/32 ) );
   }
}


void MyModel::initialCondition() 
{
 init2();
 
   boundaryConditions();
}

void MyModel::step()
{
   m.step();
   //filter();
   boundaryConditions();
}


void MyModel::filter() 
{
   

   for(size_t ix=0; ix<Nx; ix++)
   for(size_t iy=0; iy<Ny; iy++)
   for(size_t iz=0; iz<Nz; iz++)
   {
      if( abs2( m.E(ix,iy,iz) ) + abs2( m.B(ix,iy,iz)) < FILTER_TRESHOLD )
      {
         m.E(ix,iy,iz) = P3::Zero;
         m.B(ix,iy,iz) = P3::Zero;
      }


   }

}

MyModel::MyModel()
: m( Dimension(Nx,Ny,Nz), Steps(dr,dt), Permutivity(1,1))
{}
