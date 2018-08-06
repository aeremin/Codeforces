#!/usr/bin/python3

import argparse
import html.parser
import itertools
import os
import sys
import urllib.request

parser = argparse.ArgumentParser(description='Generate solution template for a new contest.')
parser.add_argument('contest_name', metavar='contest-name',
                    help='The name of the contest')
parser.add_argument('--num-problems', type=int, default=0,
                    help='The number of problems in the contest (0 = autodetect)')
parser.add_argument('--contest-family', default='codeforces',
                    help='The name of the competition system')
download_tests_parser = parser.add_mutually_exclusive_group(required=False)
download_tests_parser.add_argument('--download-tests', dest='download_tests', action='store_true')
download_tests_parser.add_argument('--no-download-tests', dest='download_tests', action='store_false')
parser.set_defaults(download_tests=True)

args = parser.parse_args()

assert 0 <= args.num_problems and args.num_problems <= 26, (
  'Invalid number of problems (must be between 0 and 26)')

assert 0 < args.num_problems or args.download_tests, (
  'Cannot determine the number of problems without talking to server')

assert not args.download_tests or args.contest_family == 'codeforces', (
  'Don\'t know how to download tests for "{0}" contest'.format(args.contest_family))


class CodeforcesHTMLParser(html.parser.HTMLParser):
  def __init__(self):
    html.parser.HTMLParser.__init__(self)
    self._tag_stack = []
    self.inputs = []
    self.outputs = []
  def handle_starttag(self, tag, attrs):
    if tag == 'div' and (('class', 'input') in attrs):
      self._tag_stack.append('input')
      self._current_data = ""
    elif tag == 'div' and (('class', 'output') in attrs):
      self._tag_stack.append('output')
      self._current_data = ""
    elif tag == 'pre':
      self._tag_stack.append('pre')
    else:
      if self._inside_input_or_output():
        self._current_data += "\n"
      self._tag_stack.append(None)
  def handle_endtag(self, tag):
    if self._tag_stack[-1:] == ['input']:
      self.inputs.append(self._current_data)
      self._current_data = None
    elif self._tag_stack[-1:] == ['output']:
      self.outputs.append(self._current_data)
      self._current_data = None
    self._tag_stack.pop()
  def handle_data(self, data):
    if self._inside_input_or_output():
      self._current_data += data
  def _inside_input_or_output(self):
    return self._tag_stack[-2:] in [['input', 'pre'], ['output', 'pre']]

def download_tests(problem_name):
  if args.contest_family == 'codeforces':
    request = urllib.request.urlopen('http://codeforces.com/contest/{0}/problem/{1}'.format(args.contest_name, problem_name))
    problem_html = request.read().decode('utf-8')
    parser = CodeforcesHTMLParser()
    parser.feed(problem_html)
    assert len(parser.inputs) == len(parser.outputs)
    return zip(parser.inputs, parser.outputs)
  else:
    raise NotImplementedError('Cannot download tests for "{0}"'.format(args.contest_family))


solution_file_content_template="""
#include "std.h"

#include "io/scan.h"
#include "io/print.h"
#include "io/targets.h"
#include "solution_tests/basic.h"
#include "solution_tests/matchers.h"


class `solver` {
public:
  void run();
};

void `solver`::run() {
}

class `solver`_Test : public SolverTest {};

`tests`

int main(int argc, char* argv[]) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
""".lstrip()


test_template="""
TEST_F(`solver`_Test, `test_name`) {
  `solver` solver;
  send_input(R"(
`input`)");
  solver.run();
  EXPECT_EQ_TRIMMED(R"(
`output`)", get_output());
}
""".strip()


cmake_executable_template="""
add_executable(`lower`_solver ${src_dir}/`upper`/`lower`.cpp)
target_link_libraries(`lower`_solver ${GTEST_LIBRARIES} "gmock" "pthread")
""".strip()


cmake_list_content_template="""
cmake_minimum_required(VERSION 2.6)
project(contest_`contest_name`)

set(src_dir ${CMAKE_SOURCE_DIR})
set(root_dir ${src_dir}/../../..)
set(common_dir ${root_dir}/common)
set(common_lib_dir ${common_dir}/lib)
set(lib_dir ${src_dir}/../../lib)

include(${common_dir}/external/CMakeLists.txt)

include_directories(${common_dir})
include_directories(${common_lib_dir})
include_directories(${lib_dir})

`executables`

add_definitions("-std=c++17 -DLOCAL_PC")
set(CMAKE_CXX_FLAGS "-Wall -Wextra -Wcast-align -Wfloat-conversion -Wunused -Wformat=2 -Wcast-qual -Wold-style-cast -Woverloaded-virtual -Wshadow -Wnon-virtual-dtor -Wno-sign-compare")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O2 -DNDEBUG")
""".lstrip()


def make_test(solver_name, test_name, input_text, output_text):
  return test_template.replace('`solver`', solver_name).replace('`test_name`', test_name).replace('`input`', input_text).replace('`output`', output_text)

contest_path = os.path.join(args.contest_family, args.contest_name)
cmake_list_executables = []

assert not os.path.exists(contest_path)

for i_problem in range(args.num_problems if args.num_problems > 0 else 26):
  problem_name_upper = chr(ord('A') + i_problem)
  problem_name_lower = chr(ord('a') + i_problem)
  solver_name = 'Solver' + problem_name_upper
  if args.download_tests:
    tests = list(download_tests(problem_name_upper))
    if not tests and args.num_problems == 0:
      break
    test_bodies = [make_test(solver_name, 'Buildin' + str(test[0]), test[1][0], test[1][1]) for test in zip(itertools.count(), tests)]
  else:
    test_bodies = [make_test(solver_name, 'Dummy', '', '')]
  problem_dir_path = os.path.join(contest_path, problem_name_upper)
  os.makedirs(problem_dir_path)
  cmake_list_executables.append(cmake_executable_template.strip().replace('`lower`', problem_name_lower).replace('`upper`', problem_name_upper))
  solution_file_content = solution_file_content_template.replace('`solver`', solver_name).replace('`tests`', '\n'.join(test_bodies))
  with open(os.path.join(problem_dir_path, problem_name_lower + '.cpp'), 'w') as f:
    f.write(solution_file_content)


cmake_list_content=cmake_list_content_template.replace('`contest_name`', args.contest_name).replace('`executables`', "\n\n".join(cmake_list_executables))

with open(os.path.join(contest_path, 'CMakeLists.txt'), 'w') as f:
  f.write(cmake_list_content)
