#include <Solvers/pch.h>
#include "algo/io/readvector.h"
#include "algo/io/printvector.h"

using namespace std;

// Solution for Codeforces problem http://codeforces.com/contest/618/problem/B
class Solver618B
{
public:
    void run();
};

void Solver618B::run()
{
    int n;
    cin >> n;
    vector<vector<int>> a(n);
    for (auto& l : a)
        l = readVector<int>(n);

    vector<int> perm(n, -1);
    for (int val = 1; val <= n; ++val)
    {
        for (int i = 0; i < n; ++i)
        {
            if (perm[i] > 0) continue;
            bool findI = true;
            for (int j = 0; j < n; ++j)
            {
                if (i == j) continue;
                if (perm[j] > 0) continue;
                findI = findI && (a[i][j] == val);
            }
            if (findI)
            {
                perm[i] = val;
                break;
            }
        }
    }

    printVector(perm);
}

class Solver618BTest : public ProblemTest {};

TEST_F(Solver618BTest, Example1)
{
    setInput("2             0 1             1 0");
    Solver618B().run();
    EXPECT_EQ("1 2", getOutput());
}

TEST_F(Solver618BTest, Example2)
{
    setInput("5             0 2 2 1 2             2 0 4 1 3             2 4 0 1 3             1 1 1 0 1             2 3 3 1 0");
    Solver618B().run();
    EXPECT_EQ("2 4 5 1 3", getOutput());
}

