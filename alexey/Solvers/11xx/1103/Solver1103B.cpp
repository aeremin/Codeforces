#include <optional>

#include <Solvers/pch.h>

#include "algo/io/baseio.h"
#include "iter/range.h"
using namespace std;

// Solution for Codeforces problem http://codeforces.com/contest/1103/problem/B
class Solver1103B {
  public:
    void run();
};

class InteractiveSolver1103B {
  public:
    void Run();
    virtual string GetResponse(int x, int y);
    virtual void PrintAnswer(int a);
};

string InteractiveSolver1103B::GetResponse(int x, int y) {
    cout << "? " << x << " " << y << endl;
    return read<string>();
}

void InteractiveSolver1103B::PrintAnswer(int a) { cout << "! " << a << endl; }

void InteractiveSolver1103B::Run() {
    bool first_stage = true;
    int64_t l, r;
    pair<int64_t, int64_t> candidates = {0, 1};

    while (first_stage || r - l > 1) {
        auto response = GetResponse(candidates.first, candidates.second);
        if (response == "e")
            return;
        const bool is_inversed = response == "x";

        if (first_stage) {
            if (candidates == pair<int64_t, int64_t>(0, 1) && is_inversed) {
                PrintAnswer(1);
                return;
            }

            if (is_inversed) {
                l = candidates.first;
                r = candidates.second;
                candidates = {l, (l + r) / 2};
                first_stage = false;
            } else {
                candidates = {candidates.second, 2 * candidates.second};
            }
        } else {
            if (is_inversed) {
                r = candidates.second;
            } else {
                l = candidates.second;
            }
            candidates = {l, (l + r) / 2};
        }
    }
    PrintAnswer(r);
}


void Solver1103B::run() {
    while (read<string>() == "start") {
        InteractiveSolver1103B().Run();
    }
}


class Solver1103BTest : public ProblemTest {};

class InteractiveSolver1103BForTest : public InteractiveSolver1103B {
  public:
    int64_t actual_a;
    int total_iterations = 0;
    bool answer_printed = false;

    InteractiveSolver1103BForTest(int64_t a) : actual_a(a) {}

    string GetResponse(int x, int y) override {
        EXPECT_GE(x, 0);
        EXPECT_LE(x, 2e9);
        EXPECT_GE(y, 0);
        EXPECT_LE(y, 2e9);
        total_iterations++;
        EXPECT_LE(total_iterations, 60);

        if ((x % actual_a) >= (y % actual_a))
            return "x";
        else
            return "y";
    }

    void PrintAnswer(int a) override {
        EXPECT_EQ(a, actual_a);
        answer_printed = true;
    }
};

TEST(InteractiveSolver1103BTest, SmallNumbers) {
    for (int64_t a : range(1, 100000)) {
        InteractiveSolver1103BForTest s(a);
        s.Run();
        EXPECT_TRUE(s.answer_printed);
    }
}

TEST(InteractiveSolver1103BTest, LargeNumbers) {
    for (int64_t a : range(1e9 - 100000, 1e9 + 1)) {
        InteractiveSolver1103BForTest s(a);
        s.Run();
        EXPECT_TRUE(s.answer_printed);
    }
}
