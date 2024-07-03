/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2023. All rights reserved.
 * Description: DesignWare kunpeng interpolation library.
 * Author:
 * Create: 2023-09-14
 */

#ifndef KML_INTERP2D_H
#define KML_INTERP2D_H

#include "kml_interp.h"

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

typedef struct {
    const char *name;
    unsigned int min_size;
    void *(*alloc)(size_t xsize, size_t ysize);
    int (*init)(void *, const float xa[], const float ya[], const float za[], size_t xsize, size_t ysize);
    int (*eval)(const void *, const float xa[], const float ya[], const float za[], size_t xsize, size_t ysize,
                float x, float y, kml_interp_accel *, kml_interp_accel *, float *z);
    int (*eval_deriv_x)(const void *, const float xa[], const float ya[], const float za[], size_t xsize,
                        size_t ysize, float x, float y, kml_interp_accel *, kml_interp_accel *, float *z_p);
    int (*eval_deriv_y)(const void *, const float xa[], const float ya[], const float za[], size_t xsize,
                        size_t ysize, float x, float y, kml_interp_accel *, kml_interp_accel *, float *z_p);
    int (*eval_deriv_xx)(const void *, const float xa[], const float ya[], const float za[], size_t xsize,
                         size_t ysize, float x, float y, kml_interp_accel *, kml_interp_accel *, float *z_pp);
    int (*eval_deriv_xy)(const void *, const float xa[], const float ya[], const float za[], size_t xsize,
                         size_t ysize, float x, float y, kml_interp_accel *, kml_interp_accel *, float *z_pp);
    int (*eval_deriv_yy)(const void *, const float xa[], const float ya[], const float za[], size_t xsize,
                         size_t ysize, float x, float y, kml_interp_accel *, kml_interp_accel *, float *z_pp);
    int (*v_eval)(const void *, const float xa[], const float ya[], const float za[], size_t xsize, size_t ysize,
        const float x[], const float y[], size_t xin_size, size_t yin_size, float *z, size_t zin_size);
    int (*v_eval_deriv_x)(const void *, const float xa[], const float ya[], const float za[], size_t xsize,
                          size_t ysize, const float x[], const float y[], size_t xin_size, size_t yin_size, float *z,
                          size_t zin_size);
    int (*v_eval_deriv_y)(const void *, const float xa[], const float ya[], const float za[], size_t xsize,
                          size_t ysize, const float x[], const float y[], size_t xin_size, size_t yin_size, float *z,
                          size_t zin_size);
    int (*v_eval_deriv_xx)(const void *, const float xa[], const float ya[], const float za[], size_t xsize,
                           size_t ysize, const float x[], const float y[], size_t xin_size, size_t yin_size, float *z,
                           size_t zin_size);
    int (*v_eval_deriv_xy)(const void *, const float xa[], const float ya[], const float za[], size_t xsize,
                           size_t ysize, const float x[], const float y[], size_t xin_size, size_t yin_size, float *z,
                           size_t zin_size);
    int (*v_eval_deriv_yy)(const void *, const float xa[], const float ya[], const float za[], size_t xsize,
                           size_t ysize, const float x[], const float y[], size_t xin_size, size_t yin_size, float *z,
                           size_t zin_size);
    void (*free)(void *);
} kml_float_interp2d_type;

typedef struct {
    const kml_float_interp2d_type *type; /* interpolation type */
    float xmin;                          /* minimum value of x for which data have been provided */
    float xmax;                          /* maximum value of x for which data have been provided */
    float ymin;                          /* minimum value of y for which data have been provided */
    float ymax;                          /* maximum value of y for which data have been provided */
    size_t xsize;                        /* number of x values provided */
    size_t ysize;                        /* number of y values provided */
    void *state;                         /* internal state object specific to the interpolation type */
} kml_float_interp2d;

/* available types */
KML_VAR const kml_float_interp2d_type *kml_float_interp2d_bilinear;
KML_VAR const kml_float_interp2d_type *kml_float_interp2d_bicubic;

kml_float_interp2d *kml_float_interp2d_alloc(const kml_float_interp2d_type *T, const size_t xsize, const size_t ysize);

const char *kml_float_interp2d_name(const kml_float_interp2d *interp);
size_t kml_float_interp2d_min_size(const kml_float_interp2d *interp);
size_t kml_float_interp2d_type_min_size(const kml_float_interp2d_type *T);
int kml_float_interp2d_set(const kml_float_interp2d *interp, float zarr[],
                           const size_t i, const size_t j, const float z);
float kml_float_interp2d_get(const kml_float_interp2d *interp, const float zarr[], const size_t i, const size_t j);
size_t kml_float_interp2d_idx(const kml_float_interp2d *interp, const size_t i, const size_t j);
int kml_float_interp2d_init(kml_float_interp2d *interp, const float xarr[], const float yarr[],
                            const float zarr[], const size_t xsize, const size_t ysize);
void kml_float_interp2d_free(kml_float_interp2d *interp);

float kml_float_interp2d_eval(const kml_float_interp2d *interp, const float xarr[],
                              const float yarr[], const float zarr[], const float x,
                              const float y, kml_interp_accel *xa, kml_interp_accel *ya);

