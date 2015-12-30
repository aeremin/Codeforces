#include <Solvers/pch.h>

using namespace std;

class Solver613E
{
public:
    void run();
};

void Solver613E::run()
{

}

class Solver613ETest : public ProblemTest
{
};

TEST_F( Solver613ETest, Example1 )
{
    setInput("");
    Solver613E().run();
    EXPECT_EQ("", getOutput());
}

TEST_F( Solver613ETest, Example2 )
{
    setInput("");
    Solver613E().run();
    EXPECT_EQ("", getOutput());
}