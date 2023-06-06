add_executable(solver1838
    ${solvers_dir}/18xx/1838/Solver1838A.cpp
    ${solvers_dir}/18xx/1838/Solver1838B.cpp
    ${solvers_dir}/18xx/1838/Solver1838C.cpp
    ${solvers_dir}/18xx/1838/Solver1838D.cpp
    ${solvers_dir}/18xx/1838/Solver1838E.cpp
    ${solvers_dir}/18xx/1838/Solver1838F.cpp
    )
target_link_libraries(solver1838 solver_testing_utils gtest gmock algo_lib)
add_test(solver1838 solver1838)
