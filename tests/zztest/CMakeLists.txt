add_library(zztest_c "zztest.c" "include/zztest.h")
add_library(zztest_cxx "zztest.cpp" "include/zztest.h")

target_include_directories(zztest_c PUBLIC "include")
target_include_directories(zztest_cxx PUBLIC "include")

add_executable(zzcheck_c "zzcheck.c" "zzcheck.inl")
target_link_libraries(zzcheck_c zztest_c)

add_executable(zzcheck_cxx "zzcheck.cpp" "zzcheck.inl")
target_link_libraries(zzcheck_cxx zztest_cxx)
