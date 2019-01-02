#include "Solvers/pch.h"

// Solution for Codeforces problem http://codeforces.com/contest/578/problem/B
class Solver578B
{
public:
    void run();
};

void Solver578B::run()
{
    uint64_t n, k, x;
    cin >> n >> k >> x;
    std::vector<uint64_t> nums(n);
    for (auto& a : nums)
        cin >> a;

    std::vector<uint64_t> timesBitSet(61, 0);
    for (auto i = 0; i < timesBitSet.size(); ++i)
    {
        uint64_t iMask = uint64_t(1) << i;
        for (auto a : nums)
            if (a & iMask) timesBitSet[i]++;
    }

    uint64_t bestGuess = 0;
    for (auto a : nums)
    {
        auto b = a;
        for (int pow = 0; pow < k; ++pow)
            b *= x;

        uint64_t currGuess = 0;
        for (auto i = 0; i < timesBitSet.size(); ++i)
        {
            uint64_t iMask = uint64_t(1) << i;
            int64_t timesCurrBitSet = int64_t( timesBitSet[i] )
                + ((b & iMask) > 0 ? 1 : 0)
                - ((a & iMask) > 0 ? 1 : 0);
            
            if (timesCurrBitSet > 0)
                currGuess |= iMask;
        }
        bestGuess = max(bestGuess, currGuess);
    }

    cout << bestGuess;
}

class Solver578BTest : public ProblemTest {};

TEST_F(Solver578BTest, Example1)
{
    setInput("3 1 2    1 1 1");
    Solver578B().run();
    EXPECT_EQ("3", getOutput());
}

TEST_F(Solver578BTest, Example2)
{
    setInput("4 2 3        1 2 4 8");
    Solver578B().run();
    EXPECT_EQ("79", getOutput());
}

TEST_F(Solver578BTest, Example3)
{
    setInput("1 10 8 1000000000");
    Solver578B().run();
    EXPECT_EQ("1073741824000000000", getOutput());
}