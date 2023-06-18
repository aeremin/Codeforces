
#include <Solvers/pch.h>

#include "algo/io/baseio.h"
#include "algo/io/readvector.h"
#include "iter/range.h"
using namespace std;

// Solution for Codeforces problem http://codeforces.com/contest/1836/problem/A

class Solver1836A {
public:
  void run();
};

void Solver1836A::run() {
  for (int icase : range(read<int>())) {
    auto l = readVector<int>(read<int>());

    bool correct = true;
    int M = *max_element(begin(l), end(l));
    map<int, int> counts;
    for (auto el : l)
      ++counts[el];

    int last = numeric_limits<int>::max();
    for (int t : range(M + 1)) {
      correct = correct && counts[t] <= last;
      last = counts[t];
    }

    print(correct ? "YES" : "NO");
    print("\n");
  }
}


class Solver1836ATest : public ProblemTest {};

TEST_F(Solver1836ATest, Example1) {
  setInput(R"(5
6
0 1 2 0 1 0
9
0 0 0 0 1 1 1 2 2
3
0 0 2
1
99
5
0 1 2 3 4
)");
  string output = R"(YES
YES
NO
NO
YES

)";
  Solver1836A().run();
  EXPECT_EQ_FUZZY(getOutput(), output);
}
