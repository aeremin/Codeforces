#pragma once
#include "algo/numbertheory/Primes.hpp"

uint64_t NumberOfDivisors(uint64_t n) {
    auto decomposition = decomposeToPrimePowers(n);
    uint64_t res = 1;
    for (auto p : decomposition)
        res *= (p.second + 1);
    return res;
}