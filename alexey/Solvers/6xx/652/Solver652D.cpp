#include <Solvers/pch.h>
#include "algo/io/baseio.hpp"
#include "iter/range.h"
#include "algo/updatetypes/IncreaseBy.hpp"
#include "algo/updateappliers/IncreaseBySum.h"
#include "algo/SegmentTree.hpp"
#include "algo/io/readvector.hpp"
#include "algo/SortWithMapping.hpp"
#include "algo/io/printvector.h"
using namespace std;

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
    auto st = makeSegmentTree( data, plus<int>(), updateTypes::IncreaseBy<int>() );

    vector<int> res( n );
    for ( int i : range( 2 * n ) )
    {
        if ( backwardMap[i] % 2 == 1 ) // Segment end
        {
            auto segmentEnd = i;
            auto segmentStart = forwardMap[backwardMap[i] - 1];
            auto segmentInd = backwardMap[i] / 2;
            res[segmentInd] = st.getValueOnSegment( segmentStart, segmentEnd );
            st.updateElement( segmentStart, updateTypes::IncreaseBy<int>( 1 ) );
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
    output.pop_back();
    setInput(input);
    Solver652D().run();
    EXPECT_EQ(output, getOutput());
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
    output.pop_back();
    setInput(input);
    Solver652D().run();
    EXPECT_EQ(output, getOutput());
}


