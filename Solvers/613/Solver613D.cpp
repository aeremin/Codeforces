#include <Solvers/pch.h>

using namespace std;

class Solver613D
{
public:
    void run();
};

void Solver613D::run()
{

}

class Solver613DTest : public ProblemTest
{
};

TEST_F( Solver613DTest, Example1 )
{
    setInput("");
    Solver613D().run();
    EXPECT_EQ("", getOutput());
}

TEST_F( Solver613DTest, Example2 )
{
    setInput("");
    Solver613D().run();
    EXPECT_EQ("", getOutput());
}