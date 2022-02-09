#include <Solvers/pch.h>
#include "algo/io/baseio.h"
#include "iter/range.h"
#include "algo/functor_iterator.h"
#include "util/relax.h"
using namespace std;

// Solution for Codeforces problem http://codeforces.com/contest/645/problem/C
class Solver645C
{
public:
    void run();
};

void Solver645C::run()
{
    int nRooms, nCows;
    cin >> nRooms >> nCows;
    ++nCows;
    string r;
    cin >> r;
    int ans = numeric_limits<int>::max();
    vector<int> prefixFree = { 0 };
    deque<int> usedRooms;
    int middle = 0;
    for (int i : range(nRooms)) {
        if (r[i] == '0') {
            usedRooms.push_back(i);
            if (usedRooms.size() > nCows) {
                usedRooms.pop_front();
                if (middle > 0)
                    --middle;
            }
            while (middle + 1 < usedRooms.size()) {
                if (max(usedRooms[middle + 1] - usedRooms.front(), -usedRooms[middle + 1] + usedRooms.back()) <
                    max(usedRooms[middle] - usedRooms.front(), -usedRooms[middle] + usedRooms.back()))
                    middle++;
                else
                    break;
            }
            if (usedRooms.size() == nCows)
                relax_min(ans, max(usedRooms[middle] - usedRooms.front(), -usedRooms[middle] + usedRooms.back()));
        }
    }
    cout << ans;
}

class Solver645CTest : public ProblemTest {};

TEST_F(Solver645CTest, Example1)
{
    string input = R"(7 2
0100100
)";
    string output = R"(2
)";
    output.pop_back();
    setInput(input);
    Solver645C().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}


TEST_F(Solver645CTest, Example2)
{
    string input = R"(5 1
01010
)";
    string output = R"(2
)";
    output.pop_back();
    setInput(input);
    Solver645C().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}


TEST_F(Solver645CTest, Example3)
{
    string input = R"(3 2
000
)";
    string output = R"(1
)";
    output.pop_back();
    setInput(input);
    Solver645C().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}


