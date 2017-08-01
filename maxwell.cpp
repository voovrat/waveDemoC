#include "maxwell.h"

#include <algorithm>  // min, swap?

#include <iostream>

using namespace std;



Maxwell::Maxwell( const Dimension & d, const Steps & s , const Permutivity & p ) 
{
   size_t i;

   this->nx = d.nx;
   this->ny = d.ny;
   this->nz = d.nz;

   for(i=0;i<2;i++)
   {
      mE[i].resize(nx, ny, nz);
      mB[i].resize(nx, ny, nz);
   }
   
   Ecurr = &mE[0]; Enext = &mE[1];
   Bcurr = &mB[0]; Bnext = &mB[1];

   this->dr = s.dr;
   this->dt = s.dt;

   this->mu = p.mu;
   this->eps = p.eps; 
}


void Maxwell::step() 
{

   P3 dBdt, dEdt;

   double mueps = mu*eps;

   int i,j,k;


   for( i = 0; i<nx; i++)
   for( j = 0; j<ny; j++)
   for( k = 0; k<nz; k++)
   {
      // rotor (E ) = -dB/dt
      // rotor (B) = 1/c^2 dE/dt where c^2 = mu*eps

      dBdt = - Ecurr->rotor( i,j,k,dr);
      dEdt =  mueps * Bcurr->rotor( i,j,k,dr);

      (*Enext)(i,j,k) = (*Ecurr)(i,j,k) + dEdt * dt;
      (*Bnext)(i,j,k) = (*Bcurr)(i,j,k) + dBdt * dt;
   }

   std::swap( Ecurr, Enext );
   std::swap( Bcurr, Bnext );
}

   
// P3 Maxwell::grad2rot( P3 grad ) {

//    //      i  j  k
//    //det  dx dy dz  =  ( dEzdy - Eydz,  -Ezdx + Exdz,  Eydx - Exdy )
//    //     Ex Ey Ez

//    throw "TODO: implement Maxwell::grad2rot";
   
//    return new P3( 0,0,0);

// }  



