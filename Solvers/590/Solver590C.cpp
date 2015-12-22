#include "Solvers/pch.h"

class Solver590C
{
public:
	void run();
};

void Solver590C::run()
{
}

class Solver590CTest : public ProblemTest {};

TEST_F(Solver590CTest, Example1)
{
    setInput("5    4 1 2 5 3");
	Solver590C().run();
    EXPECT_EQ("2", getOutput());
}

TEST_F(Solver590CTest, Example2)
{
    setInput("4        4 1 3 2");
	Solver590C().run();
    EXPECT_EQ("2", getOutput());
}