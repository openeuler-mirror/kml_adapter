#!/bin/bash
# ------------------------------------------------------------------------------
# Copyright (c) 2020-2023 Huawei Technologies Co., Ltd. All rights reserved.
# ------------------------------------------------------------------------------
# Build libkscalapack_full.so for BoostKit's libkscalapack.so
# Amend symbols via objcopy
#
# See https://www.hikunpeng.com/document/detail/en/kunpengaccel/math-lib/devg-kml/kunpengaccel_kml_16_0348.html

set -eE

# Some helper functions --------------------------------------------------------

function INFORM { printf "\n====== $1\n" ; }
function DIE { printf "\nFATAL ERROR: $*\n" ; exit 1 ; }

INFORM "Define and check build and test parameters ($0)"

echo "LIBKSCALAPACK_SO       ${LIBKSCALAPACK_SO:=/usr/local/kml/lib/libkscalapack.so}"
echo "LIBKBLAS_SO            ${LIBKBLAS_SO:=$(dirname ${LIBKSCALAPACK_SO})/kblas/omp/libkblas.so}"
echo "SCALAPACK_SRC_DIR      ${SCALAPACK_SRC_DIR:=/undefined/SCALAPACK_SRC_DIR}"
echo "BUILD_DIR              ${BUILD_DIR:=${PWD}/tmp-build-scalapack}"
echo "CMAKE_BUILD_TYPE       ${CMAKE_BUILD_TYPE:=Release}"
echo "CTEST_PARALLEL_LEVEL   ${CTEST_PARALLEL_LEVEL:=8}"
echo "OMP_NUM_THREADS        ${OMP_NUM_THREADS:=8}"
echo "MPICC                  ${MPICC:=mpicc}"
echo "MPIFC                  ${MPIFC:=mpifort}"
echo "LIBKLAPACK_FULL_SO     ${LIBKLAPACK_FULL_SO:=${LIBKSCALAPACK_SO/kscalapack.so*/klapack_full.so}}"
echo "LDFLAGS_EXTRA          ${LDFLAGS_EXTRA}"
# result
echo "LIBKSCALAPACK_FULL_SO  ${LIBKSCALAPACK_FULL_SO:=${BUILD_DIR}/lib/libkscalapack_full.so}"

export CMAKE_BUILD_TYPE CTEST_PARALLEL_LEVEL OMP_NUM_THREADS

test -x ${LIBKSCALAPACK_SO} || DIE "invalid LIBKSCALAPACK_SO"
test -x ${LIBKBLAS_SO} || DIE "invalid LIBKBLAS_SO"
test -r ${SCALAPACK_SRC_DIR}/CMakeLists.txt || DIE "invalid SCALAPACK_SRC_DIR
Download hint:
    git clone https://github.com/Reference-ScaLAPACK/scalapack ${SCALAPACK_SRC_DIR}
"

# Add extra compiler flags -----------------------------------------------------

case $(${MPIFC} -std=legacy - </dev/null 2>&1) in
    *standard*input) export FFLAGS="$FFLAGS -std=legacy" ;;
esac

case $(${MPICC} -Wno-implicit-function-declaration - </dev/null 2>&1) in
    *standard*input) export CFLAGS="$CFLAGS -Wno-implicit-function-declaration" ;;
esac

#-------------------------------------------------------------------------------
INFORM "Configure BUILD_DIR for building STATIC libscalapack.a"

cmake_flags=(
    -DBLAS_LIBRARIES=/do/not/care
    -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    -DCMAKE_C_COMPILER=${MPICC}
    -DCMAKE_C_FLAGS_RELEASE="-O2 -DNDEBUG="
    -DCMAKE_Fortran_COMPILER=${MPIFC}
    -DCMAKE_POSITION_INDEPENDENT_CODE=ON
    -DCMAKE_RULE_MESSAGES=OFF
    -DCMAKE_VERBOSE_MAKEFILE=no
    -DLAPACK_FOUND=true
    -DLAPACK_LIBRARIES=/do/not/care
    -DSCALAPACK_BUILD_TESTS=off
)

( set -x ; mkdir -p ${BUILD_DIR} )
( set -x ; cd ${BUILD_DIR} ; cmake ${SCALAPACK_SRC_DIR} "${cmake_flags[@]}" )

#-------------------------------------------------------------------------------
INFORM "Build adapted libscalapack.a"

rm ${BUILD_DIR}/lib/libscalapack.a || true
( set -x ; cd ${BUILD_DIR} ; cmake --build . --parallel || cmake --build . --parallel 1 -v )

# ------------------------------------------------------------------------------
INFORM "Get symbols defined BOTH in KSCALAPACK and in Reference ScaLAPACK"

