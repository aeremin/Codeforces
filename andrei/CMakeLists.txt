cmake_minimum_required(VERSION 2.6)
project(contest_lib_test)

find_package(Boost 1.54.0 COMPONENTS program_options REQUIRED)

set(src_dir ${CMAKE_SOURCE_DIR})
set(root_dir ${src_dir}/..)
set(common_dir ${root_dir}/common)
set(common_lib_dir ${common_dir}/lib)
set(lib_dir ${src_dir}/lib)

include(${common_dir}/external/CMakeLists.txt)

set(tests_exe contest_lib_test)
set(tests_srcs
    ${lib_dir}/test.cc
    ${lib_dir}/container/indexer_test.cpp
    ${lib_dir}/graph/dfs_test.cpp
    ${lib_dir}/solution_tests/matchers_test.cpp
    ${lib_dir}/util/projected_test.cpp
)
add_executable(${tests_exe}  ${tests_srcs})
target_link_libraries(${tests_exe} "gmock" "benchmark" "pthread")

set(fuser_exe solution_fuser)
set(fuser_srcs
    ${src_dir}/fuser/fuser_main.cpp
    ${common_dir}/tools/fuser/fuser.cpp
    ${common_dir}/tools/fuser/file_parser.cpp
)
add_executable(${fuser_exe}  ${fuser_srcs})
target_link_libraries(${fuser_exe} ${Boost_LIBRARIES})

include_directories(${common_dir})
include_directories(${common_lib_dir})
include_directories(${lib_dir})

add_definitions("-std=c++11 -DLOCAL_PC")
set(CMAKE_CXX_FLAGS "-Wall -Wextra -Wcast-align -Wfloat-conversion -Wunused -Wformat=2 -Wcast-qual -Wold-style-cast -Woverloaded-virtual -Wshadow -Wnon-virtual-dtor -Werror")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O2 -DNDEBUG")
