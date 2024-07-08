/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2023. All rights reserved.
 * Description: DesignWare kunpeng interpolation library.
 * Author:
 * Create: 2023-09-14
 */

#ifndef KML_SPLINE_H
#define KML_SPLINE_H
#include <stdlib.h>
#include "kml_interp.h"

#undef __BEGIN_DECLS
#undef __END_DECLS
#ifdef __cplusplus
#define __BEGIN_DECLS \
    extern "C"        \
    {
#define __END_DECLS }
#else
#define __BEGIN_DECLS /* empty */
#define __END_DECLS   /* empty */
#endif

__BEGIN_DECLS

/* general interpolation object */
typedef struct {
    kml_float_interp *interp;
    float *x;
    float *y;
    size_t size;
} kml_float_spline;

kml_float_spline *kml_float_spline_alloc(const kml_float_interp_type *t, size_t size);

int kml_float_spline_init(kml_float_spline *spline, const float x_array[], const float y_array[], size_t size);

const char *kml_float_spline_name(const kml_float_spline *spline);

unsigned int kml_float_spline_min_size(const kml_float_spline *spline);

int kml_float_spline_eval_e(const kml_float_spline *spline, float x,
                            kml_interp_accel *a, float *y);

float kml_float_spline_eval(const kml_float_spline *spline, float x, kml_interp_accel *a);

int kml_float_spline_eval_deriv_e(const kml_float_spline *spline, float x,
                                  kml_interp_accel *a, float *dydx);

float kml_float_spline_eval_deriv(const kml_float_spline *spline, float x, kml_interp_accel *a);

int kml_float_spline_eval_deriv2_e(const kml_float_spline *spline, float x, kml_interp_accel *a,
                                   float *d2);

float kml_float_spline_eval_deriv2(const kml_float_spline *spline,
                                   float x, kml_interp_accel *a);

int kml_float_spline_eval_integ_e(const kml_float_spline *spline,
                                  float a, float b,
                                  kml_interp_accel *acc,
                                  float *result);

float kml_float_spline_eval_integ(const kml_float_spline *spline,
                                  float a, float b,
                                  kml_interp_accel *acc);

void kml_float_spline_free(kml_float_spline *spline);

__END_DECLS

#endif /* KML_INTERP_H */
