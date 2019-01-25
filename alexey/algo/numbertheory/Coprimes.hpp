#pragma once
#include <algorithm>
#include <cstdint>
#include <vector>

#include "algo/numbertheory/Primes.hpp"

//! Returns vector of numbers from [0, n], such that their GCD with n is 1.
//! Order is guaranteed to be increasing.
//! Time complexity is O(n log n) with some quite good constant.
inline std::vector<int64_t> getCoprimes(int64_t n) {
    std::vector<int64_t> res;
    auto decompositionOfN = decomposeToPrimePowers(n);
    for (int64_t i = 1; i <= n; ++i) {
        bool isCoprime = std::none_of(begin(decompositionOfN), end(decompositionOfN),
                                      [&](const std::pair<uint64_t, uint64_t>& p) { return i % p.first == 0; });
        if (isCoprime)
            res.push_back(i);
    }

    return res;
}