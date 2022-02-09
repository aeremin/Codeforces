#include <gtest/gtest.h>
#include "algo/number_theory/coprimes.h"
#include "algo/number_theory/residue.h"
#include "math/quick_power.h"

TEST(CoprimeTest, CoprimeWithOne)
{
    auto divisors = getCoprimes(1);
    EXPECT_EQ(std::vector<int64_t>({ 1 }), divisors);
}

TEST(CoprimeTest, CoprimeWithTwo)
{
    auto divisors = getCoprimes(2);
    EXPECT_EQ(std::vector<int64_t>({ 1 }), divisors);
}

TEST(CoprimeTest, CoprimeWithPrime)
{
    auto divisors = getCoprimes(7);
    EXPECT_EQ(std::vector<int64_t>({ 1, 2, 3, 4, 5, 6 }), divisors);
}

TEST(CoprimeTest, CoprimeWithNonPrime)
{
    auto divisors = getCoprimes(12);
    EXPECT_EQ(std::vector<int64_t>({ 1, 5, 7, 11 }), divisors);
}

TEST(CoprimeTest, EulerTheorem)
{
    constexpr int64_t n = 123645;
    auto coprimes = getCoprimes(n);
    int64_t phiOfN = coprimes.size();
    using ResidueModuloN = Residue<int64_t, n>;
    for (auto a : coprimes)
        EXPECT_EQ(ResidueModuloN(1), quick_power(ResidueModuloN(a), phiOfN));
    
}