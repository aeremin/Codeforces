#include <Solvers/pch.h>
#include "algo/io/baseio.hpp"
#include "iter/range.h"
#include "algo/updatetypes/IncreaseBy.hpp"
#include "algo/binaryfunctors/Max.hpp"
#include "algo/updateappliers/IncreaseByIdempotent.h"
#include "algo/SegmentTree.hpp"
#include "algo/geometry/geomvector.hpp"

using namespace std;

// Solution for Codeforces problem http://codeforces.com/contest/377/problem/D
class Solver377D
{
public:
    void run();
};

void Solver377D::run()
{
    int nDevs;
    cin >> nDevs;
    vector<tuple<int, int, int, int>> devsRectangles;
    vector<tuple<int, int, int>> devs;
    for (auto i : range(nDevs)) {
        int l, v, r;
        cin >> l >> v >> r;
        devsRectangles.emplace_back(l, -1, v, r + 1);
        devsRectangles.emplace_back(v, +1, v, r + 1);
        devs.emplace_back(l, v, r);
    }

    sort(devsRectangles.rbegin(), devsRectangles.rend());

    const int maxCoordinate = 3 * 100000;
    vector<GeomVector2I> data(maxCoordinate + 1);
    for (int i : range(maxCoordinate + 1))
        data[i] = GeomVector2I({ 0, i });

    auto st = makeSegmentTree(data, binaryFunctors::Max<GeomVector2I>(), updateTypes::IncreaseBy<GeomVector2I>());
    int ans = 0;
    int bestL = -1;
    int bestR = -1;
    for (auto& d : devsRectangles) {
        st.updateRange(get<2>(d), get<3>(d), updateTypes::IncreaseBy<GeomVector2I>({ get<1>(d), 0 }));
        auto ansCand = st.getValueOnSegment(0, maxCoordinate + 1);
        if (ansCand[0] > ans) {
            ans = ansCand[0];
            bestL = get<0>(d);
            bestR = ansCand[1];
        }
    }

    cout << ans << '\n';
    for (int i : range(nDevs)) {
        auto& d = devs[i];
        if (get<0>(d) <= bestL && get<1>(d) >= bestL && get<1>(d) <= bestR && get<2>(d) >= bestR)
            cout << (i + 1) << " ";
    }
}

class Solver377DTest : public ProblemTest {};

TEST_F(Solver377DTest, Example1)
{
    string input = R"(4
2 8 9
1 4 7
3 6 8
5 8 10
)";
    string output = R"(3
1 3 4 )";
    setInput(input);
    Solver377D().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}


TEST_F(Solver377DTest, Example2)
{
    string input = R"(6
3 5 16
1 6 11
4 8 12
7 9 16
2 10 14
8 13 15
)";
    string output = R"(4
1 2 3 5 )";
    setInput(input);
    Solver377D().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}


