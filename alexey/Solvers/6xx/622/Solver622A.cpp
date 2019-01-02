#include <Solvers/pch.h>
#include "algo/FunctorIterator.hpp"
#include "algo/io/baseio.hpp"

using namespace std;

// Solution for Codeforces problem http://codeforces.com/contest/622/problem/A
class Solver622A
{
public:
    void run();
};

void Solver622A::run()
{
    auto n = read<int64_t>();

    auto countAfterKParts = [](int64_t k)
    {
        return k * (k + 1) / 2;
    };

    auto l = makeFunctorIterator(int64_t(0), countAfterKParts);
    auto r = makeFunctorIterator(int64_t(1e9), countAfterKParts);
    auto countOfFullParts = lower_bound(l, r, n).getParameter() - 1;
    cout << n - countAfterKParts(countOfFullParts);
}

class Solver622ATest : public ProblemTest {};

TEST_F(Solver622ATest, Example1)
{
    string input = R"(3
)";
    string output = R"(2
)";
    setInput(input);
    Solver622A().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}


TEST_F(Solver622ATest, Example2)
{
    string input = R"(5
)";
    string output = R"(2
)";
    setInput(input);
    Solver622A().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}


TEST_F(Solver622ATest, Example3)
{
    string input = R"(10
)";
    string output = R"(4
)";
    setInput(input);
    Solver622A().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}


TEST_F(Solver622ATest, Example4)
{
    string input = R"(55
)";
    string output = R"(10
)";
    setInput(input);
    Solver622A().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}


TEST_F(Solver622ATest, Example5)
{
    string input = R"(56
)";
    string output = R"(1
)";
    setInput(input);
    Solver622A().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}


