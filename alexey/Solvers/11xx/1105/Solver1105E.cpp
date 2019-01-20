#include <Solvers/pch.h>
#include <optional>

#include "algo/io/baseio.hpp"
#include "graph/graph.h"
#include "iter/range.h"
#include "algo/graph/max_clique.h"
#include "algo/graph/complement.h"
using namespace std;

// Solution for Codeforces problem http://codeforces.com/contest/1105/problem/E
class Solver1105E {
  public:
    void run();
};

void Solver1105E::run() {
    auto n_events = read<int>();
    auto n_friends = read<int>();
    set<string> names_batch;
    UndirectedGraph<> bans(n_friends);

    map<string, int> name_to_index;

    auto get_index = [&](const string& name) {
        auto it = name_to_index.find(name);
        if (it != name_to_index.end())
            return it->second;
        int res = name_to_index.size();
        name_to_index[name] = res;
        return res;
    };

    auto flush_batch = [&]() {
        for (const auto& name1 : names_batch) {
            for (const auto& name2 : names_batch) {
                if (name1 == name2)
                    continue;
                auto i1 = get_index(name1);
                auto i2 = get_index(name2);
                bans.add_edge(i1, i2);
            }
        }
        names_batch.clear();
    };

    for (int i : range(n_events)) {
        int kind = read<int>();
        if (kind == 1) {
            flush_batch();
        } else {
            auto name = read<string>();
            names_batch.insert(name);
        }
    }
    flush_batch();

    cout << MaximumClique(ComplementGraph(bans)).size();
}

class Solver1105ETest : public ProblemTest {};


TEST_F(Solver1105ETest, Example1) {
    setInput(R"(
5 3
1
2 motarack
2 mike
1
2 light

)");
    string output = R"(
2

)";
    Solver1105E().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}

TEST_F(Solver1105ETest, Example2) {
    setInput(R"(
4 3
1
2 alice
2 bob
2 tanyaromanova

)");
    string output = R"(
1

)";
    Solver1105E().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}
