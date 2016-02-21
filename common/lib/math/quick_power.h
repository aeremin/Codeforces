#pragma once

#include "util/types.h"

template<class T>
T quick_power(const T& a, int64 p, T one = T(1)) {
    auto res = one;
    auto m = a;
    while (p > 0) {
        if (p % 2 == 0) {
            m = m * m;
            p /= 2;
        }
        else {
            res *= m;
            p--;
        }
    }
    return res;
}
