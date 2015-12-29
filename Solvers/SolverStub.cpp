#include <Solvers/pch.h>

using namespace std;

class SolverStub
{
public:
    void run();
};

void SolverStub::run()
{

}

class SolverStubTest : public ProblemTest
{
};

TEST_F( SolverStubTest, Example1 )
{
    setInput("");
    SolverStub().run();
    EXPECT_EQ("", getOutput());
}

TEST_F( SolverStubTest, Example2 )
{
    setInput("");
    SolverStub().run();
    EXPECT_EQ("", getOutput());
}