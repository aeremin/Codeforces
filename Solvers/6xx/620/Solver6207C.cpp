#include <Solvers/pch.h>

using namespace std;

class Solver620C
{
public:
    void run();
};

void Solver620C::run()
{
    int n;
    cin >> n;
    vector<int> colors( n );
    for ( auto& c : colors )
        cin >> c;

    vector<pair<int, int>> answer;
    int i = 0;
    while ( i < n )
    {
        unordered_set<int> existingColors;
        int j;
        for ( j = i; j < n; ++j )
        {
            if ( existingColors.count( colors[j] ) > 0 )
            {
                answer.push_back( { i + 1, j + 1 } );
                break;
            }
            existingColors.insert( colors[j] );
        }
        i = j + 1;
    }

    if ( answer.empty() )
        cout << -1;
    else
    {
        answer.back().second = n;
        cout << answer.size() << "\n";
        for ( auto p : answer )
            cout << p.first << " " << p.second << "\n";
    }
}

class Solver620CTest : public ProblemTest
{
};

TEST_F( Solver620CTest, Example1 )
{
    setInput("5              1 2 3 4 1");
    Solver620C().run();
    EXPECT_EQ("1\n1 5\n", getOutput());
}

TEST_F( Solver620CTest, Example2 )
{
    setInput("5              1 2 3 4 5");
    Solver620C().run();
    EXPECT_EQ("-1", getOutput());
}

TEST_F( Solver620CTest, Example3 )
{
    setInput( "7              1 2 1 3 1 2 1" );
    Solver620C().run();
    EXPECT_EQ( "2\n1 3\n4 7\n", getOutput() );
}

