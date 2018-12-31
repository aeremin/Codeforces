#include <Solvers/pch.h>
#include "algo/io/baseio.hpp"
#include "iter/range.h"
#include "util/relax.h"
using namespace std;

class Solver645D
{
public:
    void run();

    vector<unordered_set<int>> loosers;
    vector<int> depth;

    int getDepth(int i) {
        if (depth[i] != -1)
            return depth[i];

        int maxChildDepth = -1;
        for (auto ch : loosers[i])
            relax_max(maxChildDepth, getDepth(ch));

        return depth[i] = maxChildDepth + 1;
    }
};

void Solver645D::run()
{
    int nRobots, nMatches;
    cin >> nRobots >> nMatches;
    vector<pair<int, int>> matches(nMatches);
    for (auto& elt : matches) {
        cin >> elt.first >> elt.second;
        --elt.first; --elt.second;
    }
    
    loosers = vector<unordered_set<int>>(nRobots);
    for (auto& elt : matches)
        loosers[elt.first].insert(elt.second);

    depth = vector<int>(nRobots, -1);
    int maxDepth = 0;
    for (int i : range(nRobots))
        relax_max(maxDepth, getDepth(i));
    
    if (maxDepth != nRobots - 1) {
        cout << -1;
        return;
    }

    vector<int> ratings(nRobots);
    iota(begin(ratings), end(ratings), 0);

    sort(begin(ratings), end(ratings), [&](int a, int b) {return depth[a] > depth[b]; });

    set<pair<int, int>> needToDecide;
    for (int i : range(nRobots - 1))
        needToDecide.emplace(ratings[i], ratings[i + 1]);

    for (int i : range(nMatches)) {
        needToDecide.erase(matches[i]);
        if (needToDecide.empty()) {
            cout << (i + 1);
            return;
        }
    }

    cout << -1;
}

class Solver645DTest : public ProblemTest {};

TEST_F(Solver645DTest, Example1)
{
    string input = R"(4 5
2 1
1 3
2 3
4 2
4 3
)";
    string output = R"(4
)";
    output.pop_back();
    setInput(input);
    Solver645D().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}


TEST_F(Solver645DTest, Example2)
{
    string input = R"(3 2
1 2
3 2
)";
    string output = R"(-1
)";
    output.pop_back();
    setInput(input);
    Solver645D().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}

TEST_F(Solver645DTest, Example3) {
    string input = R"(3 1
1 2
)";
    string output = R"(-1
)";
    output.pop_back();
    setInput(input);
    Solver645D().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}

TEST_F(Solver645DTest, Example4) {
    string input = R"(4 7
1 3
1 2
1 4
2 3
2 3
3 4
2 4
)";
    string output = R"(6
)";
    output.pop_back();
    setInput(input);
    Solver645D().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}