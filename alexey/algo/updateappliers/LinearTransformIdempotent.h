#pragma once
#include "algo/updateappliers/UpdateApplier.hpp"

template <typename T, typename IdempotentFunctor>
struct UpdateApplier<updateTypes::LinearTransform<T>, IdempotentFunctor> {
    static T apply(const T& v, const updateTypes::LinearTransform<T>& upd, size_t) { return upd.a_ * v + upd.b_; }
};
