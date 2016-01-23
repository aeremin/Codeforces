#include <Solvers/pch.h>
#include "algo/Relax.hpp"

using namespace std;

class SolverFBHC2B
{
public:
    void run();
    void runOneTest();
};

void SolverFBHC2B::run()
{
    int t;
    cin >> t;
    for (int i = 1; i <= t; ++i)
    {
        cout << "Case #" << i << ": ";
        runOneTest();
        if (i != t) cout << "\n";
    }
}

double probSum(double x, double y)
{
    return x + y - x * y;
}

void SolverFBHC2B::runOneTest()
{
    int nCoins, goal;
    double p;
    cin >> nCoins >> goal >> p;

    vector<vector<double>> probs(nCoins + 1, vector<double>(nCoins + 1, 0.0));
    probs[0][0] = 1.0;
    for (int a = 1; a <= nCoins; ++a)
    {
        probs[a][0] = (1 - p) * probs[a - 1][0];
        for (int b = 1; b <= a; ++b)
            probs[a][b] = p * probs[a - 1][b - 1] + (1 - p) * probs[a - 1][b];
    }

    vector<double> probsOfGoal(nCoins + 1);
    for (int i = 0; i <= nCoins; ++i)
        probsOfGoal[i] = accumulate(begin(probs[i]) + goal, end(probs[i]), 0.0);
    
    vector<double> bestEv(nCoins + 1, 0.0);
    for (int i = 1; i <= nCoins; ++i)
        for (int j = 1; j <= i; ++j)
            relaxMax(bestEv[i], bestEv[i - j] + probsOfGoal[j]);

    cout << setprecision(9) << fixed << bestEv.back();
}

class SolverFBHC2BTest : public FBHCProblemTest
{
public:
    SolverFBHC2BTest() : FBHCProblemTest("Inputs\\FBHC\\Round2\\B\\") {}
};

TEST_F(SolverFBHC2BTest, Example )
{
    SolverFBHC2B().run();
}

