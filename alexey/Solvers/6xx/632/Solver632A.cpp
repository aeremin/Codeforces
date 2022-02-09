#include <Solvers/pch.h>
#include "algo/io/baseio.h"
#include "iter/range.h"
using namespace std;

// Solution for Codeforces problem http://codeforces.com/contest/632/problem/A
class Solver632A
{
public:
    void run();
};

void Solver632A::run()
{
    int nBuyers;
    int price;
    cin >> nBuyers >> price;
    vector<bool> isBonus;
    int totalBonus = 0;
    for ( int i : range( nBuyers ) )
    {
        string s;
        cin >> s;
        bool isb = ( s == "halfplus" );
        isBonus.push_back( isb );
        if ( isb )
            totalBonus++;
    }

    int64_t totalApples = 0;
    for ( int i = nBuyers - 1; i >= 0; --i )
    {
        if ( isBonus[i] )
            totalApples = 2 * totalApples + 1;
        else
            totalApples = 2 * totalApples;
    }

    int64_t totalPaidHalves = 2 * totalApples - totalBonus;
    cout << ( price / 2 ) * totalPaidHalves;
}

class Solver632ATest : public ProblemTest {};

TEST_F(Solver632ATest, Example1)
{
    string input = R"(2 10
half
halfplus
)";
    string output = R"(15
)";
    setInput(input);
    Solver632A().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}


TEST_F(Solver632ATest, Example2)
{
    string input = R"(3 10
halfplus
halfplus
halfplus
)";
    string output = R"(55
)";
    setInput(input);
    Solver632A().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}


