
#include <Solvers/pch.h>
#include "algo/io/baseio.hpp"
#include "iter/range.h"
#include "algo/io/readvector.hpp"
#include "util/relax.h"
#include "algo/geometry/geomvector.hpp"
using namespace std;

// Solution for Codeforces problem http://codeforces.com/contest/1129/problem/A
      
class Solver1129A {
  public:
    void run();
};

void Solver1129A::run() {
    auto n = read<int64_t>();
    auto m = read<int64_t>();
    auto items = readVector<GeomVector2I>(m);

    vector<int64_t> station_estimate(n, 0);
    vector<vector<int>> from_station(n);
    for (auto p : items) {
        from_station[p[0] - 1].push_back((p[1] - p[0] + n) % n);
    }

    for (auto i : range(n)) {
        if (!from_station[i].empty()) {
            sort(begin(from_station[i]), end(from_station[i]));
            station_estimate[i] = n * (from_station[i].size() - 1) + from_station[i].front();
        }
    }

    for (auto i : range(n)) {
        int64_t ans = 0;
        for (int k : range(n)) {
            auto s = (i + k) % n;
            if (station_estimate[s] > 0) {
                relax_max(ans, k + station_estimate[s]);
            }
        }
        cout << ans << " ";
    }
}


class Solver1129ATest : public ProblemTest {};
    
TEST_F(Solver1129ATest, Example1) {
    setInput(R"(
5 7
2 4
5 1
2 3
3 4
4 1
5 3
3 5

)");
    string output = R"(
10 9 10 10 9 

)";
    Solver1129A().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}

TEST_F(Solver1129ATest, Example2) {
    setInput(R"(
2 3
1 2
1 2
1 2

)");
    string output = R"(
5 6

)";
    Solver1129A().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}


