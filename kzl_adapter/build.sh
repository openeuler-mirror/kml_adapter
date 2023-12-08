#!/bin/bash
# KZL test 
# Copyright 2023 Huawei Technologies Co., Ltd

set -e

function main()
{
    unzip BoostKit-KZL_1.0.0.zip
    tar -zxvf lz4-1.9.3.tar.gz
    patch -p0 < ./lz4_kzl.patch
    cp ./kzl.a ./lz4_accelerater.h ./lz4-1.9.3/lib
    cd lz4-1.9.3/lib
    ar -x kzl.a
    cd ..
    make -j
}

main $@