#include "std.h"

#include "io/scan.h"
#include "io/targets.h"
#include "solution_tests/basic.h"
#include "solution_tests/matchers.h"
#include "io/print.h"
#include "container/container_alg.h"


class SolverC {
public:
  void run();
};

void SolverC::run() {
  auto k = scan_vector<int>(3);
  c_sort(k);
  int k1 = k[0], k2 = k[1], k3 = k[2];
  bool yes = false;
  yes |= k1 == 1;
  yes |= k1 == 2 && k2 == 2;
  yes |= k1 == 2 && k2 == 4 && k3 == 4;
  yes |= k1 == 3 && k2 == 3 && k3 == 3;
  print_ln(yes ? "YES" : "NO");
}

class SolverC_Test : public SolverTest {};

TEST_F(SolverC_Test, Buildin0) {
  SolverC solver;
  send_input(R"(
2 2 3
)");
  solver.run();
  EXPECT_EQ_TRIMMED(R"(
YES
)", get_output());
}
TEST_F(SolverC_Test, Buildin1) {
  SolverC solver;
  send_input(R"(
4 2 3
)");
  solver.run();
  EXPECT_EQ_TRIMMED(R"(
NO
)", get_output());
}

int main(int argc, char* argv[]) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
