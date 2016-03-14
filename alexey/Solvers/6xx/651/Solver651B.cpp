#include <Solvers/pch.h>
#include "algo/io/baseio.hpp"
#include "iter/range.h"
#include "algo/io/readvector.hpp"
#include "util/relax.h"
using namespace std;

class Solver651B
{
public:
    void run();
};

void Solver651B::run()
{
    int n = read<int>();
    auto pics = readVector<int>(n);
    unordered_map<int, int> counts;
    int maxCount = 0;
    for (auto p : pics)
        relax_max(maxCount, ++counts[p]);
    
    cout << (n - maxCount);
}

class Solver651BTest : public ProblemTest {};

TEST_F(Solver651BTest, Example1)
{
    string input = R"(5
20 30 10 50 40
)";
    string output = R"(4
)";
    output.pop_back();
    setInput(input);
    Solver651B().run();
    EXPECT_EQ(output, getOutput());
}


TEST_F(Solver651BTest, Example2)
{
    string input = R"(4
200 100 100 200
)";
    string output = R"(2
)";
    output.pop_back();
    setInput(input);
    Solver651B().run();
    EXPECT_EQ(output, getOutput());
}


