#include <Solvers/pch.h>
#include "algo/io/baseio.h"
#include "iter/range.h"
using namespace std;

// Solution for Codeforces problem http://codeforces.com/contest/567/problem/D
class Solver567D
{
public:
    void run();
    
    int n, k, a;

    int maxFit(int len) {
        return (len + 1) / (a + 1);
    }

};

void Solver567D::run()
{
    cin >> n >> k >> a;
    set<int> checkedPos = { 0, n + 1 };
    int currMax = maxFit(n);
    int m;
    cin >> m;
    for (int i : range(m)) {
        int x;
        cin >> x;
        checkedPos.insert(x);
        auto iter = checkedPos.find(x);
        ++iter;
        auto currLen = *iter - 1;
        auto nextLenR = *iter - x - 1;
        --iter; --iter;
        currLen -= *iter;
        auto nextLenL = x - *iter - 1;
        currMax = currMax + maxFit(nextLenL) + maxFit(nextLenR) - maxFit(currLen);
        if (currMax < k) {
            cout << (i + 1);
            return;
        }
    }

    cout << -1;
}

class Solver567DTest : public ProblemTest {};

TEST_F(Solver567DTest, Example1)
{
    string input = R"(11 3 3
5
4 8 6 1 11
)";
    string output = R"(3
)";
    output.pop_back();
    setInput(input);
    Solver567D().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}


TEST_F(Solver567DTest, Example2)
{
    string input = R"(5 1 3
2
1 5
)";
    string output = R"(-1
)";
    output.pop_back();
    setInput(input);
    Solver567D().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}


TEST_F(Solver567DTest, Example3)
{
    string input = R"(5 1 3
1
3
)";
    string output = R"(1
)";
    output.pop_back();
    setInput(input);
    Solver567D().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}


