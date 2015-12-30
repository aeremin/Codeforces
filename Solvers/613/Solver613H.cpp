#include <Solvers/pch.h>

using namespace std;

class Solver613H
{
public:
    void run();
};

void Solver613H::run()
{

}

class Solver613HTest : public ProblemTest
{
};

TEST_F( Solver613HTest, Example1 )
{
    setInput("");
    Solver613H().run();
    EXPECT_EQ("", getOutput());
}

TEST_F( Solver613HTest, Example2 )
{
    setInput("");
    Solver613H().run();
    EXPECT_EQ("", getOutput());
}