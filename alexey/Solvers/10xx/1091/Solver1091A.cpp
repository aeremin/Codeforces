#include <Solvers/pch.h>
#include "algo/io/baseio.hpp"
#include "iter/range.h"
using namespace std;

// Solution for Codeforces problem http://codeforces.com/contest/1091/problem/A
class Solver1091A {
public:
    void run();
};

void Solver1091A::run() {
    int y, b, r;
    cin >> y >> b >> r;
    cout << 3 * min({ b, r - 1, y + 1 });
}


class Solver1091ATest : public ProblemTest {};


TEST_F(Solver1091ATest, Example1) {
    string input = R"(
8 13 9

)";
    string output = R"(24
)";
    setInput(input);
    Solver1091A().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}

TEST_F(Solver1091ATest, Example2) {
    string input = R"(
13 3 6

)";
    string output = R"(9
)";
    setInput(input);
    Solver1091A().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}

