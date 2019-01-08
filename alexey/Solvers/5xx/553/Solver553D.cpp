#include <Solvers/pch.h>
#include "algo/io/readvector.hpp"
#include "algo/graph/Graph.hpp"
#include "algo/io/printvector.h"

using namespace std;

// Solution for Codeforces problem http://codeforces.com/contest/553/problem/D
class Solver553D
{
public:
    void run();

    struct City
    {
        bool hasFortress = false;
        vector<double> neighbourStrengths;
        int currentStrengthEstimate;
        int neighboursProcessed = 0;
    };
};

void Solver553D::run()
{
    int nVertices, nEdges, nFortresses;
    cin >> nVertices >> nEdges >> nFortresses;
    UndirectedGraph<EmptyStruct, City> graph(nVertices);
    for (int i = 0; i < nFortresses; ++i)
    {
        int a;
        cin >> a;
        graph.get_vertex_data(a - 1).hasFortress = true;
    }
    
    for (int i = 0; i < nEdges; ++i)
    {
        int a, b;
        cin >> a >> b;
        graph.add_edge(a - 1, b - 1);
    }

    typedef pair<double, size_t> QueueElt;
    priority_queue<QueueElt, vector<QueueElt>, greater<QueueElt>> toProcess;
    
    for (int i = 0; i < nVertices; ++i)
    {
        auto& currRef = graph.get_vertex_data(i);
        currRef.currentStrengthEstimate = graph.out_nbrs(i).size();
        currRef.neighbourStrengths = vector<double>(currRef.currentStrengthEstimate, 1.0);
        toProcess.push({ (currRef.hasFortress ? 0.0 : 1.0), i });
    }

    vector<double> finalStrength(nVertices, -1.0);
    
    while (!toProcess.empty())
    {
        auto currCity = toProcess.top();
        toProcess.pop();
        if (finalStrength[currCity.second] != -1.0)
            continue;

        finalStrength[currCity.second] = currCity.first;
        for (auto& pNei : graph.out_nbrs(currCity.second))
        {
            if (finalStrength[pNei.first] != -1.0)
                continue;

            auto& neiDataRef = graph.get_vertex_data(pNei.first);
            auto neiDegree = graph.out_nbrs(pNei.first).size();
            neiDataRef.neighboursProcessed++;
            neiDataRef.neighbourStrengths[neiDegree - neiDataRef.neighboursProcessed] = currCity.first;
            while (neiDataRef.currentStrengthEstimate > 0 &&
                   neiDataRef.neighbourStrengths[neiDataRef.currentStrengthEstimate - 1] < (neiDataRef.currentStrengthEstimate - 1.0) / neiDegree)
                neiDataRef.currentStrengthEstimate--;
            double currEstimate = min(double(neiDataRef.currentStrengthEstimate) / double(neiDegree),
                                      neiDataRef.neighbourStrengths[neiDataRef.currentStrengthEstimate - 1]);
            toProcess.push({ currEstimate, pNei.first });
        }
    }
    

    double maxStrength = *max_element(begin(finalStrength), end(finalStrength));

    vector<size_t> ans;
    for (size_t i = 0; i < nVertices; ++i)
        if (finalStrength[i] == maxStrength && !graph.get_vertex_data(i).hasFortress)
            ans.push_back(i + 1);

    cout << ans.size() << "\n";
    printVector(ans);
}

class Solver553DTest : public ProblemTest {};

TEST_F(Solver553DTest, Example1)
{
    string input = R"(9 8 4
3 9 6 8
1 2
1 3
1 4
1 5
2 6
2 7
2 8
2 9
)";
    string output = R"(3
1 4 5
)";
    setInput(input);
    Solver553D().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}


TEST_F(Solver553DTest, Example2)
{
    string input = R"(10 8 2
2 9
1 3
2 9
4 5
5 6
6 7
7 8
8 10
10 4
)";
    string output = R"(8
1 3 4 5 6 7 8 10
)";
    setInput(input);
    Solver553D().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}

