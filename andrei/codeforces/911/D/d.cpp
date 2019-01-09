#include "std.h"

#include "io/scan.h"
#include "io/targets.h"
#include "solution_tests/basic.h"
#include "solution_tests/matchers.h"


class SolverD {
public:
  void run();
};

void SolverD::run() {
}

class SolverD_Test : public SolverTest {};

TEST_F(SolverD_Test, Buildin0) {
  SolverD solver;
  send_input(R"(
3
1 2 3
2
1 2
2 3
)");
  solver.run();
  EXPECT_EQ_TRIMMED(R"(
odd
even
)", get_output());
}
TEST_F(SolverD_Test, Buildin1) {
  SolverD solver;
  send_input(R"(
4
1 2 4 3
4
1 1
1 4
1 4
2 3
)");
  solver.run();
  EXPECT_EQ_TRIMMED(R"(
odd
odd
odd
even
)", get_output());
}

int main(int argc, char* argv[]) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
