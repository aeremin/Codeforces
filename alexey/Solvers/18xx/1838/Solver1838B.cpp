
#include <Solvers/pch.h>

#include "algo/io/baseio.h"
#include "algo/io/readvector.h"
#include "iter/range.h"
using namespace std;

// Solution for Codeforces problem http://codeforces.com/contest/1838/problem/B

class Solver1838B {
public:
  void run();
};

void Solver1838B::run() {
  for (int k : range(read<int>())) {
    auto nums = readVector<int>(read<int>());
    auto p1 = find(begin(nums), end(nums), 1) - begin(nums) + 1;
    auto p2 = find(begin(nums), end(nums), 2) - begin(nums) + 1;
    auto pN = find(begin(nums), end(nums), nums.size()) - begin(nums) + 1;
    print(pN);
    print(" ");
    print(p1 + p2 + pN - max({p1, p2, pN}) - min({p1, p2, pN}));
    print("\n");
  }
}


class Solver1838BTest : public ProblemTest {};

TEST_F(Solver1838BTest, Example1) {
  setInput(R"(8
3
1 2 3
3
1 3 2
5
1 3 2 5 4
6
4 5 6 1 2 3
9
8 7 6 3 2 1 4 5 9
10
7 10 5 1 9 8 3 2 6 4
10
8 5 10 9 2 1 3 4 6 7
10
2 3 5 7 10 1 8 6 4 9
)");
  string output = R"(3 2
2 2
4 3
3 4
9 6
2 4
3 5
5 5
)";
  Solver1838B().run();
  EXPECT_EQ_FUZZY(getOutput(), output);
}
