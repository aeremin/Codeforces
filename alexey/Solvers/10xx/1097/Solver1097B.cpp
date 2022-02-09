#include <Solvers/pch.h>
#include "algo/io/baseio.h"
#include "iter/range.h"
#include "algo/io/readvector.h"
using namespace std;

// Solution for Codeforces problem http://codeforces.com/contest/1097/problem/B
class Solver1097B {
public:
    void run();
};

void Solver1097B::run() {
    auto n = read<int>();
    auto r = readVector<int>(n);
    for (int mask = 0; mask < (1 << n); ++mask) {
        int sum = 0;
        for (int i = 0; i < n; ++i) {
            sum += (mask & (1 << i)) ? r[i] : -r[i];
        }
        if (sum % 360 == 0) {
            cout << "YES";
            return;
        }
    }
    cout << "NO";
}


class Solver1097BTest : public ProblemTest {};


TEST_F(Solver1097BTest, Example1) {
    setInput(R"(
3
10
20
30

)");
    string output = R"(
YES

)";
    Solver1097B().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}

TEST_F(Solver1097BTest, Example2) {
    setInput(R"(
3
10
10
10

)");
    string output = R"(
NO

)";
    Solver1097B().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}

TEST_F(Solver1097BTest, Example3) {
    setInput(R"(
3
120
120
120

)");
    string output = R"(
YES

)";
    Solver1097B().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}

