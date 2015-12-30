#include <Solvers/pch.h>

using namespace std;

class Solver613B
{
public:
    void run();
};

void Solver613B::run()
{

}

class Solver613BTest : public ProblemTest
{
};

TEST_F( Solver613BTest, Example1 )
{
    setInput("");
    Solver613B().run();
    EXPECT_EQ("", getOutput());
}

TEST_F( Solver613BTest, Example2 )
{
    setInput("");
    Solver613B().run();
    EXPECT_EQ("", getOutput());
}