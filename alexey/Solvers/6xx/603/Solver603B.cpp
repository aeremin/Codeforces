#include "Solvers/pch.h"
#include "Solver603B.h"

const int64_t cModulo = 1000000007;

int64_t minPow(int64_t p, int64_t k)
{
    auto l = k;
    int64_t ans = 1;
    while (l != 1)
    {
        l = (l * k) % p;
        ++ans;
    }
    return ans;
}

int64_t quick_power(int64_t a, int64_t d)
{
    int64_t ans = 1;
    while (d > 0)
    {
        if (d % 2 == 0)
        {
            a = (a * a) % cModulo;
            d /= 2;
        }
        else
        {
            ans = (ans * a) % cModulo;
            --d;
        }
    }
    return ans;
}

void Solver603B::run()
{
    int64_t p, k;
    cin >> p >> k;
    auto m = (k == 0) ? 1 : minPow(p, k);
    auto l = (p - 1) / m;
    if (k == 1) ++l;
    std::cout << quick_power(p, l);
}

class Solver603BTest : public ProblemTest {};

TEST_F(Solver603BTest, Example1)
{
    setInput("3 2");
    Solver603B().run();
    EXPECT_EQ("3", getOutput());
}

TEST_F(Solver603BTest, Example2)
{
    setInput("5 4");
    Solver603B().run();
    EXPECT_EQ("25", getOutput());
}

TEST_F(Solver603BTest, Example3)
{
    setInput("5 0");
    Solver603B().run();
    EXPECT_EQ("625", getOutput());
}

TEST_F(Solver603BTest, Example4)
{
    setInput("3 1");
    Solver603B().run();
    EXPECT_EQ("27", getOutput());
}
