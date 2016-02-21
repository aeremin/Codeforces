#pragma once

#include <algorithm>

#include "util/types.h"

template<typename T>
T BinomialCoefficient(int64 n, int64 k)
{
    if (n < 0)
        return T(0);

    if (k >= n || k <= 0)
        return T(1);

    k = std::min(k, n - k);

    auto res = T(1);
    for (int64 i = k - 1; i >= 0; --i)
        res = (res * T(n - i)) / T(k - i);

    return res;
}
