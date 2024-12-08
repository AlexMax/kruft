include(CheckCompilerFlag)
include(FetchContent)

FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG v1.15.2)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

set(TEST_SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/test_ctype.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/test_lib.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/test_str.cpp")

# Test suite.
add_executable(kruft_test ${TEST_SOURCES})
target_include_directories(kruft_test PRIVATE "${CMAKE_CURRENT_BINARY_DIR}")
target_link_libraries(kruft_test PRIVATE kruft GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(kruft_test)

check_compiler_flag(CXX -Wmost W_MOST)
if(W_MOST)
    target_compile_options(kruft_test PRIVATE "-Wmost")
endif()

check_compiler_flag(CXX -Werror=c++17-extensions WERROR_CXX17_EXTENSIONS)
if(WERROR_CXX17_EXTENSIONS)
    target_compile_options(kruft_test PRIVATE "-Werror=c++17-extensions")
endif()

check_compiler_flag(CXX -Werror=c++20-extensions WERROR_CXX20_EXTENSIONS)
if(WERROR_CXX20_EXTENSIONS)
    target_compile_options(kruft_test PRIVATE "-Werror=c++20-extensions")
endif()

if(MSVC)
    target_compile_options(kruft_test PUBLIC /W4 /permissive-)
else()
    target_compile_options(kruft_test PUBLIC -Wall -Wextra -Wno-unknown-pragmas)
endif()

# Test compiling as C.
add_library(kruft_testc STATIC "${CMAKE_CURRENT_SOURCE_DIR}/testc.c")
target_link_libraries(kruft_testc PRIVATE kruft)
