#include <Solvers/pch.h>

using namespace std;

class Solver621D
{
public:
    void run();
};

void Solver621D::run()
{

}

class Solver621DTest : public ProblemTest {};

TEST_F(Solver621DTest, Example1)
{
    string input = R"(1.1 3.4 2.5
)";
    string output = R"(z^y^x
)";
    output.pop_back();
    setInput(input);
    Solver621D().run();
    EXPECT_EQ(output, getOutput());
}


TEST_F(Solver621DTest, Example2)
{
    string input = R"(2.0 2.0 2.0
)";
    string output = R"(x^y^z
)";
    output.pop_back();
    setInput(input);
    Solver621D().run();
    EXPECT_EQ(output, getOutput());
}


TEST_F(Solver621DTest, Example3)
{
    string input = R"(1.9 1.8 1.7
)";
    string output = R"((x^y)^z
)";
    output.pop_back();
    setInput(input);
    Solver621D().run();
    EXPECT_EQ(output, getOutput());
}


