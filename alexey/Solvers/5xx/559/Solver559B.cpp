#include <Solvers/pch.h>
#include "algo/io/baseio.h"
#include "iter/range.h"
using namespace std;

// Solution for Codeforces problem http://codeforces.com/contest/559/problem/B
class Solver559B
{
public:
    void run();
    int maxPowOf2 = 1;
    int n;

    void normalize(string& s) {
        int chunkSize = n / maxPowOf2;
        while (chunkSize < n) {
            for (int i = 0; i < n / chunkSize; i += 2) {
                bool isInverted = false;
                for (int j : range(chunkSize)) {
                    if (s[i * chunkSize + j] > s[(i + 1) * chunkSize + j]) {
                        isInverted = true;
                        break;
                    }
                    else if (s[i * chunkSize + j] < s[(i + 1) * chunkSize + j]) {
                        break;
                    }
                }
                if (isInverted) {
                    for (int j : range(chunkSize))
                        swap(s[i * chunkSize + j], s[(i + 1) * chunkSize + j]);
                }
            }
            chunkSize *= 2;
        }
    }

    bool isEquivalent(string s1, string s2) {
        n = s1.length();
        while (n % (2 * maxPowOf2) == 0) maxPowOf2 *= 2;
        normalize(s1);
        normalize(s2);
        return (s1 == s2);
    }
};

void Solver559B::run()
{
    string s1, s2;
    cin >> s1 >> s2;
    if (isEquivalent(s1, s2))
        cout << "YES";
    else
        cout << "NO";
}

class Solver559BTest : public ProblemTest {};

TEST_F(Solver559BTest, Example1)
{
    string input = R"(aaba
abaa
)";
    string output = R"(YES
)";
    output.pop_back();
    setInput(input);
    Solver559B().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}


TEST_F(Solver559BTest, Example2) {
    string input = R"(aabb
abab
)";
    string output = R"(NO
)";
    output.pop_back();
    setInput(input);
    Solver559B().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}


TEST_F(Solver559BTest, Example3) {
    string input = R"(a
b
)";
    string output = R"(NO
)";
    output.pop_back();
    setInput(input);
    Solver559B().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}

TEST_F(Solver559BTest, Example4) {
    string input = R"(aaabbb
bbbaaa
)";
    string output = R"(YES
)";
    output.pop_back();
    setInput(input);
    Solver559B().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}

TEST_F(Solver559BTest, MaxLen) {
    EXPECT_TRUE(Solver559B().isEquivalent(string(1 << 17, 'a'), string(1 << 17, 'a')));
}
