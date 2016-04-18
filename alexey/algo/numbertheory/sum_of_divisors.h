#pragma once
#include "algo/numbertheory/Primes.hpp"
#include "math/quick_power.h"

uint64_t SumOfDivisors(uint64_t n) {
    auto decomposition = decomposeToPrimePowers(n);
    uint64_t res = 1;
    for (auto p : decomposition)
        res *= (quick_power(p.first, p.second + 1) - 1) / (p.first - 1);
    return res;
}