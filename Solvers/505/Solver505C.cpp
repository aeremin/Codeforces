#include <Solvers/pch.h>

using namespace std;

class Solver505C
{
public:
    void run();

    const int nIslands = 30001;
    int maxIslandContainingTreasure = 0;

    int step;

    int possibleSteps = 4 * sqrt(nIslands);
    vector<vector<int>> resultCache = vector<vector<int>>(nIslands, vector<int>(possibleSteps, -1));

    inline int hasher(const pair<int, int>& a)
    {
        return (a.first << 15) + a.second;
    }

    int& access(int iIsland, int iStep)
    {
        return resultCache[iIsland][iStep - step + possibleSteps / 2];
    }

    vector<int> nDiamonds = vector<int>(nIslands, 0);

    int maxStep = 0;
    int nFromCache = 0;
    int nCalculated = 0;

    int result(int start, int prevStep)
    {
        maxStep = max(maxStep, prevStep);

        if (start > maxIslandContainingTreasure)
            return 0;

        auto& cached = access(start, prevStep);
        if (cached >= 0)
        {
            ++nFromCache;
            return cached;
        }
        ++nCalculated;

        int r1 = result(start + prevStep + 1, prevStep + 1);
        int r2 = result(start + prevStep, prevStep);
        int r3 = (prevStep > 1) ? result(start + prevStep - 1, prevStep - 1) : 0;

        cached = max(max(r1, r2), r3) + nDiamonds[start];
        return cached;
    }

};

void Solver505C::run()
{
    int n;
    cin >> n >> step;
    for (int i = 0; i < n; ++i)
    {
        int t;
        cin >> t;
        maxIslandContainingTreasure = max(maxIslandContainingTreasure, t);
        nDiamonds[t]++;
    }

    cout << nDiamonds[0] + result(step, step);
}

class Solver505CTest : public ProblemTest
{
};

TEST_F( Solver505CTest, Example1 )
{
    setInput("4 10        10        21        27        27");
    Solver505C().run();
    EXPECT_EQ("3", getOutput());
}

TEST_F( Solver505CTest, Example2 )
{
    setInput("8 8        9        19        28        36        45        55        66        78");
    Solver505C().run();
    EXPECT_EQ("6", getOutput());
}

TEST_F(Solver505CTest, Example3)
{
    setInput("13 7        8        8        9        16        17        17        18        21        23        24        24        26        30");
    Solver505C().run();
    EXPECT_EQ("4", getOutput());
}
