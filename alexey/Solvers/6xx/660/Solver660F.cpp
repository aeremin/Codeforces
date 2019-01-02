#include <Solvers/pch.h>
#include "algo/io/baseio.hpp"
#include "iter/range.h"
#include "algo/io/readvector.hpp"
#include "algo/geometry/linear_functions_max.h"
#include "util/relax.h"
using namespace std;

// Solution for Codeforces problem http://codeforces.com/contest/660/problem/F
class Solver660F
{
public:
    void run();
};

void Solver660F::run()
{
    int n; cin >> n;
    auto s = readVector<int64_t>(n);
    vector<int64_t> h(n + 1), g(n + 1), f(n + 1);
    for (int i : range(1, n + 1)) {
        h[i] = h[i - 1] - s[i - 1];
        g[i] = g[i - 1] + i * s[i - 1];
    }

    for (int i : range(n + 1))
        f[i] = -g[i] - i * h[i];

    LinearFunctionsMaximum<int64_t> maxim;
    int64_t ans = 0;
    for (int l = n; l >= 0; --l) {
        maxim.add_function(h[l], g[l]);
        auto v = f[l] + maxim.get_value(l);
        relax_max(ans, v);
    }

    cout << ans;
}

class Solver660FTest : public ProblemTest {};

TEST_F(Solver660FTest, Example1)
{
    string input = R"(6
5 -1000 1 -3 7 -8
)";
    string output = R"(16
)";
    setInput(input);
    Solver660F().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}


TEST_F(Solver660FTest, Example2)
{
    string input = R"(5
1000 1000 1001 1000 1000
)";
    string output = R"(15003
)";
    setInput(input);
    Solver660F().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}

TEST_F(Solver660FTest, Example3) {
    string input = R"(3
-60 -70 -80
)";
    string output = R"(0
)";
    setInput(input);
    Solver660F().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}




