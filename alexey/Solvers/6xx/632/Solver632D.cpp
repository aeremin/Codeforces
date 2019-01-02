#include <Solvers/pch.h>
#include "algo/io/baseio.hpp"
#include "iter/range.h"
#include "algo/io/readvector.hpp"
using namespace std;

// Solution for Codeforces problem http://codeforces.com/contest/632/problem/D
class Solver632D {
public:
    void run();
};

void Solver632D::run() {
    int n = read<int>();
    int m = read<int>();
    auto nums = readVector<int>(n);
    vector<int> numsCount(m + 1, 0), divisorsCount(m + 1, 0);
    for (auto num : nums)
        if (num <= m)
            ++numsCount[num];
    for (int multiplier : range(1, m + 1))
        for (int i : range(1, m / multiplier + 1))
            divisorsCount[i * multiplier] += numsCount[i];

    auto maxIter = max_element(begin(divisorsCount) + 1, end(divisorsCount));
    auto bestLCM = maxIter - begin(divisorsCount);
    cout << bestLCM << " " << *maxIter << "\n";
    for (auto i : range(n))
        if (bestLCM % nums[i] == 0)
            cout << (i + 1) << " ";
}

class Solver632DTest : public ProblemTest {};

TEST_F(Solver632DTest, Example1) {
    string input = R"(7 8
6 2 9 2 7 2 3
)";
    string output = R"(6 5
1 2 4 6 7 )";
    setInput(input);
    Solver632D().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}


TEST_F(Solver632DTest, Example2) {
    string input = R"(6 4
2 2 2 3 3 3
)";
    string output = R"(2 3
1 2 3 )";
    setInput(input);
    Solver632D().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}


