#include <Solvers/pch.h>
#include "algo/io/baseio.hpp"
#include "iter/range.h"
using namespace std;

class Solver599D
{
public:
    void run();
};

void Solver599D::run()
{
    auto y = read<uint64_t>();
    vector<pair<uint64_t, uint64_t>> ans;
    for (uint64_t k = 1; k * k * k < 3 * y; ++k)
        if ((6 * y) % (k * (k + 1)) == 0)
        {
            auto d = (6 * y) / (k * (k + 1));
            int64_t threeX = d + 2 - 2 * k;
            if (threeX > 0 && threeX % 3 == 0)
                ans.emplace_back(k, k + threeX / 3 - 1);
        }

    for (int i = ans.size() - 1; i >= 0; --i)
        if (ans[i].first != ans[i].second)
            ans.push_back({ ans[i].second, ans[i].first });

    cout << ans.size() << "\n";
    
    for (auto elt : ans)
        cout << elt.first << " " << elt.second << "\n";
}

class Solver599DTest : public ProblemTest {};

TEST_F(Solver599DTest, Example1)
{
    string input = R"(26
)";
    string output = R"(6
1 26
2 9
3 5
5 3
9 2
26 1
)";
    setInput(input);
    Solver599D().run();
    EXPECT_EQ(output, getOutput());
}


TEST_F(Solver599DTest, Example2)
{
    string input = R"(2
)";
    string output = R"(2
1 2
2 1
)";
    setInput(input);
    Solver599D().run();
    EXPECT_EQ(output, getOutput());
}


TEST_F(Solver599DTest, Example3)
{
    string input = R"(8
)";
    string output = R"(4
1 8
2 3
3 2
8 1
)";
    setInput(input);
    Solver599D().run();
    EXPECT_EQ(output, getOutput());
}


