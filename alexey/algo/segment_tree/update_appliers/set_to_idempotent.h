#pragma once
#include "update_applier.h"
#include "algo/segment_tree/update_types/set_to.h"

template <typename T, typename IdempotentFunctor>
struct UpdateApplier<update_types::SetTo<T>, IdempotentFunctor> {
    static T apply(const T& v, const update_types::SetTo<T>& upd, size_t) { return upd.isId_ ? v : upd.value_; }
};
