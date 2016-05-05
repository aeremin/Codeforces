#include <Solvers/pch.h>
#include "algo/io/baseio.hpp"
#include "iter/range.h"
#include "algo/graph/Graph.hpp"
#include "algo/graph/Dijkstra.hpp"
using namespace std;

class Solver666B {
public:
    void run();

    struct BestPath {
        int distance;
        int c1, c2, c3, c4;
    };

    BestPath bestPath = { 0, 0, 0, 0, 0 };

    void relaxBestPath(int distance, int c1, int c2, int c3, int c4) {
        if (c1 == c2 || c1 == c3 || c1 == c4 || c2 == c3 || c2 == c4 || c3 == c4)
            return;

        if (distance > bestPath.distance) {
            bestPath = { distance, c1 + 1, c2 + 1, c3 + 1, c4 + 1};
        }
    }
};

void Solver666B::run() {
    int nCities, nRoads;
    cin >> nCities >> nRoads;
    Graph<int, EmptyStruct> g(nCities);

    for (int i : range(nRoads)) {
        int from, to;
        cin >> from >> to;
        g.add_directed_edge(from - 1, to - 1, 1);
    }

    vector<vector<int>> distanceMatrix(nCities, vector<int>(nCities));

    for (int startCity : range(nCities)) {
        auto d = getMinimalPathsFrom(g, startCity, numeric_limits<int>::min() / 5);
        for (int finishCity : range(nCities))
            distanceMatrix[startCity][finishCity] = d.minimalDistances[finishCity];
    }

    vector<vector<pair<int, int>>> maxDistancesTo(nCities, vector<pair<int, int>>(nCities));
    auto maxDistancesFrom = maxDistancesTo;
    for (int iCity : range(nCities)) {
        for (int otherCity : range(nCities)) {
            maxDistancesFrom[iCity][otherCity] = { distanceMatrix[iCity][otherCity], otherCity };
            maxDistancesTo[iCity][otherCity] = { distanceMatrix[otherCity][iCity], otherCity };
        }
        sort(begin(maxDistancesFrom[iCity]), end(maxDistancesFrom[iCity]), greater<pair<int, int>>());
        sort(begin(maxDistancesTo[iCity]), end(maxDistancesTo[iCity]), greater<pair<int, int>>());
    }

    for (int c2 : range(nCities)) {
        for (int c3 : range(nCities)) {
            auto d23 = distanceMatrix[c2][c3];
            for (int i : range(3))
                for (int j : range(3))
                    relaxBestPath(d23 + maxDistancesTo[c2][i].first + maxDistancesFrom[c3][j].first,
                                  maxDistancesTo[c2][i].second, c2, c3, maxDistancesFrom[c3][j].second);
        }
    }

    cout << bestPath.c1 << " " << bestPath.c2 << " " << bestPath.c3 << " " << bestPath.c4;
}


class Solver666BTest : public ProblemTest {};


TEST_F(Solver666BTest, Example1) {
    string input = R"(8 9
1 2
2 3
3 4
4 1
4 5
5 6
6 7
7 8
8 5
)";
    string output = R"(2 1 8 7
)";
    output.pop_back();
    setInput(input);
    Solver666B().run();
    EXPECT_EQ(output, getOutput());
}

