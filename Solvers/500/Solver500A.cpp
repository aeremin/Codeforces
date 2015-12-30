#include <Solvers/pch.h>

using namespace std;

class Solver500A
{
public:
    void run();
};

void Solver500A::run()
{
    int n, t;
    cin >> n >> t;

    vector<bool> can( n );
    can[0] = true;

    for ( int i = 0; i < n - 1; ++i )
    {
        int dist;
        cin >> dist;
        if ( can[i] ) can[i + dist] = true;
    }

    cout << ( can[t - 1] ? "YES" : "NO" );
}

class Solver500ATest : public ProblemTest
{
};

TEST_F( Solver500ATest, Example1 )
{
    setInput("8 4              1 2 1 2 1 2 1");
    Solver500A().run();
    EXPECT_EQ("YES", getOutput());
}

TEST_F( Solver500ATest, Example2 )
{
    setInput("8 5              1 2 1 2 1 1 1");
    Solver500A().run();
    EXPECT_EQ("NO", getOutput());
}
