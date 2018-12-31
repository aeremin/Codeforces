#include <Solvers/pch.h>

using namespace std;

class Solver598A
{
public:
    void run();

    int64_t maxPowerOfTwo(int64_t n)
    {
        int p = 0;
        while ((int64_t(1) << p) <= n)
            ++p;
        return (int64_t(1) << (p - 1));
    }
};

void Solver598A::run()
{
    int nTests;
    cin >> nTests;
    for (int i = 0; i < nTests; ++i)
    {
        int64_t n;
        cin >> n;
        cout << (n * (n + 1) / 2 - 2 * (2 * maxPowerOfTwo(n) - 1)) << "\n";
    }
}

class Solver598ATest : public ProblemTest {};

TEST_F(Solver598ATest, Example1)
{
    string input = R"(2
4
1000000000
)";
    string output = R"(-4
499999998352516354
)";
    setInput(input);
    Solver598A().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}


