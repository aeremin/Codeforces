
#include <Solvers/pch.h>
#include "algo/io/baseio.h"
#include "iter/range.h"
using namespace std;

// Solution for Codeforces problem http://codeforces.com/contest/1107/problem/B
      
class Solver1107B {
  public:
    void run();
};

void Solver1107B::run() {
    int n = read<int>();
    for (int i : range(n)) {
        auto k = read<int64_t>();
        auto x = read<int64_t>();
        cout << 9 * (k - 1) + x << "\n";
    }
}


class Solver1107BTest : public ProblemTest {};
    
TEST_F(Solver1107BTest, Example1) {
    setInput(R"(
4
1 5
5 2
3 1
1 9

)");
    string output = R"(
5
38
19
9
)";
    Solver1107B().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}


