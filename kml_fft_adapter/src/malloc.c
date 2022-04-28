#include "fft_type.h"

void *FFTW(malloc)(size_t n)
{
    return KML(malloc)(n);
}

void FFTW(free)(void *p)
{
    return KML(destroy_plan)(p);
}

void FFTW(destroy_plan)(FFTW(plan) plan)
{
    return KML(destroy_plan)((KML(plan))plan);
}