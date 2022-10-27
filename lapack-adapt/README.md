# Introduction

KML_LAPACK library provides selected optimized functions that represent
a subset of LAPACK API. These functions *may need* to call original
LAPACK functions. Also, your application *may need* to call LAPACK
functions that KML_LAPACK does not provide. Therefore, for using KML_LAPACK you need to complement it with an *adapted LAPACK* library,
or build a *full KLAPACK* library.

Script [`build.sh`](build.sh) in this directory is to help you
with building *adapted LAPACK* and *full KLAPACK* libraries.

# Adapted LAPACK

Assuming the adapted LAPACK shared library is `${lapack1_so}`
(or static library `${lapack1_a}`) the application is linked
with KML LAPACK as follows:
```
gfortran ... ${klapack_so} ${lapack1_so} ${kservice_so} ${kblas_so} -fopenmp ...
gfortran ... ${klapack_so} ${lapack1_a} ${kservice_so} ${kblas_so} -fopenmp ...

```

In essence, the adapted LAPACK library
has some function names suffixed with `_netlib`.

# Full KLAPACK (KML LAPACK)

Assuming the full KLAPACK shared library is `${klapack_full_so}`
the application is linked with KML LAPACK as follows:
```
gfortran ... ${klapack_full_so} ${kservice_so} ${kblas_so} -fopenmp ...
```

# Building

This build script uses reference LAPACK source-code patching.
In order to build adapted LAPACK and full KLAPACK libraries you do:

1. Clone this repository in a writable location (script `lapack-adapt/build.sh`
   does in-place source code patching of `lapack-release` subdirectory)
2. Set environment variable `KML_ROOT` to point to location of your KML library
   installation, for example `export KML_ROOT=/usr/local/kml`
3. *(optionally)* Set environment variables `CC` and `FC` to point to compatible
   compiler (e.g. `export CC=gcc FC=gfortran`, or `export CC=clang FC=flang` for
   HUAWEI Bisheng compiler)
4. Run the build script, *optionally* pointing to a build directory, for example
   `BUILD_ROOT=$HOME/tmp-build ./lapack-adapt/build.sh`. Expect the build to
   complete with lines like these:
```
WE HAVE BUILT "ADAPTED" LAPACK and FULL LAPACK LIBRARIES:
-rwxr-xr-x 1 user group 5555555 Jun  6 12:48 /home/user/kml_adapter/tmp-build/lib/liblapack1.so
-rwxr-xr-x 1 user group 8888888 Jun  6 12:48 /home/user/kml_adapter/tmp-build/lib/libklapack_full.so
--------------------------------------------------------------------------------
```
5. Copy the abovementtioned created libraries to your preferred location
   for linking with


Another way to create the adapted LAPACK and full KLAPACK libraries
is desribed at ["generate complete LAPACK"](https://www.hikunpeng.com/document/detail/zh/kunpengaccel/math-lib/devg-kml/kunpengaccel_kml_16_0218.html) page.
It employs binary patching with `objcopy`.
