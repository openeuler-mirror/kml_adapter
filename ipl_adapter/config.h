/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2023. All rights reserved.
 * Description: DesignWare kunpeng interpolation library.
 * Author:
 * Create: 2023-09-14
 */

#ifndef CONFIG_H
#define CONFIG_H

/* Define if you have inline with C99 behavior */
#define HAVE_C99_INLINE 1

/* Define to 1 if you have the declaration of `acosh', and to 0 if you don't. */
#define HAVE_DECL_ACOSH 1

/* Define to 1 if you have the declaration of `asinh', and to 0 if you don't. */
#define HAVE_DECL_ASINH 1

/* Define to 1 if you have the declaration of `atanh', and to 0 if you don't. */
#define HAVE_DECL_ATANH 1

/* Define to 1 if you have the declaration of `expm1', and to 0 if you don't. */
#define HAVE_DECL_EXPM1 1

/* Define to 1 if you have the declaration of `finite', and to 0 if you don't. */
#define HAVE_DECL_FINITE 1

/* Define to 1 if you have the declaration of `frexp', and to 0 if you don't. */
#define HAVE_DECL_FREXP 1

/* Define to 1 if you have the declaration of `hypot', and to 0 if you don't. */
#define HAVE_DECL_HYPOT 1

/* Define to 1 if you have the declaration of `isfinite', and to 0 if you don't. */
#define HAVE_DECL_ISFINITE 1

/* Define to 1 if you have the declaration of `isinf', and to 0 if you don't. */
#define HAVE_DECL_ISINF 1

/* Define to 1 if you have the declaration of `isnan', and to 0 if you don't. */
#define HAVE_DECL_ISNAN 1

/* Define to 1 if you have the declaration of `ldexp', and to 0 if you don't. */
#define HAVE_DECL_LDEXP 1

/* Define to 1 if you have the declaration of `log1p', and to 0 if you don't. */
#define HAVE_DECL_LOG1P 1

/* Defined if you have ansi EXIT_SUCCESS and EXIT_FAILURE in stdlib.h */
#define HAVE_EXIT_SUCCESS_AND_FAILURE 1

/* Defined on architectures with excess floating-point precision */
#define HAVE_EXTENDED_PRECISION_REGISTERS 1

/* Define this if IEEE comparisons work correctly (e.g. NaN != NaN) */
#define HAVE_IEEE_COMPARISONS 1

/* Define if you have inline */
#define HAVE_INLINE 1

/* Define to 1 if you have the `vprintf' function. */
#define HAVE_VPRINTF 1

/* Define to 1 if you have the ANSI C header files. */
#define STDC_HEADERS 1

/* Use 0 and 1 for EXIT_SUCCESS and EXIT_FAILURE if we don't have them */
#if !HAVE_EXIT_SUCCESS_AND_FAILURE
#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1
#endif

/* Substitute kml functions for missing system functions */

#if !HAVE_DECL_HYPOT
#define hypot kml_hypot
#endif

#if !HAVE_DECL_LOG1P
#define log1p kml_log1p
#endif

#if !HAVE_DECL_EXPM1
#define expm1 kml_expm1
#endif

#if !HAVE_DECL_ACOSH
#define acosh kml_acosh
#endif

#if !HAVE_DECL_ASINH
#define asinh kml_asinh
#endif

#if !HAVE_DECL_ATANH
#define atanh kml_atanh
#endif

#if !HAVE_DECL_LDEXP
#define ldexp kml_ldexp
#endif

#if !HAVE_DECL_FREXP
#define frexp kml_frexp
#endif

#if !HAVE_DECL_ISINF
#define isinf kml_isinf
#endif

#if !HAVE_DECL_ISFINITE
#define isfinite kml_finite
#endif

#if !HAVE_DECL_FINITE
#define finite kml_finite
#endif

#if !HAVE_DECL_ISNAN
#define isnan kml_isnan
#endif

#if defined(KML_RANGE_CHECK_OFF) || !defined(KML_RANGE_CHECK)
#define KML_RANGE_CHECK 0 /* turn off range checking by default internally */
#endif

#endif /* CONFIG_H */
