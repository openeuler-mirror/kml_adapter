#!/bin/bash
# Copyright (c) 2022 Huawei Technologies Co., Ltd. All rights reserved.
#
# Use this script to build complementary ("adapted") lapack library
# for use with BoostKit KML KLAPACK library.

# Usage: ./build.sh [clean]

set -eE

option_cmake_build_type=Release
export CTEST_PARALLEL_LEVEL=8
export OMP_NUM_THREADS=8

# Some helper functions --------------------------------------------------------

function die {
    echo "FATAL ERROR: $*"
    exit 1
}

function ANNOUNCE {
    printf "\n===== $1\n"
}

# Require KML_ROOT, set paths, respect BUILD_ROOT ------------------------------

if test -z "${KML_ROOT}" ; then
    die 'Environment variable KML_ROOT must be set'
fi

kml_adapter_dir=$(cd $(dirname $0)/..; pwd)
lapack_adapt_dir=${kml_adapter_dir}/lapack-adapt
lapack_release_dir=${kml_adapter_dir}/lapack-release
build_root_dir=${BUILD_ROOT:-${kml_adapter_dir}}
tmp_build_dir=${build_root_dir}/tmp-build
tmp_test_dir=${build_root_dir}/tmp-test

# Handle optional 'clean' ------------------------------------------------------

case "$1" in
clean)
    ( rm -rf tmp-* )
    ;;
esac

# Define items used in this script ---------------------------------------------

# adapted lapack
liblapack_a=${tmp_build_dir}/lib/liblapack.a
liblapack1_a=${tmp_build_dir}/lib/liblapack1.a # complement libklapack.so
liblapack1_so=${tmp_build_dir}/lib/liblapack1.so # complement libklapack.so

# klapack
libklapack_a=${KML_ROOT}/lib/libklapack.a
libklapack_so=${KML_ROOT}/lib/libklapack.so
libkservice_a=${KML_ROOT}/lib/libkservice.a
libkservice_so=${KML_ROOT}/lib/libkservice.so
libklapack_full_a=${tmp_build_dir}/lib/libklapack_full.a
libklapack_full_so=${tmp_build_dir}/lib/libklapack_full.so
libkblas_so=${KML_ROOT}/lib/kblas/omp/libkblas.so

#-------------------------------------------------------------------------------
kmlver=$(strings ${libkservice_so} | grep -o 'VERSION.*COMPILER.*')
ANNOUNCE "Check if compilers are compatible with KML '${kmlver}'"

function check_compiler {
    local name=$1 parlor=$2
    case `${!name} --version 2>/dev/null` in
    *${parlor}*) echo "  Using ${name}=${!name}" ;;
    '') die "Missing compiler ${name}=${!name}" ;;
    *) die "Wrong compiler ${name}=${!name}" ;;
    esac
}

case ${kmlver} in
*COMPILER:GNU*)
    export CC=${CC:-gcc} FC=${FC:-gfortran}
    check_compiler CC 'GCC'
    check_compiler FC 'GNU Fortran'
    ;;

*COMPILER:Clang*)
    export CC=${CC:-clang} FC=${FC:-flang}
    check_compiler CC 'clang'
    check_compiler FC 'clang'
    ;;

*)
    die "Unknown KML version ${kmlver}"
    ;;
esac

# Determine libklapack names that we shall suffix with `_netlib` ---------------

names=$(
    nm -gD --defined-only ${libklapack_so} \
    | sed -n 's/.* T \(.*\)_/\1/p'
)

# Define patcher function ------------------------------------------------------

function add_suffix_netlib {
    local name=$1 src=$2
    if ! test -r ${src} ; then
        return
    fi
    if grep -Ei "^ {6,}SUBROUTINE +${name} *\(" ${src} >/dev/null ; then
        sed -Ee 's:^( {6,}SUBROUTINE +'${name}') *\(:\1_NETLIB\n     +    (:i' \
        ${src} >${src}.tmp
    fi
    if grep -Ei "^ {6,}.*FUNCTION +${name} *\(" ${src} >/dev/null ; then
        sed -Ee 's:^( {6,}.*FUNCTION +'${name}') *\(:\1_NETLIB\n     +    (:i' \
            -Ee 's:^(.* '${name}') *=:\1_NETLIB\n     +    =:i' \
        ${src} >${src}.tmp
    fi
    if grep -iw ${name}_NETLIB ${src} >/dev/null ; then
        cat ${src} >${src}.tmp
    fi
    if test -r ${src}.tmp ; then
        if diff ${src} ${src}.tmp >/dev/null 2>&1 ; then
            echo 'No change:' ${src}
            rm ${src}.tmp
        else
            echo 'Patched:  ' ${src}
            mv ${src}.tmp ${src}
        fi
    fi
}


