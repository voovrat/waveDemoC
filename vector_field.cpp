#include "vector_field.h"

#include <stdlib.h>


void VectorField::randomInit() 
{
	FOR3VF(*this, ix, iy, iz ) 
      mField[ix][iy][iz].setXYZ( rand()-0.5, rand()-0.5,rand()-0.5);         
}