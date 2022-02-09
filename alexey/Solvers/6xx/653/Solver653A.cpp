#include <Solvers/pch.h>
#include "algo/io/baseio.h"
#include "iter/range.h"
using namespace std;

// Solution for Codeforces problem http://codeforces.com/contest/653/problem/A
class Solver653A
{
public:
    void run();
};

void Solver653A::run()
{
    int nBalls;
    cin >> nBalls;
    set<int> balls;
    for (int i : range(nBalls)) {
        int s;
        cin >> s;
        balls.insert(s);
    }

    for (int i : range(1, 1000)) {
        if (balls.count(i) > 0 && balls.count(i + 1) > 0 && balls.count(i + 2) > 0) {
            cout << "YES";
            return;
        }
    }

    cout << "NO";
}

class Solver653ATest : public ProblemTest {};

TEST_F(Solver653ATest, Example1)
{
    string input = R"(4
18 55 16 17
)";
    string output = R"(YES
)";
    setInput(input);
    Solver653A().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}


TEST_F(Solver653ATest, Example2)
{
    string input = R"(6
40 41 43 44 44 44
)";
    string output = R"(NO
)";
    setInput(input);
    Solver653A().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}


TEST_F(Solver653ATest, Example3)
{
    string input = R"(8
5 972 3 4 1 4 970 971
)";
    string output = R"(YES
)";
    setInput(input);
    Solver653A().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}


