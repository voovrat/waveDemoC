#ifndef P3_H
#define P3_H

#include <unistd.h>   // size_t
#include <math.h>  // sqrt

class P3 {

protected:
    double mX[3];


public: 

     static const P3 Zero;

public:

    P3() 
    {
        setXYZ(0,0,0);
    }

    P3( double _x, double _y, double _z )
    {
        setXYZ(_x,_y,_z);
    }

    P3( const P3 & pt )
    {
        setXYZ( pt.xyz() );
    } 


    double x() const { return mX[0]; }
    double y() const { return mX[1]; }
    double z() const { return mX[2]; }

    double &operator[]( int i) {return mX[i];}

    const double * xyz () const { return &mX[0]; }
    double xyz( size_t i ) const { return mX[i]; }

    void setX( double _x ) { mX[0] = _x; }
    void setY( double _y ) { mX[1] = _y; }
    void setZ( double _z ) { mX[2] = _z; }


    void setXYZ(double _x, double _y, double _z) 
    {
        mX[0] = _x;
        mX[1] = _y;
        mX[2] = _z;
    }

    void setXYZ( const double *xyz )
    {
        size_t i;
        for(i=0;i<3;i++) mX[i] = xyz[i];
    }


    /// named index
    ///   coord('x') --> x
    ///   coord('y') --> y
    ///   coord('z') --> z
    double coord( char dim) const 
    {
       return mX[ dim - 'x'];
    }

    double abs2() const 
    {
        return mX[0]*mX[0] + mX[1]*mX[1] + mX[2]*mX[2];
    }

    double abs() const 
    {
        return sqrt(abs2());
    }


    double xi( char dim ) const { return coord(dim); } // for compatibiity and brevity
 
    // operators
    const P3 & operator=( const P3 & pt)
    {
        this->setXYZ( pt.xyz() );
        return *this;
    }

    P3 & operator+=( const P3 & d)
    {
        size_t i;
        for(i=0;i<3;i++)  mX[i]+=d.xyz(i);
        return *this;
    }

    P3 & operator-=( const P3 &d)
    {
        size_t i;
        for(i=0;i<3;i++) mX[i] -= d.xyz(i);
        return *this;
    }


};


inline P3 operator-( const P3 & pt) 
{
    return P3( -pt.x(), -pt.y(), -pt.z());
}


inline P3 operator+( const P3 &a, const P3 &b)
{
    return P3( a.x() + b.x(), a.y() + b.y(), a.z() + b.z());
}


inline P3 operator-( const P3 &a, const P3 &b ) 
{
    return P3( a.x() - b.x(), a.y() - b.y(), a.z() - b.z() );    
}

inline P3  operator*( double k, const P3 &a)
{
    return P3( k*a.x(), k*a.y(), k*a.z());
}

inline P3  operator*( const P3 &a, double k) { return k*a;}


inline double scalProd( const P3 &a, const P3 &b ) 
{
    double S = 0;
    size_t i;
    for(i=0;i<3;i++) S+=a.xyz(i) * b.xyz(i);
    return S;
}

//     i j k
//  a: x y z
//  b: x y z
//
inline P3  vecProd( const P3 &a, const P3 &b )
{
    return P3(  a.y() * b.z() - b.y() * a.z()
             , -a.x() * b.z() + a.z() * b.x()
             ,  a.x() * b.y() - a.y() * b.x()
            ); 
}

inline double abs2(const P3 &P ) { return P.abs2(); }
inline double abs( const P3 & P) { return P.abs(); }

#endif


