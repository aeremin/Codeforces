
#include <Solvers/pch.h>
#include "algo/io/baseio.hpp"
#include "iter/range.h"
#include "util/relax.h"
using namespace std;

// Solution for Codeforces problem http://codeforces.com/contest/1106/problem/E
      
class Solver1106E {
  public:
    void run();
};

void Solver1106E::run() {
    auto total_time = read<int>();
    auto allowed_interruptions = read<int>();
    auto n_envelopes = read<int>();
    vector<tuple<int, int, int, int64_t>> envelopes(n_envelopes);

    vector<vector<int>> ending_at(total_time + 1);
    vector<vector<int>> starting_at(total_time + 1);

    for (int i: range(n_envelopes)) {
        auto& env = envelopes[i];
        get<0>(env) = read<int>();
        get<1>(env) = read<int>();
        get<2>(env) = read<int>();
        get<3>(env) = read<int64_t>();

        starting_at[get<0>(env)].push_back(i);
        ending_at[get<1>(env)].push_back(i);
    }

    vector<vector<int64_t>> dp(total_time + 2, vector<int64_t>(allowed_interruptions + 1, numeric_limits<int64_t>::max()));
    for (int i : range(allowed_interruptions + 1))
        dp[total_time + 1][i] = 0;

    set<tuple<int64_t, int, int>> choices;
    for (int t = total_time; t >= 0; --t) {
        for (auto& ind : ending_at[t]) {
            choices.insert({get<3>(envelopes[ind]), get<2>(envelopes[ind]), ind });
        }
        for (int i : range(allowed_interruptions + 1)) {
            if (i > 0) {
                relax_min(dp[t][i], dp[t + 1][i - 1]);
            }

            if (choices.empty()) {
                relax_min(dp[t][i], dp[t + 1][i]);
            }
            else {
                auto best_choice_it = end(choices);
                --best_choice_it;
                auto c = *best_choice_it;
                relax_min(dp[t][i], get<0>(c) + dp[get<1>(c) + 1][i]);
            }
        }
        for (auto& ind : starting_at[t]) {
            choices.erase({get<3>(envelopes[ind]), get<2>(envelopes[ind]), ind});
        }
    }

    int64_t ans = *min_element(begin(dp[0]), end(dp[0]));
    cout << ans;
}


class Solver1106ETest : public ProblemTest {};
    
TEST_F(Solver1106ETest, Example1) {
    setInput(R"(
5 0 2
1 3 4 5
2 5 5 8

)");
    string output = R"(
13
)";
    Solver1106E().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}

TEST_F(Solver1106ETest, Example2) {
    setInput(R"(
10 1 6
1 1 2 4
2 2 6 2
3 3 3 3
4 4 4 5
5 5 5 7
6 6 6 9

)");
    string output = R"(
2
)";
    Solver1106E().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}

TEST_F(Solver1106ETest, Example3) {
    setInput(R"(
12 2 6
1 5 5 4
4 6 6 2
3 8 8 3
2 9 9 5
6 10 10 7
8 12 12 9

)");
    string output = R"(
11
)";
    Solver1106E().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}


