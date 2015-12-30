#include <Solvers/pch.h>

using namespace std;

class Solver613A
{
public:
    void run();
};

void Solver613A::run()
{

}

class Solver613ATest : public ProblemTest
{
};

TEST_F( Solver613ATest, Example1 )
{
    setInput("");
    Solver613A().run();
    EXPECT_EQ("", getOutput());
}

TEST_F( Solver613ATest, Example2 )
{
    setInput("");
    Solver613A().run();
    EXPECT_EQ("", getOutput());
}