cmake_minimum_required(VERSION 3.14.1)
project(FFT C)
set(FFT_VERSION 1.0.0)
set(FFT_LIB_NAME fftw3)

if(NOT FFT_FLOAT_TYPE)
    set(FFT_FLOAT_TYPE float)
endif()

if(NOT FFT_THREAD_TYPE)
    set(FFT_THREAD_TYPE pthread)
endif()

message(STATUS "Lib name: ${FFT_LIB_NAME}")

if(${FFT_FLOAT_TYPE} STREQUAL "double")
    message(STATUS "Date type: double")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -DFFT_FP64")
    set(FFT_LIB_OUT "${FFT_LIB_NAME}")
    set(CMAKE_SHARED_LINKER_FLAGS "-lkfft -L/usr/local/kml/lib")
else()
    message(STATUS "Date type: float")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -DFFT_FP32")
    set(FFT_LIB_OUT "${FFT_LIB_NAME}f")
    set(CMAKE_SHARED_LINKER_FLAGS "-lkfftf -L/usr/local/kml/lib")
endif()

if(CMAKE_C_COMPILER_ID STREQUAL "GNU")
    if(CMAKE_C_COMPILER_VERION VERSION_LESS "4.8.5" OR CMAKE_C_COMPILER_VERION VERSION_EQUAL "4.8.5")
        message("--Low gcc version:${CMAKE_C_COMPILER_VERION}")
        set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=gnu99")
    else()
        message("--gcc version:${CMAKE_C_COMPILER_VERION}")
        set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wdate-time")
    endif()
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wtrampolines -freg-struct-return")
endif()

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O3 -pipe")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Werror -Wextra -Wfloat-equal -Wshadow -Wformat=2")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fPIC -fpie -fstack-protector-strong")

set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -lm")
set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -pie")

if(${CMAKE_INSTALL_PREFIX} STREQUAL /usr/local)
    set(CMAKE_INSTALL_PREFIX ${CMAKE_CURRENT_SOURCE_DIR/output})
endif()

include_directories("${CMAKE_CURRENT_SOURCE_DIR}/include")

file(GLOB fft_src src "src/*.c")

add_library(${FFT_LIB_OUT} SHARED ${fft_src})

set_target_properties(${FFT_LIB_OUT} PROPERTIES VERSION ${FFT_VERSION})

install(TARGETS ${FFT_LIB_OUT} LIBRARY DESTINATION lin)

link_directories(/usr/local/kml/lib)
link_libraries("libkfft.so")
link_libraries("libkfftf.so")