add_executable(solver1841
    ${solvers_dir}/18xx/1841/Solver1841A.cpp
    ${solvers_dir}/18xx/1841/Solver1841B.cpp
    ${solvers_dir}/18xx/1841/Solver1841C.cpp
    ${solvers_dir}/18xx/1841/Solver1841D.cpp
    )
target_link_libraries(solver1841 solver_testing_utils gtest gmock algo_lib)
add_test(solver1841 solver1841)
