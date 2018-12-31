#include <Solvers/pch.h>
#include "algo/io/baseio.hpp"
#include "iter/range.h"
using namespace std;

class Solver652A
{
public:
    void run();
};

void Solver652A::run()
{
    int h1, h2, a, b;
    cin >> h1 >> h2 >> a >> b;
    auto dayChange = 12 * a;
    auto nightChange = -12 * b;
    h1 -= 4 * a;
    auto diff = h2 - h1;
    if ( diff <= dayChange ) {
        cout << 0;
        return;
    }

    if ( dayChange + nightChange <= 0 ) {
        cout << -1;
        return;
    }

    cout << ( diff + nightChange - 1 ) / ( dayChange + nightChange );
}

class Solver652ATest : public ProblemTest {};

TEST_F(Solver652ATest, Example1)
{
    string input = R"(10 30
2 1
)";
    string output = R"(1
)";
    setInput(input);
    Solver652A().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}


TEST_F(Solver652ATest, Example2)
{
    string input = R"(10 13
1 1
)";
    string output = R"(0
)";
    setInput(input);
    Solver652A().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}


TEST_F(Solver652ATest, Example3)
{
    string input = R"(10 19
1 2
)";
    string output = R"(-1
)";
    setInput(input);
    Solver652A().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}


TEST_F(Solver652ATest, Example4)
{
    string input = R"(1 50
5 4
)";
    string output = R"(1
)";
    setInput(input);
    Solver652A().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}


