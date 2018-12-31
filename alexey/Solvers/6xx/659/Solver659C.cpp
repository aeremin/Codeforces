#include <Solvers/pch.h>
#include "algo/io/baseio.hpp"
#include "iter/range.h"
#include "algo/io/printvector.h"
using namespace std;

class Solver659C
{
public:
    void run();
};

void Solver659C::run()
{
    int nHas, money;
    cin >> nHas >> money;
    unordered_set<int> has;
    for ( int i : range( nHas ) ) {
        int p;
        cin >> p;
        has.insert( p );
    }

    vector<int> ans;
    for ( int buy = 1; buy <= money; ++buy ) {
        if ( has.count( buy ) == 0 ) {
            ans.push_back( buy );
            money -= buy;
        }
    }

    cout << ans.size() << "\n";
    printVector( ans );
}

class Solver659CTest : public ProblemTest {};

TEST_F(Solver659CTest, Example1)
{
    string input = R"(3 7
1 3 4
)";
    string output = R"(2
2 5
)";
    setInput(input);
    Solver659C().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}


TEST_F(Solver659CTest, Example2)
{
    string input = R"(4 14
4 6 12 8
)";
    string output = R"(4
1 2 3 5
)";
    setInput(input);
    Solver659C().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}


