#pragma once
#include <cassert>

// Worst-case complexity is O(modulo)
int GroupOrder(int elt, int modulo) {
    auto pow = elt % modulo;
    for (int i : range(1, modulo)) {
        if (pow == 1)
            return i;
        pow = (int64_t(pow) * elt) % modulo;
    }
    assert(false);
    return -1;
}
