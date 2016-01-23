#include <Solvers/pch.h>
#include "algo/numbertheory/Residue.hpp"

using namespace std;

class SolverFBHC2C
{
public:
    void run();
    void runOneTest();
};

void SolverFBHC2C::run()
{
    int t;
    cin >> t;
    for (int i = 1; i <= t; ++i)
    {
        cout << "Case #" << i << ": ";
        runOneTest();
        if (i != t) cout << "\n";
    }
}

void SolverFBHC2C::runOneTest()
{
    int n;
    cin >> n;
    vector<pair<int64_t, int64_t>> heightAndPosition(n);
    for (auto& p : heightAndPosition)
    {
        cin >> p.second >> p.first;
        p.first = -p.first;
    }

    sort(begin(heightAndPosition), end(heightAndPosition));
    heightAndPosition.push_back({ 1, 0 });

    CodeforcesResidue64 totalPrice = 0;
    int64_t prevHeight = numeric_limits<int64_t>::min();
    set<int64_t> blockedPositions;

    CodeforcesResidue64 sum = 0;
    CodeforcesResidue64 sumOfSquares = 0;
    CodeforcesResidue64 count = 0;
    pair<int64_t, int64_t> prevLadder;
    for (auto ladder : heightAndPosition)
    {
        if (ladder.first != prevHeight)
        {
            prevHeight = ladder.first;
            totalPrice += count * sumOfSquares - sum * sum;
            count = 1;
            sumOfSquares = ladder.second * ladder.second;
            sum = ladder.second;
        }
        else
        {
            if ((blockedPositions.upper_bound(prevLadder.second) != blockedPositions.upper_bound(ladder.second)))
            {
                totalPrice += count * sumOfSquares - sum * sum;
                count = 0;
                sumOfSquares = 0;
                sum = 0;
            }
            count++;
            sum += ladder.second;
            sumOfSquares += ladder.second * ladder.second;
        }
        prevLadder = ladder;
        blockedPositions.insert(ladder.second);
    }

    cout << totalPrice;
}

class SolverFBHC2CTest : public FBHCProblemTest
{
public:
    SolverFBHC2CTest() : FBHCProblemTest("Inputs\\FBHC\\Round2\\C\\") {}
};

TEST_F(SolverFBHC2CTest, Example )
{
    SolverFBHC2C().run();
}

