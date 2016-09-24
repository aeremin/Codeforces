#include <Solvers/pch.h>
#include "algo/io/baseio.hpp"
#include "iter/range.h"
#include "algo/io/readvector.hpp"
#include "util/relax.h"
using namespace std;

class Solver657C
{
public:
    void run();
   
    int64_t dist(int64_t x, int64_t y) const {
        if (x > y) return numeric_limits<int64_t>::max() / 10;
        if (b >= 5 * c) return c * (y - x);
        return (y - x) / 5 * b + ((y - x) % 5) * c;
    }

    int64_t n, k, b, c;
    
    struct BestSet {
        multiset<int64_t> numbersTaken;
        int64_t totalTime = 0;
        int64_t equalityValue;
    };
    
    BestSet bestSets[5];
    int64_t currOffset;

    int64_t ans = numeric_limits<int64_t>::max();

    int64_t mod(int64_t a, int64_t d) {
        auto res = a % d;
        if (res < 0) res += d;
        return res;
    }

    void tryToAdd(int64_t a) {
        for (auto nextEqValue : range(a, a + 5) ) {
            int64_t ind = mod(nextEqValue, 5);
            bestSets[ind].totalTime += min(b, 5 * c) * k * (nextEqValue - bestSets[ind].equalityValue) / 5;
            bestSets[ind].equalityValue = nextEqValue;
            int64_t bestImprovement = 0;
            int64_t bestRemove = a;
            int64_t minInSet = *begin(bestSets[ind].numbersTaken);
            for (int64_t toRemove : range(minInSet, minInSet + 5)) {
                if (bestSets[ind].numbersTaken.count(toRemove)) {
                    auto improvement = dist(bestRemove, nextEqValue) - dist(toRemove, nextEqValue);
                    if (improvement < 0)
                        bestRemove = toRemove;
                }
            }
            bestSets[ind].totalTime += dist(a, nextEqValue) - dist(bestRemove, nextEqValue);
            bestSets[ind].numbersTaken.insert(a);
            bestSets[ind].numbersTaken.erase(bestSets[ind].numbersTaken.find(bestRemove));
            relax_min(ans, bestSets[ind].totalTime);
        }
    }
};

void Solver657C::run()
{
    cin >> n >> k >> b >> c;
    auto r = readVector<int64_t>(n);
    sort(begin(r), end(r));

    multiset<int64_t> currSet(begin(r), begin(r) + k);
    currOffset = *(begin(r) + k - 1);
    for (int64_t j : range(5)) {
        int64_t cand = currOffset + j;
        int64_t ind = mod(cand, 5);
        for (auto elt : currSet)
            bestSets[ind].totalTime += dist(elt, cand);
        bestSets[ind].numbersTaken = currSet;
        bestSets[ind].equalityValue = cand;
        relax_min(ans, bestSets[ind].totalTime);
    }

    for (auto i = k; i < n; ++i)
        tryToAdd(r[i]);

    cout << ans;
}

class Solver657CTest : public ProblemTest {};

TEST_F(Solver657CTest, Example1)
{
    string input = R"(4 3 100 30
12 2 6 1
)";
    string output = R"(220
)";
    output.pop_back();
    setInput(input);
    Solver657C().run();
    EXPECT_EQ(output, getOutput());
}


TEST_F(Solver657CTest, Example2)
{
    string input = R"(4 3 30 100
12 2 6 1
)";
    string output = R"(190
)";
    output.pop_back();
    setInput(input);
    Solver657C().run();
    EXPECT_EQ(output, getOutput());
}


TEST_F(Solver657CTest, Example3)
{
    string input = R"(6 2 987 789
-8 42 -4 -65 -8 -8
)";
    string output = R"(0
)";
    output.pop_back();
    setInput(input);
    Solver657C().run();
    EXPECT_EQ(output, getOutput());
}


