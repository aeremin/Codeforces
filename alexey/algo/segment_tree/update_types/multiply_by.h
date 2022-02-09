#pragma once

namespace update_types {

template <typename T>
struct MultiplyBy {
  public:
    MultiplyBy(T value = {1}) : value_(std::move(value)) {}

    friend MultiplyBy<T> operator*(const MultiplyBy<T>& lh, const MultiplyBy<T>& rh) { return {lh.value_ * rh.value_}; }
    T value_;
};

}  // namespace update_types
