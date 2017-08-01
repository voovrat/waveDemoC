#ifndef VECTOR_FIELD_H
#define VECTOR_FIELD_H 

#include "vectorN.h"
#include "P3.h"

#include <algorithm>

using namespace std;

class VectorField 
{
protected:
    vector3<P3> mField;
    int nX,nY,nZ;
public:

    operator vector3<P3> &() { return mField; }
    operator const vector3<P3> &() const { return mField; }

    size_t nx() const { return nX; }
    size_t ny() const { return nY; }
    size_t nz() const { return nZ; }

    const P3 & get(size_t n1, size_t n2, size_t n3) const 
    {
       return mField[n1][n2][n3];
    }

    P3 & operator()(size_t n1, size_t n2, size_t n3) 
    {
        return mField[n1][n2][n3];
    }


    VectorField() { nX = nY = nZ = 0;}

    VectorField(size_t nx, size_t ny, size_t nz)
    {
        resize(nx,ny,nz);
    }

    void resize( size_t nx, size_t ny, size_t nz) 
    {
        mField.assign(nx,ny,nz,P3(0,0,0));
        nX = nx; nY = ny; nZ = nz;
    }



    // x[-1]  x0   x[+1]
    // y[-1]  y0   y[+1]
    // we draw parabola through the points
    // and calc the derivative at x0

    //parabola  a(x-x0)^2 + b(x-x0) + c

    // x-1:   a(x[-1]-x0)^2 + b(x[-1]-x0) + c = y[-1]
    //  x0:                                 c = y0
    // x+1:   a(x[+1]-x0)^2 + b(x[+1]-x0) + c = y[+1]

    // now grid step is d
    //        a d^2  - b d + c = y[-1]
    //                       c = y0     + , -
    //        a d^2  + b d + c = y[+1]

    //        2 a d^2  = ( y[-1] - c + y[+1] - c)
    //          a = 0.5/d^2 * ( y[-1] + y[+1] - 2y0 )
    //
    //        2 b d = ( y[+1] - c - y[-1] + c)
    //          b =   0.5/d ( y[+1] - y[-1])

    //  derivative is 2a (x - x0) + b
    //  at x = x0      derivative is b = 0.5/dr ( y[+1] - y[-1])

    // dfxi/dxj

    //  (x+1 + x0)/2   - (x0-x-1)/2

    int u(int x,int n) { return (x<n) ? x : x-n; }
    int d(int x,int n) { return (x<0) ? x+n : x; }
 

    double partial(  int ix, int iy, int iz, char dim1, char dim2, double dr ) 
    {
       switch(dim2) {
          case 'x': return (mField[u(ix+1,nX)][iy][iz].xi(dim1) - mField[d(ix-1,nX)][iy][iz].xi(dim1) )/(2*dr);
          case 'y': return (mField[ix][u(iy+1,nY)][iz].xi(dim1) - mField[ix][d(iy-1,nY)][iz].xi(dim1) )/(2*dr);
          case 'z': return (mField[ix][iy][u(iz+1,nZ)].xi(dim1) - mField[ix][iy][d(iz-1,nZ)].xi(dim1) )/(2*dr);
       }
    }

    double partialx(  int ix, int iy, int iz, char dim1, char dim2, double dr ) 
    {
       switch(dim2) {
          case 'x': return (mField[min(ix+1,nX-1)][iy][iz].xi(dim1) - mField[max(ix-1,0)][iy][iz].xi(dim1) )/(2*dr);
          case 'y': return (mField[ix][min(iy+1,nY-1)][iz].xi(dim1) - mField[ix][max(iy-1,0)][iz].xi(dim1) )/(2*dr);
          case 'z': return (mField[ix][iy][min(iz+1,nZ-1)].xi(dim1) - mField[ix][iy][max(iz-1,0)].xi(dim1) )/(2*dr);
       }
    }



    P3 rotor( size_t i,size_t j,size_t k , double dr) 
    {
       //      i  j  k
       //det  dx dy dz  =  ( dEzdy - Eydz,  -Ezdx + Exdz,  Eydx - Exdy )
       //     Ex Ey Ez

       return P3(   partial(i,j,k,'z','y',dr) - partial(i,j,k,'y','z',dr) 
                ,  -partial(i,j,k,'z','x',dr) + partial(i,j,k,'x','z',dr) 
                ,   partial(i,j,k,'y','x',dr) - partial(i,j,k,'x','y',dr)
                );

    }

    // works only for inner regions.
    // one should remember to divide the result by 2dr
    #define FAST_PARTIALX( L, N )                                    \
     double dFxd##L(int ix,int iy, int iz)                           \
     { return mField[ix+1][iy][iz][N] - mField[ix-1][iy][iz][N]; }

    #define FAST_PARTIALY( L, N )                                    \
     double dFyd##L(int ix,int iy, int iz)                           \
     { return mField[ix][iy+1][iz][N] - mField[ix][iy-1][iz][N]; }

    #define FAST_PARTIALZ( L, N )                                  \
     double dFzd##L(int ix,int iy, int iz)                         \
     { return mField[ix][iy][iz+1][N] - mField[ix][iy][iz-1][N]; }


     FAST_PARTIALX(x,0)  // dFxdx
     FAST_PARTIALX(y,1)  // dFxdy
     FAST_PARTIALX(z,2)  // dFxdz

     FAST_PARTIALY(x,0)  // dFydx
     FAST_PARTIALY(y,1)  // dFydy
     FAST_PARTIALY(z,2)  // dFydz

     FAST_PARTIALZ(x,0)  // dFzdx
     FAST_PARTIALZ(y,1)  // dFzdy
     FAST_PARTIALZ(z,2)  // dFzdz
    
    #undef FAST_PARTIALX
    #undef FAST_PARTIALY
    #undef FAST_PARTIALZ


    // can be applied to the inner parts only
    // should be divided by 2dr

    P3 fast_rotor(int i, int j, int k)
    {
       return P3(  dFzdy(i,j,k) - dFydz(i,j,k)
                , -dFzdx(i,j,k) + dFxdz(i,j,k)
                ,  dFydx(i,j,k) - dFxdy(i,j,k)
                );
    }

  
    void randomInit(); 
};

//template<class T>
//inline void swapptr( T ** p1, T ** p2) 
//{
 //   T * tmp = *p1;
 //   *p1 = *p2;
  //  *p2 = tmp;
//}


#define FOR3VF(vf,ix,iy,iz)                     \
    for( size_t ix = 0; ix < (vf).nx(); ix++ )  \
    for( size_t iy = 0; iy < (vf).ny(); iy++ )  \
    for( size_t iz = 0; iz < (vf).nz(); iz++ )



#endif