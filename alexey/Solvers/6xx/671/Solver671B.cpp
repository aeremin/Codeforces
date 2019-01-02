#include <Solvers/pch.h>
#include "algo/io/baseio.hpp"
#include "iter/range.h"
#include "algo/io/readvector.hpp"
#include "algo/FunctorIterator.hpp"
using namespace std;

// Solution for Codeforces problem http://codeforces.com/contest/671/problem/B
class Solver671B {
public:
    void run();

    vector<int64_t> coins;
    vector<int64_t> coinsPrefixSums = { 0 };

    int64_t n;

    int64_t neededToSetMinTo(int v) const {
        int64_t r = lower_bound(begin(coins), end(coins), v) - begin(coins);
        int64_t s = coinsPrefixSums[r];
        return r * v - s;
    }


    int64_t neededToSetMaxTo(int v) const {
        int64_t l = upper_bound(begin(coins), end(coins), v) - begin(coins);
        int64_t s = coinsPrefixSums[n] - coinsPrefixSums[l];
        return s - (n - l) * v;
    }
};

void Solver671B::run() {
    int64_t k;
    cin >> n >> k;
    coins = readVector<int64_t>(n);
    int64_t s = 0;
    for (auto c : coins)
        s += c;

    sort(begin(coins), end(coins));
    partial_sum(begin(coins), end(coins), back_inserter(coinsPrefixSums));

    int64_t minConverge, maxConverge;
    if (s % n == 0)
        minConverge = maxConverge = s / n;
    else {
        minConverge = s / n;
        maxConverge = s / n + 1;
    }

    auto minFunctor = [&](int64_t v) ->int {return neededToSetMinTo(v) > k; };
    auto lMin = makeFunctorIterator(int64_t (-1), minFunctor);
    auto rMin = makeFunctorIterator(int64_t(2e9 + 1), minFunctor);
    auto minV = upper_bound(lMin, rMin, 0).getParameter() - 1;

    auto maxFunctor = [&](int64_t v) ->int {return neededToSetMaxTo(v) <= k; };
    auto lMax = makeFunctorIterator(int64_t (-1), maxFunctor);
    auto rMax = makeFunctorIterator(int64_t(2e9 + 1), maxFunctor);
    auto maxV = lower_bound(lMax, rMax, 1).getParameter();

    cout << max(maxConverge - minConverge, maxV  - minV);
}


class Solver671BTest : public ProblemTest {};


TEST_F(Solver671BTest, Example1) {
    string input = R"(4 1
1 1 4 2
)";
    string output = R"(2
)";
    setInput(input);
    Solver671B().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}

TEST_F(Solver671BTest, Example2) {
    string input = R"(3 1
2 2 2
)";
    string output = R"(0
)";
    setInput(input);
    Solver671B().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}

TEST_F(Solver671BTest, Example3) {
    string input = R"(3 100
1 2 2
)";
    string output = R"(1
)";
    setInput(input);
    Solver671B().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}

TEST_F(Solver671BTest, Example4) {
    string input = R"(4 7
1 2 8 9
)";
    string output = R"(0
)";
    setInput(input);
    Solver671B().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}

TEST_F(Solver671BTest, Example5) {
    string input = R"(1 100
66666
)";
    string output = R"(0
)";
    setInput(input);
    Solver671B().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}
