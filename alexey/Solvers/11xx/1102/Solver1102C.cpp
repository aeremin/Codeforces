#include <Solvers/pch.h>
#include "algo/io/baseio.h"
#include "algo/io/readvector.h"
#include "iter/range.h"
using namespace std;

// Solution for Codeforces problem http://codeforces.com/contest/1102/problem/C
class Solver1102C {
public:
    void run();
};

void Solver1102C::run() {
    auto n = read<int>();
    auto x = read<int>();
    auto y = read<int>();
    auto doors = readVector<int>(n);
    if (y < x) {
        cout << n;
        return;
    }
    int small_doors = count_if(begin(doors), end(doors),
        [&](int d) {return d <= x; });
    cout << (small_doors + 1) / 2;
}


class Solver1102CTest : public ProblemTest {};


TEST_F(Solver1102CTest, Example1) {
    setInput(R"(
6 3 2
2 3 1 3 4 2

)");
    string output = R"(
6

)";
    Solver1102C().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}

TEST_F(Solver1102CTest, Example2) {
    setInput(R"(
5 3 3
1 2 4 2 3

)");
    string output = R"(
2

)";
    Solver1102C().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}

TEST_F(Solver1102CTest, Example3) {
    setInput(R"(
5 5 6
1 2 6 10 3

)");
    string output = R"(
2

)";
    Solver1102C().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}

