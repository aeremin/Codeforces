#include <Solvers/pch.h>
#include "algo/io/printvector.h"

using namespace std;

// Solution for Codeforces problem http://codeforces.com/contest/625/problem/C
class Solver625C
{
public:
    void run();
};

void Solver625C::run()
{
    int n, k;
    cin >> n >> k;
    vector<vector<int>> res(n, vector<int>(n));
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < k - 1; ++j)
            res[i][j] = i * (k - 1) + j + 1;

        for (int j = k - 1; j < n; ++j)
            res[i][j] = (k - 1) * n + i * (n - k + 1) + (j - k) + 2;
    }

    int sum = 0;
    for (int i = 0; i < n; ++i)
        sum += res[i][k - 1];

    cout << sum << "\n";

    for (auto& line : res)
    {
        printVector(line);
        cout << "\n";
    }
}

class Solver625CTest : public ProblemTest {};

TEST_F(Solver625CTest, Example1)
{
    string input = R"(4 1
)";
    string output = R"(28
1 2 3 4
5 6 7 8
9 10 11 12
13 14 15 16
)";
    setInput(input);
    Solver625C().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}


TEST_F(Solver625CTest, Example2)
{
    string input = R"(5 3
)";
    string output = R"(85
1 2 11 12 13
3 4 14 15 16
5 6 17 18 19
7 8 20 21 22
9 10 23 24 25
)";
    setInput(input);
    Solver625C().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}


