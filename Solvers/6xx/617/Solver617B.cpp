#include <Solvers/pch.h>

using namespace std;

class SolverStub617B
{
public:
    void run();
};

void SolverStub617B::run()
{

}

class SolverStub617BTest : public ProblemTest
{
};

TEST_F( SolverStub617BTest, Example1 )
{
    setInput("");
    SolverStub617B().run();
    EXPECT_EQ("", getOutput());
}

TEST_F( SolverStub617BTest, Example2 )
{
    setInput("");
    SolverStub617B().run();
    EXPECT_EQ("", getOutput());
}