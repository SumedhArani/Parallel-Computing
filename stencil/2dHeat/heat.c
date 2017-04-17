#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include "heat.h"

void heat(double* A0, double* Anext, int nx, int ny, int timesteps)
{
	double h = A0[0];
  double *temp_ptr;
  int i, j, k, t;
  for (t = 0; t < timesteps; t++) 
  {
  	#pragma omp parallel for
    for (j = 1; j < ny - 1; j++)
    {
    	for (i = 1; i < nx - 1; i++) 
      {
        Anext[Index2D (nx, i, j)] = 
          A0[Index2D (nx, i+1, j)] +
          A0[Index2D (nx, i-1, j)] +
          A0[Index2D (nx, i, j + 1)] +
          A0[Index2D (nx, i, j - 1)] 
          - 4.0 * A0[Index2D (nx, i, j)] / (h*h);
    	}
    }
    temp_ptr = A0;
    A0 = Anext;
    Anext = temp_ptr;
  }
}

//SIMD not possible
//collapse more expensive more chunks have to be bought in
//Which loop should be parallelised?