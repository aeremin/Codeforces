#pragma once
#include "update_applier.h"
#include "algo/segment_tree/update_types/increase_by.h"

template <typename T, typename IdempotentFunctor>
struct UpdateApplier<update_types::IncreaseBy<T>, IdempotentFunctor> {
    static T apply(const T& v, const update_types::IncreaseBy<T>& upd, size_t) { return v + upd.value_; }
};
