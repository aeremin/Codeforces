#include <Solvers/pch.h>
#include "algo/io/readvector.hpp"

using namespace std;

class Solver624B
{
public:
    void run();
};

void Solver624B::run()
{
    int n;
    cin >> n;
    auto maxAllowed = readVector<int>(n);
    sort(begin(maxAllowed), end(maxAllowed), greater<int>());
    int64_t totalLen = 0;
    int currAllowed = maxAllowed.front() + 1;
    for (auto elt : maxAllowed)
    {
        currAllowed = min(elt, currAllowed - 1);
        totalLen += max(0, currAllowed);
    }

    cout << totalLen;
}

class Solver624BTest : public ProblemTest {};

TEST_F(Solver624BTest, Example1)
{
    string input = R"(3
2 5 5
)";
    string output = R"(11
)";
    setInput(input);
    Solver624B().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}


TEST_F(Solver624BTest, Example2)
{
    string input = R"(3
1 1 2
)";
    string output = R"(3
)";
    setInput(input);
    Solver624B().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}

TEST_F(Solver624BTest, Example3)
{
    string input = R"(4
1 1 1 2
)";
    string output = R"(3
)";
    setInput(input);
    Solver624B().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}

