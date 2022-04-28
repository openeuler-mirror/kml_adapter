#include "fft_type.h"
void FFTW(plan_with_nthreads)(int nthreads)
{
    KML(plan_with_nthreads)(nthreads);
}

int FFTW(init_threads)(void)
{
    return KML(init_threads)();
}

void FFTW(cleanup_threads)(void)
{
    KML(cleanup_threads)();
}