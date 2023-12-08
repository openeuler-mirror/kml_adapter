#!/bin/bash
# KZL test 
# Copyright 2023 Huawei Technologies Co., Ltd

set -e

Kunpeng_PATH=$(pwd)

function glibc_build()
{
	if [ ! -d glibc-2.17 ]; then
		tar -xf glibc-2.17-patch-1910.tar.gz
		tar -xf glibc-2.31.tar.gz
		tar -xf glibc-2.32.tar.gz

		mkdir final_package
		cp ${Kunpeng_PATH}/glibc-2.31/sysdeps/generic/dwarf2.h ${Kunpeng_PATH}/final_package/
		cp ${Kunpeng_PATH}/glibc-2.31/sysdeps/aarch64/memset-reg.h ${Kunpeng_PATH}/final_package/
		cp ${Kunpeng_PATH}/glibc-2.31/sysdeps/generic/sysdep.h  ${Kunpeng_PATH}/final_package/
		mv ${Kunpeng_PATH}/final_package/sysdep.h  ${Kunpeng_PATH}/final_package/sysdep_generic.h

		cp ${Kunpeng_PATH}/glibc-2.17/sysdeps/aarch64/port_aarch64.h ${Kunpeng_PATH}/final_package/
		cp ${Kunpeng_PATH}/glibc-2.17/sysdeps/aarch64/memcmp.S ${Kunpeng_PATH}/final_package/
		cp ${Kunpeng_PATH}/glibc-2.17/sysdeps/aarch64/memset.S ${Kunpeng_PATH}/final_package/

		cp ${Kunpeng_PATH}/glibc-2.32/sysdeps/aarch64/multiarch/memcpy_falkor.S ${Kunpeng_PATH}/final_package/
		mv ${Kunpeng_PATH}/final_package/memcpy_falkor.S  ${Kunpeng_PATH}/final_package/memcpy.S

		cp ${Kunpeng_PATH}/glibc_kzl.patch ${Kunpeng_PATH}/final_package	
		cd ${Kunpeng_PATH}/final_package
		patch --quiet -p1 < glibc_kzl.patch

		gcc memcmp.S -march=armv8-a+lse -fPIC -shared -o kunpeng_memcmp.o
		gcc memcpy.S -march=armv8-a+lse -fPIC -shared -o kunpeng_memcpy.o
		gcc memset.S -march=armv8-a+lse -fPIC -shared -o kunpeng_memset.o
		
		cp kunpeng_memcmp.o ${Kunpeng_PATH}/
		cp kunpeng_memcpy.o ${Kunpeng_PATH}/
		cp kunpeng_memset.o ${Kunpeng_PATH}/
		
		
		cp ${Kunpeng_PATH}/BoostKit-KZL_1.0.0/kzl.a ./
		ar -x kzl.a
		ar -rcs kzl.a ./init.o ./lz4_accelerater.o ./lz4_cpu_checker.o ./kunpeng_memcmp.o ./kunpeng_memcpy.o ./kunpeng_memset.o
		rm -f ${Kunpeng_PATH}/kunpeng_memcmp.o
		rm -f ${Kunpeng_PATH}/kunpeng_memcpy.o
		rm -f ${Kunpeng_PATH}/kunpeng_memset.o

		rm -f ${Kunpeng_PATH}/kzl.a
		cp kzl.a ${Kunpeng_PATH}
		
		cd ${Kunpeng_PATH}		
		build_clean
	else
		echo "You have already create these files, clean before build."
	fi
}

function build_clean()
{
	if [ ! -d glibc-2.17 ]; then
		echo "No need clean all packages."
	else
		rm -rf ${Kunpeng_PATH}/final_package
		rm -rf ${Kunpeng_PATH}/glibc-2.17
		rm -rf ${Kunpeng_PATH}/glibc-2.31
		rm -rf ${Kunpeng_PATH}/glibc-2.32
		echo "Clean finsh."
	fi
}

function main()
{
    unzip BoostKit-KZL_1.0.0.zip
    tar -zxvf lz4-1.9.3.tar.gz
    patch -p0 < ./lz4_kzl.patch
    glibc_build
    cp ${Kunpeng_PATH}/kzl.a ${Kunpeng_PATH}/BoostKit-KZL_1.0.0/lz4_accelerater.h ./lz4-1.9.3/lib
    cd lz4-1.9.3/lib
    ar -x kzl.a
    cd ..
    make -j
}

main $@