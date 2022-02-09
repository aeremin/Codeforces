#include <Solvers/pch.h>
#include "algo/io/baseio.h"
#include "iter/range.h"
using namespace std;

// Solution for Codeforces problem http://codeforces.com/contest/1100/problem/C
class Solver1100C {
public:
    void run();
};

void Solver1100C::run() {
    auto n = read<int>();
    auto R = read<double>();
    double s = sin(3.14159265358979323846 / n);
    double r = R * s / (1 - s);
    cout << std::setprecision(7) << r;
}


class Solver1100CTest : public ProblemTest {};


TEST_F(Solver1100CTest, Example1) {
    setInput(R"(3 1
)");
    string output = R"(6.4641016
)";
    Solver1100C().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}

TEST_F(Solver1100CTest, Example2) {
    setInput(R"(6 1
)");
    string output = R"(1
)";
    Solver1100C().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}

TEST_F(Solver1100CTest, Example3) {
    setInput(R"(100 100
)");
    string output = R"(3.2429391
)";
    Solver1100C().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}

