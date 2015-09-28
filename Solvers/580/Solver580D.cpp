#include "Solvers/pch.h"
#include "Solver580D.h"

static int64_t bitsSet(int64_t n)
{
    int64_t res = 0;
    while (n > 0)
    {
        res += n & 1;
        n /= 2;
    }
    return res;
}


void Solver580D::run()
{
    int64_t totalDishes, dishesToEat, nRules;
    cin >> totalDishes >> dishesToEat >> nRules;

    vector<int64_t> tastiness(totalDishes);
    for (auto& t : tastiness)
        cin >> t;

    vector<vector<int64_t>> rules(totalDishes, vector<int64_t>(totalDishes, 0));
    for (int64_t i = 0; i < nRules; ++i)
    {
        int64_t from, to, goodness;
        cin >> from >> to >> goodness;
        rules[from - 1][to - 1] = goodness;
    }
    
    std::vector<std::vector<int64_t>> masks(totalDishes + 1);
    int64_t maxMask = 1 << totalDishes;
    for (int64_t mask = 0; mask < maxMask; ++mask)
        masks[bitsSet(mask)].push_back(mask);

    std::vector<std::vector<int64_t>> dp(totalDishes, std::vector<int64_t>(maxMask, 0));
    
    for (int64_t currDishes = dishesToEat - 2; currDishes >= 0; --currDishes)
    {
        for (int64_t iDish = 0; iDish < totalDishes; ++iDish)
        {
            int64_t iDishMask = 1 << iDish;
            for (auto& m : masks[currDishes])
            {
                for (int64_t dishToAdd = 0; dishToAdd < totalDishes; ++dishToAdd)
                {
                    int64_t dishToAddMask = 1 << dishToAdd;
                    if ((m & iDishMask) == 0 && (iDish != dishToAdd) && (m & dishToAddMask) == 0)
                        if (dp[dishToAdd][m | iDishMask] + tastiness[dishToAdd] + rules[iDish][dishToAdd] > dp[iDish][m])
                            dp[iDish][m] = dp[dishToAdd][m | iDishMask] + tastiness[dishToAdd] + rules[iDish][dishToAdd];
                }
            }
        }
    }
    

    int64_t result = 0;
    for (int64_t iFirstDish = 0; iFirstDish < totalDishes; ++iFirstDish)
        result = max(result, dp[iFirstDish][0] + tastiness[iFirstDish]);

    cout << result;
}

class Solver580DTest : public ProblemTest {};

TEST_F(Solver580DTest, Example1)
{
    setInput("2 2 1        1 1        2 1 1");
    Solver580D().run();
    EXPECT_EQ("3", getOutput());
}

TEST_F(Solver580DTest, Example2)
{
    setInput(R"(4 3 2
        1 2 3 4
        2 1 5
        3 4 2)");
    Solver580D().run();
    EXPECT_EQ("12", getOutput());
}

TEST_F(Solver580DTest, Example2Simplified)
{
    setInput(R"(4 3 1
        1 2 3 4
        2 1 5)");
    Solver580D().run();
    EXPECT_EQ("12", getOutput());
}

TEST_F(Solver580DTest, Example3)
{
    setInput("2 2 0    100 0");
    Solver580D().run();
    EXPECT_EQ("100", getOutput());
}

TEST_F(Solver580DTest, Example4)
{
    setInput("2 1 0        15 14");
    Solver580D().run();
    EXPECT_EQ("15", getOutput());
}
