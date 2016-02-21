#include <Solvers/pch.h>

using namespace std;

class Solver617A
{
public:
    void run();
};

void Solver617A::run()
{
    int n;
    cin >> n;
    cout << (n + 4) / 5;
}

class Solver617ATest : public ProblemTest
{
};

TEST_F(Solver617ATest, Example1 )
{
    setInput("5");
    Solver617A().run();
    EXPECT_EQ("1", getOutput());
}

TEST_F(Solver617ATest, Example2 )
{
    setInput("12");
    Solver617A().run();
    EXPECT_EQ("3", getOutput());
}