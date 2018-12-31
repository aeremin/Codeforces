#include <Solvers/pch.h>
#include "algo/io/baseio.hpp"
#include "iter/range.h"
#include "algo/io/readvector.hpp"
using namespace std;

class Solver665B {
public:
    void run();
};

void Solver665B::run() {
    int nBuyers, goodsPerBuyer, totalGoods;
    cin >> nBuyers >> goodsPerBuyer >> totalGoods;
    vector<int> pos(totalGoods);
    for (int i : range(totalGoods)) {
        int g;
        cin >> g;
        pos[g - 1] = i + 1;
    }

    int64_t ans = 0;
    for (int iBuyer : range(nBuyers)) {
        auto goods = readVector<int>(goodsPerBuyer);
        for (auto g : goods) {
            int currPos = pos[g - 1];
            ans += currPos;
            for (auto f : range(totalGoods))
                if (pos[f] < currPos)
                    ++pos[f];
            pos[g - 1] = 1;
        }
    }
    cout << ans;
}


class Solver665BTest : public ProblemTest {};


TEST_F(Solver665BTest, Example1) {
    string input = R"(2 2 5
3 4 1 2 5
1 5
3 1
)";
    string output = R"(14
)";
    setInput(input);
    Solver665B().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}
