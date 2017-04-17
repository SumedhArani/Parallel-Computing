/*
	Stencil Probe utilities
	Helper functions for the probe.
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "util.h"
#include "cycle.h"

void StencilInit(int nx, int ny, double *A)
{
  long last = nx*ny;
  long i;
  float check;
  for(i=0;i<last;i++) {
#ifdef RANDOMVALUES
    srand(31);
  	check = rand() % 100;
	  A[i] = check /100;
  }
#else
	  A[i]=1.0;
  }
#endif
}

/*
  This function determines ticks per second.
  Inspired by OSKI function (bebop.cs.berkeley.edu)
	Used from mit.csail.lab
*/
double seconds_per_tick()
{
	ticks t0,t1;
	unsigned int i = 3;
	double spt = 0;

	while (spt <= 0)
	{

	t0=getticks();	
	sleep(i);
	t1=getticks();
	spt = (double)i / elapsed(t1,t0);
	i++;

	}

	return spt;
}

/*
  Function to clear the cache, preventing data items in cache
  from making subsequent trials run faster.
*/
void clear_cache()
{
  int i;
  float* tarray, accum;

  tarray = (float*) malloc(sizeof(float)*1310720);
  for (i=0,accum=0; i<1310719; i++)
    tarray[i] = 1.0;
}
