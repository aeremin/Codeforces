cmake_minimum_required(VERSION 2.6)
project(contest_911)

add_executable(contest_911_a ${CMAKE_CURRENT_LIST_DIR}/A/a.cpp)
target_link_libraries(contest_911_a ${GTEST_LIBRARIES} "gmock" "pthread")

add_executable(contest_911_b ${CMAKE_CURRENT_LIST_DIR}/B/b.cpp)
target_link_libraries(contest_911_b ${GTEST_LIBRARIES} "gmock" "pthread")

add_executable(contest_911_c ${CMAKE_CURRENT_LIST_DIR}/C/c.cpp)
target_link_libraries(contest_911_c ${GTEST_LIBRARIES} "gmock" "pthread")

add_executable(contest_911_d ${CMAKE_CURRENT_LIST_DIR}/D/d.cpp)
target_link_libraries(contest_911_d ${GTEST_LIBRARIES} "gmock" "pthread")

add_executable(contest_911_e ${CMAKE_CURRENT_LIST_DIR}/E/e.cpp)
target_link_libraries(contest_911_e ${GTEST_LIBRARIES} "gmock" "pthread")

add_executable(contest_911_f ${CMAKE_CURRENT_LIST_DIR}/F/f.cpp)
target_link_libraries(contest_911_f ${GTEST_LIBRARIES} "gmock" "pthread")

add_executable(contest_911_g ${CMAKE_CURRENT_LIST_DIR}/G/g.cpp)
target_link_libraries(contest_911_g ${GTEST_LIBRARIES} "gmock" "pthread")

add_definitions("-std=c++17 -DLOCAL_PC")
set(CMAKE_CXX_FLAGS "-Wall -Wextra -Wcast-align -Wfloat-conversion -Wunused -Wformat=2 -Wcast-qual -Wold-style-cast -Woverloaded-virtual -Wshadow -Wnon-virtual-dtor -Wno-sign-compare")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O2 -DNDEBUG")
