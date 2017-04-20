#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#include "blocked.h"

#ifndef BLOCK_SIZE
#define BLOCK_SIZE ((int) 16)
#endif

/*
  A is M-by-K
  B is K-by-N
  C is M-by-N

  lda is the leading dimension of the matrix
*/

void base_op(const int lda, const int M, const int N, const int K,
                 const double *A, const double *B, double *C)
{
    int i, j, k;
    for (i = 0; i < M; ++i) {
        for (j = 0; j < N; ++j) {
            double cij = C[j*lda+i];
            for (k = 0; k < K; ++k) {
                cij += A[k*lda+i] * B[j*lda+k];
            }
            C[j*lda+i] = cij;
        }
    }
}

void do_block(const int lda,
              const double *A, const double *B, double *C,
              const int i, const int j, const int k)
{
    const int M = (i+BLOCK_SIZE > lda? lda-i : BLOCK_SIZE);
    const int N = (j+BLOCK_SIZE > lda? lda-j : BLOCK_SIZE);
    const int K = (k+BLOCK_SIZE > lda? lda-k : BLOCK_SIZE);
    base_op(lda, M, N, K,
                A + i + k*lda, B + k + j*lda, C + i + j*lda);
}

void blocked_matmul(const int M, const double *A, const double *B, double *C)
{
    const int n_blocks = M / BLOCK_SIZE + (M%BLOCK_SIZE? 1 : 0);
    int bi, bj, bk;
    #pragma omp parallel for collapse(2)
    for (bi = 0; bi < n_blocks; ++bi) {
        const int i = bi * BLOCK_SIZE; 
        for (bj = 0; bj < n_blocks; ++bj) {
            const int j = bj * BLOCK_SIZE;
            for (bk = 0; bk < n_blocks; ++bk) {
                const int k = bk * BLOCK_SIZE;
                do_block(M, A, B, C, i, j, k);
            }
        }
    }
    double check = 0.0;
      for(bj=0; bj<M; bj++)
          for(bi=0; bi<M; bi++)
            check+=C[bj*M+bi];
    printf("%f\n", check);
}


/*
Block - obs 1 
NO false sharing 
Only reads? 
Why so?
Probably it's being called several times, overhead inc

*/

