
#include <Solvers/pch.h>
#include "algo/io/baseio.h"
#include "algo/io/readvector.h"
#include "util/relax.h"
#include "iter/range.h"
using namespace std;

// Solution for Codeforces problem http://codeforces.com/contest/1637/problem/E
      
class Solver1637E {
  public:
    void run();
};

void Solver1637E::run() {
    for (int i : range(read<int>())) {
        auto n = read<int>();
        auto m = read<int>();
        auto v = readVector<int64_t>(n);
        set<pair<int64_t, int64_t>> bad_pairs;
        for (auto j: range(m)) {
            auto x = read<int64_t>();
            auto y = read<int64_t>();
            bad_pairs.insert({min(x, y), max(x,y)});
        }
        unordered_map<int64_t, int> counts;
        for (auto elt: v) ++counts[elt];
        vector<pair<int, int64_t>> choices;
        for (auto [value, count]: counts) choices.emplace_back(count, -value);
        sort(choices.begin(), choices.end());
        vector<int> optimal_choice_indices;
        int current_count = 0;
        for (auto j: range(choices.size())) {
            if (choices[j].first > current_count) {
                current_count = choices[j].first;
                optimal_choice_indices.push_back(j);
            }
        }

        int64_t answer = 0;
        for (int j: range(choices.size())) {
            for (auto optimal_choice_index: optimal_choice_indices) {
                for (auto choice_index: range<int>(optimal_choice_index, choices.size())) {
                    if (choices[choice_index].first > choices[optimal_choice_index].first) break;
                    auto v_1 = -choices[j].second;
                    auto v_2 = -choices[choice_index].second;
                    if (choice_index != j && bad_pairs.count({min(v_1, v_2), max(v_1, v_2)}) == 0) {
                        relax_max(answer, (choices[j].first + choices[choice_index].first) * (v_1 + v_2));
                        break;
                    }
                }
            }
        }
        print(answer);
        print("\n");
    }
}


class Solver1637ETest : public ProblemTest {};
    
TEST_F(Solver1637ETest, Example1) {
    setInput(R"(
3
6 1
6 3 6 7 3 3
3 6
2 0
3 4
7 4
1 2 2 3 1 5 1
1 5
3 5
1 3
2 5

)");
    string output = R"(
40
14
15

)";
    Solver1637E().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}


