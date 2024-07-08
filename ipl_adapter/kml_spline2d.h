/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2023. All rights reserved.
 * Description: DesignWare kunpeng interpolation library.
 * Author:
 * Create: 2023-09-14
 */

#ifndef KML_SPLINE2D_H
#define KML_SPLINE2D_H

#include "kml_interp.h"
#include "kml_interp2d.h"

#undef __BEGIN_DECLS
#undef __END_DECLS
#ifdef __cplusplus
#define __BEGIN_DECLS extern "C" {
#define __END_DECLS }
#else
#define __BEGIN_DECLS /* empty */
#define __END_DECLS   /* empty */
#endif

__BEGIN_DECLS

/*
 * A 2D interpolation object which stores the arrays defining the function.
 * In all other respects, this is just like a kml_interp2d object.
 */
typedef struct {
    kml_float_interp2d interp_object; /* low-level interpolation object */
    float *xarr;                      /* x data array */
    float *yarr;                      /* y data array */
    float *zarr;                      /* z data array */
} kml_float_spline2d;

kml_float_spline2d *kml_float_spline2d_alloc(const kml_float_interp2d_type *t, size_t xsize, size_t ysize);

int kml_float_spline2d_init(kml_float_spline2d *interp, const float xarr[],
                            const float yarr[], const float zarr[],
                            size_t xsize, size_t ysize);

void kml_float_spline2d_free(kml_float_spline2d *interp);

float kml_float_spline2d_eval(const kml_float_spline2d *interp, const float x,
                              const float y, kml_interp_accel *xa, kml_interp_accel *ya);

int kml_float_spline2d_eval_e(const kml_float_spline2d *interp, const float x,
                              const float y, kml_interp_accel *xa, kml_interp_accel *ya,
                              float *z);

int kml_v_float_spline2d_eval_e(const kml_float_spline2d *interp, const float x[],
                                const float y[], size_t xin_size, size_t yin_size, float *z, size_t zin_size);

float kml_float_spline2d_eval_extrap(const kml_float_spline2d *interp, const float x,
                                     const float y, kml_interp_accel *xa, kml_interp_accel *ya);

int kml_float_spline2d_eval_extrap_e(const kml_float_spline2d *interp, const float x,
                                     const float y, kml_interp_accel *xa, kml_interp_accel *ya,
                                     float *z);

float kml_float_spline2d_eval_deriv_x(const kml_float_spline2d *interp, const float x,
                                      const float y, kml_interp_accel *xa, kml_interp_accel *ya);

int kml_float_spline2d_eval_deriv_x_e(const kml_float_spline2d *interp, const float x,
                                      const float y, kml_interp_accel *xa,
                                      kml_interp_accel *ya, float *z);

int kml_v_float_spline2d_eval_deriv_x_e(const kml_float_spline2d *interp, const float x[],
                                        const float y[], size_t xin_size, size_t yin_size, float *z, size_t zin_size);

float kml_float_spline2d_eval_deriv_y(const kml_float_spline2d *interp, const float x,
                                      const float y, kml_interp_accel *xa,
                                      kml_interp_accel *ya);

int kml_float_spline2d_eval_deriv_y_e(const kml_float_spline2d *interp, const float x,
                                      const float y, kml_interp_accel *xa,
                                      kml_interp_accel *ya, float *z);

int kml_v_float_spline2d_eval_deriv_y_e(const kml_float_spline2d *interp, const float x[],
                                        const float y[], size_t xin_size, size_t yin_size, float *z, size_t zin_size);

float kml_float_spline2d_eval_deriv_xx(const kml_float_spline2d *interp, const float x,
                                       const float y, kml_interp_accel *xa, kml_interp_accel *ya);

int kml_float_spline2d_eval_deriv_xx_e(const kml_float_spline2d *interp, const float x,
                                       const float y, kml_interp_accel *xa,
                                       kml_interp_accel *ya, float *z);

int kml_v_float_spline2d_eval_deriv_xx_e(const kml_float_spline2d *interp, const float x[],
                                         const float y[], size_t xin_size, size_t yin_size, float *z, size_t zin_size);


float kml_float_spline2d_eval_deriv_yy(const kml_float_spline2d *interp, const float x,
                                       const float y, kml_interp_accel *xa, kml_interp_accel *ya);

int kml_float_spline2d_eval_deriv_yy_e(const kml_float_spline2d *interp, const float x,
                                       const float y, kml_interp_accel *xa,
                                       kml_interp_accel *ya, float *z);

int kml_v_float_spline2d_eval_deriv_yy_e(const kml_float_spline2d *interp, const float x[],
                                         const float y[], size_t xin_size, size_t yin_size, float *z, size_t zin_size);


float kml_float_spline2d_eval_deriv_xy(const kml_float_spline2d *interp, const float x,
                                       const float y, kml_interp_accel *xa, kml_interp_accel *ya);

int kml_float_spline2d_eval_deriv_xy_e(const kml_float_spline2d *interp, const float x,
                                       const float y, kml_interp_accel *xa,
                                       kml_interp_accel *ya, float *z);

int kml_v_float_spline2d_eval_deriv_xy_e(const kml_float_spline2d *interp, const float x[],
                                         const float y[], size_t xin_size, size_t yin_size, float *z, size_t zin_size);


size_t kml_float_spline2d_min_size(const kml_float_spline2d *interp);

const char *kml_float_spline2d_name(const kml_float_spline2d *interp);

int kml_float_spline2d_set(const kml_float_spline2d *interp, float zarr[],
                           const size_t i, const size_t j, const float z);
float kml_float_spline2d_get(const kml_float_spline2d *interp, const float zarr[],
                             const size_t i, const size_t j);

__END_DECLS

#endif /* KML_SPLINE2D_H */
