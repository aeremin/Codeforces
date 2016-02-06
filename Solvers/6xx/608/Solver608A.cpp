#include <Solvers/pch.h>
#include "algo/Relax.hpp"

using namespace std;

class Solver608A
{
public:
    void run();
};

void Solver608A::run()
{
    int nPeople, nFloors;
    cin >> nPeople >> nFloors;
    vector<int> lastOnFloor(nFloors + 1, 0);
    for (int i = 0; i < nPeople; ++i)
    {
        int f, t;
        cin >> f >> t;
        relaxMax(lastOnFloor[f], t);
    }

    int ans = 0;
    for (int i = nFloors; i > 0; --i)
    {
        relaxMax(ans, lastOnFloor[i]);
        relaxMax(ans, ans + 1);
    }

    cout << ans;
}

class Solver608ATest : public ProblemTest {};

TEST_F(Solver608ATest, Example1)
{
    string input = R"(3 7
2 1
3 8
5 2
)";
    string output = R"(11
)";
    output.pop_back();
    setInput(input);
    Solver608A().run();
    EXPECT_EQ(output, getOutput());
}


TEST_F(Solver608ATest, Example2)
{
    string input = R"(5 10
2 77
3 33
8 21
9 12
10 64
)";
    string output = R"(79
)";
    output.pop_back();
    setInput(input);
    Solver608A().run();
    EXPECT_EQ(output, getOutput());
}


