#include <Solvers/pch.h>

using namespace std;

class Solver489F
{
public:
    void run();
};

void Solver489F::run()
{
    int n, m, mod;
    cin >> n >> m >> mod;

    vector<int> onesCount(n, 0);
    for (int i = 0; i < m; ++i)
    {
        string line;
        cin >> line;
        for (int j = 0; j < n; ++j)
            if (line[j] == '1')
                onesCount[j]++;
    }

    auto startColumnsWithOneOne = count(begin(onesCount), end(onesCount), 1);
    auto startColumnsWithTwoOnes = count(begin(onesCount), end(onesCount), 2);
    
    vector<vector<int64_t>> ans(n + 1, vector<int64_t>(n + 1, 0));
    ans[startColumnsWithOneOne][startColumnsWithTwoOnes] = 1;

    for (int columnsWithTwoOnes = 0; columnsWithTwoOnes <= n; ++columnsWithTwoOnes)
        for (int columnsWithOneOne = 0; columnsWithOneOne <= n; ++columnsWithOneOne)
        {
            auto columsWithZeroOnes = n - columnsWithOneOne - columnsWithTwoOnes;
            auto& currRef = ans[columnsWithOneOne][columnsWithTwoOnes];
            if (columnsWithTwoOnes >= 2 && columnsWithOneOne + 2 <= n)
                currRef = (currRef + ((columnsWithOneOne + 2)*(columnsWithOneOne + 1) / 2) * ans[columnsWithOneOne + 2][columnsWithTwoOnes - 2]) % mod;
            if (columnsWithTwoOnes >= 1 && columnsWithOneOne >= 1)
                currRef = (currRef + columnsWithOneOne * (columsWithZeroOnes + 1) * ans[columnsWithOneOne][columnsWithTwoOnes - 1]) % mod;
            if (columnsWithOneOne >= 2)
                currRef = (currRef + ((columsWithZeroOnes + 2)*(columsWithZeroOnes + 1) / 2) * ans[columnsWithOneOne - 2][columnsWithTwoOnes]) % mod;
        }

    cout << ans[0][n];
}

class Solver489FTest : public ProblemTest
{
};

TEST_F( Solver489FTest, Example1 )
{
    setInput(R"(3 1 1000
011)");
    Solver489F().run();
    EXPECT_EQ("2", getOutput());
}

TEST_F(Solver489FTest, Example2)
{
    setInput(R"(4 4 100500
0110
1010
0101
1001)");
    Solver489F().run();
    EXPECT_EQ("1", getOutput());
}
