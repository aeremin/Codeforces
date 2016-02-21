#include <Solvers/pch.h>
#include "algo/Relax.hpp"

using namespace std;

class Solver582B
{
public:
    void run();
};

void Solver582B::run()
{
    int nNumbers, nPeriods;
    cin >> nNumbers >> nPeriods;
    vector<int> numbers(nNumbers);
    for (auto& elt : numbers)
        cin >> elt;

    unordered_map<int, int> numberCount;
    for (auto elt : numbers)
        numberCount[elt]++;

    int maxNumberCount = 0;
    for (auto& p : numberCount)
        relaxMax(maxNumberCount, p.second);

    int periodsToIterate = min(300, nPeriods);
    vector<int> maxLen(periodsToIterate * nNumbers, 1);

    for (int i = 0; i < periodsToIterate * nNumbers; ++i)
        for (int j = i - 1; j >= max(0, i - nNumbers); --j)
            if (numbers[j % nNumbers] <= numbers[i % nNumbers])
                relaxMax(maxLen[i], maxLen[j] + 1);

    int ans = 0;
    for (int i = 0; i < periodsToIterate * nNumbers; ++i)
        relaxMax(ans, maxLen[i] + (nPeriods - i / nNumbers - 1) * maxNumberCount);

    relaxMax(ans, nPeriods * maxNumberCount);

    cout << ans;
}

class Solver582BTest : public ProblemTest
{
};

TEST_F( Solver582BTest, Example1 )
{
    setInput("4 3        3 1 4 2");
    Solver582B().run();
    EXPECT_EQ("5", getOutput());
}

