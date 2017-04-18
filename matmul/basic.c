#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#include "basic.h"

void basic_matmul(const int M, 
                  const double *A, const double *B, double *C)
{
    int i, j, k;
    for (j = 0; j < M; ++j)
    {
        #pragma omp parallel for
		for (i = 0; i < M; ++i)         
        {
            double cij = C[j*M+i];
            for (k = 0; k < M; ++k)
            {
                cij += A[k*M+i] * B[j*M+k];
            }
            C[j*M+i] = cij;
        }
    }
    double check = 0.0;
 	  for(j=0; j<M; j++)
 		  for(i=0; i<M; i++)
  			check+=C[j*M+i];
  	printf("%f\n", check);
}
