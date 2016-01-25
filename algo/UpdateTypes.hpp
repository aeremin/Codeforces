#pragma once
#include "algo/Functors.hpp"

namespace updateTypes
{

template<typename T>
struct SetValueTo
{
public:
    typedef T ValueType;

    SetValueTo() : isId_(true) {};
    SetValueTo(T value) : isId_(false), value_(std::move(value)) {}

    friend SetValueTo<T> operator*(const SetValueTo<T>& lh, const SetValueTo<T>& rh) { return lh.isId_ ? rh : lh; }

public:
    bool isId_;
    T value_;
};

template<typename T>
struct IncreaseValueBy
{
public:
    IncreaseValueBy(T value = T(0)) : value_(std::move(value)) {}
    
    friend IncreaseValueBy<T> operator*(const IncreaseValueBy<T>& lh, const IncreaseValueBy<T>& rh) { return {lh.value_ + rh.value_ }; }
    T value_;
};

}

template<class UpdateType, class BinaryFunctor> 
struct UpdateApplier
{
    static typename UpdateType::ValueType apply(const typename UpdateType::ValueType& v, const UpdateType& upd, size_t length) { return upd.isId_ ? v : upd.value_; }
};

template<typename T>
struct UpdateApplier<updateTypes::SetValueTo<T>, std::plus<T>>
{
    static T apply(const T& v, const updateTypes::SetValueTo<T>& upd, size_t length) { return upd.isId_ ? v : upd.value_ * length; }
};

