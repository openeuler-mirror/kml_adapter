#!/bin/bash
set -e

LIB_ROOT_PATH=$(cd $(dirname $0)/..; pwd)/Julia_adapter

if [ ! -d "${LIB_ROOT_PATH}/output" ];then
    mkdir ${LIB_ROOT_PATH}/output
fi

if [ ! -d "${LIB_ROOT_PATH}/../tmp-build/lib/libklapack_full.so" ];then
    sh ${LIB_ROOT_PATH}/../lapack-adapt/build.sh
fi

cd ${LIB_ROOT_PATH}/output/
cmake ../ -DLAPACK_FULL_DIRECTORY=${LIB_ROOT_PATH}/../tmp-build/lib/
make clean || exit "$?"
make -j32 2>&1 | tee -a $LIB_ROOT_PATH/output/build.log || exit "$?"

