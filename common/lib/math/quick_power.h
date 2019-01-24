#pragma once

#include "util/types.h"

template <class T, class MultiplicationFunctor = std::multiplies<T>>
T quick_power(const T& a, int64 p, T one = {1}, MultiplicationFunctor mf = {}) {
    auto res = one;
    auto m = a;
    while (p > 0) {
        if (p % 2 == 0) {
            m = mf(m, m);
            p /= 2;
        } else {
            res = mf(res, m);
            p--;
        }
    }
    return res;
}
