CC = gcc-6 
CFLAGS = -fopenmp -O3

debug : matmul_debug 

matmul_debug: matmul.c matrix.c basic.c blocked.c
	$(CC) $(CFLAGS) -DBASIC matmul.c matrix.c basic.c blocked.c -o matmul-basic
	$(CC) $(CFLAGS) -DBLOCKED matmul.c matrix.c basic.c blocked.c -o matmul-blocked