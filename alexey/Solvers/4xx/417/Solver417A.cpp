#include <Solvers/pch.h>

using namespace std;

class Solver417A
{
public:
    void run();
};

void Solver417A::run()
{
    int c, d;
    cin >> c >> d;

    int n, m;
    cin >> n >> m;

    int k;
    cin >> k;

    vector<int> maxWinnersPerProblemCount = { k };
    while (maxWinnersPerProblemCount.back() < n * m)
    {
        int nextProblemCount = maxWinnersPerProblemCount.size();
        int nextMaxWinners = k;
        if (nextProblemCount >= c)
            nextMaxWinners = max(nextMaxWinners, maxWinnersPerProblemCount[nextProblemCount - c] + n);
        if (nextProblemCount >= d)
            nextMaxWinners = max(nextMaxWinners, maxWinnersPerProblemCount[nextProblemCount - d] + 1);
        maxWinnersPerProblemCount.push_back(nextMaxWinners);
    }

    cout << maxWinnersPerProblemCount.size() - 1;

}

class Solver417ATest : public ProblemTest
{
};

TEST_F( Solver417ATest, Example1 )
{
    setInput("1 10        7 2        1");
    Solver417A().run();
    EXPECT_EQ("2", getOutput());
}

TEST_F( Solver417ATest, Example2 )
{
    setInput("2 2        2 1        2");
    Solver417A().run();
    EXPECT_EQ("0", getOutput());
}