#-------------------------------------------------------------------------------
ANNOUNCE "Configure lapack for building STATIC liblapack.a"

cmake_flags=(
    -DBUILD_SHARED_LIBS=OFF
    -DCMAKE_POSITION_INDEPENDENT_CODE=ON
    -DBUILD_TESTING=OFF
    -DCMAKE_BUILD_TYPE=${option_cmake_build_type}
    -DUSE_OPTIMIZED_BLAS=ON
    -DBLASLIB="${libkblas_so}"
    -DBLAS_LIBRARIES="${libkblas_so}"
    -DCMAKE_INSTALL_PREFIX=/dev/null
    -DCMAKE_RULE_MESSAGES=OFF
)

mkdir -p ${tmp_build_dir}
( set -x ; cd ${tmp_build_dir} ; cmake ${lapack_release_dir} "${cmake_flags[@]}" )

#-------------------------------------------------------------------------------
ANNOUNCE "Build liblapack1.{a,so}, for linking with libklapack.so"

( cd ${lapack_release_dir} && git checkout . )
for name in ${names} ; do
    add_suffix_netlib ${name} ${lapack_release_dir}/SRC/${name}.*
done
( set -x ; cd ${tmp_build_dir} ; cmake --build . --parallel || cmake --build . --parallel 1 -v )
( set -x ; cp -p ${liblapack_a} ${liblapack1_a} )

ld_group=(
    -Wl,--whole-archive
    -Wl,--start-group
    ${liblapack1_a}
    -Wl,--end-group
    -Wl,--no-whole-archive
)
( set -x ; ${FC} "${ld_group[@]}" -shared -o ${liblapack1_so} )

# Define testing function ------------------------------------------------------

function tests {
    local tmp_dir=${1:-tmp-dir} lapack_libs=$2
    cmake_flags=(
        -DCMAKE_BUILD_TYPE=${option_cmake_build_type}
        -DBUILD_TESTING=ON
        -DUSE_OPTIMIZED_BLAS=ON
        -DUSE_OPTIMIZED_LAPACK=ON
        -DBLASLIB="${libkblas_so}"
        -DBLAS_LIBRARIES="${libkblas_so}"
        -DLAPACKLIB="${lapack_libs}"
        -DLAPACK_LIBRARIES="${lapack_libs}"
        -DCMAKE_RULE_MESSAGES=OFF
    )

    mkdir -p ${tmp_dir}
    ( set -x ; cd ${tmp_dir} ; cmake ${lapack_release_dir} "${cmake_flags[@]}" )
    ( set -x ; cd ${tmp_dir} ; cmake --build . --parallel || cmake --build . --parallel 1 -v )
    ( set -x ; cd ${tmp_dir} ; ctest --output-on-failure )
    echo "FINISHED LAPACK TESTS IN ${tmp_dir}"
}

#-------------------------------------------------------------------------------
ANNOUNCE "Run tests with libklapack + liblapack1"

tests tmp-1 "${libklapack_so};${liblapack1_a};${libkservice_so};${libkblas_so};-fopenmp"
tests tmp-2 "${libklapack_so};${liblapack1_so};${libkservice_so};${libkblas_so};-fopenmp"

#-------------------------------------------------------------------------------
ANNOUNCE "Create libklapack_full.so"

ld_group=(
    -Wl,--whole-archive
    -Wl,--start-group
    ${libklapack_a}
    ${liblapack1_a}
    -Wl,--end-group
    -Wl,--no-whole-archive
)
( set -x ; ${FC} "${ld_group[@]}" -shared -o ${libklapack_full_so} )

#-------------------------------------------------------------------------------
ANNOUNCE "Run tests with libklapack_full.so"

tests tmp-3 "${libklapack_full_so};${libkservice_so};${libkblas_so};-fopenmp"

# Report build results ---------------------------------------------------------

cat <<EOF
--------------------------------------------------------------------------------
FOR THIS KLAPACK LIBRARY (${kmlver}):
$(ls -lU ${libklapack_a})

WE HAVE BUILT "ADAPTED" LAPACK and FULL LAPACK LIBRARIES:
$(ls -lU ${liblapack1_so} ${libklapack_full_so})
--------------------------------------------------------------------------------
EOF
