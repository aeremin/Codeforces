#pragma once
#include "algo/updateappliers/UpdateApplier.hpp"

template<typename Functor>
struct UpdateApplier<updateTypes::Id, Functor>
{
    template<typename T>
    static T apply(const T& v, const updateTypes::Id&, size_t)
    {
        return v;
    }
};
