#include <Solvers/pch.h>

using namespace std;

class Solver500C
{
public:
    void run();
};

void Solver500C::run()
{
    int nBooks, nDays;

    cin >> nBooks >> nDays;

    vector<int> weight;

    for ( int i = 0; i < nBooks; ++i )
    {
        int w;
        cin >> w;
        weight.push_back( w );
    }

    vector<int> toread;
    for ( int i = 0; i < nDays; ++i )
    {
        int w;
        cin >> w;
        toread.push_back( w - 1 );
    }

    int total = 0;


    for ( int iBook = 0; iBook < nBooks; ++iBook )
    {
        vector<bool> alreadyCounted( nBooks, false );
        int localTotal = 0;
        for ( int iDay = 0; iDay < nDays; ++iDay )
        {
            if ( toread[iDay] == iBook )
            {
                total += localTotal;
                fill( begin( alreadyCounted ), end( alreadyCounted ), false );
                localTotal = 0;
            }
            else
            {
                if ( !alreadyCounted[toread[iDay]] )
                {
                    localTotal += weight[toread[iDay]];
                    alreadyCounted[toread[iDay]] = true;
                }
            }
        }
    }

    cout << total;
}

class Solver500CTest : public ProblemTest
{
};

TEST_F( Solver500CTest, Example1 )
{
    setInput("3 5              1 2 3              1 3 2 3 1");
    Solver500C().run();
    EXPECT_EQ("12", getOutput());
}
