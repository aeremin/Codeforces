
#include <Solvers/pch.h>

#include "algo/io/baseio.h"
#include "algo/io/readvector.h"
#include "iter/range.h"
using namespace std;

// Solution for Codeforces problem http://codeforces.com/contest/1834/problem/A

class Solver1834A {
public:
  void run();
};

void Solver1834A::run() {
  for (int icase : range(read<int>())) {
    auto a = readVector<int>(read<int>());
    int x = std::count(a.begin(), a.end(), 1);
    int y = std::count(a.begin(), a.end(), -1);
    int ans = 0;

    if (y > x) {
      auto t = (y - x + 1) / 2;
      ans += t;

      x += t;
      y -= t;
    }
    
    if (y % 2 == 1) {
      ++ans;
    }

    print(ans);
    print("\n");
  }
}


class Solver1834ATest : public ProblemTest {};

TEST_F(Solver1834ATest, Example1) {
  setInput(R"(7
4
-1 -1 1 -1
5
-1 -1 -1 1 1
4
-1 1 -1 1
3
-1 -1 -1
5
1 1 1 1 1
1
-1
2
-1 -1
)");
  string output = R"(1
1
0
3
0
1
2

)";
  Solver1834A().run();
  EXPECT_EQ_FUZZY(getOutput(), output);
}
