#include "Solvers/pch.h"

// Solution for Codeforces problem http://codeforces.com/contest/580/problem/A
class Solver580A
{
public:
    void run();
};

void Solver580A::run()
{
    int nDays;
    cin >> nDays;
    int prevM = 0;
    int maxStreak = 0;
    int curStreak = 0;
    for (int i = 0; i < nDays; ++i)
    {
        int currM;
        cin >> currM;

        if (currM >= prevM)
        {
            curStreak++;
            maxStreak = max(maxStreak, curStreak);
        }
        else
            curStreak = 1;

        prevM = currM;
    }

    cout << maxStreak;
}

class Solver580ATest : public ProblemTest {};

TEST_F(Solver580ATest, Example1)
{
    setInput("6\n2 2 1 3 4 1");
    Solver580A().run();
    EXPECT_EQ("3", getOutput());
}

TEST_F(Solver580ATest, Example2)
{
    setInput("3\n2 2 9");
    Solver580A().run();
    EXPECT_EQ("3", getOutput());
}