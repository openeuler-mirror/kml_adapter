/*
 * @CopyRight: Copyright (c) Huawei Technologies Co., Ltd. 2023-2023. All rights reserved.
 * @Description: kml interface for numpy funtions
 * @Aythor: LiuYongYang
 * @Date: 2023-02-20 17:45:45
 */

#ifndef KVML_ADAPTER_H
#define KVML_ADAPTER_H

#include <math.h>
#include <arm_neon.h>
#include "Python.h"
#include "kvml.h"
#include "km.h"
#include "ksvml.h"

//  ---------------------------------------------------------------------------------
//  --------------------------------------PROXY--------------------------------------
//  ---------------------------------------------------------------------------------
inline void KML_SVML_f32_i1o1_Proxy(const Py_intptr_t n, float *ip1, float *op1, float32x4_t (*svmlFunc)(float32x4_t),
    float (*scalarFunc)(float))
{
    const Py_intptr_t svmlCnt = n / 0x4;
    const Py_intptr_t scalarCnt = n & 0x3;
    float32x4_t ov1;
    //  vector NEON op
    for (Py_intptr_t i = 0; i < svmlCnt; ++i, ip1 += 0x4, op1 += 0x4) {
        ov1 = svmlFunc(vld1q_f32(ip1));
        vst1q_f32(op1, ov1);
    }
    //  scalar op
    for (Py_intptr_t i = 0; i < scalarCnt; ++i, ++ip1, ++op1) { *op1 = scalarFunc(*ip1); }
}

inline void KML_SVML_f64_i1o1_Proxy(const Py_intptr_t n, double *ip1, double *op1, float64x2_t (*svmlFunc)(float64x2_t),
    double (*scalarFunc)(double))
{
    const Py_intptr_t svmlCnt = n / 0x2;
    const Py_intptr_t scalarCnt = n & 0x1;
    float64x2_t ov1;
    //  vector NEON op
    for (Py_intptr_t i = 0; i < svmlCnt; ++i, ip1 += 0x2, op1 += 0x2) {
        ov1 = svmlFunc(vld1q_f64(ip1));
        vst1q_f64(op1, ov1);
    }
    //  scalar op
    for (Py_intptr_t i = 0; i < scalarCnt; ++i, ++ip1, ++op1) { *op1 = scalarFunc(*ip1); }
}

//  ---------------------------------------------------------------------------------
//  --------------------------------------FLOAT--------------------------------------
//  ---------------------------------------------------------------------------------

inline void KML_VML_FLOAT_add(char **args, Py_intptr_t const *dimensions)
{
    vsadd(dimensions[0], (float*)args[0], (float*)args[1], (float*)args[0x2]);
}

inline void KML_VML_FLOAT_subtract(char **args, Py_intptr_t const *dimensions)
{
    vssub(dimensions[0], (float*)args[0], (float*)args[1], (float*)args[0x2]);
}

inline void KML_VML_FLOAT_multiply(char **args, Py_intptr_t const *dimensions)
{
    vsmul(dimensions[0], (float*)args[0], (float*)args[1], (float*)args[0x2]);
}

inline void KML_VML_FLOAT_exp(char **args, Py_intptr_t const *dimensions)
{
    vsexp(dimensions[0], (float*)args[0], (float*)args[1]);
}

inline void KML_VML_FLOAT_sqrt(char **args, Py_intptr_t const *dimensions)
{
    vssqrt(dimensions[0], (float*)args[0], (float*)args[1]);
}

inline void KML_VML_FLOAT_log(char **args, Py_intptr_t const *dimensions)
{
    vsln(dimensions[0], (float*)args[0], (float*)args[1]);
}

inline void KML_VML_FLOAT_sin(char **args, Py_intptr_t const *dimensions)
{
    vssin(dimensions[0], (float*)args[0], (float*)args[1]);
}

inline void KML_VML_FLOAT_cos(char **args, Py_intptr_t const *dimensions)
{
    vscos(dimensions[0], (float*)args[0], (float*)args[1]);
}

inline void KML_VML_FLOAT_tan(char **args, Py_intptr_t const *dimensions)
{
    vstan(dimensions[0], (float*)args[0], (float*)args[1]);
}

