#include <stdio.h>
#include <stdlib.h>
#include "heat-blocked.h"

#define MIN(x,y) (x < y ? x : y)

void heatBlocked(double* A0, double* Anext, int nx, int ny, int nz,
                  int tx, int ty, int tz, int timesteps)
{
	double fac = A0[0];
  double *temp_ptr;
  int t, i, ii, j, jj, k;

  for (t = 0; t < timesteps; t++) {
  	#pragma omp parallel for
    for (jj = 1; jj < ny-1; jj+=ty) {
    	for (ii = 1; ii < nx - 1; ii+=tx) {
				for (k = 1; k < nz - 1; k++) {
  				for (j = jj; j < MIN(jj+ty,ny - 1); j++) {
				    for (i = ii; i < MIN(ii+tx,nx - 1); i++) {
				      Anext[Index3D (nx, ny, i, j, k)] = 
								A0[Index3D (nx, ny, i, j, k + 1)] +
								A0[Index3D (nx, ny, i, j, k - 1)] +
								A0[Index3D (nx, ny, i, j + 1, k)] +
								A0[Index3D (nx, ny, i, j - 1, k)] +
								A0[Index3D (nx, ny, i + 1, j, k)] +
								A0[Index3D (nx, ny, i - 1, j, k)]
								- 6.0 * A0[Index3D (nx, ny, i, j, k)] / (fac*fac);
	    			}
	  			}
				}
      }
    }
    temp_ptr = A0;
    A0 = Anext;
    Anext = temp_ptr;
  }
}