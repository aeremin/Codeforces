
#include <Solvers/pch.h>
#include "algo/io/baseio.h"
#include "iter/range.h"
#include "algo/io/readvector.h"
#include "algo/io/printvector.h"
using namespace std;

// Solution for Codeforces problem http://codeforces.com/contest/1641/problem/B
      
class Solver1641B {
  public:
    void run();
};

void Solver1641B::run() {
    for (auto t: range(read<int>())) {
        auto a = readVector<int>(read<int>());
        int l = 0;
        bool success = true;
        map<int, int> counts;
        for (auto elt: a) counts[elt]++;
        for (auto [v, c]: counts) success = success && (c % 2 == 0); 
        if (success) {
            vector<pair<int, int>> insertions;
            vector<int> intervals;
            while (l < a.size()) {
                int x = a[l];
                auto i_x = find(a.begin() + l + 1, a.end(), x) - a.begin();
                for (int j: range<int>(l + 1, i_x)) {
                    insertions.emplace_back(i_x + j - l, a[j]);
                    a.insert(a.begin() + i_x + j - l, a[j]);
                    a.insert(a.begin() + i_x + j - l, a[j]);
                }
                intervals.push_back(2 * (i_x - l));
                l += 2 * (i_x - l);
            }
            print(insertions.size());
            print("\n");
            for (auto [a, b]: insertions) {
                print(a);
                print(" ");
                print(b);
                print("\n");
            }
            print(intervals.size());
            print("\n");
            printVector(intervals);
            print("\n");
        }
        else {
            print(-1);
            print("\n");
        }
    }
}

class Solver1641BTest : public ProblemTest {};
    
TEST_F(Solver1641BTest, Example1) {
    setInput(R"(
4
2
5 7
2
5 5
6
1 3 1 2 2 3
6
3 2 1 1 2 3

)");
    string output = R"(
-1
0
1
2
3
3 3
8 2
9 2
3
4 6 2
6
6 2
7 1
8 1
9 2
14 1
15 1
3
10 6 2
)";
    Solver1641B().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}
