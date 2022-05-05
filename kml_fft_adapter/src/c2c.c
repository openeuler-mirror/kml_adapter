#include "fft_type.h"

FFTW(plan) FFTW(plan_dft)(int rank, const int *n, FFTW(complex) *in, FFTW(complex) *out,
    int sign, unsigned flags)
{
    return (FFTW(plan))KML(plan_dft)(rank, n, (KML(complex) *)in, (KML(complex) *)out,
        sign, flags);
}

FFTW(plan) FFTW(plan_dft_1d)(int n, FFTW(complex) *in, FFTW(complex) *out,
    int sign, unsigned flags)
{
    return (FFTW(plan))KML(plan_dft_1d)(n, (KML(complex) *)in, (KML(complex) *)out,
        sign, flags);
}

FFTW(plan) FFTW(plan_dft_2d)(int n0, int n1, FFTW(complex) *in, FFTW(complex) *out,
    int sign, unsigned flags)
{
    return (FFTW(plan))KML(plan_dft_2d)(n0, n1, (KML(complex) *)in, (KML(complex) *)out,
        sign, flags);
}

FFTW(plan) FFTW(plan_dft_3d)(int n0, int n1, int n2, FFTW(complex) *in, FFTW(complex) *out,
    int sign, unsigned flags)
{
    return (FFTW(plan))KML(plan_dft_3d)(n0, n1, n2, (KML(complex) *)in, (KML(complex) *)out,
        sign, flags);
}

FFTW(plan) FFTW(plan_guru_dft)(int rank, const FFTW(iodim) *dims, int howmany_rank,
    const FFTW(iodim) *howmany_dims, FFTW(complex) *in, FFTW(complex) *out, int sign,
    unsigned flags)
{
    return (FFTW(plan))KML(plan_guru_dft)(rank, (KML(iodim) *)dims, howmany_rank,
        (KML(iodim) *)howmany_dims, (KML(complex) *)in, (KML(complex) *)out, sign, flags);
}

FFTW(plan) FFTW(plan_guru_split_dft)(int rank, const FFTW(iodim) *dims, int howmany_rank,
    const FFTW(iodim) *howmany_dims, FP *ri, FP *ii, FP *ro, FP *io, unsigned flags)
{
    return (FFTW(plan))KML(plan_guru_split_dft)(rank, (KML(iodim) *)dims, howmany_rank,
        (KML(iodim) *)howmany_dims, ri, ii, ro, io, flags);
}

FFTW(plan) FFTW(plan_guru64_dft)(int rank, const FFTW(iodim64) *dims, int howmany_rank,
    const FFTW(iodim64) *howmany_dims, FFTW(complex) *in, FFTW(complex) *out, int sign,
    unsigned flags)
{
    return (FFTW(plan))KML(plan_guru64_dft)(rank, (KML(iodim64) *)dims, howmany_rank,
        (KML(iodim64) *)howmany_dims, (KML(complex) *)in, (KML(complex) *)out, sign, flags);
}

FFTW(plan) FFTW(plan_guru64_split_dft)(int rank, const FFTW(iodim64) *dims, int howmany_rank,
    const FFTW(iodim64) *howmany_dims, FP *ri, FP *ii, FP *ro, FP *io, unsigned flags)
{
    return (FFTW(plan))KML(plan_guru64_split_dft)(rank, (KML(iodim64) *)dims, howmany_rank,
        (KML(iodim64) *) howmany_dims, ri, ii, ro, io, flags);
}

FFTW(plan) FFTW(plan_many_dft)(int rank, const int *n, int howmany, FFTW(complex) *in,
    const int *inembed, int istride, int idist, FFTW(complex) *out, const int *onembed,
    int ostride, int odist, int sign, unsigned flags)
{
    return (FFTW(plan))KML(plan_many_dft)(rank, n, howmany, (KML(complex) *)in, inembed,
        istride, idist, (KML(complex) *)out, onembed, ostride, odist, sign, flags);
}

//test