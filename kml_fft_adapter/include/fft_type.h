#ifndef __FFT_TYPE__
#define __FFT_TYPE__
#include <kfft.h>
#include <fftw3.h>
#define FFTW_VOIDFUNC void
#define CONCAT(prefix, name) prefix##name


#ifdef FFT_FP32
    typedef float FP;
    #define KML(name)       kml_fftf_ ##name
    #define FFTW(name)      fftwf_ ##name
    #define x77(name) CONCAT(dfftwf_, name)
    #define X77(NAME) CONCAT(DFFTWF_, NAME)
#else
    typedef double FP;
    #define KML(name)       kml_fft_ ##name
    #define FFTW(name)      fftw_ ##name
    #define x77(name) CONCAT(dfftw_, name)
    #define X77(NAME) CONCAT(DFFTW_, NAME)
#endif
#define F77x(a, A) F77_FUNC(a, A)

#define F77_FUNC(a, A) a##_
#define F77(a, A) F77x(x77(a), X77(A))

#endif
