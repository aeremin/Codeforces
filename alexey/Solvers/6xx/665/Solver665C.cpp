#include <Solvers/pch.h>
#include "algo/io/baseio.hpp"
#include "iter/range.h"
using namespace std;

class Solver665C {
public:
    void run();

    char notCoincide(char a, char b) {
        for (auto c = 'a'; c < 'z'; ++c)
            if (c != a && c != b)
                return c;
        return 0;
    }
};

void Solver665C::run() {
    string s;
    cin >> s;
    for (int i : range(s.length() - 1)) {
        if (s[i] == s[i + 1]) {
            s[i + 1] = (i < s.length() - 2) ? notCoincide(s[i], s[i + 2]) : notCoincide(s[i], s[i]);
        }
    }

    cout << s;
}


class Solver665CTest : public ProblemTest {};


TEST_F(Solver665CTest, Example1) {
    string input = R"(aab
)";
    string output = R"(acb
)";
    output.pop_back();
    setInput(input);
    Solver665C().run();
    EXPECT_EQ(output, getOutput());
}
TEST_F(Solver665CTest, Example2) {
    string input = R"(caaab
)";
    string output = R"(cabab
)";
    output.pop_back();
    setInput(input);
    Solver665C().run();
    EXPECT_EQ(output, getOutput());
}
TEST_F(Solver665CTest, Example3) {
    string input = R"(zscoder
)";
    string output = R"(zscoder
)";
    output.pop_back();
    setInput(input);
    Solver665C().run();
    EXPECT_EQ(output, getOutput());
}
