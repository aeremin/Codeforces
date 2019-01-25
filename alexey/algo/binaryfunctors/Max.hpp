#pragma once
#include <algorithm>

namespace binaryFunctors {

template <typename T>
struct Max {
    T operator()(const T& t, const T& u) const { return std::max(t, u); }
};

}  // namespace binaryFunctors