
#include <Solvers/pch.h>

#include "algo/io/baseio.h"
#include "iter/range.h"
using namespace std;

// Solution for Codeforces problem http://codeforces.com/contest/1834/problem/B

class Solver1834B {
public:
  void run();
};

void Solver1834B::run() {
  for (int icase : range(read<int>())) {
    auto l = read<string>();
    auto r = read<string>();

    l = string(r.length() - l.length(), '0') + l;

    int ans = 0;
    for (int i : range(r.length())) {
      if (l[i] != r[i]) {
        ans = r[i] - l[i] + 9 * (r.length() - i - 1);
        break;
      }
    }

    print(ans);
    print("\n");
  }
}


class Solver1834BTest : public ProblemTest {};

TEST_F(Solver1834BTest, Example1) {
  setInput(R"(6
53 57
179 239
13 37
132228 132228
54943329752812629795 55157581939688863366
88 1914
)");
  string output = R"(4
19
11
0
163
28

)";
  Solver1834B().run();
  EXPECT_EQ_FUZZY(getOutput(), output);
}
