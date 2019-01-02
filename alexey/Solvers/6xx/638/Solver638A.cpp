#include <Solvers/pch.h>
#include "algo/io/baseio.hpp"
#include "iter/range.h"
using namespace std;

// Solution for Codeforces problem http://codeforces.com/contest/638/problem/A
class Solver638A
{
public:
    void run();

    int n;

    int dist( int a ) {
        if ( a % 2 == 0 )
            return 1 + ( n - a ) / 2;
        else
            return 1 + a / 2;
    }
};

void Solver638A::run()
{
    int a;
    cin >> n >> a;
    cout << min( dist( a ), dist( n + 1 - a ) );
}

class Solver638ATest : public ProblemTest {};

TEST_F( Solver638ATest, Example1 ) {
    string input = "4 2";
    string output = "2";
    setInput( input );
    Solver638A().run();
    EXPECT_EQ( output, getOutput() );
}

TEST_F( Solver638ATest, Example2 ) {
    string input = "8 5";
    string output = "3";
    setInput( input );
    Solver638A().run();
    EXPECT_EQ( output, getOutput() );
}
