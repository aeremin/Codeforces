#!/usr/bin/python3

import argparse
import time
import os

parser = argparse.ArgumentParser(description='Generate solution template for a new contest.')
parser.add_argument('contest_name',
                    help='The name of the contest')
parser.add_argument('--num_problems', type=int, default=5,
                    help='The number of problems in the contest')
parser.add_argument('--contest_family', default='codeforces',
                    help='The name of the competition system')

args = parser.parse_args()

assert 1 <= args.num_problems and args.num_problems <= 26, "Invalid number of problems (must be between 1 and 26)"


solution_file_content_template="""
#include "std.h"

#include "io/scan.h"
#include "io/targets.h"
#include "solution_tests/basic.h"


class `solver` {
public:
  void run();
};

void `solver`::run() {
}

class `solver`_Test : public SolverTest {};

TEST_F(`solver`_Test, Test0) {
  `solver` solver;
  send_input(R"()");
  solver.run();
  EXPECT_EQ(R"()", get_output());
}

int main(int argc, char* argv[]) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
""".lstrip()


cmake_executable_template="""
add_executable(`lower`_solver ${src_dir}/`upper`/`lower`.cpp)
target_link_libraries(`lower`_solver ${GTEST_LIBRARIES} "pthread")
""".strip()


cmake_list_content_template="""
cmake_minimum_required(VERSION 2.6)
project(contest_`contest_name`)

find_package(GTest REQUIRED)

set(src_dir ${CMAKE_SOURCE_DIR})
set(lib_dir ${CMAKE_SOURCE_DIR}/../../lib)

include_directories(${lib_dir})

`executables`

add_definitions("-std=c++11 -DLOCAL_PC")
set(CMAKE_CXX_FLAGS "-Wall -Wextra -Wcast-align -Wconversion -Wunused -Wformat=2 -Wcast-qual -Wold-style-cast -Woverloaded-virtual -Wshadow -Wnon-virtual-dtor -Wsuggest-override -Werror")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O2 -DNDEBUG")
""".lstrip()


contest_path = os.path.join(args.contest_family, args.contest_name)
cmake_list_executables = []

for i_problem in range(args.num_problems):
  problem_name_upper = chr(ord('A') + i_problem)
  problem_name_lower = chr(ord('a') + i_problem)
  problem_dir_path = os.path.join(contest_path, problem_name_upper)
  os.makedirs(problem_dir_path)
  cmake_list_executables.append(cmake_executable_template.strip().replace('`lower`', problem_name_lower).replace('`upper`', problem_name_upper))
  solution_file_content=solution_file_content_template.replace('`solver`', 'Solver' + problem_name_upper)
  with open(os.path.join(problem_dir_path, problem_name_lower + '.cpp'), 'w') as f:
    f.write(solution_file_content)


cmake_list_content=cmake_list_content_template.replace('`contest_name`', args.contest_name).replace('`executables`', "\n\n".join(cmake_list_executables))

with open(os.path.join(contest_path, 'CMakeLists.txt'), 'w') as f:
  f.write(cmake_list_content)
