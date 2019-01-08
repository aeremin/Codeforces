#include <Solvers/pch.h>
#include "algo/io/baseio.hpp"
#include "iter/range.h"
#include "algo/io/readvector.hpp"
#include "algo/numbertheory/Primes.hpp"
#include "graph/graph.h"
#include "algo/graph/max_flow_push_relabel.h"
#include "algo/DisjointSet.hpp"

using namespace std;

// Solution for Codeforces problem http://codeforces.com/contest/510/problem/E
class Solver510E
{
public:
    void run();
};

void Solver510E::run()
{
    int nFoxes;
    cin >> nFoxes;
    auto foxAges = readVector<int>(nFoxes);
    auto possiblePrimesVec = generatePrimesUntil(20000);
    unordered_set<int> possiblePrimes(begin(possiblePrimesVec), end(possiblePrimesVec));
    DirectedGraph<int, EmptyStruct> g(nFoxes + 2);
    for (int i : range(nFoxes)) {
        for (int j : range(nFoxes)) {
            if (possiblePrimes.count(foxAges[i] + foxAges[j])) {
                int u = i + 1;
                int v = j + 1;
                if (foxAges[i] % 2 == 0)
                    g.add_directed_edge(u, v, 1);
            }
        }
    }

    for (int i : range(nFoxes))
        if (foxAges[i] % 2 == 0)
            g.add_directed_edge(0, i + 1, 2);
        else
            g.add_directed_edge(i + 1, nFoxes + 1, 2);

    MaxFlowPushRelabel<true, int, EmptyStruct> maxFlowCalc(g);
    auto flow = maxFlowCalc.GetMaxFlow(0, nFoxes + 1);
    if (flow.totalFlow != nFoxes) {
        cout << "Impossible";
        return;
    }


    
    vector<vector<int>> neighbours(nFoxes);
    for (int i : range(nFoxes)) {
        auto outedges = flow.flow.out_nbrs(i + 1);
        if (outedges.size() == 2) {
            for (auto[vertex, payload] : outedges) {
                neighbours[i].push_back(vertex - 1);
                neighbours[vertex - 1].push_back(i);
            }
        }
    }

    vector<vector<int>> foxesPerTable;
    vector<bool> usedFoxes(nFoxes, false);

    for (int i : range(nFoxes)) {
        if (usedFoxes[i]) continue;
        usedFoxes[i] = true;
        foxesPerTable.push_back({ i });
        auto& currTable = foxesPerTable.back();
        auto nextFox = [&](int f) -> int {
            return (currTable.size() > 1 && neighbours[f][0] == currTable[currTable.size() - 2])
                 ? neighbours[f][1] : neighbours[f][0];
        };

        for (auto f = nextFox(foxesPerTable.back().back()); !usedFoxes[f]; f = nextFox(f)) {
            usedFoxes[f] = true;
            foxesPerTable.back().push_back(f);
        }
    }

    cout << foxesPerTable.size() << "\n";
    for (auto& table : foxesPerTable) {
        cout << table.size() << " ";
        for (auto fox : table)
            cout << fox + 1 << " ";
        cout << "\n";
    }
}

class Solver510ETest : public ProblemTest {
protected:
    vector<int> foxAges;
    
    string generateInput() const {
        stringstream ss;
        ss << foxAges.size() << " ";
        for (auto age : foxAges) ss << age << " ";
        return ss.str();
    }
    
    void validateAnswer(const string& output) {
        stringstream ss(output);
        int nTables;
        ss >> nTables;
        unordered_set<int> usedFoxes;
        for (int i : range(nTables)) {
            int tableSize;
            ss >> tableSize;
            EXPECT_GT(tableSize, 2);
            vector<int> table(tableSize);
            for (auto& f : table)
                ss >> f;
            
            for (int i : range(tableSize)) {
                EXPECT_TRUE(usedFoxes.insert(table[i]).second);
                auto age1 = foxAges[table[i] - 1];
                auto age2 = foxAges[table[(i + 1) % tableSize] - 1];
                EXPECT_TRUE(isPrime(age1 + age2));
            }
        }
        EXPECT_EQ(foxAges.size(), usedFoxes.size());
    }
};


TEST_F(Solver510ETest, Example1)
{
    foxAges = { 3, 4, 8, 9 };
    setInput(generateInput());
    Solver510E().run();
    validateAnswer(getOutput());
}


TEST_F(Solver510ETest, Example2)
{
    string input = R"(5
2 2 2 2 2
)";
    string output = R"(Impossible
)";
    output.pop_back();
    setInput(input);
    Solver510E().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}


TEST_F(Solver510ETest, Example3)
{
    foxAges = { 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13 };
    setInput(generateInput());
    Solver510E().run();
    validateAnswer(getOutput());
}


TEST_F(Solver510ETest, Example4)
{
    foxAges = { 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25 };
    setInput(generateInput());
    Solver510E().run();
    validateAnswer(getOutput());
}


