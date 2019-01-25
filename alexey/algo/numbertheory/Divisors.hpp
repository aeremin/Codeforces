#pragma once
#include <algorithm>
#include <cstdint>
#include <iterator>
#include <vector>

//! Returns vector of all divisors of n (including 1 and n).
//! It's guaranteed that order of divisors is strictly increasing.
//! Time complexity is O(sqrt(n))
inline std::vector<int64_t> getDivisorsOf(int64_t n) {
    std::vector<int64_t> divisorsSmallerOrEqualSqrtOfN, divisorsBiggerSqrtOfN;
    for (int64_t d = 1; d * d <= n; ++d) {
        if (n % d == 0) {
            divisorsSmallerOrEqualSqrtOfN.push_back(d);
            if (d * d < n)
                divisorsBiggerSqrtOfN.push_back(n / d);
        }
    }

    std::copy(divisorsBiggerSqrtOfN.rbegin(), divisorsBiggerSqrtOfN.rend(),
              std::back_inserter(divisorsSmallerOrEqualSqrtOfN));
    return divisorsSmallerOrEqualSqrtOfN;
}