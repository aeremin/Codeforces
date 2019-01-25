#pragma once
#include "algo/numbertheory/Primes.hpp"
#include "iter/range.h"
#include "math/quick_power.h"

int64_t PrimeRoot(int64_t primeModulo) {
    assert(isPrime(primeModulo));
    auto dec = decomposeToPrimePowers(primeModulo - 1);

    auto check = [&](int64_t r) -> bool {
        for (auto pr : dec) {
            if (quick_power(r, (primeModulo - 1) / pr.first, int64_t(1),
                            [&](int64_t a, int64_t b) { return (a * b) % primeModulo; }) == 1)
                return false;
        }
        return true;
    };

    for (auto r : range<int64_t>(1, primeModulo))
        if (check(r))
            return r;

    assert(false);
    return 0;
}