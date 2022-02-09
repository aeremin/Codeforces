#include <Solvers/pch.h>
#include "algo/io/baseio.h"
#include "iter/range.h"
#include "algo/io/readvector.h"
#include "algo/number_theory/greatest_common_divisor.h"
#include "algo/io/printvector.h"
using namespace std;

// Solution for Codeforces problem http://codeforces.com/contest/660/problem/A
class Solver660A
{
public:
    void run();
};

void Solver660A::run()
{
    int n = read<int>();
    auto d = readVector<int>(n);
    vector<int> ans;
    for (int i : range(n - 1)) {
        ans.push_back(d[i]);
        if (greatestCommonDivisor(d[i], d[i + 1]) > 1)
            ans.push_back(1);
    }
    ans.push_back(d.back());
    cout << ans.size() - n << endl;
    printVector(ans);
}

class Solver660ATest : public ProblemTest {};

TEST_F(Solver660ATest, Example1)
{
    string input = R"(3
2 7 28
)";
    string output = R"(1
2 7 1 28
)";
    setInput(input);
    Solver660A().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}


