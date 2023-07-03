/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2022-2022. All rights reserved.
 * Description: Fortran api of kml_fft
 * Author: fgk
 * Create: 2022-11-14
 */
#include "kfft.h"
#include "fft_type.h"
 
KML(plan) KML(plan_dft_1d_)(int *n, KML(complex) *in, KML(complex) *out, int *sign, unsigned *flags)
{
    return KML(plan_dft_1d)(*n, in, out, *sign, *flags);
}
 
KML(plan) KML(plan_dft_2d_)(int *n0, int *n1, KML(complex) *in, KML(complex) *out, int *sign, unsigned *flags)
{
    return KML(plan_dft_2d)(*n0, *n1, in, out, *sign, *flags);
}
 
KML(plan) KML(plan_dft_3d_)(int *n0, int *n1, int *n2, KML(complex) *in, KML(complex) *out, int *sign, unsigned *flags)
{
    return KML(plan_dft_3d)(*n0, *n1, *n2, in, out, *sign, *flags);
}
 
KML(plan) KML(plan_dft_)(int *rank, const int *n, KML(complex) *in, KML(complex) *out, int *sign, unsigned *flags)
{
    return KML(plan_dft)(*rank, n, in, out, *sign, *flags);
}
 
KML(plan) KML(plan_many_dft_)(int *rank, const int *n, int *howmany, KML(complex) *in, const int *inembed,
    int *istride, int *idist, KML(complex) *out, const int *onembed, int *ostride, int *odist, int *sign, unsigned *flags)
{
    return KML(plan_many_dft)(*rank, n, *howmany, in, inembed, *istride, *idist, out, onembed, *ostride, *odist,
        *sign, *flags);
}
 
KML(plan) KML(plan_dft_r2c_1d_)(int *n, FP *in, KML(complex) *out, unsigned *flags)
{
    return KML(plan_dft_r2c_1d)(*n, in, out, *flags);
}
 
KML(plan) KML(plan_dft_r2c_2d_)(int *n0, int *n1, FP *in, KML(complex) *out, unsigned *flags)
{
    return KML(plan_dft_r2c_2d)(*n0, *n1, in, out, *flags);
}
 
KML(plan) KML(plan_dft_r2c_3d_)(int *n0, int *n1, int *n2, FP *in, KML(complex) *out, unsigned *flags)
{
    return KML(plan_dft_r2c_3d)(*n0, *n1, *n2, in, out, *flags);
}
 
KML(plan) KML(plan_dft_r2c_)(int *rank, const int *n, FP *in, KML(complex) *out, unsigned *flags)
{
    return KML(plan_dft_r2c)(*rank, n, in, out, *flags);
}
 
KML(plan) KML(plan_many_dft_r2c_)(int *rank, const int *n, int *howmany, FP *in, const int *inembed,
    int *istride, int *idist, KML(complex) *out, const int *onembed, int *ostride, int *odist, unsigned *flags)
{
    return KML(plan_many_dft_r2c)(*rank, n, *howmany, in, inembed, *istride, *idist, out, onembed, * ostride, *odist,
        *flags);
}
 
KML(plan) KML(plan_dft_c2r_1d_)(int *n, KML(complex) *in, FP *out, unsigned *flags)
{
    return KML(plan_dft_c2r_1d)(*n, in, out, *flags);
}
 
KML(plan) KML(plan_dft_c2r_2d_)(int *n0, int *n1, KML(complex) *in, FP *out, unsigned *flags)
{
    return KML(plan_dft_c2r_2d)(*n0, *n1, in, out, *flags);
}
 
KML(plan) KML(plan_dft_c2r_3d_)(int *n0, int *n1, int *n2, KML(complex) *in, FP *out, unsigned *flags)
{
    return KML(plan_dft_c2r_3d)(*n0, *n1, *n2, in, out, *flags);
}
 
KML(plan) KML(plan_dft_c2r_)(int *rank, const int *n, KML(complex) *in, FP *out, unsigned *flags)
{
    return KML(plan_dft_c2r)(*rank, n, in, out, *flags);
}
 
KML(plan) KML(plan_many_dft_c2r_)(int *rank, const int *n, int *howmany, KML(complex) *in, const int *inembed,
    int *istride, int *idist, FP *out, const int *onembed, int *ostride, int *odist, unsigned *flags)
{
    return KML(plan_many_dft_c2r)(*rank, n, *howmany, in, inembed, *istride, *idist, out, onembed, *ostride, *odist,
        *flags);
}
 
