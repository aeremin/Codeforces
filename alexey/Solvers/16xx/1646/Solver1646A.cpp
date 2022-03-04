
#include <Solvers/pch.h>
#include "algo/io/baseio.h"
#include "iter/range.h"
using namespace std;

// Solution for Codeforces problem http://codeforces.com/contest/1646/problem/A
      
class Solver1646A {
  public:
    void run();
};

void Solver1646A::run() {
    for (int i: range(read<int>())) {
        auto n = read<int64_t>();
        auto s = read<int64_t>();
        print(s / (n * n));
        print("\n");
    }
}


class Solver1646ATest : public ProblemTest {};
    
TEST_F(Solver1646ATest, Example1) {
    setInput(R"(
4
7 0
1 1
2 12
3 12

)");
    string output = R"(
0
1
3
1

)";
    Solver1646A().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}


