#ifndef AME_CALCULATOR_H
#define AME_CALCULATOR_H

#include "thread.h"

namespace AME {


template<class Model, class Settings>
class Calculator  : public Thread 
{
protected:

  SharedObject<Model> *pSharedModel;
  SharedObject<Settings> *pSharedSettings;

  Model mModel;
  Settings mSettings;


  virtual void readSettings()
  {
    mSettings << *pSharedSettings;
  }

  virtual void saveSettings()
  {
    mSettings >> *pSharedSettings;
  }

  virtual void saveModel()
  {
    mModel >> *pSharedModel;
  }

  virtual void sync()
  {
     saveModel();
     readSettings();
  }

public:

  // virtual void run() inherited ! 

  Calculator( SharedObject<Model> * model, SharedObject<Settings> *settings) 
    : pSharedModel(model)
    , pSharedSettings(settings)
  {}

  virtual ~Calculator() {}
};

}

#endif
