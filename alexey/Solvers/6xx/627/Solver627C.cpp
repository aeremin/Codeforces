#include <Solvers/pch.h>

#include "algo/segment_tree/binary_functors/min.h"
#include "algo/io/baseio.h"
#include "algo/segment_tree/segment_tree.h"
#include "algo/segment_tree/update_appliers/id_applier.h"
#include "algo/segment_tree/update_types/id.h"
#include "iter/range.h"

using namespace std;

// Solution for Codeforces problem http://codeforces.com/contest/627/problem/C
class Solver627C {
public:
    void run();
};

void Solver627C::run() {
    int64_t distance, maxFuel, nFuelStations;
    cin >> distance >> maxFuel >> nFuelStations;
    deque<pair<int64_t, int64_t>> fuelStations(nFuelStations);
    for (auto& p : fuelStations)
        cin >> p.first >> p.second;

    fuelStations.push_back({ distance, numeric_limits<int64_t>::max() });
    ++nFuelStations;

    fuelStations.push_front({ 0, numeric_limits<int64_t>::max() });
    ++nFuelStations;

    sort(begin(fuelStations), end(fuelStations));

    vector<pair<int64_t, int>> minPriceData(nFuelStations);
    for (int i : range(nFuelStations))
        minPriceData[i] = make_pair(fuelStations[i].second, i);

    auto stree = makeSegmentTree(minPriceData, binary_functors::Min<pair<int64_t, int>>(), update_types::Id());

    std::function<int64_t(int, int)> getMinPrice = [&](int l, int r) -> int64_t {
        if (r - l == 1)
            return (fuelStations[r].first - fuelStations[l].first <= maxFuel) ? 0 : -1;
        auto minStationIndex = stree.getValueOnSegment(l + 1, r).second;
        auto haveFuelAfterMinStation = min(maxFuel, fuelStations[r].first - fuelStations[minStationIndex].first);
        auto haveFuelBeforeMinStation = max<int64_t>(0, maxFuel - fuelStations[minStationIndex].first + fuelStations[l].first);
        auto buyFuelOnMinStation = max<int64_t>(0, haveFuelAfterMinStation - haveFuelBeforeMinStation);
        auto minPriceLeft = getMinPrice(l, minStationIndex);
        auto minPriceRight = getMinPrice(minStationIndex, r);
        if (minPriceRight == -1 || minPriceLeft == -1)
            return -1;

        return buyFuelOnMinStation * fuelStations[minStationIndex].second + minPriceLeft + minPriceRight;
    };

    cout << getMinPrice(0, nFuelStations - 1);
}

class Solver627CTest : public ProblemTest {};

TEST_F(Solver627CTest, Example1) {
    string input = R"(10 4 4
3 5
5 8
6 3
8 4
)";
    string output = R"(22
)";
    output.pop_back();
    setInput(input);
    Solver627C().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}


TEST_F(Solver627CTest, Example2) {
    string input = R"(16 5 2
8 2
5 1
)";
    string output = R"(-1
)";
    output.pop_back();
    setInput(input);
    Solver627C().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}


