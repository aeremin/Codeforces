add_executable(solver1830
    ${solvers_dir}/18xx/1830/Solver1830A.cpp
    )
target_link_libraries(solver1830 solver_testing_utils gtest gmock algo_lib)
add_test(solver1830 solver1830)
