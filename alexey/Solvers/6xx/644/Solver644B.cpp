#include <Solvers/pch.h>
#include "algo/io/baseio.hpp"
#include "iter/range.h"
#include "algo/io/printvector.h"
using namespace std;

class Solver644B {
public:
    void run();
};

void Solver644B::run() {
    int n, b;
    cin >> n >> b;
    deque<pair<int64_t, int64_t>> requestsDuration;
    vector<int64_t> ans( n, -1 );
    int64_t currTime = 1;
    for ( int i : range( n ) ) {
        int64_t t, d;
        cin >> t >> d;
        while ( !requestsDuration.empty() && currTime + requestsDuration.front().second <= t ) {
            currTime += requestsDuration.front().second;
            ans[requestsDuration.front().first] = currTime;
            requestsDuration.pop_front();
        }

        if ( requestsDuration.empty() )
            currTime = t;

        if ( requestsDuration.size() <= b )
            requestsDuration.emplace_back( i, d );
    }

    while ( !requestsDuration.empty() ) {
        currTime += requestsDuration.front().second;
        ans[requestsDuration.front().first] = currTime;
        requestsDuration.pop_front();
    }

    printVector( ans );
}


class Solver644BTest : public ProblemTest {};

TEST_F( Solver644BTest, Example1 ) {
    string input = R"(5 1
2 9
4 8
10 9
15 2
19 1
)";
    string output = R"(11 19 -1 21 22
)";
    setInput( input );
    Solver644B().run();
    EXPECT_EQ_FUZZY( output, getOutput() );
}


TEST_F( Solver644BTest, Example2 ) {
    string input = R"(4 1
2 8
4 8
10 9
15 2
)";
    string output = R"(10 18 27 -1
)";
    setInput( input );
    Solver644B().run();
    EXPECT_EQ_FUZZY( output, getOutput() );
}

TEST_F(Solver644BTest, Example3) {
	string input = R"(4 0
3 2
5 3
6 5
8 1
)";
	string output = R"(5 8 -1 9)";
	setInput(input);
	Solver644B().run();
	EXPECT_EQ_FUZZY(getOutput(), output);
}

TEST_F( Solver644BTest, Example4 ) {
    string input = R"(4 4
3 2
4 5
5 4
6 10
)";
    string output = R"(5 10 14 24)";
    setInput( input );
    Solver644B().run();
    EXPECT_EQ_FUZZY( output, getOutput() );
}

TEST_F( Solver644BTest, InversedOutOrder ) {
    string input = R"(4 4
3 2
4 5
5 4
6 10
)";
    string output = R"(5 10 14 24)";
    setInput( input );
    Solver644B().run();
    EXPECT_EQ_FUZZY( output, getOutput() );
}