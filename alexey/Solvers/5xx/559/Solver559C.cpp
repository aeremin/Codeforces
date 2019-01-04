#include <Solvers/pch.h>
#include "algo/io/baseio.hpp"
#include "iter/range.h"
#include "algo/numbertheory/Residue.hpp"
#include "algo/combinatorics/combinatorics_helper.h"
using namespace std;

// Solution for Codeforces problem http://codeforces.com/contest/559/problem/C
class Solver559C
{
public:
    void run();
};

void Solver559C::run()
{
    int h, w, n;
    cin >> h >> w >> n;
    vector<pair<int, int>> blacks(n);
    for (auto& elt : blacks)
        cin >> elt.first >> elt.second;

    blacks.push_back({ h, w });
    sort(begin(blacks), end(blacks));

    CombinatoricsHelper<int64_t, cCodeforcesModulo> helper{ h + w };

    vector<CodeforcesResidue64> dp(blacks.size() + 1);
    dp[0] = 0;
    for (int i : range<int>(1, blacks.size() + 1)) {
        auto yOffs = blacks[i - 1].first - 1;
        auto xOffs = blacks[i - 1].second - 1;
        dp[i] = helper.binomial_coefficient(xOffs + yOffs, xOffs);
        for (int j : range(i - 1)) {
            auto yOffsPrev = blacks[j].first - 1;
            auto xOffsPrev = blacks[j].second - 1;
            if (xOffsPrev <= xOffs && yOffsPrev <= yOffs)
                dp[i] -= dp[j + 1] * helper.binomial_coefficient(xOffs + yOffs - xOffsPrev - yOffsPrev, xOffs - xOffsPrev);
        }
    }

    cout << dp.back();
}

class Solver559CTest : public ProblemTest {};

TEST_F(Solver559CTest, Example1)
{
    string input = R"(3 4 2
2 2
2 3
)";
    string output = R"(2
)";
    output.pop_back();
    setInput(input);
    Solver559C().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}


TEST_F(Solver559CTest, Example2)
{
    string input = R"(100 100 3
15 16
16 15
99 88
)";
    string output = R"(545732279
)";
    output.pop_back();
    setInput(input);
    Solver559C().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}


