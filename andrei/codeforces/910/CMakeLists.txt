cmake_minimum_required(VERSION 2.6)
project(contest_910)

add_executable(contest_910_a ${CMAKE_CURRENT_LIST_DIR}/A/a.cpp)
target_link_libraries(contest_910_a ${GTEST_LIBRARIES} "gmock" "pthread")

add_executable(contest_910_b ${CMAKE_CURRENT_LIST_DIR}/B/b.cpp)
target_link_libraries(contest_910_b ${GTEST_LIBRARIES} "gmock" "pthread")

add_executable(contest_910_c ${CMAKE_CURRENT_LIST_DIR}/C/c.cpp)
target_link_libraries(contest_910_c ${GTEST_LIBRARIES} "gmock" "pthread")

add_definitions("-std=c++17 -DLOCAL_PC")
set(CMAKE_CXX_FLAGS "-Wall -Wextra -Wcast-align -Wno-sign-compare -Wconversion -Wunused -Wformat=2 -Wcast-qual -Wold-style-cast -Woverloaded-virtual -Wshadow -Wnon-virtual-dtor")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O2 -DNDEBUG")
