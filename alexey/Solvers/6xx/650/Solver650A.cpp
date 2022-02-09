#include <Solvers/pch.h>
#include "algo/io/baseio.h"
#include "iter/range.h"
using namespace std;

// Solution for Codeforces problem http://codeforces.com/contest/650/problem/A
class Solver650A
{
public:
    void run();
};

void Solver650A::run()
{
    int n;
    cin >> n;
    unordered_map<int, int64_t> x, y;
    map<pair<int, int>, int64_t> all;
    for (int i : range(n)) {
        int a, b;
        cin >> a >> b;
        x[a]++;
        y[b]++;
        all[{a, b}]++;
    }

    int64_t res = 0;
    for (auto p : x)
        res += p.second * (p.second - 1) / 2;

    for (auto p : y)
        res += p.second * (p.second - 1) / 2;

    for (auto p : all)
        res -= p.second * (p.second - 1) / 2;

    cout << res;
}


class Solver650ATest : public ProblemTest {};

TEST_F(Solver650ATest, Example1)
{
    string input = R"(3
1 1
7 5
1 5
)";
    string output = R"(2
)";
    output.pop_back();
    setInput(input);
    Solver650A().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}


TEST_F(Solver650ATest, Example2)
{
    string input = R"(6
0 0
0 1
0 2
-1 1
0 1
1 1
)";
    string output = R"(11
)";
    output.pop_back();
    setInput(input);
    Solver650A().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}


