#pragma once

namespace updateTypes
{

template<typename T>
struct IncreaseBy
{
public:
    IncreaseBy(T value = T()) : value_(std::move(value)) {}

    friend IncreaseBy<T> operator*(const IncreaseBy<T>& lh, const IncreaseBy<T>& rh) { return{ lh.value_ + rh.value_ }; }
    T value_;
};

}
