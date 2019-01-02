#include <Solvers/pch.h>
#include "algo/io/baseio.hpp"
#include "algo/updatetypes/IncreaseBy.hpp"
#include "algo/updateappliers/IncreaseBySum.h"
#include "algo/SegmentTree.hpp"
#include "iter/range.h"
#include "algo/io/printvector.h"

using namespace std;

// Solution for Codeforces problem http://codeforces.com/contest/627/problem/B
class Solver627B
{
public:
    void run();
};

void Solver627B::run()
{
    int nDays, repairLen, produceBeforeRepair, produceAfterRepair, nQueries;
    cin >> nDays >> repairLen >> produceAfterRepair >> produceBeforeRepair >> nQueries;
    vector<int> result;
    vector<int> nRequests(nDays, 0);
    auto streeBefore = makeSegmentTree(nRequests, plus<int>(), updateTypes::IncreaseBy<int>());
    auto streeAfter = makeSegmentTree(nRequests, plus<int>(), updateTypes::IncreaseBy<int>());
    for (int i : range(nQueries))
    {
        int t;
        cin >> t;
        if (t == 1)
        {
            int d, a;
            cin >> d >> a;
            --d;
            auto currBefore = streeBefore.getValueOnSegment(d, d + 1);
            auto incrBefore = min(a, produceBeforeRepair - currBefore);
            streeBefore.updateElement(d, updateTypes::IncreaseBy<int>(incrBefore));
         
            auto currAfter = streeAfter.getValueOnSegment(d, d + 1);
            auto incrAfter = min(a, produceAfterRepair - currAfter);
            streeAfter.updateElement(d, updateTypes::IncreaseBy<int>(incrAfter));
        }
        else
        {
            int p;
            cin >> p;
            --p;
            auto fullfillBeforeRepair = (p > 0) ? streeBefore.getValueOnSegment(0, p) : 0;
            auto fullfillAfterRepair = (nDays > p + repairLen) ? streeAfter.getValueOnSegment(p + repairLen, nDays) : 0;
            result.push_back(fullfillBeforeRepair + fullfillAfterRepair);
        }
    }
    printVector(result, "\n");
}

class Solver627BTest : public ProblemTest {};

TEST_F(Solver627BTest, Example1)
{
    string input = R"(5 2 2 1 8
1 1 2
1 5 3
1 2 1
2 2
1 4 2
1 3 2
2 1
2 3
)";
    string output = R"(3
6
4
)";
    setInput(input);
    Solver627B().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}


TEST_F(Solver627BTest, Example2)
{
    string input = R"(5 4 10 1 6
1 1 5
1 5 5
1 3 2
1 5 2
2 1
2 2
)";
    string output = R"(7
1
)";
    setInput(input);
    Solver627B().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}


