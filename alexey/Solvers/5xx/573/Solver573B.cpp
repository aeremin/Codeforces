#include <Solvers/pch.h>
#include "algo/io/baseio.hpp"
#include "algo/io/readvector.hpp"
#include "iter/range.h"
#include "util/relax.h"
using namespace std;

class Solver573B
{
public:
    void run();
};

void Solver573B::run()
{
    int n = read<int>();
    auto h = readVector<int>(n);
    vector<int> maxL(n), maxR(n);

    maxL[0] = 1;
    for (int i = 1; i < n; ++i)
        maxL[i] = min(h[i], maxL[i - 1] + 1);

    maxR[n - 1] = 1;
    for (int i = n - 2; i >= 0; --i)
        maxR[i] = min(h[i], maxR[i + 1] + 1);

    int ans = 0;
    for (int i = 0; i < n; ++i)
        relax_max(ans, min(maxL[i], maxR[i]));

    cout << ans;
}

class Solver573BTest : public ProblemTest {};

TEST_F(Solver573BTest, Example1)
{
    string input = R"(6
2 1 4 6 2 2
)";
    string output = R"(3
)";
    output.pop_back();
    setInput(input);
    Solver573B().run();
    EXPECT_EQ(output, getOutput());
}


TEST_F(Solver573BTest, Example2)
{
    string input = R"(7
3 3 3 1 3 3 3
)";
    string output = R"(2
)";
    output.pop_back();
    setInput(input);
    Solver573B().run();
    EXPECT_EQ(output, getOutput());
}


