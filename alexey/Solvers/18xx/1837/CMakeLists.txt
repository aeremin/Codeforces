add_executable(solver1837
    ${solvers_dir}/18xx/1837/Solver1837A.cpp
    ${solvers_dir}/18xx/1837/Solver1837B.cpp
    ${solvers_dir}/18xx/1837/Solver1837C.cpp
    )
target_link_libraries(solver1837 solver_testing_utils gtest gmock algo_lib)
add_test(solver1837 solver1837)
