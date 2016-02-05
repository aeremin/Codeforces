#include <Solvers/pch.h>

using namespace std;

class Solver624A
{
public:
    void run();
};

void Solver624A::run()
{
    double d, l, v1, v2;
    cin >> d >> l >> v1 >> v2;
    cout << setprecision(15) << fixed << (l - d) / (v1 + v2);
}

class Solver624ATest : public ProblemTest {};

TEST_F(Solver624ATest, Example1)
{
    string input = R"(2 6 2 2)";
    string output = R"(1.000000000000000)";
    setInput(input);
    Solver624A().run();
    EXPECT_EQ(output, getOutput());
}


TEST_F(Solver624ATest, Example2)
{
    string input = R"(1 9 1 2)";
    string output = R"(2.666666666666667)";
    setInput(input);
    Solver624A().run();
    EXPECT_EQ(output, getOutput());
}


