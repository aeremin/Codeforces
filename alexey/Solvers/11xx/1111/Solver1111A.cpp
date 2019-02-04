
#include <Solvers/pch.h>
#include "algo/io/baseio.hpp"
#include "iter/range.h"
using namespace std;

// Solution for Codeforces problem http://codeforces.com/contest/1111/problem/A

class Solver1111A {
  public:
    void run();
};

string CanonicalName(const string& name) {
    string res;
    for (auto c : name) {
        if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u') {
            res.push_back('a');
        }
        else {
            res.push_back('b');
        }
    }
    return res;
}

void Solver1111A::run() {
    auto x = read<string>();
    auto y = read<string>();
    if (CanonicalName(x) == CanonicalName(y)) {
        cout << "Yes";
    }
    else {
        cout << "No";
    }
}


class Solver1111ATest : public ProblemTest {};
    
TEST_F(Solver1111ATest, Example1) {
    setInput(R"(
a
u

)");
    string output = R"(
Yes

)";
    Solver1111A().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}

TEST_F(Solver1111ATest, Example2) {
    setInput(R"(
abc
ukm

)");
    string output = R"(
Yes

)";
    Solver1111A().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}

TEST_F(Solver1111ATest, Example3) {
    setInput(R"(
akm
ua

)");
    string output = R"(
No

)";
    Solver1111A().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}


