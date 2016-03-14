#include <Solvers/pch.h>
#include "algo/io/baseio.hpp"
#include "iter/range.h"
#include "algo/io/readvector.hpp"
#include "util/weight_comparator.h"
using namespace std;

class Solver637B {
public:
    void run();
};

void Solver637B::run() {
    int n = read<int>();
    auto names = readVector<string>( n );
    unordered_map<string, int> lastMsgTime;
    for ( int i : range( n ) )
        lastMsgTime[names[i]] = i;

    vector<pair<string, int>> lastMsgTimeFlat( begin( lastMsgTime ), end( lastMsgTime ) );
    sort( begin( lastMsgTimeFlat ), end( lastMsgTimeFlat ), 
          make_weight_comparator( []( const pair<string, int>& v ) {return -v.second; } ) );
    for ( auto name : lastMsgTimeFlat )
        cout << name.first << '\n';

}

class Solver637BTest : public ProblemTest {};

TEST_F( Solver637BTest, Example1 ) {
    string input = R"(4
alex
ivan
roman
ivan
)";
    string output = R"(ivan
roman
alex
)";
    setInput( input );
    Solver637B().run();
    EXPECT_EQ( output, getOutput() );
}


TEST_F( Solver637BTest, Example2 ) {
    string input = R"(8
alina
maria
ekaterina
darya
darya
ekaterina
maria
alina
)";
    string output = R"(alina
maria
ekaterina
darya
)";
    setInput( input );
    Solver637B().run();
    EXPECT_EQ( output, getOutput() );
}

