#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include "heat-blocked.h"

#define MIN(x,y) (x < y ? x : y)

void heatBlocked(double* A0, double* Anext, int nx, int ny,
                  int tx, int ty, int timesteps)
{
	double h = A0[0];
  double *temp_ptr;
  int i, j, t, ii;
  for (t = 0; t < timesteps; t++) 
  {
  	#pragma omp parallel for
  	for (ii = 1; ii < nx - 1; ii+=tx)
  	{
	    for (j = 1; j < ny - 1; j++)
	    {
	    	for (i = ii; i < MIN(ii+tx,nx - 1); i++)
	      {
	        Anext[Index2D (nx, i, j)] = 
	          A0[Index2D (nx, i+1, j)] +
	          A0[Index2D (nx, i-1, j)] +
	          A0[Index2D (nx, i, j + 1)] +
	          A0[Index2D (nx, i, j - 1)] 
	          - 4.0 * A0[Index2D (nx, i, j)] / (h*h);
	    	}
	    }
	  }
    temp_ptr = A0;
    A0 = Anext;
    Anext = temp_ptr;
  }
}

//20s -> 32s on blocking?
//Why did the blocking increase the cost? expensive for the cache?