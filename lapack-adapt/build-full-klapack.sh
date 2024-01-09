#!/bin/bash
# ------------------------------------------------------------------------------
# Copyright (c) 2020-2023 Huawei Technologies Co., Ltd. All rights reserved.
# ------------------------------------------------------------------------------
# Build libklapack_full.so for BoostKit's libklapack.so
# Amend symbols via objcopy
#
# See https://www.hikunpeng.com/document/detail/en/kunpengaccel/math-lib/devg-kml/kunpengaccel_kml_16_0218.html

set -eE

# Some helper functions --------------------------------------------------------

function INFORM { printf "\n====== $1\n" ; }
function DIE { printf "\nFATAL ERROR: $*\n" ; exit 1 ; }

INFORM "Define and check build and test parameters ($0)"

echo "LIBKLAPACK_SO         ${LIBKLAPACK_SO:=/usr/local/kml/lib/libklapack.so}"
echo "LIBKBLAS_SO           ${LIBKBLAS_SO:=$(dirname ${LIBKLAPACK_SO})/kblas/omp/libkblas.so}"
echo "LAPACK_SRC_DIR        ${LAPACK_SRC_DIR:=/undefined/LAPACK_SRC_DIR}"
echo "BUILD_DIR             ${BUILD_DIR:=${PWD}/tmp-build-lapack}"
echo "CMAKE_BUILD_TYPE      ${CMAKE_BUILD_TYPE:=Release}"
echo "CTEST_PARALLEL_LEVEL  ${CTEST_PARALLEL_LEVEL:=8}"
echo "OMP_NUM_THREADS       ${OMP_NUM_THREADS:=8}"
echo "LDFLAGS_EXTRA         ${LDFLAGS_EXTRA}"
# result
echo "LIBKLAPACK_FULL_SO    ${LIBKLAPACK_FULL_SO:=${BUILD_DIR}/lib/libklapack_full.so}"

export CMAKE_BUILD_TYPE CTEST_PARALLEL_LEVEL OMP_NUM_THREADS

test -x ${LIBKLAPACK_SO} || DIE "invalid LIBKLAPACK_SO"
test -x ${LIBKBLAS_SO} || DIE "invalid LIBKBLAS_SO"
test -r ${LAPACK_SRC_DIR}/SRC/dgetrf.f || DIE "invalid LAPACK_SRC_DIR
Download hint:
    git clone https://github.com/Reference-LAPACK/lapack ${LAPACK_SRC_DIR}
"

#-------------------------------------------------------------------------------
kmlver=$(strings ${LIBKLAPACK_SO/klapack.so*/kservice.so} | grep -o 'VERSION.*COMPILER.*')
INFORM "Check if compilers are compatible with KML '${kmlver}'"

function check_compiler {
    local name=$1 parlor=$2
    case `${!name} --version 2>/dev/null` in
    *${parlor}*) echo "  Using ${name}=${!name}" ;;
    '') DIE "Missing compiler ${name}=${!name}" ;;
    *) DIE "Wrong compiler ${name}=${!name}" ;;
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
    DIE "Unknown KML version ${kmlver}"
    ;;
esac

#-------------------------------------------------------------------------------
INFORM "Configure BUILD_DIR for building STATIC liblapack.a and liblapacke.a"

cmake_flags=(
    -DBLAS_LIBRARIES="${LIBKBLAS_SO}"
    -DBLASLIB="${LIBKBLAS_SO}"
    -DBUILD_DEPRECATED=ON
    -DBUILD_SHARED_LIBS=OFF
    -DBUILD_TESTING=OFF
    -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    -DCMAKE_INSTALL_PREFIX=/dev/null
    -DCMAKE_POSITION_INDEPENDENT_CODE=ON
    -DCMAKE_RULE_MESSAGES=OFF
    -DLAPACKE=ON
    -DUSE_OPTIMIZED_BLAS=ON
)

( set -x ; mkdir -p ${BUILD_DIR} )
( set -x ; cd ${BUILD_DIR} ; cmake ${LAPACK_SRC_DIR} "${cmake_flags[@]}" )

#-------------------------------------------------------------------------------
INFORM "Build adapted liblapack.a, and liblapacke.a"

rm ${BUILD_DIR}/lib/liblapack.a || true
rm ${BUILD_DIR}/lib/liblapacke.a || true
( set -x ; cd ${BUILD_DIR} ; cmake --build . --parallel || cmake --build . --parallel 1 -v )
ar d ${BUILD_DIR}/lib/liblapack.a xerbla.f.o

