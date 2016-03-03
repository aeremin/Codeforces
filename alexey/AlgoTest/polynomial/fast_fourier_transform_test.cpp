#include <gtest/gtest.h>
#include "algo/polynomial/fast_fourier_transform.h"

TEST( FastFourierTransformTest, Inversible ) {
    Polynomial<std::complex<double>> p = { { 1, 0 }, { 2, 3 }, { 4, 5 }, { 3, 5 } };
    auto q = FastFourierTransform( p, false );
    auto r = FastFourierTransform( q, true );
    EXPECT_EQ( p, r );
}