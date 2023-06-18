add_executable(solver1834
    ${solvers_dir}/18xx/1834/Solver1834A.cpp
    ${solvers_dir}/18xx/1834/Solver1834B.cpp
    ${solvers_dir}/18xx/1834/Solver1834C.cpp
    ${solvers_dir}/18xx/1834/Solver1834D.cpp
    )
target_link_libraries(solver1834 solver_testing_utils gtest gmock algo_lib)
add_test(solver1834 solver1834)
