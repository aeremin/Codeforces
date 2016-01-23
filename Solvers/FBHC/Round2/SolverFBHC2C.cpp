#include <Solvers/pch.h>

using namespace std;

class SolverFBHC2C
{
public:
    void run();
    void runOneTest();
};

void SolverFBHC2C::run()
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

void SolverFBHC2C::runOneTest()
{

}

class SolverFBHC2CTest : public FBHCProblemTest
{
public:
    SolverFBHC2CTest() : FBHCProblemTest("Inputs\\FBHC\\Round2\\C\\") {}
};

TEST_F(SolverFBHC2CTest, Example )
{
    SolverFBHC2C().run();
}

