add_executable(solver1648
    ${solvers_dir}/16xx/1648/Solver1648A.cpp
    ${solvers_dir}/16xx/1648/Solver1648B.cpp
    ${solvers_dir}/16xx/1648/Solver1648C.cpp
)
target_link_libraries(solver1648 solver_testing_utils gtest gmock algo_lib)
add_test(solver1648 solver1648)