inline void KML_VML_FLOAT_arctan(char **args, Py_intptr_t const *dimensions)
{
    vsatan(dimensions[0], (float*)args[0], (float*)args[1]);
}

inline void KML_VML_FLOAT_power(char **args, Py_intptr_t const *dimensions)
{
    vspow(dimensions[0], (float*)args[0], (float*)args[1], (float*)args[0x2]);
}

inline void KML_VML_FLOAT_fmod(char **args, Py_intptr_t const *dimensions)
{
    float *ip1 = (float*)args[0];
    float *ip2 = (float*)args[1];
    float* op = (float*)args[0x2];
    Py_intptr_t n = dimensions[0];
    for (Py_intptr_t i = 0; i < n; ++i, ++ip1, ++ip2, ++op) {
        *op = fmodf(*ip1, *ip2);
    }
}

inline void KML_VML_FLOAT_exp2(char **args, Py_intptr_t const *dimensions)
{
    KML_SVML_f32_i1o1_Proxy(dimensions[0], (float*)args[0], (float*)args[1], svml128_exp2_f32, exp2f);
}

//  ----------------------------------------------------------------------------------
//  --------------------------------------DOUBLE--------------------------------------
//  ----------------------------------------------------------------------------------

inline void KML_VML_DOUBLE_add(char **args, Py_intptr_t const *dimensions)
{
    vdadd(dimensions[0], (double*)args[0], (double*)args[1], (double*)args[0x2]);
}

inline void KML_VML_DOUBLE_subtract(char **args, Py_intptr_t const *dimensions)
{
    vdsub(dimensions[0], (double*)args[0], (double*)args[1], (double*)args[0x2]);
}

inline void KML_VML_DOUBLE_multiply(char **args, Py_intptr_t const *dimensions)
{
    vdmul(dimensions[0], (double*)args[0], (double*)args[1], (double*)args[0x2]);
}

inline void KML_VML_DOUBLE_exp(char **args, Py_intptr_t const *dimensions)
{
    vdexp(dimensions[0], (double*)args[0], (double*)args[1]);
}

inline void KML_VML_DOUBLE_sqrt(char **args, Py_intptr_t const *dimensions)
{
    vdsqrt(dimensions[0], (double*)args[0], (double*)args[1]);
}

inline void KML_VML_DOUBLE_log(char **args, Py_intptr_t const *dimensions)
{
    vdln(dimensions[0], (double*)args[0], (double*)args[1]);
}

inline void KML_VML_DOUBLE_sin(char **args, Py_intptr_t const *dimensions)
{
    vdsin(dimensions[0], (double*)args[0], (double*)args[1]);
}

inline void KML_VML_DOUBLE_cos(char **args, Py_intptr_t const *dimensions)
{
    vdcos(dimensions[0], (double*)args[0], (double*)args[1]);
}

inline void KML_VML_DOUBLE_tan(char **args, Py_intptr_t const *dimensions)
{
    vdtan(dimensions[0], (double*)args[0], (double*)args[1]);
}

inline void KML_VML_DOUBLE_arctan(char **args, Py_intptr_t const *dimensions)
{
    vdatan(dimensions[0], (double*)args[0], (double*)args[1]);
}

inline void KML_VML_DOUBLE_power(char **args, Py_intptr_t const *dimensions)
{
    vdpow(dimensions[0], (double*)args[0], (double*)args[1], (double*)args[0x2]);
}

inline void KML_VML_DOUBLE_fmod(char **args, Py_intptr_t const *dimensions)
{
    double *ip1 = (double*)args[0];
    double *ip2 = (double*)args[1];
    double* op = (double*)args[0x2];
    Py_intptr_t n = dimensions[0];
    for (Py_intptr_t i = 0; i < n; ++i, ++ip1, ++ip2, ++op) {
        *op = fmod(*ip1, *ip2);
    }
}

inline void KML_VML_DOUBLE_exp2(char **args, Py_intptr_t const *dimensions)
{
    KML_SVML_f64_i1o1_Proxy(dimensions[0], (double*)args[0], (double*)args[1], svml128_exp2_f64, exp2);
}

#endif
