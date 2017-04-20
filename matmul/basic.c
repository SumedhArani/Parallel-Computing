#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#include "basic.h"

void basic_matmul(const int M, 
                  const double *A, const double *B, double *C)
{
    omp_set_num_threads(8);

    int i, j, k;
    double cij;
    #pragma omp parallel for private(cij) collapse(2) schedule(static)
    for (j = 0; j < M; ++j)
    {
		for (i = 0; i < M; ++i)         
        {
            cij = C[j*M+i];
            #pragma omp parallel for shared(cij)    
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
