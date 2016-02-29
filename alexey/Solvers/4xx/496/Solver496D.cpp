#include <Solvers/pch.h>

using namespace std;

class Solver496D
{
public:
    void run();

    int n, blockSize, winner;
    vector<int> results;
    vector<int> wins1;
    vector<int> wins2;

    int getSforT( int t )
    {
        int total[2] = { 0, 0 };
        int local[2] = { 0, 0 };
        int k = 0;
        while ( k < n )
        {
            while ( k % blockSize != 0 && max( local[0], local[1] ) < t && k < n )
            {
                local[results[k] - 1]++;
                k++;
            }

            if ( max( local[0], local[1] ) >= t )
            {
                if ( local[0] > local[1] ) total[0]++; else total[1]++;
                local[0] = 0; local[1] = 0;
                continue;
            }

            if ( k >= n )
            {
                return -1;
            }

            int posLocal[2] = { local[0], local[1] };
            while ( max( posLocal[0], posLocal[1] ) < t && k < n )
            {
                posLocal[0] += wins1[k / blockSize];
                posLocal[1] += wins2[k / blockSize];
                k += blockSize;
            }

            if ( max( posLocal[0], posLocal[1] ) >= t )
            {
                k -= blockSize;
                local[0] = posLocal[0] - wins1[k / blockSize];
                local[1] = posLocal[1] - wins2[k / blockSize];
                while ( max( local[0], local[1] ) < t )
                {
                    local[results[k] - 1]++;
                    k++;
                }

                if ( local[0] > local[1] ) total[0]++; else total[1]++;
                local[0] = 0; local[1] = 0;
                continue;
            }

            if ( k >= n )
            {
                return -1;
            }
        }

        if ( total[0] == total[1] ) return -1;
        if ( total[0] > total[1] ) return winner == 1 ? total[0] : -1;
        return winner == 2 ? total[1] : -1;
    }
};

void Solver496D::run()
{
    cin >> n;

    results.resize( n );
    for ( int i = 0; i < n; ++i )
    {
        cin >> results[i];
        wins1.push_back( 0 );
        wins2.push_back( 0 );
    }

    winner = results.back();

    blockSize = sqrt( float( n ) );

    for ( int i = 0; i < n; ++i )
    {
        int iBlock = i / blockSize;
        if ( results[i] == 1 ) wins1[iBlock]++; else wins2[iBlock]++;
    }

    struct Params
    {
        int s;
        int t;
    };

    vector<Params> possibl;

    for ( int t = 1; t <= n; ++t )
    {
        int s = getSforT( t );
        if ( s > 0 )
        {
            Params p;
            p.s = s; p.t = t;
            possibl.push_back( p );
        }
    }

    sort( begin( possibl ), end( possibl ), []( Params a, Params b )->bool
    {
        if ( a.s < b.s ) return true;
        if ( a.s > b.s ) return false;
        return a.t < b.t;
    } );

    cout << possibl.size() << endl;
    for ( int i = 0; i < possibl.size(); ++i )
    {
        cout << possibl[i].s << ' ' << possibl[i].t << '\n';
    }
}

class Solver496DTest : public ProblemTest
{
};

TEST_F( Solver496DTest, Example1 )
{
    setInput( "5              1 2 1 2 1" );
    Solver496D().run();
    EXPECT_EQ( "2\n1 3\n3 1\n", getOutput() );
}

TEST_F( Solver496DTest, Example2 )
{
    setInput( "4              1 1 1 1" );
    Solver496D().run();
    EXPECT_EQ( "3\n1 4\n2 2\n4 1\n", getOutput() );
}

TEST_F( Solver496DTest, Example3 )
{
    setInput( "4              1 2 1 2" );
    Solver496D().run();
    EXPECT_EQ( "0\n", getOutput() );
}

TEST_F( Solver496DTest, Example4 )
{
    setInput( "8              2 1 2 1 1 1 1 1" );
    Solver496D().run();
    EXPECT_EQ( "3\n1 6\n2 3\n6 1\n", getOutput() );
}
