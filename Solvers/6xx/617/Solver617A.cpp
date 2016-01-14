#include <Solvers/pch.h>

using namespace std;

class SolverStub617A
{
public:
    void run();
};

void SolverStub617A::run()
{

}

class SolverStub617ATest : public ProblemTest
{
};

TEST_F( SolverStub617ATest, Example1 )
{
    setInput("");
    SolverStub617A().run();
    EXPECT_EQ("", getOutput());
}

TEST_F( SolverStub617ATest, Example2 )
{
    setInput("");
    SolverStub617A().run();
    EXPECT_EQ("", getOutput());
}