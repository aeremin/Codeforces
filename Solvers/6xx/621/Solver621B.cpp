#include <Solvers/pch.h>

using namespace std;

class Solver621B
{
public:
    void run();
};

void Solver621B::run()
{
    int n;
    cin >> n;
    unordered_map<int, int> diag1, diag2;
    for (int i = 0; i < n; ++i)
    {
        int a, b;
        cin >> a >> b;
        diag1[a + b]++;
        diag2[a - b]++;
    }

    int64_t ans = 0;
    for (auto p : diag1)
        ans += (p.second * (p.second - 1)) / 2;

    for (auto p : diag2)
        ans += (p.second * (p.second - 1)) / 2;

    cout << ans;
}

class Solver621BTest : public ProblemTest {};

TEST_F(Solver621BTest, Example1)
{
    string input = R"(5
1 1
1 5
3 3
5 1
5 5
)";
    string output = R"(6
)";
    output.pop_back();
    setInput(input);
    Solver621B().run();
    EXPECT_EQ(output, getOutput());
}


TEST_F(Solver621BTest, Example2)
{
    string input = R"(3
1 1
2 3
3 5
)";
    string output = R"(0
)";
    output.pop_back();
    setInput(input);
    Solver621B().run();
    EXPECT_EQ(output, getOutput());
}


