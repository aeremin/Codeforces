#include "std.h"

#include "io/scan.h"
#include "io/targets.h"
#include "solution_tests/basic.h"
#include "solution_tests/matchers.h"


class SolverF {
public:
  void run();
};

void SolverF::run() {
}

class SolverF_Test : public SolverTest {};

TEST_F(SolverF_Test, Buildin0) {
  SolverF solver;
  send_input(R"(
3
1 2
1 3
)");
  solver.run();
  EXPECT_EQ_TRIMMED(R"(
3
2 3 3
2 1 1
)", get_output());
}
TEST_F(SolverF_Test, Buildin1) {
  SolverF solver;
  send_input(R"(
5
1 2
1 3
2 4
2 5
)");
  solver.run();
  EXPECT_EQ_TRIMMED(R"(
9
3 5 5
4 3 3
4 1 1
4 2 2
)", get_output());
}

int main(int argc, char* argv[]) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
