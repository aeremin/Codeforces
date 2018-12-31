#include <Solvers/pch.h>
#include "algo/io/baseio.hpp"
#include "iter/range.h"
#include "algo/io/readvector.hpp"
using namespace std;

class Solver670B {
public:
    void run();
};

void Solver670B::run() {
    int64_t n, k;
    cin >> n >> k;
    auto ids = readVector<int>(n);
    for (int64_t i : range(n)) {
        if ((i + 1) * (i + 2) >= 2 * k) {
            int ind = k - i * (i + 1) / 2;
            cout << ids[ind - 1];
            return;
        }
    }
}


class Solver670BTest : public ProblemTest {};


TEST_F(Solver670BTest, Example1) {
    string input = R"(2 2
1 2
)";
    string output = R"(1
)";
    setInput(input);
    Solver670B().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}

TEST_F(Solver670BTest, Example2) {
    string input = R"(4 5
10 4 18 3
)";
    string output = R"(4
)";
    setInput(input);
    Solver670B().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}

TEST_F(Solver670BTest, Example3) {
    string input = R"(4 10
1 2 3 4
)";
    string output = R"(4
)";
    setInput(input);
    Solver670B().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}
