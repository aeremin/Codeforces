#include <Solvers/pch.h>
#include "algo/io/baseio.hpp"
#include "iter/range.h"
using namespace std;

// Solution for Codeforces problem http://codeforces.com/contest/1102/problem/A
class Solver1102A {
public:
    void run();
};

void Solver1102A::run() {
    auto n = read<int64_t>();
    if (auto r = n % 4; r == 1 || r == 2) {
        cout << 1;
    } else {
        cout << 0;
    }
}


class Solver1102ATest : public ProblemTest {};


TEST_F(Solver1102ATest, Example1) {
    setInput(R"(
3

)");
    string output = R"(
0

)";
    Solver1102A().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}

TEST_F(Solver1102ATest, Example2) {
    setInput(R"(
5

)");
    string output = R"(
1

)";
    Solver1102A().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}

TEST_F(Solver1102ATest, Example3) {
    setInput(R"(
6

)");
    string output = R"(
1

)";
    Solver1102A().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}

