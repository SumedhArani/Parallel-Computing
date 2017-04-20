#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include "heat.h"

void heat(double* A0, double* Anext, int nx, int ny, int nz, int timesteps)
{
	double h = A0[0];
  double *temp_ptr;
  int i, j, k, t;
  double tsum;

  omp_set_num_threads(8);

  for (t = 0; t < timesteps; t++) 
  {
    //#pragma omp parallel for collapse(2) private(i, j, k) schedule(static)
    for (k = 1; k < nz - 1; k++) {
      #pragma omp parallel for schedule(static)
      for (j = 1; j < ny - 1; j++) {
        //#pragma omp parallel for shared(i, j, k)
      	for (i = 1; i < nx - 1; i++) {
          Anext[Index3D (nx, ny, i, j, k)] = 
            A0[Index3D (nx, ny, i, j, k + 1)] +
            A0[Index3D (nx, ny, i, j, k - 1)] +
            A0[Index3D (nx, ny, i, j + 1, k)] +
            A0[Index3D (nx, ny, i, j - 1, k)] +
            A0[Index3D (nx, ny, i + 1, j, k)] +
            A0[Index3D (nx, ny, i - 1, j, k)]
            - 6.0 * A0[Index3D (nx, ny, i, j, k)] / (h*h);
      	}
      }
    }
    temp_ptr = A0;
    A0 = Anext;
    Anext = temp_ptr;
  }
}