#include <Solvers/pch.h>

using namespace std;

class SolverFBHC2A
{
public:
    void run();
    void runOneTest();
};

void SolverFBHC2A::run()
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

void SolverFBHC2A::runOneTest()
{

}

class SolverFBHC2ATest : public FBHCProblemTest
{
public:
    SolverFBHC2ATest() : FBHCProblemTest("Inputs\\FBHC\\Round2\\A\\") {}
};

TEST_F(SolverFBHC2ATest, Example )
{
    SolverFBHC2A().run();
}

