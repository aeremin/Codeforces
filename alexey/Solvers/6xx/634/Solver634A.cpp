#include <Solvers/pch.h>
#include "algo/io/baseio.h"
#include "iter/range.h"
#include "algo/io/readvector.h"
using namespace std;

// Solution for Codeforces problem http://codeforces.com/contest/634/problem/A
class Solver634A
{
public:
    void run();

    vector<int> normalize( const vector<int>& in )
    {
        vector<int> result;
        auto firstStatueIter = find( begin( in ), end( in ), 1 );
        auto collectIfNotZero = [&]( int val )
        {
            if ( val != 0 )
                result.push_back( val );
        };

        for ( auto it = firstStatueIter; it != end( in ); ++it )
            collectIfNotZero( *it );

        for ( auto it = begin( in ); it != firstStatueIter; ++it )
            collectIfNotZero( *it );

        return result;
    }
};

void Solver634A::run()
{
    int n = read<int>();
    auto before = readVector<int>( n );
    auto after = readVector<int>( n );
    before = normalize( before );
    after = normalize( after );
    if ( after == before )
        cout << "YES";
    else
        cout << "NO";
}

class Solver634ATest : public ProblemTest {};

TEST_F(Solver634ATest, Example1)
{
    string input = R"(3
1 0 2
2 0 1
)";
    string output = R"(YES
)";
    setInput(input);
    Solver634A().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}


TEST_F(Solver634ATest, Example2)
{
    string input = R"(2
1 0
0 1
)";
    string output = R"(YES
)";
    setInput(input);
    Solver634A().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}


TEST_F(Solver634ATest, Example3)
{
    string input = R"(4
1 2 3 0
0 3 2 1
)";
    string output = R"(NO
)";
    setInput(input);
    Solver634A().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}


