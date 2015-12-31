#include "Solvers/pch.h"

using namespace std;

class Solver612A
{
public:
	void run();
};


void Solver612A::run()
{
	int n, p, q;
	cin >> n >> p >> q;
	string s;
	cin >> s;
	int a = -1, b = -1;
	for (int aa = 0; aa <= 100; ++aa)
		for (int bb = 0; bb <= 100; ++bb)
			if (aa * p + bb * q == n)
			{
				a = aa;
				b = bb;
			}
	
	if (a == -1)
	{
		cout << -1;
		return;
	}

	cout << a + b << endl;
	auto stringIter = s.begin();
	for (int i = 0; i < a; ++i)
	{
		for (int j = 0; j < p; ++j)
			cout << (*stringIter++);
		cout << endl;
	}

	for (int i = 0; i < b; ++i)
	{
		for (int j = 0; j < q; ++j)
			cout << (*stringIter++);
		cout << endl;
	}
}

class Solver612ATest : public ProblemTest {};

TEST_F(Solver612ATest, Example1)
{
	setInput("5 2 3		Hello");
	Solver612A().run();
	EXPECT_EQ("2\nHe\nllo\n", getOutput());
}

TEST_F(Solver612ATest, Example2)
{
	setInput("6 4 5		Privet");
	Solver612A().run();
	EXPECT_EQ("-1", getOutput());
}

TEST_F(Solver612ATest, Example3)
{
	setInput("8 1 1		abacabac");
	Solver612A().run();
	EXPECT_EQ("8\na\nb\na\nc\na\nb\na\nc\n", getOutput());
}