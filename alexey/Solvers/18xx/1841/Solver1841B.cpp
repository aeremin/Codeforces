
#include <Solvers/pch.h>
#include "algo/io/baseio.h"
#include "algo/io/readvector.h"
#include "iter/range.h"
using namespace std;

// Solution for Codeforces problem http://codeforces.com/contest/1841/problem/B

class Solver1841B {
  public:
    void run();
};

void Solver1841B::run() {
  for (int i : range(read<int>())) {
    int n = read<int>();
    const auto v = readVector<int>(n);

    int jumps = 0;
    vector<int> collected;

    for (auto ind : range(v.size())) {
      auto elt = v[ind];
      auto maybe_jumps = jumps;
      if (collected.size() && elt < collected.back())
        ++maybe_jumps;
      if (collected.size() && elt > collected.front())
        ++maybe_jumps;
      if (collected.size() >= 2 && collected[collected.size() - 1] > collected.front()) {
        --maybe_jumps;
      }
      if (maybe_jumps <= 1) {
        jumps = maybe_jumps;
        print('1');
        collected.push_back(elt);
      } else {
        print('0');
      }
    }
    print("\n");
  }
}


class Solver1841BTest : public ProblemTest {};

TEST_F(Solver1841BTest, Example1) {
    setInput(R"(3
9
3 7 7 9 2 4 6 3 4
5
1 1 1 1 1
5
3 2 1 2 3
)");
    string output = R"(111110010
11111
11011

)";
    Solver1841B().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}


