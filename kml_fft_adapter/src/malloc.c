#include "fft_type.h"

void *FFTW(malloc)(size_t n)
{
    return KML(malloc)(n);
}

void FFTW(free)(void *p)
{
    return KML(free)(p);
}

void FFTW(destroy_plan)(FFTW(plan) plan)
{
    return KML(destroy_plan)((KML(plan))plan);
}

void FFTW(printer_destroy)(void *p)
{
    return KML(free)(p);
}

void *FFTW(malloc_plain)(size_t n)
{
    if (n == 0)
        n = 1;
    return KML(malloc)(n);
}

void FFTW(ifree)(void *p)
{
    return KML(free)(p);
}