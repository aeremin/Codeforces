#include <Solvers/pch.h>
#include "algo/io/baseio.hpp"
#include "iter/range.h"
#include "util/relax.h"
using namespace std;

class Solver567B
{
public:
    void run();
};

void Solver567B::run()
{
    int n = read<int>();
    unordered_set<int> entered;
    int maxEntered = 0;
    int wasBefore = 0;
    for (int i : range(n)) {
        char c;
        int r;
        cin >> c >> r;
        if (c == '+') {
            entered.insert(r);
            relax_max<int>(maxEntered, entered.size() - wasBefore);
        }
        else if (entered.count(r) > 0) {
            entered.erase(r);
        }
        else {
            wasBefore++;
        }
    }

    cout << wasBefore + maxEntered;
}

class Solver567BTest : public ProblemTest {};

TEST_F(Solver567BTest, Example1)
{
    string input = R"(6
+ 12001
- 12001
- 1
- 1200
+ 1
+ 7
)";
    string output = R"(3)";
    setInput(input);
    Solver567B().run();
    EXPECT_EQ(output, getOutput());
}


TEST_F(Solver567BTest, Example2)
{
    string input = R"(2
- 1
- 2
)";
    string output = R"(2)";
    setInput(input);
    Solver567B().run();
    EXPECT_EQ(output, getOutput());
}


TEST_F(Solver567BTest, Example3)
{
    string input = R"(2
+ 1
- 1
)";
    string output = R"(1)";
    setInput(input);
    Solver567B().run();
    EXPECT_EQ(output, getOutput());
}


