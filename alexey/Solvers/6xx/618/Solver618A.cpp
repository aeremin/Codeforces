#include <Solvers/pch.h>
#include "algo/io/printvector.h"

using namespace std;

// Solution for Codeforces problem http://codeforces.com/contest/618/problem/A
class Solver618A
{
public:
    void run();
};

void Solver618A::run()
{
    int n;
    cin >> n;
    vector<int> sizes = { 1 };
    for (int i = 1; i < n; ++i)
    {
        sizes.push_back(1);
        while (sizes.size() >= 2 && (sizes[sizes.size() - 1] == (sizes[sizes.size() - 2])))
        {
            sizes.pop_back();
            sizes.back()++;
        }
    }
    printVector(sizes);
}

class Solver618ATest : public ProblemTest {};

TEST_F(Solver618ATest, Example1)
{
    setInput("1");
    Solver618A().run();
    EXPECT_EQ("1", getOutput());
}

TEST_F(Solver618ATest, Example2)
{
    setInput("2");
    Solver618A().run();
    EXPECT_EQ("2", getOutput());
}

TEST_F(Solver618ATest, Example3)
{
    setInput("8");
    Solver618A().run();
    EXPECT_EQ("4", getOutput());
}
