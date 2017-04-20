#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "matrix.h"
#include "blocked.h"
#include "tiled.h"
#include "basic.h"

#define MAX_SIZE 1024

int main(int argc, char const *argv[])
{
	#ifdef DEBUG
	srand48(21);
	#endif

	double* A = (double*) malloc(MAX_SIZE * MAX_SIZE * sizeof(double));
    double* B = (double*) malloc(MAX_SIZE * MAX_SIZE * sizeof(double));
    double* C = (double*) malloc(MAX_SIZE * MAX_SIZE * sizeof(double));

    matrix_init(A, MAX_SIZE);
    matrix_init(B, MAX_SIZE);

    matrix_clear(C, MAX_SIZE);

    #ifdef BASIC
    const int M = MAX_SIZE;
    basic_matmul(M, A, B, C);
    #endif

    #ifdef BLOCKED
    const int M = MAX_SIZE;
    blocked_matmul(M, A, B, C);
    #endif

    #ifdef TILED
    const int M = MAX_SIZE;
    tiled_matmul(M, A, B, C);
    #endif

    free(A);
    free(B);
    free(C);

	return 0;
}