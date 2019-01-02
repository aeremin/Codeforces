#include <Solvers/pch.h>
#include "algo/io/baseio.hpp"
#include "iter/range.h"
#include "algo/FunctorIterator.hpp"
using namespace std;

// Solution for Codeforces problem http://codeforces.com/contest/633/problem/B
class Solver633B
{
public:
    void run();
};

void Solver633B::run()
{
    std::function<int(int)> zeroesCount = [&]( int n )
    {
        if ( n == 0 ) return 0;
        return n / 5 + zeroesCount( n / 5 );
    };

    int m;
    cin >> m;
    
    auto l = makeFunctorIterator( 0, zeroesCount );
    auto r = makeFunctorIterator( 5 * m + 5, zeroesCount );

    auto lb = lower_bound( l, r, m );
    auto rb = upper_bound( l, r, m );

    cout << rb - lb << "\n";
    for ( auto i : range( lb.getParameter(), rb.getParameter() ) )
        cout << i << " ";
}

class Solver633BTest : public ProblemTest {};

TEST_F(Solver633BTest, Example1)
{
    string input = R"(1
)";
    string output = R"(5
5 6 7 8 9 )";
    setInput(input);
    Solver633B().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}


TEST_F(Solver633BTest, Example2)
{
    string input = R"(5
)";
    string output = R"(0
)";
    setInput(input);
    Solver633B().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}


