#pragma once
#include <vector>

#include "algo/io/baseio.h"

template <typename T>
std::vector<T> readVector(size_t size) {
    std::vector<T> res(size);
    for (auto& elt : res)
        elt = read<T>();
    return res;
}
