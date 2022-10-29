# --------------------------------------------------------------------
# vsl
# --------------------------------------------------------------------
set(MATHLIB_NAME_VSL vsl_wrapper)
set(MATHLIB_OBJECT_VSL mathlib_obj_vsl)
list(APPEND CFLAGS "-DPACKAGE=\"boostkit-kml-vsl\"") 
file(GLOB vsl_math_source_list src "${CMAKE_CURRENT_SOURCE_DIR}/*.c")
add_library(${MATHLIB_OBJECT_VSL} OBJECT ${vsl_math_source_list} ${common_source_list} ${vector_source_list})

link_directories(/usr/local/kml/lib)
link_libraries("libkvsl.so")
link_libraries("libksvml.so")
link_libraries("libkm.so")
target_include_directories(${MATHLIB_OBJECT_VSL} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../include)
target_include_directories(${MATHLIB_OBJECT_VSL} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../../../../include)
target_include_directories(${MATHLIB_OBJECT_VSL} PUBLIC /usr/local/kml/include)

target_compile_options(${MATHLIB_OBJECT_VSL} PUBLIC ${CFLAGS} ${MATH_CFLAGS})
set_target_properties(${MATHLIB_OBJECT_VSL} PROPERTIES POSITION_INDEPENDENT_CODE 1)

add_library(${MATHLIB_NAME_VSL} SHARED $<TARGET_OBJECTS:${MATHLIB_OBJECT_VSL}>)
add_library(${MATHLIB_NAME_VSL}_static STATIC $<TARGET_OBJECTS:${MATHLIB_OBJECT_VSL}>)

set_target_properties(${MATHLIB_NAME_VSL} PROPERTIES LINK_FLAGS ${LINK_CFLAGS} )

set_target_properties(${MATHLIB_NAME_VSL} PROPERTIES VERSION "1.0.0")
set_target_properties(${MATHLIB_NAME_VSL}_static PROPERTIES OUTPUT_NAME ${MATHLIB_NAME_VSL} )
set_target_properties(${MATHLIB_NAME_VSL} PROPERTIES CLEAN_DIRECT_OUTPUT 1)
set_target_properties(${MATHLIB_NAME_VSL}_static PROPERTIES CLEAN_DIRECT_OUTPUT 1)
set_target_properties(${MATHLIB_NAME_VSL} PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set_target_properties(${MATHLIB_NAME_VSL}_static PROPERTIES ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include DESTINATION ${CMAKE_INSTALL_PREFIX})
install(TARGETS ${MATHLIB_NAME_VSL} LIBRARY DESTINATION ${CMAKE_INSTALL_PREFIX}/lib)
install(TARGETS ${MATHLIB_NAME_VSL}_static ARCHIVE DESTINATION ${CMAKE_INSTALL_PREFIX}/lib)
