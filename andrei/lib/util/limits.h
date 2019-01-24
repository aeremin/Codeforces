#pragma once

#include <limits>


namespace internal {

class LimitLowest {
  public:
    LimitLowest(const LimitLowest&) = delete;
    LimitLowest& operator=(const LimitLowest&) = delete;

    template <typename T>
    operator T() && {
        return std::numeric_limits<T>().lowest();
    }
};

class LimitMax {
  public:
    LimitMax(const LimitMax&) = delete;
    LimitMax& operator=(const LimitMax&) = delete;

    template <typename T>
    operator T() && {
        return std::numeric_limits<T>().max();
    }
};

}  // namespace internal


internal::LimitLowest limit_lowest() { return {}; }

internal::LimitMax limit_max() { return {}; }
