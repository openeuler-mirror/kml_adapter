#ifndef __FFT_TYPE__
#define __FFT_TYPE__
#include <kfft.h>
#include <fftw3.h>
#ifdef FFT_FP32
    typedef float FP;
    #define KML(name)       kml_fftf_ ##name
    #define FFTW(name)      fftwf_ ##name
#else
    typedef double FP;
    #define KML(name)       kml_fft_ ##name
    #define FFTW(name)      fftw_ ##name
#endif

#endif
