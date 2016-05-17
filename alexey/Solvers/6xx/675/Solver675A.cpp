#include <Solvers/pch.h>
#include "algo/io/baseio.hpp"
#include "iter/range.h"
#include "math/sign.h"
using namespace std;

class Solver675A {
public:
    void run();
};

void Solver675A::run() {
    int64_t a, b, c;
    cin >> a >> b >> c;
    bool ans = (a == b) ||
               (sgn(b - a) == sgn(c)  && (sgn(c) == 0 || ((b - a) % c == 0)));
    
    if (ans) cout << "YES"; else cout << "NO";
}


class Solver675ATest : public ProblemTest {};


TEST_F(Solver675ATest, Example1) {
    string input = R"(1 7 3
)";
    string output = R"(YES
)";
    output.pop_back();
    setInput(input);
    Solver675A().run();
    EXPECT_EQ(output, getOutput());
}

TEST_F(Solver675ATest, Example2) {
    string input = R"(10 10 0
)";
    string output = R"(YES
)";
    output.pop_back();
    setInput(input);
    Solver675A().run();
    EXPECT_EQ(output, getOutput());
}

TEST_F(Solver675ATest, Example3) {
    string input = R"(1 -4 5
)";
    string output = R"(NO
)";
    output.pop_back();
    setInput(input);
    Solver675A().run();
    EXPECT_EQ(output, getOutput());
}

TEST_F(Solver675ATest, Example4) {
    string input = R"(0 60 50
)";
    string output = R"(NO
)";
    output.pop_back();
    setInput(input);
    Solver675A().run();
    EXPECT_EQ(output, getOutput());
}

