cmake_minimum_required(VERSION 3.25)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON CACHE INTERNAL "")

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

option(KRUFT_ENABLE_TESTS "Enable tests for LPC")
option(KRUFT_ENABLE_BENCHES "Enable benchmarks for LPC")

project(kruft LANGUAGES C CXX)

set(KRUFT_HEADERS
    "${CMAKE_CURRENT_SOURCE_DIR}/include/krbit.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/krbool.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/krconfig.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/krctype.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/krint.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/krlib.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/krserial.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/krstr.h")

add_library(kruft INTERFACE ${KRUFT_HEADERS})
target_include_directories(kruft INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}/include/")

if(KRUFT_ENABLE_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()
if(KRUFT_ENABLE_BENCHES)
    add_subdirectory(benches)
endif()
