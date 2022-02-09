#pragma once
#include "algo/number_theory/primes.h"

uint64_t NumberOfDivisors(uint64_t n) {
    auto decomposition = decomposeToPrimePowers(n);
    uint64_t res = 1;
    for (auto p : decomposition)
        res *= (p.second + 1);
    return res;
}