
#include <Solvers/pch.h>

#include "algo/io/baseio.h"
#include "algo/io/readvector.h"
#include "algo/number_theory/residue.h"
#include "iter/range.h"
#include "math/factorial.h"
#include "math/quick_power.h"
using namespace std;

// Solution for Codeforces problem http://codeforces.com/contest/1838/problem/E

class Solver1838E {
public:
  void run();
};

void Solver1838E::run() {
  for (int _ : range(read<int>())) {
    auto n = read<int64_t>();
    auto m = read<int64_t>();
    auto k = read<int64_t>();
    auto x = readVector<int>(n);
    if (k == 1) {
      print("1\n");
      continue;
    }

    CodeforcesResidue64 s = 0;
    CodeforcesResidue64 v = quick_power(CodeforcesResidue64(k - 1), m);
    for (int l : range(n)) {
      s += v;
      v *= CodeforcesResidue64(m - l) / (CodeforcesResidue64(l + 1) * CodeforcesResidue64(k - 1));
    }

    auto result = quick_power(CodeforcesResidue64(k), m) - s;
    print(result.rep());
    print("\n");
  }
}


class Solver1838ETest : public ProblemTest {};

TEST_F(Solver1838ETest, Example1) {
  setInput(R"(7
1 1000000 1
1
3 4 3
1 2 2
5 7 8
1 2 3 4 1
6 6 18
18 2 2 5 2 16
1 10 2
1
8 10 1234567
1 1 2 1 2 2 2 1
5 1000000000 1000000000
525785549 816356460 108064697 194447117 725595511
)");
  string output = R"(1
9
1079
1
1023
906241579
232432822
)";
  Solver1838E().run();
  EXPECT_EQ_FUZZY(getOutput(), output);
}
