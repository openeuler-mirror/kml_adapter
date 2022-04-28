#include "fft_type.h"

FFTW(plan) FFTW(plan_dft_r2c)(int rank, const int *n, FP *in, FFTW(complex) *out,
    unsigned flags)
{
    return (FFTW(plan))KML(plan_dft_r2c)(rank, n, in, (KML(complex) *)out,
        flags);
}

FFTW(plan) FFTW(plan_dft_r2c_1d)(int n, FP *in, FFTW(complex) *out,
    unsigned flags)
{
    return (FFTW(plan))KML(plan_dft_r2c_1d)(n, in, (KML(complex) *)out,
        flags);
}

FFTW(plan) FFTW(plan_dft_r2c_2d)(int n0, int n1, FP *in, FFTW(complex) *out,
    unsigned flags)
{
    return (FFTW(plan))KML(plan_dft_r2c_2d)(n0, n1, in, (KML(complex) *)out,
        flags);
}

FFTW(plan) FFTW(plan_dft_r2c_3d)(int n0, int n1, int n2, FP *in, FFTW(complex) *out,
    unsigned flags)
{
    return (FFTW(plan))KML(plan_dft_r2c_3d)(n0, n1, n2, in, (KML(complex) *)out,
        flags);
}

FFTW(plan) FFTW(plan_guru_dft_r2c)(int rank, const FFTW(iodim) *dims, int howmany_rank,
    const FFTW(iodim) *howmany_dims, FP *in, FFTW(complex) *out,
    unsigned flags)
{
    return (FFTW(plan))KML(plan_guru_dft_r2c)(rank, (KML(iodim) *)dims, howmany_rank,
        (KML(iodim) *)howmany_dims, in, (KML(complex) *)out, flags);
}

FFTW(plan) FFTW(plan_guru_split_dft_r2c)(int rank, const FFTW(iodim) *dims, int howmany_rank,
    const FFTW(iodim) *howmany_dims, FP *in, FP *ro, FP *io, unsigned flags)
{
    return (FFTW(plan))KML(plan_guru_split_dft_r2c)(rank, (KML(iodim) *)dims, howmany_rank,
        (KML(iodim) *)howmany_dims, in, ro, io, flags);
}

FFTW(plan) FFTW(plan_guru64_dft_r2c)(int rank, const FFTW(iodim64) *dims, int howmany_rank,
    const FFTW(iodim64) *howmany_dims, FP *in, FFTW(complex) *out,
    unsigned flags)
{
    return (FFTW(plan))KML(plan_guru64_dft_r2c)(rank, (KML(iodim64) *)dims, howmany_rank,
        (KML(iodim64) *)howmany_dims, in, (KML(complex) *)out, flags);
}

FFTW(plan) FFTW(plan_guru64_split_dft_r2c)(int rank, const FFTW(iodim64) *dims, int howmany_rank,
    const FFTW(iodim64) *howmany_dims, FP *in, FP *ro, FP *io, unsigned flags)
{
    return (FFTW(plan))KML(plan_guru64_split_dft_r2c)(rank, (KML(iodim64) *)dims, howmany_rank,
        (KML(iodim64) *) howmany_dims, in, ro, io, flags);
}

FFTW(plan) FFTW(plan_many_dft_r2c)(int rank, const int *n, int howmany, FP *in,
    const int *inembed, int istride, int idist, FFTW(complex) *out, const int *onembed,
    int ostride, int odist, unsigned flags)
{
    return (FFTW(plan))KML(plan_many_dft_r2c)(rank, n, howmany, in, inembed,
        istride, idist, (KML(complex) *)out, onembed, ostride, odist, flags);
}