#include <Solvers/pch.h>
#include "algo/io/baseio.hpp"
#include "iter/range.h"
using namespace std;

class Solver653B
{
public:
    void run();
};

void Solver653B::run()
{
    int len, nSubs;
    cin >> len >> nSubs;
    vector<pair<string, string>> subs(nSubs);
    for (auto& elt : subs)
        cin >> elt.first >> elt.second;

    array<int64_t, 6> ans = { 1, 0, 0, 0, 0, 0 };
    for (int i : range(1, len)) {
        array<int64_t, 6> ansNext = { 0, 0, 0, 0, 0 , 0 };
        for (auto s : subs)
            ansNext[s.first[0] - 'a'] += ans[s.second[0] - 'a'];
        ans = ansNext;
    }

    auto total = accumulate(begin(ans), end(ans), 0);
    cout << total;
}

class Solver653BTest : public ProblemTest {};

TEST_F(Solver653BTest, Example1)
{
    string input = R"(3 5
ab a
cc c
ca a
ee c
ff d
)";
    string output = R"(4
)";
    output.pop_back();
    setInput(input);
    Solver653B().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}


TEST_F(Solver653BTest, Example2)
{
    string input = R"(2 8
af e
dc d
cc f
bc b
da b
eb a
bb b
ff c
)";
    string output = R"(1
)";
    output.pop_back();
    setInput(input);
    Solver653B().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}


TEST_F(Solver653BTest, Example3)
{
    string input = R"(6 2
bb a
ba a
)";
    string output = R"(0
)";
    output.pop_back();
    setInput(input);
    Solver653B().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}


