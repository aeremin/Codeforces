cmake_minimum_required(VERSION 2.6)
project(common_lib_tests)

set(src_dir ${CMAKE_SOURCE_DIR})
set(lib_dir ${src_dir}/lib)
set(lib_tests_dir ${src_dir}/lib_tests)

include(${src_dir}/external/CMakeLists.txt)

set(tests_exe common_lib_tests)
set(tests_srcs
    ${lib_tests_dir}/test.cpp
    ${lib_tests_dir}/graph/dfs_test.cpp
    ${lib_tests_dir}/graph/graph_test.cpp
    ${lib_tests_dir}/graph/topological_sort_test.cpp
    ${lib_tests_dir}/iter/range_test.cpp
    ${lib_tests_dir}/math/binomial_coefficient_test.cpp
    ${lib_tests_dir}/math/quick_power_test.cpp
    ${lib_tests_dir}/solution_tests/matchers_test.cpp
    ${lib_tests_dir}/util/lexicographical_compare_test.cpp
)
add_executable(${tests_exe}  ${tests_srcs})
target_link_libraries(${tests_exe} "gmock" "pthread")

include_directories(${lib_dir})

add_definitions("-std=c++17 -DLOCAL_PC")
set(CMAKE_CXX_FLAGS "-Wall -Wextra -Wcast-align -Wfloat-conversion -Wunused -Wformat=2 -Wcast-qual -Wold-style-cast -Woverloaded-virtual -Wshadow -Wnon-virtual-dtor -Werror")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O2 -DNDEBUG")
