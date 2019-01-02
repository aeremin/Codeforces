#include <Solvers/pch.h>
#include "algo/io/readvector.hpp"

using namespace std;

// Solution for Codeforces problem http://codeforces.com/contest/554/problem/B
class Solver554B
{
public:
    void run();
};

void Solver554B::run()
{
    int n;
    cin >> n;
    auto field = readVector<string>( n );
    unordered_map<string, int> count;
    for ( auto s : field )
        count[s]++;

    auto pred = []( const pair<string, int>& lh, const pair<string, int>& rh )
    {
        return lh.second < rh.second;
    };
    cout << ( max_element( begin( count ), end( count ), pred )->second );
}

class Solver554BTest : public ProblemTest {};

TEST_F(Solver554BTest, Example1)
{
    string input = R"(4
0101
1000
1111
0101
)";
    string output = R"(2
)";
    setInput(input);
    Solver554B().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}


TEST_F(Solver554BTest, Example2)
{
    string input = R"(3
111
111
111
)";
    string output = R"(3
)";
    setInput(input);
    Solver554B().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}


