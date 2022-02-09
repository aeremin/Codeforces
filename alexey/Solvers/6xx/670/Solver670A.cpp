#include <Solvers/pch.h>
#include "algo/io/baseio.h"
#include "iter/range.h"
using namespace std;

// Solution for Codeforces problem http://codeforces.com/contest/670/problem/A
class Solver670A {
public:
    void run();
};

void Solver670A::run() {
    int n;
    cin >> n;
    int minPos = 0, maxPos = 0;
    for (int i : range(n)) {
        if (i % 7 == 0 || i % 7 == 1) maxPos++;
        if (i % 7 == 5 || i % 7 == 6) minPos++;
    }

    cout << minPos << " " << maxPos;
}


class Solver670ATest : public ProblemTest {};


TEST_F(Solver670ATest, Example1) {
    string input = R"(14
)";
    string output = R"(4 4
)";
    setInput(input);
    Solver670A().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}

TEST_F(Solver670ATest, Example2) {
    string input = R"(2
)";
    string output = R"(0 2
)";
    setInput(input);
    Solver670A().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}

