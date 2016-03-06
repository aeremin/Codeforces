#include <Solvers/pch.h>
#include "algo/io/baseio.hpp"
#include "iter/range.h"
#include "algo/numbertheory/Residue.hpp"
using namespace std;

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

    vector<CodeforcesResidue64> factorials(h + w - 1);
    factorials[0] = 1;
    for (int i : range(1, h + w - 1))
        factorials[i] = factorials[i - 1] * int64_t(i);

    auto maxDim = max(h, w);
    vector<CodeforcesResidue64> invertedFactorials(maxDim);
    invertedFactorials[maxDim - 1] = factorials[maxDim - 1].inversed();
    for (int i = maxDim - 2; i >= 0; --i)
        invertedFactorials[i] = invertedFactorials[i + 1] * int64_t(i + 1);

    vector<CodeforcesResidue64> dp(blacks.size() + 1);
    dp[0] = 0;
    for (int i : range<int>(1, blacks.size() + 1)) {
        auto yOffs = blacks[i - 1].first - 1;
        auto xOffs = blacks[i - 1].second - 1;
        dp[i] = factorials[xOffs + yOffs] * invertedFactorials[xOffs] * invertedFactorials[yOffs];
        for (int j : range(i - 1)) {
            auto yOffsPrev = blacks[j].first - 1;
            auto xOffsPrev = blacks[j].second - 1;
            if (xOffsPrev <= xOffs && yOffsPrev <= yOffs)
                dp[i] -= dp[j + 1] * factorials[xOffs + yOffs - xOffsPrev - yOffsPrev] * invertedFactorials[xOffs - xOffsPrev] * invertedFactorials[yOffs - yOffsPrev];
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
    EXPECT_EQ(output, getOutput());
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
    EXPECT_EQ(output, getOutput());
}


