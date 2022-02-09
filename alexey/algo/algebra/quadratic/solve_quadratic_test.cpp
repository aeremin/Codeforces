#include <gtest/gtest.h>
#include "algo/algebra/quadratic/solve_quadratic_real.h"
using namespace std;

TEST(SolveQuadraticTest, Real) {
    // (x - 3)(x - 5) = x^2 - 8x + 15
    EXPECT_EQ(make_pair(3., 5.), solve_quadratic_equation(1., -8., 15.));
    EXPECT_EQ(make_pair(3., 5.), solve_quadratic_equation(-1., 8., -15.));

    EXPECT_EQ(make_pair(100.0, 100.0), solve_quadratic_equation(1.0, -200.0, 10000.0));
    EXPECT_EQ(make_pair(100.0, 100.0), solve_quadratic_equation(-1.0, 200.0, -10000.0));
}