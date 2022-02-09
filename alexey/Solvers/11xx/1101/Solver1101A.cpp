#include <Solvers/pch.h>
#include "algo/io/baseio.h"
#include "iter/range.h"
using namespace std;

// Solution for Codeforces problem http://codeforces.com/contest/1101/problem/A
class Solver1101A {
public:
    void run();
};

void Solver1101A::run() {
    auto n = read<int>();
    for (int i : range(n)) {
        auto l = read<int64_t>();
        auto r = read<int64_t>();
        auto d = read<int64_t>();
        if (d < l) {
            cout << d << "\n";
        }
        else {
            cout << (((r / d) * d) + d) << "\n";
        }
    }
}


class Solver1101ATest : public ProblemTest {};


TEST_F(Solver1101ATest, Example1) {
    setInput(R"(
5
2 4 2
5 10 4
3 10 1
1 2 3
4 6 5

)");
    string output = R"(
6
4
1
3
10

)";
    Solver1101A().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}

