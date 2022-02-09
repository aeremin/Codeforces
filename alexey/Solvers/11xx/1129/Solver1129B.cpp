
#include <Solvers/pch.h>
#include "algo/io/baseio.h"
#include "iter/range.h"
#include "util/relax.h"
#include "algo/io/printvector.h"
#include <random>
using namespace std;

// Solution for Codeforces problem http://codeforces.com/contest/1129/problem/B
      
int64_t find_answer(const vector<int64_t>& a) {
    int64_t res = 0;
    int cur = 0;
    int k = -1;
    for (auto i : range(a.size())) {
        cur += a[i];
        if (cur < 0) {
            cur = 0;
            k = i;
        }
        res = max<int64_t>(res, (i - k) * cur);
    }
    return res;
}

int64_t find_real_answer(const vector<int64_t>& a) {
    int64_t res = numeric_limits<int64_t>::min();
    vector<int64_t> sums = { 0 };
    partial_sum(begin(a), end(a), back_inserter(sums));
    for (int l : range(a.size())) {
        for (int r : range<int>(l, a.size())) {
            relax_max(res, (r - l + 1) * sums[r + 1] - sums[l]);
        }
    }
    return res;
}

vector<int64_t> GenerateWithDiff(int64_t d) {
    for (int k : range(d / 1000000, d / 1000000 + 2)) {
        relax_min(k, 999);
        relax_max(k, 1);
        for (int64_t x : range(2 * k, 6 * 100000)) {
            auto v = 2 * k * x - (k + 1) * (2 * k + 1) + 1;
            if (v >= d) {
                int64_t a = v - d;
                vector<int64_t> res = { (x - 1 + a), (-x - a) };
                for (int i : range(k - 1)) {
                    res.push_back(x - 1);
                    res.push_back(-x);
                }
                res.push_back(x - 1);
                return res;
            }
        }
    }
    assert(false);
    return {};
}

class Solver1129B {
  public:
    void run();
};

void Solver1129B::run() {
    int d = read<int>();
    auto a = GenerateWithDiff(d);
    auto d1 = find_real_answer(a);
    auto d2 = find_answer(a);
    assert(d1 - d2 == d);
    cout << a.size() << "\n";
    printVector(a);
}


class Solver1129BTest : public ProblemTest {};

void Check(int64_t d) {
    auto a = GenerateWithDiff(d);
    auto d1 = find_real_answer(a);
    auto d2 = find_answer(a);
    ASSERT_EQ(d1 - d2, d);
}

TEST_F(Solver1129BTest, Example1) {
    for (int d : range(1, 1000))
        Check(d);
}

TEST_F(Solver1129BTest, Example2) {
    for (int d : {1, 10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000, 1000000000})
        Check(d);
}

TEST_F(Solver1129BTest, Example3) {
    int64_t d = 1;
    while (d < 1000000000) {
        Check(d);
        d *= 2;
    }
}

TEST_F(Solver1129BTest, Example4) {
    std::mt19937 rng;
    rng.seed(std::random_device()());
    std::uniform_int_distribution<std::mt19937::result_type> dist(1, 1000000000);

    for (int i : range(1000)) {
        Check(dist(rng));
    }
}
