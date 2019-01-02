#include <Solvers/pch.h>
#include "algo/io/baseio.hpp"
#include "iter/range.h"
#include "algo/io/printvector.h"
using namespace std;

// Solution for Codeforces problem http://codeforces.com/contest/674/problem/B
class Solver674B {
public:
    void run();
};

void Solver674B::run() {
    int n, k;
    cin >> n >> k;
    if (n < 5 || k <= n) {
        cout << -1;
        return;
    }

    int a, b, c, d;
    cin >> a >> b >> c >> d;
    vector<int> mapping(n);
    mapping[0] = a;
    mapping[n - 1] = b;
    mapping[1] = c;
    mapping[n - 2] = d;
    int j = 1;
    for (int i : range(2, n - 2)) {
        while (j == a || j == b || j == c || j == d)
            ++j;
        mapping[i] = j;
        ++j;
    }


    vector<int> ans(n);
    iota(begin(ans), end(ans), 0);
    for (auto elt : ans)
        cout << mapping[elt] << ' ';
    cout << '\n';
    swap(ans[0], ans[1]);
    swap(ans[n - 1], ans[n - 2]);
    for (auto elt : ans)
        cout << mapping[elt] << ' ';
}


class Solver674BTest : public ProblemTest {};


TEST_F(Solver674BTest, Example1) {
    string input = R"(7 11
2 4 7 3
)";
    string output = R"(2 7 1 5 6 3 4 
7 2 1 5 6 4 3 
)";
    setInput(input);
    Solver674B().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}

TEST_F(Solver674BTest, Example2) {
    string input = R"(1000 999
10 20 30 40
)";
    string output = R"(-1
)";
    setInput(input);
    Solver674B().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}

