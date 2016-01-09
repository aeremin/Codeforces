#include <Solvers/pch.h>
#include "algo/Relax.hpp"
#include "algo/GreatestCommonDivisor.hpp"

using namespace std;

class Solver582C
{
public:
    void run();
};

void Solver582C::run()
{
    int64_t n;
    cin >> n;
    valarray<int64_t> numbers(n);
    for (auto& elt : numbers)
        cin >> elt;

    if (n == 1)
    {
        cout << 0;
        return;
    }
    
    vector<int64_t> divisorsOfN;
    for (int64_t d = 1; d * d <= n; ++d)
        if (n % d == 0)
        {
            divisorsOfN.push_back(d);
            if (n / d > d && d != 1)
                divisorsOfN.push_back(n / d);
        }

    int64_t ans = 0;
    for (auto& d : divisorsOfN)
    {
        vector<int64_t> maximums(d);
        for (int64_t i = 0; i < d; ++i)
            maximums[i] = valarray<int64_t>(numbers[slice(i, n / d, d)]).max();

        vector<int64_t> consequentMaximumsLengths;
        bool onConsequentMaximum = false;
        for (int64_t i = 0; i < n; ++i)
        {
            if (numbers[i] == maximums[i % d])
            {
                if (onConsequentMaximum)
                    ++consequentMaximumsLengths.back();
                else
                {
                    consequentMaximumsLengths.push_back(1);
                    onConsequentMaximum = true;
                }
            }
            else
                onConsequentMaximum = false;
        }

        if (onConsequentMaximum && numbers[0] == maximums[0] && consequentMaximumsLengths.size() > 1)
        {
            consequentMaximumsLengths.front() += consequentMaximumsLengths.back();
            consequentMaximumsLengths.pop_back();
        }

        for (auto l : consequentMaximumsLengths)
            for (int64_t multiplier = 1; d * multiplier <= l; ++multiplier)
            {
                if (greatestCommonDivisor(n / d, multiplier) > 1)
                    continue;
                if (l == n)
                    ans += l;
                else
                    ans += l - d * multiplier + 1;
            }
    }

    cout << ans;
}

class Solver582CTest : public ProblemTest
{
};

TEST_F( Solver582CTest, Example1 )
{
    setInput("4        7 1 2 3");
    Solver582C().run();
    EXPECT_EQ("2", getOutput());
}

TEST_F( Solver582CTest, Example2 )
{
    setInput("2        2 1");
    Solver582C().run();
    EXPECT_EQ("1", getOutput());
}

TEST_F(Solver582CTest, Example3)
{
    setInput("3        1 1 1");
    Solver582C().run();
    EXPECT_EQ("6", getOutput());
}

TEST_F(Solver582CTest, ExampleSingleElement)
{
    setInput("1        5");
    Solver582C().run();
    EXPECT_EQ("0", getOutput());
}

TEST_F(Solver582CTest, ExamplePrimeN)
{
    setInput("7        1 1 0 1 0 1 1");
    Solver582C().run();
    EXPECT_EQ("11", getOutput());
}

TEST_F(Solver582CTest, ExampleNonPrimeN)
{
    setInput("4        1 1 1 1");
    Solver582C().run();
    EXPECT_EQ("12", getOutput());
}

TEST_F(Solver582CTest, ExampleNonPrimeN2)
{
    setInput("6        1 1 1 1 1 1");
    Solver582C().run();
    EXPECT_EQ("30", getOutput());
}
