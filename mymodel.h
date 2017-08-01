#ifndef MYMODEL_H
#define MYMODEL_H

#include "maxwell.h"

class MyModel 
{
public:

	static constexpr int Nx = 20, Ny = 20, Nz = 20;
	static constexpr double dr = 1, dt = 0.001;
  static constexpr double FILTER_TRESHOLD = 1e-8;

public:  

  Maxwell m;

  const VectorField &E() const { return m.E(); }
  const VectorField &B() const { return m.B(); }

  void init();

  void filter();

  void initialCondition();
  void boundaryConditions();
  void step();

  MyModel();


private:
   void init1();
   void init2();
};


#endif
