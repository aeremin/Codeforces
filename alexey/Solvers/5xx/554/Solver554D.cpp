#include <Solvers/pch.h>
#include "algo/io/printvector.h"

using namespace std;

class Solver554D
{
public:
    void run();

    vector<int64_t> goodPermCounts;

    vector<int> findAns( int64_t n, int64_t k )
    {
        if ( n == 1 )
        {
            return{ 1 };
        }
        if ( n == 0 )
        {
            return{};
        }
        if ( k <= goodPermCounts[n - 1] )
        {
            auto preAns = findAns( n - 1, k );
            vector<int> ans = { 1 };
            for ( auto elt : preAns )
                ans.push_back( elt + 1 );
            return ans;
        }
        else
        {
            auto preAns = findAns( n - 2, k - goodPermCounts[n - 1] );
            vector<int> ans = { 2, 1 };
            for ( auto elt : preAns )
                ans.push_back( elt + 2 );
            return ans;
        }
    }
};

void Solver554D::run()
{
    int64_t n, k;
    cin >> n >> k;
    goodPermCounts = { 1, 1 };
    while ( goodPermCounts.size() <= n )
        goodPermCounts.push_back( goodPermCounts[goodPermCounts.size() - 1] + goodPermCounts[goodPermCounts.size() - 2] );
    auto ans = findAns( n, k );
    printVector( ans );
}
class Solver554DTest : public ProblemTest {};

TEST_F(Solver554DTest, Example1)
{
    string input = R"(4 3
)";
    string output = R"(1 3 2 4
)";
    setInput(input);
    Solver554D().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}


TEST_F(Solver554DTest, Example2)
{
    string input = R"(10 1
)";
    string output = R"(1 2 3 4 5 6 7 8 9 10
)";
    setInput(input);
    Solver554D().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}


TEST_F( Solver554DTest, Example3 )
{
    string input = R"(1 1
)";
    string output = R"(1
)";
    setInput( input );
    Solver554D().run();
    EXPECT_EQ_FUZZY( output, getOutput() );
}

TEST_F( Solver554DTest, Example4 )
{
    string input = R"(50 100000000)";
    setInput( input );
    Solver554D().run();
}

TEST_F( Solver554DTest, Example5 )
{
    string input = R"(2 2
)";
    string output = R"(2 1
)";
    setInput( input );
    Solver554D().run();
    EXPECT_EQ_FUZZY( output, getOutput() );
}