# ------------------------------------------------------------------------------
INFORM "Get symbols defined BOTH in KLAPACK and in Reference LAPACK"

nm -g ${BUILD_DIR}/lib/liblapack.a | grep -oP ' T \K\w+(?=_$)' | sort | uniq > netlib.sym
nm -g ${LIBKLAPACK_SO/klapack.so*/klapack.a} | grep -oP ' T \K\w+(?=_$)' | sort | uniq > klapack.sym
comm -12 klapack.sym netlib.sym > comm.sym

# ------------------------------------------------------------------------------
INFORM "Extract relevant modules and update symbol names"
( set -x ; mkdir -p ${BUILD_DIR}/mods )
while read sym; do
    (
        cd ${BUILD_DIR}/mods
        tloc=$(nm -gA --defined-only ${BUILD_DIR}/lib/liblapack.a | grep " T ${sym}_\$")
        if [[ -n "${tloc}" ]]; then
            libmod=${tloc%:*}
            mod=${libmod#*:}
            ( set -x ; ar x ${BUILD_DIR}/lib/liblapack.a ${mod} )
            ( set -x ; objcopy --redefine-sym ${sym}_=${sym}_netlib_ ${mod} )
        fi
    ) &
done < comm.sym
wait

ar d ${BUILD_DIR}/lib/liblapack.a $(cd ${BUILD_DIR}/mods ; ls *.o)
( cd ${BUILD_DIR}/mods ; ar ru ${BUILD_DIR}/lib/liblapack.a *.o )
( cd ${BUILD_DIR}/mods ; rm *.o )

#-------------------------------------------------------------------------------
INFORM "Amend libkservice.a before building libklapack_full.so"

libkservice_fixed_a=${BUILD_DIR}/lib/libkservice_fixed.a
( set -x ; cp -p ${LIBKLAPACK_SO/klapack.so*/kservice.a} ${libkservice_fixed_a})
( set -x ; ar d ${libkservice_fixed_a} timer.c.o || true )

#-------------------------------------------------------------------------------
INFORM "Create libklapack_full.so"

( set -x ; mkdir -p $(dirname ${LIBKLAPACK_FULL_SO}))

ldflags=(
    -Wl,--whole-archive
    -Wl,--start-group
    ${LIBKLAPACK_SO/klapack.so*/klapack.a}
    ${BUILD_DIR}/lib/liblapack.a
    ${BUILD_DIR}/lib/liblapacke.a
    ${libkservice_fixed_a}
    -Wl,--end-group
    -Wl,--no-whole-archive
    ${LDFLAGS_EXTRA}
)
( set -x ; ${FC} "${ldflags[@]}" -shared -o ${LIBKLAPACK_FULL_SO} )

#-------------------------------------------------------------------------------
if [[ "$1" == "test" ]]; then

    INFORM "Run tests with libklapack_full.so"

    function tests {
        local tmp_dir=$1 lapack_libs=$2
        cmake_flags=(
            -DBUILD_TESTING=ON
            -DUSE_OPTIMIZED_BLAS=ON
            -DUSE_OPTIMIZED_LAPACK=ON
            -DBLAS_LIBRARIES="${LIBKBLAS_SO}"
            -DLAPACK_LIBRARIES="${lapack_libs}"
            -DCMAKE_RULE_MESSAGES=OFF
            -DLAPACKE=ON
        )

        mkdir -p ${tmp_dir}
        ( set -x ; cd ${tmp_dir} ; cmake ${LAPACK_SRC_DIR} "${cmake_flags[@]}" )
        ( set -x ; cd ${tmp_dir} ; cmake --build . --parallel || cmake --build . --parallel 1 -v )
        ( set -x ; cd ${tmp_dir} ; ctest --output-on-failure )
        echo "FINISHED LAPACK TESTS IN ${tmp_dir}"
    }

    tests ${BUILD_DIR}-tests "${LIBKLAPACK_FULL_SO};${LIBKBLAS_SO};-fopenmp"
fi

# Report build results ---------------------------------------------------------

cat <<EOF
--------------------------------------------------------------------------------
FOR THIS KLAPACK LIBRARY (${kmlver}):
$(ls -lU ${LIBKLAPACK_SO} ${LIBKLAPACK_SO/klapack.so*/klapack.a})

WE HAVE BUILT FULL LAPACK+LAPACKE LIBRARY:
$(ls -lU ${LIBKLAPACK_FULL_SO})

USE THESE HEADER FILES:
$(ls -lU ${BUILD_DIR}/include/*.h)
--------------------------------------------------------------------------------
EOF
