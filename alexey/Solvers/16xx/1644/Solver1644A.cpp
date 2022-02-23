
#include <Solvers/pch.h>
#include "algo/io/baseio.h"
#include "iter/range.h"
using namespace std;

// Solution for Codeforces problem http://codeforces.com/contest/1644/problem/A
      
class Solver1644A {
  public:
    void run();
};

void Solver1644A::run() {
    for (int i: range(read<int>())) {
        auto s = read<string>();
        bool can = s.find("R") > s.find("r") && s.find("G") > s.find("g") && s.find("B") > s.find("b");
        print(can ? "YES\n" : "NO\n");
    }
}


class Solver1644ATest : public ProblemTest {};
    
TEST_F(Solver1644ATest, Example1) {
    setInput(R"(
4
rgbBRG
RgbrBG
bBrRgG
rgRGBb

)");
    string output = R"(
YES
NO
YES
NO

)";
    Solver1644A().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}


