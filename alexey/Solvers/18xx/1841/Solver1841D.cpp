
#include <Solvers/pch.h>

#include "algo/io/baseio.h"
#include "algo/sort_by.h"
#include "iter/range.h"
#include "util/relax.h"
using namespace std;

// Solution for Codeforces problem http://codeforces.com/contest/1841/problem/D

class Solver1841D {
public:
  void run();
};

void Solver1841D::run() {
  for (int i_case : range(read<int>())) {
    int n = read<int>();
    vector<pair<int, int>> intervals(n);
    for (auto& [l, r] : intervals) {
      l = read<int>();
      r = read<int>();
    }

    sortBy(intervals, [](auto& p) { return p.second; });

    vector<int> dp(n + 1, 0);

    for (int i : range(n)) {
      dp[i + 1] = dp[i] + 1;
      auto p1 = intervals[i];
      for (int j = i - 1; j >= 0; --j) {
        auto p2 = intervals[j];
        if (p2.second < p1.first)
          break;

        auto it_k = lower_bound(begin(intervals), end(intervals), make_pair(0, min(p1.first, p2.first)),
                                [](const pair<int, int>& a, const pair<int, int>& b) { return a.second < b.second; });
        auto k = it_k - begin(intervals) - 1;
        relax_min<int>(dp[i + 1], i - k - 2 + dp[k + 1]);
      }
    }
    print(dp[n]);
    print("\n");
  }
}


class Solver1841DTest : public ProblemTest {};

TEST_F(Solver1841DTest, Example1) {
  setInput(R"(3
7
2 4
9 12
2 4
7 7
4 8
10 13
6 8
5
2 2
2 8
0 10
1 2
5 6
4
1 1
2 2
3 3
4 4
)");
  string output = R"(1
3
4
)";
  Solver1841D().run();
  EXPECT_EQ_FUZZY(getOutput(), output);
}
