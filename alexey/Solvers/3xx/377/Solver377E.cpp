#include <Solvers/pch.h>
#include "algo/io/baseio.hpp"
#include "iter/range.h"
#include "algo/geometry/geomvector.hpp"
using namespace std;

class Solver377E
{
public:
    void run();

    class LinearFunctionsMaximum {
    public:
        void addLinearFunction(GeomVector2I64 start, int64_t k) {
            bool biggerThanLast = false;
            GeomVector2I64 offsettedStart = start;
            while (functions_.size() > 0) {
                auto lastK = functions_.back().second;
                auto lastStart = functions_.back().first;
                auto x = divRoundingUp(lastStart[1] - start[1] + start[0] * k - lastStart[0] * lastK, k - lastK);
                offsettedStart = start + GeomVector2I64(1, k) * (x - start[0]);
                if (offsettedStart[0] > lastStart[0])
                    break;
                functions_.pop_back();
            }
            functions_.emplace_back(offsettedStart, k);
        }

        GeomVector2I64 getMinXAndYByY(int64_t y) const {
            auto compareByY = [](const pair<GeomVector2I64, int64_t>& lh, const pair<GeomVector2I64, int64_t>& rh) {
                return lh.first[1] < rh.first[1];
            };
            auto it = upper_bound(begin(functions_), end(functions_), make_pair(GeomVector2I64(0, y), 0), compareByY);
            auto f = *(it - 1);
            auto res = f.first + divRoundingUp(y - f.first[1], f.second) * GeomVector2I64(1, f.second);
            if (it != end(functions_) && it->first[0] <= res[0])
                res = it->first;
            return res;
        }

    private:
        int64_t divRoundingUp(int64_t a, int64_t b) const {
            return (a + b - 1) / b;
        }

        vector<pair<GeomVector2I64, int64_t>> functions_;
    };

};

void Solver377E::run() {
    int nBuildings = read<int>();
    int64_t expectedMoney = read<int64_t>();
    vector<pair<int64_t, int64_t>> allBuildings(nBuildings);
    for (auto& b : allBuildings)
        cin >> b.first >> b.second;

    auto cmpByPriceThanByQuantityGenerated = [](const pair<int64_t, int64_t>& lh, const pair<int64_t, int64_t>& rh) {
        if (lh.second < rh.second)
            return true;
        if (lh.second > rh.second)
            return false;
        return (lh.first > rh.first);
    };

    sort(begin(allBuildings), end(allBuildings), cmpByPriceThanByQuantityGenerated);
    vector<pair<int64_t, int64_t>> interestingBuildings = { allBuildings.front() };
    for (int i : range(1, nBuildings))
        if (allBuildings[i].first > interestingBuildings.back().first)
            interestingBuildings.push_back(allBuildings[i]);

    LinearFunctionsMaximum lfm;
    for (auto b : interestingBuildings) {
        GeomVector2I64 minPointToBuy(0, 0);
        if (b.second > 0) {
            minPointToBuy = lfm.getMinXAndYByY(b.second);
            minPointToBuy[1] -= b.second;
        }
        lfm.addLinearFunction(minPointToBuy, b.first);
    }

    cout << lfm.getMinXAndYByY(expectedMoney)[0];
}

class Solver377ETest : public ProblemTest {};

TEST_F(Solver377ETest, Example1)
{
    string input = R"(3 9
1 0
2 3
5 4
)";
    string output = R"(6
)";
    output.pop_back();
    setInput(input);
    Solver377E().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}


TEST_F(Solver377ETest, Example2)
{
    string input = R"(3 6
1 0
2 2
5 4
)";
    string output = R"(5
)";
    output.pop_back();
    setInput(input);
    Solver377E().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}


TEST_F(Solver377ETest, Example3)
{
    string input = R"(3 13
1 0
2 2
6 5
)";
    string output = R"(7
)";
    output.pop_back();
    setInput(input);
    Solver377E().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}


TEST_F(Solver377ETest, Example4)
{
    string input = R"(1 10000000000000000
1 0
)";
    string output = R"(10000000000000000
)";
    output.pop_back();
    setInput(input);
    Solver377E().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}


TEST_F(Solver377ETest, Example5) {
    string input = R"(3 10
1 0
2 0
5 0
)";
    string output = R"(2
)";
    output.pop_back();
    setInput(input);
    Solver377E().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}

TEST_F(Solver377ETest, Example6) {
    string input = R"(3 90
1 0
6 3
88 4
)";
    string output = R"(5
)";
    output.pop_back();
    setInput(input);
    Solver377E().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}
