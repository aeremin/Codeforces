#pragma once
#include <vector>

#include "algo/numbertheory/Residue.hpp"
#include "iter/range.h"

template<typename UnderlyingInt, UnderlyingInt MOD>
class CombinatoricsHelper {
public:
    using ValueType = Residue<UnderlyingInt, MOD>;

    // Precalculates all needed to calculate factorials/inverted factorials/binomial coefficients up to n (inclusive).
    // Time complexity is O(n), memory is O(n).
    CombinatoricsHelper(int n): factorials_(n + 1), inverted_factorials_(n + 1) {
        factorials_[0] = 1;
        for (int i : range(1, n + 1))
            factorials_[i] = factorials_[i - 1] * ValueType(i);

        inverted_factorials_[n] = factorials_[n].inversed();
        for (int i = n - 1; i >= 0; --i)
            inverted_factorials_[i] = inverted_factorials_[i + 1] * ValueType(i + 1);
    }

    // Return k! (in Z_MOD field). k must be <= n.
    ValueType factorial(int k) {
        return factorials_[k];
    }

    // Return 1/(k!) (in Z_MOD field). k must be <= n.
    ValueType inverted_factorial(int k) {
        return inverted_factorials_[k];
    }

    // Return C_m^k (in Z_MOD field). m, k must be <= n.
    ValueType binomial_coefficient(int m, int k) {
        if (k < 0 || k > m) return 0;
        return factorials_[m] * inverted_factorials_[k] * inverted_factorials_[m - k];
    }

private:
    std::vector<ValueType> factorials_;
    std::vector<ValueType> inverted_factorials_;
};
