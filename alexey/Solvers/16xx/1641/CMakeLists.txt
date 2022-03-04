add_executable(solver1641
    ${solvers_dir}/16xx/1641/Solver1641A.cpp
    ${solvers_dir}/16xx/1641/Solver1641B.cpp)
target_link_libraries(solver1641 solver_testing_utils gtest gmock algo_lib)
add_test(solver1641 solver1641)
