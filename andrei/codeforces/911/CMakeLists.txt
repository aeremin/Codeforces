cmake_minimum_required(VERSION 2.6)
project(contest_911)

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

add_executable(d_solver ${src_dir}/D/d.cpp)
target_link_libraries(d_solver ${GTEST_LIBRARIES} "gmock" "pthread")

add_executable(e_solver ${src_dir}/E/e.cpp)
target_link_libraries(e_solver ${GTEST_LIBRARIES} "gmock" "pthread")

add_executable(f_solver ${src_dir}/F/f.cpp)
target_link_libraries(f_solver ${GTEST_LIBRARIES} "gmock" "pthread")

add_executable(g_solver ${src_dir}/G/g.cpp)
target_link_libraries(g_solver ${GTEST_LIBRARIES} "gmock" "pthread")

add_definitions("-std=c++17 -DLOCAL_PC")
set(CMAKE_CXX_FLAGS "-Wall -Wextra -Wcast-align -Wfloat-conversion -Wunused -Wformat=2 -Wcast-qual -Wold-style-cast -Woverloaded-virtual -Wshadow -Wnon-virtual-dtor -Wno-sign-compare")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O2 -DNDEBUG")
