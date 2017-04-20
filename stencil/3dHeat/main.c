#include <stdio.h>
#include <stdlib.h>
#include "util.h"
#include "cycle.h"
#include "common.h"
#include "heat-blocked.h"
#include "heat.h"
#include "heat-time.h"

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
  nx = 514;
  ny = 514;
  nz = 514;
  tx = 512;
  ty = 64;
  tz = 4;
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
   	clear_cache();

   	/* Initialise Arrays */
    StencilInit(nx,ny,nz,Anext);
    StencilInit(nx,ny,nz,A0);
 
    t1 = getticks();	
    
    /* stencil function */ 
    #ifdef HEAT
    heat(A0, Anext, nx, ny, nz, timesteps);
    #endif

    #ifdef HEATBLOCK
    heatBlocked(A0, Anext, nx, ny, nz, tx, ty, tz, timesteps);
  	#endif

    #ifdef HEATTIME
    heatTime(A0, Anext, nx, ny, nz, tx, ty, tz, timesteps);
    #endif
    t2 = getticks();
    
    printf("elapsed ticks: %g  time:%g \n", elapsed(t2, t1), spt * elapsed(t2,t1));
  }
  double total = 0.0;
  for (int k = 0; k < nz; k++) {
    for (int j = 0; j < ny; j++) {
      for (int i = 0; i < nx; i++) {
        total += A0[Index3D (nx, ny, i, j, k)];
      }
    }
  }
  printf("Check: %f\n", total);
}

