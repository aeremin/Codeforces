#include <Solvers/pch.h>

using namespace std;

class Solver613G
{
public:
    void run();
};

void Solver613G::run()
{

}

class Solver613GTest : public ProblemTest
{
};

TEST_F( Solver613GTest, Example1 )
{
    setInput("");
    Solver613G().run();
    EXPECT_EQ("", getOutput());
}

TEST_F( Solver613GTest, Example2 )
{
    setInput("");
    Solver613G().run();
    EXPECT_EQ("", getOutput());
}