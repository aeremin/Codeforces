#include "Solvers/pch.h"
#include "Solver581C.h"


void Solver581C::run()
{
    int64_t nSkills, levelUps;
    cin >> nSkills >> levelUps;

    std::vector<int64_t> skills(nSkills);
    for (auto& s : skills)
        cin >> s;

    auto totalSkills = std::accumulate(begin(skills), end(skills), 0ll);
    auto maxTotalSkills = 100 * nSkills;
    bool canMaxLevel = totalSkills + levelUps >= maxTotalSkills;
    if (canMaxLevel)
    {
        cout << 10 * nSkills;
        return;
    }

    std::vector<int64_t> buckets(10, 0);
    int64_t result = 0;
    for (auto& s : skills)
    {
        buckets[s % 10]++;
        result += s / 10;
    }


    int toLevelUp = 9;
    while (levelUps > 0 && toLevelUp >= 1)
    {
        int64_t canSpend = (10 - toLevelUp) * buckets[toLevelUp];
        if (levelUps >= canSpend)
        {
            levelUps -= canSpend;
            result += buckets[toLevelUp];
            toLevelUp--;
        }
        else
        {
            result += levelUps / (10 - toLevelUp);
            levelUps = 0;
        }
    }

    result += levelUps / 10;

    cout << result;
}

class Solver581CTest : public ProblemTest {};

TEST_F(Solver581CTest, Example1)
{
    setInput("2 4   7 9");
    Solver581C().run();
    EXPECT_EQ("2", getOutput());
}

TEST_F(Solver581CTest, Example2)
{
    setInput("3 8        17 15 19");
    Solver581C().run();
    EXPECT_EQ("5", getOutput());
}

TEST_F(Solver581CTest, Example3)
{
    setInput("2 2        99 100");
    Solver581C().run();
    EXPECT_EQ("20", getOutput());
}
