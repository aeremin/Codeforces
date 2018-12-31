#include <Solvers/pch.h>
#include "algo/io/baseio.hpp"
#include "iter/range.h"
using namespace std;

class Solver665A {
public:
    void run();

    int charToDigit(char c) { return c - '0'; }
};

void Solver665A::run() {
    int a, ta, b, tb;
    cin >> a >> ta >> b >> tb;
    string time;
    cin >> time;
    int startTime = (10 * charToDigit(time[0]) + charToDigit(time[1])) * 60 + 
        (10 * charToDigit(time[3]) + charToDigit(time[4]));
    int finishTime = startTime + ta;
    int ans = 0;
    for (int tStart = 300; tStart < 24 * 60; tStart += b) {
        int tFinish = tStart + tb;
        if (startTime < tFinish && tStart < finishTime)
            ++ans;
    }

    cout << ans;
}


class Solver665ATest : public ProblemTest {};


TEST_F(Solver665ATest, Example1) {
    string input = R"(10 30
10 35
05:20
)";
    string output = R"(5
)";
    setInput(input);
    Solver665A().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}
TEST_F(Solver665ATest, Example2) {
    string input = R"(60 120
24 100
13:00
)";
    string output = R"(9
)";
    setInput(input);
    Solver665A().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}
