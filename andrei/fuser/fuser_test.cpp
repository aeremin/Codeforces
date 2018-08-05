#include "tools/fuser/file_parser.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "solution_tests/matchers.h"

using testing::ElementsAre;


TEST(ParseFile, SolutionFile) {
  const std::string input = R"input(
#include <iostream>

#include "std.h"
#include "io/targets.h"
#include "solution_tests/basic.h"


class SolverC {
public:
  void run();
};

void SolverC::run() {
}

class SolverC_Test : public SolverTest {};

TEST_F(SolverC_Test, Buildin0) {
  SolverC solver;
  send_input(R"(
3
ab
de
aj
)");
  solver.run();
  EXPECT_EQ(R"(
47
)", get_output());
}
TEST_F(SolverC_Test, Buildin1) {
  SolverC solver;
  send_input(R"(
5
abcdef
ghij
bdef
accbd
g
)");
  solver.run();
  EXPECT_EQ(R"(
136542
)", get_output());
}

int main(int argc, char* argv[]) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
    )input";

  std::istringstream stream(input);
  const ParsedFile parsed_file = ParseFile(stream, ParserOptions{}, /*is_header=*/false);

  std::string code;
  for (const std::string& l : parsed_file.code_lines)
    code += l + "\n";
  EXPECT_EQ_TRIMMED(code, R"(
class SolverC {
public:
  void run();
};

void SolverC::run() {
}


int main() {
    SolverC solver;
    solver.run();
}
  )"
  );

  EXPECT_THAT(parsed_file.system_includes, ElementsAre("iostream"));
  EXPECT_THAT(parsed_file.local_includes, ElementsAre("std.h", "io/targets.h"));
  EXPECT_TRUE(parsed_file.problems.empty());
}
