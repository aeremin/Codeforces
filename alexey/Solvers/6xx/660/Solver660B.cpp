#include <Solvers/pch.h>
#include "algo/io/baseio.hpp"
#include "iter/range.h"
using namespace std;

// Solution for Codeforces problem http://codeforces.com/contest/660/problem/B
class Solver660B
{
public:
    void run();
};

void Solver660B::run()
{
    int n, m;
    cin >> n >> m;
    vector<int> ind(4 * n);
    for (int i : range(1, m + 1))
        ind[i - 1] = i;

    for (int i : range(2 * n)) {
        if (ind[i + 2 * n] != 0) cout << ind[i + 2 * n] << " ";
        if (ind[i] != 0) cout << ind[i] << " ";
    }
}

class Solver660BTest : public ProblemTest {};

TEST_F(Solver660BTest, Example1)
{
    string input = R"(2 7
)";
    string output = R"(5 1 6 2 7 3 4 
)";
    setInput(input);
    Solver660B().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}


TEST_F(Solver660BTest, Example2)
{
    string input = R"(9 36
)";
    string output = R"(19 1 20 2 21 3 22 4 23 5 24 6 25 7 26 8 27 9 28 10 29 11 30 12 31 13 32 14 33 15 34 16 35 17 36 18 
)";
    setInput(input);
    Solver660B().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}


