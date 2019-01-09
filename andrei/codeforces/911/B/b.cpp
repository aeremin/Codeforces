#include "std.h"

#include "io/scan.h"
#include "io/print.h"
#include "io/targets.h"
#include "solution_tests/basic.h"
#include "solution_tests/matchers.h"
#include "iter/range.h"
#include "util/relax.h"


class SolverB {
public:
  void run();
};

void SolverB::run() {
  int n, a, b;
  scan(n, a, b);
  int r = 0;
  for (int i : range(1, n)) {
    LOG(print_ln("###", r));
    relax_max(r, std::min(a / i, b / (n - i)));
  }
  print_ln(r);
}

class SolverB_Test : public SolverTest {};

TEST_F(SolverB_Test, Buildin0) {
  SolverB solver;
  send_input(R"(
5 2 3
)");
  solver.run();
  EXPECT_EQ_TRIMMED(R"(
1
)", get_output());
}
TEST_F(SolverB_Test, Buildin1) {
  SolverB solver;
  send_input(R"(
4 7 10
)");
  solver.run();
  EXPECT_EQ_TRIMMED(R"(
3
)", get_output());
}

int main(int argc, char* argv[]) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
