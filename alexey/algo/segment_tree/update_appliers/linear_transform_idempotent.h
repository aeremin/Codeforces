#pragma once
#include "update_applier.h"
#include "algo/segment_tree/update_types/linear_transform.h"

template <typename T, typename IdempotentFunctor>
struct UpdateApplier<update_types::LinearTransform<T>, IdempotentFunctor> {
    static T apply(const T& v, const update_types::LinearTransform<T>& upd, size_t) { return upd.a_ * v + upd.b_; }
};
