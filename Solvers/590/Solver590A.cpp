#include "Solvers/pch.h"

class Solver590A
{
public:
	void run();
};

void Solver590A::run()
{
}

class Solver590ATest : public ProblemTest {};

TEST_F(Solver590ATest, Example1)
{
    setInput("5    4 1 2 5 3");
	Solver590A().run();
    EXPECT_EQ("2", getOutput());
}

TEST_F(Solver590ATest, Example2)
{
    setInput("4        4 1 3 2");
	Solver590A().run();
    EXPECT_EQ("2", getOutput());
}