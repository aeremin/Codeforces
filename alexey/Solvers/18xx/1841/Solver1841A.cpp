
#include <Solvers/pch.h>
#include "algo/io/baseio.h"
#include "iter/range.h"
using namespace std;

// Solution for Codeforces problem http://codeforces.com/contest/1841/problem/A

class Solver1841A {
  public:
    void run();
};

void Solver1841A::run() {
  for (int i : range(read<int>())) {
    int n = read<int>();
    if (n <= 4) {
      print("Bob\n");
    } else {
      print("Alice\n");
    }
  }
}


class Solver1841ATest : public ProblemTest {};

TEST_F(Solver1841ATest, Example1) {
    setInput(R"(2
3
6
)");
    string output = R"(Bob
Alice

)";
    Solver1841A().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}


