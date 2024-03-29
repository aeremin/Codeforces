#include <Solvers/pch.h>

#include "algo/sort_with_mapping.h"
#include "algo/segment_tree/binary_functors/max.h"
#include "algo/segment_tree/segment_tree.h"
#include "algo/segment_tree/update_appliers/set_to_idempotent.h"
#include "algo/segment_tree/update_types/set_to.h"
#include "util/relax.h"

using namespace std;

// Solution for Codeforces problem http://codeforces.com/contest/474/problem/E
class Solver474E
{
public:
    void run();
};



void Solver474E::run()
{
    size_t nHeights;
    cin >> nHeights;
    int64_t minAllowedDiff;
    cin >> minAllowedDiff;
    vector<int64_t> heights(nHeights);
    for (auto& h : heights)
        cin >> h;

    heights.push_back(int64_t(1) << 60);

    auto sortedHeights = heights;
    vector<size_t> forwardMapping;
    sortWithMappings(sortedHeights, &forwardMapping, nullptr);

    vector<int> predecessors(heights.size());
    vector<pair<int, int>> maxJumpCountAndPredecessor(heights.size(), make_pair(0, -1));
    auto segmentTree = makeSegmentTree(maxJumpCountAndPredecessor, binary_functors::Max<pair<int, int>>(),
                                       update_types::SetTo<pair<int, int>>());
    auto segmentTreeBegin = begin(maxJumpCountAndPredecessor);
    for (size_t i = 0; i < heights.size(); ++i)
    {
        auto currH = heights[i];
        auto l = lower_bound(begin(sortedHeights), end(sortedHeights), currH - minAllowedDiff + 1);
        auto r = lower_bound(begin(sortedHeights), end(sortedHeights), currH + minAllowedDiff);
        auto currMax = make_pair(1, -1);
        if (l > begin(sortedHeights))
        {
            auto maxL = segmentTree.getValueOnSegment(0, l - begin(sortedHeights));
            maxL.first++;
            relax_max(currMax, maxL);
        }
        if (r < end(sortedHeights))
        {
            auto maxR = segmentTree.getValueOnSegment(r - begin(sortedHeights), maxJumpCountAndPredecessor.size());
            maxR.first++;
            relax_max(currMax, maxR);
        }
        predecessors[i] = currMax.second;
        maxJumpCountAndPredecessor[forwardMapping[i]] = { currMax.first, i };
        auto upd = update_types::SetTo<pair<int, int>>(make_pair(currMax.first, int(i)));
        segmentTree.updateElement(forwardMapping[i], upd);
    }

    deque<size_t> ans;
    size_t i = heights.size() - 1;
    while (predecessors[i] != -1)
    {
        ans.push_front(predecessors[i]);
        i = ans.front();
    }

    cout << ans.size() << "\n";
    for (auto& a : ans)
        cout << (a + 1) << " ";

}

class Solver474ETest : public ProblemTest
{
};

TEST_F( Solver474ETest, Example1 )
{
    setInput("5 2        1 3 6 7 4");
    Solver474E().run();
    EXPECT_EQ("4\n1 2 4 5 ", getOutput());
}

TEST_F( Solver474ETest, Example2 )
{
    setInput("10 3        2 1 3 6 9 11 7 3 20 18");
    Solver474E().run();
    EXPECT_EQ("6\n3 4 6 7 8 10 ", getOutput());
}

TEST_F(Solver474ETest, AllEqualZeroJumpAllowed)
{
    setInput("10 0        5 5 5 5 5 5 5 5 5 5");
    Solver474E().run();
    EXPECT_EQ("10\n1 2 3 4 5 6 7 8 9 10 ", getOutput());
}

TEST_F(Solver474ETest, AllEqualZeroJumpNotAllowed)
{
    setInput("10 1        5 5 5 5 5 5 5 5 5 5");
    Solver474E().run();
    EXPECT_EQ("1\n10 ", getOutput());
}