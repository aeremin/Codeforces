#include <Solvers/pch.h>

using namespace std;

class Solver613C
{
public:
    void run();
};

void Solver613C::run()
{

}

class Solver613CTest : public ProblemTest
{
};

TEST_F( Solver613CTest, Example1 )
{
    setInput("");
    Solver613C().run();
    EXPECT_EQ("", getOutput());
}

TEST_F( Solver613CTest, Example2 )
{
    setInput("");
    Solver613C().run();
    EXPECT_EQ("", getOutput());
}