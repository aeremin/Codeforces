#include <Solvers/pch.h>
#include "algo/io/baseio.h"
#include "iter/range.h"
#include "algo/io/readvector.h"
#include "algo/io/printvector.h"
using namespace std;

// Solution for Codeforces problem http://codeforces.com/contest/1098/problem/B
class Solver1098B {
public:
    void run();
};

int NumDifferences(const string& s, const array<char, 2>& pattern) {
    int result = 0;
    for (int i : range(s.length()))
        if (s[i] != pattern[i % 2])
            ++result;
    return result;
}

pair<int, string> MinimalChangesAndBestPattern(const string& s, string pattern) {
    assert(pattern.length() == 2);
    auto a = NumDifferences(s, { pattern[0], pattern[1] });
    auto b = NumDifferences(s, { pattern[1], pattern[0] });
    if (a < b) {
        return { a, pattern };
    }
    else
    {
        swap(pattern[0], pattern[1]);
        return { b, pattern };
    }
}

pair<int, vector<string>> MinimalChangesForRows(const vector<string>& table) {
    int n = table.size();
    
    // Each row is XYXYXY...
    const vector<array<string, 2>> opportunities = {
        {"AG", "CT"},
        {"AT", "CG"},
        {"AC", "TG"},
        {"CT", "AG"},
        {"CG", "AT"},
        {"TG", "AC"},
    };

    int answer = numeric_limits<int>::max();
    vector<string> bestGenerator(n), currentGenerator(n);
    for (auto opt : opportunities) {
        int candidate = 0;
        for (int i : range(n)) {
            auto [price, pattern] = MinimalChangesAndBestPattern(table[i], opt[i % 2]);
            currentGenerator[i] = pattern;
            candidate += price;
        }
        if (candidate < answer) {
            answer = candidate;
            bestGenerator = currentGenerator;
        }
    }
    
    return { answer, bestGenerator };
}

vector<string> Transpose(const vector<string>& table) {
    string empty(table.size(), ' ');
    vector<string> result(table[0].length(), empty);
    for (int i : range(table.size()))
        for (int j : range(table[0].size()))
            result[j][i] = table[i][j];
    return result;
}

vector<string> Generate(const vector<string>& generator, int lineLen) {
    vector<string> result(generator.size());
    for (int i : range(generator.size()))
        for (int j : range(lineLen))
            result[i].push_back(generator[i][j % 2]);
    return result;
}


void Solver1098B::run() {
    auto n = read<int>();
    auto m = read<int>();
    auto table = readVector<string>(n);

    auto [rowPrice, rowGenerator] = MinimalChangesForRows(table);
    auto [columnPrice, columnGenerator] = MinimalChangesForRows(Transpose(table));

    auto answer = (rowPrice < columnPrice) ? Generate(rowGenerator, m) : Transpose(Generate(columnGenerator, n));
    printVector(answer, "\n");
}


class Solver1098BTest : public ProblemTest {};


TEST_F(Solver1098BTest, Example1) {
    setInput(R"(
2 2
AG
CT

)");
    string output = R"(
AG
CT

)";
    Solver1098B().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}

TEST_F(Solver1098BTest, Example2) {
    setInput(R"(
3 5
AGCAG
AGCAG
AGCAG

)");
    string output = R"(
AGCGC
CTATA
AGCGC

)";
    Solver1098B().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}

