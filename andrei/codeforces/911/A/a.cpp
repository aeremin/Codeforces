#include "std.h"

#include "io/scan.h"
#include "io/print.h"
#include "io/targets.h"
#include "iter/range.h"
#include "container/container_alg_minmax.h"
#include "solution_tests/basic.h"
#include "solution_tests/matchers.h"
#include "util/relax.h"


class SolverA {
public:
  void run();
};

void SolverA::run() {
  int n = scan();
  auto v = scan_vector<int>(n);
  int minval = *c_min_element(v);
  int last = -1;
  int min_dist = std::numeric_limits<int>::max();
  for (int i : range(v.size())) {
    if (v[i] == minval) {
      if (last >= 0)
        relax_min(min_dist, i - last);
      last = i;
    }
  }
  print_ln(min_dist);
}

class SolverA_Test : public SolverTest {};

TEST_F(SolverA_Test, Buildin0) {
  SolverA solver;
  send_input(R"(
2
3 3
)");
  solver.run();
  EXPECT_EQ_TRIMMED(R"(
1
)", get_output());
}
TEST_F(SolverA_Test, Buildin1) {
  SolverA solver;
  send_input(R"(
3
5 6 5
)");
  solver.run();
  EXPECT_EQ_TRIMMED(R"(
2
)", get_output());
}
TEST_F(SolverA_Test, Buildin2) {
  SolverA solver;
  send_input(R"(
9
2 1 3 5 4 1 2 3 1
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
