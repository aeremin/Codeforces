#include <Solvers/pch.h>
#include "algo/io/baseio.hpp"
#include "iter/range.h"
#include "algo/io/readvector.hpp"
using namespace std;

// Solution for Codeforces problem http://codeforces.com/contest/1097/problem/A
class Solver1097A {
public:
    void run();
};

void Solver1097A::run() {
    auto table = read<string>();
    auto hand = readVector<string>(5);
    
    for (auto card : hand) {
        if (card[0] == table[0] || card[1] == table[1]) {
            cout << "YES";
            return;
        }
    }

    cout << "NO";
}


class Solver1097ATest : public ProblemTest {};


TEST_F(Solver1097ATest, Example1) {
    setInput(R"(
AS
2H 4C TH JH AD

)");
    string output = R"(
YES

)";
    Solver1097A().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}

TEST_F(Solver1097ATest, Example2) {
    setInput(R"(
2H
3D 4C AC KD AS

)");
    string output = R"(
NO

)";
    Solver1097A().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}

TEST_F(Solver1097ATest, Example3) {
    setInput(R"(
4D
AS AC AD AH 5H

)");
    string output = R"(
YES

)";
    Solver1097A().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}

