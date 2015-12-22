#include "Solvers/pch.h"

class Solver590B
{
public:
	void run();
};

void Solver590B::run()
{
}

class Solver590BTest : public ProblemTest {};

TEST_F(Solver590BTest, Example1)
{
    setInput("5    4 1 2 5 3");
	Solver590B().run();
    EXPECT_EQ("2", getOutput());
}

TEST_F(Solver590BTest, Example2)
{
    setInput("4        4 1 3 2");
	Solver590B().run();
    EXPECT_EQ("2", getOutput());
}