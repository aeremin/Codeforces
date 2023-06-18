
#include <Solvers/pch.h>

#include "algo/io/baseio.h"
#include "iter/range.h"
#include "math/quick_power.h"
using namespace std;

// Solution for Codeforces problem http://codeforces.com/contest/1836/problem/C

class Solver1836C {
public:
  void run();
};

void Solver1836C::run() {
  for (int icase : range(read<int>())) {
    int A = read<int>();
    int B = read<int>();
    int C = read<int>();
    int64_t k = read<int64_t>() - 1;

    bool found = false;

    for (int a : range(quick_power(10, A - 1), quick_power(10, A))) {
      int min_b = max(quick_power(10, B - 1), quick_power(10, C - 1) - a);
      int max_b_plus_one = min(quick_power(10, B), quick_power(10, C) - a);
      int l = max(0, max_b_plus_one - min_b);
      if (l > k) {
        int b = min_b + k;
        int c = a + b;
        print(a);
        print(" + ");
        print(b);
        print(" = ");
        print(c);
        print("\n");
        found = true;
        break;
      } else {
        k -= l;
      }
    }

    if (!found) {
      print("-1\n");
    }
  }
}


class Solver1836CTest : public ProblemTest {};

TEST_F(Solver1836CTest, Example1) {
  setInput(R"(7
2 2 3 1
1 1 1 9
2 2 1 1
1 5 6 42
1 6 6 10000000
5 5 6 3031568815
6 6 6 1000000000000
)");
  string output = R"(10 + 90 = 100
2 + 1 = 3
-1
9 + 99996 = 100005
-1
78506 + 28543 = 107049
-1

)";
  Solver1836C().run();
  EXPECT_EQ_FUZZY(getOutput(), output);
}
