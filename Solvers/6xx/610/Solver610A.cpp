#include <Solvers/pch.h>

using namespace std;

class Solver610A
{
public:
    void run();
};

void Solver610A::run()
{
	int len;
	cin >> len;
	if (len % 2 == 1)
		cout << 0;
	else if (len % 4 == 0)
		cout << (len / 4 - 1);
	else
		cout << (len / 4);
}

class Solver610ATest : public ProblemTest {};

TEST_F(Solver610ATest, Example1)
{
    string input = R"(6
)";
    string output = R"(1
)";
    output.pop_back();
    setInput(input);
    Solver610A().run();
    EXPECT_EQ(output, getOutput());
}


TEST_F(Solver610ATest, Example2)
{
    string input = R"(20
)";
    string output = R"(4
)";
    output.pop_back();
    setInput(input);
    Solver610A().run();
    EXPECT_EQ(output, getOutput());
}


