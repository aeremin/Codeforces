#include <Solvers/pch.h>
#include "algo/io/baseio.hpp"
#include "iter/range.h"
using namespace std;

class Solver644A {
public:
    void run();
};

void Solver644A::run() {
    int n, a, b;
    cin >> n >> a >> b;
    if ( n > a * b ) {
        cout << -1;
        return;
    }
    for ( int y : range( a ) ) {
        for ( int x : range( b ) ) {
            auto ind = 1 + y * b + ( y % 2 == 0 ? x : b - 1 - x );
            if ( ind > n )
                ind = 0;
            cout << ind << ' ';
        }

        cout << '\n';
    }
}

class Solver644ATest : public ProblemTest {};

TEST_F( Solver644ATest, Example1 ) {
    string input = R"(3 2 2
)";
    string output = R"(1 2 
0 3 
)";
    setInput( input );
    Solver644A().run();
    EXPECT_EQ( output, getOutput() );
}


TEST_F( Solver644ATest, Example2 ) {
    string input = R"(8 4 3
)";
    string output = R"(1 2 3 
6 5 4 
7 8 0 
0 0 0 
)";
    setInput( input );
    Solver644A().run();
    EXPECT_EQ( output, getOutput() );
}


TEST_F( Solver644ATest, Example3 ) {
    string input = R"(10 2 2
)";
    string output = R"(-1)";
    setInput( input );
    Solver644A().run();
    EXPECT_EQ( output, getOutput() );
}


