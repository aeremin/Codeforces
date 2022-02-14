
#include <Solvers/pch.h>
#include "algo/io/baseio.h"
#include "algo/io/readvector.h"
#include "iter/range.h"
using namespace std;

// Solution for Codeforces problem http://codeforces.com/contest/1637/problem/A
      
class Solver1637A {
  public:
    void run();
};

void Solver1637A::run() {
    for (int i : range(read<int>())) {
        auto v = readVector<int>(read<int>());
        bool sorted = true;
        for (int j : range<int>(1, v.size())) {
            sorted = sorted && v[j] >= v[j-1];
        }
        print(sorted ? "NO\n" : "YES\n");
    }
}


class Solver1637ATest : public ProblemTest {};
    
TEST_F(Solver1637ATest, Example1) {
    setInput(R"(
3
3
2 2 1
4
3 1 2 1
5
1 2 2 4 4

)");
    string output = R"(
YES
YES
NO

)";
    Solver1637A().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}


