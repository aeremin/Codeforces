#include <Solvers/pch.h>
#include "algo/io/readvector.hpp"

using namespace std;

// Solution for Codeforces problem http://codeforces.com/contest/606/problem/A
class Solver606A
{
public:
    void run();
};

void Solver606A::run()
{
    auto has = readVector<int>(3);
    auto need = readVector<int>(3);
    int balance = 0;
    for (int i = 0; i < 3; ++i)
    {
        auto diff = has[i] - need[i];
        balance += (diff > 0) ? diff / 2 : diff;
    }

    cout << ((balance >= 0) ? "Yes" : "No");
}

class Solver606ATest : public ProblemTest {};

TEST_F(Solver606ATest, Example1)
{
    string input = R"(4 4 0
2 1 2
)";
    string output = R"(Yes
)";
    setInput(input);
    Solver606A().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}


TEST_F(Solver606ATest, Example2)
{
    string input = R"(5 6 1
2 7 2
)";
    string output = R"(No
)";
    setInput(input);
    Solver606A().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}


TEST_F(Solver606ATest, Example3)
{
    string input = R"(3 3 3
2 2 2
)";
    string output = R"(Yes
)";
    setInput(input);
    Solver606A().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}


