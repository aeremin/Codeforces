#pragma once

namespace binary_functors {

template <typename T>
struct FirstArgument {
    T operator()(const T& t, const T& u) const { return t; }
};


}  // namespace binary_functors