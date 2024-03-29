#include <Solvers/pch.h>
#include "algo/number_theory/residue.h"
#include "math/quick_power.h"
#include "algo/number_theory/primes.h"

using namespace std;

// Solution for Codeforces problem http://codeforces.com/contest/615/problem/D
class Solver615D
{
public:
    void run();
};

void Solver615D::run()
{
    int nPrimes;
    cin >> nPrimes;
    unordered_map<int64_t, int64_t> primesPowers;
    for (int i = 0; i < nPrimes; ++i)
    {
        int64_t p;
        cin >> p;
        ++primesPowers[p];
    }

    Residue<int64_t, cCodeforcesModulo - 1> divisorsCount = 1;
    CodeforcesResidue64 ans = 1;
    for (auto& p : primesPowers)
    {
        ans = quick_power(ans, p.second + 1);
        auto prod = quick_power<CodeforcesResidue64>(p.first, (p.second + 1) * p.second / 2);
        ans *= quick_power(prod, divisorsCount.rep());
        divisorsCount *= (p.second + 1);
    }

    cout << ans;
}

class Solver615DTest : public ProblemTest
{
};

TEST_F( Solver615DTest, Example1 )
{
    setInput("2        2 3");
    Solver615D().run();
    EXPECT_EQ("36", getOutput());
}

TEST_F( Solver615DTest, Example2 )
{
    setInput("3        2 3 2");
    Solver615D().run();
    EXPECT_EQ("1728", getOutput());
}

TEST_F(Solver615DTest, Example3)
{
    auto primes = generatePrimesUntil(200000);
    auto pow = 200000 / primes.size();
    auto input = to_string(primes.size() * pow);
    for (int i = 0; i < pow; ++i)
        for (auto p : primes)
            input.append(" " + to_string(p));
        
    setInput(input);
    Solver615D().run();
}