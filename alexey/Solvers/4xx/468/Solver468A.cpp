#include <Solvers/pch.h>
using namespace std;

// Solution for Codeforces problem http://codeforces.com/contest/468/problem/A
class Solver468A
{
public:
    void run();
};

void Solver468A::run()
{
    int n;
    cin >> n;

    if ( n < 4 )
    {
        cout << "NO";
        return;
    }

    cout << "YES" << endl;
    int s;
    if ( n % 2 == 0 )
    {
        cout << "1 * 2 = 2" << endl;
        cout << "2 * 3 = 6" << endl;
        cout << "6 * 4 = 24" << endl;
        s = 5;
    }
    else
    {
        cout << "1 + 5 = 6" << endl;
        cout << "4 * 6 = 24" << endl;
        cout << "3 - 2 = 1" << endl;
        cout << "24 * 1 = 24" << endl;
        s = 6;
    }

    for ( int i = s; i < n; i += 2 )
    {
        cout << i + 1 << " - " << i << " = 1" << endl;
        cout << "24 * 1 = 24" << endl;
    }
}

class Solver468ATest : public ProblemTest
{
};

TEST_F( Solver468ATest, Example1 )
{
    setInput("1");
    Solver468A().run();
    EXPECT_EQ("NO", getOutput());
}

TEST_F( Solver468ATest, Example2 )
{
    setInput("8");
    Solver468A().run();
    auto ans =
R"(YES
1 * 2 = 2
2 * 3 = 6
6 * 4 = 24
6 - 5 = 1
24 * 1 = 24
8 - 7 = 1
24 * 1 = 24
)";
    EXPECT_EQ(ans, getOutput());
}