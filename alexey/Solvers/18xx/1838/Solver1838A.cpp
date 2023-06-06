
#include <Solvers/pch.h>

#include "algo/io/baseio.h"
#include "algo/io/readvector.h"
#include "iter/range.h"
using namespace std;

// Solution for Codeforces problem http://codeforces.com/contest/1838/problem/A

class Solver1838A {
public:
  void run();
};

void Solver1838A::run() {
  for (int k : range(read<int>())) {
    auto nums = readVector<int>(read<int>());
    auto m = *min_element(begin(nums), end(nums));
    auto M = *max_element(begin(nums), end(nums));
    if (m < 0) {
      print(m);
      print("\n");
    } else {
      print(M);
      print("\n");
    }
  }
}


class Solver1838ATest : public ProblemTest {};

TEST_F(Solver1838ATest, Example1) {
  setInput(R"(9
3
9 2 7
3
15 -4 11
4
-9 1 11 -10
5
3 0 0 0 3
7
8 16 8 0 8 16 8
4
0 0 0 0
10
27 1 24 28 2 -1 26 25 28 27
6
600000000 800000000 0 -200000000 1000000000 800000000
3
0 -1000000000 1000000000
)");
  string output = R"(9
-4
-10
3
16
0
-1
-200000000
-1000000000
)";
  Solver1838A().run();
  EXPECT_EQ_FUZZY(getOutput(), output);
}
