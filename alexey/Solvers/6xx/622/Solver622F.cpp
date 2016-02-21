#include <Solvers/pch.h>
#include "algo/numbertheory/Residue.hpp"
#include "math/quick_power.h"

using namespace std;

class Solver622F
{
public:
    void run();

    CodeforcesResidue64 res(int n, int k)
    {
        vector<CodeforcesResidue64> factorials = { 1 };
        for (int64_t i = 1; i <= k + 1; ++i)
            factorials.push_back(factorials.back() * i);

        vector<CodeforcesResidue64> inversedFactorials;
        for (auto f : factorials)
            inversedFactorials.push_back(f.inversed());

        vector<CodeforcesResidue64> values = { 0 };
        for (int64_t i = 1; i <= k + 1; ++i)
            values.push_back(values.back() + quick_power(CodeforcesResidue64(i), k));

        if (n <= k + 1)
            return values[n];

        CodeforcesResidue64 ans = 0;

        CodeforcesResidue64 numerator = 1;
        for (int64_t i = 0; i <= k + 1; ++i)
            numerator *= (n - i);

        for (int64_t i = 0; i <= k + 1; ++i)
        {
            int64_t sign = (k + 1 - i) % 2 == 0 ? 1 : -1;
            ans += numerator * CodeforcesResidue64(n - i).inversed() * inversedFactorials[i] * inversedFactorials[k + 1 - i] * sign * values[i];
        }
        return ans;
    }
};

void Solver622F::run()
{
    int n, k;
    cin >> n >> k;
    cout << res(n, k);
}

class Solver622FTest : public ProblemTest {};

TEST_F(Solver622FTest, Example1)
{
    string input = R"(4 1
)";
    string output = R"(10
)";
    output.pop_back();
    setInput(input);
    Solver622F().run();
    EXPECT_EQ(output, getOutput());
}


TEST_F(Solver622FTest, Example2)
{
    string input = R"(4 2
)";
    string output = R"(30
)";
    output.pop_back();
    setInput(input);
    Solver622F().run();
    EXPECT_EQ(output, getOutput());
}


TEST_F(Solver622FTest, Example3)
{
    string input = R"(4 3
)";
    string output = R"(100
)";
    output.pop_back();
    setInput(input);
    Solver622F().run();
    EXPECT_EQ(output, getOutput());
}


TEST_F(Solver622FTest, Example4)
{
    string input = R"(4 0
)";
    string output = R"(4
)";
    output.pop_back();
    setInput(input);
    Solver622F().run();
    EXPECT_EQ(output, getOutput());
}


TEST_F(Solver622FTest, CompareWithBruteForce)
{
    for (int k = 0; k < 100; ++k)
    {
        CodeforcesResidue64 bruteForceAnswer = 0;
        for (int n = 1; n <= 100; ++n)
        {
            bruteForceAnswer += quick_power(CodeforcesResidue64(n), k);
            ASSERT_EQ(bruteForceAnswer, Solver622F().res(n, k)) << n << " " << k;
        }
    }
}


