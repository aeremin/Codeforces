#include <Solvers/pch.h>
#include "algo/io/baseio.hpp"
#include "iter/range.h"
#include "algo/io/readvector.hpp"
using namespace std;

class Solver567A
{
public:
    void run();
};

void Solver567A::run()
{
    int n = read<int>();
    auto pos = readVector<int>(n);
    for (int i : range(n)) {
        int m;
        if (i > 0 && i < n - 1)
            m = min(pos[i] - pos[i - 1], pos[i + 1] - pos[i]);
        else if (i > 0)
            m = pos[i] - pos[i - 1];
        else
            m = pos[i + 1] - pos[i];
        auto M = max(pos[n - 1] - pos[i], pos[i] - pos[0]);
        cout << m << " " << M << "\n";
    }
}

class Solver567ATest : public ProblemTest {};

TEST_F(Solver567ATest, Example1)
{
    string input = R"(4
-5 -2 2 7
)";
    string output = R"(3 12
3 9
4 7
5 12
)";
    setInput(input);
    Solver567A().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}


TEST_F(Solver567ATest, Example2)
{
    string input = R"(2
-1 1
)";
    string output = R"(2 2
2 2
)";
    setInput(input);
    Solver567A().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}


