
#include <Solvers/pch.h>
#include "algo/io/baseio.h"
#include "iter/range.h"
#include "algo/io/readvector.h"
using namespace std;

// Solution for Codeforces problem http://codeforces.com/contest/1107/problem/C
      
class Solver1107C {
  public:
    void run();
};

void Solver1107C::run() {
    int n = read<int>();
    int k = read<int>();
    auto dmg = readVector<int64_t>(n);
    auto seq = read<string>();
    int64_t ans = 0;
    vector<int64_t> buffer;
    auto flush = [&]() {
        sort(rbegin(buffer), rend(buffer));
        for (int i : range(min<int>(k, buffer.size())))
            ans += buffer[i];
        buffer.clear();
    };
    for (int i: range(n)) {
        if (i > 0 && seq[i] != seq[i - 1]) {
            flush();
        }
        buffer.push_back(dmg[i]);
    }
    flush();
    cout << ans;
}


class Solver1107CTest : public ProblemTest {};
    
TEST_F(Solver1107CTest, Example1) {
    setInput(R"(
7 3
1 5 16 18 7 2 10
baaaaca

)");
    string output = R"(
54

)";
    Solver1107C().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}

TEST_F(Solver1107CTest, Example2) {
    setInput(R"(
5 5
2 4 1 3 1000
aaaaa

)");
    string output = R"(
1010

)";
    Solver1107C().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}

TEST_F(Solver1107CTest, Example3) {
    setInput(R"(
5 4
2 4 1 3 1000
aaaaa

)");
    string output = R"(
1009

)";
    Solver1107C().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}

TEST_F(Solver1107CTest, Example4) {
    setInput(R"(
8 1
10 15 2 1 4 8 15 16
qqwweerr

)");
    string output = R"(
41

)";
    Solver1107C().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}

TEST_F(Solver1107CTest, Example5) {
    setInput(R"(
6 3
14 18 9 19 2 15
cccccc

)");
    string output = R"(
52

)";
    Solver1107C().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}

TEST_F(Solver1107CTest, Example6) {
    setInput(R"(
2 1
10 10
qq

)");
    string output = R"(
10

)";
    Solver1107C().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}


