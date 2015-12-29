#include <Solvers/pch.h>

using namespace std;

class Solver482A
{
public:
    void run();
};

void Solver482A::run()
{
    int n, k;
    cin >> n >> k;

    deque<int> ans;

    int dif = 0;
    for ( int i = 0; i <= k; ++i )
    {
        ans.push_back( dif );
        if ( i % 2 == 0 )
            dif = -dif + 1;
        else
            dif = -dif;
    }

    int last = ans.back();
    if ( last <= 0 )
    {
        while ( ans.size() < n )
        {
            last--;
            ans.push_back( last );
        }

        for ( int elt : ans )
            cout << elt - last + 1 << ' ';
    }
    else
    {
        while ( ans.size() < n )
        {
            last++;
            ans.push_back( last );
        }

        for ( int elt : ans )
            cout << elt + n - last << ' ';
    }
}

class Solver482ATest : public ProblemTest
{
};

TEST_F( Solver482ATest, Example1 )
{
    setInput("3 2");
    Solver482A().run();
    EXPECT_EQ("2 3 1 ", getOutput());
}

TEST_F( Solver482ATest, Example2 )
{
    setInput("3 1");
    Solver482A().run();
    EXPECT_EQ("1 2 3 ", getOutput());
}

TEST_F( Solver482ATest, Example3 )
{
    setInput( "5 2" );
    Solver482A().run();
    EXPECT_EQ( "4 5 3 2 1 ", getOutput() );
}