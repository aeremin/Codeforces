#include <Solvers/pch.h>
#include "algo/io/baseio.hpp"
#include "iter/range.h"
#include "algo/borrower.h"
#include "util/relax.h"

using namespace std;

// Solution for Codeforces problem http://codeforces.com/contest/633/problem/D
class Solver633D
{
public:
    void run();
};

void Solver633D::run()
{
    int n;
    cin >> n;
    unordered_multiset<int> nums;
    vector<int> numsRaw;
    for ( int i : range( n ) )
    {
        int elt;
        cin >> elt;
        nums.insert( elt );
        numsRaw.push_back( elt );
    }

    int ans = 0;

    vector<Borrower<unordered_multiset<int>>> borrowers;
    borrowers.reserve( n );
    for ( auto i : range(n) )
    {
        for ( auto j : range(n) )
        {
            if (i == j)
                continue;
            auto f1 = numsRaw[i];
            auto f2 = numsRaw[j];
            borrowers.clear();
            borrowers.push_back( make_borrower( nums, f1 ) );
            borrowers.push_back( make_borrower( nums, f2 ) );
            int currLen = 2;
            for ( auto iter = nums.find( f1 + f2 ); iter != end( nums ); iter = nums.find( f1 + f2 ) )
            {
                ++currLen;
                tie( f1, f2 ) = make_pair( f2, f1 + f2 );
                borrowers.push_back( make_borrower( nums, iter ) );
            }
            relax_max(ans, currLen);
        }
    }

    cout << ans;
}

class Solver633DTest : public ProblemTest {};

TEST_F(Solver633DTest, Example1)
{
    string input = R"(3
1 2 -1
)";
    string output = R"(3
)";
    setInput(input);
    Solver633D().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}


TEST_F(Solver633DTest, Example2)
{
    string input = R"(5
28 35 7 14 21
)";
    string output = R"(4
)";
    setInput(input);
    Solver633D().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}

TEST_F( Solver633DTest, Zeroes )
{
    string input = R"(7
0 0 0 3 0 0 0
)";
    string output = R"(6
)";
    setInput( input );
    Solver633D().run();
    EXPECT_EQ_FUZZY( output, getOutput() );
}


