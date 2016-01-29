#pragma once
#include "algo/updateappliers/UpdateApplier.hpp"

template<typename T, typename IdempotentFunctor>
struct UpdateApplier<updateTypes::IncreaseBy<T>, IdempotentFunctor>
{
    static T apply(const T& v, const updateTypes::IncreaseBy<T>& upd, size_t)
    {
        return T + upd.value_;
    }
};
