#include <Solvers/pch.h>
#include "algo/io/baseio.hpp"
#include "iter/range.h"
#include "algo/io/readvector.hpp"
using namespace std;

// Solution for Codeforces problem http://codeforces.com/contest/675/problem/D
class Solver675D {
public:
    void run();
};

void Solver675D::run() {
    auto n = read<int>();
    auto a = readVector<int>(n);
    map<int, int> sprouts = { {numeric_limits<int>::min(), a[0]}, {a[0], a[0] } };
    for (int i : range(1, n)) {
        auto elt = a[i];
        auto it = prev(sprouts.upper_bound(elt));
        cout << it->second << ' ';
        auto l = it->first;
        sprouts.erase(it);
        sprouts.emplace(l, elt);
        sprouts.emplace(elt, elt);
    }
}


class Solver675DTest : public ProblemTest {};


TEST_F(Solver675DTest, Example1) {
    string input = R"(3
1 2 3
)";
    string output = R"(1 2 
)";
    setInput(input);
    Solver675D().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}

TEST_F(Solver675DTest, Example2) {
    string input = R"(5
4 2 3 1 6
)";
    string output = R"(4 2 2 4 
)";
    setInput(input);
    Solver675D().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}

