#include <Solvers/pch.h>
#include "algo/numbertheory/GreatestCommonDivisor.hpp"

using namespace std;

class Solver613C
{
public:
    void run();

    vector<int64_t> colorCounts;
    int nBeads;

    void printZeroExample()
    {
        cout << 0 << "\n";
        for (int i = 0; i < colorCounts.size(); ++i)
            for (int k = 0; k < colorCounts[i]; ++k)
                cout << char('a' + i);
    }

    void printExample(int count, const vector<char>& period)
    {
        cout << count << "\n";
        for (int i = 0; i < nBeads; ++i)
            cout << period[i % period.size()];
    }

    vector<char> generatePeriod(int countDivisor)
    {
        vector<char> res(nBeads / countDivisor);
        int i = 0;
        for (int iColor = 0; iColor < colorCounts.size(); ++iColor)
        {
            auto cnt = colorCounts[iColor] / countDivisor;
            if (cnt % 2 == 1)
            {
                res[(nBeads - 1) / (2 * countDivisor)] = 'a' + iColor;
                --cnt;
            }
            for (int t = 0; t < cnt / 2; ++t)
                res[t + i] = res[(nBeads - 1) / countDivisor - t - i] = 'a' + iColor;
            i += cnt / 2;
        }
        return res;
    }
};

void Solver613C::run()
{
    int nColors;
    cin >> nColors;
    colorCounts = vector<int64_t>(nColors);
    for (auto& elt : colorCounts)
        cin >> elt;

    nBeads = accumulate(begin(colorCounts), end(colorCounts), 0);
    int colorCountsGCD = greatestCommonDivisor(colorCounts);
    int nOdd = count_if(begin(colorCounts), end(colorCounts), [](int k) { return k % 2 == 1; });

    if (nBeads % 2 == 1)
        if (nOdd > 1)
            printZeroExample();
        else
            printExample(colorCountsGCD, generatePeriod(colorCountsGCD));
    else
        if (colorCountsGCD % 2 == 1)
            printZeroExample();
        else
            printExample(colorCountsGCD, generatePeriod(colorCountsGCD / 2));
}

class Solver613CTest : public ProblemTest
{};

TEST_F(Solver613CTest, Example1)
{
    setInput("3             4 2 1");
    Solver613C().run();
    EXPECT_EQ("1\naabcbaa", getOutput());
}

TEST_F(Solver613CTest, Example2)
{
    setInput("1             4             ");
    Solver613C().run();
    EXPECT_EQ("4\naaaa", getOutput());
}

TEST_F(Solver613CTest, Example3)
{
    setInput("2             1 1");
    Solver613C().run();
    EXPECT_EQ("0\nab", getOutput());
}

TEST_F(Solver613CTest, Example4)
{
    setInput("1             5");
    Solver613C().run();
    EXPECT_EQ("5\naaaaa", getOutput());
}

TEST_F(Solver613CTest, Example5)
{
    setInput("3             3 3 3");
    Solver613C().run();
    EXPECT_EQ("0\naaabbbccc", getOutput());
}


TEST_F(Solver613CTest, Example6)
{
    setInput("2             3 6");
    Solver613C().run();
    EXPECT_EQ("3\nbabbabbab", getOutput());
}

TEST_F(Solver613CTest, Example7)
{
    setInput("2             4 4");
    Solver613C().run();
    EXPECT_EQ("4\nabbaabba", getOutput());
}
