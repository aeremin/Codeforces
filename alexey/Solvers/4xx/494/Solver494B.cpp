#include <Solvers/pch.h>
#include "algo/strings/KnuttMorrisPratt.hpp"

using namespace std;

class Solver494B
{
public:
    void run();
};

void Solver494B::run()
{
    const int MODULO = 1e9 + 7;

    string s;
    string t;
    cin >> s;
    cin >> t;

    string concat = t + '$' + s;
    auto pi = calc_prefix_function( concat );

    int goodpi = t.length();

    vector<int64_t> res;
    vector<int64_t> sumres;

    res.push_back( 1 );
    sumres.push_back( 1 );
    int lastStringStart = -1;

    for ( int i = 0; i < s.length(); ++i )
    {
        if ( pi[i + goodpi + 1] == goodpi ) lastStringStart = i - goodpi + 1;
        int64_t curres = res.back();
        if ( lastStringStart >= 0 )
        {
            curres = ( curres + sumres[lastStringStart] ) % MODULO;
        }
        int64_t currsumres = ( sumres.back() + curres ) % MODULO;
        res.push_back( curres );
        sumres.push_back( currsumres );
    }

    cout << ( res.back() + MODULO - 1 ) % MODULO;
}

class Solver494BTest : public ProblemTest
{
};

TEST_F( Solver494BTest, Example1 )
{
    setInput( "ababa              aba" );
    Solver494B().run();
    EXPECT_EQ( "5", getOutput() );
}

TEST_F( Solver494BTest, Example2 )
{
    setInput( "welcometoroundtwohundredandeightytwo              d" );
    Solver494B().run();
    EXPECT_EQ( "274201", getOutput() );
}

TEST_F( Solver494BTest, Example3 )
{
    setInput( "ddd              d" );
    Solver494B().run();
    EXPECT_EQ( "12", getOutput() );
}