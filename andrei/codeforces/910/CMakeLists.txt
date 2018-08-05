cmake_minimum_required(VERSION 2.6)
project(contest_910)

set(src_dir ${CMAKE_SOURCE_DIR})
set(root_dir ${src_dir}/../../..)
set(common_dir ${root_dir}/common)
set(common_lib_dir ${common_dir}/lib)
set(lib_dir ${src_dir}/../../lib)

include(${common_dir}/external/CMakeLists.txt)

include_directories(${common_dir})
include_directories(${common_lib_dir})
include_directories(${lib_dir})

add_executable(a_solver ${src_dir}/A/a.cpp)
target_link_libraries(a_solver ${GTEST_LIBRARIES} "gmock" "pthread")

add_executable(b_solver ${src_dir}/B/b.cpp)
target_link_libraries(b_solver ${GTEST_LIBRARIES} "gmock" "pthread")

add_executable(c_solver ${src_dir}/C/c.cpp)
target_link_libraries(c_solver ${GTEST_LIBRARIES} "gmock" "pthread")

add_definitions("-std=c++17 -DLOCAL_PC")
set(CMAKE_CXX_FLAGS "-Wall -Wextra -Wcast-align -Wno-sign-compare -Wconversion -Wunused -Wformat=2 -Wcast-qual -Wold-style-cast -Woverloaded-virtual -Wshadow -Wnon-virtual-dtor")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O2 -DNDEBUG")
