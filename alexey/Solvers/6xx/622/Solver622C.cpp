#include <Solvers/pch.h>
#include "algo/updatetypes/Id.hpp"
#include "algo/updateappliers/IdApplier.hpp"
#include "algo/SegmentTree.hpp"

using namespace std;

class Solver622C
{
public:
    void run();

    struct MinMaxData
    {
        int m, M;
        int i, I;
    };
};

void Solver622C::run()
{
    int n, m;
    cin >> n >> m;
    vector<MinMaxData> data(n);
    for (int i = 0; i < n; ++i)
    {
        int v;
        cin >> v;
        auto& ref = data[i];
        ref.m = ref.M = v;
        ref.i = ref.I = i;
    }

    auto concat = [](const MinMaxData& lh, const MinMaxData& rh) -> MinMaxData
    {
        MinMaxData res;
        auto& minArg = (lh.m < rh.m) ? lh : rh;
        res.m = minArg.m;
        res.i = minArg.i;

        auto& maxArg = (lh.M > rh.M) ? lh : rh;
        res.M = maxArg.M;
        res.I = maxArg.I;
        return res;
    };

    auto stree = makeSegmentTree(data, concat, updateTypes::Id());

    for (int i = 0; i < m; ++i)
    {
        int l, r, x;
        cin >> l >> r >> x;
        --l;
        auto minMaxData = stree.getValueOnSegment(l, r);
        int pos = -1;
        if (minMaxData.m != x)
            pos = minMaxData.i + 1;
        else if (minMaxData.M != x)
            pos = minMaxData.I + 1;
        cout << pos << "\n";
    }
}

class Solver622CTest : public ProblemTest {};

TEST_F(Solver622CTest, Example1)
{
    string input = R"(6 4
1 2 1 1 3 5
1 4 1
2 6 2
3 4 1
3 4 2
)";
    string output = R"(2
4
-1
4
)";
    setInput(input);
    Solver622C().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}


TEST_F(Solver622CTest, MaxTest)
{
    stringstream ss;
    int maxSize = 200000;
    ss << maxSize << " " << maxSize << "\n";
    for (int i = 0; i < maxSize; ++i)
        ss << "1 ";
    
    for (int i = 0; i < maxSize; ++i)
        ss << 1 << " " << maxSize << " " << 1 << " ";

    setInput(ss.str());
    Solver622C().run();
}
