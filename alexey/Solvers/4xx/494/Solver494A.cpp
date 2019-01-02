#include <Solvers/pch.h>

using namespace std;

// Solution for Codeforces problem http://codeforces.com/contest/494/problem/A
class Solver494A
{
public:
    void run();
};

void Solver494A::run()
{
    string s;
    cin >> s;
    int numLeft = 0;
    int numRight = 0;
    int numSharp = 0;

    vector<int> balance;
    int lastSharp = 0;
    for ( int i = 0; i < s.length(); ++i )
    {
        switch ( s[i] )
        {
        case '(': numLeft++; break;
        case ')': numRight++; break;
        case '#': numSharp++; lastSharp = i;  break;
        }
        balance.push_back( numLeft - numRight - numSharp );
    }

    if ( any_of( begin( balance ), end( balance ), []( int bal )
    {
        return bal < 0;
    } ) )
    {
        cout << -1;
        return;
    }

    for ( int i = lastSharp; i < balance.size(); ++i )
    {
        if ( balance[i] < balance.back() )
        {
            cout << -1;
            return;
        }
    }

    for ( int i = 0; i < numSharp - 1; ++i )
    {
        cout << 1 << '\n';
    }
    cout << 1 + balance.back();
}

class Solver494ATest : public ProblemTest
{
};

TEST_F( Solver494ATest, Example1 )
{
    setInput("(((#)((#)");
    Solver494A().run();
    EXPECT_EQ("1\n2", getOutput());
}

TEST_F( Solver494ATest, Example2 )
{
    setInput("()((#((#(#()");
    Solver494A().run();
    EXPECT_EQ("1\n1\n3", getOutput());
}

TEST_F( Solver494ATest, Example3 )
{
    setInput( "#" );
    Solver494A().run();
    EXPECT_EQ( "-1", getOutput() );
}

TEST_F( Solver494ATest, Example4 )
{
    setInput( "(#)" );
    Solver494A().run();
    EXPECT_EQ( "-1", getOutput() );
}