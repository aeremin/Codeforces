
#include <Solvers/pch.h>

#include "algo/io/baseio.h"
#include "iter/range.h"
#include "util/relax.h"
using namespace std;

// Solution for Codeforces problem http://codeforces.com/contest/1834/problem/C

class Solver1834C {
public:
  void run();
};

void Solver1834C::run() {
  for (int icase : range(read<int>())) {
    int n = read<int>();
    auto s = read<string>();
    auto t = read<string>();

    int ans = 2 * n;

    for (bool has_inversion : {false, true}) {
      for (bool bob_last : {false, true}) {
        int alice_oddity = (has_inversion == bob_last) ? 1 : 0;
        int alice_needs = 0;
        for (int i : range(n)) {
          int j = has_inversion ? n - 1 - i : i;
          if (s[i] != t[j])
            ++alice_needs;
        }
        if (alice_needs % 2 != alice_oddity)
          ++alice_needs;

        int total = 2 * alice_needs - (bob_last ? 0 : 1);
        if (total >= 0) {
          relax_min(ans, total);
        }
      }
    }

    print(ans);
    print("\n");
  }
}


class Solver1834CTest : public ProblemTest {};

TEST_F(Solver1834CTest, Example1) {
  setInput(R"(7
5
abcde
abxde
5
hello
olleo
2
ab
cd
7
aaaaaaa
abbbbba
1
q
q
6
yoyoyo
oyoyoy
8
abcdefgh
hguedfbh
)");
  string output = R"(1
2
3
9
0
2
6

)";
  Solver1834C().run();
  EXPECT_EQ_FUZZY(getOutput(), output);
}
