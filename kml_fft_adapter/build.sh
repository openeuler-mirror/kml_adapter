#!/bin/bash
set -e

LIB_ROOT_PATH=$(pwd)

# build library of double precision float
if [ ! -d "${LIB_ROOT_PATH}/build" ];then
    mkdir ${LIB_ROOT_PATH}/build
fi

cd ${LIB_ROOT_PATH}/build/
cmake ../ -DFFT_FLOAT_TYPE=double
make clean || exit "$?"
make -j32 2>&1 | tee -a $LIB_ROOT_PATH/build/build.log || exit "$?"

# build library of single precision float
cd ${LIB_ROOT_PATH}/build/
cmake ../ -DFFT_FLOAT_TYPE=float
make clean || exit "$?"
make -j32 2>&1 | tee -a $LIB_ROOT_PATH/build/build.log || exit "$?"
ln -s libfftw3.so.1.0.0 libfftw3.so.3
ln -s libfftw3.so.1.0.0 libfftw3_threads.so.3
ln -s libfftw3f.so.1.0.0 libfftw3f.so.3
ln -s libfftw3f.so.1.0.0 libfftw3f_threads.so.3
