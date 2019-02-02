
#include <Solvers/pch.h>
#include "algo/io/baseio.hpp"
#include "iter/range.h"
#include "algo/io/readvector.hpp"
using namespace std;

// Solution for Codeforces problem http://codeforces.com/contest/1106/problem/A
      
class Solver1106A {
  public:
    void run();
};

void Solver1106A::run() {
    auto m = readVector<string>(read<int>());
    int ans = 0;
    for (int i : range<int>(1, m.size() - 1)) {
        for (int j : range<int>(1, m.size() - 1)) {
            if (m[i][j] == 'X' && m[i - 1][j - 1] == 'X' &&m[i + 1][j + 1] == 'X' &&m[i + 1][j - 1] == 'X' &&m[i - 1][j + 1] == 'X') {
                ++ans;
            }
        }
    }

    cout << ans;
}


class Solver1106ATest : public ProblemTest {};
    
TEST_F(Solver1106ATest, Example1) {
    setInput(R"(
5
.....
.XXX.
.XXX.
.XXX.
.....

)");
    string output = R"(
1

)";
    Solver1106A().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}

TEST_F(Solver1106ATest, Example2) {
    setInput(R"(
2
XX
XX

)");
    string output = R"(
0

)";
    Solver1106A().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}

TEST_F(Solver1106ATest, Example3) {
    setInput(R"(
6
......
X.X.X.
.X.X.X
X.X.X.
.X.X.X
......

)");
    string output = R"(
4

)";
    Solver1106A().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}


