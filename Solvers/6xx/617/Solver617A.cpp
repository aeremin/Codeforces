#include <Solvers/pch.h>

using namespace std;

class Solver621A
{
public:
    void run();
};

void Solver621A::run()
{
    int n;
    cin >> n;
    cout << (n + 4) / 5;
}

class Solver621ATest : public ProblemTest
{
};

TEST_F( Solver621ATest, Example1 )
{
    setInput("5");
    Solver621A().run();
    EXPECT_EQ("1", getOutput());
}

TEST_F( Solver621ATest, Example2 )
{
    setInput("12");
    Solver621A().run();
    EXPECT_EQ("3", getOutput());
}