#ifndef __BLOCKED_
#define __BLOCKED_

void base_op(const int lda, const int M, const int N, const int K,
                 const double *A, const double *B, double *C);

void do_block(const int lda,
              const double *A, const double *B, double *C,
              const int i, const int j, const int k);

void blocked_matmul(const int M, const double *A, const double *B, double *C);

#endif
