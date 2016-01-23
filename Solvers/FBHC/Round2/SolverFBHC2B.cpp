#include <Solvers/pch.h>

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

void SolverFBHC2B::runOneTest()
{

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

