#include <Solvers/pch.h>
#include "algo/io/baseio.hpp"
#include "iter/range.h"
#include "algo/io/readvector.hpp"
using namespace std;

class Solver626D
{
public:
    void run();
};

void Solver626D::run()
{
    auto n = read<int>();
    auto scores = readVector<int>(n);
    sort(begin(scores), end(scores));
    vector<double> diffsDistr(scores.back(), 0.0);
    for (int i : range(n))
        for (int j : range(i))
            diffsDistr[scores[i] - scores[j]] += 1.0;
    vector<double> diffsDistrPS;
    partial_sum(begin(diffsDistr), end(diffsDistr), back_inserter(diffsDistrPS));
    double res = 0.0;
    double op = n * (n - 1) / 2;
    for (int i : range(diffsDistr.size()))
        for (int j : range(diffsDistr.size() - i))
            res += (diffsDistr[i] / op) * (diffsDistr[j] / op) * (1.0 - diffsDistrPS[i + j] / op);

    cout << setprecision(10) << fixed << res;
}

class Solver626DTest : public ProblemTest {};

TEST_F(Solver626DTest, Example1)
{
    string input = R"(2
1 2
)";
    string output = R"(0.0000000000
)";
    setInput(input);
    Solver626D().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}


TEST_F(Solver626DTest, Example2)
{
    string input = R"(3
1 2 10
)";
    string output = R"(0.0740740741
)";
    setInput(input);
    Solver626D().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}


