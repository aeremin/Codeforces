cmake_minimum_required(VERSION 2.8.3)

# Download and unpack googletest at configure time
configure_file(${CMAKE_CURRENT_LIST_DIR}/GTest.cmake.in
               googletest-download/CMakeLists.txt)
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
                WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/googletest-download )
execute_process(COMMAND ${CMAKE_COMMAND} --build .
                WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/googletest-download )

# Download and unpack googletest at configure time
configure_file(${CMAKE_CURRENT_LIST_DIR}/GBenchmark.cmake.in
               googlebenchmark-download/CMakeLists.txt)
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
                WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/googlebenchmark-download )
execute_process(COMMAND ${CMAKE_COMMAND} --build .
                WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/googlebenchmark-download )

# Prevent GoogleTest from overriding our compiler/linker options
# when building with Visual Studio
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# Add googletest directly to our build. This adds
# the following targets: gtest, gtest_main, gmock
# and gmock_main
add_subdirectory(${CMAKE_BINARY_DIR}/googletest-src
                 ${CMAKE_BINARY_DIR}/googletest-build)

add_subdirectory(${CMAKE_BINARY_DIR}/googlebenchmark-src
                 ${CMAKE_BINARY_DIR}/googlebenchmark-build)

include_directories("${gtest_SOURCE_DIR}/include"
                    "${gmock_SOURCE_DIR}/include"
                    "${benchmark_SOURCE_DIR}/include")
