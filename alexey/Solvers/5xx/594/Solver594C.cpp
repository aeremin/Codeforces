#include <Solvers/pch.h>
#include "algo/io/baseio.hpp"
#include "iter/range.h"
#include "util/relax.h"
using namespace std;

// Solution for Codeforces problem http://codeforces.com/contest/594/problem/C
class Solver594C
{
public:
    void run();

    int64_t minArea(int64_t x1, int64_t y1, int64_t x2, int64_t y2) const
    {
        auto dx = max<int64_t>(1, (x2 - x1 + 1) / 2);
        auto dy = max<int64_t>(1, (y2 - y1 + 1) / 2);
        return dx * dy;
    }
};

void Solver594C::run()
{
    auto n = read<int>();
    auto k = read<int>();
    vector<pair<int64_t, int>> x, y;
    for (int i : range(n))
    {
        auto x1 = read<int64_t>();
        auto y1 = read<int64_t>();
        auto x2 = read<int64_t>();
        auto y2 = read<int64_t>();
        x.emplace_back(x1 + x2, i);
        y.emplace_back(y1 + y2, i);
    }

    sort(begin(x), end(x));
    sort(begin(y), end(y));

    int64_t ans = minArea(x.front().first, y.front().first, x.back().first, y.back().first);
    for (int a : range(k + 1))
        for (int b : range(k + 1 - a))
            for (int c : range(k + 1))
                for (int d : range(k + 1 - c))
                {
                    unordered_set<int> del;
                    for (int i : range(a))
                        del.insert(x[i].second);
                    for (int i : range(b))
                        del.insert(x[n - 1 - i].second);
                    for (int i : range(c))
                        del.insert(y[i].second);
                    for (int i : range(d))
                        del.insert(y[n - 1 - i].second);
                    if (del.size() <= k)
                        relax_min(ans, minArea(x[a].first, y[c].first, x[n - 1 - b].first, y[n - 1 - d].first));
                }
    print(ans);
}

class Solver594CTest : public ProblemTest {};

TEST_F(Solver594CTest, Example1)
{
    string input = R"(3 1
1 1 2 2
2 2 3 3
3 3 4 4
)";
    string output = R"(1
)";
    setInput(input);
    Solver594C().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}


TEST_F(Solver594CTest, Example2)
{
    string input = R"(4 1
1 1 2 2
1 9 2 10
9 9 10 10
9 1 10 2
)";
    string output = R"(64
)";
    setInput(input);
    Solver594C().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}


TEST_F(Solver594CTest, Example3)
{
    string input = R"(3 0
1 1 2 2
1 1 1000000000 1000000000
1 3 8 12
)";
    string output = R"(249999999000000001
)";
    setInput(input);
    Solver594C().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}

