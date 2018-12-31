#include <Solvers/pch.h>
#include "algo/io/readvector.hpp"

using namespace std;

class Solver600B
{
public:
    void run();
};

void Solver600B::run()
{
    auto n = read<int>();
    auto m = read<int>();
    auto a = readVector<int>( n );
    auto b = readVector<int>( m );
    sort( begin( a ), end( a ) );
    for ( auto bb : b )
        cout << ( upper_bound( begin( a ), end( a ), bb ) - begin( a ) ) << " ";
}

class Solver600BTest : public ProblemTest {};

TEST_F(Solver600BTest, Example1)
{
    string input = R"(5 4
1 3 5 7 9
6 4 2 8
)";
    string output = R"(3 2 1 4 
)";
    setInput(input);
    Solver600B().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}


TEST_F(Solver600BTest, Example2)
{
    string input = R"(5 5
1 2 1 2 5
3 1 4 1 5
)";
    string output = R"(4 2 4 2 5 
)";
    setInput(input);
    Solver600B().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}


