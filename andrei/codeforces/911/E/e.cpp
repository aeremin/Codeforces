#include "std.h"

#include "io/scan.h"
#include "io/targets.h"
#include "solution_tests/basic.h"
#include "solution_tests/matchers.h"


class SolverE {
public:
  void run();
};

void SolverE::run() {
}

class SolverE_Test : public SolverTest {};

TEST_F(SolverE_Test, Buildin0) {
  SolverE solver;
  send_input(R"(
5 3
3 2 1
)");
  solver.run();
  EXPECT_EQ_TRIMMED(R"(
3 2 1 5 4 )", get_output());
}
TEST_F(SolverE_Test, Buildin1) {
  SolverE solver;
  send_input(R"(
5 3
2 3 1
)");
  solver.run();
  EXPECT_EQ_TRIMMED(R"(
-1
)", get_output());
}
TEST_F(SolverE_Test, Buildin2) {
  SolverE solver;
  send_input(R"(
5 1
3
)");
  solver.run();
  EXPECT_EQ_TRIMMED(R"(
3 2 1 5 4 )", get_output());
}
TEST_F(SolverE_Test, Buildin3) {
  SolverE solver;
  send_input(R"(
5 2
3 4
)");
  solver.run();
  EXPECT_EQ_TRIMMED(R"(
-1
)", get_output());
}

int main(int argc, char* argv[]) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
