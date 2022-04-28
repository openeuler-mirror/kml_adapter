#include "fft_type.h"

FFTW(plan) FFTW(plan_r2r)(int rank, const int *n, FP *in, FP *out, const FFTW(r2r_kind) *kind,
    unsigned flags)
{
    return (FFTW(plan))KML(plan_r2r)(rank, n, in, out, (KML(r2r_kind) *)kind,
        flags);
}

FFTW(plan) FFTW(plan_r2r_1d)(int n, FP *in, FP *out, FFTW(r2r_kind) kind,
    unsigned flags)
{
    return (FFTW(plan))KML(plan_r2r_1d)(n, in, out, (KML(r2r_kind))kind,
        flags);
}

FFTW(plan) FFTW(plan_r2r_2d)(int n0, int n1, FP *in, FP *out, FFTW(r2r_kind) kind0, FFTW(r2r_kind) kind1,
    unsigned flags)
{
    return (FFTW(plan))KML(plan_r2r_2d)(n0, n1, in, out, (KML(r2r_kind))kind0, (KML(r2r_kind))kind1,
        flags);
}

FFTW(plan) FFTW(plan_r2r_3d)(int n0, int n1, int n2, FP *in, FP *out, FFTW(r2r_kind) kind0, FFTW(r2r_kind) kind1, 
    FFTW(r2r_kind) kind2, unsigned flags)
{
    return (FFTW(plan))KML(plan_r2r_3d)(n0, n1, n2, in, out, (KML(r2r_kind))kind0, (KML(r2r_kind))kind1,
        (KML(r2r_kind))kind2, flags);
}

FFTW(plan) FFTW(plan_guru_r2r)(int rank, const FFTW(iodim) *dims, int howmany_rank,
    const FFTW(iodim) *howmany_dims, FP *in, FP *out, const FFTW(r2r_kind) *kind,
    unsigned flags)
{
    return (FFTW(plan))KML(plan_guru_r2r)(rank, (KML(iodim) *)dims, howmany_rank,
        (KML(iodim) *)howmany_dims, in, out, (KML(r2r_kind) *)kind, flags);
}

FFTW(plan) FFTW(plan_guru64_r2r)(int rank, const FFTW(iodim64) *dims, int howmany_rank,
    const FFTW(iodim64) *howmany_dims, FP *in, FP *out, const FFTW(r2r_kind) *kind,
    unsigned flags)
{
    return (FFTW(plan))KML(plan_guru64_r2r)(rank, (KML(iodim64) *)dims, howmany_rank,
        (KML(iodim64) *)howmany_dims, in, out, (KML(r2r_kind) *)kind, flags);
}

FFTW(plan) FFTW(plan_many_r2r)(int rank, const int *n, int howmany, FP *in,
    const int *inembed, int istride, int idist, FP *out, const int *onembed,
    int ostride, int odist, const FFTW(r2r_kind) *kind, unsigned flags)
{
    return (FFTW(plan))KML(plan_many_r2r)(rank, n, howmany, in, inembed,
        istride, idist, out, onembed, ostride, odist, (KML(r2r_kind) *)kind, flags);
}