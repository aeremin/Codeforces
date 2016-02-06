cmake_minimum_required(VERSION 2.6)
project(contest_lib_test)

set(executable_name contest_lib_test)
set(lib_dir ${CMAKE_SOURCE_DIR}/lib)
set(lib_tests_dir ${CMAKE_SOURCE_DIR}/lib_tests)
set(srcs ${lib_tests_dir}/test.cc)

include_directories(${lib_dir})

add_executable(${executable_name}  ${srcs})

add_definitions("-std=c++11 -DLOCAL_PC")
set(CMAKE_CXX_FLAGS "-Wall -Wextra -Wcast-align -Wconversion -Wunused -Wformat=2 -Wcast-qual -Wold-style-cast -Woverloaded-virtual -Wshadow -Wnon-virtual-dtor -Wsuggest-override -Werror")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O2 -DNDEBUG")
