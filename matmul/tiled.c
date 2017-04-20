#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#include "tiled.h"

#ifndef TILE_SIZE
#define TILE_SIZE ((int) 512)
#endif

#define MIN(x,y) (x < y ? x : y)

void tiled_matmul(const int M, 
                  const double *A, const double *B, double *C)
{
	omp_set_num_threads(8);

  int i, j, k, ii, jj;
  double cij;
  #pragma omp parallel for collapse(2) schedule(static)
  for(jj = 0; jj < M; jj+= TILE_SIZE){
	  for(ii = 0; ii < M; ii+= TILE_SIZE){
	  	for (j = jj; j < jj + TILE_SIZE; ++j) {
				for (i = ii; i < ii + TILE_SIZE; ++i) {
		      cij = C[j*M+i];
		      for (k = 0; k < M; ++k){
		          cij += A[k*M+i] * B[j*M+k];
		      }
	     		C[j*M+i] = cij;
	    	}
	  	}
		}
	}

  double check = 0.0;
	  for(j=0; j<M; j++)
		  for(i=0; i<M; i++)
				check+=C[j*M+i];
	printf("%f\n", check);
}