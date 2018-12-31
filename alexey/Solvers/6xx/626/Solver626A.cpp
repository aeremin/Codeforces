#include <Solvers/pch.h>
#include "algo/io/baseio.hpp"
#include "iter/range.h"
using namespace std;

class Solver626A
{
public:
    void run();
};

void Solver626A::run()
{
    auto n = read<int>();
    auto s = read<string>();
    map<pair<int, int>, int> count;
    int res = 0;
    pair<int, int> curr = { 0, 0 };
    count[curr]++;
    for (auto c : s)
    {
        if (c == 'L')
            curr.first--;
        if (c == 'R')
            curr.first++;
        if (c == 'D')
            curr.second--;
        if (c == 'U')
            curr.second++;
        res += count[curr];
        count[curr]++;
    }

    print(res);
}

class Solver626ATest : public ProblemTest {};

TEST_F(Solver626ATest, Example1)
{
    string input = R"(6
URLLDR
)";
    string output = R"(2
)";
    setInput(input);
    Solver626A().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}


TEST_F(Solver626ATest, Example2)
{
    string input = R"(4
DLUU
)";
    string output = R"(0
)";
    setInput(input);
    Solver626A().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}


TEST_F(Solver626ATest, Example3)
{
    string input = R"(7
RLRLRLR
)";
    string output = R"(12
)";
    setInput(input);
    Solver626A().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}


