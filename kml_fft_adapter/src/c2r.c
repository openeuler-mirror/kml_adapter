#include "fft_type.h"

FFTW(plan) FFTW(plan_dft_c2r)(int rank, const int *n, FFTW(complex) *in, FP *out,
    unsigned flags)
{
    return (FFTW(plan))KML(plan_dft_c2r)(rank, n, (KML(complex) *)in, out,
        flags);
}

FFTW(plan) FFTW(plan_dft_c2r_1d)(int n, FFTW(complex) *in, FP *out,
    unsigned flags)
{
    return (FFTW(plan))KML(plan_dft_c2r_1d)(n, (KML(complex) *)in, out,
        flags);
}

FFTW(plan) FFTW(plan_dft_c2r_2d)(int n0, int n1, FFTW(complex) *in, FP *out,
    unsigned flags)
{
    return (FFTW(plan))KML(plan_dft_c2r_2d)(n0, n1, (KML(complex) *)in, out,
        flags);
}

FFTW(plan) FFTW(plan_dft_c2r_3d)(int n0, int n1, int n2, FFTW(complex) *in, FP *out,
    unsigned flags)
{
    return (FFTW(plan))KML(plan_dft_c2r_3d)(n0, n1, n2, (KML(complex) *)in, out,
        flags);
}

FFTW(plan) FFTW(plan_guru_dft_c2r)(int rank, const FFTW(iodim) *dims, int howmany_rank,
    const FFTW(iodim) *howmany_dims, FFTW(complex) *in, FP *out, unsigned flags)
{
    return (FFTW(plan))KML(plan_guru_dft_c2r)(rank, (KML(iodim) *)dims, howmany_rank,
        (KML(iodim) *)howmany_dims, (KML(complex) *)in, out, flags);
}

FFTW(plan) FFTW(plan_guru_split_dft_c2r)(int rank, const FFTW(iodim) *dims, int howmany_rank,
    const FFTW(iodim) *howmany_dims, FP *ri, FP *ii, FP *out, unsigned flags)
{
    return (FFTW(plan))KML(plan_guru_split_dft_c2r)(rank, (KML(iodim) *)dims, howmany_rank,
        (KML(iodim) *)howmany_dims, ri, ii, out, flags);
}

FFTW(plan) FFTW(plan_guru64_dft_c2r)(int rank, const FFTW(iodim64) *dims, int howmany_rank,
    const FFTW(iodim64) *howmany_dims, FFTW(complex) *in, FP *out,
    unsigned flags)
{
    return (FFTW(plan))KML(plan_guru64_dft_c2r)(rank, (KML(iodim64) *)dims, howmany_rank,
        (KML(iodim64) *)howmany_dims, (KML(complex) *)in, out, flags);
}

FFTW(plan) FFTW(plan_guru64_split_dft_c2r)(int rank, const FFTW(iodim64) *dims, int howmany_rank,
    const FFTW(iodim64) *howmany_dims, FP *ri, FP *ii, FP *out, unsigned flags)
{
    return (FFTW(plan))KML(plan_guru64_split_dft_c2r)(rank, (KML(iodim64) *)dims, howmany_rank,
        (KML(iodim64) *) howmany_dims, ri, ii, out, flags);
}

FFTW(plan) FFTW(plan_many_dft_c2r)(int rank, const int *n, int howmany, FFTW(complex) *in,
    const int *inembed, int istride, int idist, FP *out, const int *onembed,
    int ostride, int odist, unsigned flags)
{
    return (FFTW(plan))KML(plan_many_dft_c2r)(rank, n, howmany, (KML(complex) *)in, inembed,
        istride, idist, out, onembed, ostride, odist, flags);
}