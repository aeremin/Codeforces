#include <Solvers/pch.h>
#include "algo/io/baseio.hpp"
#include "iter/range.h"
#include "algo/io/readvector.hpp"
#include "util/relax.h"
using namespace std;

// Solution for Codeforces problem http://codeforces.com/contest/675/problem/C
class Solver675C {
public:
    void run();
};

void Solver675C::run() {
    auto n = read<int>();
    auto a = readVector<int64_t>(n);
    for (int i : range(n))
        a.push_back(a[i]);

    vector<int> jump(2 * n);

    int64_t s = 0;
    map<int64_t, int> sumToInd;
    for (int i : range(2 * n)) {
        auto elt = a[i];
        sumToInd.emplace(s, i);
        s += elt;
        auto it = sumToInd.find(s);
        if (it != end(sumToInd)) {
            auto ind = it->second;
            jump[ind] = i + 1;
            sumToInd.erase(it);
        }
    }

    int maxZeroParts = 0;
    vector<bool> used(2 * n);
    for (int i : range(n)) {
        if (used[i])
            continue;

        used[i] = true;
        int j = i;
        int steps = 0;
        while (j < i + n) {
            j = jump[j];
            used[j] = true;
            ++steps;
        }

        relax_max(maxZeroParts, steps);
    }

    cout << n - maxZeroParts;
}


class Solver675CTest : public ProblemTest {};


TEST_F(Solver675CTest, Example1) {
    string input = R"(3
5 0 -5
)";
    string output = R"(1
)";
    setInput(input);
    Solver675C().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}

TEST_F(Solver675CTest, Example2) {
    string input = R"(4
-1 0 1 0
)";
    string output = R"(2
)";
    setInput(input);
    Solver675C().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}

TEST_F(Solver675CTest, Example3) {
    string input = R"(4
1 2 3 -6
)";
    string output = R"(3
)";
    setInput(input);
    Solver675C().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}

