#include <Solvers/pch.h>
#include "algo/io/baseio.hpp"
#include "iter/range.h"
#include "algo/io/readvector.hpp"
#include "algo/io/printvector.h"
using namespace std;

// Solution for Codeforces problem http://codeforces.com/contest/632/problem/C
class Solver632C
{
public:
    void run();
};

void Solver632C::run()
{
    auto n = read<int>();
    auto words = readVector<string>(n);
    auto cmp = [](const string& a, const string& b) {
        return a + b < b + a;
    };

    sort(begin(words), end(words), cmp);
    printVector(words, "");
}

class Solver632CTest : public ProblemTest {};

TEST_F(Solver632CTest, Example1)
{
    string input = R"(4
abba
abacaba
bcd
er
)";
    string output = R"(abacabaabbabcder
)";
    output.pop_back();
    setInput(input);
    Solver632C().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}


TEST_F(Solver632CTest, Example2)
{
    string input = R"(5
x
xx
xxa
xxaa
xxaaa
)";
    string output = R"(xxaaaxxaaxxaxxx
)";
    output.pop_back();
    setInput(input);
    Solver632C().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}


TEST_F(Solver632CTest, Example3)
{
    string input = R"(3
c
cb
cba
)";
    string output = R"(cbacbc
)";
    output.pop_back();
    setInput(input);
    Solver632C().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}


