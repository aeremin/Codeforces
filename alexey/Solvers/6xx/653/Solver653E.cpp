#include <Solvers/pch.h>
#include "algo/io/baseio.hpp"
#include "iter/range.h"
using namespace std;

class Solver653E
{
public:
    void run();
    
    vector<vector<int>> antiEdges;
    vector<int> unvisited;
    
    bool achievableFromFirst = false;

    bool has(const vector<int>& v, int elt) {
        auto it = lower_bound(begin(v), end(v), elt);
        return it != end(v) && (*it) == elt;
    }

    void dfs(int v) {
        achievableFromFirst = achievableFromFirst || has(antiEdges[0], v) == 0;
        vector<int> toVisit;
        for (int i = 0; i < unvisited.size(); ++i) {
            auto unv = unvisited[i];
            if (has(antiEdges[v], unv) == 0) {
                unvisited[i] = unvisited.back();
                unvisited.pop_back();
                --i;
                toVisit.push_back(unv);
            }
        }

        for (auto unv : toVisit)
            dfs(unv);
    }
};

void Solver653E::run()
{
    int nVertices, nForbiddenEdges, k;
    cin >> nVertices >> nForbiddenEdges >> k;
    antiEdges.resize(nVertices);
    for (int i : range(nForbiddenEdges)) {
        int a, b;
        cin >> a >> b;
        --a; --b;
        antiEdges[a].push_back(b);
        antiEdges[b].push_back(a);
    }

    for (auto& elt : antiEdges)
        sort(begin(elt), end(elt));

    for (int i : range(1, nVertices))
        unvisited.push_back(i);

    bool veryBad = false;
    int nComps = 0;
    while (!unvisited.empty()) {
        auto start = unvisited.back();
        unvisited.pop_back();
        achievableFromFirst = false;
        dfs(start);
        if (!achievableFromFirst)
            veryBad = true;
        ++nComps;
    }

    bool hasEnoughDegree = nVertices - 1 - antiEdges[0].size() >= k;
    
    if (!veryBad && nComps <= k && hasEnoughDegree)
        cout << "possible";
    else
        cout << "impossible";
}

class Solver653ETest : public ProblemTest {};

TEST_F(Solver653ETest, Example1)
{
    string input = R"(5 4 2
1 2
2 3
4 2
4 1
)";
    string output = R"(possible
)";
    output.pop_back();
    setInput(input);
    Solver653E().run();
    EXPECT_EQ(output, getOutput());
}


TEST_F(Solver653ETest, Example2)
{
    string input = R"(6 5 3
1 2
1 3
1 4
1 5
1 6
)";
    string output = R"(impossible
)";
    output.pop_back();
    setInput(input);
    Solver653E().run();
    EXPECT_EQ(output, getOutput());
}

TEST_F(Solver653ETest, Example3) {
    string input = R"(4 4 1
1 3
2 3
1 4
2 4
)";
    string output = R"(impossible
)";
    output.pop_back();
    setInput(input);
    Solver653E().run();
    EXPECT_EQ(output, getOutput());
}

TEST_F(Solver653ETest, Example4) {
    string input = R"(3 1 1
2 3
)";
    string output = R"(impossible
)";
    output.pop_back();
    setInput(input);
    Solver653E().run();
    EXPECT_EQ(output, getOutput());
}

TEST_F(Solver653ETest, Example5) {
    string input = R"(4 3 2
1 2
1 3
2 4
)";
    string output = R"(impossible
)";
    output.pop_back();
    setInput(input);
    Solver653E().run();
    EXPECT_EQ(output, getOutput());
}
