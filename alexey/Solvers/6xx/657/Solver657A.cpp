#include <Solvers/pch.h>
#include "algo/io/baseio.h"
#include "iter/range.h"
using namespace std;

// Solution for Codeforces problem http://codeforces.com/contest/657/problem/A
class Solver657A
{
public:
    void run();
};

void Solver657A::run()
{
    int n, d, h;
    cin >> n >> d >> h;
    if (2 * h < d) {
        cout << -1;
        return;
    }

    if (d == 1 && n != 2){
        cout << -1;
        return;
    }

    if (d == 1 && n == 2) {
        cout << "1 2";
        return;
    }

    if (h == 1 && d == 2) {
        for (int i = 2; i <= n; ++i)
            cout << i << " 1\n";
        return;
    }


    vector<int> to(n);
    for (int i : range(n)) to[i] = i + 1;

    swap(to[0], to[h]);
    
    for (int i = 0; i < d; ++i)
        cout << to[i] << " " << to[i + 1] << "\n";

    for (int i = d + 1; i < n; ++i)
        cout << to[i] << " " << to[h - 1] << "\n";
}

class Solver657ATest : public ProblemTest {};

TEST_F(Solver657ATest, Example1)
{
    string input = R"(5 3 2
)";
    string output = R"(3 2
2 1
1 4
5 2
)";
    setInput(input);
    Solver657A().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}


TEST_F(Solver657ATest, Example2)
{
    string input = R"(8 5 2
)";
    string output = R"(-1
)";
    setInput(input);
    Solver657A().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}


TEST_F(Solver657ATest, Example3)
{
    string input = R"(8 4 2
)";
    string output = R"(3 2
2 1
1 4
4 5
6 2
7 2
8 2
)";
    setInput(input);
    Solver657A().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}


