#ifndef AME_SHARED_OBJECT_H
#define AME_SHARED_OBJECT_H

#include <pthread.h>

namespace AME {

template<class T>
class SharedObject {
protected: 
  mutable pthread_mutex_t m_lock;
  T m_data;
public: 
  
  SharedObject() {  
    pthread_mutex_init(&m_lock,NULL);
  }

  ~SharedObject() {
    pthread_mutex_destroy(&m_lock);
  }


  SharedObject( const T &src ) 
  {
     pthread_mutex_init(&m_lock,NULL); 
     getFrom(src);
  }  

  void putTo( T & dst) const
  {
    pthread_mutex_lock(&m_lock);
    dst = m_data;
    pthread_mutex_unlock(&m_lock);
  }

  void getFrom( const T & src ) 
  {
    pthread_mutex_lock(&m_lock);
    m_data = src; 
    pthread_mutex_unlock(&m_lock);
  }

  void operator<<( const T &src )   {  getFrom( src );  }
  void operator>>( T & dst ) const { putTo( dst ); }

  operator T () { 
     T tmp;
     putTo(tmp);
     return tmp; 
  }

  void operator=( const T & src ) 
  {
     getFrom(src);
  }  

};

}

template< class T>
void operator<<( T & dst, const AME::SharedObject<T> & src )
{
   src >> dst;
}


template< class T >
void operator>>( const T & src, AME::SharedObject<T> & dst )
{
  dst << src;
}


#endif
