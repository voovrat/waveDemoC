#ifndef VECTORN_H
#define VECTORN_H

#include <vector>
#include <unistd.h>

// idea is to write the classes with the similar implementation:
//  e.g:
//    constructor  vectorN(n1,n2,...,nN)
//       resize(n1,n2,...,nN)
//       assign(n1,n2,...,nN,val)
//
//  For example for vector2 the implementation is:
//
// template< class T>
// class vector2 : public std::vector< std::vector< T > >  
// {
//  public:
// 	vector2(size_t n1,size_t n2) { resize(n1,n2);}
// 	vector2(size_t n1,size_t n2, const T & value) { assign(n1,n2,value); }

// 	void resize( size_t n1, size_t n2)
// 	{
// 		std::vector<T> tmp(n2);
// 		this->assign( n1, tmp );
// 	}

// 	void assign( size_t n1, size_t n2, const T & value )
// 	{
// 		std::vector<T> tmp(n2,value);
// 		this->assign( n1,tmp);
// 	}

// };


#define KOMA ,

///  N   : dimension
///  Nm1 : (N-1)
///  arg_list_tail :   n2 KOMA n3 KOMA ... nN
///  arg_def_tail  :   size_t n2 KOMA size_t n3 KOMA .... size_t nN
///
///  for example for vector3:
///     DEF_VECTOR_N(3,2,n2 KOMA n3, size_t n2 KOMA size_t n3)
///
#define DEF_VECTOR_N( N, Nm1, arg_list_tail, arg_def_tail )   \
template< class T>                                            \
class vector##N : public std::vector< vector##Nm1<T> >        \
{ public:                                                     \
	vector##N() {}                                            \
	vector##N(size_t n1, arg_def_tail) { resize(n1, arg_list_tail); }                          \
	vector##N(size_t n1, arg_def_tail, const T & value )  { assign(n1,arg_list_tail,value);}   \
	                                                \
	void resize( size_t n1, arg_def_tail)           \
	{   vector##Nm1<T> tmp(arg_list_tail);          \
		std::vector< vector##Nm1<T> >::assign(n1,tmp);  \
	}                                               \
	                                                \
	void assign( size_t n1, arg_def_tail,const T & value)     \
	{   vector##Nm1<T> tmp(arg_list_tail,value);              \
		std::vector< vector##Nm1<T> >::assign(n1,tmp);  }     \
};


// and now define vectors up to 6

template< class T>
class vector1 : public std::vector<T> 
{
	public:
		vector1(size_t n) : std::vector<T>(n) {}
		vector1(size_t n, const T &v) : std::vector<T>(n,v) {}
};


DEF_VECTOR_N( 2, 1, n2, size_t n2 )
DEF_VECTOR_N( 3, 2, n2 KOMA n3, size_t n2 KOMA size_t n3 )
DEF_VECTOR_N( 4, 3, n2 KOMA n3 KOMA n4, size_t n2 KOMA size_t n3 KOMA size_t n4 )
DEF_VECTOR_N( 5, 4, n2 KOMA n3 KOMA n4 KOMA n5, size_t n2 KOMA size_t n3 KOMA size_t n4 KOMA size_t n5 )
DEF_VECTOR_N( 6, 5, n2 KOMA n3 KOMA n4 KOMA n5 KOMA n6, size_t n2 KOMA size_t n3 KOMA size_t n4 KOMA size_t n5 KOMA size_t n6 )



#endif