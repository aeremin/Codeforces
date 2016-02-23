cmake_minimum_required(VERSION 2.6)
project(codeforces)

set(root_dir ${CMAKE_SOURCE_DIR}/..)
set(common_dir ${root_dir}/common)
set(common_lib_dir ${common_dir}/lib)
set(src_dir ${CMAKE_SOURCE_DIR})
set(solvers_dir ${CMAKE_SOURCE_DIR}/Solvers)
set(launcher_dir ${CMAKE_SOURCE_DIR}/Launcher)
set(algotest_dir ${CMAKE_SOURCE_DIR}/AlgoTest)

# Download and unpack googletest at configure time
configure_file(CMakeLists.txt.in
               googletest-download/CMakeLists.txt)
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
  WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/googletest-download )
execute_process(COMMAND ${CMAKE_COMMAND} --build .
  WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/googletest-download )
 
# Prevent GoogleTest from overriding our compiler/linker options
# when building with Visual Studio
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
 
# Add googletest directly to our build. This adds
# the following targets: gtest, gtest_main, gmock
# and gmock_main
add_subdirectory(${CMAKE_BINARY_DIR}/googletest-src
                 ${CMAKE_BINARY_DIR}/googletest-build)
 
include_directories("${gtest_SOURCE_DIR}/include"
                    "${gmock_SOURCE_DIR}/include")

