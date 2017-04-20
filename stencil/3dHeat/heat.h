#ifndef __HEAT_
#define __HEAT_

#include "common.h"

#define MIN(x,y) (x < y ? x : y)
#define MAX(x,y) (x > y ? x : y)

void heat(double* A0, double* Anext, int nx, int ny, int nz, int timesteps);

#endif