#include "std.h"

#include "io/scan.h"
#include "io/targets.h"
#include "solution_tests/basic.h"
#include "solution_tests/matchers.h"


class SolverG {
public:
  void run();
};

void SolverG::run() {
}

class SolverG_Test : public SolverTest {};

TEST_F(SolverG_Test, Buildin0) {
  SolverG solver;
  send_input(R"(
5
1 2 3 4 5
3
3 5 3 5
1 5 5 1
1 5 1 5
)");
  solver.run();
  EXPECT_EQ_TRIMMED(R"(
5 2 5 4 5 )", get_output());
}

int main(int argc, char* argv[]) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
