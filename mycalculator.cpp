#include "mycalculator.h"

#include <math.h>

#include <iostream> 

MyCalculator::MyCalculator( AME::SharedObject<MyModel> * model
                          , AME::SharedObject<MySettings> * settings
                          )
   : AME::Calculator<MyModel, MySettings>(model, settings )
{
  bAborted = false;
  t = 0;
  dt = 0.1;
}

MyCalculator::~MyCalculator() {}

void MyCalculator::abort() 
{ 
  bAborted = true; 
}

void MyCalculator::run()
{
  int tic = 0;

  std::cout<<"Calculator run\n";

  mModel.init();

  readSettings();
  tic = mSettings.tic;


  while( true )
  {

    readSettings();

    if( mSettings.aborted ) break;

    if( !mSettings.paused ) 
    {
         mModel.step();
          if( tic != mSettings.tic)
          {
            tic = mSettings.tic;
            saveModel();
          }
    }
  } // while true

  mSettings.finished = true;
  saveSettings();
    
}
