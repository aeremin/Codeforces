#include <Solvers/pch.h>
#include "algo/io/baseio.hpp"
#include "iter/range.h"
#include "algo/io/readvector.hpp"
using namespace std;

class Solver604B
{
public:
    void run();
};

void Solver604B::run()
{
    auto n = read<int>();
    auto k = read<int>();
    auto bellsizes = readVector<int>(n);

    int l = 0;
    int r = 2 * bellsizes.back();
    while (r - l > 1)
    {
        auto c = (r + l) / 2;
        int il = 0;
        int ir = bellsizes.size() - 1;
        bool can = false;
        for (int i = 0; i < k; ++i)
        {
            if (bellsizes[il] + bellsizes[ir] <= c)
                ++il;
            if (bellsizes[ir] <= c)
                --ir;
            if (il > ir)
            {
                can = true;
                break;
            }
        }

        if (can) r = c; else l = c;
    }
    cout << r;
}

class Solver604BTest : public ProblemTest {};

TEST_F(Solver604BTest, Example1)
{
    string input = R"(2 1
2 5
)";
    string output = R"(7
)";
    output.pop_back();
    setInput(input);
    Solver604B().run();
    EXPECT_EQ(output, getOutput());
}


TEST_F(Solver604BTest, Example2)
{
    string input = R"(4 3
2 3 5 9
)";
    string output = R"(9
)";
    output.pop_back();
    setInput(input);
    Solver604B().run();
    EXPECT_EQ(output, getOutput());
}


TEST_F(Solver604BTest, Example3)
{
    string input = R"(3 2
3 5 7
)";
    string output = R"(8
)";
    output.pop_back();
    setInput(input);
    Solver604B().run();
    EXPECT_EQ(output, getOutput());
}


