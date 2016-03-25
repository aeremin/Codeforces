#include <Solvers/pch.h>
#include "algo/io/baseio.hpp"
#include "iter/range.h"
#include "algo/io/readvector.hpp"
using namespace std;

class Solver652B
{
public:
    void run();
};

void Solver652B::run()
{
    int n = read<int>();
    auto nums = readVector<int>(n);
    sort( begin( nums ), end( nums ) );
    for ( int i : range( n ) ) {
        if ( i % 2 == 0 )
            cout << nums[i / 2] << " ";
        else
            cout << nums[n - 1 - i / 2] << " ";
    }
}

class Solver652BTest : public ProblemTest {};

TEST_F(Solver652BTest, Example1)
{
    string input = R"(4
1 2 2 1
)";
    string output = R"(1 2 1 2 
)";
    output.pop_back();
    setInput(input);
    Solver652B().run();
    EXPECT_EQ(output, getOutput());
}


TEST_F(Solver652BTest, Example2)
{
    string input = R"(5
1 3 2 2 5
)";
    string output = R"(1 5 2 3 2 
)";
    output.pop_back();
    setInput(input);
    Solver652B().run();
    EXPECT_EQ(output, getOutput());
}


