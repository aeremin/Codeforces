#include <Solvers/pch.h>

using namespace std;

class Solver616A
{
public:
    void run();
};

void Solver616A::run()
{
    string s1, s2;
    cin >> s1 >> s2;
    if (s2.length() > s1.length())
        s1 = string(s2.length() - s1.length(), '0') + s1;
    if (s1.length() > s2.length())
        s2 = string(s1.length() - s2.length(), '0') + s2;
    if (s1 < s2)
        cout << '<';
    else if (s1 > s2)
        cout << '>';
    else
        cout << '=';
}

class Solver616ATest : public ProblemTest
{};

TEST_F(Solver616ATest, Example1)
{
    setInput("9           10");
    Solver616A().run();
    EXPECT_EQ("<", getOutput());
}

TEST_F(Solver616ATest, Example2)
{
    setInput("11 10");
    Solver616A().run();
    EXPECT_EQ(">", getOutput());
}

TEST_F(Solver616ATest, Example3)
{
    setInput("00012345             12345");
    Solver616A().run();
    EXPECT_EQ("=", getOutput());
}

TEST_F(Solver616ATest, Example4)
{
    setInput("0123             111");
    Solver616A().run();
    EXPECT_EQ(">", getOutput());
}

TEST_F(Solver616ATest, Example5)
{
    setInput("0123             9");
    Solver616A().run();
    EXPECT_EQ(">", getOutput());
}
