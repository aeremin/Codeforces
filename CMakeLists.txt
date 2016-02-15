cmake_minimum_required(VERSION 2.6)
project(contest_lib_test)

find_package(Boost 1.54.0 COMPONENTS program_options REQUIRED)
find_package(GTest REQUIRED)

set(lib_dir ${CMAKE_SOURCE_DIR}/lib)

set(tests_exe contest_lib_test)
set(tests_srcs
    ${lib_dir}/test.cc
    ${lib_dir}/container/indexer_test.cpp
    ${lib_dir}/graph/dfs_test.cpp
)
add_executable(${tests_exe}  ${tests_srcs})
target_link_libraries(${tests_exe} ${GTEST_LIBRARIES})
target_link_libraries(${tests_exe} "pthread")

set(compiler_dir ${CMAKE_SOURCE_DIR}/compiler)
set(compiler_exe solution_compiler)
set(compiler_srcs
    ${compiler_dir}/compiler.cpp
    ${compiler_dir}/file_parser.cpp
)
add_executable(${compiler_exe}  ${compiler_srcs})
target_link_libraries(${compiler_exe} ${Boost_LIBRARIES})

include_directories(${lib_dir})

add_definitions("-std=c++11 -DLOCAL_PC")
set(CMAKE_CXX_FLAGS "-Wall -Wextra -Wcast-align -Wconversion -Wunused -Wformat=2 -Wcast-qual -Wold-style-cast -Woverloaded-virtual -Wshadow -Wnon-virtual-dtor -Wsuggest-override -Werror")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O2 -DNDEBUG")
