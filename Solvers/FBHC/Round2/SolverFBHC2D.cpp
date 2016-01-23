#include <Solvers/pch.h>

using namespace std;

class SolverFBHC2D
{
public:
    void run();
    void runOneTest();
};

void SolverFBHC2D::run()
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

void SolverFBHC2D::runOneTest()
{

}

class SolverFBHC2DTest : public FBHCProblemTest
{
public:
    SolverFBHC2DTest() : FBHCProblemTest("Inputs\\FBHC\\Round2\\D\\") {}
};

TEST_F(SolverFBHC2DTest, Example )
{
    SolverFBHC2D().run();
}

