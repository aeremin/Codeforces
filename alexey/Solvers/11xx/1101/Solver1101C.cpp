#include <Solvers/pch.h>
#include "algo/io/baseio.hpp"
#include "iter/range.h"
#include "algo/io/readvector.hpp"
#include "algo/geometry/geomvector.hpp"
#include <optional>
using namespace std;

// Solution for Codeforces problem http://codeforces.com/contest/1101/problem/C
class Solver1101C {
public:
    void run();
};

void Solver1101C::run() {
    for (int i : range(read<int>())) {
        auto intervals = readVector<GeomVector2I>(read<int>());
        vector<pair<int, int>> ends;
        for (auto interval : intervals) {
            ends.emplace_back(interval[0], -1);
            ends.emplace_back(interval[1], +1);
        }
        sort(begin(ends), end(ends));
        ends.pop_back();

        int divisionPoint = -1;
        int balance = 0;
        for (auto [point, score] : ends) {
            balance += score;
            if (balance == 0) {
                divisionPoint = point;
                break;
            }
        }

        if (divisionPoint == -1) {
            cout << "-1\n";
        }
        else {
            for (auto interval : intervals) {
                if (interval[1] <= divisionPoint) {
                    cout << "1 ";
                }
                else {
                    cout << "2 ";
                }
            }
            cout << "\n";
        }
    }
}


class Solver1101CTest : public ProblemTest {};


TEST_F(Solver1101CTest, Example1) {
    setInput(R"(
3
2
5 5
2 3
3
3 5
2 3
2 3
3
3 3
4 4
5 5

)");
    string output = R"(
2 1 
-1
1 2 2 

)";
    Solver1101C().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}

