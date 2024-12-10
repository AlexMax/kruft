include(CheckCompilerFlag)

set(TEST_HEADERS
    "${CMAKE_CURRENT_SOURCE_DIR}/zztest.h")

set(TEST_SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/t_ctype.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/t_lib.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/t_str.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/zztest.c")

# Test suite.
add_executable(kruft_test_c ${TEST_SOURCES} ${TEST_HEADERS} "${CMAKE_CURRENT_SOURCE_DIR}/test_c.c")
add_executable(kruft_test_cxx ${TEST_SOURCES} ${TEST_HEADERS} "${CMAKE_CURRENT_SOURCE_DIR}/test_cpp.cpp")

target_include_directories(kruft_test_c PRIVATE "${CMAKE_CURRENT_BINARY_DIR}")
target_include_directories(kruft_test_cxx PRIVATE "${CMAKE_CURRENT_BINARY_DIR}")

target_link_libraries(kruft_test_c PRIVATE kruft)
target_link_libraries(kruft_test_cxx PRIVATE kruft)

check_compiler_flag(CXX -Wmost W_MOST)
if(W_MOST)
    target_compile_options(kruft_test_c PRIVATE "-Wmost")
    target_compile_options(kruft_test_cxx PRIVATE "-Wmost")
endif()

check_compiler_flag(CXX -Werror=c++17-extensions WERROR_CXX17_EXTENSIONS)
if(WERROR_CXX17_EXTENSIONS)
    target_compile_options(kruft_test_cxx PRIVATE "-Werror=c++17-extensions")
endif()

check_compiler_flag(CXX -Werror=c++20-extensions WERROR_CXX20_EXTENSIONS)
if(WERROR_CXX20_EXTENSIONS)
    target_compile_options(kruft_test_cxx PRIVATE "-Werror=c++20-extensions")
endif()

if(MSVC)
    target_compile_options(kruft_test_c PUBLIC /W4 /permissive-)
    target_compile_options(kruft_test_cxx PUBLIC /W4 /permissive-)
else()
    target_compile_options(kruft_test_c PUBLIC -Wall -Wextra -Wno-unknown-pragmas)
    target_compile_options(kruft_test_cxx PUBLIC -Wall -Wextra -Wno-unknown-pragmas)
endif()
