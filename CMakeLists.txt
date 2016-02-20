cmake_minimum_required(VERSION 2.6)
project(codeforces)

find_package(GTest REQUIRED)

set(src_dir ${CMAKE_SOURCE_DIR})
set(solvers_dir ${CMAKE_SOURCE_DIR}/Solvers)
set(launcher_dir ${CMAKE_SOURCE_DIR}/Launcher)
set(algotest_dir ${CMAKE_SOURCE_DIR}/AlgoTest)

set(tests_exe codeforces)
set(tests_srcs
    ${launcher_dir}/main.cpp
    ${launcher_dir}/CodeFuser.h
    ${launcher_dir}/CodeFuser.cpp
    ${solvers_dir}/testutils/ProblemTest.cpp
    ${solvers_dir}/6xx/626/Solver626A.cpp
    ${solvers_dir}/6xx/626/Solver626B.cpp
    ${solvers_dir}/6xx/626/Solver626C.cpp
    ${solvers_dir}/6xx/626/Solver626D.cpp
    ${algotest_dir}/geometry/ConvexHullTest.cpp
    ${algotest_dir}/geometry/geomvectortest.cpp
    ${algotest_dir}/AngleSortTest.cpp
    ${algotest_dir}/BinaryCubePrefixTest.cpp
    ${algotest_dir}/BinarySearchTest.cpp
    ${algotest_dir}/BinomialCoefficientTest.cpp
    ${algotest_dir}/BipartitionCheckerTest.cpp
    ${algotest_dir}/BreadthSearchTest.cpp
    ${algotest_dir}/ConnectedComponentsDecomposerTest.cpp
    ${algotest_dir}/CoprimeTest.cpp
    ${algotest_dir}/DepthFirstSearchTest.cpp
    ${algotest_dir}/DisjointSetTest.cpp
    ${algotest_dir}/DivisorsTest.cpp
    ${algotest_dir}/DPProcessorTest.cpp
    ${algotest_dir}/FactorialTest.cpp
    ${algotest_dir}/FibonacciHeapTest.cpp
    ${algotest_dir}/FullBinaryTrieTest.cpp
    ${algotest_dir}/FunctorIteratorTest.cpp
    ${algotest_dir}/GraphHelper.cpp
    ${algotest_dir}/GreatestCommonDivisorTest.cpp
    ${algotest_dir}/HasCycleTest.cpp
    ${algotest_dir}/HeapTest.cpp
    ${algotest_dir}/IndicatorTest.cpp
    ${algotest_dir}/KnuttMorrisPrattTest.cpp
    ${algotest_dir}/MaximalIncreasingSubsequenceTest.cpp
    ${algotest_dir}/MergeSortTest.cpp
    ${algotest_dir}/MoQueryProcessorTest.cpp
    ${algotest_dir}/PrimesTest.cpp
    ${algotest_dir}/QuickPowerTest.cpp
    ${algotest_dir}/RangeTest.cpp
    ${algotest_dir}/ResidueTest.cpp
    ${algotest_dir}/SegmentTreeTest.cpp
    ${algotest_dir}/SingleLinkedListTest.cpp
    ${algotest_dir}/SlidingWindowMinFinderTest.cpp
    ${algotest_dir}/TreePreprocessorTest.cpp
)
add_executable(${tests_exe}  ${tests_srcs})
target_link_libraries(${tests_exe} ${GTEST_LIBRARIES})
target_link_libraries(${tests_exe} "pthread")

include_directories(${src_dir})

add_definitions("-std=c++11 -DLOCAL_PC")