KML(plan) KML(plan_r2r_1d_)(int *n, FP *in, FP *out, KML(r2r_kind) *kind, unsigned *flags)
{
    return KML(plan_r2r_1d)(*n, in, out, *kind, *flags);
}
 
KML(plan) KML(plan_r2r_2d_)(int *n0, int *n1, FP *in, FP *out, KML(r2r_kind) *kind0, KML(r2r_kind) *kind1,
    unsigned *flags)
{
    return KML(plan_r2r_2d)(*n0, *n1, in, out, *kind0, *kind1, *flags);
}
 
KML(plan) KML(plan_r2r_3d_)(int *n0, int *n1, int *n2, FP *in, FP *out, KML(r2r_kind) *kind0,
    KML(r2r_kind) *kind1, KML(r2r_kind) *kind2, unsigned *flags)
{
    return KML(plan_r2r_3d)(*n0, *n1, *n2, in, out, *kind0, *kind1, *kind2, *flags);
}
 
KML(plan) KML(plan_r2r_)(int *rank, const int *n, FP *in, FP *out, const KML(r2r_kind) *kind,
    unsigned *flags)
{
    return KML(plan_r2r)(*rank, n, in, out, kind, *flags);
}
 
KML(plan) KML(plan_many_r2r_)(int *rank, const int *n, int *howmany, FP *in, const int *inembed,
    int *istride, int *idist, FP *out, const int *onembed, int *ostride, int *odist, const KML(r2r_kind) *kind,
    unsigned *flags)
{
    return KML(plan_many_r2r)(*rank, n, *howmany, in, inembed, *istride, *idist, out, onembed, *ostride, *odist, kind,
        *flags);
}
 
KML(plan) KML(plan_guru_dft_)(int *rank, const KML(iodim) *dims, int *howmany_rank, const KML(iodim) *howmany_dims,
    KML(complex) *in, KML(complex) *out, int *sign, unsigned *flags)
{
    return KML(plan_guru_dft)(*rank, dims, *howmany_rank, howmany_dims, in, out, *sign, *flags);
}
 
KML(plan) KML(plan_guru_split_dft_)(int *rank, const KML(iodim) *dims, int *howmany_rank,
    const KML(iodim) *howmany_dims, FP *ri, FP *ii, FP *ro, FP *io, unsigned *flags)
{
    return KML(plan_guru_split_dft)(*rank, dims, *howmany_rank, howmany_dims, ri, ii, ro, io, *flags);
}
 
KML(plan) KML(plan_guru64_dft_)(int *rank, const KML(iodim64) *dims, int *howmany_rank,
    const KML(iodim64) *howmany_dims, KML(complex) *in, KML(complex) *out, int *sign, unsigned *flags)
{
    return KML(plan_guru64_dft)(*rank, dims, *howmany_rank, howmany_dims, in, out, *sign, *flags);
}
 
KML(plan) KML(plan_guru64_split_dft_)(int *rank, const KML(iodim64) *dims, int *howmany_rank,
    const KML(iodim64) *howmany_dims, FP *ri, FP *ii, FP *ro, FP *io, unsigned *flags)
{
    return KML(plan_guru64_split_dft)(*rank, dims, *howmany_rank, howmany_dims, ri, ii, ro, io, *flags);
}
 
KML(plan) KML(plan_guru_dft_r2c_)(int *rank, const KML(iodim) *dims, int *howmany_rank,
    const KML(iodim) *howmany_dims, FP *in, KML(complex) *out, unsigned *flags)
{
    return KML(plan_guru_dft_r2c)(*rank, dims, *howmany_rank, howmany_dims, in, out, *flags);
}
 
KML(plan) KML(plan_guru_split_dft_r2c_)(int *rank, const KML(iodim) *dims, int *howmany_rank,
    const KML(iodim) *howmany_dims, FP *in, FP *ro, FP *io, unsigned *flags)
{
    return KML(plan_guru_split_dft_r2c)(*rank, dims, *howmany_rank, howmany_dims, in, ro, io, *flags);
}
 
KML(plan) KML(plan_guru64_dft_r2c_)(int *rank, const KML(iodim64) *dims, int *howmany_rank,
    const KML(iodim64) *howmany_dims, FP *in, KML(complex) *out, unsigned *flags)
{
    return KML(plan_guru64_dft_r2c)(*rank, dims, *howmany_rank, howmany_dims, in, out, *flags);
}
 
