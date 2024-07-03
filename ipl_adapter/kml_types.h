/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2023. All rights reserved.
 * Description: DesignWare kunpeng interpolation library.
 * Author:
 * Create: 2023-09-14
 */

#ifndef KML_TYPES_H
#define KML_TYPES_H

#define likely(x) __builtin_expect(!!(x), 1)
#define unlikely(x) __builtin_expect(x, 0)

#ifndef KML_VAR

#ifdef WIN32
#  ifdef KML_DLL
#    ifdef DLL_EXPORT
#      define KML_VAR extern __declspec(dllexport)
#    else
#      define KML_VAR extern __declspec(dllimport)
#    endif
#  else
#    define KML_VAR extern
#  endif
#else
#  define KML_VAR extern
#endif

#endif

#endif /* KML_TYPES_H */
