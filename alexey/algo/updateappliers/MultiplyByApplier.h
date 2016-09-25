#pragma once
#include "algo/updateappliers/UpdateApplier.hpp"

template<typename T, typename Functor>
struct UpdateApplier<updateTypes::MultiplyBy<T>, Functor>
{
    static T apply(const T& v, const updateTypes::MultiplyBy<T>& upd, size_t)
    {
        return upd.value_ * v;
    }
};
