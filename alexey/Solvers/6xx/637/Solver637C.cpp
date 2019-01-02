#include <Solvers/pch.h>
#include "algo/io/baseio.hpp"
#include "iter/range.h"
#include "algo/io/readvector.hpp"
#include "util/relax.h"
using namespace std;

// Solution for Codeforces problem http://codeforces.com/contest/637/problem/C
class Solver637C {
public:
    void run();

    int dist( const string& a, const string& b ) {
        int res = 0;
        for ( int i : range( 6 ) )
            if ( a[i] != b[i] )
                ++res;
        return res;
    }
};

void Solver637C::run() {
    int n = read<int>();
    auto codes = readVector<string>( n );
    int minDist = numeric_limits<int>::max();
    for ( int i : range( n ) )
        for ( int j : range( i ) )
            relax_min( minDist, dist( codes[i], codes[j] ) );
    cout << min( 6, (minDist - 1) / 2 );
}

class Solver637CTest : public ProblemTest {};


TEST_F( Solver637CTest, Example1 ) {
    string input = R"(2
000000
999999
)";
    string output = R"(2)";
    setInput( input );
    Solver637C().run();
    EXPECT_EQ( output, getOutput() );
}


TEST_F( Solver637CTest, Example2 ) {
    string input = R"(6
211111
212111
222111
111111
112111
121111
)";
    string output = R"(0)";
    setInput( input );
    Solver637C().run();
    EXPECT_EQ( output, getOutput() );
}
