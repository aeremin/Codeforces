#pragma once
#include <algorithm>

namespace binary_functors {

template <typename T>
struct Min {
    T operator()(const T& t, const T& u) const { return std::min(t, u); }
};

}  // namespace binary_functors