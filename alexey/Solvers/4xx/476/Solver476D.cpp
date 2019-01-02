#include <Solvers/pch.h>

using namespace std;

// Solution for Codeforces problem http://codeforces.com/contest/476/problem/D
class Solver476D
{
public:
    void run();
};

void Solver476D::run()
{
    int n, k;
    cin >> n >> k;

    cout << ( 6 * n - 1 ) * k << endl;

    for ( int i = 0; i < n; ++i )
        cout << k * ( 1 + 6 * i ) << ' ' << k * ( 2 + 6 * i ) << ' ' << k * ( 3 + 6 * i ) << ' ' << k * ( 5 + 6 * i ) << endl;
}

class Solver476DTest : public ProblemTest
{
};

TEST_F( Solver476DTest, Example1 )
{
    setInput("1 1");
    Solver476D().run();
    EXPECT_EQ("5\n1 2 3 5\n", getOutput());
}

TEST_F( Solver476DTest, Example2 )
{
    setInput("2 2");
    Solver476D().run();
    EXPECT_EQ("22\n2 4 6 10\n14 16 18 22\n", getOutput());
}