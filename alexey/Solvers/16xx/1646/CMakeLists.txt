add_executable(solver1646
    ${solvers_dir}/16xx/1646/Solver1646A.cpp
    ${solvers_dir}/16xx/1646/Solver1646B.cpp
    ${solvers_dir}/16xx/1646/Solver1646C.cpp
    ${solvers_dir}/16xx/1646/Solver1646E.cpp
)
target_link_libraries(solver1646 solver_testing_utils gtest gmock algo_lib)
add_test(solver1646 solver1646)
