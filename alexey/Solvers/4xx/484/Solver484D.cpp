#include <Solvers/pch.h>
#include "math/sign.h"

using namespace std;

// Solution for Codeforces problem http://codeforces.com/contest/484/problem/D
class Solver484D
{
public:
    void run();
};

void Solver484D::run()
{
    int nChilds;
    cin >> nChilds;

    deque<int> ch( nChilds );
    for ( int& charisma : ch )
        cin >> charisma;

    ch.push_front( ch.front() );
    ch.push_back( ch.back() );

    vector<int64_t> dynRes;
    dynRes.push_back( 0 );
    dynRes.push_back( 0 );

    int lastExtremalInd = 1;
    for ( int i = 2; i < ch.size() - 1; ++i )
    {
        int64_t curres = max( dynRes[lastExtremalInd] + abs( ch[i] - ch[lastExtremalInd + 1] ),
                              dynRes[lastExtremalInd - 1] + abs( ch[i] - ch[lastExtremalInd] ) );
        dynRes.push_back( curres );
        if ( sgn( ch[i] - ch[i - 1] ) != sgn( ch[i + 1] - ch[i] ) )
            lastExtremalInd = i;
    }

    cout << dynRes.back();
}

class Solver484DTest : public ProblemTest
{
};

TEST_F( Solver484DTest, Example1 )
{
    setInput("5              1 2 3 1 2");
    Solver484D().run();
    EXPECT_EQ("3", getOutput());
}

TEST_F( Solver484DTest, Example2 )
{
    setInput("3              3 3 3");
    Solver484D().run();
    EXPECT_EQ("0", getOutput());
}