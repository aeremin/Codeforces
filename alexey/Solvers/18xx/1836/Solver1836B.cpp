
#include <Solvers/pch.h>

#include "algo/io/baseio.h"
#include "iter/range.h"
#include "util/relax.h"
using namespace std;

// Solution for Codeforces problem http://codeforces.com/contest/1836/problem/B

class Solver1836B {
public:
  void run();
};

void Solver1836B::run() {
  for (int icase : range(read<int>())) {
    int64_t n = read<int64_t>();
    int64_t k = read<int64_t>();
    int64_t g = read<int64_t>();

    int64_t f = (g - 1) / 2;

    int64_t ans = 0;
    if (g > 2) {
      int64_t p = min(n - 1, k * g / f);

      for (int64_t q : {p, p - 1}) {
        if (q >= 0) {
          int64_t t = (k * g - q * f) % g;
          if (t <= f) {
            int64_t saved = t + q * f;
            relax_max(ans, saved);
          } else {
            int64_t saved = t - g + q * f;
            relax_max(ans, saved);
          }
        }
      }
    }

    print(ans);
    print("\n");
  }
}


class Solver1836BTest : public ProblemTest {};

TEST_F(Solver1836BTest, Example1) {
  setInput(R"(7
3 3 100
2 1 14
91 2 13
36 16 6
73 8 22
2 22 14
2 22 13
)");
  string output = R"(100
0
26
72
176
0
0
)";
  Solver1836B().run();
  EXPECT_EQ_FUZZY(getOutput(), output);
}
