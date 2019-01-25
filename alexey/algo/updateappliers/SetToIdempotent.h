#pragma once
#include "algo/updateappliers/UpdateApplier.hpp"

template <typename T, typename IdempotentFunctor>
struct UpdateApplier<updateTypes::SetTo<T>, IdempotentFunctor> {
    static T apply(const T& v, const updateTypes::SetTo<T>& upd, size_t) { return upd.isId_ ? v : upd.value_; }
};
