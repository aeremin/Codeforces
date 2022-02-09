#pragma once
#include "update_applier.h"
#include "algo/segment_tree/update_types/multiply_by.h"

template <typename T, typename Functor>
struct UpdateApplier<update_types::MultiplyBy<T>, Functor> {
    static T apply(const T& v, const update_types::MultiplyBy<T>& upd, size_t) { return upd.value_ * v; }
};