KML(plan) KML(plan_guru64_split_dft_r2c_)(int *rank, const KML(iodim64) *dims, int *howmany_rank,
    const KML(iodim64) *howmany_dims, FP *in, FP *ro, FP *io, unsigned *flags)
{
    return KML(plan_guru64_split_dft_r2c)(*rank, dims, *howmany_rank, howmany_dims, in, ro, io, *flags);
}
 
KML(plan) KML(plan_guru_dft_c2r_)(int *rank, const KML(iodim) *dims, int *howmany_rank,
    const KML(iodim) *howmany_dims, KML(complex) *in, FP *out, unsigned *flags)
{
    return KML(plan_guru_dft_c2r)(*rank, dims, *howmany_rank, howmany_dims, in, out, *flags);
}
 
KML(plan) KML(plan_guru_split_dft_c2r_)(int *rank, const KML(iodim) *dims, int *howmany_rank,
    const KML(iodim) *howmany_dims, FP *ri, FP *ii, FP *out, unsigned *flags)
{
    return KML(plan_guru_split_dft_c2r)(*rank, dims, *howmany_rank, howmany_dims, ri, ii, out, *flags);
}
 
KML(plan) KML(plan_guru64_dft_c2r_)(int *rank, const KML(iodim64) *dims, int *howmany_rank,
    const KML(iodim64) *howmany_dims, KML(complex) *in, FP *out, unsigned *flags)
{
    return KML(plan_guru64_dft_c2r)(*rank, dims, *howmany_rank, howmany_dims, in, out, *flags);
}
 
KML(plan) KML(plan_guru64_split_dft_c2r_)(int *rank, const KML(iodim64) *dims, int *howmany_rank,
    const KML(iodim64) *howmany_dims, FP *ri, FP *ii, FP *out, unsigned *flags)
{
    return KML(plan_guru64_split_dft_c2r)(*rank, dims, *howmany_rank, howmany_dims, ri, ii, out, *flags);
}
 
KML(plan) KML(plan_guru_r2r_)(int *rank, const KML(iodim) *dims, int *howmany_rank,
    const KML(iodim) *howmany_dims, FP *in, FP *out, const KML(r2r_kind) *kind, unsigned *flags)
{
    return KML(plan_guru_r2r)(*rank, dims, *howmany_rank, howmany_dims, in, out, kind, *flags);
}
 
KML(plan) KML(plan_guru64_r2r_)(int *rank, const KML(iodim64) *dims, int *howmany_rank,
    const KML(iodim64) *howmany_dims, FP *in, FP *out, const KML(r2r_kind) *kind, unsigned *flags)
{
    return KML(plan_guru64_r2r)(*rank, dims, *howmany_rank, howmany_dims, in, out, kind, *flags);
}
 
void KML(execute_)(const KML(plan) *p)
{
    KML(execute)(*p);
}
 
void KML(execute_dft_)(const KML(plan) *p, KML(complex) *in, KML(complex) *out)
{
    KML(execute_dft)(*p, in, out);
}
 
void KML(execute_dft_r2c_)(const KML(plan) *p, FP *in, KML(complex) *out)
{
    KML(execute_dft_r2c)(*p, in, out);
}
 
void KML(execute_dft_c2r_)
(const KML(plan) *p, KML(complex) *in, FP *out)
{
    KML(execute_dft_c2r)(*p, in, out);
}
 
void KML(execute_split_dft_)(const KML(plan) *p, FP *ri, FP *ii, FP *ro, FP *io)
{
    KML(execute_split_dft)(*p, ri, ii, ro, io);
}
 
void KML(execute_split_dft_r2c_)(const KML(plan) *p, FP *in, FP *ro, FP *io)
{
    KML(execute_split_dft_r2c)(*p, in, ro, io);
}
 
void KML(execute_split_dft_c2r_)(const KML(plan) *p, FP *ri, FP *ii, FP *out)
{
    KML(execute_split_dft_c2r)(*p, ri, ii, out);
}
 
void KML(execute_r2r_)(const KML(plan) *p, FP *in, FP *out)
{
    KML(execute_r2r)(*p, in, out);
}
 
void KML(destroy_plan_)(KML(plan) *p)
{
    KML(destroy_plan)(*p);
}
 
void KML(plan_with_nthreads_)(int *nthreads)
{
    KML(plan_with_nthreads)(*nthreads);
}
 
int KML(init_threads_)(void)
{
    return KML(init_threads)();
}
 
void KML(cleanup_threads_)(void)
{
    KML(cleanup_threads)();
}
 
void *KML(malloc_)(size_t *n)
{
    return KML(malloc)(*n);
}
 
void KML(free_)(void *p)
{
    KML(free)(p);
}