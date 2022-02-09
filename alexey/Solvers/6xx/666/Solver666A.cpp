#include <Solvers/pch.h>
#include "algo/io/baseio.h"
#include "iter/range.h"
using namespace std;

// Solution for Codeforces problem http://codeforces.com/contest/666/problem/A
class Solver666A {
public:
    void run();

    map<pair<int, string>, bool> cache;
    set<string> suffixes;

    string s;

    bool process(int t, string banned = "") {
        auto w = s.substr(0, t);
        pair<int, string> p = { t, banned };
        auto it = cache.find(p);
        if (it != cache.end())
            return it->second;
        
        cache[p] = false;

        if (t >= 5) {
            cache[p] = true;
        }

        if (t >= 7) {
            auto sf = s.substr(t - 2, 2);
            if (sf != banned && process(t - 2, sf)) {
                suffixes.insert(sf);
                cache[p] = true;
            }
        }

        if (t >= 8) {
            auto sf = s.substr(t - 3, 3);
            if (sf != banned && process(t - 3, sf)) {
                suffixes.insert(sf);
                cache[p] = true;
            }
        }

        return cache[p];
    }
};

void Solver666A::run() {
    cin >> s;
    process(s.length());

    cout << suffixes.size() << "\n";
    for (auto sf : suffixes)
        cout << sf << "\n";
}

class Solver666ATest : public ProblemTest {};


TEST_F(Solver666ATest, Example1) {
    string input = R"(abacabaca
)";
    string output = R"(3
aca
ba
ca
)";
    setInput(input);
    Solver666A().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}

TEST_F(Solver666ATest, Example2) {
    string input = R"(abaca
)";
    string output = R"(0
)";
    setInput(input);
    Solver666A().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}

