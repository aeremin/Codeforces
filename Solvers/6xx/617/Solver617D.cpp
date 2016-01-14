#include <Solvers/pch.h>

using namespace std;

class SolverStub617D
{
public:
    void run();
};

void SolverStub617D::run()
{

}

class SolverStub617DTest : public ProblemTest
{
};

TEST_F( SolverStub617DTest, Example1 )
{
    setInput("");
    SolverStub617D().run();
    EXPECT_EQ("", getOutput());
}

TEST_F( SolverStub617DTest, Example2 )
{
    setInput("");
    SolverStub617D().run();
    EXPECT_EQ("", getOutput());
}