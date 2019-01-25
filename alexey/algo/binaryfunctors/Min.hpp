#pragma once
#include <algorithm>

namespace binaryFunctors {

template <typename T>
struct Min {
    T operator()(const T& t, const T& u) const { return std::min(t, u); }
};

}  // namespace binaryFunctors