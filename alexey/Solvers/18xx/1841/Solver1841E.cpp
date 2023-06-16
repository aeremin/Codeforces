
#include <Solvers/pch.h>

#include "algo/io/baseio.h"
#include "algo/io/readvector.h"
#include "algo/segment_tree/binary_functors/max.h"
#include "algo/segment_tree/segment_tree.h"
#include "algo/segment_tree/update_appliers/set_to_idempotent.h"
#include "algo/segment_tree/update_types/set_to.h"
#include "iter/range.h"

using namespace std;

// Solution for Codeforces problem http://codeforces.com/contest/1841/problem/E

class Solver1841E {
public:
  void run();
};

void Solver1841E::run() {
  for (int test : range(read<int>())) {
    int n = read<int>();
    auto depths = readVector<int>(n);

    map<int, vector<int>> depth_to_indices;
    for (int i : range(n)) {
      depth_to_indices[depths[i]].push_back(i);
    }

    auto st = makeSegmentTree(depths, binary_functors::Max<int>(), update_types::SetTo<int>());

    vector<int64_t> interval_counts(n + 1, 0);

    set<int> encountered = {-1, n};
    interval_counts[n] = n - st.getValueOnSegment(0, n);
    for (int d = n; d > 0; --d) {
      encountered.insert(begin(depth_to_indices[d]), end(depth_to_indices[d]));
      for (auto m : depth_to_indices[d]) {
        auto it = encountered.find(m);
        auto l = *prev(it);
        auto r = *next(it);
        if (m - l - 1 > 0) {
          interval_counts[m - l - 1] += d - st.getValueOnSegment(l + 1, m);
        }
        if (r - m - 1 > 0 && (r >= n || depths[r] != d)) {
          interval_counts[r - m - 1] += d - st.getValueOnSegment(m + 1, r);
        }
      }
    }

    auto m = read<int64_t>();
    int64_t answer = 0;
    for (int l = n; l > 1; --l) {
      auto t = min<int64_t>(m / l, interval_counts[l]);
      interval_counts[l] -= t;
      m -= l * t;

      answer += t * (l - 1);

      if (interval_counts[l] > 0 && m > 0) {
        answer += m - 1;
        m = 0;
      }
    }
    print(answer);
    print("\n");
  }
}


class Solver1841ETest : public ProblemTest {};

TEST_F(Solver1841ETest, Example1) {
  setInput(R"(6
3
0 0 0
9
4
2 0 3 1
5
4
2 0 3 1
6
4
2 0 3 1
10
10
0 2 2 1 5 10 3 4 1 1
20
1
1
0
)");
  string output = R"(6
3
4
4
16
0

)";
  Solver1841E().run();
  EXPECT_EQ_FUZZY(getOutput(), output);
}
