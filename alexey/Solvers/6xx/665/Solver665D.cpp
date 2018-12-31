#include <Solvers/pch.h>
#include "algo/io/baseio.hpp"
#include "iter/range.h"
#include "algo/io/readvector.hpp"
#include "algo/numbertheory/Primes.hpp"
using namespace std;

class Solver665D {
public:
    void run();
};

void Solver665D::run() {
    int n = read<int>();
    auto a = readVector<int>(n);
    int onesCnt = count(begin(a), end(a), 1);
    int indPrePrime = -1;
    for (int i : range(n)) {
        auto elt = a[i];
        if (elt > 1 && isPrime(elt + 1))
            indPrePrime = i;
    }
    auto primes = generatePrimesUntil(2e6);
    unordered_set<int> primeSet(begin(primes), end(primes));

    for (int i : range(n)) {
        auto elt = a[i];
        if (elt > 1 && primeSet.count(elt + 1))
            indPrePrime = i;
    }

    pair<int, int> indPrimePair = { -1, -1 };
    for (int i : range(n)) {
        for (int j : range(i)) {
            int cand = a[i] + a[j];
            if (cand > 2 && primeSet.count(cand)) {
                indPrimePair = { i, j };
                break;
            }
        }
        if (indPrimePair.first > 0)
            break;
    }

    int cntWithOnes = onesCnt + ((indPrePrime != -1) ? 1 : 0);
    int cntWithoutOnes = (indPrimePair.first != -1) ? 2 : 1;

    cout << max(cntWithOnes, cntWithoutOnes) << "\n";
    if (cntWithOnes >= cntWithoutOnes) {
        for (int i : range(onesCnt))
            cout << "1 ";
        if (indPrePrime != -1)
            cout << a[indPrePrime];
    }
    else {
        if (indPrimePair.first != -1)
            cout << a[indPrimePair.first] << " " << a[indPrimePair.second];
        else
            cout << a[0];
    }
}



class Solver665DTest : public ProblemTest {};


TEST_F(Solver665DTest, Example1) {
    string input = R"(2
2 3
)";
    string output = R"(2
3 2
)";
    setInput(input);
    Solver665D().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}
TEST_F(Solver665DTest, Example2) {
    string input = R"(2
2 2
)";
    string output = R"(1
2
)";
    setInput(input);
    Solver665D().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}
TEST_F(Solver665DTest, Example3) {
    string input = R"(3
2 1 1
)";
    string output = R"(3
1 1 2
)";
    setInput(input);
    Solver665D().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}
TEST_F(Solver665DTest, Example4) {
    string input = R"(2
83 14
)";
    string output = R"(2
14 83
)";
    setInput(input);
    Solver665D().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}
