
#include <Solvers/pch.h>
#include "algo/io/baseio.h"
#include "algo/io/readvector.h"
#include "iter/range.h"
using namespace std;

// Solution for Codeforces problem http://codeforces.com/contest/1637/problem/B
      
class Solver1637B {
  public:
    void run();
};

void Solver1637B::run() {
    for (int i : range(read<int>())) {
        auto v = readVector<int>(read<int>());
        int64_t cost = 0;
        for (int j: range<int>(v.size() + 1)) {
            cost += j * (v.size() + 1 - j);
        }

        for (int j: range<int>(v.size())) {
            if (v[j] == 0) {
                cost += (j + 1) * (v.size() - j);
            }
        }
        print(cost);
        print("\n");
    }
}


class Solver1637BTest : public ProblemTest {};
    
TEST_F(Solver1637BTest, Example1) {
    setInput(R"(
4
2
1 2
3
2 0 1
4
2 0 5 1
5
0 1 1 0 1

)");
    string output = R"(
4
14
26
48

)";
    Solver1637B().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}


