#include <Solvers/pch.h>
#include "algo/io/baseio.hpp"
#include "algo/SortWithMapping.hpp"
#include "algo/pi.hpp"
#include "algo/Range.hpp"
#include "algo/binaryfunctors/Max.hpp"
#include "algo/updatetypes/SetTo.hpp"
#include "algo/updateappliers/SetToIdempotent.h"
#include "algo/SegmentTree.hpp"
using namespace std;

class Solver629D
{
public:
    void run();
};

void Solver629D::run()
{
    int n;
    cin >> n;
    vector<int64_t> vol = {0};
    for (int i : range(n))
    {
        int64_t r, h;
        cin >> r >> h;
        vol.push_back(r * r * h);
    }
    
    vector<size_t> forwardMap;
    auto volCopy = vol;
    sortWithMappings(volCopy, &forwardMap, nullptr);
    
    vector<int64_t> data(n + 1, std::numeric_limits<int64_t>::min());
    data[0] = 0;
    auto segmentTree = makeSegmentTree(data, binaryFunctors::Max<int64_t>(), updateTypes::SetTo<int64_t>());
    for (int i : range(1, n + 1))
    {
        auto currOrder = forwardMap[i];
        auto cntSmaller = lower_bound(begin(volCopy), end(volCopy), vol[i]) - begin(volCopy);
        auto maxSumV = segmentTree.getValueOnSegment(0, cntSmaller);
        maxSumV += vol[i];
        segmentTree.updateElement(currOrder, maxSumV);
    }
    auto ans = segmentTree.getValueOnSegment(0, n + 1);
    cout << setprecision(9) << fixed << cPi * ans;
}

class Solver629DTest : public ProblemTest {};

TEST_F(Solver629DTest, Example1)
{
    string input = R"(2
100 30
40 10
)";
    string output = R"(942477.796076938
)";
    output.pop_back();
    setInput(input);
    Solver629D().run();
    EXPECT_EQ(output, getOutput());
}


TEST_F(Solver629DTest, Example2)
{
    string input = R"(4
1 1
9 7
1 4
10 7
)";
    string output = R"(3983.539484752
)";
    output.pop_back();
    setInput(input);
    Solver629D().run();
    EXPECT_EQ(output, getOutput());
}

TEST_F(Solver629DTest, SamePies)
{
    string input = R"(4
1 1
1 1
1 1
1 1
)";
    string output = R"(3.141592654
)";
    output.pop_back();
    setInput(input);
    Solver629D().run();
    EXPECT_EQ(output, getOutput());
}
