#include <Solvers/pch.h>
#include "algo/io/baseio.hpp"
#include "iter/range.h"
using namespace std;

// Solution for Codeforces problem http://codeforces.com/contest/631/problem/B
class Solver631B
{
public:
    void run();
};

void Solver631B::run()
{
    int n = read<int>();
    int m = read<int>();
    vector<pair<int, int>> rows(n, { 0, 0 }), columns(m, { 0, 0 });
    int q = read<int>();
    for (int i : range(q)) {
        int a, b, c;
        cin >> a >> b >> c;
        if (a == 1)
            rows[b - 1] = { c, i + 1 };
        else
            columns[b - 1] = { c, i + 1 };
    }

    for (int i : range(n)) {
        for (int j : range(m)) {
            auto c1 = rows[i];
            auto c2 = columns[j];
            if (c1.second > c2.second)
                cout << c1.first << " ";
            else
                cout << c2.first << " ";
        }
        cout << "\n";
    }
}

class Solver631BTest : public ProblemTest {};

TEST_F(Solver631BTest, Example1)
{
    string input = R"(3 3 3
1 1 3
2 2 1
1 2 2
)";
    string output = R"(3 1 3 
2 2 2 
0 1 0 
)";
    setInput(input);
    Solver631B().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}


TEST_F(Solver631BTest, Example2)
{
    string input = R"(5 3 5
1 1 1
1 3 1
1 5 1
2 1 1
2 3 1
)";
    string output = R"(1 1 1 
1 0 1 
1 1 1 
1 0 1 
1 1 1 
)";
    setInput(input);
    Solver631B().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}


