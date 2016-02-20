#include <Solvers/pch.h>
#include "algo/io/baseio.hpp"
#include "algo/Range.hpp"
using namespace std;

class Solver626B
{
public:
    void run();
};

void Solver626B::run()
{
    auto n = read<int>();
    auto s = read<string>();
    int r = 0;
    int g = 0;
    int b = 0;
    for (auto c : s)
    {
        if (c == 'R')
            r++;
        if (c == 'G')
            g++;
        if (c == 'B')
            b++;
    }

    if      (r + g == 0)
        cout << "B";
    else if (r + b == 0)
        cout << "G";
    else if (g + b == 0)
        cout << "R";

    else if (r == 1 && g == 1 && b == 0)
        cout << "B";
    else if (r == 1 && g == 0 && b == 1)
        cout << "G";
    else if (r == 0 && g == 1 && b == 1)
        cout << "R";

    else if (r == 1 && g >= 2 && b == 0)
        cout << "BR";
    else if (r == 1 && g == 0 && b >= 2)
        cout << "GR";
    else if (r >= 2 && g == 1 && b == 0)
        cout << "BG";
    else if (r >= 2 && g == 0 && b == 1)
        cout << "BG";
    else if (r == 0 && g >= 2 && b == 1)
        cout << "BR";
    else if (r == 0 && g == 1 && b >= 2)
        cout << "GR";

    else 
        cout << "BGR";
}

class Solver626BTest : public ProblemTest {};

TEST_F(Solver626BTest, Example1)
{
    string input = R"(2
RB
)";
    string output = R"(G
)";
    output.pop_back();
    setInput(input);
    Solver626B().run();
    EXPECT_EQ(output, getOutput());
}


TEST_F(Solver626BTest, Example2)
{
    string input = R"(3
GRG
)";
    string output = R"(BR
)";
    output.pop_back();
    setInput(input);
    Solver626B().run();
    EXPECT_EQ(output, getOutput());
}


TEST_F(Solver626BTest, Example3)
{
    string input = R"(5
BBBBB
)";
    string output = R"(B
)";
    output.pop_back();
    setInput(input);
    Solver626B().run();
    EXPECT_EQ(output, getOutput());
}


TEST_F(Solver626BTest, Example4)
{
   string input = R"(3
RGB
)";
    string output = R"(BGR
)";
    output.pop_back();
    setInput(input);
    Solver626B().run();
    EXPECT_EQ(output, getOutput());
}

TEST_F(Solver626BTest, Example5)
{
    string input = R"(4
RGRG
)";
    string output = R"(BGR
)";
    output.pop_back();
    setInput(input);
    Solver626B().run();
    EXPECT_EQ(output, getOutput());
}

