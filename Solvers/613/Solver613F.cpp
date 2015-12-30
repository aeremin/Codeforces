#include <Solvers/pch.h>

using namespace std;

class Solver613F
{
public:
    void run();
};

void Solver613F::run()
{

}

class Solver613FTest : public ProblemTest
{
};

TEST_F( Solver613FTest, Example1 )
{
    setInput("");
    Solver613F().run();
    EXPECT_EQ("", getOutput());
}

TEST_F( Solver613FTest, Example2 )
{
    setInput("");
    Solver613F().run();
    EXPECT_EQ("", getOutput());
}