#include <Solvers/pch.h>

#include "algo/geometry/geomvector.h"
#include "algo/io/baseio.h"
#include "algo/io/readvector.h"
#include "iter/range.h"
#include "algo/io/printvector.h"
using namespace std;

// Solution for Codeforces problem http://codeforces.com/contest/1105/problem/D
class Solver1105D {
  public:
    void run();
};

void Solver1105D::run() {
    auto n = read<int>();
    auto m = read<int>();
    auto num_players = read<int>();
    auto speeds = readVector<int>(num_players);
    vector<string> field(n);
    for (auto& l : field) l = read<string>();
    auto can_extend = [&](const GeomVector2I& where) {
        return where[0] >= 0 && where[0] < n && where[1] >= 0 && where[1] < m && field[where[0]][where[1]] == '.';
    };
    vector<vector<GeomVector2I>> border_castles(num_players);

    vector<int> scores(num_players, 0);

    for (int x : range(n)) {
        for (int y : range(m)) {
            auto c = field[x][y];
            if (c >= '1' && c <= '9') {
                border_castles[c - '1'].push_back({x, y});
                scores[c - '1']++;
            }
        }
    }

    bool has_turns = true;
    while (has_turns) {
        has_turns = false;
        for (int player : range(num_players)) {
            for (int iteration : range(speeds[player])) {
                if (border_castles[player].empty())
                    break;
                vector<GeomVector2I> border_castles_next;
                for (const auto& castle : border_castles[player]) {
                    static const vector<GeomVector2I> dirs = {{-1, 0}, {1, 0}, {0, 1}, {0, -1}};
                    for (const auto& dir : dirs) {
                        const GeomVector2I candidate = castle + dir;
                        if (can_extend(candidate)) {
                            field[candidate[0]][candidate[1]] = '1' + player;
                            scores[player]++;
                            border_castles_next.push_back(candidate);
                            has_turns = true;
                        }
                    }
                }
                border_castles[player] = move(border_castles_next);
            }
        }
    }

    printVector(scores);
}


class Solver1105DTest : public ProblemTest {};


TEST_F(Solver1105DTest, Example1) {
    setInput(R"(
3 3 2
1 1
1..
...
..2

)");
    string output = R"(
6 3 

)";
    Solver1105D().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}

TEST_F(Solver1105DTest, Example2) {
    setInput(R"(
3 4 4
1 1 1 1
....
#...
1234

)");
    string output = R"(
1 4 3 3 

)";
    Solver1105D().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}
