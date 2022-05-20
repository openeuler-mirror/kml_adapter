#!/bin/bash

# Set paths, respect BUILD_ROOT, require KML_ROOT ------------------------------

kml_adapter_dir=$(cd $(dirname $0)/..; pwd)
lapack_adapt_dir=${kml_adapter_dir}/lapack-adapt
lapack_release_dir=${kml_adapter_dir}/lapack-release
build_root_dir=${BUILD_ROOT:-${kml_adapter_dir}}
tmp_build_dir=${build_root_dir}/tmp-build
tmp_install_dir=${build_root_dir}/tmp-install

if test -z "${KML_ROOT}" ; then
    echo '
    ERROR: Environment variable KML_ROOT is not set
    '
    exit 1
fi

# Obtain list of libklapack references to names suffixed with `_netlib` --------

names=$(
    nm ${KML_ROOT}/lib/libklapack.so \
    | grep 'U .*_netlib_' \
    | sed 's/U \(.*\)_netlib_/\1/'
)

# Define patcher function ------------------------------------------------------

function add_suffix_netlib {
    local name=$1 src=$2
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

# For each of the names patch respective source --------------------------------

for name in ${names} ; do
    add_suffix_netlib ${name} ${lapack_release_dir}/SRC/${name}.*
done

# Fix lapack test system for using klapack -------------------------------------

for cmakelists_txt in \
    ${lapack_release_dir}/TESTING/{LIN,EIG}/CMakeLists.txt \
    ${lapack_release_dir}/LAPACKE/example/CMakeLists.txt \
    ; do
    if ! grep KML_LIBS ${cmakelists_txt} >/dev/null ; then
        sed -i 's:\(target_link_lib.*\) \(${LAPACK\):\1 ${KML_LIBS} \2:' \
            ${cmakelists_txt}
    fi
done

# Configure, build, install adapted lapack -------------------------------------

cmake_flags=(
    -DBUILD_SHARED_LIBS=ON
    -DBUILD_TESTING=ON
    -DCBLAS=ON
    -DCMAKE_BUILD_TYPE=Release
    -DCMAKE_EXE_LINKER_FLAGS="-L${KML_ROOT}/lib"
    -DKML_LIBS="-lklapack -lkservice"
    -DCMAKE_INSTALL_PREFIX=${tmp_install_dir}
    -DCMAKE_SKIP_RPATH=ON
    -DLAPACKE_WITH_TMG=OFF
    -DLAPACKE=ON
)

set -Ex

mkdir -p ${tmp_build_dir}
( cd ${tmp_build_dir} ; cmake ${lapack_release_dir} "${cmake_flags[@]}" )
( cd ${tmp_build_dir} ; cmake --build . --parallel || cmake --build . --parallel 1 -v )
( cd ${tmp_build_dir} ; cmake --install . )

# Test adapted lapack ----------------------------------------------------------

export LD_LIBRARY_PATH=${KML_ROOT}/lib:${tmp_install_dir}/lib64:${LD_LIBRARY_PATH}
export CTEST_PARALLEL_LEVEL=1
export OMP_NUM_THREADS=8
( cd ${tmp_build_dir} ; ctest --output-on-failure )
