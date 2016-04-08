#include <Solvers/pch.h>
#include "algo/io/baseio.hpp"
#include "iter/range.h"
#include "algo/io/readvector.hpp"
#include "algo/geometry/linear_functions_max.h"
#include "util/relax.h"
using namespace std;

class Solver319C
{
public:
    void run();
};

void Solver319C::run()
{
    int n = read<int>();
    auto heights = readVector<int64_t>(n);
    auto prices = readVector<int64_t>(n);
    vector<int64_t> minPrice(n, numeric_limits<int64_t>::max());
    minPrice.back() = 0;
    LinearFunctionsMaximum<int64_t> lfm;
    for (int i = n - 2; i >= 0; --i) {
        lfm.add_function(-heights[i + 1], - minPrice[i + 1]);
        minPrice[i] = -lfm.get_value(prices[i]);
    }

    cout << minPrice.front();
}

class Solver319CTest : public ProblemTest {};

TEST_F(Solver319CTest, Example1)
{
    string input = R"(5
1 2 3 4 5
5 4 3 2 0
)";
    string output = R"(25
)";
    output.pop_back();
    setInput(input);
    Solver319C().run();
    EXPECT_EQ(output, getOutput());
}


TEST_F(Solver319CTest, Example2)
{
    string input = R"(6
1 2 3 10 20 30
6 5 4 3 2 0
)";
    string output = R"(138
)";
    output.pop_back();
    setInput(input);
    Solver319C().run();
    EXPECT_EQ(output, getOutput());
}