float kml_float_interp2d_eval_extrap(const kml_float_interp2d *interp, const float xarr[], const float yarr[],
                                     const float zarr[], const float x, const float y, kml_interp_accel *xa,
                                     kml_interp_accel *ya);

int kml_float_interp2d_eval_e(const kml_float_interp2d *interp, const float xarr[],
                              const float yarr[], const float zarr[], const float x, const float y,
                              kml_interp_accel *xa, kml_interp_accel *ya, float *z);

int kml_v_float_interp2d_eval_e(const kml_float_interp2d *interp, const float xarr[],
                                const float yarr[], const float zarr[], const float x[], const float y[],
                                size_t xin_size, size_t yin_size, float *z, size_t zin_size);

#ifndef KML_DISABLE_DEPRECATED

int kml_float_interp2d_eval_e_extrap(const kml_float_interp2d *interp, const float xarr[],
                                     const float yarr[], const float zarr[], const float x, const float y,
                                     kml_interp_accel *xa, kml_interp_accel *ya, float *z);

#endif /* !KML_DISABLE_DEPRECATED */
int kml_float_interp2d_eval_extrap_e(const kml_float_interp2d *interp, const float xarr[],
                                     const float yarr[], const float zarr[], const float x, const float y,
                                     kml_interp_accel *xa, kml_interp_accel *ya, float *z);

float kml_float_interp2d_eval_deriv_x(const kml_float_interp2d *interp, const float xarr[],
                                      const float yarr[], const float zarr[], const float x, const float y,
                                      kml_interp_accel *xa, kml_interp_accel *ya);

int kml_float_interp2d_eval_deriv_x_e(const kml_float_interp2d *interp, const float xarr[],
                                      const float yarr[], const float zarr[], const float x, const float y,
                                      kml_interp_accel *xa, kml_interp_accel *ya, float *z);

int kml_v_float_interp2d_eval_deriv_x_e(const kml_float_interp2d *interp, const float xarr[],
                                        const float yarr[], const float zarr[], const float x[], const float y[],
                                        size_t xin_size, size_t yin_size, float *z, size_t zin_size);

float kml_float_interp2d_eval_deriv_y(const kml_float_interp2d *interp, const float xarr[],
                                      const float yarr[], const float zarr[], const float x, const float y,
                                      kml_interp_accel *xa, kml_interp_accel *ya);

int kml_float_interp2d_eval_deriv_y_e(const kml_float_interp2d *interp, const float xarr[],
                                      const float yarr[], const float zarr[], const float x, const float y,
                                      kml_interp_accel *xa, kml_interp_accel *ya, float *z);

int kml_v_float_interp2d_eval_deriv_y_e(const kml_float_interp2d *interp, const float xarr[],
                                        const float yarr[], const float zarr[], const float x[], const float y[],
                                        size_t xin_size, size_t yin_size, float *z, size_t zin_size);

float kml_float_interp2d_eval_deriv_xx(const kml_float_interp2d *interp, const float xarr[],
                                       const float yarr[], const float zarr[], const float x, const float y,
                                       kml_interp_accel *xa, kml_interp_accel *ya);

int kml_float_interp2d_eval_deriv_xx_e(const kml_float_interp2d *interp, const float xarr[],
                                       const float yarr[], const float zarr[], const float x, const float y,
                                       kml_interp_accel *xa, kml_interp_accel *ya, float *z);

int kml_v_float_interp2d_eval_deriv_xx_e(const kml_float_interp2d *interp, const float xarr[],
                                         const float yarr[], const float zarr[], const float x[], const float y[],
                                         size_t xin_size, size_t yin_size, float *z, size_t zin_size);

float kml_float_interp2d_eval_deriv_yy(const kml_float_interp2d *interp, const float xarr[],
                                       const float yarr[], const float zarr[], const float x, const float y,
                                       kml_interp_accel *xa, kml_interp_accel *ya);

int kml_float_interp2d_eval_deriv_yy_e(const kml_float_interp2d *interp, const float xarr[],
                                       const float yarr[], const float zarr[], const float x, const float y,
                                       kml_interp_accel *xa, kml_interp_accel *ya, float *z);

int kml_v_float_interp2d_eval_deriv_yy_e(const kml_float_interp2d *interp, const float xarr[],
                                         const float yarr[], const float zarr[], const float x[], const float y[],
                                         size_t xin_size, size_t yin_size, float *z, size_t zin_size);

float kml_float_interp2d_eval_deriv_xy(const kml_float_interp2d *interp, const float xarr[],
                                       const float yarr[], const float zarr[], const float x, const float y,
                                       kml_interp_accel *xa, kml_interp_accel *ya);

int kml_float_interp2d_eval_deriv_xy_e(const kml_float_interp2d *interp, const float xarr[],
                                       const float yarr[], const float zarr[], const float x, const float y,
                                       kml_interp_accel *xa, kml_interp_accel *ya, float *z);

int kml_v_float_interp2d_eval_deriv_xy_e(const kml_float_interp2d *interp, const float xarr[],
                                         const float yarr[], const float zarr[], const float x[], const float y[],
                                         size_t xin_size, size_t yin_size, float *z, size_t zin_size);

__END_DECLS

#endif /* KML_INTERP2D_H */
