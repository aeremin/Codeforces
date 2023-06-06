
#include <Solvers/pch.h>

#include "algo/io/baseio.h"
#include "algo/io/printvector.h"
#include "iter/range.h"
using namespace std;

// Solution for Codeforces problem http://codeforces.com/contest/1838/problem/C

class Solver1838C {
public:
  void run();
};

void Solver1838C::run() {
  for (int l : range(read<int>())) {
    int n = read<int>();
    int m = read<int>();
    if (m % 2 == 0) {
      vector<int> line(m);
      for (int i : range(n)) {
        for (int j : range(m)) {
          line[j] = 1 + j + i * m;
        }
        printVector(line);
        print("\n");
      }
    } else {
      vector<int> line(m);
      int pos = 0;
      for (int i : range(n)) {
        for (int j : range(m)) {
          line[(pos + j) % m] = 1 + j + i * m;
        }
        printVector(line);
        print("\n");
        if (pos == 0) {
          pos = m - 1;
        } else {
          --pos;
        }
      }
    }
    print("\n");
  }
}


class Solver1838CTest : public ProblemTest {};

TEST_F(Solver1838CTest, Example1) {
  setInput(R"(3
4 4
5 7
6 4
)");
  string output = R"(1 2 3 4
5 6 7 8
9 10 11 12
13 14 15 16

1 2 3 4 5 6 7
9 10 11 12 13 14 8
17 18 19 20 21 15 16
25 26 27 28 22 23 24
33 34 35 29 30 31 32

1 2 3 4
5 6 7 8
9 10 11 12
13 14 15 16
17 18 19 20
21 22 23 24
)";
  Solver1838C().run();
  EXPECT_EQ_FUZZY(getOutput(), output);
}
