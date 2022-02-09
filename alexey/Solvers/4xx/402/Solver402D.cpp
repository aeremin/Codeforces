#include <Solvers/pch.h>
#include "algo/number_theory/greatest_common_divisor.h"
#include "algo/number_theory/primes.h"

using namespace std;

// Solution for Codeforces problem http://codeforces.com/contest/402/problem/D
class Solver402D
{
public:
    void run();

    unordered_set<int> badPrimes;

    int f(int n)
    {
        auto primeDecomposition = decomposeToPrimePowers(n);
        int res = 0;
        for (auto p : primeDecomposition)
            if (badPrimes.count(p.first))
                res -= p.second;
            else
                res += p.second;
        return res;
    }
};

void Solver402D::run()
{
    int nNumbers, nBadPrimes;
    cin >> nNumbers >> nBadPrimes;
    vector<int> numbers(nNumbers);
    for (auto& n : numbers)
        cin >> n;

    for (int i = 0; i < nBadPrimes; ++i)
    {
        int p;
        cin >> p;
        badPrimes.insert(p);
    }

    vector<int> gcds = { numbers[0] };
    for (int i = 1; i < nNumbers; ++i)
        gcds.push_back(greatestCommonDivisor(gcds.back(), numbers[i]));

    vector<int> fgcds = { f(numbers[0]) };
    for (int i = 1; i < nNumbers; ++i)
        fgcds.push_back(fgcds.back() - f(gcds[i - 1] / gcds[i]));

    int ans = 0;
    int substractedF = 0;
    for (int i = nNumbers - 1; i >= 0; --i)
    {
        int currF = fgcds[i] - substractedF;
        if (currF < 0)
            substractedF += currF;
        ans += f(numbers[i]) - substractedF;
    }

    cout << ans;
}

class Solver402DTest : public ProblemTest
{
};

TEST_F( Solver402DTest, Example1 )
{
    setInput("5 2        4 20 34 10 10        2 5");
    Solver402D().run();
    EXPECT_EQ("-2", getOutput());
}

TEST_F( Solver402DTest, Example2 )
{
    setInput("4 5        2 4 8 16        3 5 7 11 17");
    Solver402D().run();
    EXPECT_EQ("10", getOutput());
}