set(tests_exe codeforces)
set(tests_srcs
    ${common_dir}/tools/fuser/fuser.cpp
    ${common_dir}/tools/fuser/file_parser.cpp
    ${launcher_dir}/main.cpp
    ${launcher_dir}/CodeFuser.h
    ${launcher_dir}/CodeFuser.cpp
    ${solvers_dir}/0xx/014/Solver014D.cpp
    ${solvers_dir}/0xx/022/Solver022B.cpp
    ${solvers_dir}/0xx/067/Solver067A.cpp
    ${solvers_dir}/0xx/071/Solver071C.cpp
    ${solvers_dir}/0xx/074/Solver074B.cpp
    ${solvers_dir}/0xx/079/Solver079C.cpp
    ${solvers_dir}/1xx/107/Solver107B.cpp
    ${solvers_dir}/1xx/132/Solver132C.cpp
    ${solvers_dir}/1xx/158/Solver158E.cpp
    ${solvers_dir}/1xx/163/Solver163A.cpp
    ${solvers_dir}/2xx/208/Solver208B.cpp
    ${solvers_dir}/2xx/245/Solver245H.cpp
    ${solvers_dir}/2xx/264/Solver264C.cpp
    ${solvers_dir}/2xx/292/Solver292D.cpp
    ${solvers_dir}/3xx/316/Solver316B.cpp
    ${solvers_dir}/3xx/321/Solver321B.cpp
    ${solvers_dir}/3xx/346/Solver346B.cpp
    ${solvers_dir}/3xx/351/Solver351B.cpp
    ${solvers_dir}/3xx/354/Solver354C.cpp
    ${solvers_dir}/3xx/358/Solver358D.cpp
    ${solvers_dir}/3xx/372/Solver372B.cpp
    ${solvers_dir}/3xx/374/Solver374C.cpp
    ${solvers_dir}/3xx/379/Solver379D.cpp
    ${solvers_dir}/4xx/401/Solver401D.cpp
    ${solvers_dir}/4xx/402/Solver402D.cpp
    ${solvers_dir}/4xx/417/Solver417A.cpp
    ${solvers_dir}/4xx/431/Solver431D.cpp
    ${solvers_dir}/4xx/432/Solver432D.cpp
    ${solvers_dir}/4xx/464/Solver464C.cpp
    ${solvers_dir}/4xx/468/Solver468A.cpp
    ${solvers_dir}/4xx/468/Solver468B.cpp
    ${solvers_dir}/4xx/474/Solver474E.cpp
    ${solvers_dir}/4xx/476/Solver476C.cpp
    ${solvers_dir}/4xx/476/Solver476D.cpp
    ${solvers_dir}/4xx/476/Solver476E.cpp
    ${solvers_dir}/4xx/482/Solver482A.cpp
    ${solvers_dir}/4xx/482/Solver482B.cpp
    ${solvers_dir}/4xx/482/Solver482D.cpp
    ${solvers_dir}/4xx/484/Solver484A.cpp
    ${solvers_dir}/4xx/484/Solver484B.cpp
    ${solvers_dir}/4xx/484/Solver484C.cpp
    ${solvers_dir}/4xx/484/Solver484D.cpp
    ${solvers_dir}/4xx/486/Solver486D.cpp
    ${solvers_dir}/4xx/487/Solver487B.cpp
    ${solvers_dir}/4xx/487/Solver487D.cpp
    ${solvers_dir}/4xx/489/Solver489F.cpp
    ${solvers_dir}/4xx/494/Solver494A.cpp
    ${solvers_dir}/4xx/494/Solver494B.cpp
    ${solvers_dir}/4xx/496/Solver496C.cpp
    ${solvers_dir}/4xx/496/Solver496D.cpp
    ${solvers_dir}/4xx/496/Solver496E.cpp
    ${solvers_dir}/4xx/497/Solver497D.cpp
    ${solvers_dir}/4xx/498/Solver498A.cpp
    ${solvers_dir}/4xx/498/Solver498B.cpp
    ${solvers_dir}/4xx/498/Solver498C.cpp
    ${solvers_dir}/4xx/498/Solver498D.cpp
    ${solvers_dir}/5xx/500/Solver500A.cpp
    ${solvers_dir}/5xx/500/Solver500B.cpp
    ${solvers_dir}/5xx/500/Solver500C.cpp
    ${solvers_dir}/5xx/500/Solver500D.cpp
    ${solvers_dir}/5xx/505/Solver505C.cpp
    ${solvers_dir}/5xx/507/Solver507E.cpp
    ${solvers_dir}/5xx/509/Solver509C.cpp
    ${solvers_dir}/5xx/524/Solver524B.cpp
    ${solvers_dir}/5xx/533/Solver533E.cpp
    ${solvers_dir}/5xx/538/Solver538E.cpp
    ${solvers_dir}/5xx/552/Solver552E.cpp
    ${solvers_dir}/5xx/553/Solver553D.cpp
    ${solvers_dir}/5xx/554/Solver554A.cpp
    ${solvers_dir}/5xx/554/Solver554B.cpp
    ${solvers_dir}/5xx/554/Solver554C.cpp
    ${solvers_dir}/5xx/554/Solver554D.cpp
    ${solvers_dir}/5xx/554/Solver554E.cpp
    ${solvers_dir}/5xx/566/Solver566F.cpp
    ${solvers_dir}/5xx/568/Solver568B.cpp
    ${solvers_dir}/5xx/571/Solver571B.cpp
    ${solvers_dir}/5xx/573/Solver573A.cpp
    ${solvers_dir}/5xx/573/Solver573B.cpp
    ${solvers_dir}/5xx/576/Solver576A.cpp
    ${solvers_dir}/5xx/576/Solver576B.cpp
    ${solvers_dir}/5xx/576/Solver576C.cpp
    ${solvers_dir}/5xx/578/Solver578A.cpp
    ${solvers_dir}/5xx/578/Solver578B.cpp
    ${solvers_dir}/5xx/579/Solver579A.cpp
    ${solvers_dir}/5xx/579/Solver579B.cpp
    ${solvers_dir}/5xx/580/Solver580A.cpp
    ${solvers_dir}/5xx/580/Solver580B.cpp
    ${solvers_dir}/5xx/580/Solver580C.cpp
    ${solvers_dir}/5xx/580/Solver580D.cpp
    ${solvers_dir}/5xx/581/Solver581A.cpp
    ${solvers_dir}/5xx/581/Solver581B.cpp
    ${solvers_dir}/5xx/581/Solver581C.cpp
    ${solvers_dir}/5xx/581/Solver581D.cpp
    ${solvers_dir}/5xx/582/Solver582A.cpp
    ${solvers_dir}/5xx/582/Solver582B.cpp
    ${solvers_dir}/5xx/582/Solver582C.cpp
    ${solvers_dir}/5xx/582/Solver582E.cpp
    ${solvers_dir}/5xx/587/Solver587A.cpp
    ${solvers_dir}/5xx/587/Solver87C.cpp
    ${solvers_dir}/5xx/590/Solver590A.cpp
    ${solvers_dir}/5xx/590/Solver590B.cpp
    ${solvers_dir}/5xx/590/Solver590C.cpp
    ${solvers_dir}/5xx/592/Solver592D.cpp
    ${solvers_dir}/5xx/594/Solver594A.cpp
    ${solvers_dir}/5xx/594/Solver594C.cpp
    ${solvers_dir}/5xx/597/Solver597B.cpp
    ${solvers_dir}/5xx/598/Solver598A.cpp
    ${solvers_dir}/5xx/598/Solver598E.cpp
    ${solvers_dir}/5xx/599/Solver599D.cpp
    ${solvers_dir}/6xx/600/Solver600A.cpp
    ${solvers_dir}/6xx/600/Solver600B.cpp
    ${solvers_dir}/6xx/600/Solver600C.cpp
    ${solvers_dir}/6xx/601/Solver601A.cpp
    ${solvers_dir}/6xx/603/Solver603A.cpp
    ${solvers_dir}/6xx/603/Solver603B.cpp
    ${solvers_dir}/6xx/603/Solver603C.cpp
    ${solvers_dir}/6xx/604/Solver604A.cpp
    ${solvers_dir}/6xx/604/Solver604B.cpp
    ${solvers_dir}/6xx/605/Solver605A.cpp
    ${solvers_dir}/6xx/605/Solver605B.cpp
    ${solvers_dir}/6xx/605/Solver605C.cpp
    ${solvers_dir}/6xx/606/Solver606A.cpp
    ${solvers_dir}/6xx/608/Solver608A.cpp
    ${solvers_dir}/6xx/608/Solver608B.cpp
    ${solvers_dir}/6xx/609/Solver609A.cpp
    ${solvers_dir}/6xx/609/Solver609B.cpp
    ${solvers_dir}/6xx/609/Solver609C.cpp
    ${solvers_dir}/6xx/610/Solver610A.cpp
    ${solvers_dir}/6xx/610/Solver610B.cpp
    ${solvers_dir}/6xx/610/Solver610C.cpp
    ${solvers_dir}/6xx/611/Solver611A.cpp
    ${solvers_dir}/6xx/611/Solver611B.cpp
    ${solvers_dir}/6xx/611/Solver611C.cpp
    ${solvers_dir}/6xx/611/Solver611D.cpp
    ${solvers_dir}/6xx/611/Solver611E.cpp
    ${solvers_dir}/6xx/611/Solver611F.cpp
    ${solvers_dir}/6xx/611/Solver611H.cpp
    ${solvers_dir}/6xx/612/Solver612A.cpp
    ${solvers_dir}/6xx/612/Solver612B.cpp
    ${solvers_dir}/6xx/612/Solver612C.cpp
    ${solvers_dir}/6xx/612/Solver612D.cpp
    ${solvers_dir}/6xx/612/Solver612E.cpp
    ${solvers_dir}/6xx/613/Solver613A.cpp
    ${solvers_dir}/6xx/613/Solver613B.cpp
    ${solvers_dir}/6xx/613/Solver613C.cpp
    ${solvers_dir}/6xx/615/Solver615A.cpp
    ${solvers_dir}/6xx/615/Solver615B.cpp
    ${solvers_dir}/6xx/615/Solver615C.cpp
    ${solvers_dir}/6xx/615/Solver615D.cpp
    ${solvers_dir}/6xx/615/Solver615E.cpp
    ${solvers_dir}/6xx/616/Solver616A.cpp
    ${solvers_dir}/6xx/616/Solver616B.cpp
    ${solvers_dir}/6xx/616/Solver616C.cpp
    ${solvers_dir}/6xx/616/Solver616D.cpp
    ${solvers_dir}/6xx/616/Solver616E.cpp
    ${solvers_dir}/6xx/617/Solver617A.cpp
    ${solvers_dir}/6xx/617/Solver617B.cpp
    ${solvers_dir}/6xx/617/Solver617C.cpp
    ${solvers_dir}/6xx/617/Solver617D.cpp
    ${solvers_dir}/6xx/617/Solver617E.cpp
    ${solvers_dir}/6xx/618/Solver618A.cpp
    ${solvers_dir}/6xx/618/Solver618B.cpp
    ${solvers_dir}/6xx/618/Solver618C.cpp
    ${solvers_dir}/6xx/618/Solver618D.cpp
    ${solvers_dir}/6xx/618/Solver618E.cpp
    ${solvers_dir}/6xx/620/Solver620B.cpp
    ${solvers_dir}/6xx/620/Solver620C.cpp
    ${solvers_dir}/6xx/620/Solver620D.cpp
    ${solvers_dir}/6xx/620/Solver620E.cpp
    ${solvers_dir}/6xx/621/Solver621A.cpp
    ${solvers_dir}/6xx/621/Solver621B.cpp
    ${solvers_dir}/6xx/621/Solver621C.cpp
    ${solvers_dir}/6xx/621/Solver621D.cpp
    ${solvers_dir}/6xx/621/Solver621E.cpp
    ${solvers_dir}/6xx/622/Solver622A.cpp
    ${solvers_dir}/6xx/622/Solver622B.cpp
    ${solvers_dir}/6xx/622/Solver622C.cpp
    ${solvers_dir}/6xx/622/Solver622D.cpp
    ${solvers_dir}/6xx/622/Solver622E.cpp
    ${solvers_dir}/6xx/622/Solver622F.cpp
    ${solvers_dir}/6xx/623/Solver623A.cpp
    ${solvers_dir}/6xx/623/Solver623B.cpp
    ${solvers_dir}/6xx/623/Solver623C.cpp
    ${solvers_dir}/6xx/623/Solver623D.cpp
    ${solvers_dir}/6xx/624/Solver624A.cpp
    ${solvers_dir}/6xx/624/Solver624B.cpp
    ${solvers_dir}/6xx/625/Solver625A.cpp
    ${solvers_dir}/6xx/625/Solver625B.cpp
    ${solvers_dir}/6xx/625/Solver625C.cpp
    ${solvers_dir}/6xx/625/Solver625D.cpp
    ${solvers_dir}/6xx/626/Solver626A.cpp
    ${solvers_dir}/6xx/626/Solver626B.cpp
    ${solvers_dir}/6xx/626/Solver626C.cpp
    ${solvers_dir}/6xx/626/Solver626D.cpp
    ${solvers_dir}/6xx/629/Solver629A.cpp
    ${solvers_dir}/6xx/629/Solver629B.cpp
    ${solvers_dir}/6xx/629/Solver629C.cpp
    ${solvers_dir}/6xx/629/Solver629D.cpp
    ${solvers_dir}/6xx/629/Solver629E.cpp
    ${solvers_dir}/6xx/630/Solver630A.cpp
    ${solvers_dir}/6xx/630/Solver630B.cpp
    ${solvers_dir}/6xx/630/Solver630C.cpp
    ${solvers_dir}/6xx/630/Solver630D.cpp
    ${solvers_dir}/6xx/630/Solver630E.cpp
    ${solvers_dir}/6xx/630/Solver630F.cpp
    ${solvers_dir}/6xx/630/Solver630G.cpp
    ${solvers_dir}/6xx/630/Solver630H.cpp
    ${solvers_dir}/6xx/630/Solver630I.cpp
    ${solvers_dir}/6xx/630/Solver630J.cpp
    ${solvers_dir}/6xx/630/Solver630K.cpp
    ${solvers_dir}/6xx/630/Solver630L.cpp
    ${solvers_dir}/6xx/630/Solver630M.cpp
    ${solvers_dir}/6xx/630/Solver630N.cpp
    ${solvers_dir}/6xx/630/Solver630O.cpp
    ${solvers_dir}/6xx/630/Solver630P.cpp
    ${solvers_dir}/6xx/630/Solver630Q.cpp
    ${solvers_dir}/6xx/630/Solver630R.cpp
    ${solvers_dir}/pch.cpp
    ${solvers_dir}/SolverStub.cpp
    ${solvers_dir}/testutils/ProblemTest.cpp
    ${algotest_dir}/geometry/ConvexHullTest.cpp
    ${algotest_dir}/geometry/geomvectortest.cpp
    ${algotest_dir}/AngleSortTest.cpp
    ${algotest_dir}/BinaryCubePrefixTest.cpp
    ${algotest_dir}/BinarySearchTest.cpp
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
    ${algotest_dir}/ResidueTest.cpp
    ${algotest_dir}/SegmentTreeTest.cpp
    ${algotest_dir}/SingleLinkedListTest.cpp
    ${algotest_dir}/SlidingWindowMinFinderTest.cpp
    ${algotest_dir}/TreePreprocessorTest.cpp
)
add_executable(${tests_exe}  ${tests_srcs})
target_link_libraries(${tests_exe} ${GTEST_LIBRARIES})
target_link_libraries(${tests_exe} "pthread")

include_directories(${common_dir})
include_directories(${common_lib_dir})
include_directories(${src_dir})
include_directories(${root_dir}/andrei/lib)  # TODO FIXME (for fuser)

add_definitions("-std=c++11 -DLOCAL_PC")
