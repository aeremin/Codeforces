#include <Solvers/pch.h>

#include "algo/sort_with_mapping.h"
#include "algo/segment_tree/binary_functors/max.h"
#include "algo/io/baseio.h"
#include "algo/segment_tree/segment_tree.h"
#include "algo/segment_tree/update_appliers/set_to_idempotent.h"
#include "algo/segment_tree/update_types/set_to.h"
#include "iter/range.h"
#include "math/pi.h"
using namespace std;

// Solution for Codeforces problem http://codeforces.com/contest/629/problem/D
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
    auto segmentTree = makeSegmentTree(data, binary_functors::Max<int64_t>(), update_types::SetTo<int64_t>());
    for (int i : range(1, n + 1))
    {
        auto currOrder = forwardMap[i];
        auto cntSmaller = lower_bound(begin(volCopy), end(volCopy), vol[i]) - begin(volCopy);
        auto maxSumV = segmentTree.getValueOnSegment(0, cntSmaller);
        maxSumV += vol[i];
        segmentTree.updateElement(currOrder, maxSumV);
    }
    auto ans = segmentTree.getValueOnSegment(0, n + 1);
    cout << setprecision(9) << fixed << kPi * ans;
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
    setInput(input);
    Solver629D().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
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
    setInput(input);
    Solver629D().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
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
    setInput(input);
    Solver629D().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}
