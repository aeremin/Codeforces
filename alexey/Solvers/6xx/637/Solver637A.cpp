#include <Solvers/pch.h>
#include "algo/io/baseio.hpp"
#include "iter/range.h"
#include "algo/io/readvector.hpp"
using namespace std;

class Solver637A {
public:
    void run();
};

void Solver637A::run() {
    int nLikes = read<int>();
    auto likes = readVector<int>( nLikes );
    int leader = 0;
    unordered_map<int, int> likeCount;
    for ( auto l : likes )
        if ( ++likeCount[l] > likeCount[leader] )
            leader = l;

    print( leader );
}

class Solver637ATest : public ProblemTest {};

TEST_F( Solver637ATest, Example1 ) {
    string input = R"(5
1 3 2 2 1
)";
    string output = R"(2)";
    setInput( input );
    Solver637A().run();
    EXPECT_EQ( output, getOutput() );
}


TEST_F( Solver637ATest, Example2 ) {
    string input = R"(9
100 200 300 200 100 300 300 100 200
)";
    string output = R"(300)";
    setInput( input );
    Solver637A().run();
    EXPECT_EQ( output, getOutput() );
}