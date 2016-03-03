#include <Solvers/pch.h>
#include "algo/io/baseio.hpp"
#include "iter/range.h"
#include "algo/io/readvector.hpp"
#include "algo/polynomial/polynomial.h"
#include "math/quick_power.h"
#include "algo/polynomial/fast_fourier_transform.h"
#include "algo/polynomial/fast_multiplication.h"

using namespace std;

class Solver632E {
public:
    void run();

    const int maxPrice = 1000;
    const int maxCount = 1000;

    void renormalizeCoefficients(Polynomial<complex<double>>& p) {
        for (auto i : range(p.formal_degree() + 1))
            p.coefficient(i) = (abs(p.coefficient(i)) > 0.5) ? 1.0 : 0.0;
    }
};

void Solver632E::run() {
    int n = read<int>();
    int k = read<int>();
    auto prices = readVector<int>(n);
    vector<complex<double>> pricesCount(maxPrice + 1, 0);
    for (auto p : prices)
        pricesCount[p] = 1.0;
    Polynomial<complex<double>> genFun(move(pricesCount));
    auto multiplyFunctor = [&](Polynomial<complex<double>> lh, Polynomial<complex<double>> rh) -> Polynomial<complex<double>> {
        auto product = move(lh) * move(rh);
        renormalizeCoefficients(product);
        return product;
    };
    
    auto genFunPowered = quick_power(genFun, k, { 1 }, multiplyFunctor);
    for (int i : range(maxPrice * maxCount + 1))
        if (abs(genFunPowered.get_coefficient(i)) > 0.5)
            cout << i << " ";
}

class Solver632ETest : public ProblemTest {};

TEST_F(Solver632ETest, Example1) {
    string input = R"(3 2
1 2 3
)";
    string output = R"(2 3 4 5 6 )";
    setInput(input);
    Solver632E().run();
    EXPECT_EQ(output, getOutput());
}


TEST_F(Solver632ETest, Example2) {
    string input = R"(5 5
1 1 1 1 1
)";
    string output = R"(5 )";
    setInput(input);
    Solver632E().run();
    EXPECT_EQ(output, getOutput());
}


TEST_F(Solver632ETest, Example3) {
    string input = R"(3 3
3 5 11
)";
    string output = R"(9 11 13 15 17 19 21 25 27 33 )";
    setInput(input);
    Solver632E().run();
    EXPECT_EQ(output, getOutput());
}


