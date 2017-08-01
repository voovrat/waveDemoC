#ifndef MYCALCULATOR_H
#define MYCALCULATOR_H

#include "calculator.h"
#include "mysettings.h"
#include "mymodel.h"

class MyCalculator : public AME::Calculator<MyModel,MySettings>
{
protected:

  bool bAborted;
  double t,dt;

public: 

   MyCalculator( AME::SharedObject<MyModel> * model
               , AME::SharedObject<MySettings> * settings
               );

   virtual ~MyCalculator();

   void abort();

   virtual void run(); 

};

#endif

