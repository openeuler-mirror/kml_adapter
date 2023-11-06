#include <stdlib.h>
#include <stdio.h>
#include "fft_type.h"
#define FFT_API  __attribute__((visibility("default")))

static int *reverse_n(int rnk, const int *n)
{
    int *nrev;
    int i;
    nrev = (int *)malloc(sizeof(int) * (unsigned)rnk);
    for (i = 0; i < rnk; ++i)
        nrev[rnk - i - 1] = n[i];
    return nrev;
}

FFT_API FFTW_VOIDFUNC F77(plan_many_dft, PLAN_MANY_DFT)(FFTW(plan) * p, int *rank, const int *n, int *howmany, FFTW(complex) * in,
    const int *inembed, int *istride, int *idist, FFTW(complex) * out, const int *onembed, int *ostride, int *odist,
    int *sign, int *flags)
{
    int *nrev = reverse_n(*rank, n);
    int *inembedrev = reverse_n(*rank, inembed);
    int *onembedrev = reverse_n(*rank, onembed);
    *p = FFTW(plan_many_dft)(*rank, nrev, *howmany, in, inembedrev, *istride, *idist, out, onembedrev, *ostride, *odist,
        *sign, *flags);
    free(onembedrev);
    free(inembedrev);
    free(nrev);
}

FFT_API FFTW_VOIDFUNC F77(plan_many_dft_r2c, PLAN_MANY_DFT_R2C)(FFTW(plan) * p, int *rank, const int *n, int *howmany, FP *in,
    const int *inembed, int *istride, int *idist, FFTW(complex) * out, const int *onembed, int *ostride, int *odist,
    int *flags)
{
    int *nrev = reverse_n(*rank, n);
    int *inembedrev = reverse_n(*rank, inembed);
    int *onembedrev = reverse_n(*rank, onembed);
    *p = FFTW(plan_many_dft_r2c)(*rank, nrev, *howmany, in, inembedrev, *istride, *idist, out, onembedrev, *ostride,
        *odist, *flags);
    free(onembedrev);
    free(inembedrev);
    free(nrev);
}

FFT_API FFTW_VOIDFUNC F77(plan_many_dft_c2r, PLAN_MANY_DFT_C2R)(FFTW(plan) * p, int *rank, const int *n, int *howmany,
    FFTW(complex) * in, const int *inembed, int *istride, int *idist, FP *out, const int *onembed, int *ostride, int *odist,
    int *flags)
{
    int *nrev = reverse_n(*rank, n);
    int *inembedrev = reverse_n(*rank, inembed);
    int *onembedrev = reverse_n(*rank, onembed);
    *p = FFTW(plan_many_dft_c2r)(*rank, nrev, *howmany, in, inembedrev, *istride, *idist, out, onembedrev, *ostride,
        *odist, *flags);
    free(onembedrev);
    free(inembedrev);
    free(nrev);
}

FFT_API FFTW_VOIDFUNC F77(plan_dft_3d, PLAN_DFT_3D)(FFTW(plan) * p, int *nx, int *ny, int *nz, FFTW(complex) * in, FFTW(complex) * out,
    int *sign, int *flags)
{
    *p = FFTW(plan_dft_3d)(*nz, *ny, *nx, in, out, *sign, *flags);
}

FFT_API FFTW_VOIDFUNC F77(plan_dft_r2c_3d, PLAN_DFT_R2C_3D)(FFTW(plan) * p, int *nx, int *ny, int *nz, FP *in, FFTW(complex) * out,
    int *flags)
{
    *p = FFTW(plan_dft_r2c_3d)(*nz, *ny, *nx, in, out, *flags);
}

FFT_API FFTW_VOIDFUNC F77(plan_dft_c2r_3d, PLAN_DFT_C2R_3D)(FFTW(plan) * p, int *nx, int *ny, int *nz, FFTW(complex) * in, FP *out,
    int *flags)
{
    *p = FFTW(plan_dft_c2r_3d)(*nz, *ny, *nx, in, out, *flags);
}

FFT_API FFTW_VOIDFUNC F77(execute_dft, EXECUTE_DFT)(FFTW(plan) * const p, FFTW(complex) * in, FFTW(complex) * out)
{
    FFTW(plan)pln = *p;
    FFTW(execute_dft)(pln, in, out);
}

FFT_API FFTW_VOIDFUNC F77(execute, EXECUTE)(FFTW(plan) * const p)
{
    FFTW(plan)pln = *p;
    FFTW(execute)(pln);
}

FFT_API FFTW_VOIDFUNC F77(execute_dft_r2c, EXECUTE_DFT_R2C)(FFTW(plan) * const p, FP *in, FFTW(complex) * out)
{
    FFTW(plan)pln = *p;
    FFTW(execute_dft_r2c)(pln, in, out);
}

FFT_API FFTW_VOIDFUNC F77(execute_dft_c2r, EXECUTE_DFT_C2R)(FFTW(plan) * const p, FFTW(complex) * in, FP *out)
{
    FFTW(plan)pln = *p;
    FFTW(execute_dft_c2r)(pln, in, out);
}

FFT_API FFTW_VOIDFUNC F77(destroy_plan, DESTROY_PLAN)(FFTW(plan) * p)
{
    FFTW(destroy_plan)(*p);
}

FFT_API int F77(import_wisdom, IMPORT_WISDOM)()
{
	return 0;
}

FFT_API FFTW_VOIDFUNC F77(export_wisdom, EXPORT_WISDOM)()
{
}
FFT_API FFTW_VOIDFUNC F77(cleanup_threads, CLEANUP_THREADS)(void)
{
    FFTW(cleanup_threads)();
}
FFT_API FFTW_VOIDFUNC F77(plan_with_nthreads, PLAN_WITH_NTHREADS)(int nthreads)
{
    FFTW(plan_with_nthreads)(nthreads);
}
FFT_API int F77(init_threads, INIT_THREADS)()
{
	return 1;
}