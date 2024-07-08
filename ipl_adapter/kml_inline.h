/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2023. All rights reserved.
 * Description: DesignWare kunpeng interpolation library.
 * Author:
 * Create: 2023-09-14
 */

#ifndef KML_INLINE_H
#define KML_INLINE_H

#include "config.h"

/*
 * In recent versiions of GCC, the inline keyword has two different
 * forms: GNU and C99.

 * In GNU mode we can use 'extern inline' to make inline functions
 * work like macros.  The function is only inlined--it is never output
 * as a definition in an object file.

 * In the new C99 mode 'extern inline' has a different meaning--it
 * causes the definition of the function to be output in each object
 * file where it is used.  This will result in multiple-definition
 * errors on linking.  The 'inline' keyword on its own (without
 * extern) has the same behavior as the original GNU 'extern inline'.

 * The C99 style is the default with -std=c99 in GCC 4.3.

 * This header file allows either form of inline to be used by
 * redefining the macros INLINE_DECL and INLINE_FUN.  These are used
 * in the public header files as
 */

#ifdef HAVE_INLINE
#if defined(__GNUC_STDC_INLINE__) || defined(KML_C99_INLINE) || defined(HAVE_C99_INLINE)
#define INLINE_DECL static inline /* use C99 inline */
#define INLINE_FUN static inline
#else
#define INLINE_DECL /* use GNU extern inline */
#define INLINE_FUN extern inline
#endif
#else
#define INLINE_DECL
#endif

/*
 * Range checking conditions in headers do not require any run-time
 * tests of the global variable kml_check_range. They are enabled or
 * disabled in user code at compile time with KML_RANGE_CHECK macro.
 * See also build.h.
 */
#define KML_RANGE_COND(x) (x)

#endif /* KML_INLINE_H */
