#include <Solvers/pch.h>
#include "algo/io/baseio.hpp"
#include "iter/range.h"
#include "algo/io/readvector.hpp"
using namespace std;

class Solver638B
{
public:
    void run();
};

void Solver638B::run() {
    int n;
    cin >> n;
    set<char> used;
    auto parts = readVector<string>( n );
    for ( auto p : parts )
        for ( auto c : p )
            used.insert( c );

    auto next = [&]( char c ) -> char {
        for ( auto p : parts ) {
            auto ind = p.find( c );
            if ( ind != string::npos && ind != p.length() - 1 )
                return p[ind + 1];
        }
        return 0;
    };
    
    auto potentialFirst = used;
    for ( auto c : used )
        potentialFirst.erase( next( c ) );

    for (auto c : potentialFirst ) {
        while ( c != 0 ) {
            cout << c;
            c = next( c );
        }
    }
}

class Solver638BTest : public ProblemTest {};

TEST_F( Solver638BTest, Example1 ) {
    string input = R"(3
bcd
ab
cdef
)";
    string output = "abcdef";
    setInput( input );
    Solver638B().run();
    EXPECT_EQ( output, getOutput() );
}
