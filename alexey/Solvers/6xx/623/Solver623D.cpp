#include <Solvers/pch.h>
#include "algo/io/readvector.hpp"

using namespace std;

// Solution for Codeforces problem http://codeforces.com/contest/623/problem/D
class Solver623D
{
public:
    void run();
};

void Solver623D::run()
{
    size_t n;
    cin >> n;
    auto probs = readVector<int>(n);
    
    vector<double> probabilitiesThatCatched(n, numeric_limits<double>::min());

    double ev = 1.0;

    const int iterations = 1e6;
    for (int i = 0; i < iterations; ++i)
    {
        int bestJ = -1;
        double bestRatio = 0.0;
        double bestNextProb;
        for (int j = 0; j < n; ++j)
        {
            auto currProb = probabilitiesThatCatched[j];
            auto nextProb = currProb + (1.0 - currProb) * double(probs[j]) / 100.0;
            if (nextProb / currProb > bestRatio)
            {
                bestRatio = nextProb / currProb;
                bestNextProb = nextProb;
                bestJ = j;
            }
        }
        probabilitiesThatCatched[bestJ] = bestNextProb;

        double probAllCatched = accumulate(begin(probabilitiesThatCatched), end(probabilitiesThatCatched), 1.0, multiplies<double>());
        ev += 1.0 - probAllCatched;
    }

    cout << setprecision(10) << fixed << ev;
}

class Solver623DTest : public ProblemTest {};

TEST_F(Solver623DTest, Example1)
{
    string input = R"(2
50 50
)";
    string output = R"(5.0000000000
)";
    setInput(input);
    Solver623D().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}


TEST_F(Solver623DTest, Example2)
{
    string input = R"(4
50 20 20 10
)";
    string output = R"(39.2846263444
)";
    setInput(input);
    Solver623D().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}


