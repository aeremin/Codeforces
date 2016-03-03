#include <Solvers/pch.h>
#include "algo/io/baseio.hpp"
#include "iter/range.h"
using namespace std;

class Solver631D {
public:
    void run();

    vector<pair<int64_t, char>> readPacked(int len) {
        vector<pair<int64_t, char>> res;
        string s;
        for (int i : range(len)) {
            cin >> s;
            int a;
            char c;
            sscanf(s.c_str(), "%d-%c", &a, &c);
            if (i > 0 && res.back().second == c)
                res.back().first += a;
            else
                res.push_back({ a, c });
        }
        return res;
    }

    inline vector<int> calcPrefixFunction(const vector<pair<int64_t, char>>& s) {
        vector<int> pi;
        if (s.empty())
            return pi;
        pi.push_back(0);
        for (int i = 1; i < s.size(); ++i) {
            int curPi = pi.back();
            while (curPi > 0 && s[i] != s[curPi])
                curPi = pi[curPi - 1];
            if (s[i] == s[curPi]) curPi++;
            pi.push_back(curPi);
        }
        return pi;
    }
};

void Solver631D::run() {
    int n, m;
    cin >> n >> m;
    const auto s1 = readPacked(n);
    const auto s2 = readPacked(m);
    if (s2.size() == 1) {
        int64_t ans = 0;
        for (auto p : s1)
            if (p.second == s2.front().second && p.first >= s2.front().first)
                ans += p.first - s2.front().first + 1;
        cout << ans;
    }
    else {
        vector<pair<int64_t, char>> concat(begin(s2) + 1, end(s2) - 1);
        concat.push_back({ 0, '#' });
        copy(begin(s1), end(s1), back_inserter(concat));
        auto pi = calcPrefixFunction(concat);
        int64_t ans = 0;
        for (int i : range(s2.size() - 1, pi.size() - 1))
            if (pi[i] == s2.size() - 2) {
                auto j = i - s2.size() + 1;
                
                auto s1partB = s1[j - s2.size() + 2];
                auto s2partB = s2.front();
                
                auto s1partA = s1[j + 1];
                auto s2partA = s2.back();

                if ((s1partB.second == s2partB.second && s1partB.first >= s2partB.first) &&
                    (s1partA.second == s2partA.second && s1partA.first >= s2partA.first))
                    ++ans;
            }

        cout << ans;
    }
}

class Solver631DTest : public ProblemTest {};

TEST_F(Solver631DTest, Example1) {
    string input = R"(5 3
3-a 2-b 4-c 3-a 2-c
2-a 2-b 1-c
)";
    string output = R"(1)";
    setInput(input);
    Solver631D().run();
    EXPECT_EQ(output, getOutput());
}


TEST_F(Solver631DTest, Example2) {
    string input = R"(6 1
3-a 6-b 7-a 4-c 8-e 2-a
3-a
)";
    string output = R"(6)";
    setInput(input);
    Solver631D().run();
    EXPECT_EQ(output, getOutput());
}


TEST_F(Solver631DTest, Example3) {
    string input = R"(4 5
1-h 1-e 2-l 1-o
1-w 1-o 1-r 1-l 1-d
)";
    string output = R"(0)";
    setInput(input);
    Solver631D().run();
    EXPECT_EQ(output, getOutput());
}

TEST_F(Solver631DTest, PackingWorks) {
    string input = R"(4 5
1-h 4-h 2-h 3-h
1-h 1-h 1-h 1-h 1-h
)";
    string output = R"(6)";
    setInput(input);
    Solver631D().run();
    EXPECT_EQ(output, getOutput());
}

TEST_F(Solver631DTest, TwoBlockPattern) {
    string input = R"(5 2
3-a 2-b 4-c 4-a 5-b
2-a 2-b
)";
    string output = R"(2)";
    setInput(input);
    Solver631D().run();
    EXPECT_EQ(output, getOutput());
}

TEST_F(Solver631DTest, LongPattern) {
    string input = R"(5 6
3-a 2-a 4-a 4-a 5-a
2-a 2-b 2-c 2-d 2-a 2-b
)";
    string output = R"(0)";
    setInput(input);
    Solver631D().run();
    EXPECT_EQ(output, getOutput());
}
