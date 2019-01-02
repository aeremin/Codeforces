#include <Solvers/pch.h>
#include "algo/io/baseio.hpp"
#include "iter/range.h"
#include "algo/numbertheory/Divisors.hpp"
using namespace std;

// Solution for Codeforces problem http://codeforces.com/contest/1091/problem/C
class Solver1091C {
public:
    void run();
};

void Solver1091C::run() {
    int64_t n;
    cin >> n;
    auto divisors = getDivisorsOf(n);
    vector<int64_t> divisors_reversed{ divisors.rbegin(), divisors.rend() };
    for (auto d : divisors_reversed) {
        auto e = n / d;
        cout << (e * (n + 2 - d)) / 2 << " ";
    }
}


class Solver1091CTest : public ProblemTest {};


TEST_F(Solver1091CTest, Example1) {
    string input = R"(
6

)";
    string output = R"(1 5 9 21 
)";
    setInput(input);
    Solver1091C().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}

TEST_F(Solver1091CTest, Example2) {
    string input = R"(
16

)";
    string output = R"(1 10 28 64 136 
)";
    setInput(input);
    Solver1091C().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}