nm -g ${BUILD_DIR}/lib/libscalapack.a | grep -oP ' T \K\w+(?=_$)' | sort | uniq > netlib.sym
nm -g ${LIBKSCALAPACK_SO/kscalapack.so*/kscalapack.a} | grep -oP ' T \K\w+(?=_$)' | sort | uniq > kscalapack.sym
comm -12 kscalapack.sym netlib.sym > comm.sym

# ------------------------------------------------------------------------------
INFORM "Extract relevant modules and update symbol names"
( set -x ; mkdir -p ${BUILD_DIR}/mods )
while read sym; do
    (
        cd ${BUILD_DIR}/mods
        tloc=$(nm -gA --defined-only ${BUILD_DIR}/lib/libscalapack.a | grep " T ${sym}_\$")
        if [[ -n "${tloc}" ]]; then
            libmod=${tloc%:*}
            mod=${libmod#*:}
            ( set -x ; ar x ${BUILD_DIR}/lib/libscalapack.a ${mod} )
            ( set -x ; objcopy --redefine-sym ${sym}_=${sym}_netlib_ ${mod} )
        fi
    ) &
done < comm.sym
wait

ar d ${BUILD_DIR}/lib/libscalapack.a $(cd ${BUILD_DIR}/mods ; ls *.o)
( cd ${BUILD_DIR}/mods ; ar ru ${BUILD_DIR}/lib/libscalapack.a *.o )
( cd ${BUILD_DIR}/mods ; rm *.o )

#-------------------------------------------------------------------------------
INFORM "Create libkscalapack_full.so"

( set -x ; mkdir -p $(dirname ${LIBKSCALAPACK_FULL_SO}))

ldflags=(
    -Wl,--whole-archive
    -Wl,--start-group
    ${LIBKSCALAPACK_SO/kscalapack.so*/kscalapack.a}
    ${BUILD_DIR}/lib/libscalapack.a
    ${LIBKSCALAPACK_SO/kscalapack.so*/kservice.a}
    -Wl,--end-group
    -Wl,--no-whole-archive
    ${LDFLAGS_EXTRA}
)
( set -x ; ${MPIFC} "${ldflags[@]}" -shared -o ${LIBKSCALAPACK_FULL_SO} )

#-------------------------------------------------------------------------------
if [[ "$1" == "test" ]]; then

    INFORM "Fixup CMakeLists in SCALAPACK_SRC_DIR/TESTING"
    ( set -x ; sed -i -e 's/ scalapack / ${SCALAPACK_LIBRARIES} /' ${SCALAPACK_SRC_DIR}/TESTING/*/CMakeLists.txt )

    INFORM "Run tests with libkscalapack_full.so"

    function tests {
        local tmp_dir=$1 scalapack_libs=$2
        cmake_flags=(
            -DBUILD_TESTING=ON
            -DBLAS_LIBRARIES="${LIBKBLAS_SO}"
            -DLAPACK_LIBRARIES="${LIBKLAPACK_FULL_SO}"
            -DSCALAPACK_LIBRARIES="${scalapack_libs}"
            -DCMAKE_RULE_MESSAGES=OFF
            -DSCALAPACK_BUILD_TESTS=ON
            -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
            -DCMAKE_C_COMPILER=${MPICC}
            -DCMAKE_C_FLAGS_RELEASE="-O2 -DNDEBUG="
            -DCMAKE_Fortran_COMPILER=${MPIFC}
        )

        mkdir -p ${tmp_dir}
        ( set -x ; cd ${tmp_dir} ; cmake ${SCALAPACK_SRC_DIR} "${cmake_flags[@]}" )
        ( set -x ; cd ${tmp_dir} ; cmake --build . --parallel || cmake --build . --parallel 1 -v )
        ( set -x ; cd ${tmp_dir} ; ctest --output-on-failure -V)
        echo "FINISHED SCALAPACK TESTS IN ${tmp_dir}"
    }

    tests ${BUILD_DIR}-tests "${LIBKSCALAPACK_FULL_SO};${LIBKBLAS_SO};-fopenmp"
fi

# Report build results ---------------------------------------------------------

cat <<EOF
--------------------------------------------------------------------------------
FOR THIS KSCALAPACK LIBRARY (${kmlver}):
$(ls -lU ${LIBKSCALAPACK_SO} ${LIBKSCALAPACK_SO/kscalapack.so*/kscalapack.a})

WE HAVE BUILT FULL SCALAPACK LIBRARY:
$(ls -lU ${LIBKSCALAPACK_FULL_SO})
--------------------------------------------------------------------------------
EOF
