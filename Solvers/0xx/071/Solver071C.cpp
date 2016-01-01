#include <Solvers/pch.h>
#include "algo/Primes.hpp"

using namespace std;

class Solver071C
{
public:
    void run();
};

void Solver071C::run()
{
    size_t n;
    cin >> n;
    valarray<int> colors(n);
    for (auto& elt : colors) cin >> elt;
    auto primeDecomposition = decomposeToPrimePowers(n);
    for (auto& p : primeDecomposition)
    {
        auto prime = p.first;
        if (prime == 2)
        {
            if (p.second >= 2)
                prime = 4;
            else
                continue;
        }
        for (int i = 0; i < n / prime; ++i)
        {
            valarray<int> sliced = colors[slice(i, prime, n / prime)];
            if (sliced.sum() == sliced.size())
            {
                cout << "YES";
                return;
            }
        }
    }

    cout << "NO";
}

class Solver071CTest : public ProblemTest
{
};

TEST_F( Solver071CTest, Example1 )
{
    setInput("3        1 1 1");
    Solver071C().run();
    EXPECT_EQ("YES", getOutput());
}

TEST_F( Solver071CTest, Example2 )
{
    setInput("6        1 0 1 1 1 0");
    Solver071C().run();
    EXPECT_EQ("YES", getOutput());
}

TEST_F(Solver071CTest, Example3)
{
    setInput("6        1 0 0 1 0 1");
    Solver071C().run();
    EXPECT_EQ("NO", getOutput());
}