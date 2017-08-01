#ifndef MAXWELL_H
#define MAXWELL_H

//import javax.swing.plaf.basic.BasicViewportUI;

#include "vector_field.h"


struct Dimension {
   int nx,ny,nz;
   Dimension(int _nx,int _ny,int _nz) : nx(_nx), ny(_ny), nz(_nz)  { }
};

struct Steps {
  double dr,dt;
   Steps(double _dr,double _dt) : dr(_dr), dt(_dt) { }
};


struct Permutivity {
   double eps,mu;
   Permutivity() {eps=1; mu=1;}
   Permutivity(double _eps,double _mu) : eps(_eps), mu(_mu) {}
};

class Maxwell {

protected:
   VectorField  mE[2];
   VectorField *Ecurr, *Enext;

   VectorField  mB[2];
   VectorField *Bcurr, *Bnext;

public:

   static constexpr double eps0 = 1.;
   static constexpr double mu0 = 1.;

   int nx,ny,nz;
   double dr,dt,mu,eps;

   #define DEFINE_GETTERS(FLD)                                                        \
   VectorField & FLD() {  return *FLD##curr; }                                        \
   const VectorField & FLD() const { return *FLD##curr; }                             \
   P3 & FLD(size_t ix, size_t iy, size_t iz) { return (*FLD##curr)(ix,iy,iz); }       \
   const P3 &FLD( size_t ix, size_t iy, size_t iz) const { return (*FLD##curr)(ix,iy,iz);}

   DEFINE_GETTERS(E)
   DEFINE_GETTERS(B)

   #undef DEFINE_GETTERS

   /// partial derivalive d2f[dim1][ix,iy,iz] / d[dim2]
   /// where dim1, dim2 in {'x','y','z'} 
   /// e.g.  partial( f, ix, iy, iz, 'x', 'y') -->  dfx/dy[ix,iy,iz] 
   double partial(  const vector3<P3> &f, int ix,int iy,int iz, char dim1, char dim2 );
   
      //      i  j  k
      //det  dx dy dz  =  ( dEzdy - Eydz,  -Ezdx + Exdz,  Eydx - Exdy )
      //     Ex Ey Ez
   P3 rotor( const vector3<P3> & E,int i,int j,int k );

   Maxwell( const Dimension & d, const Steps & s , const Permutivity & p );

   /// for all x,y,z: 
   /// rotor (E ) = -dB/dt
   /// rotor (B) = 1/c^2 dE/dt   where c^2 = mu*eps
   //// --> E+= dE/dt * dt,   B += dB/dt * dt
   void step();

   
//   P3 grad2rot( P3 grad );


};

#endif