#include <Solvers/pch.h>
#include "algo/io/baseio.h"
#include "iter/range.h"
#include "algo/io/readvector.h"
#include "algo/algebra/quadratic/solve_quadratic_real.h"
using namespace std;

// Solution for Codeforces problem http://codeforces.com/contest/668/problem/C
class Solver668C {
public:
    void run();
};

void Solver668C::run() {
    int n = read<int>();
    auto maxProb = readVector<double>(n);
    auto minProb = readVector<double>(n);

    vector<double> distFunctionMax = { 0 };
    partial_sum(begin(maxProb), end(maxProb), back_inserter(distFunctionMax));

    vector<double> distFunctionMin = { 0 };
    partial_sum(begin(minProb), end(minProb), back_inserter(distFunctionMin));

    vector<double> distFunctionFirst(n + 1), distFunctionSecond(n + 1);
    distFunctionFirst.back() = distFunctionSecond.back() = 1.0;

    for (int i : range(1, n)) {
        auto alpha = distFunctionMax[i];
        auto beta = 1.0 - distFunctionMin[i];

        auto roots = solve_quadratic_equation(1.0, beta - alpha - 1.0, alpha);
        distFunctionFirst[i] = roots.first;
        distFunctionSecond[i] = roots.second;
    }

    for (auto& distFunction : { distFunctionFirst, distFunctionSecond }) {
        for (int i : range(n)) {
            auto v = max(0.0, distFunction[i + 1] - distFunction[i]);
            print(v);
            print(' ');
        }
        print('\n');
    }
}
 

#include "solution_tests/matchers.h"

class Solver668CTest : public ProblemTest {};


TEST_F(Solver668CTest, Example1) {
    string input = R"(2
0.25 0.75
0.75 0.25
)";
    string output = R"(0.5 0.5 
0.5 0.5 
)";
    setInput(input);
    Solver668C().run();
    EXPECT_THAT(getOutput(), EqualsFuzzy(output));
}
TEST_F(Solver668CTest, Example2) {
    string input = R"(3
0.125 0.25 0.625
0.625 0.25 0.125
)";
    string output = R"(0.25 0.25 0.5 
0.5 0.25 0.25 
)";
    setInput(input);
    Solver668C().run();
    EXPECT_THAT(getOutput(), EqualsFuzzy(output));
}
TEST_F(Solver668CTest, Example3) {
    string input = R"(2
0.25 0.75
0.75 0.25
)";
    string output = R"(0.5 0.5 
0.5 0.5 
)";
    setInput(input);
    Solver668C().run();
    EXPECT_THAT(getOutput(), EqualsFuzzy(output));
}
TEST_F(Solver668CTest, Example4) {
    string input = R"(3
0.125 0.25 0.625
0.625 0.25 0.125
)";
    string output = R"(0.25 0.25 0.5 
0.5 0.25 0.25 
)";
    setInput(input);
    Solver668C().run();
    EXPECT_THAT(getOutput(), EqualsFuzzy(output));
}
