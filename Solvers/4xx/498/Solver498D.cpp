#include <Solvers/pch.h>
#include "algo/updatetypes/SetTo.hpp"
#include "algo/updateappliers/SetToIdempotent.h"
#include "algo/SegmentTree.hpp"

using namespace std;

class Solver498D
{
public:
    void run();

    struct TimeToMove
    {
        int time[60];
    };

    TimeToMove constructFromPeriod(int period)
    {
        TimeToMove result;
        for (int t = 0; t < 60; ++t)
            result.time[t] = (t % period == 0) ? 2 : 1;
        return result;
    }
};

void Solver498D::run()
{
    int nRoads;
    cin >> nRoads;
    vector<TimeToMove> singleRoadTimes(nRoads);

    for (auto& singleTime : singleRoadTimes)
    {
        int period;
        cin >> period;
        singleTime = constructFromPeriod(period);
    }

    auto concatFunctor = [](const TimeToMove& first, const TimeToMove& second) -> TimeToMove
    {
        TimeToMove result;
        for (int t = 0; t < 60; ++t)
        {
            int firstTime = first.time[t];
            result.time[t] = firstTime + second.time[(t + firstTime) % 60];
        }
        return result;
    };

    auto timeTree = makeSegmentTree(singleRoadTimes, concatFunctor, updateTypes::SetTo<TimeToMove>());

    int nQueries;
    cin >> nQueries;
    for (int i = 0; i < nQueries; ++i)
    {
        char type;
        int a, b;
        cin >> type >> a >> b;
        if (type == 'A')
        {
            cout << timeTree.getValueOnSegment(a - 1, (b - 1)).time[0] << endl;
        }
        else
        {
            timeTree.updateElement(a - 1, updateTypes::SetTo<TimeToMove>(constructFromPeriod(b)));
        }
    }
}

class Solver498DTest : public ProblemTest
{
};

TEST_F(Solver498DTest, Example1)
{
    setInput(
        R"(10
2 5 3 2 3 5 3 4 2 4
10
C 10 6
A 2 6
A 1 3
C 3 4
A 3 11
A 4 9
A 5 6
C 7 3
A 8 10
A 2 5
)");
    Solver498D().run();
    string expectedRes =
R"(5
3
14
6
2
4
4
)";
    EXPECT_EQ(expectedRes, getOutput());
}
