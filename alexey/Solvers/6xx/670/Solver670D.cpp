#include <Solvers/pch.h>
#include "algo/io/baseio.h"
#include "iter/range.h"
#include "algo/io/readvector.h"
#include "algo/functor_iterator.h"
using namespace std;

// Solution for Codeforces problem http://codeforces.com/contest/670/problem/D
class Solver670D {
public:
    void run();
};

void Solver670D::run() {
    int n;
    cin >> n;

    int64_t cntMagic;
    cin >> cntMagic;

    auto cntNeeded = readVector<int64_t>(n);
    auto cntHas = readVector<int64_t>(n);

    auto canCook = [&](int k) -> int {
        int64_t needMagic = 0;
        for (int i : range(n)) {
            needMagic += max<int64_t>(0, cntNeeded[i] * k - cntHas[i]);
            if (needMagic > cntMagic) return 1;
        }

        return 0;
    };

    auto l = makeFunctorIterator(0, canCook);
    auto r = makeFunctorIterator(int(2e9 + 2), canCook);

    auto it = lower_bound(l, r, 1);

    cout << it.getParameter() - 1;
}


class Solver670DTest : public ProblemTest {};

TEST_F(Solver670DTest, Example1) {
    string input = R"(1 1000000000
1
1000000000
)";
    string output = R"(2000000000
)";
    setInput(input);
    Solver670D().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}

TEST_F(Solver670DTest, Example2) {
    string input = R"(10 1
1000000000 1000000000 1000000000 1000000000 1000000000 1000000000 1000000000 1000000000 1000000000 1000000000
1 1 1 1 1 1 1 1 1 1
)";
    string output = R"(0
)";
    setInput(input);
    Solver670D().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}

TEST_F(Solver670DTest, Example3) {
    string input = R"(3 1
2 1 4
11 3 16
)";
    string output = R"(4
)";
    setInput(input);
    Solver670D().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}

TEST_F(Solver670DTest, Example4) {
    string input = R"(4 3
4 3 5 6
11 12 14 20
)";
    string output = R"(3
)";
    setInput(input);
    Solver670D().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}

