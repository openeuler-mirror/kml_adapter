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
make install

# build library of single precision float
cd ${LIB_ROOT_PATH}/build/
cmake ../ -DFFT_FLOAT_TYPE=float
make clean || exit "$?"
make -j32 2>&1 | tee -a $LIB_ROOT_PATH/build/build.log || exit "$?"
make install
