#include <Solvers/pch.h>
#include "algo/numbertheory/Primes.hpp"

using namespace std;

// Solution for Codeforces problem http://codeforces.com/contest/566/problem/F
class Solver566F
{
public:
    void run();

    const int maxNumber = 1000000;
    const vector<uint64_t> primes = generatePrimesUntil(maxNumber);
    vector<vector<uint64_t>> primeDivisors = vector<vector<uint64_t>>(maxNumber + 1);
    vector<int> maxChain = vector<int>(maxNumber + 1, 0);

    void cachePrimeDivisors()
    {
        for (auto& p : primes)
            for (auto multiplier = 1; multiplier <= maxNumber / p; ++multiplier)
                primeDivisors[p * multiplier].push_back(p);
    }

    void processNumber(int num, bool isInSet)
    {
        int counts = isInSet ? 1 : 0;
        maxChain[num] = counts + maxChain[1];
        for (auto& p : primeDivisors[num])
            maxChain[num] = max(maxChain[num], maxChain[num / p] + counts);
    }
};

void Solver566F::run()
{
    cachePrimeDivisors();

    int nNumbers;
    cin >> nNumbers;

    int prevNumber;
    cin >> prevNumber;
    for (int i = 1; i < nNumbers; ++i)
    {
        int nextNumber;
        cin >> nextNumber;
        for (int j = prevNumber; j < nextNumber; ++j)
            processNumber(j, j == prevNumber);
        prevNumber = nextNumber;
    }

    processNumber(prevNumber, true);

    cout << *max_element(begin(maxChain), begin(maxChain) + prevNumber + 1);
}

class Solver566FTest : public ProblemTest
{
};

TEST_F( Solver566FTest, Example1 )
{
    setInput("8        3 4 6 8 10 18 21 24");
    Solver566F().run();
    EXPECT_EQ("3", getOutput());
}

TEST_F(Solver566FTest, Example2)
{
    setInput("5        250000 333333 500000 666666 1000000");
    Solver566F().run();
    EXPECT_EQ("3", getOutput());
}


