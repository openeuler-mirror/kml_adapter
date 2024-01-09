# Introduction

KML LAPACK library provides selected optimized functions that represent a subset
of LAPACK API. Some optimized functions need to be linked to respective original
LAPACK functions by the name with suffix `_netlib`. Also, your application may
need a LAPACK function that KML LAPACK does not provide. The best way to satisfy
these requirements is to build *full KLAPACK* library.

Similarly, KML ScaLAPACK library provides selected optimized functions that
represent a subset of ScaLAPACK API. Your application may need a ScaLAPACK
function that KML ScaLAPACK does not provide. The best way to satisfy these
requirements is to build *full KScaLAPACK* library.

The scripts in this directory help you to build the *full KLAPACK* library and
*full KScaLAPACK* library.

> It is important that both *full KLAPACK* and *full KScaLAPACK* libraries are
> built with the same complier, for the built libraries have dependence on *the
> same Fortran runtime*.

Execution of the build scripts is controlled by environment variables with
reasonable default values.

Both script use the same approach to build the full libraries:
1. build Reference (Sca)LAPACK static library
2. *(as needed)* add suffix `_netlib` to selected symbols of the static library
   by means of
   [`objcopy`](https://www.man7.org/linux/man-pages/man1/objcopy.1.html) tool
3. combine the static optimized K(Sca)LAPACK library and the just built static
   library into resulting *full K(Sca)LAPACK* shared object library


# Building the full K(Sca)LAPACK libraries

1. Download the scripts (or clone this repository)
   - `build-full-klapack.sh` &mdash; for building *full KLAPACK*
   - `build-full-kscalapack.sh` &mdash; for building *full KScaLAPACK*

2. Download or clone Reference (Sca)LAPACK. The latest version is recommended
   - [Reference LAPACK](https://github.com/Reference-LAPACK/lapack)
   - [Reference ScaLAPACK](https://github.com/Reference-ScaLAPACK/scalapack)

3. (*recommended*) Create an environment setter script (`env.txt`) where you
   specify required variables (for both LAPACK and ScaLAPACK). For example:

   ```sh
   export LAPACK_SRC_DIR=~/lapack       # location of Reference LAPACK
   export SCALAPACK_SRC_DIR=~/scalapack # location of Reference ScaLAPACK

   export PATH=/tools/openmpi/bin:$PATH # MPI installation

   # where to plac resulting libs
   export LIBKLAPACK_FULL_SO=$PWD/res/libklapack_full.so
   export LIBKSCALAPACK_FULL_SO=$PWD/res/libkscalapack_full.so

   # optionally override other default values (see the scripts)
   ```

4. Build *full KLAPACK* library
   ```sh
   ( . env.txt ; ./build-full-klapack.sh )
   ```
   Expect the build to complete with lines like these:
   ```
   WE HAVE BUILT FULL LAPACK+LAPACKE LIBRARY:
   -rwxr-xr-x 1 user group 20991432 Dec 21 23:35 res/libklapack_full.so

   USE THESE HEADER FILES:
   -rw-r--r-- 1 user group   4214 Dec  1 17:57 tmp/include/lapacke_config.h
   -rw-r--r-- 1 user group 840098 Dec  1 17:57 tmp/include/lapacke.h
   -rw-r--r-- 1 user group    560 Dec 21 17:15 tmp/include/lapacke_mangling.h
   -rw-r--r-- 1 user group  33134 Dec  1 17:57 tmp/include/lapacke_utils.h
   -rw-r--r-- 1 user group 719021 Dec  1 17:57 tmp/include/lapack.h
   ```

   > Adding optional argument `test` on the build command line would trigger
   > testing of the full KLAPACK library just build.


5. Build *full KScaLAPACK* library
   ```sh
   ( . env.txt ; ./build-full-kscalapack.sh )
   ```
   > Adding optional argument `test` on the build command line would trigger
   > testing of the full KScaLAPACK library just build.
