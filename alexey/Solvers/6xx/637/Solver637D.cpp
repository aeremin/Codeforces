#include <Solvers/pch.h>
#include "algo/io/baseio.h"
#include "iter/range.h"
#include "algo/io/readvector.h"
using namespace std;

// Solution for Codeforces problem http://codeforces.com/contest/637/problem/D
class Solver637D {
public:
    void run();
};

void Solver637D::run() {
    int nObstacles = read<int>();
    int finishPos = read<int>();
    int runBeforeJump = read<int>();
    int maxJump = read<int>();
    auto obstacles = readVector<int>( nObstacles );
    obstacles.push_back( -1 );
    sort( begin( obstacles ), end( obstacles ) );
    
    if ( obstacles[1] < 1 + runBeforeJump ) {
        cout << "IMPOSSIBLE";
        return;
    }
    
    int iFrom = 1;
    stringstream ss;
    while ( iFrom < obstacles.size()
            ) {
        ss << "RUN " << obstacles[iFrom] - obstacles[iFrom - 1] - 2 << '\n';
        for ( int iTo : range<int>( iFrom, obstacles.size()) ) {
            if ( iTo == obstacles.size() - 1 || obstacles[iTo + 1] - obstacles[iTo] >= 2 + runBeforeJump ) {
                int jumpLen = obstacles[iTo] - obstacles[iFrom] + 2;
                if ( jumpLen > maxJump ) {
                    cout << "IMPOSSIBLE";
                    return;
                }
                ss << "JUMP " << jumpLen << "\n";
                iFrom = iTo + 1;
                break;
            }
        }
    }
    auto finalRunLen = finishPos - obstacles.back() - 1;
    if (finalRunLen > 0)
        ss << "RUN " << finalRunLen << '\n';

    cout << ss.str();
}

class Solver637DTest : public ProblemTest {};

TEST_F( Solver637DTest, Example1 ) {
    string input = R"(3 10 1 3
3 4 7
)";
    string output = R"(RUN 2
JUMP 3
RUN 1
JUMP 2
RUN 2
)";
    setInput( input );
    Solver637D().run();
    EXPECT_EQ( output, getOutput() );
}


TEST_F( Solver637DTest, Example2 ) {
    string input = R"(2 9 2 3
6 4
)";
    string output = R"(IMPOSSIBLE)";
    setInput( input );
    Solver637D().run();
    EXPECT_EQ( output, getOutput() );
}
