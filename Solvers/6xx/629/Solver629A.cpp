#include <Solvers/pch.h>
#include "algo/io/baseio.hpp"
#include "algo/io/readvector.hpp"
#include "algo/Range.hpp"
using namespace std;

class Solver629A
{
public:
    void run();
};

void Solver629A::run()
{
    int n;
    cin >> n;
    auto field = readVector<string>(n);
    vector<int> r(n, 0), c(n, 0);
    for (int i : range(n))
        for(int j : range(n))
            if (field[i][j] =='C'){
                r[i]++;
                c[j]++;
            }
    int ans = 0;
    for (auto elt : r)
        ans += elt * (elt - 1) / 2;

    for (auto elt : c)
        ans += elt * (elt - 1) / 2;
    
    cout << ans;
}

class Solver629ATest : public ProblemTest {};

TEST_F(Solver629ATest, Example1)
{
    string input = R"(3
.CC
C..
C.C
)";
    string output = R"(4
)";
    output.pop_back();
    setInput(input);
    Solver629A().run();
    EXPECT_EQ(output, getOutput());
}


TEST_F(Solver629ATest, Example2)
{
    string input = R"(4
CC..
C..C
.CC.
.CC.
)";
    string output = R"(9
)";
    output.pop_back();
    setInput(input);
    Solver629A().run();
    EXPECT_EQ(output, getOutput());
}

