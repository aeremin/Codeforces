#include <Solvers/pch.h>
#include "algo/numbertheory/Primes.hpp"
#include "algo/io/printvector.h"

using namespace std;

class Solver576A
{
public:
    void run();
};

void Solver576A::run()
{
    int n;
    cin >> n;
    auto primes = generatePrimesUntil(n);
    vector<int> ans;
    for (auto p : primes)
        for (int pp = p; pp <= n; pp *= p)
            ans.push_back(pp);

    cout << ans.size() << "\n";
    printVector(ans);
}

class Solver576ATest : public ProblemTest {};

TEST_F(Solver576ATest, Example1)
{
    string input = R"(4
)";
    string output = R"(3
2 4 3)";
    setInput(input);
    Solver576A().run();
    EXPECT_EQ(output, getOutput());
}


TEST_F(Solver576ATest, Example2)
{
    string input = R"(6
)";
    string output = R"(4
2 4 3 5)";
    setInput(input);
    Solver576A().run();
    EXPECT_EQ(output, getOutput());
}


