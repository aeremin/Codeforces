#include <Solvers/pch.h>
#include "algo/io/baseio.h"
#include "iter/range.h"
#include "algo/number_theory/primes.h"
#include "algo/number_theory/residue.h"
#include "math/quick_power.h"
using namespace std;

// Solution for Codeforces problem http://codeforces.com/contest/1097/problem/D
class Solver1097D {
public:
    void run();
};

void Solver1097D::run() {
    const auto n = read<int64_t>();
    const auto k = read<int>();
    const auto prime_decomposition = decomposeToPrimePowers(n);
    CodeforcesResidue64 resulting_ev = 1;
    for (const auto [p, alpha] : prime_decomposition) {
        vector<CodeforcesResidue64> probability_distribution(alpha + 1);
        probability_distribution[alpha] = 1;
        for (int iteration : range(k)) {
            vector<CodeforcesResidue64> probability_distribution_next(alpha + 1);
            for (int beta : range(alpha + 1)) {
                auto add = probability_distribution[beta] * CodeforcesResidue64(beta + 1).inversed();
                for (int gamma : range(beta + 1)) {
                    probability_distribution_next[gamma] += add;
                }
            }
            probability_distribution = move(probability_distribution_next);
        }

        CodeforcesResidue64 p_to_delta = 1;
        CodeforcesResidue64 ev_multiplier = 0;
        for (int delta : range(alpha + 1)) {
            ev_multiplier += p_to_delta * probability_distribution[delta];
            p_to_delta *= CodeforcesResidue64(p);
        }
        resulting_ev *= ev_multiplier;
    }

    cout << resulting_ev;
}


class Solver1097DTest : public ProblemTest {};


TEST_F(Solver1097DTest, Example1) {
    setInput(R"(
6 1

)");
    string output = R"(
3

)";
    Solver1097D().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}

TEST_F(Solver1097DTest, Example2) {
    setInput(R"(
6 2

)");
    string output = R"(
875000008

)";
    Solver1097D().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}

TEST_F(Solver1097DTest, Example3) {
    setInput(R"(
60 5

)");
    string output = R"(
237178099

)";
    Solver1097D().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}

TEST_F(Solver1097DTest, MaxTest) {
    setInput(to_string(int64_t(1) << 50) + " 10000");
    Solver1097D().run();
}

