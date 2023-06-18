add_executable(solver1836
    ${solvers_dir}/18xx/1836/Solver1836A.cpp
    ${solvers_dir}/18xx/1836/Solver1836B.cpp
    ${solvers_dir}/18xx/1836/Solver1836C.cpp
    )
target_link_libraries(solver1836 solver_testing_utils gtest gmock algo_lib)
add_test(solver1836 solver1836)
