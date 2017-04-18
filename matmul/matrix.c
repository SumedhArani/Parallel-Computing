#include <stdlib.h>
#include <string.h>
#include "matrix.h"

void matrix_init(double *A, int MAX_SIZE)
{
    for (int i = 0; i < MAX_SIZE*MAX_SIZE; ++i) 
        A[i] = drand48();
}

void matrix_clear(double *C, int MAX_SIZE)
{
    memset(C, 0, MAX_SIZE * MAX_SIZE * sizeof(double));
}

