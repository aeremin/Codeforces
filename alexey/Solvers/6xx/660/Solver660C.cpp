#include <Solvers/pch.h>
#include "algo/io/baseio.hpp"
#include "iter/range.h"
#include "algo/io/readvector.hpp"
#include "util/relax.h"
using namespace std;

class Solver660C
{
public:
    void run();
};

void Solver660C::run()
{
    int n, k;
    cin >> n >> k;
    auto d = readVector<int>(n);
    auto ans = d;
    int bestL = 0, bestR = 0;
    int r = 0;
    int left = k;
    for (int l : range(n)) {
        if (l > 0) {
            if (d[l - 1] == 0 && ans[l - 1] == 1) {
                ans[l - 1] = 0;
                ++left;
            }
        }
        
        relax_max(r, l);

        while (r < n && (left > 0 || d[r] == 1)) {
            if (d[r] == 0) {
                ans[r] = 1;
                --left;
            }
            ++r;
        }
        if (r - l > bestR - bestL) {
            bestR = r;
            bestL = l;
        }
    }

    cout << (bestR - bestL) << endl;
    for (int i : range(n))
        if (i >= bestL && i < bestR) cout << 1 << " "; else cout << d[i] << " ";
}

class Solver660CTest : public ProblemTest {};

TEST_F(Solver660CTest, Example1)
{
    string input = R"(7 1
1 0 0 1 1 0 1
)";
    string output = R"(4
1 0 0 1 1 1 1 
)";
    output.pop_back();
    setInput(input);
    Solver660C().run();
    EXPECT_EQ(output, getOutput());
}


TEST_F(Solver660CTest, Example2)
{
    string input = R"(10 2
1 0 0 1 0 1 0 1 0 1
)";
    string output = R"(5
1 0 0 1 1 1 1 1 0 1 
)";
    output.pop_back();
    setInput(input);
    Solver660C().run();
    EXPECT_EQ(output, getOutput());
}

TEST_F(Solver660CTest, Example3) {
    string input = R"(5 0
0 0 0 0 0
)";
    string output = R"(0
0 0 0 0 0 
)";
    output.pop_back();
    setInput(input);
    Solver660C().run();
    EXPECT_EQ(output, getOutput());
}

TEST_F(Solver660CTest, Example4) {
    string input = R"(2 0
0 1 
)";
    string output = R"(1
0 1 
)";
    output.pop_back();
    setInput(input);
    Solver660C().run();
    EXPECT_EQ(output, getOutput());
}
