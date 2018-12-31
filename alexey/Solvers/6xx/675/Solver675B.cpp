#include <Solvers/pch.h>
#include "algo/io/baseio.hpp"
#include "iter/range.h"
using namespace std;

class Solver675B {
public:
    void run();
};

void Solver675B::run() {
    int64_t n, a, b, c, d;
    cin >> n >> a >> b >> c >> d;
    auto l = { a + c, c + d, d + b, b + a };
    auto m = min(l);
    auto M = max(l);
    cout << n * max<int64_t>(0, n - (M - m));
}


class Solver675BTest : public ProblemTest {};


TEST_F(Solver675BTest, Example1) {
    string input = R"(2 1 1 1 2
)";
    string output = R"(2
)";
    setInput(input);
    Solver675B().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}

TEST_F(Solver675BTest, Example2) {
    string input = R"(3 3 1 2 3
)";
    string output = R"(6
)";
    setInput(input);
    Solver675B().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}

