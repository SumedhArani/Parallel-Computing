#ifndef _PROBE_H_
#define _PROBE_H_

#include "common.h"

void StencilInit(int nx, int ny, int nz, double *A);

void clear_cache();

double seconds_per_tick();

#endif
