#include <Solvers/pch.h>
#include "algo/io/baseio.hpp"
#include "iter/range.h"
using namespace std;

class Solver645A
{
public:
    void run();
};

void Solver645A::run()
{
    string a, b, c, d;
    cin >> a >> b >> c >> d;
    auto x = a + b[1] + b[0];
    auto y = c + d[1] + d[0];
    x.erase(remove(begin(x), end(x), 'X'), end(x));
    y.erase(remove(begin(y), end(y), 'X'), end(y));
    bool can = false;
    for (int i : range(3)) {
        auto xRot = x.substr(i, string::npos) + x.substr(0, i);
        can = can || xRot == y;
    }
    if (can)
        cout << "YES";
    else
        cout << "NO";
}

class Solver645ATest : public ProblemTest {};

TEST_F(Solver645ATest, Example1)
{
    string input = R"(AB
XC
XB
AC
)";
    string output = R"(YES
)";
    setInput(input);
    Solver645A().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}


TEST_F(Solver645ATest, Example2)
{
    string input = R"(AB
XC
AC
BX
)";
    string output = R"(NO
)";
    setInput(input);
    Solver645A().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}


