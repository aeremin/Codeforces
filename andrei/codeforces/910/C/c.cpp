#include "std.h"

#include "io/scan.h"
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
TEST_F(SolverC_Test, Buildin2) {
  SolverC solver;
  send_input(R"(
3
aa
jj
aa
)");
  solver.run();
  EXPECT_EQ(R"(
44
)", get_output());
}

int main(int argc, char* argv[]) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
