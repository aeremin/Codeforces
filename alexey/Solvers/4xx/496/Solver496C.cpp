#include <Solvers/pch.h>

using namespace std;

class Solver496C
{
public:
    void run();
};

void Solver496C::run()
{
    int n, m;
    cin >> n >> m;

    vector<vector<char>> table;
    vector<bool> canbreak( m, false );

    for ( int i = 0; i < n; ++i )
    {
        table.push_back( vector<char>( m ) );
        for ( int j = 0; j < m; ++j )
        {
            cin >> table[i][j];
        }
    }

    int todel = 0;
    for ( int j = 0; j < m; ++j )
    {
        bool needdel = false;

        vector<int> breaks;

        char cur = 'a';
        for ( int i = 0; i < n; ++i )
        {
            if ( canbreak[i] )
            {
                cur = 'a';
            }

            if ( table[i][j] < cur )
            {
                needdel = true;
                break;
            }

            if ( table[i][j] > cur )
            {
                breaks.push_back( i );
            }

            cur = table[i][j];
        }

        if ( needdel ) todel++;
        else     for ( int k = 0; k < breaks.size(); ++k ) canbreak[breaks[k]] = true;
    }

    cout << todel;
}

class Solver496CTest : public ProblemTest
{
};

TEST_F( Solver496CTest, Example1 )
{
    setInput("1 10              codeforces");
    Solver496C().run();
    EXPECT_EQ("0", getOutput());
}

TEST_F( Solver496CTest, Example2 )
{
    setInput("4 4              case              care              test              code");
    Solver496C().run();
    EXPECT_EQ("2", getOutput());
}

TEST_F( Solver496CTest, Example3 )
{
    setInput( "5 4              code              forc              esco              defo              rces" );
    Solver496C().run();
    EXPECT_EQ( "4", getOutput() );
}