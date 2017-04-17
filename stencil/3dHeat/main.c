#include <stdio.h>
#include <stdlib.h>
#include "util.h"
#include "cycle.h"
#include "common.h"
#include "heat-blocked.h"
#include "heat.h"

#define NUM_TRIALS 2
#define CUTOFF 4096

int main(int argc,char *argv[])
{
	double *Anext;
  double *A0;
  int nx;
  int ny;
  int nz;
  int tx;
  int ty;
  int tz;
  int timesteps;
  int i;

  #ifdef DEBUG
  nx = 250;
  ny = 250;
  nz = 250;
  tx = 125;
  ty = 125;
  tz = 125;
  timesteps = 100;
  #else
  nx = atoi(argv[1]);
  ny = atoi(argv[2]);
  nz = atoi(argv[3]);
  tx = atoi(argv[4]);
  ty = atoi(argv[5]);
  tz = atoi(argv[6]);
  timesteps = atoi(argv[7]);
  #endif
  
  ticks t1, t2;
  double spt;

  /* find conversion factor from ticks to seconds */
  spt = seconds_per_tick();

  /* allocate arrays */ 
  Anext=(double*)malloc(sizeof(double)*nx*ny*nz);
  A0=(double*)malloc(sizeof(double)*nx*ny*nz);
  
  printf("USING TIMER: %s \t  SECONDS PER TICK:%g \n", TIMER_DESC, spt);

	for (i=0;i<NUM_TRIALS;i++) 
	{
   	// clear_cache();

   	/* Initialise Arrays */
    StencilInit(nx,ny,Anext);
    StencilInit(nx,ny,A0);
 
    t1 = getticks();	
    
    /* stencil function */ 
    #ifdef HEAT
    heat(A0, Anext, nx, ny, nz, timesteps);
    #endif

    #ifdef HEATBLOCK
    heatBlocked(A0, Anext, nx, ny, nz, tx, ty, tz, timesteps);
  	#endif
    t2 = getticks();
    
    printf("elapsed ticks: %g  time:%g \n", elapsed(t2, t1), spt * elapsed(t2,t1));
  }
}

