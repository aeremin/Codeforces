#pragma once
#include "algo/segment_tree/update_appliers/update_applier.h"
#include "algo/segment_tree/update_types/increase_by.h"

template <typename T>
struct UpdateApplier<update_types::IncreaseBy<T>, std::plus<T>> {
    static T apply(const T& v, const update_types::IncreaseBy<T>& upd, size_t cnt) { return v + cnt * upd.value_; }
};
