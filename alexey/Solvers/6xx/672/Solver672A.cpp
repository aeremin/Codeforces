#include <Solvers/pch.h>
#include "algo/io/baseio.hpp"
#include "iter/range.h"
using namespace std;

class Solver672A {
public:
    void run();
};

void Solver672A::run() {
    string s;
    for (int i : range(1000))
        s += to_string(i);

    cout << s[read<int>()];
}


class Solver672ATest : public ProblemTest {};


TEST_F(Solver672ATest, Example1) {
    string input = R"(3
)";
    string output = R"(3
)";
    setInput(input);
    Solver672A().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}

TEST_F(Solver672ATest, Example2) {
    string input = R"(11
)";
    string output = R"(0
)";
    setInput(input);
    Solver672A().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}

