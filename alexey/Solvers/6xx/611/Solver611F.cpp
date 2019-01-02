#include <Solvers/pch.h>
#include "algo/numbertheory/Residue.hpp"

using namespace std;

// Solution for Codeforces problem http://codeforces.com/contest/611/problem/F
class Solver611F
{
public:
    void run();

    int64_t patternLen, width, height;
    string pattern;

    void prolongArray(vector<int64_t>& times, int neededSize, int stepPerPattern)
    {
        auto startSize = times.size();
        for (int i = startSize; i < neededSize; ++i)
        {
            if (stepPerPattern > 0)
                times.push_back(times[i - stepPerPattern] + patternLen);
            else
                times.push_back(numeric_limits<int64_t>::max());
        }
    }
};

void Solver611F::run()
{
    cin >> patternLen >> height >> width;
    cin >> pattern;

    vector<int64_t> timesToLeft = { 0 }, timesToRight = { 0 }, timesToTop = { 0 }, timesToBottom = { 0 };

    int64_t x = 0, y = 0;
    for (int64_t t = 1; t <= pattern.length(); ++t)
    {
        auto c = pattern[t - 1];
        if (c == 'U')
        {
            ++y;
            if (y >= timesToTop.size()) timesToTop.push_back(t);
        }
        if (c == 'D')
        {
            --y;
            if (-y >= timesToBottom.size()) timesToBottom.push_back(t);
        }
        if (c == 'R')
        {
            ++x;
            if (x >= timesToRight.size()) timesToRight.push_back(t);
        }
        if (c == 'L')
        {
            --x;
            if (-x >= timesToLeft.size()) timesToLeft.push_back(t);;
        }
    }

    prolongArray(timesToTop, height + 1, y);
    prolongArray(timesToBottom, height + 1, -y);
    prolongArray(timesToRight, width + 1, x);
    prolongArray(timesToLeft, width + 1, -x);

    vector<int64_t> timesToLeftPS, timesToRightPS;
    auto smartSummator = [](int64_t a, int64_t b) -> int64_t
    {
        return (max(a, b) == numeric_limits<int64_t>::max()) ? numeric_limits<int64_t>::max() : a + b;
    };
    partial_sum(begin(timesToRight), end(timesToRight), back_inserter(timesToRightPS), smartSummator);
    partial_sum(begin(timesToLeft), end(timesToLeft), back_inserter(timesToLeftPS), smartSummator);
    
    int64_t totalHorizontalTimePerLine = 0;
    for (int i = 0; i < width; ++i)
        totalHorizontalTimePerLine = smartSummator(min(timesToLeft[i + 1], timesToRight[width - i]), totalHorizontalTimePerLine);
    
    CodeforcesResidue ans = 0;
    
    for (int yy = 0; yy < height; ++yy)
    {
        auto timeToTopOrBottom = min(timesToBottom[yy + 1], timesToTop[height - yy]);
        auto it1 = upper_bound(begin(timesToLeft), end(timesToLeft), timeToTopOrBottom) - begin(timesToLeft) - 1;
        auto it2 = upper_bound(begin(timesToRight), end(timesToRight), timeToTopOrBottom) - begin(timesToRight) - 1;
        if (it1 + it2 > width)
        {
            if (totalHorizontalTimePerLine == numeric_limits<int64_t>::max())
            {
                cout << -1;
                return;
            }
            ans += totalHorizontalTimePerLine;
        }
        else
        {
            ans += timesToLeftPS[it1];
            ans += timesToRightPS[it2];
            ans += (width - it1 - it2) * timeToTopOrBottom;
        }
    }

    cout << ans.rep();
}

class Solver611FTest : public ProblemTest
{
};

TEST_F( Solver611FTest, Example1 )
{
    setInput("1 10 2        R");
    Solver611F().run();
    EXPECT_EQ("30", getOutput());
}

TEST_F( Solver611FTest, Example2 )
{
    setInput("3 4 6        RUL");
    Solver611F().run();
    EXPECT_EQ("134", getOutput());
}

TEST_F(Solver611FTest, Example3)
{
    setInput("4 1 5000        RLRL");
    Solver611F().run();
    EXPECT_EQ("-1", getOutput());
}

TEST_F(Solver611FTest, Example4)
{
    setInput("4 2 2        RULDRULDRULDRULD");
    Solver611F().run();
    EXPECT_EQ("-1", getOutput());
}