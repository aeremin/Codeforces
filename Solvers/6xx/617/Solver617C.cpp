#include <Solvers/pch.h>

using namespace std;

class SolverStub617C
{
public:
    void run();
};

void SolverStub617C::run()
{

}

class SolverStub617CTest : public ProblemTest
{
};

TEST_F( SolverStub617CTest, Example1 )
{
    setInput("");
    SolverStub617C().run();
    EXPECT_EQ("", getOutput());
}

TEST_F( SolverStub617CTest, Example2 )
{
    setInput("");
    SolverStub617C().run();
    EXPECT_EQ("", getOutput());
}