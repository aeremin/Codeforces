#include "std.h"

#include "io/scan.h"
#include "io/targets.h"
#include "solution_tests/basic.h"
#include "solution_tests/matchers.h"


class SolverB {
public:
  void run();
};

int calc(int n, int a, int b) {
  if (4*a + 2*b <= n)
    return 1;
  else if ((4*a <= n && 2*b <= n) || (2*a + b <= n))
    return 2;
  else if (((a + b) <= n && 2*a <= n) || (4*a <= n && b <= n))
    return 3;
  else if ((2*a <= n && b <= n) || (a + b) <= n)
    return 4;
  else if (a <= n && 2*b <= n)
    return 5;
  else
    return 6;
}

void SolverB::run() {
  int n = scan();
  int a = scan();
  int b = scan();
  std::cout << calc(n, a, b);
}

class SolverB_Test : public SolverTest {};

TEST_F(SolverB_Test, Buildin0) {
  SolverB solver;
  send_input(R"(
8
1
2
)");
  solver.run();
  EXPECT_EQ_TRIMMED(R"(
1
)", get_output());
}
TEST_F(SolverB_Test, Buildin1) {
  SolverB solver;
  send_input(R"(
5
3
4
)");
  solver.run();
  EXPECT_EQ_TRIMMED(R"(
6
)", get_output());
}
TEST_F(SolverB_Test, Buildin2) {
  SolverB solver;
  send_input(R"(
6
4
2
)");
  solver.run();
  EXPECT_EQ_TRIMMED(R"(
4
)", get_output());
}
TEST_F(SolverB_Test, Buildin3) {
  SolverB solver;
  send_input(R"(
20
5
6
)");
  solver.run();
  EXPECT_EQ_TRIMMED(R"(
2
)", get_output());
}

int main(int argc, char* argv[]) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
