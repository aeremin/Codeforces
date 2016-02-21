#include <Solvers/pch.h>
#include "algo/io/baseio.hpp"
#include "algo/Relax.hpp"
#include "algo/Range.hpp"
using namespace std;

class Solver629B
{
public:
    void run();
};

void Solver629B::run()
{
    int n;
    cin >> n;
    vector<pair<int, int>> f, m;
    for (int i : range(n))
    {
        char c;
        int a, b;
        cin >> c >> a >> b;
        if (c == 'F')
            f.emplace_back(a, b);
        else
            m.emplace_back(a, b);
    }
    
    int ans = 0;
    for (int i : range(1, 367))
    {
        int canF = 0;
        int canM = 0;
        for (auto p : f)
            if (p.first <= i && p.second >= i)
                ++canF;

        for (auto p : m)
            if (p.first <= i && p.second >= i)
                ++canM;
        relaxMax(ans, 2 * min(canF, canM));
    }
    cout << ans;
}

class Solver629BTest : public ProblemTest {};

TEST_F(Solver629BTest, Example1)
{
    string input = R"(4
M 151 307
F 343 352
F 117 145
M 24 128
)";
    string output = R"(2
)";
    output.pop_back();
    setInput(input);
    Solver629B().run();
    EXPECT_EQ(output, getOutput());
}


TEST_F(Solver629BTest, Example2)
{
    string input = R"(6
M 128 130
F 128 131
F 131 140
F 131 141
M 131 200
M 140 200
)";
    string output = R"(4
)";
    output.pop_back();
    setInput(input);
    Solver629B().run();
    EXPECT_EQ(output, getOutput());
}


