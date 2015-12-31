#include "Solvers/pch.h"

using namespace std;

class Solver587A
{
public:
	void run();
};


void Solver587A::run()
{
    vector<int> weightCounts(1000000 + 1 + 20);
    int nWeights;
    cin >> nWeights;
    for (int i = 0; i < nWeights; ++i)
    {
        int w;
        cin >> w;
        weightCounts[w]++;
    }

    int ans = 0;
    for (int i = 0; i < weightCounts.size(); ++i)
    {
        auto curW = weightCounts[i];
        ans += curW  % 2;
        if (curW > 1)
            weightCounts[i + 1] += weightCounts[i] / 2;
    }

    cout << ans;
}

class Solver587ATest : public ProblemTest {};

TEST_F(Solver587ATest, Example1)
{
    setInput("5        1 1 2 3 3");
    Solver587A().run();
	EXPECT_EQ("2", getOutput());
}

TEST_F(Solver587ATest, Example2)
{
    setInput("4        0 1 2 3");
    Solver587A().run();
	EXPECT_EQ("4", getOutput());
}