#include <Solvers/pch.h>
#include "algo/io/baseio.h"
#include "iter/range.h"
using namespace std;

// Solution for Codeforces problem http://codeforces.com/contest/630/problem/E
class Solver630E
{
public:
    void run();
};

void Solver630E::run()
{
    int64_t x1, y1, x2, y2;
    cin >> x1 >> y1 >> x2 >> y2;
    auto dx = (x2 - x1) / 2;
    auto dy = (y2 - y1) / 2;
    cout << dx * dy + (dx + 1) * (dy + 1);
}

class Solver630ETest : public ProblemTest {};

TEST_F(Solver630ETest, Example1)
{
    string input = R"(1 1 5 5
)";
    string output = R"(13)";
    setInput(input);
    Solver630E().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}


