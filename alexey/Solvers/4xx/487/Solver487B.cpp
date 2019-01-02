#include <Solvers/pch.h>
#include "algo/SlidingWindowMinFinder.h"

using namespace std;

// Solution for Codeforces problem http://codeforces.com/contest/487/problem/B
class Solver487B
{
public:
    void run();
};

void Solver487B::run()
{
    int nNumbers, maxDif, minLen;
    cin >> nNumbers >> maxDif >> minLen;

    vector<int> tape, minustape;
    for (int i = 0; i < nNumbers; ++i)
    {
        int t;
        cin >> t;
        tape.push_back(t);
        minustape.push_back(-t);
    }

    SlidingWindowMinFinder<int> minFinder(tape);
    SlidingWindowMinFinder<int> maxFinder(minustape);

    vector<int> maxBack;
    int left = 0;
    for (int right = 0; right < nNumbers; ++right)
    {
        minFinder.incRight();
        maxFinder.incRight();

        int min = minFinder.getMin();
        int max = -maxFinder.getMin();
        while (max - min > maxDif)
        {
            minFinder.incLeft();
            maxFinder.incLeft();
            left++;
            min = minFinder.getMin();
            max = -maxFinder.getMin();
        }
        maxBack.push_back(right - left + 1);
    }

    vector<int> minParts;
    SlidingWindowMinFinder<int> resultFinder(minParts);

    for (int i = 0; i < nNumbers; ++i)
    {
        if (i + 1 < minLen)
        {
            minParts.push_back(numeric_limits<int>::max());
            continue;
        }

        if (maxBack[i] == i + 1)
        {
            minParts.push_back(1);
            continue;
        }

        if (maxBack[i] < minLen)
        {
            minParts.push_back(numeric_limits<int>::max());
            continue;
        }

        while (resultFinder.getLeft() < i - maxBack[i]) resultFinder.incLeft();
        while (resultFinder.getRight() <= i - minLen) resultFinder.incRight();
        int curMinParts = resultFinder.getMin();
        if (curMinParts < numeric_limits<int>::max()) curMinParts++;
        minParts.push_back(curMinParts);
    }

    if (minParts.back() < numeric_limits<int>::max())
    {
        cout << minParts.back();
    }
    else
    {
        cout << -1;
    }
}

class Solver487BTest : public ProblemTest {};

TEST_F(Solver487BTest, Example1)
{
    setInput("7 2 2     1 3 1 2 4 1 2");
    Solver487B().run();
    EXPECT_EQ("3", getOutput());
}

TEST_F(Solver487BTest, Example2)
{
    setInput("7 2 2   1 100 1 100 1 100 1");
    Solver487B().run();
    EXPECT_EQ("-1", getOutput());
}