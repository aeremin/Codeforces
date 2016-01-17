#include <Solvers/pch.h>
#include "algo/FunctorIterator.hpp"
#include "algo/Relax.hpp"

using namespace std;

class Solver000B
{
public:
    void run();
    void runOneTest();
};

void Solver000B::run()
{
    int t;
    cin >> t;
    for (int i = 0; i < t; ++i)
    {
        cout << "Case #" << (i + 1) << ": ";
        runOneTest();
        if (i != t - 1) cout << "\n";
    }
}

void Solver000B::runOneTest()
{
    int64_t nLoads, nWashers, nDryers, dryTime;
    cin >> nLoads >> nWashers >> nDryers >> dryTime;

    vector<int64_t> washTime(nWashers);
    for (auto& t : washTime)
        cin >> t;

    auto canWashIn = [&](int64_t t) -> int64_t
    {
        int64_t res = 0;
        for (auto& w : washTime)
            res += t / w;
        return res;
    };

    auto l = makeFunctorIterator(int64_t(0), canWashIn);
    auto r = makeFunctorIterator(int64_t(1e16), canWashIn);
    auto minTimeToWashEverything = lower_bound(l, r, nLoads).getParameter();

    vector<int64_t> finishTimes;
    for (auto& w : washTime)
        for (int64_t m = 1; m * w <= minTimeToWashEverything; ++m)
            finishTimes.push_back(m * w);

    sort(begin(finishTimes), end(finishTimes));
    finishTimes.erase(begin(finishTimes) + nLoads, end(finishTimes));

    priority_queue<int64_t, vector<int64_t>, greater<int64_t>> dryingQueue;
    for (int64_t i = 0; i < min(nLoads, nDryers); ++i)
        dryingQueue.push(0);

    int64_t ans = 0;
    for (auto t : finishTimes)
    {
        auto firstAvailableDryingStart = dryingQueue.top();
        dryingQueue.pop();
        auto dryFinishTime = dryTime + max(t, firstAvailableDryingStart);
        dryingQueue.push(dryFinishTime);
        relaxMax(ans, dryFinishTime);
    }

    cout << ans;
}

class Solver000BTest : public ProblemTest
{
};

TEST_F( Solver000BTest, Example )
{
    setInput(
        R"(5
1 1 1 34
1200
2 3 2 10
100 10 1
3 3 3 3
1 2 3
4 2 2 7
5 8
999 1 999 6
3
)");

    std::string expected = 
R"(Case #1: 1234
Case #2: 12
Case #3: 5
Case #4: 22
Case #5: 3003)";
    Solver000B().run();
    EXPECT_EQ(expected, getOutput());
}