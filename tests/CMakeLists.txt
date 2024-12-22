include(CheckCompilerFlag)

set(KRUFT_C_STANDARD "90" CACHE STRING "C Standard to use")
set(KRUFT_CXX_STANDARD "14" CACHE STRING "C++ Standard to use")

set(ZZTEST_SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/zztest.h")

set(TEST_SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/t_bit.inl"
    "${CMAKE_CURRENT_SOURCE_DIR}/t_ctype.inl"
    "${CMAKE_CURRENT_SOURCE_DIR}/t_int.inl"
    "${CMAKE_CURRENT_SOURCE_DIR}/t_lib.inl"
    "${CMAKE_CURRENT_SOURCE_DIR}/t_limits.inl"
    "${CMAKE_CURRENT_SOURCE_DIR}/t_serial.inl"
    "${CMAKE_CURRENT_SOURCE_DIR}/t_str.inl")

# Test suite.
add_executable(kruft_test_c ${ZZTEST_SOURCES} ${TEST_SOURCES}
    "${CMAKE_CURRENT_SOURCE_DIR}/test_c.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/zztest.c")
add_executable(kruft_test_cxx ${ZZTEST_SOURCES} ${TEST_SOURCES}
    "${CMAKE_CURRENT_SOURCE_DIR}/test_cxx.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/zztest.cpp")

target_include_directories(kruft_test_c PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}")
target_include_directories(kruft_test_cxx PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}")

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

set_target_properties(kruft_test_c PROPERTIES C_STANDARD "${KRUFT_C_STANDARD}")
set_target_properties(kruft_test_cxx PROPERTIES CXX_STANDARD "${KRUFT_CXX_STANDARD}")

enable_testing()
add_test(NAME kruft_test_c COMMAND $<TARGET_FILE:kruft_test_c>)
add_test(NAME kruft_test_cxx COMMAND $<TARGET_FILE:kruft_test_cxx>)
