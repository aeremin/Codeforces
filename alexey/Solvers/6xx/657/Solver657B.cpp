#include <Solvers/pch.h>
#include "algo/io/baseio.h"
#include "iter/range.h"
#include "algo/io/readvector.h"
using namespace std;

// Solution for Codeforces problem http://codeforces.com/contest/657/problem/B
class Solver657B
{
public:
    void run();
};

void Solver657B::run() {
    int64_t deg, k;
    cin >> deg >> k;
    auto a = readVector<int64_t>(deg + 1);
    vector<int64_t> b(deg + 100);
    for (int i : range(deg + 1)) {
        int64_t ai = a[i];
        int j = i;
        if (ai < 0) {
            ai += (1ll << 50);
            b[j + 50]--;
        }
        while (ai) {
            ai += b[j];
            b[j] = 0;
            if (ai % 2) {
                b[j]++;
                --ai;
            }
            ai /= 2;
            ++j;
        }
    }

    int maxPowerOfTwo = 0;
    for (; b[maxPowerOfTwo] == 0; ++maxPowerOfTwo) {}

    int ans = 0;
    for (int i = b.size() - 1; i > maxPowerOfTwo; --i) {
        b[i - 1] += 2 * b[i];
        b[i] = 0;
        if (abs(b[i - 1]) > 3 * k) {
            cout << 0;
            return;
        }
    }

    int64_t val = b[maxPowerOfTwo];
    for (int i = maxPowerOfTwo; i >= 0; --i) {
        if (abs(a[i] - val) <= k && !(a[i] == val && i == deg))
            ++ans;
        val *= 2;
        if (abs(val) > 3 * k)
            break;
    }

    cout << ans;
}

class Solver657BTest : public ProblemTest {};

TEST_F(Solver657BTest, Example1)
{
    string input = R"(3 1000000000
10 -9 -3 5
)";
    string output = R"(3
)";
    setInput(input);
    Solver657B().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}


TEST_F(Solver657BTest, Example2)
{
    string input = R"(3 12
10 -9 -3 5
)";
    string output = R"(2
)";
    setInput(input);
    Solver657B().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}


TEST_F(Solver657BTest, Example3)
{
    string input = R"(2 20
14 -7 19
)";
    string output = R"(0
)";
    setInput(input);
    Solver657B().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}

TEST_F(Solver657BTest, Example4) {
    string input = R"(3 1000000000
-10 9 3 -5
)";
    string output = R"(3
)";
    setInput(input);
    Solver657B().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}

TEST_F(Solver657BTest, Example5) {
    string input = R"(80 63
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 -1
)";
    string output = R"(5
)";
    setInput(input);
    Solver657B().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}