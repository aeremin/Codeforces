#pragma once
#include "algo/updateappliers/UpdateApplier.hpp"

template<typename T>
struct UpdateApplier<updateTypes::SetTo<T>, std::plus<T>>
{
    static T apply(const T& v, const updateTypes::SetTo<T>& upd, size_t length) { return upd.isId_ ? v : upd.value_ * length; }
};
