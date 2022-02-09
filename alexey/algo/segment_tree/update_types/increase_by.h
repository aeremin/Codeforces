#pragma once

namespace update_types {

template <typename T>
struct IncreaseBy {
  public:
    IncreaseBy(T value = T()) : value_(std::move(value)) {}

    friend IncreaseBy<T> operator*(const IncreaseBy<T>& lh, const IncreaseBy<T>& rh) { return {lh.value_ + rh.value_}; }
    T value_;
};

}  // namespace update_types
