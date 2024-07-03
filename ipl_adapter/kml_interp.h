/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2023. All rights reserved.
 * Description: DesignWare kunpeng interpolation library.
 * Author:
 * Create: 2023-09-14
 */

#ifndef KML_INTERP_H
#define KML_INTERP_H

#include <stdlib.h>
#include "kml_inline.h"
#include "kml_types.h"

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

/* evaluation accelerator */
typedef struct {
    size_t cache;      /* cache of index   */
    size_t miss_count; /* keep statistics  */
    size_t hit_count;
} kml_interp_accel;

/* interpolation object type */
typedef struct {
    const char *name;
    unsigned int min_size;
    void *(*alloc)(size_t size);
    int (*init)(void *, const float xa[], const float ya[], size_t size);
    int (*eval)(const void *, const float xa[], const float ya[], size_t size,
                float x, kml_interp_accel *, float *y);
    int (*eval_deriv)(const void *, const float xa[], const float ya[], size_t size, float x,
                      kml_interp_accel *, float *y_p);
    int (*eval_deriv2)(const void *, const float xa[], const float ya[], size_t size,
                       float x, kml_interp_accel *, float *y_pp);
    int (*eval_integ)(const void *, const float xa[], const float ya[], size_t size, kml_interp_accel *,
                      float a, float b, float *result);
    void (*free)(void *);
} kml_float_interp_type;

/* general interpolation object */
typedef struct {
    const kml_float_interp_type *type;
    float xmin;
    float xmax;
    size_t size;
    void *state;
} kml_float_interp;

/* available types */
KML_VAR const kml_float_interp_type *kml_float_interp_cspline;
KML_VAR const kml_float_interp_type *kml_float_interp_cspline_periodic;

kml_interp_accel *kml_interp_accel_alloc(void);

int kml_interp_accel_reset(kml_interp_accel *a);

void kml_interp_accel_free(kml_interp_accel *a);

kml_float_interp *kml_float_interp_alloc(const kml_float_interp_type *T, size_t size);

int kml_float_interp_init(kml_float_interp *interp, const float x_array[], const float y_array[], size_t size);

const char *kml_float_interp_name(const kml_float_interp *interp);
unsigned int kml_float_interp_min_size(const kml_float_interp *interp);
unsigned int kml_float_interp_type_min_size(const kml_float_interp_type *T);

int kml_float_interp_eval_e(const kml_float_interp *interp, const float xa[],
                            const float ya[], float x, kml_interp_accel *a, float *y);

float kml_float_interp_eval(const kml_float_interp *interp, const float xa[], const float ya[], float x,
                            kml_interp_accel *a);

int kml_float_interp_eval_deriv_e(const kml_float_interp *interp, const float xa[], const float ya[], float x,
                                  kml_interp_accel *a, float *dydx);

float kml_float_interp_eval_deriv(const kml_float_interp *interp, const float xa[], const float ya[], float x,
                                  kml_interp_accel *a);

int kml_float_interp_eval_deriv2_e(const kml_float_interp *interp, const float xa[], const float ya[], float x,
                                   kml_interp_accel *a, float *d2);

float kml_float_interp_eval_deriv2(const kml_float_interp *interp, const float xa[],
                                   const float ya[], float x, kml_interp_accel *a);

int kml_float_interp_eval_integ_e(const kml_float_interp *interp, const float xa[], const float ya[],
                                  float a, float b, kml_interp_accel *acc, float *result);

float kml_float_interp_eval_integ(const kml_float_interp *interp, const float xa[], const float ya[],
                                  float a, float b, kml_interp_accel *acc);

void kml_float_interp_free(kml_float_interp *interp);

INLINE_DECL size_t kml_float_interp_bsearch(const float x_array[], float x, size_t index_lo, size_t index_hi);

#ifdef HAVE_INLINE

/* Perform a binary search of an array of values.
 *
 * The parameters index_lo and index_hi provide an initial bracket,
 * and it is assumed that index_lo < index_hi. The resulting index
 * is guaranteed to be strictly less than index_hi and greater than
 * or equal to index_lo, so that the implicit bracket [index, index+1]
 * always corresponds to a region within the implicit value range of
 * the value array.
 *
 * Note that this means the relationship of 'x' to x_array[index]
 * and x_array[index+1] depends on the result region, i.e. the
 * behaviour at the boundaries may not correspond to what you
 * expect. We have the following complete specification of the
 * behaviour.
 * Suppose the input is x_array[] = { x0, x1, ..., xN }
 *    if ( x == x0 )           then  index == 0
 *    if ( x > x0 && x <= x1 ) then  index == 0, and sim. for other interior pts
 *    if ( x == xN )           then  index == N-1
 *    if ( x > xN )            then  index == N-1
 *    if ( x < x0 )            then  index == 0
 */

INLINE_FUN size_t kml_float_interp_bsearch(const float x_array[], float x, size_t index_lo, size_t index_hi)
{
    size_t ilo = index_lo;
    size_t ihi = index_hi;
    while (ihi > ilo + 1) {
        size_t i = (ihi + ilo) / 2;
        /* To avoid bisheng producing the csel intruction for selection judgment */
        float xaim = x_array[i];
        if (xaim > x) {
            ihi = i;
        } else if (xaim <= x) {
            ilo = i;
        }
    }

    return ilo;
}

#endif

INLINE_DECL size_t kml_float_interp_accel_find(kml_interp_accel *a, const float xa[], size_t len, float x);

#ifdef HAVE_INLINE

INLINE_FUN size_t kml_float_interp_accel_find(kml_interp_accel *a, const float xa[], size_t len, float x)
{
    size_t x_index = a->cache;

    if (x < xa[x_index]) {
        a->miss_count++;
        a->cache = kml_float_interp_bsearch(xa, x, 0, x_index);
    } else if (x >= xa[x_index + 1]) {
        a->miss_count++;
        a->cache = kml_float_interp_bsearch(xa, x, x_index, len - 1);
    } else {
        a->hit_count++;
    }

    return a->cache;
}

#endif /* HAVE_INLINE */

__END_DECLS

#endif /* KML_INTERP_H */
