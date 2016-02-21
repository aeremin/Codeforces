#include <Solvers/pch.h>

using namespace std;

class Solver484A
{
public:
    void run();
};

void Solver484A::run()
{
    int nQueries;
    cin >> nQueries;

    const uint64_t one = 1;
    for ( int i = 0; i < nQueries; ++i )
    {
        uint64_t l, r;
        cin >> l >> r;

        if ( l == r )
        {
            cout << l << '\n';
            continue;
        }

        int maxDifPow = 1;
        while ( l >> maxDifPow != r >> maxDifPow )
            ++maxDifPow;
        uint64_t ones = ( one << maxDifPow - 1 ) - 1;

        if ( ( r | ones ) <= r )
            cout << ( r | ones ) << endl;
        else
            cout << ( l | ones ) << endl;
    }
}

class Solver484ATest : public ProblemTest
{
};

TEST_F( Solver484ATest, Example1 )
{
    setInput("3              1 2              2 4              1 10");
    Solver484A().run();
    EXPECT_EQ("1\n3\n7\n", getOutput());
}