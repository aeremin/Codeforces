#include "std.h"

#include "io/scan.h"
#include "io/targets.h"
#include "solution_tests/basic.h"
#include "solution_tests/matchers.h"


class SolverA {
public:
  void run();
};

void SolverA::run() {
  int n = scan();
  int d = scan();
  string s = scan();
  CHECK(n == s.size());
  int x = 0;
  int num_jumps = 0;
  while (x < n - 1) {
    int y = min(x + d, n - 1);
    while (s[y] == '0' && y > x)
      --y;
    if (y <= x) {
      std::cout << -1;
      return;
    }
    x = y;
    ++num_jumps;
  }
  std::cout << num_jumps;
}

class SolverA_Test : public SolverTest {};

TEST_F(SolverA_Test, Buildin0) {
  SolverA solver;
  send_input(R"(
8 4
10010101
)");
  solver.run();
  EXPECT_EQ_TRIMMED(R"(
2
)", get_output());
}
TEST_F(SolverA_Test, Buildin1) {
  SolverA solver;
  send_input(R"(
4 2
1001
)");
  solver.run();
  EXPECT_EQ_TRIMMED(R"(
-1
)", get_output());
}
TEST_F(SolverA_Test, Buildin2) {
  SolverA solver;
  send_input(R"(
8 4
11100101
)");
  solver.run();
  EXPECT_EQ_TRIMMED(R"(
3
)", get_output());
}
TEST_F(SolverA_Test, Buildin3) {
  SolverA solver;
  send_input(R"(
12 3
101111100101
)");
  solver.run();
  EXPECT_EQ_TRIMMED(R"(
4
)", get_output());
}

int main(int argc, char* argv[]) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
