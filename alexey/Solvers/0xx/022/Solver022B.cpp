#include <Solvers/pch.h>

using namespace std;

// Solution for Codeforces problem http://codeforces.com/contest/022/problem/B
class Solver022B
{
public:
    void run();
};

void Solver022B::run()
{
    int n, m; 
    cin >> n >> m;
    vector<vector<int>> office(n, vector<int>(m));
    for (auto& row : office)
        for (auto& elt : row)
        {
            char c; 
            cin >> c; 
            elt = c == '1' ? 1 : 0;
        }

    vector<vector<int>> sum(n + 1, vector<int>(m + 1, 0));
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j)
            sum[i][j] = office[i - 1][j - 1] + sum[i - 1][j] + sum[i][j - 1] - sum[i - 1][j - 1];

    int maxPerimeter = 0;
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
            for (int ii = i; ii < n; ++ii)
                for (int jj = j; jj < m; ++jj)
                    if (sum[ii + 1][jj + 1] - sum[i][jj + 1] - sum[ii + 1][j] + sum[i][j] == 0)
                        maxPerimeter = max(maxPerimeter, 2 * (2 + ii + jj - i - j));

    cout << maxPerimeter;
}

class Solver022BTest : public ProblemTest
{
};

TEST_F( Solver022BTest, Example1 )
{
    setInput(
R"(3 3
000
010
000)"
);
    Solver022B().run();
    EXPECT_EQ("8", getOutput());
}

TEST_F( Solver022BTest, Example2 )
{
    setInput(
R"(5 4
1100
0000
0000
0000
0000)");
    Solver022B().run();
    EXPECT_EQ("16", getOutput());
}
