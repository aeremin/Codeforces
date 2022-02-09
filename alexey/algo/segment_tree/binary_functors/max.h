#pragma once
#include <algorithm>

namespace binary_functors {

template <typename T>
struct Max {
    T operator()(const T& t, const T& u) const { return std::max(t, u); }
};

}  // namespace binary_functors