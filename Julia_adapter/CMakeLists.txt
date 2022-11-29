cmake_minimum_required(VERSION 3.14.1)
project(JULIA C)
set(JULIA_VERSION 1.0.0)
set(JULIA_LIB_OUT kblas)

set(CMAKE_SHARED_LINKER_FLAGS "-lkblas -lklapack_full -L/usr/local/kml/lib/kblas/pthread -Wl,-rpath,/usr/local/kml/lib/kblas/pthread -L${LAPACK_FULL_DIRECTORY} -Wl,-rpath,${LAPACK_FULL_DIRECTORY}")

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

include_directories("/usr/local/kml/include")

file(GLOB julia_src src "src/*.c")

add_library(${JULIA_LIB_OUT} SHARED ${julia_src})

set_target_properties(${JULIA_LIB_OUT} PROPERTIES VERSION ${JULIA_VERSION})

install(TARGETS ${JULIA_LIB_OUT} LIBRARY DESTINATION lib)

link_directories(/usr/local/kml/lib)
link_directories(${LAPACK_FULL_DIRECTORY})
link_libraries("libkblas.so")
link_libraries("libklapack_full.so")
