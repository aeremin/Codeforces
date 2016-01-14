#include <Solvers/pch.h>

using namespace std;

class SolverStub617E
{
public:
    void run();
};

void SolverStub617E::run()
{

}

class SolverStub617ETest : public ProblemTest
{
};

TEST_F( SolverStub617ETest, Example1 )
{
    setInput("");
    SolverStub617E().run();
    EXPECT_EQ("", getOutput());
}

TEST_F( SolverStub617ETest, Example2 )
{
    setInput("");
    SolverStub617E().run();
    EXPECT_EQ("", getOutput());
}