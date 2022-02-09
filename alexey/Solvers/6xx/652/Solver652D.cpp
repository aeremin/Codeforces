#include <Solvers/pch.h>

#include "algo/sort_with_mapping.h"
#include "algo/io/baseio.h"
#include "algo/io/printvector.h"
#include "algo/io/readvector.h"
#include "algo/segment_tree/segment_tree.h"
#include "algo/segment_tree/update_appliers/increase_by_sum.h"
#include "algo/segment_tree/update_types/increase_by.h"
#include "iter/range.h"
using namespace std;

// Solution for Codeforces problem http://codeforces.com/contest/652/problem/D
class Solver652D
{
public:
    void run();
};

void Solver652D::run()
{
    int n = read<int>();
    auto allEnds = readVector<int>( 2 * n );

    auto allEndsCopy = allEnds;
    vector<size_t> forwardMap, backwardMap;
    sortWithMappings( allEndsCopy, &forwardMap, &backwardMap );

    std::vector<int> data( 2 * n );
    auto st = makeSegmentTree( data, plus<int>(), update_types::IncreaseBy<int>() );

    vector<int> res( n );
    for ( int i : range( 2 * n ) )
    {
        if ( backwardMap[i] % 2 == 1 ) // Segment end
        {
            auto segmentEnd = i;
            auto segmentStart = forwardMap[backwardMap[i] - 1];
            auto segmentInd = backwardMap[i] / 2;
            res[segmentInd] = st.getValueOnSegment( segmentStart, segmentEnd );
            st.updateElement( segmentStart, update_types::IncreaseBy<int>( 1 ) );
        }
    }

    printVector( res, "\n" );
}

class Solver652DTest : public ProblemTest {};

TEST_F(Solver652DTest, Example1)
{
    string input = R"(4
1 8
2 3
4 7
5 6
)";
    string output = R"(3
0
1
0
)";
    setInput(input);
    Solver652D().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}


TEST_F(Solver652DTest, Example2)
{
    string input = R"(3
3 4
1 5
2 6
)";
    string output = R"(0
1
1
)";
    setInput(input);
    Solver652D().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}


