#ifndef AME_VIEW_H
#define AME_VIEW_H

#include "shared_object.h"

namespace AME {


template<class Settings>
class IView 
{
  protected:
    SharedObject<Settings> *pSharedSettings;
    Settings mSettings;

  public: 

    IView( SharedObject<Settings> * settings) 
    : pSharedSettings(settings) 
    {}
    virtual ~IView() {}

    void saveSettings() { *pSharedSettings << mSettings; }   
    void readSettings() { mSettings << *pSharedSettings; }

    virtual void timer() = 0;
    virtual void draw() = 0;

    virtual void keydown( int key ) {}
    virtual void click( int x, int y) {}
    virtual void exit() {}
};


template<class Model, class Settings> 
class View : public IView<Settings>
{
protected:

  SharedObject<Model> * pSharedModel;
  Model mModel;

public:


  View( SharedObject<Model> * model, SharedObject<Settings> * settings )
  : IView<Settings>(settings)
  , pSharedModel( model )
  {}

  void syncModel()
  {
     mModel << *pSharedModel;
  }

  // virtual void timer() = 0;
  // virtual void draw() = 0;

};


}

#endif

