#include <Solvers/pch.h>
#include "algo/io/baseio.hpp"
#include "iter/range.h"
using namespace std;

class Solver427A
{
public:
    void run();
};

void Solver427A::run()
{
    int n;
    cin >> n;
    int ans = 0;
    int freeGuys = 0;
    for (int i : range(n)) {
        int t;
        cin >> t;
        if (t > 0) freeGuys += t;
        if (t == -1) {
            if (freeGuys > 0) --freeGuys;
            else ++ans;
        }
    }

    cout << ans;
}

class Solver427ATest : public ProblemTest {};

TEST_F(Solver427ATest, Example1)
{
    string input = R"(3
-1 -1 1
)";
    string output = R"(2
)";
    output.pop_back();
    setInput(input);
    Solver427A().run();
    EXPECT_EQ(output, getOutput());
}


TEST_F(Solver427ATest, Example2)
{
    string input = R"(8
1 -1 1 -1 -1 1 1 1
)";
    string output = R"(1
)";
    output.pop_back();
    setInput(input);
    Solver427A().run();
    EXPECT_EQ(output, getOutput());
}


TEST_F(Solver427ATest, Example3)
{
    string input = R"(11
-1 -1 2 -1 -1 -1 -1 -1 -1 -1 -1
)";
    string output = R"(8
)";
    output.pop_back();
    setInput(input);
    Solver427A().run();
    EXPECT_EQ(output, getOutput());
}


