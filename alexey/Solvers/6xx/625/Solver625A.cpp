#include <Solvers/pch.h>

using namespace std;

class Solver625A
{
public:
    void run();
};

void Solver625A::run()
{
    int64_t n, a, b, c;
    cin >> n >> a >> b >> c;
    int64_t res = 0;
    if (a <= b - c || n < b)
        res = n / a;
    else
        res = (n - c) / (b - c) + ((n - c) % (b - c) + c) / a;

    cout << res;
}

class Solver625ATest : public ProblemTest {};

TEST_F(Solver625ATest, Example1)
{
    string input = R"(10
11
9
8
)";
    string output = R"(2
)";
    setInput(input);
    Solver625A().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}


TEST_F(Solver625ATest, Example2)
{
    string input = R"(10
5
6
1
)";
    string output = R"(2
)";
    setInput(input);
    Solver625A().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}


TEST_F(Solver625ATest, Example3)
{
    string input = R"(10
5
11
10
)";
    string output = R"(2)";
    setInput(input);
    Solver625A().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}

TEST_F(Solver625ATest, Example4)
{
    string input = R"(999
9
100
99
)";
    string output = R"(911)";
    setInput(input);
    Solver625A().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}
